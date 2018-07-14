#ifndef SCILOG_MAIN_HPP_INCLUDED
#define SCILOG_MAIN_HPP_INCLUDED

#include <string>

using namespace std;

namespace scilog_cli
{
	enum class entry_kind {all,learn,project};

	enum class fs_mode {all,year,month};

	struct fs_args
	{
		bool is_year_dir;
		string year_selection;
		string month_selection;
		fs_mode mode;
	};

	fs_args fs_selection(int, char*[]);
}

#endif // SCILOG_MAIN_HPP_INCLUDED
