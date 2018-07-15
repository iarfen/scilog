#include "list_topics.hpp"
#include "core/conf.hpp"
#include "core/filesystem.hpp"
#include "core/learn_topic.hpp"
#include "core/xml_parser.hpp"
#include "cli/cli.hpp"
#include "core/categories.hpp"

#include <iostream>

#include "boost/filesystem.hpp"
#include "cafi/cafi.hpp"

using namespace std;

namespace scilog_cli
{
	void command_list_topics_year(const string& year,const string& filtered_category)
	{
		string filepath = cafi::root_dir + "/" + year + "/topics.scilog_topics";
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

	void command_list_topics_all_years(const string& filtered_category)
	{
		vector<string> years_path = cafi::get_years_path(cafi::root_dir);
		for (const string& x_year : years_path)
		{
			command_list_topics_year(cafi::get_last_directory(x_year),filtered_category);
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
			cout << scilog_cli::green_text << x_topic->get_name();
			if (x_topic->get_finished())
			{
				 cout << scilog_cli::cyan_text << " (finished)";
			}
			cout << scilog_cli::green_text << ": " << scilog_cli::normal_text << x_topic->get_description();
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
