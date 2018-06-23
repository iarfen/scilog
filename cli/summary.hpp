#ifndef SCILOG_CLI_SUMMARY_HPP_INCLUDED
#define SCILOG_CLI_SUMMARY_HPP_INCLUDED

#include "core/entry.hpp"
#include "core/topic.hpp"

#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace scilog_cli
{
	void command_summary_month(const string&,const string&,const string&);
	void command_summary_month_by_topics(const string&,const string&,const string&);
	void command_summary_month_by_sciences(const string&,const string&,const string&);

	void command_summary_year(const string&,const string&);
	void command_summary_year_by_topics(const string&,const string&);
	void command_summary_year_by_sciences(const string&,const string&);

	void command_summary_all_years(const string&);
	void command_summary_all_years_by_topics(const string&);
	void command_summary_all_years_by_sciences(const string&);

	void print_summary(const vector<shared_ptr<entry>>&);
	void print_topics(const vector<shared_ptr<entry>>&);
	void print_sciences(const vector<shared_ptr<entry>>&,vector<shared_ptr<topic>>&);
}

#endif // SCILOG_CLI_SUMMARY_HPP_INCLUDED
