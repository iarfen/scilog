#include "list_topics.hpp"
#include "core/filesystem.hpp"
#include "core/xml_parser.hpp"

#include <iostream>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void command_list_topics_year(const string& directory_path)
	{
		string filepath = directory_path + "/topics.xml";
		if (boost::filesystem::exists(filepath))
		{
			vector<shared_ptr<topic>> topics = scilog_cli::create_topics_from_scilog_file(filepath);
			print_topics(topics);
		}
		else
		{
			print_non_exist_message(filepath);
		}
	}

	void command_list_topics_all_years(const string& directory_path)
	{
		boost::filesystem::directory_iterator end_itr;
		for (boost::filesystem::directory_iterator itr(directory_path); itr != end_itr; ++itr)
		{
			if (is_directory(itr->status()))
			{
				command_list_topics_year(itr->path().generic_string());
			}
		}
	}

	void print_topics(const vector<shared_ptr<topic>>& topics)
	{
		for (const shared_ptr<topic>& x_topic : topics)
		{
			cout << x_topic->get_name() << ": " << x_topic->get_description() << endl;
		}
	}
}
