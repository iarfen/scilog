#include "list.hpp"

#include "core/xml_parser.hpp"

#include <iostream>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void list_command(const string& filename,list_type selected_type)
	{
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
}
