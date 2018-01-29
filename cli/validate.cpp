#include "validate.hpp"
#include "cli/cli.hpp"
#include "core/filesystem.hpp"
#include "core/xml_parser.hpp"

#include <iostream>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void command_validate_month(const string& x,const string& directory_path,bool print_exist_message)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		string filepath = directory_path + "/" + filename;
		if (boost::filesystem::exists(filepath))
		{
			string result = scilog_cli::validate_scilog_file(filepath);
			if (result != "")
			{
				cout << scilog_cli::green_text << filepath << scilog_cli::white_text << " is an invalid file" << endl;
				cout << result;
			}
			else
			{
				cout << scilog_cli::green_text << filepath << scilog_cli::white_text << " is a valid file" << endl;
			}
		}
		else
		{
			if (print_exist_message)
			{
				print_non_exist_message(filepath);
			}
		}
	}

	void command_validate_year(const string& directory_path)
	{
		command_validate_month("1",directory_path,false);
		command_validate_month("2",directory_path,false);
		command_validate_month("3",directory_path,false);
		command_validate_month("4",directory_path,false);
		command_validate_month("5",directory_path,false);
		command_validate_month("6",directory_path,false);
		command_validate_month("7",directory_path,false);
		command_validate_month("8",directory_path,false);
		command_validate_month("9",directory_path,false);
		command_validate_month("10",directory_path,false);
		command_validate_month("11",directory_path,false);
		command_validate_month("12",directory_path,false);
		command_validate_topics("topics.scilog_topics",directory_path);
	}

	void command_validate_all_years(const string& directory_path)
	{
		boost::filesystem::directory_iterator end_itr;
		for (boost::filesystem::directory_iterator itr(directory_path); itr != end_itr; ++itr)
		{
			if (is_directory(itr->status()))
			{
				command_validate_year(itr->path().generic_string());
			}
		}
	}

	void command_validate_topics(const string& filename,const string& directory_path)
	{
		string filepath = directory_path + "/" + filename;
		if (boost::filesystem::exists(filepath))
		{
			string result = scilog_cli::validate_topics_xml_file(filepath);
			if (result != "")
			{
				cout << scilog_cli::green_text << filepath << scilog_cli::white_text << " is an invalid file" << endl;
				cout << result;
			}
			else
			{
				cout << scilog_cli::green_text << filepath << scilog_cli::white_text << " is a valid file" << endl;
			}
		}
		else
		{
			print_non_exist_message(filepath);
		}
	}
}
