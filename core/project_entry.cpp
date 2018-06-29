#include "project_entry.hpp"

using namespace std;

namespace scilog_cli
{
	project_entry::project_entry() : entry()
	{
	}

	project_entry::project_entry(const string& new_type, const string& new_topic, const string& new_date, const string& new_description) : entry("project",new_type,new_topic,new_date,new_description)
	{
	}
}
