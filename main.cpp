#include "main.hpp"

#include "cli/create.hpp"
#include "cli/help.hpp"
#include "cli/list.hpp"
#include "cli/summary.hpp"
#include "cli/validate.hpp"
#include "cli/version.hpp"

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
		if (argc > 3)
		{
			return 0;
		}
		bool topics = false;
		for (unsigned int i = 2; i < argc; i++)
		{
			if (string(argv[i]) == "--topics")
			{
				topics = true;
			}
		}
		if (topics)
		{
			scilog_cli::validate_topics_file("topics.xml");
		}
		else if (argc == 3)
		{
			scilog_cli::validate_month_file(string(argv[2]));
		}
		else
		{
			scilog_cli::validate_year_files();
		}
		return 0;
	}
	else if (string(argv[1]) == "list")
	{
		scilog_cli::list_type selected_type = scilog_cli::list_type::all;
		if (argc > 3)
		{
			for (unsigned int i = 3; i < argc; i++)
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
		scilog_cli::list_command(string(argv[2]),selected_type);
		return 0;
	}
	else if (string(argv[1]) == "summary-year")
	{
		if (argc > 3)
		{
			return 0;
		}
		if (argc == 2)
		{
			scilog_cli::command_summary_year();
		}
		else
		{
			bool topics = false;
			for (unsigned int i = 2; i < argc; i++)
			{
				if (string(argv[i]) == "--topics")
				{
					topics = true;
				}
			}
			if (topics)
			{
				scilog_cli::command_summary_year_by_topics();
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
	else if (string(argv[2]) == "summary-month")
	{
		if (argc == 3)
		{
			scilog_cli::command_summary_month(string(argv[1]));
		}
		else
		{
			bool topics = false;
			for (unsigned int i = 3; i < argc; i++)
			{
				if (string(argv[i]) == "--topics")
				{
					topics = true;
				}
			}
			if (topics)
			{
				scilog_cli::command_summary_month_by_topics(string(argv[1]));
			}
		}
		return 0;
	}
	return 0;
}
