#include <vector>
#include <algorithm>
#include "file_struct.h"

namespace sorts{

	void balance_merge(std::string name, const int& N){
		ifile R(name);
		std::vector<ofile> w(N);
		std::vector<ifile> r(N);
		std::vector<std::string> g(N);
		std::vector<int> t(N);//отображение индексов

		InitTitleList(g);

		//подключить обертки w к файлам g
		std::vector <std::string>::iterator it_g = g.begin();
		std::for_each(w.begin(), w.end(), [&it_g](ofile& f) { f.open_trunc(*it_g); ++it_g; });

		int j = 0, L = 0;
		//распределить начальные серии из R в w[0]...w[N-1]
		while (!R.f_eof()){
			//копировать одну серию из R в w[j]
			while (!R.f_eor())
				R.write_to(&w[j]);

			++j; ++L;
			if (j == N)
				j = 0;
		}

		auto of_close = [](ofile& f) { f.close(); };
		std::for_each(w.begin(), w.end(), of_close);

		while (L > 1){//слияние из r в w
			//переключить обертки r на файлы g
			int k1 = (L < N) ? L : N;
			int K1 = k1;

			//установить указатели на источники
			it_g = g.begin();
			std::for_each(r.begin(), r.begin() + k1, [&it_g](ifile& f) { f.open(*it_g); ++it_g; });

			//слить из r[0]...r[k1-1] в w[0]...w[K1-1]

			int i = 0;
			std::generate(t.begin(), t.begin() + k1, [&i](){return i++; });

			L = 0; j = 0;//j-индекс файла-приемника

			//слить по одной серии из каждого источника в w[j]
			while (k1 != 0){//все источники исчерпаны
				++L;
				int k2 = k1;

				while (k2 > 0){
					int m = 0;
					char r_min;
					r[t[0]].get(r_min);
					int i = 1;
					while (i < k2){
						char x;
						r[t[i]].get(x);
						if (x < r_min){
							r_min = x;
							m = i;
						}
						++i;
					}

					int pos;
					if (t[m] != j){
						pos = r[j].get_pos();
						r[j].close();
						w[j].open_app();
					}

					r[t[m]].write_to(&w[j]/*, t[m] == j*/);

					if (t[m] != j){
						w[j].close();
						r[j].open();
						r[j].set_pos(pos);
					}

					if (r[t[m]].f_eof()){//исключить последовательность
						//оичстим исключенную последовательность, но только если исключенная последовательность не равна той в которую писали на данной итерации
						if (t[m] != j){
							r[t[m]].close();
							w[t[m]].open_trunc();
							w[t[m]].close();
							r[t[m]].open();
						}
						//
						--k1;
						--k2;
						t[m] = t[k2];
						t[k2] = t[k1];
					}
					else if (r[t[m]].f_eor()){//закрыть серию
						--k2;
						std::swap(t[m], t[k2]);
					}
				}

				++j;

				if (j == K1) j = 0;
			}

			//установить указатели на источники
			std::for_each(r.begin(), r.end(), [](ifile& f) { f.close(); });
		}

		//отсортированный файл присоединен к w[0]
	}
}