#include "conf.hpp"

#include "filesystem.hpp"

#include <cstdlib>
#include <iostream>

#include "boost/filesystem.hpp"
#include "conf/conf.hpp"

using namespace std;

namespace scilog_cli
{
	string root_dir = "";

	bool initialize_conf_file()
	{
		string conf_filepath = string(getenv("MINGW_HOME")) + "/etc/scilog.conf";
		if (is_scilog_directory())
		{
			root_dir = get_current_source_path();
			return true;
		}
		else if (boost::filesystem::exists(conf_filepath))
		{
			map<string,conf::variable> variables = conf::parse_file(conf_filepath);
			root_dir = string(variables["root_dir"]);
			return true;
		}
		else
		{
			cout << "scilog.conf not found" << endl;
		}
		return false;
	}
}
