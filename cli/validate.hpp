#ifndef SCILOG_CLI_VALIDATE_HPP_INCLUDED
#define SCILOG_CLI_VALIDATE_HPP_INCLUDED

#include <string>

using namespace std;

namespace scilog_cli
{
	void command_validate_month(const string&,const string&,bool);
	void command_validate_year(const string&);
	void command_validate_all_years();
	void command_validate_topics(const string&);
}

#endif // SCILOG_CLI_VALIDATE_HPP_INCLUDED
