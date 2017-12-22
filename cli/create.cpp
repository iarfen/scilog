#include "create.hpp"
#include "core/scilog_file.hpp"

#include <fstream>

using namespace std;

namespace scilog_cli
{
	void create_month_file(const string& x)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		ofstream new_file (filename);

		new_file << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
		new_file << "<scilog>" << endl;
		new_file << "</scilog>" << endl;

		new_file.close();
	}

	void create_year_files()
	{
		create_month_file("1");
		create_month_file("2");
		create_month_file("3");
		create_month_file("4");
		create_month_file("5");
		create_month_file("6");
		create_month_file("7");
		create_month_file("8");
		create_month_file("9");
		create_month_file("10");
		create_month_file("11");
		create_month_file("12");
	}
}
