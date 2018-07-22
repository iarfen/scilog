#ifndef SCILOG_CORE_CATEGORY_HPP_INCLUDED
#define SCILOG_CORE_CATEGORY_HPP_INCLUDED

#include <map>
#include <string>

using namespace std;

namespace scilog_cli
{
	class category
	{
		public:
			category();
			category(const string&,const string&);

			inline string& get_name()
			{
				return name;
			}

			inline const string& get_name() const
			{
				return name;
			}

			inline string& get_parent_category()
			{
				return parent_category;
			}

			inline const string& get_parent_category() const
			{
				return parent_category;
			}

		private:
			string name;
			string parent_category;
	};

	extern map<string,category> default_categories;
	extern map<string,category> all_categories;

	bool is_parent_category(const string&,const string&);

	void initialize_all_categories();
}

bool operator ==(const scilog_cli::category&,const scilog_cli::category&);
bool operator !=(const scilog_cli::category&,const scilog_cli::category&);

#endif // SCILOG_CORE_CATEGORY_HPP_INCLUDED
