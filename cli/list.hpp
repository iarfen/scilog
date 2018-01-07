#ifndef SCILOG_LIST_HPP_INCLUDED
#define SCILOG_LIST_HPP_INCLUDED

#include "core/category.hpp"
#include "main.hpp"

#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace scilog_cli
{
	void list_command(const string&,list_type);
	void list_categories();
	void print_child_categories(const vector<category>&,const category&,const string&,int);
}

#endif // SCILOG_LIST_HPP_INCLUDED
