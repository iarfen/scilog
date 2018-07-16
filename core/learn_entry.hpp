#ifndef SCILOG_CORE_LEARN_ENTRY_HPP_INCLUDED
#define SCILOG_CORE_LEARN_ENTRY_HPP_INCLUDED

#include "core/entry.hpp"

using namespace std;

namespace scilog_cli
{
	class learn_entry : public entry
	{
		public:
			learn_entry();
			learn_entry(const string&,const string&,const string&,const string&,bool,int);

			inline int& get_page_point()
			{
				return page_point;
			}

			inline const int& get_page_point() const
			{
				return page_point;
			}

		private:
			int page_point;
	};

	int previous_pages(const string&,const string&);
}

#endif // SCILOG_CORE_LEARN_ENTRY_HPP_INCLUDED
