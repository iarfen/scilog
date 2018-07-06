#include "topic.hpp"

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
		for (const shared_ptr<topic>& topic : topics_vector)
		{
			topics_map[topic->get_name()] = topic;
		}
		return topics_map;
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
