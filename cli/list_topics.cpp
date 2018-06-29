#include "list_topics.hpp"
#include "core/filesystem.hpp"
#include "core/learn_topic.hpp"
#include "core/xml_parser.hpp"
#include "cli/cli.hpp"
#include "core/categories.hpp"

#include <iostream>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void command_list_topics_year(const string& directory_path,const string& filtered_category)
	{
		string filepath = directory_path + "/topics.scilog_topics";
		if (boost::filesystem::exists(filepath))
		{
			vector<shared_ptr<topic>> topics = scilog_cli::create_topics_from_scilog_file(filepath);
			print_topics(topics,filtered_category);
		}
		else
		{
			print_non_exist_message(filepath);
		}
	}

	void command_list_topics_all_years(const string& directory_path,const string& filtered_category)
	{
		boost::filesystem::directory_iterator end_itr;
		for (boost::filesystem::directory_iterator itr(directory_path); itr != end_itr; ++itr)
		{
			if (is_directory(itr->status()))
			{
				command_list_topics_year(itr->path().generic_string(),filtered_category);
			}
		}
	}

	void print_topics(const vector<shared_ptr<topic>>& topics,const string& filtered_category)
	{
		for (const shared_ptr<topic>& x_topic : topics)
		{
			if (filtered_category != "" and !is_parent_category(x_topic->get_category(),filtered_category))
			{
				continue;
			}
			cout << scilog_cli::green_text << x_topic->get_name() << ": " << scilog_cli::normal_text << x_topic->get_description();
			if (x_topic->get_kind() == topic_kind::learn)
			{
				const shared_ptr<learn_topic>& x_learn_topic = dynamic_pointer_cast<learn_topic>(x_topic);
				if (x_learn_topic->get_pages() > 0)
				{
					cout << scilog_cli::green_text << " Pages: " << scilog_cli::normal_text << x_learn_topic->get_pages();
				}
			}
			cout << endl;
		}
	}
}
