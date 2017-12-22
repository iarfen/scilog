#include "topic.hpp"

using namespace std;

namespace scilog_cli
{
	topic::topic() : type(),category(),parent_category(),name(),start_date(),description()
	{
	}

	topic::topic(const string& new_type,const string& new_category,const string& new_parent_category,const string& new_name,const string& new_start_date,const string& new_description) : type(new_type),category(new_category),parent_category(new_parent_category),name(new_name),start_date(new_start_date),description(new_description)
	{
	}
}

bool operator ==(const scilog_cli::topic& x,const scilog_cli::topic& y)
{
	return (x.get_name() == y.get_name());
}

bool operator !=(const scilog_cli::topic& x,const scilog_cli::topic& y)
{
	return !(x == y);
}
