#include "validate.hpp"
#include "core/scilog_file.hpp"
#include "core/xml_parser.hpp"

#include <iostream>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void validate_month_file(const string& x,const string& directory_path,bool print_exist_message)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		if (boost::filesystem::exists(directory_path + "/" + filename))
		{
			string result = scilog_cli::validate_scilog_file(directory_path + "/" + filename);
			if (result != "")
			{
				cout << result;
			}
			else
			{
				cout << (directory_path + "/" + filename) << " is a valid file!" << endl;
			}
		}
		else
		{
			if (print_exist_message)
			{
				cout << (directory_path + "/" + filename) << " file doesn't exist" << endl;
			}
		}
	}

	void validate_year_files(const string& x)
	{
		validate_month_file("1",x,false);
		validate_month_file("2",x,false);
		validate_month_file("3",x,false);
		validate_month_file("4",x,false);
		validate_month_file("5",x,false);
		validate_month_file("6",x,false);
		validate_month_file("7",x,false);
		validate_month_file("8",x,false);
		validate_month_file("9",x,false);
		validate_month_file("10",x,false);
		validate_month_file("11",x,false);
		validate_month_file("12",x,false);
		validate_topics_file(x + "/" + "topics.xml");
	}

	void validate_all_year_files()
	{
		boost::filesystem::directory_iterator end_itr;
		for (boost::filesystem::directory_iterator itr("."); itr != end_itr; ++itr)
		{
			if (is_directory(itr->status()))
			{
				validate_year_files(itr->path().generic_string());
			}
		}
	}

	void validate_topics_file(const string& x)
	{
		if (boost::filesystem::exists(x))
		{
			string result = scilog_cli::validate_topics_xml_file(x);
			if (result != "")
			{
				cout << result;
			}
			else
			{
				cout << x << " is a valid file!" << endl;
			}
		}
		else
		{
			cout << x << " file doesn't exist" << endl;
		}
	}
}
