#ifndef NATURAL_MERGE_H
#define NATURAL_MERGE_H
#include <string>

namespace sorts {
	/*
	//копирование серии
	void copyrun(ifile* from, ofile* to);
	//слияние серии
	void mergerun(ofile* to, ifile* from1, ifile* from2);
	//слияние
	void f_merge(ifile* from1, ifile* from2, ofile* to);
	//распределение
	void f_distribute(ifile* from, ofile* to1, ofile* to2);*/

	void natural_merge(std::string file_name);
}

#endif