#ifndef SCILOG_CORE_LEARN_TOPIC_HPP_INCLUDED
#define SCILOG_CORE_LEARN_TOPIC_HPP_INCLUDED

#include "core/topic.hpp"

#include <string>

using namespace std;

namespace scilog_cli
{
	class learn_topic : public topic
	{
		public:
			learn_topic();
			learn_topic(const string&,const string&,const string&,const string&,const string&,const string&,int);

			inline string& get_type()
			{
				return type;
			}

			inline const string& get_type() const
			{
				return type;
			}

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
			string type;
			int pages;
	};
}

#endif // SCILOG_CORE_LEARN_TOPIC_HPP_INCLUDED
