#ifndef FILE_STRUCT_H
#define FILE_STRUCT_H

#include <string>
#include <fstream>

namespace sorts{

	class file_no_name_exception{};
	struct ifile;

	struct ofile {
		ofile() :name_("") {}
		explicit ofile(std::string name) :name_(name), file_(name_, std::ios_base::trunc) {}
		~ofile() { file_.close(); }

		void open_trunc(std::string name = "") {
			if (!name.empty())
				name_ = name;
			if (name_.empty())
				throw file_no_name_exception();
			file_.open(name_, std::ios_base::trunc);
		}
		void open_app(std::string name = "") {
			if (!name.empty())
				name_ = name;
			if (name_.empty())
				throw file_no_name_exception();
			file_.open(name_, std::ios_base::app);
		}
		void close() { file_.close(); }
		void put(char& c) { file_.put(c); }

		char get_first(){
			close();
			ifile temp(name_);
			char ch;
			temp.get(ch);
			temp.close();
			open_app();
			return ch;
		}

		friend struct ifile;
	private:
		std::string name_;
		std::ofstream file_;
	};

	struct ifile {
		ifile() :name_(""), eor_(false){}
		explicit ifile(std::string name) : name_(name), file_(name_, std::ios_base::in), eor_(false){}
		explicit ifile(const ofile& out) :name_(out.name_), file_(name_, std::ios_base::in), eor_(false){}
		~ifile() { file_.close(); }

		void open(std::string name = "")  {
			if (!name.empty())
				name_ = name;
			if (name_.empty())
				throw file_no_name_exception();
			file_.open(name_, std::ios_base::in);
			file_.seekg(0);
			eor_ = false;
		}
		void close() {
			file_.close();
		}

		void get(char& c) {
			if (file_.get(c))
				file_.unget();
		}

		void write_to(ofile* out/*, bool himself_write = false*/){
			if (name_ == out->name_){
				char c_temp;
				if (file_.get(c_temp)){
					bool temp_eor = true;
					bool one_run = true;

					char c_temp2;
					if (file_.get(c_temp2)){
						file_.unget();
						if (c_temp2 < c_temp)
							temp_eor = true;
						else
							temp_eor = false;
					}

					ofile fo_temp("temp");
					while (!f_eof()){
						write_to(&fo_temp);
						if (temp_eor && eor_ && !f_eof())
							one_run = false;
					}

					file_.close();

					fo_temp.put(c_temp);
					fo_temp.close();

					ifile fi_temp("temp");
					out->open_trunc();
					while (!fi_temp.f_eof())
						fi_temp.write_to(out);
					out->close();
					fi_temp.close();

					file_.open(name_);
					eor_ = temp_eor;
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

		int get_pos() { return file_.tellg(); }
		void set_pos(const int& pos) {
			file_.clear();
			file_.seekg(pos);
		}

		bool f_eof() {
			char temp;
			if (file_.get(temp)){
				file_.unget();
				return false;
			}
			return true;
		}

		bool f_eor() {
			if (eor_){
				eor_ = false;
				return true;
			}
			else
				return false;
		}

	private:
		std::string name_;
		std::ifstream file_;
		bool eor_;
	};

	void InitTitleList(std::vector<std::string> &titles){
		char c = 'a';
		std::generate(titles.begin(), titles.end(), [&c](){ std::string s;  return s = (c++); });
	}
}

#endif