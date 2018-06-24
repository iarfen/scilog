#ifndef SCILOG_LIST_HPP_INCLUDED
#define SCILOG_LIST_HPP_INCLUDED

#include "core/category.hpp"
#include "core/entry.hpp"
#include "core/topic.hpp"
#include "main.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace scilog_cli
{
	void command_list_month(const string&,const string&,const string&,entry_kind,const string&,const string&,bool);
	void command_list_year(const string&,const string&,entry_kind,const string&,const string&);
	void command_list_all_years(const string&,entry_kind,const string&,const string&);
	void command_list_categories();

	void print_list(const vector<shared_ptr<entry>>&,entry_kind,const string&,const string&,const map<string,shared_ptr<topic>>&);
	void print_child_categories(const vector<category>&,const category&,const string&,int);
}

#endif // SCILOG_LIST_HPP_INCLUDED
