#ifndef SCILOG_CORE_TOPIC_HPP_INCLUDED
#define SCILOG_CORE_TOPIC_HPP_INCLUDED

#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace scilog_cli
{
	enum class topic_kind {learn,project};

	class topic
	{
		public:
			topic();
			topic(const string&,const string&,const string&,const string&,const string&,const string&);

			inline string& get_category()
			{
				return category;
			}

			inline const string& get_category() const
			{
				return category;
			}

			inline string& get_name()
			{
				return name;
			}

			inline const string& get_name() const
			{
				return name;
			}

			inline string& get_start_date()
			{
				return start_date;
			}

			inline const string& get_start_date() const
			{
				return start_date;
			}

			inline string& get_end_date()
			{
				return end_date;
			}

			inline const string& get_end_date() const
			{
				return end_date;
			}

			inline string& get_description()
			{
				return description;
			}

			inline const string& get_description() const
			{
				return description;
			}

			inline string& get_parent_topic()
			{
				return parent_topic;
			}

			inline const string& get_parent_topic() const
			{
				return parent_topic;
			}

			virtual topic_kind get_kind() const;

		private:
			string category;
			string name;
			string start_date;
			string end_date;
			string description;
			string parent_topic;
	};

	map<string,shared_ptr<topic>> create_topics_map(vector<shared_ptr<topic>>);
}

bool operator ==(const scilog_cli::topic&,const scilog_cli::topic&);
bool operator !=(const scilog_cli::topic&,const scilog_cli::topic&);

#endif // SCILOG_CORE_TOPIC_HPP_INCLUDED
