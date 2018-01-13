#include "create.hpp"
#include "core/filesystem.hpp"

#include <fstream>

using namespace std;

namespace scilog_cli
{
	void command_create_month_file(const string& x)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		ofstream new_file (filename);

		new_file << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
		new_file << "<scilog>" << endl;
		new_file << "</scilog>" << endl;

		new_file.close();
	}

	void command_create_year_files()
	{
		command_create_month_file("1");
		command_create_month_file("2");
		command_create_month_file("3");
		command_create_month_file("4");
		command_create_month_file("5");
		command_create_month_file("6");
		command_create_month_file("7");
		command_create_month_file("8");
		command_create_month_file("9");
		command_create_month_file("10");
		command_create_month_file("11");
		command_create_month_file("12");
	}
}
