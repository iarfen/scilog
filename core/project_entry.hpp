#ifndef SCILOG_CORE_PROJECT_ENTRY_HPP_INCLUDED
#define SCILOG_CORE_PROJECT_ENTRY_HPP_INCLUDED

#include "core/entry.hpp"

using namespace std;

namespace scilog_cli
{
	class project_entry : public entry
	{
		public:
			project_entry();
			project_entry(const string&,const string&,const string&,const string&,bool);
	};
}

#endif // SCILOG_CORE_PROJECT_ENTRY_HPP_INCLUDED
