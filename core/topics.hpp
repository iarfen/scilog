#ifndef SCILOG_CORE_TOPICS_HPP_INCLUDED
#define SCILOG_CORE_TOPICS_HPP_INCLUDED

#include "topic.hpp"

#include <map>
#include <string>

using namespace std;

namespace scilog_cli
{
	extern map<string,shared_ptr<topic>> all_topics;

	void initialize_all_topics();
}

#endif // SCILOG_CORE_TOPICS_HPP_INCLUDED
