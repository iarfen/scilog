#include "open.hpp"

#include "core/conf.hpp"
#include "core/filesystem.hpp"

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void command_open(const string& x,const string& year)
	{
		if (WIN32)
		{
			string filepath;
			if (x != "topics")
			{
				string filename = scilog_cli::get_filename_from_month_number(x);
				filepath = root_dir + "/" + year + "/" + filename;
			}
			else
			{
				filepath = root_dir + "/" + year + "/topics.scilog_topics";
			}
			string command = "\"" + regex_replace(filepath,regex("/"),"\\") + "\"";

			auto actual_time = chrono::system_clock::now();
			time_t now_c = chrono::system_clock::to_time_t(actual_time);
			tm* parts = localtime(&now_c);
			string actual_month = to_string(parts->tm_mon + 1);

			if (!boost::filesystem::exists(filepath) and (x == "now" or x == actual_month or x == ("0" + actual_month)))
			{
				ofstream new_file (filepath);
				new_file << "<?xml version='1.0' encoding='UTF-8'?>" << endl << "<scilog>" << endl << "</scilog>";
				new_file.close();
			}
			system(command.c_str());
		}
	}

	void command_open_directory()
	{
		string command;
		if (WIN32)
		{
			command = "explorer \"" + regex_replace(root_dir,regex("/"),"\\") + "\"";
		}
		system(command.c_str());
	}
}
