#ifndef NATURAL_MERGE_H
#define NATURAL_MERGE_H
#include <string>

namespace sorts {
	/*
	//����������� �����
	void copyrun(ifile* from, ofile* to);
	//������� �����
	void mergerun(ofile* to, ifile* from1, ifile* from2);
	//�������
	void f_merge(ifile* from1, ifile* from2, ofile* to);
	//�������������
	void f_distribute(ifile* from, ofile* to1, ofile* to2);*/

	void natural_merge(std::string file_name);
}

#endif