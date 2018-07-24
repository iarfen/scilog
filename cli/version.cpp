#include "version.hpp"

#include "config.hpp"

#include <iostream>

using namespace std;

namespace scilog_cli
{
	void command_version()
	{
		cout << PACKAGE_NAME << " " << PACKAGE_VERSION << endl;
		cout << "Copyright (C) " << PACKAGE_YEAR << " " << PACKAGE_AUTHOR << " " << PACKAGE_BUGREPORT << endl;
		cout << PACKAGE_WEBSITE << endl << endl;
		cout << "This program is free software, you can redistribute it under the terms of the GPLv3. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." << endl;
	}
}
