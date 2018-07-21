#include "main.hpp"

#include "cli/calendar.hpp"
#include "cli/create.hpp"
#include "cli/help.hpp"
#include "cli/list.hpp"
#include "cli/list_topics.hpp"
#include "cli/open.hpp"
#include "cli/summary.hpp"
#include "cli/validate.hpp"
#include "cli/version.hpp"
#include "core/filesystem.hpp"
#include "core/conf.hpp"

#include <cctype>
#include <iostream>
#include <string>

#include "boost/filesystem.hpp"
#include "cafi/cafi.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	if (!scilog_cli::initialize_conf_file())
	{
		return 0;
	}
	if (argc == 1)
	{
		cafi::arguments values = cafi::parse_commands(argc,argv);
		scilog_cli::command_open("now",values.year_selection);
		return 0;
	}
	string command = string(argv[1]);
	if (command == "--help" or command == "-h")
	{
		scilog_cli::command_help();
		return 0;
	}
	else if (command == "--version" or command == "-v")
	{
		scilog_cli::command_version();
		return 0;
	}
	else if (command == "calendar")
	{
		cafi::arguments values = cafi::parse_commands(argc,argv);
		if (values.month_selection == "")
		{
			values.month_selection = "now";
		}
		scilog_cli::command_calendar_month(values.month_selection,values.year_selection);
	}
	else if (command == "open")
	{
		cafi::arguments values = cafi::parse_commands(argc,argv);
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
		if (values.month_selection == "")
		{
			values.month_selection = "now";
		}
		if (topics)
		{
			scilog_cli::command_open("topics",values.year_selection);
		}
		else
		{
			scilog_cli::command_open(values.month_selection,values.year_selection);
		}
		return 0;
	}
	else if (command == "open-dir")
	{
		cafi::arguments values = cafi::parse_commands(argc,argv);
		scilog_cli::command_open_directory();
		return 0;
	}
	else if (command == "validate")
	{
		cafi::arguments values = cafi::parse_commands(argc,argv);
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
			scilog_cli::command_validate_topics(values.year_selection);
			return 0;
		}
		if (values.mode == cafi::cafi_mode::all)
		{
			scilog_cli::command_validate_all_years();
			return 0;
		}
		else if (values.mode == cafi::cafi_mode::year)
		{
			scilog_cli::command_validate_year(values.year_selection);
			return 0;
		}
		else
		{
			scilog_cli::command_validate_month(values.month_selection,values.year_selection,true);
			return 0;
		}
	}
	else if (command == "list")
	{
		cafi::arguments values = cafi::parse_commands(argc,argv);
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
		if (values.mode == cafi::cafi_mode::all)
		{
			scilog_cli::command_list_all_years(selected_type,filtered_topic,filtered_category);
			return 0;
		}
		else if (values.mode == cafi::cafi_mode::year)
		{
			scilog_cli::command_list_year(values.year_selection,selected_type,filtered_topic,filtered_category);
			return 0;
		}
		else
		{
			scilog_cli::command_list_month(values.month_selection,values.year_selection,selected_type,filtered_topic,filtered_category,true);
			return 0;
		}
	}
	else if (command == "list-topics")
	{
		cafi::arguments values = cafi::parse_commands(argc,argv);
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
		if (values.mode == cafi::cafi_mode::all)
		{
			scilog_cli::command_list_topics_all_years(filtered_category);
			return 0;
		}
		else if (values.mode == cafi::cafi_mode::year)
		{
			scilog_cli::command_list_topics_year(values.year_selection,filtered_category);
			return 0;
		}
	}
	else if (command == "create-month-file")
	{
		scilog_cli::command_create_month_file(string(argv[2]));
		return 0;
	}
	else if (command == "create-year-files")
	{
		scilog_cli::command_create_year_files();
		return 0;
	}
	else if (command == "create-sql-dump")
	{
		cafi::arguments values = cafi::parse_commands(argc,argv);
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
		if (values.mode == cafi::cafi_mode::all)
		{
			scilog_cli::command_create_sql_dump_all_years(table_prefix);
			return 0;
		}
		else if (values.mode == cafi::cafi_mode::year)
		{
			scilog_cli::command_create_sql_dump_year(values.year_selection,table_prefix);
			return 0;
		}
		else
		{
			scilog_cli::command_create_sql_dump_month(values.month_selection,values.year_selection,table_prefix);
			return 0;
		}
	}
	else if (command == "list-categories")
	{
		scilog_cli::command_list_categories();
		return 0;
	}
	else if (command == "summary")
	{
		cafi::arguments values = cafi::parse_commands(argc,argv);
		bool each = false;
		if (argc >= 3)
		{
			for (unsigned int i = 2; i < argc; i++)
			{
				string actual_argument = string(argv[i]);
				if (actual_argument == "--each")
				{
					each = true;
				}
			}
		}
		if (values.mode == cafi::cafi_mode::all)
		{
			scilog_cli::command_summary_all_years();
			return 0;
		}
		else if (values.mode == cafi::cafi_mode::year)
		{
			scilog_cli::command_summary_year(values.year_selection,each);
			return 0;
		}
		else
		{
			scilog_cli::command_summary_month(values.month_selection,values.year_selection,true);
			return 0;
		}
	}
	else if (command == "summary-topics")
	{
		cafi::arguments values = cafi::parse_commands(argc,argv);
		bool each = false;
		if (argc >= 3)
		{
			for (unsigned int i = 2; i < argc; i++)
			{
				string actual_argument = string(argv[i]);
				if (actual_argument == "--each")
				{
					each = true;
				}
			}
		}
		if (values.mode == cafi::cafi_mode::all)
		{
			scilog_cli::command_summary_all_years_by_topics();
			return 0;
		}
		else if (values.mode == cafi::cafi_mode::year)
		{
			scilog_cli::command_summary_year_by_topics(values.year_selection,each);
			return 0;
		}
		else
		{
			scilog_cli::command_summary_month_by_topics(values.month_selection,values.year_selection,true);
			return 0;
		}
	}
	else if (command == "summary-sciences")
	{
		cafi::arguments values = cafi::parse_commands(argc,argv);
		bool each = false;
		if (argc >= 3)
		{
			for (unsigned int i = 2; i < argc; i++)
			{
				string actual_argument = string(argv[i]);
				if (actual_argument == "--each")
				{
					each = true;
				}
			}
		}
		if (values.mode == cafi::cafi_mode::all)
		{
			scilog_cli::command_summary_all_years_by_sciences();
			return 0;
		}
		else if (values.mode == cafi::cafi_mode::year)
		{
			scilog_cli::command_summary_year_by_sciences(values.year_selection,each);
			return 0;
		}
		else
		{
			scilog_cli::command_summary_month_by_sciences(values.month_selection,values.year_selection,true);
			return 0;
		}
	}
	return 0;
}
