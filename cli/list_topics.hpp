#ifndef SCILOG_LIST_TOPICS_HPP_INCLUDED
#define SCILOG_LIST_TOPICS_HPP_INCLUDED

#include "core/topic.hpp"

#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace scilog_cli
{
	void command_list_topics_year(const string&,const string&);
	void command_list_topics_all_years(const string&);

	void print_topics(const vector<shared_ptr<topic>>&,const string&);
}

#endif // SCILOG_LIST_TOPICS_HPP_INCLUDED
