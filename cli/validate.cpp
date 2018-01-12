#include "validate.hpp"
#include "core/filesystem.hpp"
#include "core/xml_parser.hpp"

#include <iostream>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void validate_month_file(const string& x,const string& directory_path,bool print_exist_message)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		string filepath = directory_path + "/" + filename;
		if (boost::filesystem::exists(filepath))
		{
			string result = scilog_cli::validate_scilog_file(filepath);
			if (result != "")
			{
				cout << filepath << " is an invalid file" << endl;
				cout << result;
			}
			else
			{
				cout << filepath << " is a valid file" << endl;
			}
		}
		else
		{
			if (print_exist_message)
			{
				cout << filepath << " file doesn't exist" << endl;
			}
		}
	}

	void validate_year_files(const string& directory_path)
	{
		validate_month_file("1",directory_path,false);
		validate_month_file("2",directory_path,false);
		validate_month_file("3",directory_path,false);
		validate_month_file("4",directory_path,false);
		validate_month_file("5",directory_path,false);
		validate_month_file("6",directory_path,false);
		validate_month_file("7",directory_path,false);
		validate_month_file("8",directory_path,false);
		validate_month_file("9",directory_path,false);
		validate_month_file("10",directory_path,false);
		validate_month_file("11",directory_path,false);
		validate_month_file("12",directory_path,false);
		validate_topics_file("topics.xml",directory_path);
	}

	void validate_all_year_files(const string& directory_path)
	{
		boost::filesystem::directory_iterator end_itr;
		for (boost::filesystem::directory_iterator itr(directory_path); itr != end_itr; ++itr)
		{
			if (is_directory(itr->status()))
			{
				validate_year_files(itr->path().generic_string());
			}
		}
	}

	void validate_topics_file(const string& filename,const string& directory_path)
	{
		string filepath = directory_path + "/" + filename;
		if (boost::filesystem::exists(filepath))
		{
			string result = scilog_cli::validate_topics_xml_file(filepath);
			if (result != "")
			{
				cout << filepath << " is an invalid file" << endl;
				cout << result;
			}
			else
			{
				cout << filepath << " is a valid file!" << endl;
			}
		}
		else
		{
			cout << filepath << " file doesn't exist" << endl;
		}
	}
}
