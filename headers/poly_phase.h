#ifndef POLY_PHASE_H
#define POLY_PHASE_H


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

	bool file_first_el_equal(ofile* r_j, ifile* R){
		int R_pos = R->get_pos();
		R->set_pos(0);
		char R_first;
		R->get(R_first);
		R->set_pos(R_pos);
		
		char r_j_first = r_j->get_first();

		return r_j_first <= R_first;
	}

	void copyrun(ifile* R, ofile* r_j){
		while (!R->f_eor())
			R->write_to(r_j);
	}

	void poly_phase(std::string name, const int& N){
		ifile R(name);
		std::vector<ofile> r(N);
		std::vector<int> a(N, 1), d(N, 1);
		std::vector<std::string> f(N);

		InitTitleList(f);	

		//распределеить начальные серии
		int level = 1;
		int j = 0;
		a[N - 1] = 0;
		d[N - 1] = 0;
		int z;

		while (!R.f_eof() && (j != N-2)) {
			select(d, a, j, level, z, N);
			copyrun(&R, &r[j]);
		}
		while (!R.f_eof()){
			select(d, a, j, level, z, N);//r[j].get() - последний элемент, записанный в f[j]
			if (file_first_el_equal(&r[j], &R)){
				copyrun(&R, &r[j]);
				if (R.f_eof())
					++d[j];
				else
					copyrun(&R, &r[j]);
			} else
				copyrun(&R, &r[j]);
		}

		std::vector<int> t(N), ta(N);
		for (int i = 0; i < N - 2; ++i){
			t[i] = i;
			//r[i].open(f[i]);???Зачем...мы и так находимся на этих позициях...
		}
		t[N - 1] = N - 1;

		while (level != 0) {//слить из t[0]...t[N-2] в t[N-1]
			z = a[N - 2];
			d[N - 1] = 0;

			r[t[N - 1]].close();
			r[t[N - 1]].open_trunc();

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

				if (k = 0)
					++d[N - 1];
				else{//слить одну серию из t[0]..t[k-1] в t[N-1]
					while (k != 0){
						int mx = 0;
						char r_min = r[ta[0]].get_first();

						int i = 1;
						while (i < k){
							char x = r[ta[i]].get_first();
							if (x < r_min){
								r_min = x;
								mx = i;								
							}
							++i;
						}

						r[ta[mx]]
						ifile r_temp(r[])
					}
				}
			}
		}		
	}
}

#endif