#include "validate.hpp"
#include "cli/cli.hpp"
#include "core/conf.hpp"
#include "core/filesystem.hpp"
#include "core/xml_parser.hpp"

#include <iostream>

#include "boost/filesystem.hpp"
#include "cafi/cafi.hpp"

using namespace std;

namespace scilog_cli
{
	void command_validate_month(const string& x,const string& year,bool print_exist_message)
	{
		string filename = cafi::get_filename_from_month(x);
		string filepath = cafi::root_dir + "/" + year + "/" + filename;
		if (boost::filesystem::exists(filepath))
		{
			string result = scilog_cli::validate_scilog_file(filepath);
			if (result != "")
			{
				cout << scilog_cli::green_text << year << "/" << filename << scilog_cli::normal_text << " has errors" << endl;
				cout << result;
			}
			else
			{
				cout << scilog_cli::green_text << year << "/" << filename << scilog_cli::normal_text << " is valid" << endl;
			}
		}
		else
		{
			if (print_exist_message)
			{
				print_non_exist_message(year + "/" + filename);
			}
		}
	}

	void command_validate_year(const string& year)
	{
		command_validate_month("1",year,false);
		command_validate_month("2",year,false);
		command_validate_month("3",year,false);
		command_validate_month("4",year,false);
		command_validate_month("5",year,false);
		command_validate_month("6",year,false);
		command_validate_month("7",year,false);
		command_validate_month("8",year,false);
		command_validate_month("9",year,false);
		command_validate_month("10",year,false);
		command_validate_month("11",year,false);
		command_validate_month("12",year,false);
		command_validate_topics(year);
	}

	void command_validate_all_years()
	{
		vector<string> years_path = cafi::get_years_path(cafi::root_dir);
		for (const string& x_year : years_path)
		{
			command_validate_year(cafi::get_last_directory(x_year));
		}
	}

	void command_validate_topics(const string& year)
	{
		string filepath = cafi::root_dir + "/" + year + "/topics.scilog_topics";
		if (boost::filesystem::exists(filepath))
		{
			string result = scilog_cli::validate_topics_xml_file(filepath);
			if (result != "")
			{
				cout << scilog_cli::green_text << year << "/topics.scilog_topics" << scilog_cli::normal_text << " has errors" << endl;
				cout << result;
			}
			else
			{
				cout << scilog_cli::green_text << year << "/topics.scilog_topics" << scilog_cli::normal_text << " is valid" << endl;
			}
		}
		else
		{
			print_non_exist_message(year + "/topics.scilog_topics");
		}
	}
}
