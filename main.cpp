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
		if (topics)
		{
			scilog_cli::command_validate_topics(values.directory_path,values.year_selection);
			return 0;
		}
		if (values.mode == scilog_cli::fs_mode::all)
		{
			scilog_cli::command_validate_all_years(values.directory_path);
			return 0;
		}
		else if (values.mode == scilog_cli::fs_mode::year)
		{
			scilog_cli::command_validate_year(values.directory_path,values.year_selection);
			return 0;
		}
		else
		{
			scilog_cli::command_validate_month(values.month_selection,values.directory_path,values.year_selection,true);
			return 0;
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
		bool each = false;
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
				else if (actual_argument == "--each")
				{
					each = true;
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
				scilog_cli::command_summary_year_by_topics(values.directory_path,values.year_selection,each);
			}
			else if (sciences)
			{
				scilog_cli::command_summary_year_by_sciences(values.directory_path,values.year_selection,each);
			}
			else
			{
				scilog_cli::command_summary_year(values.directory_path,values.year_selection,each);
			}
			return 0;
		}
		else
		{
			if (topics)
			{
				scilog_cli::command_summary_month_by_topics(values.month_selection,values.directory_path,values.year_selection,false);
			}
			else if (sciences)
			{
				scilog_cli::command_summary_month_by_sciences(values.month_selection,values.directory_path,values.year_selection,false);
			}
			else
			{
				scilog_cli::command_summary_month(values.month_selection,values.directory_path,values.year_selection,false);
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
		values.month_selection = "";
		values.year_selection = "";
		values.directory_path = "";
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
			for (unsigned int i = 2; i < argc; i++)
			{
				string actual_argument = string(argv[i]);
				if (actual_argument.substr(0,2) == "--")
				{
					continue;
				}
				else if (isdigit(actual_argument[0]))
				{
					int arg_number = stoi(actual_argument);
					if (arg_number > 12)
					{
						values.year_selection = actual_argument;
					}
					else
					{
						values.month_selection = actual_argument;
					}
				}
			}
			if (values.month_selection != "")
			{
				values.mode = fs_mode::month;
				if (values.year_selection == "")
				{
					values.year_selection = get_current_directory_year();
				}
			}
			else
			{
				if (values.year_selection == "")
				{
					if (values.is_year_dir)
					{
						values.mode = fs_mode::year;
						values.year_selection = get_current_directory_year();
					}
					else
					{
						values.mode = fs_mode::all;
					}
				}
				else
				{
					values.mode = fs_mode::year;
				}
			}
			if (values.mode != fs_mode::all)
			{
				if (values.is_year_dir)
				{
					values.directory_path = "../" + values.year_selection;
				}
				else
				{
					values.directory_path = values.year_selection;
				}
			}
			else
			{
				values.directory_path = ".";
			}
		}
		return values;
	}
}
