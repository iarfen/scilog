#include "version.hpp"

#include "config.hpp"

#include <iostream>

using namespace std;

namespace scilog_cli
{
	void command_version()
	{
		cout << PACKAGE_NAME << " " << PACKAGE_VERSION << endl;
	}
}
