#ifndef SCILOG_CLI_SUMMARY_HPP_INCLUDED
#define SCILOG_CLI_SUMMARY_HPP_INCLUDED

#include <string>

using namespace std;

namespace scilog_cli
{
	void command_summary_month(const string&,const string&);
	void command_summary_month_by_topics(const string&);
	void command_summary_month_by_sciences(const string&);

	void command_summary_year(const string&);
	void command_summary_year_by_topics();
	//void summary_all_year_files();
}

#endif // SCILOG_CLI_SUMMARY_HPP_INCLUDED
