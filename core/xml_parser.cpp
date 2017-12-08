#include "xml_parser.hpp"

#include <sstream>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

using namespace std;

namespace scilog_cli
{
	vector<shared_ptr<entry>> create_entries_from_scilog_file(const string& filename)
	{
		rapidxml::file<> file(filename.c_str());
		rapidxml::xml_document<> xml_file;
		xml_file.parse<0>(file.data());
		rapidxml::xml_node<> * root_node;
		root_node = xml_file.first_node("scilog");
		vector<shared_ptr<entry>> entries = vector<shared_ptr<entry>>();
		for (rapidxml::xml_node<>* entry_node = root_node->first_node(); entry_node; entry_node = entry_node->next_sibling())
		{
			if (string(entry_node->name()) == "entry")
			{
				string type = entry_node->first_attribute("type") ? entry_node->first_attribute("type")->value() : "";
				string subtype = entry_node->first_attribute("subtype") ? entry_node->first_attribute("subtype")->value() : "";
				string topic = entry_node->first_attribute("topic") ? entry_node->first_attribute("topic")->value() : "";
				string date = entry_node->first_attribute("date") ? entry_node->first_attribute("date")->value() : "";
				string description = entry_node->value() ? entry_node->value() : "";
				shared_ptr<entry> new_entry(new entry(type,subtype,topic,date,description));
				entries.push_back(new_entry);
			}
		}
		return entries;
	}

	string create_scilog_file_from_entries(const vector<shared_ptr<entry>>& entries)
	{
		ostringstream out;
		out << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
		out << "<scilog>" << endl;
		for (const shared_ptr<entry>& entry : entries)
		{
			out << "<entry type='" << entry->get_type() << "' subtype='" << entry->get_subtype() << "'";
			if (entry->get_topic() != "")
			{
				out << " topic='" << entry->get_topic() << "'";
			}
			out << "' date='" << entry->get_date() << "'>" << entry->get_description() << "</entry>";
		}
		out << "</scilog>" << endl;
		return out.str();
	}

	string validate_scilog_file(const string& filename)
	{
		rapidxml::file<> file(filename.c_str());
		rapidxml::xml_document<> xml_file;
		xml_file.parse<0>(file.data());
		rapidxml::xml_node<> * root_node;
		root_node = xml_file.first_node("scilog");
		ostringstream out;
		for (rapidxml::xml_node<>* entry_node = root_node->first_node(); entry_node; entry_node = entry_node->next_sibling())
		{
			if (string(entry_node->name()) != "entry")
			{
				out << "Invalid tag name '" << string(entry_node->name()) << "'. Only <entry> is allowed" << endl;
			}
			else
			{
				bool has_type = false;
				bool repeated_type = false;
				bool has_subtype = false;
				bool repeated_subtype = false;
				bool has_topic = false;
				bool repeated_topic = false;
				bool has_date = false;
				bool repeated_date = false;
				for (rapidxml::xml_attribute<>* node_attribute = entry_node->first_attribute(); node_attribute; node_attribute = node_attribute->next_attribute())
				{
					string attribute_name = string(node_attribute->name());
					if (!(attribute_name == "type" and attribute_name == "subtype" and attribute_name == "topic" and attribute_name == "date"))
					{
						out << "Invalid attribute name '" << attribute_name << "'" << endl;
					}
					else if (attribute_name == "type")
					{
						if (has_type)
						{
							repeated_type = true;
						}
						else
						{
							has_type = true;
						}
					}
					else if (attribute_name == "subtype")
					{
						if (has_subtype)
						{
							repeated_subtype = true;
						}
						else
						{
							has_subtype = true;
						}
					}
					else if (attribute_name == "topic")
					{
						if (has_topic)
						{
							repeated_topic = true;
						}
						else
						{
							has_topic = true;
						}
					}
					else if (attribute_name == "date")
					{
						if (has_date)
						{
							repeated_date = true;
						}
						else
						{
							has_date = true;
						}
					}
				}
				string error_sentence;
				if (has_topic)
				{
					error_sentence = "The entry '" + string(entry_node->first_attribute("type")->value()) + "'";
				}
				else
				{
					error_sentence = "An anonymous entry";
				}
				if (!has_type)
				{
					out << error_sentence << " doesn't has type" << endl;
				}
				if (repeated_type)
				{
					out << error_sentence << "' has a type repeated" << endl;
				}
				if (!has_subtype)
				{
					out << error_sentence << " doesn't has subtype" << endl;
				}
				if (repeated_subtype)
				{
					out << error_sentence << "' has a subtype repeated" << endl;
				}
				if (!has_topic)
				{
					out << error_sentence << " doesn't has topic" << endl;
				}
				if (repeated_topic)
				{
					out << error_sentence << "' has a topic repeated" << endl;
				}
				if (!has_date)
				{
					out << error_sentence << " doesn't has date" << endl;
				}
				if (repeated_date)
				{
					out << error_sentence << "' has a date repeated" << endl;
				}
				string description = entry_node->value();
				if (description == "")
				{
					out << error_sentence << " has an empty description" << endl;
				}
			}
		}
		return out.str();
	}
}
