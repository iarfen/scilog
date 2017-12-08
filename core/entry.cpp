#include "entry.hpp"

using namespace std;

namespace scilog_cli
{
	entry::entry() : type(), subtype(), topic(), date(), description()
	{
	}

	entry::entry(const string& new_type, const string& new_subtype, const string& new_topic, const string& new_date, const string& new_description) : type(new_type), subtype(new_subtype), topic(new_topic), date(new_date), description(new_description)
	{
	}
}

bool operator ==(const scilog_cli::entry& x,const scilog_cli::entry& y)
{
	return (x.get_type() == y.get_type() and x.get_subtype() == y.get_subtype() and x.get_topic() == y.get_topic() and x.get_date() == y.get_date() and x.get_description() == y.get_description());
}

bool operator !=(const scilog_cli::entry& x,const scilog_cli::entry& y)
{
	return !(x == y);
}
