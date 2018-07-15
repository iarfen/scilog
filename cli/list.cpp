#include "list.hpp"
#include "core/conf.hpp"
#include "core/filesystem.hpp"
#include "core/xml_parser.hpp"
#include "cli/cli.hpp"
#include "core/categories.hpp"

#include <iostream>

#include "boost/filesystem.hpp"
#include "cafi/cafi.hpp"

using namespace std;

namespace scilog_cli
{
	void command_list_month(const string& x,const string& year,entry_kind selected_type,const string& filtered_topic,const string& filtered_category,bool month_case)
	{
		string filename = cafi::get_filename_from_month(x);
		if (check_scilog_file(filename,year,month_case,month_case))
		{
			string filepath = cafi::root_dir + "/" + year + "/" + filename;
			vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath,x,year);
			const map<string,shared_ptr<topic>>& topics = get_all_topics_map();
			print_list(entries,selected_type,filtered_topic,filtered_category,topics);
		}
	}

	void command_list_year(const string& year,entry_kind selected_type,const string& filtered_topic,const string& filtered_category)
	{
		vector<string> year_months = cafi::get_year_months();
		for (const string& x_month : year_months)
		{
			string filename = cafi::get_filename_from_month(x_month);
			check_scilog_file(filename,year,false,true);
		}
		for (const string& x_month : year_months)
		{
			command_list_month(x_month,year,selected_type,filtered_topic,filtered_category,false);
		}
	}

	void command_list_all_years(entry_kind selected_type,const string& filtered_topic,const string& filtered_category)
	{
		map<string,vector<string>> months = cafi::get_all_years_months();
		for (const auto& x : months)
		{
			for (const string& x_month : x.second)
			{
				string filename = cafi::get_filename_from_month(x_month);
				check_scilog_file(filename,x.first,false,true);
			}
		}
		for (const auto& x : months)
		{
			for (const string& x_month : x.second)
			{
				command_list_month(x_month,x.first,selected_type,filtered_topic,filtered_category,false);
			}
		}
	}

	void command_list_categories()
	{
		vector<category> categories = get_all_categories();
		print_child_categories(categories,categories.front(),"",1);
	}

	void print_list(const vector<shared_ptr<entry>>& entries,entry_kind selected_type,const string& filtered_topic,const string& filtered_category,const map<string,shared_ptr<topic>>& topics)
	{
		for (const shared_ptr<entry>& entry : entries)
		{
			if (selected_type == entry_kind::learn and entry->get_kind() != "learn")
			{
				continue;
			}
			if (selected_type == entry_kind::project and entry->get_kind() != "project")
			{
				continue;
			}
			if (filtered_topic != "" and filtered_topic != entry->get_topic())
			{
				continue;
			}
			if (filtered_category != "" and topics.count(entry->get_topic()) == 0)
			{
				continue;
			}
			if (filtered_category != "" and topics.count(entry->get_topic()) > 0 and !is_parent_category(topics.at(entry->get_topic())->get_category(),filtered_category))
			{
				continue;
			}
			cout << scilog_cli::normal_text << "(" << entry->get_date() << ") ";
			if (entry->get_topic() != "")
			{
				cout << scilog_cli::cyan_text << entry->get_topic() << ": ";
			}
			cout << scilog_cli::normal_text << entry->get_description();
			if (entry->get_finished())
			{
				cout << scilog_cli::cyan_text << " finished";
			}
			cout << endl;
		}
	}

	void print_child_categories(const vector<category>& categories,const category& x_category,const string& actual_parent_category,int number)
	{
		for (const category& x_category : categories)
		{
			if (x_category.get_parent_category() == actual_parent_category)
			{
				cout << scilog_cli::cyan_text;
				for (int i = 1; i < number; i++)
				{
					cout << "-";
				}
				cout << scilog_cli::normal_text << x_category.get_name() << endl;
				print_child_categories(categories,x_category,x_category.get_name(),number + 1);
			}
		}
	}
}
