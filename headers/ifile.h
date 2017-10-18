#ifndef IFILE_H
#define IFILE_H

#include <string>
#include <fstream>

namespace sorts{
	struct ofile;

	struct ifile {
		ifile();
		explicit ifile(std::string name);
		explicit ifile(const ofile& out);
		~ifile();

		void open(std::string name = "");
		void close();

		//get element(char) at current position at ifile::file_
		void get(char& c);

		//write one element(char) from ifile::file_ to ofile::file_
		void write_to(ofile* out);

		//get cur pos from file_
		int get_pos();
		//set pos in file_
		void set_pos(const int& pos);

		//end of file
		bool f_eof();
		//end of run
		bool f_eor();

	private:
		std::string name_;
		std::ifstream file_;
		bool eor_;
	};
}

#endif