#include "list.hpp"
#include "core/scilog_file.hpp"

#include "core/xml_parser.hpp"

#include <iostream>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void list_command(const string& x,list_type selected_type)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		if (boost::filesystem::exists(filename))
		{
			vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filename);
			for (const shared_ptr<entry>& entry : entries)
			{
				if (selected_type == list_type::learn and entry->get_type() != "learn")
				{
					continue;
				}
				if (selected_type == list_type::project and entry->get_type() != "project")
				{
					continue;
				}
				cout << "(" << entry->get_date() << ") ";
				if (entry->get_topic() != "")
				{
					cout << entry->get_topic() << ": ";
				}
				cout << entry->get_description() << endl;
			}
		}
		else
		{
			cout << "The requested month doesn't exist" << endl;
		}
	}

	void list_categories()
	{
		vector<category> categories = get_all_categories();
		print_child_categories(categories,categories.front(),"",1);
	}

	void print_child_categories(const vector<category>& categories,const category& x_category,const string& actual_parent_category,int number)
	{
		for (const category& x_category : categories)
		{
			if (x_category.get_parent_category() == actual_parent_category)
			{
				for (int i = 1; i < number; i++)
				{
					cout << "-";
				}
				cout << x_category.get_name() << endl;
				print_child_categories(categories,x_category,x_category.get_name(),number + 1);
			}
		}
	}
}
