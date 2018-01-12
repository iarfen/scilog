#ifndef SCILOG_CLI_VALIDATE_HPP_INCLUDED
#define SCILOG_CLI_VALIDATE_HPP_INCLUDED

#include <string>

using namespace std;

namespace scilog_cli
{
	void validate_month_file(const string&,const string&,bool);
	void validate_year_files(const string&);
	void validate_all_year_files(const string&);
	void validate_topics_file(const string&,const string&);
}

#endif // SCILOG_CLI_VALIDATE_HPP_INCLUDED
