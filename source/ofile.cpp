#include "ofile.h"
#include "ifile.h"

namespace sorts{
	ofile::ofile()
		:name_("")
	{}

	ofile::ofile(std::string name)
		: name_(name)
		, file_(name_
		, std::ios_base::trunc)
	{}

	ofile::~ofile(){
		file_.close();
	}

	void ofile::open_trunc(std::string name) {
		if (!name.empty())
			name_ = name;
		//if (name_.empty())
		//	throw file_no_name_exception();
		file_.open(name_, std::ios_base::trunc);
	}

	void ofile::open_app(std::string name) {
		if (!name.empty())
			name_ = name;
		//if (name_.empty())
		//	throw file_no_name_exception();
		file_.open(name_, std::ios_base::app);
	}

	void ofile::close() {
		file_.close();
	}

	void ofile::put(char& c) {
		file_.put(c);
	}

	char ofile::get_first(){
		close();
		ifile temp(name_);
		char ch;
		temp.get(ch);
		temp.close();
		open_app();
		return ch;
	}
}