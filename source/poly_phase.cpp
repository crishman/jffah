#include "poly_phase.h"
#include "ifile.h"
#include "ofile.h"
#include <vector>
#include <algorithm>

namespace sorts{

	//выбор приемника
	void select(std::vector<int>& d, std::vector<int>& a, int& j, int& level, int& z, const int& N){
		if (d[j] < d[j + 1])
			++j;
		else {
			if (d[j] == 0){
				++level;
				z = a[0];
				for (int i = 0; i < N - 1; ++i){
					d[i] = z + a[i + 1] - a[i];
					a[i] = z + a[i + 1];
				}
			}
			j = 0;
		}
		--d[j];
	}

	bool file_el_equal(ofile* r_j, const int& r_j_pos, ifile* R){
		char R_first;
		R->get(R_first);

		char r_j_first = r_j->get_by_pos(r_j_pos);
		
		return r_j_first <= R_first;
	}

	void poly_phase(std::string name, const int& N){
		ifile R(name);
		std::vector<ofile> r(N);//
		std::vector<int> a(N, 1);//идеальное число серий i-ой последовательности
		std::vector<int> d(N, 1);//фиктивное число серий i-ой последовательности
		std::vector<std::string> f(N);
		std::vector<int> read_pos(N, 0);

		{
			char c = 'a';
			std::generate(f.begin(), f.end(), [&c](){ std::string s;  return s = (c++); });
		}

		std::vector <std::string>::iterator it_f = f.begin();
		std::for_each(r.begin(), r.end(), [&it_f](ofile& f) { f.open_trunc(*it_f); ++it_f; });

		//распределеить начальные серии
		int level = 1;
		int j = 0;//текущая принимающая последовательность
		a[N - 1] = 0;
		d[N - 1] = 0;
		int z;

		while (!R.f_eof() && (j != N - 2)) {
			select(d, a, j, level, z, N);
			R.copyrun(&r[j]);
			read_pos[j] = r[j].get_pos() - 1;
		}
		while (!R.f_eof()){
			select(d, a, j, level, z, N);//r[j].get() - последний элемент, записанный в f[j]
			if (file_el_equal(&r[j], read_pos[j], &R)){
				R.copyrun(&r[j]);
				read_pos[j] = r[j].get_pos() - 1;
				if (R.f_eof())
					++d[j];
				else{
					R.copyrun(&r[j]);
					read_pos[j] = r[j].get_pos() - 1;
				}
			}
			else{
				R.copyrun(&r[j]);
				read_pos[j] = r[j].get_pos() - 1;
			}
		}

		std::vector<int> t(N), ta(N);
		for (int i = 0; i < N - 1; ++i){
			t[i] = i;
			//r[i].open(f[i]);???Зачем...мы и так находимся на этих позициях...
		}
		t[N - 1] = N - 1;

		std::fill(read_pos.begin(), read_pos.end(), 0);

		while (level != 0) {//слить из t[0]...t[N-2] в t[N-1]
			z = a[N - 2];
			d[N - 1] = 0;

			r[t[N - 1]].close();
			r[t[N - 1]].open_trunc();
			read_pos[t[N - 1]] = 0;

			while (z != 0){//слить одну серию
				int k = 0;
				for (int i = 0; i < N - 1; ++i){
					if (d[i] > 0)
						--d[i];
					else{
						ta[k] = t[i];
						++k;
					}
				}

				if (k == 0)
					++d[N - 1];
				else{//слить одну серию из t[0]..t[k-1] в t[N-1]
					while (k != 0){
						int mx = 0;
						char r_min = r[ta[0]].get_by_pos(read_pos[ta[0]]);
						int i = 1;

						while (i < k){
							char x = r[ta[i]].get_by_pos(read_pos[ta[i]]);
							if (x < r_min){
								r_min = x;
								mx = i;
							}
							++i;
						}
						
						int cur_ta = ta[mx];
						r[cur_ta].close();
						ifile r_temp(r[cur_ta]);
						r_temp.set_pos(read_pos[cur_ta]);
						r_temp.write_to(&r[t[N - 1]]);
						if (r_temp.f_eor()){
							ta[mx] = ta[k - 1];
							--k;
						}
						
						r_temp.close();
						r[cur_ta].open_app();
						r[cur_ta].set_pos(++read_pos[cur_ta]);
					}
				}
				--z;
			}

			//ротация последовательностей
			int tn = t[N - 1];
			int dn = d[N - 1];
			z = a[N - 2];

			for (int i = N - 1; i > 0; --i){
				t[i] = t[i - 1];
				d[i] = d[i - 1];
				a[i] = a[i - 1] - z;
			}

			t[0] = tn;
			d[0] = dn;
			a[0] = z;
			--level;
		}

		R.close();
		ofile R_out;
		r[t[0]].close();
		ifile r_temp(r[t[0]]);
		R_out.open_trunc(R);
		while (!r_temp.f_eof()){
			r_temp.write_to(&R_out);
		}
		r_temp.close();
		R_out.close();
	}
}