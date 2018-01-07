#ifndef SCILOG_CORE_SCILOG_FILE_HPP_INCLUDED
#define SCILOG_CORE_SCILOG_FILE_HPP_INCLUDED

#include "category.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace scilog_cli
{
	string get_filename_from_month_number(const string&);
	vector<category> get_all_categories();
	map<string,category> get_all_categories_map();
}

#endif // SCILOG_CORE_SCILOG_FILE_HPP_INCLUDED
