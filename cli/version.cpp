#include "version.hpp"

#include "config.hpp"

#include <iostream>

using namespace std;

namespace scilog_cli
{
	void version_command()
	{
		cout << PACKAGE_NAME << " " << PACKAGE_VERSION << endl;
	}
}
