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
				//real eor of this ifile
				bool temp_eor = true;
				//one run in file
				bool one_run = true;

				char c_temp2;
				if (file_.get(c_temp2)){
					file_.unget();
					if (c_temp2 < c_temp)
						temp_eor = true;
					else
						temp_eor = false;
				}

				//copy elements ifile[1]..ifile[N-1] to temp file, N = count of elements in ifile
				ofile fo_temp("temp");
				while (!f_eof()){
					write_to(&fo_temp);
					if (temp_eor && eor_ && !f_eof())
						one_run = false;
				}

				file_.close();

				//copy elements ifile[0] to end of temp file
				fo_temp.put(c_temp);
				fo_temp.close();

				//copy elements fo_temp[0]..fo_temp[N-1] to our file back, N = count of elements in fo_temp
				ifile fi_temp("temp");
				out->open_trunc();
				while (!fi_temp.f_eof())
					fi_temp.write_to(out);
				out->close();
				fi_temp.close();

				file_.open(name_);
				eor_ = temp_eor;
				//if ifile have one run and eor_ is true, then this sequence is ordered and set curent position in file_ at file_.end
				if (eor_ && one_run)
					file_.seekg(0, file_.end);
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

	int ifile::get_pos() {
		return file_.tellg(); 
	}

	void ifile::set_pos(const int& pos) {
		file_.clear();
		file_.seekg(pos);
	}

	bool ifile::f_eof() {
		char temp;
		if (file_.get(temp)){
			file_.unget();
			return false;
		}
		return true;
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
}