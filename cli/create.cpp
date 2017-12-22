#include "create.hpp"

#include <fstream>

using namespace std;

namespace scilog_cli
{
	void create_month_file(const string& month)
	{
		string filename;
		if (month == "1")
		{
			filename = "01-january";
		}
		else if (month == "2")
		{
			filename = "02-february";
		}
		else if (month == "3")
		{
			filename = "03-march";
		}
		else if (month == "4")
		{
			filename = "04-april";
		}
		else if (month == "5")
		{
			filename = "05-may";
		}
		else if (month == "6")
		{
			filename = "06-june";
		}
		else if (month == "7")
		{
			filename = "07-july";
		}
		else if (month == "8")
		{
			filename = "08-august";
		}
		else if (month == "9")
		{
			filename = "09-september";
		}
		else if (month == "10")
		{
			filename = "10-october";
		}
		else if (month == "11")
		{
			filename = "11-november";
		}
		else if (month == "12")
		{
			filename = "12-december";
		}

		ofstream new_file (filename + ".xml");

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
