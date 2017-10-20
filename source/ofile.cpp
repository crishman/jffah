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

	void ofile::open_trunc(const ifile& other){
		open_trunc(other.name_);
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

	int ofile::get_pos(){
		return file_.tellp();
	}

	void ofile::set_pos(int pos){
		file_.seekp(pos);
		file_.clear();
	}

	char ofile::get_by_pos(int pos){
		close();
		ifile temp(name_);
		temp.set_pos(pos);
		char ch;
		temp.get(ch);
		temp.close();
		open_app();
		return ch;
	}

	bool ofile::is_open() const{
		return file_.is_open();
	}
}