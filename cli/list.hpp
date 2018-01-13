#ifndef SCILOG_LIST_HPP_INCLUDED
#define SCILOG_LIST_HPP_INCLUDED

#include "core/category.hpp"
#include "core/entry.hpp"
#include "main.hpp"

#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace scilog_cli
{
	void command_list_month(const string&,const string&,list_type,bool);
	void command_list_year(const string&,list_type);
	void command_list_all_years(const string&,list_type);
	void list_categories();
	void print_list(const vector<shared_ptr<entry>>&,list_type);
	void print_child_categories(const vector<category>&,const category&,const string&,int);
}

#endif // SCILOG_LIST_HPP_INCLUDED
