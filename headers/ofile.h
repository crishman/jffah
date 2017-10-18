#ifndef OFILE_H
#define OFILE_H

#include <string>
#include <fstream>

namespace sorts{
	struct ofile {
		ofile();
		explicit ofile(std::string name);
		~ofile();

		void open_trunc(std::string name = "");
		void open_app(std::string name = "");
		void close();
		void put(char& c);
		char get_first();

		friend struct ifile;
	private:
		std::string name_;
		std::ofstream file_;
	};
}

#endif 
