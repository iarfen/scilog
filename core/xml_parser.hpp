#ifndef SCILOG_CORE_XML_PARSER_HPP_INCLUDED
#define SCILOG_CORE_XML_PARSER_HPP_INCLUDED

#include "entry.hpp"
#include "topic.hpp"

#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace scilog_cli
{
	vector<shared_ptr<entry>> create_entries_from_scilog_file(const string&);
	vector<shared_ptr<topic>> create_topics_from_scilog_file(const string&);

	string create_scilog_file_from_entries(const vector<shared_ptr<entry>>&);

	string validate_scilog_file(const string&);
	string validate_topics_xml_file(const string&);
}

#endif // SCILOG_CORE_XML_PARSER_HPP_INCLUDED
