#ifndef SCILOG_CORE_ENTRIES_HPP_INCLUDED
#define SCILOG_CORE_ENTRIES_HPP_INCLUDED

#include "entry.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace scilog_cli
{
	extern map<string,map<string,vector<shared_ptr<entry>>>> all_entries;

	void load_entries(const string&,const string&);

	vector<shared_ptr<entry>>& get_entries(const string&,const string&);
}

#endif // SCILOG_CORE_ENTRIES_HPP_INCLUDED
