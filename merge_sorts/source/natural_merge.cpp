//#define _CRT_SECURE_NO_WARNINGS

#include "natural_merge.h"
#include "ifile.h"
#include "ofile.h"

namespace sorts {

	struct L_series {
		static void incL() { ++L; }
		static void set_L_value_0() { L = 0; }
		static bool L_is_equal_to_1() { return L == 1; }
	private:
		static int L;
	};
	int L_series::L = 0;
	
	//������� �����
	void mergerun(ofile* to, ifile* from1, ifile* from2) {
		char from1_c, from2_c;

		while (true){
			from1->get(from1_c);
			from2->get(from2_c);

			if (from1_c < from2_c) {
				from1->write_to(to);
				if (from1->f_eor()){
					from2->copyrun(to);
					break;
				}
			}
			else {
				from2->write_to(to);
				if (from2->f_eor()){
					from1->copyrun(to);
					break;
				}
			}
		}
	}

	//�������
	void f_merge(ifile* from1, ifile* from2, ofile* to) {
		while (!from1->f_eof() && !from2->f_eof()) {
			mergerun(to, from1, from2);
			L_series::incL();
		}

		while (!from1->f_eof()) {
			from1->copyrun(to);
			L_series::incL();
		}

		while (!from2->f_eof()) {
			from2->copyrun(to);
			L_series::incL();
		}
	}

	//�������������
	void f_distribute(ifile* from, ofile* to1, ofile* to2) {
		while (!from->f_eof()) {
			from->copyrun(to1);
			if (!from->f_eof())
				from->copyrun(to2);
		}
	}

	void natural_merge(std::string file_name) {
		L_series::set_L_value_0();
		while (!L_series::L_is_equal_to_1()) {
			{
				ifile r2(file_name);
				ofile r0("a");
				ofile r1("b");

				//������������� c � a � b
				f_distribute(&r2, &r0, &r1);
			}

			{
				ofile r2(file_name);
				ifile r0("a");
				ifile r1("b");

				L_series::set_L_value_0();
				//������� a � b � c
				f_merge(&r0, &r1, &r2);
			}
		}
	}
}