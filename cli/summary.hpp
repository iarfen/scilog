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
	void command_summary_month(const string&,const string&,bool);
	void command_summary_month_by_topics(const string&,const string&,bool);
	void command_summary_month_by_sciences(const string&,const string&,bool);

	void command_summary_year(const string&,bool);
	void command_summary_year_by_topics(const string&,bool);
	void command_summary_year_by_sciences(const string&,bool);

	void command_summary_all_years();
	void command_summary_all_years_by_topics();
	void command_summary_all_years_by_sciences();

	void print_summary(vector<shared_ptr<entry>>&);
	void print_topics(const vector<shared_ptr<entry>>&);
	void print_sciences(const vector<shared_ptr<entry>>&,const map<string,shared_ptr<topic>>&);
}

#endif // SCILOG_CLI_SUMMARY_HPP_INCLUDED
