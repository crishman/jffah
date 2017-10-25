#include "ifile.h"
#include "ofile.h"

namespace sorts{
	ifile::ifile()
	: name_("")
	, eor_(false)
	{}

	ifile::ifile(std::string name)
	: name_(name)
	, file_(name_, std::ios_base::in)
	, eor_(false)
	{}

	ifile::ifile(const ofile& out)
	: name_(out.name_)
	, file_(name_, std::ios_base::in)
	, eor_(false)
	{}

	ifile::~ifile() { 
		file_.close();
	}

	void ifile::open(std::string name)  {
		if (!name.empty())
			name_ = name;
		//if (name_.empty())
		//	throw file_no_name_exception();
		file_.open(name_, std::ios_base::in);
		file_.seekg(0);
		eor_ = false;
	}

	void ifile::close() {
		file_.close();
	}

	void ifile::get(char& c) {
		if (file_.get(c))
			file_.unget();
	}

	void ifile::write_to(ofile* out){
		//if write in himself
		if (name_ == out->name_){			
			char c_temp;
			if (file_.get(c_temp)){
				bool temp_eor = true;

				char c_temp2;
				if (file_.get(c_temp2)){
					file_.unget();
					if (c_temp2 < c_temp)
						temp_eor = true;
					else
						temp_eor = false;
				}

				int pos = get_pos();
				close();

				out->open_app();
				out->put(c_temp);
				out->close();

				open();
				eor_ = temp_eor;				
				set_pos(pos);								
			}
		}
		else {
			char temp;
			if (file_.get(temp)){
				char next;
				if (file_.get(next)){
					file_.unget();
					//if next element is less than the current then it's end of run
					if (next < temp)
						eor_ = true;
				}
				else
					eor_ = true;
				out->put(temp);
			}
			else
				eor_ = true;
		}
	}

	void ifile::copyrun(ofile* to) {
		while (!f_eor())
			write_to(to);
	}

	bool ifile::is_one_run(){
		int cur_pos = get_pos();

		while (!f_eof()){
			char test_ch;
			if (file_.get(test_ch)){
				char test_next_ch;
				if (file_.get(test_next_ch)){
					file_.unget();
					if (test_next_ch < test_ch){
						set_pos(cur_pos);
						return false;
					}
				}
			}
		}

		set_pos(cur_pos);
		return true;
	}

	int ifile::get_pos() {
		return file_.tellg(); 
	}

	void ifile::set_pos(const int& pos) {
		file_.seekg(pos);
		file_.clear();
	}

	bool ifile::f_eof() {
		return file_.eof();
	}

	bool ifile::f_eor() {
		if (eor_){
			//to avoid  loops, reset the eor_
			//so, this check is work at one moment
			eor_ = false;
			return true;
		}
		else
			return false;
	}

	bool ifile::is_open() const{
		return file_.is_open();
	}
}