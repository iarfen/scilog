#ifndef SCILOG_CORE_CATEGORIES_HPP_INCLUDED
#define SCILOG_CORE_CATEGORIES_HPP_INCLUDED

#include "category.hpp"

#include <map>
#include <string>

using namespace std;

namespace scilog_cli
{
	extern map<string,category> default_categories;
	extern map<string,category> all_categories;

	bool is_parent_category(const string&,const string&);

	void initialize_all_categories();
}

#endif // SCILOG_CORE_CATEGORIES_HPP_INCLUDED
