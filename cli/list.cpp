#include "list.hpp"
#include "core/filesystem.hpp"
#include "core/xml_parser.hpp"
#include "cli/cli.hpp"

#include <iostream>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void command_list_month(const string& x,const string& directory_path,const string& year,entry_kind selected_type,const string& filtered_topic,bool print_exist_message)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		string filepath = directory_path + "/" + filename;
		if (boost::filesystem::exists(filepath))
		{
			vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath,x,year);
			print_list(entries,selected_type,filtered_topic);
		}
		else
		{
			if (print_exist_message)
			{
				print_non_exist_message(filepath);
			}
		}
	}

	void command_list_year(const string& directory_path,const string& year,entry_kind selected_type,const string& filtered_topic)
	{
		command_list_month("1",directory_path,year,selected_type,filtered_topic,false);
		command_list_month("2",directory_path,year,selected_type,filtered_topic,false);
		command_list_month("3",directory_path,year,selected_type,filtered_topic,false);
		command_list_month("4",directory_path,year,selected_type,filtered_topic,false);
		command_list_month("5",directory_path,year,selected_type,filtered_topic,false);
		command_list_month("6",directory_path,year,selected_type,filtered_topic,false);
		command_list_month("7",directory_path,year,selected_type,filtered_topic,false);
		command_list_month("8",directory_path,year,selected_type,filtered_topic,false);
		command_list_month("9",directory_path,year,selected_type,filtered_topic,false);
		command_list_month("10",directory_path,year,selected_type,filtered_topic,false);
		command_list_month("11",directory_path,year,selected_type,filtered_topic,false);
		command_list_month("12",directory_path,year,selected_type,filtered_topic,false);
	}

	void command_list_all_years(const string& directory_path,entry_kind selected_type,const string& filtered_topic)
	{
		boost::filesystem::directory_iterator end_itr;
		for (boost::filesystem::directory_iterator itr(directory_path); itr != end_itr; ++itr)
		{
			if (is_directory(itr->status()))
			{
				string cwd = itr->path().generic_string();
				command_list_year(itr->path().generic_string(),get_directory(cwd),selected_type,filtered_topic);
			}
		}
	}

	void command_list_categories()
	{
		vector<category> categories = get_all_categories();
		print_child_categories(categories,categories.front(),"",1);
	}

	void print_list(const vector<shared_ptr<entry>>& entries,entry_kind selected_type,const string& filtered_topic)
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
			cout << scilog_cli::normal_text << "(" << entry->get_date() << ") ";
			if (entry->get_topic() != "")
			{
				cout << scilog_cli::green_text << entry->get_topic() << ": ";
			}
			cout << scilog_cli::normal_text << entry->get_description() << endl;
		}
	}

	void print_child_categories(const vector<category>& categories,const category& x_category,const string& actual_parent_category,int number)
	{
		for (const category& x_category : categories)
		{
			if (x_category.get_parent_category() == actual_parent_category)
			{
				cout << scilog_cli::green_text;
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
