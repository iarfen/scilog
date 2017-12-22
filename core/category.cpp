#include "category.hpp"

using namespace std;

namespace scilog_cli
{
	category::category() : name(),parent_category()
	{
	}

	category::category(const string& new_name,const string& new_parent_category) : name(new_name),parent_category(new_parent_category)
	{
	}
}

bool operator ==(const scilog_cli::category& x,const scilog_cli::category& y)
{
	return (x.get_name() == y.get_name());
}

bool operator !=(const scilog_cli::category& x,const scilog_cli::category& y)
{
	return !(x == y);
}
