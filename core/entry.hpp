#ifndef SCILOG_CORE_ENTRY_HPP_INCLUDED
#define SCILOG_CORE_ENTRY_HPP_INCLUDED

#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace scilog_cli
{
	class entry
	{
		public:
		entry();
		entry(const string&, const string&, const string&, const string&, const string&, bool);
		virtual ~entry() {};

		inline string& get_kind()
		{
			return kind;
		}

		inline const string& get_kind() const
		{
			return kind;
		}

		inline string& get_topic()
		{
			return topic;
		}

		inline const string& get_topic() const
		{
			return topic;
		}

		inline string& get_type()
		{
			return type;
		}

		inline const string& get_type() const
		{
			return type;
		}

		inline string& get_date()
		{
			return date;
		}

		inline const string& get_date() const
		{
			return date;
		}

		inline string& get_description()
		{
			return description;
		}

		inline const string& get_description() const
		{
			return description;
		}

		inline bool& get_finished()
		{
			return finished;
		}

		inline const bool& get_finished() const
		{
			return finished;
		}

		private:
			string kind;
			string type;
			string topic;
			string date;
			string description;
			bool finished;
	};

	extern map<string,map<string,vector<shared_ptr<entry>>>> all_entries;

	void load_entries(const string&,const string&);

	const vector<shared_ptr<entry>>& get_entries(const string&,const string&);
}

bool operator ==(const scilog_cli::entry&,const scilog_cli::entry&);
bool operator !=(const scilog_cli::entry&,const scilog_cli::entry&);

#endif // SCILOG_CORE_ENTRY_HPP_INCLUDED
