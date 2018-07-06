#ifndef SCILOG_CORE_PROJECT_TOPIC_HPP_INCLUDED
#define SCILOG_CORE_PROJECT_TOPIC_HPP_INCLUDED

#include "topic.hpp"

using namespace std;

namespace scilog_cli
{
	class project_topic : public topic
	{
		public:
			project_topic();
			project_topic(const string&,const string&,const string&,const string&,const string&,const string&);

			virtual topic_kind get_kind() const;
	};
}

#endif // SCILOG_CORE_PROJECT_TOPIC_HPP_INCLUDED
