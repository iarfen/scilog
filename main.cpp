#include "main.hpp"

#include "cli/create.hpp"
#include "cli/help.hpp"
#include "cli/list.hpp"
#include "cli/summary.hpp"
#include "cli/validate.hpp"
#include "cli/version.hpp"
#include "core/filesystem.hpp"

#include <cctype>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		return 0;
	}
	if (string(argv[1]) == "--help" or string(argv[1]) == "-h")
	{
		scilog_cli::help_command();
		return 0;
	}
	else if (string(argv[1]) == "--version" or string(argv[1]) == "-v")
	{
		scilog_cli::version_command();
		return 0;
	}
	else if (string(argv[1]) == "validate")
	{
		bool is_year_dir = scilog_cli::is_year_directory(".");
		if (argc == 2)
		{
			if (is_year_dir)
			{
				scilog_cli::validate_year_files(".");
			}
			else
			{
				scilog_cli::validate_all_year_files(".");
			}
		}
		else
		{
			bool topics = false;
			string month_selection;
			string year_selection;
			string first_argument = string(argv[2]);
			if (first_argument.substr(0,2) == "--")
			{
				month_selection = "none";
				year_selection = "none";
			}
			else if (isdigit(first_argument[0]) && stoi(first_argument) > 12)
			{
				year_selection = first_argument;
				month_selection = "none";
			}
			else
			{
				month_selection = first_argument;
				string second_argument;
				if (argc > 3)
				{
					second_argument = string(argv[3]);
				}
				if (isdigit(second_argument[0]) && stoi(second_argument) > 12)
				{
					if (is_year_dir)
					{
						year_selection = "../" + second_argument;
					}
					else
					{
						year_selection = second_argument;
					}
				}
				else
				{
					year_selection = ".";
				}
			}
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
			if (month_selection == "all" or (is_year_dir == false and month_selection == "none" and year_selection == "none"))
			{
				string directory_path;
				if (is_year_dir)
				{
					directory_path = "..";
				}
				else
				{
					directory_path = ".";
				}
				scilog_cli::validate_all_year_files(directory_path);
			}
			else if (month_selection == "none" or month_selection == ".")
			{
				scilog_cli::validate_year_files(year_selection);
			}
			else
			{
				if (topics)
				{
					scilog_cli::validate_topics_file(month_selection,year_selection);
				}
				else
				{
					scilog_cli::validate_month_file(month_selection,year_selection,true);
				}
			}
		}
		return 0;
	}
	else if (string(argv[1]) == "list")
	{
		bool is_year_dir = scilog_cli::is_year_directory(".");
		if (argc == 2)
		{
			if (is_year_dir)
			{
				scilog_cli::command_list_year(".",scilog_cli::list_type::all);
			}
			else
			{
				scilog_cli::command_list_all_years(".",scilog_cli::list_type::all);
			}
		}
		else
		{
			scilog_cli::list_type selected_type = scilog_cli::list_type::all;
			string month_selection;
			string year_selection;
			string first_argument = string(argv[2]);
			if (first_argument.substr(0,2) == "--")
			{
				month_selection = "none";
				year_selection = "none";
			}
			else if (isdigit(first_argument[0]) && stoi(first_argument) > 12)
			{
				year_selection = first_argument;
				month_selection = "none";
			}
			else
			{
				month_selection = first_argument;
				string second_argument;
				if (argc > 3)
				{
					second_argument = string(argv[3]);
				}
				if (isdigit(second_argument[0]) && stoi(second_argument) > 12)
				{
					if (is_year_dir)
					{
						year_selection = "../" + second_argument;
					}
					else
					{
						year_selection = second_argument;
					}
				}
				else
				{
					year_selection = ".";
				}
			}
			if (argc >= 3)
			{
				for (unsigned int i = 2; i < argc; i++)
				{
					if (string(argv[i]) == "--type=learn")
					{
						selected_type = scilog_cli::list_type::learn;
					}
					else if (string(argv[i]) == "--type=project")
					{
						selected_type = scilog_cli::list_type::project;
					}
				}
			}
			if (month_selection == "all" or (is_year_dir == false and month_selection == "none" and year_selection == "none"))
			{
				string directory_path;
				if (is_year_dir)
				{
					directory_path = "..";
				}
				else
				{
					directory_path = ".";
				}
				scilog_cli::command_list_all_years(directory_path,selected_type);
			}
			else if (month_selection == "none" or month_selection == ".")
			{
				scilog_cli::command_list_year(year_selection,selected_type);
			}
			else
			{
				scilog_cli::command_list_month(month_selection,year_selection,selected_type,true);
			}
		}
		return 0;
	}
	else if (string(argv[1]) == "create-month-file")
	{
		scilog_cli::create_month_file(string(argv[2]));
	}
	else if (string(argv[1]) == "create-year-files")
	{
		scilog_cli::create_year_files();
	}
	else if (string(argv[1]) == "list-categories")
	{
		scilog_cli::list_categories();
		return 0;
	}
	else if (string(argv[1]) == "summary")
	{
		bool is_year_dir = scilog_cli::is_year_directory(".");
		if (argc == 2)
		{
			if (is_year_dir)
			{
				scilog_cli::command_summary_year(".");
			}
			else
			{
				scilog_cli::command_summary_all_years(".");
			}
		}
		else
		{
			bool topics = false;
			bool sciences = false;
			string month_selection;
			string year_selection;
			string first_argument = string(argv[2]);
			if (first_argument.substr(0,2) == "--")
			{
				month_selection = "none";
				year_selection = "none";
			}
			else if (isdigit(first_argument[0]) && stoi(first_argument) > 12)
			{
				year_selection = first_argument;
				month_selection = "none";
			}
			else
			{
				month_selection = first_argument;
				string second_argument;
				if (argc > 3)
				{
					second_argument = string(argv[3]);
				}
				if (isdigit(second_argument[0]) && stoi(second_argument) > 12)
				{
					if (is_year_dir)
					{
						year_selection = "../" + second_argument;
					}
					else
					{
						year_selection = second_argument;
					}
				}
				else
				{
					year_selection = ".";
				}
			}
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
			if (month_selection == "all" or (is_year_dir == false and month_selection == "none" and year_selection == "none"))
			{
				string directory_path;
				if (is_year_dir)
				{
					directory_path = "..";
				}
				else
				{
					directory_path = ".";
				}
				if (topics)
				{
					scilog_cli::command_summary_all_years_by_topics(directory_path);
				}
				else if (sciences)
				{
					scilog_cli::command_summary_all_years_by_sciences(directory_path);
				}
				else
				{
					scilog_cli::command_summary_all_years(directory_path);
				}
			}
			else if (month_selection == "none" or month_selection == ".")
			{
				if (topics)
				{
					scilog_cli::command_summary_year_by_topics(year_selection);
				}
				else if (sciences)
				{
					scilog_cli::command_summary_year_by_sciences(year_selection);
				}
				else
				{
					scilog_cli::command_summary_year(year_selection);
				}
			}
			else
			{
				if (topics)
				{
					scilog_cli::command_summary_month_by_topics(month_selection,year_selection);
				}
				else if (sciences)
				{
					scilog_cli::command_summary_month_by_sciences(month_selection,year_selection);
				}
				else
				{
					scilog_cli::command_summary_month(month_selection,year_selection);
				}
			}
		}
		return 0;
	}
	return 0;
}
