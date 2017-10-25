#ifndef FILE_STRUCT_H
#define FILE_STRUCT_H

#include <string>
#include <fstream>

namespace sorts{

	class file_no_name_exception{}

	void InitTitleList(std::vector<std::string> &titles){
		char c = 'a';
		std::generate(titles.begin(), titles.end(), [&c](){ std::string s;  return s = (c++); });
	}
}

#endif