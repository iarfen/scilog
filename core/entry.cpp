#include "entry.hpp"

using namespace std;

namespace scilog_cli
{
	entry_type_value::entry_type_value() : value(), type(union_type::name_type)
	{
	}

	entry_type_value::entry_type_value(entry_type new_enum_type) : value(new_enum_type), type(union_type::enum_type)
	{
	}

	entry_type_value::entry_type_value(const string& new_name_type) : value(new_name_type), type(union_type::name_type)
	{
	}

	entry_learn_subtype_value::entry_learn_subtype_value() : value(), type(union_type::name_type)
	{
	}

	entry_learn_subtype_value::entry_learn_subtype_value(entry_learn_subtype new_enum_type) : value(new_enum_type), type(union_type::enum_type)
	{
	}

	entry_learn_subtype_value::entry_learn_subtype_value(const string& new_name_type) : value(new_name_type), type(union_type::name_type)
	{
	}

	entry_learn_subtype_value& entry_learn_subtype_value::operator=(const entry_learn_subtype_value& x)
	{
		value = x.get_value();
		type = x.get_union_type();
	}

	entry_project_subtype_value::entry_project_subtype_value() : value(), type(union_type::name_type)
	{
	}

	entry_project_subtype_value::entry_project_subtype_value(entry_project_subtype new_enum_type) : value(new_enum_type), type(union_type::enum_type)
	{
	}

	entry_project_subtype_value::entry_project_subtype_value(const string& new_name_type) : value(new_name_type), type(union_type::name_type)
	{
	}

	entry_project_subtype_value& entry_project_subtype_value::operator=(const entry_project_subtype_value& x)
	{
		value = x.get_value();
		type = x.get_union_type();
	}

	entry_subtype_value::entry_subtype_value() : value(), type()
	{
	}

	entry_subtype_value::entry_subtype_value(entry_learn_subtype x) : value(x), type(union_type::learn)
	{
	}

	entry_subtype_value::entry_subtype_value(entry_project_subtype x) : value(x), type(union_type::project)
	{
	}

	entry_subtype_value::entry_subtype_value(const string& x, entry_type new_type) : value(x, new_type), type()
	{
		if (new_type == entry_type::learn)
		{
			type = union_type::learn;
		}
		else if (new_type == entry_type::project)
		{
			type = union_type::project;
		}
	}

	entry::entry() : type(), subtype(), topic(), date(), description()
	{
	}

	entry::entry(const string& new_type, const string& new_subtype, const string& new_topic, const string& new_date, const string& new_description) : type(get_entry_type(new_type)), subtype(new_subtype,type), topic(new_topic), date(new_date), description(new_description)
	{
	}

	entry_type get_entry_type(const string& x)
	{
		if (x == "learn")
		{
			return entry_type::learn;
		}
		else if (x == "project")
		{
			return entry_type::project;
		}
	}

	entry_learn_subtype get_entry_learn_subtype(const string& x)
	{
		if (x == "documentation")
		{
			return entry_learn_subtype::documentation;
		}
		else if (x == "book")
		{
			return entry_learn_subtype::book;
		}
	}

	entry_project_subtype get_entry_project_subtype(const string& x)
	{
		if (x == "design")
		{
			return entry_project_subtype::design;
		}
		else if (x == "programming")
		{
			return entry_project_subtype::programming;
		}
		else if (x == "planification")
		{
			return entry_project_subtype::planification;
		}
	}

	bool same_type(const entry& x, const entry& y)
	{
		return (x.get_type() == y.get_type());
	}

	bool same_subtype(const entry& x, const entry& y)
	{
		return (x.get_subtype() == y.get_subtype());
	}
}

bool operator==(const scilog_cli::entry_type_value& x, const scilog_cli::entry_type_value& y)
{
	if (x.get_union_type() == y.get_union_type())
	{
		if (x.get_union_type() == scilog_cli::entry_type_value::union_type::enum_type)
		{
			return (x.get_enum_type() == y.get_enum_type());
		}
		else
		{
			return (x.get_name_type() == y.get_name_type());
		}
	}
	else
	{
		return false;
	}
}

bool operator!=(const scilog_cli::entry_type_value& x, const scilog_cli::entry_type_value& y)
{
	return !(x == y);
}

bool operator==(const scilog_cli::entry_subtype_value& x, const scilog_cli::entry_subtype_value& y)
{
	if (x.get_union_type() == y.get_union_type())
	{
		if (x.get_union_type() == entry_subtype_value::union_type::learn)
		{
			return (x.get_entry_learn_subtype() == y.get_entry_learn_subtype());
		}
		else
		{
			return (x.get_entry_project_subtype() == y.get_entry_project_subtype());
		}
	}
	else
	{
		return false;
	}
}

bool operator!=(const scilog_cli::entry_subtype_value& x, const scilog_cli::entry_subtype_value& y)
{
	return !(x == y);
}

bool operator==(const scilog_cli::entry_learn_subtype_value& x, const scilog_cli::entry_learn_subtype_value& y)
{
	if (x.get_union_type() == y.get_union_type())
	{
		if (x.get_union_type() == scilog_cli::entry_learn_subtype_value::union_type::enum_type)
		{
			return (x.get_enum_type() == y.get_enum_type());
		}
		else
		{
			return (x.get_name_type() == y.get_name_type());
		}
	}
	else
	{
		return false;
	}
}

bool operator!=(const scilog_cli::entry_learn_subtype_value& x, const scilog_cli::entry_learn_subtype_value& y)
{
	return !(x == y);
}

bool operator==(const scilog_cli::entry_project_subtype_value& x, const scilog_cli::entry_project_subtype_value& y)
{
	if (x.get_union_type() == y.get_union_type())
	{
		if (x.get_union_type() == scilog_cli::entry_project_subtype_value::union_type::enum_type)
		{
			return (x.get_enum_type() == y.get_enum_type());
		}
		else
		{
			return (x.get_name_type() == y.get_name_type());
		}
	}
	else
	{
		return false;
	}
}

bool operator!=(const scilog_cli::entry_project_subtype_value& x, const scilog_cli::entry_project_subtype_value& y)
{
	return !(x == y);
}
