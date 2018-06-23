#ifndef SCILOG_CLI_CREATE_HPP_INCLUDED
#define SCILOG_CLI_CREATE_HPP_INCLUDED

#include <string>

using namespace std;

namespace scilog_cli
{
	void command_create_month_file(const string&);
	void command_create_year_files();

	void command_create_sql_dump_month(const string&,const string&,const string&,const string&);
	void command_create_sql_dump_year(const string&,const string&,const string&);
	void command_create_sql_dump_all_years(const string&,const string&);
}

#endif // SCILOG_CLI_CREATE_HPP_INCLUDED
