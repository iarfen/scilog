#include "help.hpp"

#include <iostream>

using namespace std;

namespace scilog_cli
{
	void help_command()
	{
		cout << "scilog is a command-line utility that tracks the science activity that the user has done during the day, in order to be able to have a summary of the week, of the month, and of the year, among any other useful information." << endl << endl;
		cout << "    scilog <command> <file>" << endl << endl;
		cout << "commands:" << endl;
		cout << "    --help,-h                            display this help message" << endl;
		cout << "    --version,-v                         display the version of sci-log" << endl << endl;
		cout << "    list <file>                          list all the entries of a scilog file" << endl;
		cout << "    list <file> --type=learn|project     list only entries of the selected type" << endl;
		cout << "    list <file> --type=learn" << endl
			 << "      --subtype=<value>                  list only entries of the selected subtype for learn entries:" << endl << endl;
		cout << "      for learn type: subtype=book|documentation|planification" << endl;
		cout << "    list <file> --type=project" << endl
			 << "      --subtype=<value>                  list only entries of the selected subtype for project entries:" << endl << endl;
		cout << "      for project type: subtype=programming|design|theory|planification" << endl;
		cout << "    list <file> --order_by=date|topic    list entries ordered by the value given" << endl;
		cout << "    summary-month <file>                 summarizes the work of the month" << endl;
		cout << "    summary-month <file> --topics        summarizes the topics worked and learned" << endl;
	}
}
