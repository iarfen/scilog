#include "create.hpp"
#include "cli/cli.hpp"
#include "core/filesystem.hpp"
#include "core/sql_parser.hpp"
#include "core/xml_parser.hpp"

#include <iostream>
#include <fstream>

#include "boost/filesystem.hpp"

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

	void command_create_sql_dump_month(const string& x,const string& directory_path,const string& table_prefix)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		string filepath = directory_path + "/" + filename;
		if (boost::filesystem::exists(filepath))
		{
			vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath);
			vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(directory_path + "/topics.xml");
			print_sql_dump(entries,topics,table_prefix);
		}
		else
		{
			print_non_exist_message(filepath);
		}
	}

	void command_create_sql_dump_year(const string& directory_path,const string& table_prefix)
	{
		vector<shared_ptr<entry>> entries = get_year_entries(directory_path);
		vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(directory_path + "/topics.xml");
		print_sql_dump(entries,topics,table_prefix);
	}

	void command_create_sql_dump_all_years(const string& directory_path,const string& table_prefix)
	{
		vector<string> paths = get_years_path(directory_path);
		vector<shared_ptr<entry>> entries = get_all_years_entries(paths);
		vector<shared_ptr<topic>> topics = get_all_years_topics(paths);
		print_sql_dump(entries,topics,table_prefix);
	}
}
