#include "learn_entry.hpp"

#include "core/entries.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "cafi/cafi.hpp"

using namespace std;

namespace scilog_cli
{
	learn_entry::learn_entry() : entry(),page_point()
	{
	}

	learn_entry::learn_entry(const string& new_type, const string& new_topic, const string& new_date, const string& new_description,bool new_finished,int new_page_point) : entry("learn",new_type,new_topic,new_date,new_description,new_finished),page_point(new_page_point)
	{
	}

	int previous_pages(const string& x_topic,const string& date)
	{
		string actual_month = date.substr(5,2);
		string actual_year = date.substr(0,4);
		string month;
		string year;
		if (actual_month != "01")
		{
			month = to_string(stoi(actual_month) - 1);
			year = date.substr(0,4);
		}
		else
		{
			month = "12";
			year = to_string(stoi(actual_year) - 1);
		}
		vector<shared_ptr<entry>> entries = get_entries(month,year);
		auto it = find_if(entries.begin(),entries.end(),[x_topic](shared_ptr<entry>& a) -> bool { a->get_topic() == x_topic; });
		if (it != entries.end())
		{
			shared_ptr<learn_entry> selected_entry = dynamic_pointer_cast<learn_entry>(*it);
			return selected_entry->get_page_point();
		}
		else
		{
			if (!cafi::exists_previous_month_file(month,year))
			{
				return 0;
			}
			if (month == "1" or month == "01")
			{
				return previous_pages(x_topic,to_string(stoi(year) - 1) + "-12-01");
			}
			else
			{
				return previous_pages(x_topic,year + "-" + to_string(stoi(month) - 1) + "-01");
			}
		}
	}
}
