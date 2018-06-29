#include "learn_entry.hpp"

using namespace std;

namespace scilog_cli
{
	learn_entry::learn_entry() : entry(),page_point()
	{
	}

	learn_entry::learn_entry(const string& new_type, const string& new_topic, const string& new_date, const string& new_description,int new_page_point) : entry("learn",new_type,new_topic,new_date,new_description),page_point(new_page_point)
	{
	}
}
