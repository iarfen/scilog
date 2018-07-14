#include "topics.hpp"

#include "core/conf.hpp"
#include "core/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	map<string,shared_ptr<topic>> all_topics = map<string,shared_ptr<topic>>();

	void initialize_all_topics()
	{
		vector<string> years_path = get_years_path(root_dir);
		vector<shared_ptr<topic>> vector_topics = get_all_years_topics(years_path);
		for (const shared_ptr<topic>& x_topic : vector_topics)
		{
			all_topics[x_topic->get_name()] = x_topic;
		}
	}
}
