#ifndef SCILOG_CORE_SCILOG_FILE_HPP_INCLUDED
#define SCILOG_CORE_SCILOG_FILE_HPP_INCLUDED

#include "core/category.hpp"
#include "core/entry.hpp"
#include "core/topic.hpp"

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

	bool is_year_directory(const string&);

	vector<shared_ptr<entry>> get_year_entries(const string&);
	vector<shared_ptr<entry>> get_all_years_entries(vector<string>);

	vector<shared_ptr<topic>> get_all_years_topics(vector<string>);

	vector<string> get_years_path(const string&);
}

#endif // SCILOG_CORE_SCILOG_FILE_HPP_INCLUDED
