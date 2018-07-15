#include "entry.hpp"

using namespace std;

namespace scilog_cli
{
	entry::entry() : kind(), type(), topic(), date(), description(), finished()
	{
	}

	entry::entry(const string& new_kind, const string& new_type, const string& new_topic, const string& new_date, const string& new_description, bool new_finished) : kind(new_kind), type(new_type), topic(new_topic), date(new_date), description(new_description),finished(new_finished)
	{
	}
}

bool operator ==(const scilog_cli::entry& x,const scilog_cli::entry& y)
{
	return (x.get_type() == y.get_type() and x.get_kind() == y.get_kind() and x.get_topic() == y.get_topic() and x.get_date() == y.get_date() and x.get_description() == y.get_description());
}

bool operator !=(const scilog_cli::entry& x,const scilog_cli::entry& y)
{
	return !(x == y);
}
