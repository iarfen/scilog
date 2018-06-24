#include "filesystem.hpp"
#include "categories.hpp"
#include "xml_parser.hpp"
#include "cli/cli.hpp"

#include <chrono>
#include <iostream>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	string get_filename_from_month_number(const string& x)
	{
		if (x == "1" or x == "01" or x == "january")
		{
			return "01-january.scilog";
		}
		else if (x == "2" or x == "02" or x == "february")
		{
			return "02-february.scilog";
		}
		else if (x == "3" or x == "03" or x == "march")
		{
			return "03-march.scilog";
		}
		else if (x == "4" or x == "04" or x == "april")
		{
			return "04-april.scilog";
		}
		else if (x == "5" or x == "05" or x == "may")
		{
			return "05-may.scilog";
		}
		else if (x == "6" or x == "06" or x == "june")
		{
			return "06-june.scilog";
		}
		else if (x == "7" or x == "07" or x == "july")
		{
			return "07-july.scilog";
		}
		else if (x == "8" or x == "08" or x == "august")
		{
			return "08-august.scilog";
		}
		else if (x == "9" or x == "09" or x == "september")
		{
			return "09-september.scilog";
		}
		else if (x == "10" or x == "october")
		{
			return "10-october.scilog";
		}
		else if (x == "11" or x == "november")
		{
			return "11-november.scilog";
		}
		else if (x == "12" or x == "december")
		{
			return "12-december.scilog";
		}
		else if (x == "now")
		{
			time_t current_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
			tm* current_tm = localtime(&current_time);
			return get_filename_from_month_number(to_string(current_tm->tm_mon + 1));
		}
		else
		{
			return x;
		}
	}

	string get_month_number_from_filename(const string& x)
	{
		if (x == "01-january.scilog")
		{
			return "1";
		}
		else if (x == "02-february.scilog")
		{
			return "2";
		}
		else if (x == "03-march.scilog")
		{
			return "3";
		}
		else if (x == "04-april.scilog")
		{
			return "4";
		}
		else if (x == "05-may.scilog")
		{
			return "5";
		}
		else if (x == "06-june.scilog")
		{
			return "6";
		}
		else if (x == "07-july.scilog")
		{
			return "7";
		}
		else if (x == "08-august.scilog")
		{
			return "8";
		}
		else if (x == "09-september.scilog")
		{
			return "9";
		}
		else if (x == "10-october.scilog")
		{
			return "10";
		}
		else if (x == "11-november.scilog")
		{
			return "11";
		}
		else if (x == "12-december.scilog")
		{
			return "12";
		}
	}

	vector<category> get_all_categories()
	{
		vector<category> categories;
		if (boost::filesystem::exists("topics.scilog_topics"))
		{
			categories = create_categories_from_scilog_file("topics.scilog_topics");
		}
		for (const auto& default_category : default_categories)
		{
			categories.push_back(default_category.second);
		}
		return categories;
	}

	map<string,category> get_all_categories_map()
	{
		map<string,category> categories = default_categories;
		if (boost::filesystem::exists("topics.scilog_topics"))
		{
			vector<category> topic_categories = create_categories_from_scilog_file("topics.scilog_topics");
			if (topic_categories.size() > 0)
			{
				for (const category& x_category : topic_categories)
				{
					categories[x_category.get_name()] = x_category;
				}
			}
		}
		return categories;
	}

	vector<shared_ptr<topic>> get_all_topics()
	{
		vector<shared_ptr<topic>> topics;
		if (boost::filesystem::exists("topics.scilog_topics"))
		{
			topics = create_topics_from_scilog_file("topics.scilog_topics");
		}
		return topics;
	}

	map<string,shared_ptr<topic>> get_all_topics_map()
	{
		vector<shared_ptr<topic>> vector_topics = get_all_topics();
		return create_topics_map(vector_topics);
	}

	bool is_year_directory(const string& directory_path)
	{
		vector<string> filenames = {"01-january","02-february","03-march","04-april","05-may","06-june","07-july","08-august","09-september","10-october","11-november","12-december"};
		for (const string& filename : filenames)
		{
			if (boost::filesystem::exists(directory_path + "/" + filename + ".scilog"))
			{
				return true;
			}
		}
		if (boost::filesystem::exists(directory_path + "/" + "topics.scilog_topics"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	string get_current_directory_year()
	{
		string cwd = boost::filesystem::current_path().generic_string();
		if (is_year_directory(cwd))
		{
			return get_directory(cwd);
		}
		else
		{
			auto x = chrono::system_clock::now();
			time_t now_c = chrono::system_clock::to_time_t(x);
			tm* parts = localtime(&now_c);
			return to_string(1900 + parts->tm_year);
		}
	}

	string get_directory(const string& cwd)
	{
		return cwd.substr(cwd.find_last_of("/") + 1);
	}

	vector<shared_ptr<entry>> get_year_entries(const string& directory_path,const string& year)
	{
		vector<shared_ptr<entry>> out_entries;
		vector<string> filenames = {"01-january","02-february","03-march","04-april","05-may","06-june","07-july","08-august","09-september","10-october","11-november","12-december"};

		for (const string& filename : filenames)
		{
			string filepath = directory_path + "/" + filename + ".scilog";
			if (!boost::filesystem::exists(filepath))
			{
				continue;
			}
			string month_number = get_month_number_from_filename(filename + ".scilog");
			vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath,month_number,year);
			out_entries.insert(out_entries.begin(),entries.begin(),entries.end());
		}
		return out_entries;
	}

	vector<shared_ptr<entry>> get_all_years_entries(vector<string> year_paths)
	{
		vector<shared_ptr<entry>> out_entries;
		for (const string& year_path : year_paths)
		{
			vector<shared_ptr<entry>> entries = get_year_entries(year_path,year_path.substr(2));
			out_entries.insert(out_entries.begin(),entries.begin(),entries.end());
		}
		return out_entries;
	}

	vector<shared_ptr<topic>> get_all_years_topics(vector<string> year_paths)
	{
		vector<shared_ptr<topic>> out_topics;
		for (const string& year_path : year_paths)
		{
			vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(year_path);
			out_topics.insert(out_topics.begin(),topics.begin(),topics.end());
		}
		return out_topics;
	}

	vector<string> get_years_path(const string& directory_path)
	{
		vector<string> paths;
		boost::filesystem::directory_iterator end_itr;
		for (boost::filesystem::directory_iterator itr(directory_path); itr != end_itr; ++itr)
		{
			if (is_directory(itr->status()))
			{
				paths.push_back(itr->path().generic_string());
			}
		}
		return paths;
	}

	void print_non_exist_message(const string& filepath)
	{
		cout << scilog_cli::green_text << filepath << scilog_cli::normal_text << " doesn't exist" << endl;
	}
}
