#include "validate.hpp"
#include "core/scilog_file.hpp"
#include "core/xml_parser.hpp"

#include <iostream>

using namespace std;

namespace scilog_cli
{
	void validate_month_file(const string& x)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		string result = scilog_cli::validate_scilog_file(filename);
		if (result != "")
		{
			cout << result;
		}
		else
		{
			cout << filename << " is a valid file!" << endl;
		}
	}

	void validate_year_files()
	{
		validate_month_file("1");
		validate_month_file("2");
		validate_month_file("3");
		validate_month_file("4");
		validate_month_file("5");
		validate_month_file("6");
		validate_month_file("7");
		validate_month_file("8");
		validate_month_file("9");
		validate_month_file("10");
		validate_month_file("11");
		validate_month_file("12");
	}
}
