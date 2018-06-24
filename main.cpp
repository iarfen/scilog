#include "main.hpp"

#include "cli/create.hpp"
#include "cli/help.hpp"
#include "cli/list.hpp"
#include "cli/list_topics.hpp"
#include "cli/summary.hpp"
#include "cli/validate.hpp"
#include "cli/version.hpp"
#include "core/filesystem.hpp"

#include <cctype>
#include <iostream>
#include <string>

#include "boost/filesystem.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		return 0;
	}
	if (string(argv[1]) == "--help" or string(argv[1]) == "-h")
	{
		scilog_cli::command_help();
		return 0;
	}
	else if (string(argv[1]) == "--version" or string(argv[1]) == "-v")
	{
		scilog_cli::command_version();
		return 0;
	}
	else if (string(argv[1]) == "fs")
	{
		scilog_cli::fs_args values = scilog_cli::fs_selection(argc,argv);
		return 0;
	}
	else if (string(argv[1]) == "validate")
	{
		scilog_cli::fs_args values = scilog_cli::fs_selection(argc,argv);
		bool topics = false;
		if (argc >= 3)
		{
			for (unsigned int i = 2; i < argc; i++)
			{
				string actual_argument = string(argv[i]);
				if (actual_argument == "--topics")
				{
					topics = true;
				}
			}
		}
		if (values.mode == scilog_cli::fs_mode::all)
		{
			scilog_cli::command_validate_all_years(values.directory_path);
			return 0;
		}
		else if (values.mode == scilog_cli::fs_mode::year)
		{
			scilog_cli::command_validate_year(values.directory_path);
			return 0;
		}
		else
		{
			if (topics)
			{
				scilog_cli::command_validate_topics(values.month_selection,values.directory_path);
				return 0;
			}
			else
			{
				scilog_cli::command_validate_month(values.month_selection,values.directory_path,true);
				return 0;
			}
		}
	}
	else if (string(argv[1]) == "list")
	{
		scilog_cli::fs_args values = scilog_cli::fs_selection(argc,argv);
		scilog_cli::entry_kind selected_type = scilog_cli::entry_kind::all;
		string filtered_topic = "";
		string filtered_category = "";
		if (argc >= 3)
		{
			for (unsigned int i = 2; i < argc; i++)
			{
				string actual_argument = string(argv[i]);
				if (actual_argument == "--kind=learn")
				{
					selected_type = scilog_cli::entry_kind::learn;
				}
				else if (actual_argument == "--kind=project")
				{
					selected_type = scilog_cli::entry_kind::project;
				}
				else if (actual_argument.substr(0,8) == "--topic=")
				{
					filtered_topic = actual_argument.substr(8);
				}
				else if (actual_argument.substr(0,11) == "--category=")
				{
					filtered_category = actual_argument.substr(11);
				}
			}
		}
		if (values.mode == scilog_cli::fs_mode::all)
		{
			scilog_cli::command_list_all_years(values.directory_path,selected_type,filtered_topic,filtered_category);
			return 0;
		}
		else if (values.mode == scilog_cli::fs_mode::year)
		{
			scilog_cli::command_list_year(values.directory_path,values.year_selection,selected_type,filtered_topic,filtered_category);
			return 0;
		}
		else
		{
			scilog_cli::command_list_month(values.month_selection,values.directory_path,values.year_selection,selected_type,filtered_topic,filtered_category,true);
			return 0;
		}
	}
	else if (string(argv[1]) == "list-topics")
	{
		scilog_cli::fs_args values = scilog_cli::fs_selection(argc,argv);
		string filtered_category = "";
		if (argc >= 3)
		{
			for (unsigned int i = 2; i < argc; i++)
			{
				string actual_argument = string(argv[i]);
				if (actual_argument.substr(0,11) == "--category=")
				{
					filtered_category = actual_argument.substr(11);
				}
			}
		}
		if (values.mode == scilog_cli::fs_mode::all)
		{
			scilog_cli::command_list_topics_all_years(values.directory_path,filtered_category);
			return 0;
		}
		else if (values.mode == scilog_cli::fs_mode::year)
		{
			scilog_cli::command_list_topics_year(values.directory_path,filtered_category);
			return 0;
		}
	}
	else if (string(argv[1]) == "create-month-file")
	{
		scilog_cli::command_create_month_file(string(argv[2]));
		return 0;
	}
	else if (string(argv[1]) == "create-year-files")
	{
		scilog_cli::command_create_year_files();
		return 0;
	}
	else if (string(argv[1]) == "create-sql-dump")
	{
		scilog_cli::fs_args values = scilog_cli::fs_selection(argc,argv);
		string table_prefix = "";
		if (argc >= 3)
		{
			for (unsigned int i = 2; i < argc; i++)
			{
				string actual_argument = string(argv[i]);
				if (actual_argument.substr(0,8) == "--prefix")
				{
					table_prefix = actual_argument.substr(9);
				}
			}
		}
		if (values.mode == scilog_cli::fs_mode::all)
		{
			scilog_cli::command_create_sql_dump_all_years(values.directory_path,table_prefix);
			return 0;
		}
		else if (values.mode == scilog_cli::fs_mode::year)
		{
			scilog_cli::command_create_sql_dump_year(values.directory_path,values.year_selection,table_prefix);
			return 0;
		}
		else
		{
			scilog_cli::command_create_sql_dump_month(values.month_selection,values.directory_path,values.year_selection,table_prefix);
			return 0;
		}
	}
	else if (string(argv[1]) == "list-categories")
	{
		scilog_cli::command_list_categories();
		return 0;
	}
	else if (string(argv[1]) == "summary")
	{
		scilog_cli::fs_args values = scilog_cli::fs_selection(argc,argv);
		bool topics = false;
		bool sciences = false;
		if (argc >= 3)
		{
			for (unsigned int i = 2; i < argc; i++)
			{
				string actual_argument = string(argv[i]);
				if (actual_argument == "--topics")
				{
					topics = true;
				}
				else if (actual_argument == "--sciences")
				{
					sciences = true;
				}
			}
		}
		if (values.mode == scilog_cli::fs_mode::all)
		{
			if (topics)
			{
				scilog_cli::command_summary_all_years_by_topics(values.directory_path);
			}
			else if (sciences)
			{
				scilog_cli::command_summary_all_years_by_sciences(values.directory_path);
			}
			else
			{
				scilog_cli::command_summary_all_years(values.directory_path);
			}
			return 0;
		}
		else if (values.mode == scilog_cli::fs_mode::year)
		{
			if (topics)
			{
				scilog_cli::command_summary_year_by_topics(values.directory_path,values.year_selection);
			}
			else if (sciences)
			{
				scilog_cli::command_summary_year_by_sciences(values.directory_path,values.year_selection);
			}
			else
			{
				scilog_cli::command_summary_year(values.directory_path,values.year_selection);
			}
			return 0;
		}
		else
		{
			if (topics)
			{
				scilog_cli::command_summary_month_by_topics(values.month_selection,values.directory_path,values.year_selection);
			}
			else if (sciences)
			{
				scilog_cli::command_summary_month_by_sciences(values.month_selection,values.directory_path,values.year_selection);
			}
			else
			{
				scilog_cli::command_summary_month(values.month_selection,values.directory_path,values.year_selection);
			}
			return 0;
		}
	}
	return 0;
}

namespace scilog_cli
{
	fs_args fs_selection(int argc, char* argv[])
	{
		fs_args values;
		values.is_year_dir = scilog_cli::is_year_directory(".");
		if (argc == 2)
		{
			if (values.is_year_dir)
			{
				values.mode = fs_mode::year;
			}
			else
			{
				values.mode = fs_mode::all;
			}
			values.directory_path = ".";
		}
		else
		{
			string first_argument = string(argv[2]);
			if (first_argument.substr(0,2) == "--")
			{
				values.month_selection = "none";
				values.year_selection = get_current_directory_year();
				values.directory_path = ".";
			}
			else if (isdigit(first_argument[0]) && stoi(first_argument) > 12)
			{
				values.year_selection = first_argument;
				values.directory_path = first_argument;
				values.month_selection = "none";
			}
			else
			{
				values.month_selection = first_argument;
				if (argc > 3)
				{
					string second_argument = string(argv[3]);
					if (isdigit(second_argument[0]) && stoi(second_argument) > 12)
					{
						values.year_selection = second_argument;
						if (values.is_year_dir)
						{
							values.directory_path = "../" + second_argument;
						}
						else
						{
							values.directory_path = second_argument;
						}
					}
					else
					{
						values.year_selection = get_current_directory_year();
						string cwd = boost::filesystem::current_path().generic_string();
						if (is_year_directory(cwd))
						{
							values.directory_path = ".";
						}
						else
						{
							values.directory_path = values.year_selection;
						}
					}
				}
				else
				{
					values.year_selection = get_current_directory_year();
					string cwd = boost::filesystem::current_path().generic_string();
					if (is_year_directory(cwd))
					{
						values.directory_path = ".";
					}
					else
					{
						values.directory_path = values.year_selection;
					}
				}
			}
			if (values.month_selection == "all" or (values.is_year_dir == false and values.month_selection == "none" and first_argument.substr(0,2) == "--"))
			{
				if (values.is_year_dir)
				{
					values.directory_path = "..";
				}
				else
				{
					values.directory_path = ".";
				}
				values.mode = fs_mode::all;
			}
			else if (values.month_selection == "none" or values.month_selection == ".")
			{
				values.mode = fs_mode::year;
			}
			else
			{
				values.mode = fs_mode::month;
			}
		}
		return values;
	}
}
