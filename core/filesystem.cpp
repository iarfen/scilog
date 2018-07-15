#include "filesystem.hpp"
#include "categories.hpp"
#include "topics.hpp"
#include "xml_parser.hpp"
#include "cli/cli.hpp"
#include "conf.hpp"

#include <chrono>
#include <iostream>
#include <string>

#include "boost/filesystem.hpp"
#include "cafi/cafi.hpp"

using namespace std;

namespace scilog_cli
{
	vector<category> get_all_categories()
	{
		vector<category> categories = vector<category>();
		for (const auto& x_category: default_categories)
		{
			categories.push_back(x_category.second);
		}
		vector<string> years_path = cafi::get_years_path(cafi::root_dir);
		vector<category> vector_categories = get_all_years_categories(years_path);
		for (const category& x_category : vector_categories)
		{
			categories.push_back(x_category);
		}
		return categories;
	}

	map<string,category>& get_all_categories_map()
	{
		if (all_categories.size() == 0)
		{
			initialize_all_categories();
		}
		return all_categories;
	}

	map<string,shared_ptr<topic>>& get_all_topics_map()
	{
		if (all_topics.size() == 0)
		{
			initialize_all_topics();
		}
		return all_topics;
	}

	vector<shared_ptr<entry>> get_year_entries(const string& year)
	{
		vector<shared_ptr<entry>> out_entries;
		vector<string> filenames = {"01-january","02-february","03-march","04-april","05-may","06-june","07-july","08-august","09-september","10-october","11-november","12-december"};

		for (const string& filename : filenames)
		{
			string filepath = cafi::root_dir + "/" + year + "/" + filename + ".scilog";
			if (!boost::filesystem::exists(filepath))
			{
				continue;
			}
			string month_number = cafi::get_month_from_filename(filename + ".scilog");
			vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath,month_number,year);
			out_entries.insert(out_entries.begin(),entries.begin(),entries.end());
		}
		return out_entries;
	}

	vector<category> get_all_years_categories(const vector<string>& year_paths)
	{
		vector<category> out_categories;
		for (const string& year_path : year_paths)
		{
			vector<category> categories = create_categories_from_scilog_file(year_path + "/topics.scilog_topics");
			out_categories.insert(out_categories.begin(),categories.begin(),categories.end());
		}
		return out_categories;
	}

	vector<shared_ptr<entry>> get_all_years_entries(const vector<string>& year_paths)
	{
		vector<shared_ptr<entry>> out_entries;
		for (const string& year_path : year_paths)
		{
			vector<shared_ptr<entry>> entries = get_year_entries(cafi::get_last_directory(year_path));
			if (entries.size() > 0)
			{
				out_entries.insert(out_entries.begin(),entries.begin(),entries.end());
			}
		}
		return out_entries;
	}

	vector<shared_ptr<topic>> get_all_years_topics(const vector<string>& year_paths)
	{
		vector<shared_ptr<topic>> out_topics;
		for (const string& year_path : year_paths)
		{
			vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(year_path + "/topics.scilog_topics");
			out_topics.insert(out_topics.begin(),topics.begin(),topics.end());
		}
		return out_topics;
	}

	void print_non_exist_message(const string& filepath)
	{
		cout << scilog_cli::green_text << filepath << scilog_cli::normal_text << " doesn't exist" << endl;
	}

	bool check_scilog_file(const string& filename,const string& year,bool print_non_exist,bool print_has_errors)
	{
		string filepath = cafi::root_dir + "/" + year + "/" + filename;
		if (boost::filesystem::exists(filepath))
		{
			string result = scilog_cli::validate_scilog_file(filepath);
			if (print_has_errors and result != "")
			{
				cout << scilog_cli::green_text << year << "/" << filename << scilog_cli::normal_text << " has errors" << endl;
			}
			return true;
		}
		else
		{
			if (print_non_exist)
			{
				print_non_exist_message(year + "/" + filename);
			}
			return false;
		}
	}

	bool check_scilog_topics_file(const string& filename,const string& year,bool print_non_exist,bool print_has_errors)
	{
		string filepath = cafi::root_dir + "/" + year + "/" + filename;
		if (boost::filesystem::exists(filepath))
		{
			string result = scilog_cli::validate_topics_xml_file(filepath);
			if (print_has_errors and result != "")
			{
				cout << scilog_cli::green_text << year << "/" << filename << scilog_cli::normal_text << " has errors" << endl;
			}
			return true;
		}
		else
		{
			if (print_non_exist)
			{
				print_non_exist_message(year + "/" + filename);
			}
			return false;
		}
	}
}
