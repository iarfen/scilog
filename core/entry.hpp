#ifndef SCILOG_CORE_ENTRY_HPP_INCLUDED
#define SCILOG_CORE_ENTRY_HPP_INCLUDED

#include <string>

using namespace std;

namespace scilog_cli
{
	enum class entry_type { learn, project };
	enum class entry_learn_subtype { documentation, book };
	enum class entry_project_subtype { design, programming, planification };

	class entry_type_value
	{
		public:
		enum class union_type { enum_type, name_type };

		entry_type_value();
		entry_type_value(entry_type);
		entry_type_value(const string&);

		inline union_type& get_union_type()
		{
			return type;
		}

		inline const union_type& get_union_type() const
		{
			return type;
		}

		inline entry_type& get_enum_type()
		{
			return value.enum_type;
		}

		inline const entry_type& get_enum_type() const
		{
			return value.enum_type;
		}

		inline string& get_name_type()
		{
			return value.name_type;
		}

		inline const string& get_name_type() const
		{
			return value.name_type;
		}

		private:
		union entry_type_union
		{
			entry_type enum_type;
			string name_type;
			entry_type_union() : name_type(){};
			entry_type_union(entry_type x) : enum_type(x){};
			entry_type_union(const string& x) : name_type(x){};
			~entry_type_union(){};
		} value;
		union_type type;
	};

	class entry_learn_subtype_value
	{
		public:
		enum class union_type { enum_type, name_type };
		union entry_learn_subtype_union
		{
			entry_learn_subtype enum_subtype;
			string name_subtype;
			entry_learn_subtype_union() : name_subtype(){};
			entry_learn_subtype_union(entry_learn_subtype x) : enum_subtype(x){};
			entry_learn_subtype_union(const string& x) : name_subtype(x){};
			~entry_learn_subtype_union(){};
		};

		entry_learn_subtype_value();
		entry_learn_subtype_value(entry_learn_subtype);
		entry_learn_subtype_value(const string&);
		entry_learn_subtype_value& operator=(const entry_learn_subtype_value&);

		inline entry_learn_subtype_union& get_value()
		{
			return value;
		}

		inline const entry_learn_subtype_union& get_value() const
		{
			return value;
		}

		inline union_type& get_union_type()
		{
			return type;
		}

		inline const union_type& get_union_type() const
		{
			return type;
		}

		inline entry_learn_subtype& get_enum_type()
		{
			return value.enum_subtype;
		}

		inline const entry_learn_subtype& get_enum_type() const
		{
			return value.enum_subtype;
		}

		inline string& get_name_type()
		{
			return value.name_subtype;
		}

		inline const string& get_name_type() const
		{
			return value.name_subtype;
		}

		private:
		entry_learn_subtype_union value;
		union_type type;
	};

	class entry_project_subtype_value
	{
		public:
		enum class union_type { enum_type, name_type };
		union entry_project_subtype_union
		{
			entry_project_subtype enum_subtype;
			string name_subtype;
			entry_project_subtype_union() : name_subtype(){};
			entry_project_subtype_union(entry_project_subtype x) : enum_subtype(x){};
			entry_project_subtype_union(const string& x) : name_subtype(x){};
			~entry_project_subtype_union(){};
		};

		entry_project_subtype_value();
		entry_project_subtype_value(entry_project_subtype);
		entry_project_subtype_value(const string&);
		entry_project_subtype_value& operator=(const entry_project_subtype_value&);

		inline entry_project_subtype_union& get_value()
		{
			return value;
		}

		inline const entry_project_subtype_union& get_value() const
		{
			return value;
		}

		inline union_type& get_union_type()
		{
			return type;
		}

		inline const union_type& get_union_type() const
		{
			return type;
		}

		inline entry_project_subtype& get_enum_type()
		{
			return value.enum_subtype;
		}

		inline const entry_project_subtype& get_enum_type() const
		{
			return value.enum_subtype;
		}

		inline string& get_name_type()
		{
			return value.name_subtype;
		}

		inline const string& get_name_type() const
		{
			return value.name_subtype;
		}

		private:
		entry_project_subtype_union value;
		union_type type;
	};

	class entry_subtype_value
	{
		public:
		enum class union_type { learn, project };

		entry_subtype_value();
		entry_subtype_value(entry_learn_subtype);
		entry_subtype_value(entry_project_subtype);
		entry_subtype_value(const string&, entry_type);

		inline union_type& get_union_type()
		{
			return type;
		}

		inline const union_type& get_union_type() const
		{
			return type;
		}

		inline entry_learn_subtype& get_entry_learn_subtype()
		{
			return value.learn_subtype.get_enum_type();
		}

		inline const entry_learn_subtype& get_entry_learn_subtype() const
		{
			return value.learn_subtype.get_enum_type();
		}

		inline entry_project_subtype& get_entry_project_subtype()
		{
			return value.project_subtype.get_enum_type();
		}

		inline const entry_project_subtype& get_entry_project_subtype() const
		{
			return value.project_subtype.get_enum_type();
		}

		inline string& get_name_type()
		{
			if (type == union_type::learn)
			{
				return value.learn_subtype.get_name_type();
			}
			else
			{
				return value.project_subtype.get_name_type();
			}
		}

		inline const string& get_name_type() const
		{
			if (type == union_type::learn)
			{
				return value.learn_subtype.get_name_type();
			}
			else
			{
				return value.project_subtype.get_name_type();
			}
		}

		private:
		union entry_subtype_union
		{
			entry_learn_subtype_value learn_subtype;
			entry_project_subtype_value project_subtype;
			entry_subtype_union(){};
			entry_subtype_union(entry_learn_subtype x) : learn_subtype(x){};
			entry_subtype_union(entry_project_subtype x) : project_subtype(x){};
			entry_subtype_union(const string& x, entry_type y)
			{
				if (y == entry_type::learn)
				{
					learn_subtype = entry_learn_subtype_value(x);
				}
				else
				{
					project_subtype = entry_project_subtype_value(x);
				}
			};
			~entry_subtype_union(){};
		} value;
		union_type type;
	};

	class entry
	{
		public:
		entry();
		entry(const string&, const string&, const string&, const string&, const string&);

		inline string& get_topic()
		{
			return topic;
		}

		inline const string& get_topic() const
		{
			return topic;
		}

		inline entry_type_value& get_type()
		{
			return type;
		}

		inline const entry_type_value& get_type() const
		{
			return type;
		}

		inline entry_subtype_value& get_subtype()
		{
			return subtype;
		}

		inline const entry_subtype_value& get_subtype() const
		{
			return subtype;
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

		private:
		entry_type_value type;
		entry_subtype_value subtype;
		string topic;
		string date;
		string description;
	};

	entry_type get_entry_type(const string&);
	entry_learn_subtype get_entry_learn_subtype(const string&);
	entry_project_subtype get_entry_project_subtype(const string&);

	bool same_type(const entry&, const entry&);
	bool same_subtype(const entry&, const entry&);
}

bool operator==(const scilog_cli::entry_type_value&, const scilog_cli::entry_type_value&);
bool operator!=(const scilog_cli::entry_type_value&, const scilog_cli::entry_type_value&);
bool operator==(const scilog_cli::entry_subtype_value&, const scilog_cli::entry_subtype_value&);
bool operator!=(const scilog_cli::entry_subtype_value&, const scilog_cli::entry_subtype_value&);
bool operator==(const scilog_cli::entry_learn_subtype_value&, const scilog_cli::entry_learn_subtype_value&);
bool operator!=(const scilog_cli::entry_learn_subtype_value&, const scilog_cli::entry_learn_subtype_value&);
bool operator==(const scilog_cli::entry_project_subtype_value&, const scilog_cli::entry_project_subtype_value&);
bool operator!=(const scilog_cli::entry_project_subtype_value&, const scilog_cli::entry_project_subtype_value&);

#endif // SCILOG_CORE_ENTRY_HPP_INCLUDED
