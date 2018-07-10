#include "topic.hpp"

#include "learn_topic.hpp"
#include "project_topic.hpp"
#include "categories.hpp"

using namespace std;

namespace scilog_cli
{
	topic::topic() : category(),name(),start_date(),end_date(),description(),parent_topic()
	{
	}

	topic::topic(const string& new_category,const string& new_name,const string& new_start_date,const string& new_end_date,const string& new_description,const string& new_parent_topic) : category(new_category),name(new_name),start_date(new_start_date),end_date(new_end_date),description(new_description),parent_topic(new_parent_topic)
	{
	}

	topic_kind topic::get_kind() const
	{
		return topic_kind::project;
	}

	map<string,shared_ptr<topic>> create_topics_map(vector<shared_ptr<topic>> topics_vector)
	{
		map<string,shared_ptr<topic>> topics_map;
		for (const shared_ptr<topic>& data_topic : topics_vector)
		{
			topics_map[data_topic->get_name()] = data_topic;
		}
		return topics_map;
	}

	string default_topic_type(const map<string,shared_ptr<topic>>& topics,const string& data_topic,const string& kind)
	{
		if (topics.count(data_topic) > 0)
		{
			if (kind == "learn")
			{
				const shared_ptr<learn_topic>& x_learn_topic = dynamic_pointer_cast<learn_topic>(topics.at(data_topic));
				if (x_learn_topic->get_type() == "book" or x_learn_topic->get_type() == "documentation")
				{
					return "read";
				}
			}
			else if (kind == "project")
			{
				const shared_ptr<project_topic>& x_project_topic = dynamic_pointer_cast<project_topic>(topics.at(data_topic));
				if (is_parent_category(x_project_topic->get_category(),"application") or x_project_topic->get_category() == "website" or x_project_topic->get_category() == "library" or x_project_topic->get_category() == "videogame")
				{
					return "programming";
				}
			}
		}
		return "";
	}
}

bool operator ==(const scilog_cli::topic& x,const scilog_cli::topic& y)
{
	return (x.get_name() == y.get_name());
}

bool operator !=(const scilog_cli::topic& x,const scilog_cli::topic& y)
{
	return !(x == y);
}
