#include "balance_merge.h"
#include <vector>
#include <algorithm>
#include "ifile.h"
#include "ofile.h"

namespace sorts{

	void balance_merge(const std::string& name, const int& N){
		ifile R(name);
		std::vector<ofile> w(N);
		std::vector<ifile> r(N);
		std::vector<std::string> g(N);
		std::vector<std::pair<int, int>> t(N);//����������� ��������

		{
			char c = 'a';
			std::generate(g.begin(), g.end(), [&c](){ std::string s;  return s = (c++); });
		}

		//���������� ������� w � ������ g
		std::vector <std::string>::iterator it_g = g.begin();
		std::for_each(w.begin(), w.end(), [&it_g](ofile& f) { f.open_trunc(*it_g); ++it_g; });

		int j = 0, L = 0;
		//������������ ��������� ����� �� R � w[0]...w[N-1]
		while (!R.f_eof()){
			//���������� ���� ����� �� R � w[j]
			while (!R.f_eor())
				R.write_to(&w[j]);

			++j; ++L;
			if (j == N)
				j = 0;
		}

		auto of_close = [](ofile& f) { f.close(); };
		std::for_each(w.begin(), w.end(), of_close);

		while (L > 1){//������� �� r � w
			//����������� ������� r �� ����� g
			int k1 = (L < N) ? L : N;
			int K1 = k1;

			//���������� ��������� �� ���������
			it_g = g.begin();
			std::for_each(r.begin(), r.begin() + k1, [&it_g](ifile& f) { f.open(*it_g); ++it_g; });			

			//����� �� r[0]...r[k1-1] � w[0]...w[K1-1]

			int i = 0;
			std::generate(t.begin(), t.begin() + k1, [&i](){return std::make_pair(i++, 0); });

			std::for_each(t.begin(), t.begin() + k1, [&r](const std::pair<int, int>& t_pair){ r[t_pair.first].set_pos(t_pair.second); });

			L = 0; j = 0;//j-������ �����-���������			

			//����� �� ����� ����� �� ������� ��������� � w[j]
			while (k1 != 0){//��� ��������� ���������
				++L;
				int k2 = k1;

				while (k2 > 0){
					int m = 0;
					char r_min;
					r[t[0].first].get(r_min);
					int i = 1;
					while (i < k2){
						char x;
						r[t[i].first].get(x);
						if (x < r_min){
							r_min = x;
							m = i;
						}
						++i;
					}

					int pos;
					if (t[m].first != j){
						pos = r[j].get_pos();
						r[j].close();
						w[j].open_app();
					}

					r[t[m].first].write_to(&w[j]);

					if (t[m].first != j){
						w[j].close();
						r[j].open();
						r[j].set_pos(pos);
					}

					if (r[t[m].first].f_eof()){//��������� ������������������
						//������� ����������� ������������������, �� ������ ���� ����������� ������������������ �� ����� ��� � ������� ������ �� ������ ��������
						if (t[m].first != j){
							r[t[m].first].close();
							w[t[m].first].open_trunc();
							w[t[m].first].close();
							r[t[m].first].open();
						}
						//
						--k1;
						--k2;
						t[m] = t[k2];
						t[k2] = t[k1];
					}
					else if (r[t[m].first].f_eor()){//������� �����
						--k2;
						std::swap(t[m], t[k2]);
					}
				}

				++j;

				if (j == K1) j = 0;
			}

			//���������� ��������� �� ���������
			std::for_each(r.begin(), r.end(), [](ifile& f) { f.close(); });
		}

		//��������������� ���� ����������� � w[0]
	}
}