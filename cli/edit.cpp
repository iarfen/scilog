#include "edit.hpp"

#include "core/filesystem.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;

namespace scilog_cli
{
	void command_edit(const string& x,const string& directory_path,const string& year)
	{
		if (WIN32)
		{
			string filename = scilog_cli::get_filename_from_month_number(x);
			string filepath = directory_path + "\\" + filename;
			string command = "\"" + filepath + "\"";
			system(command.c_str());
		}
	}
}
