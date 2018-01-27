#ifndef SCILOG_SQL_PARSER_HPP_INCLUDED
#define SCILOG_SQL_PARSER_HPP_INCLUDED

#include "core/entry.hpp"
#include "core/topic.hpp"

#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace scilog_cli
{
	void print_sql_dump(const vector<shared_ptr<entry>>&,const vector<shared_ptr<topic>>&,string);
}

#endif // SCILOG_SQL_PARSER_HPP_INCLUDED
