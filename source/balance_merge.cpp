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
		std::vector<int> t(N);//����������� ��������
		std::vector<int> read_pos(N);

		{
			char c = 'a';
			std::generate(g.begin(), g.end(), [&c](){ std::string s;  return s = (c++); });
		}

		//���������� ������� w � ������ g
		//std::vector <std::string>::iterator it_g = g.begin();
		//std::for_each(w.begin(), w.end(), [&it_g](ofile& f) { f.open_trunc(*it_g); ++it_g; });

		int j = 0, L = 0;
		//������������ ��������� ����� �� R � w[0]...w[N-1]
		while (!R.f_eof()){
			//���������� ���� ����� �� R � w[j]
			while (!R.f_eor()){
				if (!w[j].is_open())
					w[j].open_trunc(g[j]);
				R.write_to(&w[j]);
			}

			++j; ++L;
			if (j == N)
				j = 0;
		}
		R.close();


		auto of_close = [](ofile& f) { f.close(); };
		std::for_each(w.begin(), w.end(), of_close);

		while (L > 1){//������� �� r � w
			//����������� ������� r �� ����� g
			int k1 = (L < N) ? L : N;
			int K1 = k1;

			//���������� ��������� �� ���������
			//it_g = g.begin();
			//std::for_each(r.begin(), r.begin() + k1, [&it_g](ifile& f) { f.open(*it_g); ++it_g; });			

			//����� �� r[0]...r[k1-1] � w[0]...w[K1-1]

			int i = 0;
			std::generate(t.begin(), t.begin() + k1, [&i](){return i++; });

			std::vector <std::string>::iterator it_g = g.begin();
			std::vector <int>::iterator it_read_pos = read_pos.begin();
			std::for_each(r.begin(), r.end(), [&it_g, &it_read_pos](ifile& f) {
				if (*it_read_pos > 0){
					if (f.is_open())
						f.open(*it_g);
					f.set_pos(*it_read_pos);
					++it_g;
					++it_read_pos;
				}
			});

			L = 0; j = 0;//j-������ �����-���������			

			//����� �� ����� ����� �� ������� ��������� � w[j]
			while (k1 != 0){//��� ��������� ���������		
				
				if (!r[t[0]].is_open())
					r[t[0]].open(g[t[0]]);

				if (k1 == 1 && r[t[0]].is_one_run()){
					--k1;
					break;
				}

				++L;
				int k2 = k1;

				while (k2 > 0){
					int m = 0;
					char r_min;
					if (!r[t[0]].is_open())
						r[t[0]].open(g[t[0]]);
					r[t[0]].get(r_min);
					int i = 1;
					while (i < k2){
						char x;
						if (!r[t[i]].is_open())
							r[t[i]].open(g[t[i]]);
						r[t[i]].get(x);
						if (x < r_min){
							r_min = x;
							m = i;
						}
						++i;
					}
										
					if (t[m] != j){
						if (r[t[0]].is_open()) {
							read_pos[j] = r[j].get_pos();
							r[j].close();
						}
						w[j].open_app();
					}

					r[t[m]].write_to(&w[j]);

					if (t[m] != j){
						w[j].close();
						if (read_pos[j] > 0){
							r[j].open();
							r[j].set_pos(read_pos[j]);
						}
					}

					if (r[t[m]].f_eof()){//��������� ������������������
						//������� ����������� ������������������, �� ������ ���� ����������� ������������������ �� ����� ��� � ������� ������ �� ������ ��������
						if (t[m] != j){
							if (r[t[m]].is_open())
								r[t[m]].close();
							w[t[m]].open_trunc();
							w[t[m]].close();
							//r[t[m]].open();
						}
						//
						--k1;
						--k2;
						t[m] = t[k2];
						t[k2] = t[k1];
					}
					else if (r[t[m]].f_eor()){//������� �����
						--k2;
						std::swap(t[m], t[k2]);
					}
				}
				if (!r[j].is_open())
					r[j].open();

				read_pos[j] = r[j].get_pos();
				++j;

				if (j == K1) j = 0;
			}

			//���������� ��������� �� ���������
			std::for_each(r.begin(), r.end(), [](ifile& f) { if(f.is_open()) f.close(); });
		}
		
		ofile R_out;
		R_out.open_trunc(R);
		if (!r[t[0]].is_open()){
			r[t[0]].open();
			r[t[0]].set_pos(read_pos[t[0]]);
		}
		while (!r[t[0]].f_eof()){
			r[t[0]].write_to(&R_out);
		}
		r[t[0]].close();
		R_out.close();
		//��������������� ���� ����������� � w[0]
	}
}