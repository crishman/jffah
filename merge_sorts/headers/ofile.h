#ifndef OFILE_H
#define OFILE_H

#include <string>
#include <fstream>

namespace sorts{
	struct ifile;

	struct ofile {
		ofile();
		explicit ofile(std::string name);
		~ofile();

		void open_trunc(std::string name = "");
		void open_trunc(const ifile& other);
		void open_app(std::string name = "");
		void close();
		void put(char& c);
		char get_by_pos(int pos);
		int get_pos();
		void set_pos(int pos);

		bool is_open() const;

		friend struct ifile;
	private:
		std::string name_;
		std::ofstream file_;
	};
}

#endif 
