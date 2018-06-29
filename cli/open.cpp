#include "open.hpp"

#include "core/filesystem.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;

namespace scilog_cli
{
	void command_open(const string& x,const string& directory_path,const string& year)
	{
		if (WIN32)
		{
			string filepath;
			if (x != "topics")
			{
				string filename = scilog_cli::get_filename_from_month_number(x);
				filepath = directory_path + "\\" + filename;
			}
			else
			{
				filepath = directory_path + "\\topics.scilog_topics";
			}
			string command = "\"" + filepath + "\"";
			system(command.c_str());
		}
	}
}
