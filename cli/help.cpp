#include "help.hpp"

#include <iostream>

using namespace std;

namespace scilog_cli
{
	void help_command()
	{
		cout << "sci-log is a command-line utility that tracks the science activity that the user has done during the day, in order to be able to have a summary of the week, of the month, and of the year, among any other useful information." << endl << endl;
		cout << "    sci-log <file> <command>" << endl << endl;
		cout << "commands:" << endl;
		cout << "    --help,-h                            display this help message" << endl;
		cout << "    --version,-v                         display the version of sci-log" << endl;
	}
}
