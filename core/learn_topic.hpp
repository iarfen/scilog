#ifndef SCILOG_CORE_LEARN_TOPIC_HPP_INCLUDED
#define SCILOG_CORE_LEARN_TOPIC_HPP_INCLUDED

#include "core/topic.hpp"

using namespace std;

namespace scilog_cli
{
	class learn_topic : public topic
	{
		public:
			learn_topic();
			learn_topic(const string&,const string&,const string&,const string&,const string&,const string&,const int&);

			inline int& get_pages()
			{
				return pages;
			}

			inline const int& get_pages() const
			{
				return pages;
			}

			virtual topic_kind get_kind() const;

		private:
			int pages;
	};
}

#endif // SCILOG_CORE_LEARN_TOPIC_HPP_INCLUDED
