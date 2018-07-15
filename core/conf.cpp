#include "conf.hpp"

#include "cli/cli.hpp"
#include "filesystem.hpp"

#include <cstdlib>
#include <iostream>

#include "boost/filesystem.hpp"
#include "cafi/cafi.hpp"
#include "conf/conf.hpp"

using namespace std;

namespace scilog_cli
{
	bool initialize_conf_file()
	{
		string conf_filepath = string(getenv("MINGW_HOME")) + "/etc/scilog.conf";
		if (cafi::inside_cafi_directory())
		{
			cafi::initialize_cafi(cafi::get_cafi_root_directory(),"scilog",{"scilog_topics"});
			return true;
		}
		else if (boost::filesystem::exists(conf_filepath))
		{
			map<string,conf::variable> variables = conf::parse_file(conf_filepath);
			cafi::initialize_cafi(string(variables["root_dir"]),"scilog",{"scilog","scilog_topics"});
			if (boost::filesystem::exists(cafi::root_dir))
			{
				return true;
			}
			else
			{
				cout << scilog_cli::normal_text << "The root_dir " << scilog_cli::green_text << cafi::root_dir << scilog_cli::normal_text << " inside scilog.conf doesn't exists" << endl;
				return false;
			}
		}
		else
		{
			cout << "scilog.conf not found" << endl;
		}
		return false;
	}
}
