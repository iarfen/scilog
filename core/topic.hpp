#ifndef SCILOG_CORE_TOPIC_HPP_INCLUDED
#define SCILOG_CORE_TOPIC_HPP_INCLUDED

#include <string>

using namespace std;

namespace scilog_cli
{
	class topic
	{
		public:
			topic();
			topic(const string&,const string&,const string&,const string&,const string&);

			inline string& get_type()
			{
				return type;
			}

			inline const string& get_type() const
			{
				return type;
			}

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

			inline string& get_description()
			{
				return description;
			}

			inline const string& get_description() const
			{
				return description;
			}

		private:
			string type;
			string category;
			string name;
			string start_date;
			string description;
	};
}

bool operator ==(const scilog_cli::topic&,const scilog_cli::topic&);
bool operator !=(const scilog_cli::topic&,const scilog_cli::topic&);

#endif // SCILOG_CORE_TOPIC_HPP_INCLUDED
