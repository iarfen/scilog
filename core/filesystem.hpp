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
	extern bool* is_year_dir;

	bool is_scilog_directory();
	bool is_year_directory(const string&);
	string get_current_source_path();
	string get_current_directory_year();
	string get_last_directory(const string&);

	string get_filename_from_month_number(const string&);
	string get_month_number_from_filename(const string&);

	vector<category> get_all_categories();
	map<string,category>& get_all_categories_map();

	map<string,shared_ptr<topic>>& get_all_topics_map();

	vector<shared_ptr<entry>> get_year_entries(const string&);

	vector<category> get_all_years_categories(const vector<string>&);
	vector<shared_ptr<entry>> get_all_years_entries(const vector<string>&);
	vector<shared_ptr<topic>> get_all_years_topics(const vector<string>&);

	vector<string> get_years_path(const string&);

	vector<string> get_year_months();
	map<string,vector<string>> get_all_years_months();

	void print_non_exist_message(const string&);

	bool check_scilog_file(const string&,const string&,bool,bool);
	bool check_scilog_topics_file(const string&,const string&,bool,bool);
}

#endif // SCILOG_CORE_SCILOG_FILE_HPP_INCLUDED
