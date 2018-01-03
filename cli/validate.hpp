#ifndef SCILOG_CLI_VALIDATE_HPP_INCLUDED
#define SCILOG_CLI_VALIDATE_HPP_INCLUDED

#include <string>

using namespace std;

namespace scilog_cli
{
	void validate_month_file(const string&);
	void validate_year_files();
	void validate_topics_file(const string&);
}

#endif // SCILOG_CLI_VALIDATE_HPP_INCLUDED
