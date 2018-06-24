#include "xml_parser.hpp"

#include "cli/cli.hpp"
#include "core/filesystem.hpp"

#include <sstream>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

using namespace std;

namespace scilog_cli
{
	vector<shared_ptr<entry>> create_entries_from_scilog_file(const string& filename,const string& month,const string& year)
	{
		rapidxml::file<> file(filename.c_str());
		rapidxml::xml_document<> xml_file;
		xml_file.parse<0>(file.data());
		rapidxml::xml_node<>* root_node;
		root_node = xml_file.first_node("scilog");
		vector<shared_ptr<entry>> entries = vector<shared_ptr<entry>>();
		for (rapidxml::xml_node<>* entry_node = root_node->first_node(); entry_node; entry_node = entry_node->next_sibling())
		{
			string node_name = string(entry_node->name());
			if (node_name == "project" or node_name == "learn")
			{
				string type = entry_node->first_attribute("type") ? entry_node->first_attribute("type")->value() : "";
				string topic = entry_node->first_attribute("topic") ? entry_node->first_attribute("topic")->value() : "";
				string day = entry_node->first_attribute("day") ? entry_node->first_attribute("day")->value() : "";
				string description = entry_node->value() ? entry_node->value() : "";
				shared_ptr<entry> new_entry(new entry(node_name,type,topic,day + "-" + month + "-" + year,description));
				entries.push_back(new_entry);
			}
		}
		return entries;
	}

	vector<shared_ptr<topic>> create_topics_from_scilog_file(const string& filename)
	{
		rapidxml::file<> file(filename.c_str());
		rapidxml::xml_document<> xml_file;
		xml_file.parse<0>(file.data());
		rapidxml::xml_node<>* root_node;
		root_node = xml_file.first_node("scilog");
		vector<shared_ptr<topic>> topics = vector<shared_ptr<topic>>();
		bool learn_topic;
		for (rapidxml::xml_node<>* category_node = root_node->first_node(); category_node; category_node = category_node->next_sibling())
		{
			if (string(category_node->name()) == "learn")
			{
				learn_topic = true;
			}
			else
			{
				learn_topic = false;
			}
			for (rapidxml::xml_node<>* topic_node = category_node->first_node(); topic_node; topic_node = topic_node->next_sibling())
			{
				string kind;
				if (learn_topic)
				{
					kind = "learn";
				}
				else
				{
					kind = "project";
				}
				string name = topic_node->first_attribute("name") ? topic_node->first_attribute("name")->value() : "";
				string start_date = topic_node->first_attribute("start_date") ? topic_node->first_attribute("start_date")->value() : "";
				string category = topic_node->first_attribute("category") ? topic_node->first_attribute("category")->value() : "";
				string description = topic_node->value() ? topic_node->value() : "";
				shared_ptr<topic> new_topic(new topic(kind,category,name,start_date,"",description));
				topics.push_back(new_topic);
			}
		}
		return topics;
	}

	vector<category> create_categories_from_scilog_file(const string& filename)
	{
		rapidxml::file<> file(filename.c_str());
		rapidxml::xml_document<> xml_file;
		xml_file.parse<0>(file.data());
		rapidxml::xml_node<>* root_node;
		root_node = xml_file.first_node("scilog");
		vector<category> categories = vector<category>();
		bool learn_topic;
		for (rapidxml::xml_node<>* category_node = root_node->first_node(); category_node; category_node = category_node->next_sibling())
		{
			if (string(category_node->name()) != "category")
			{
				continue;
			}
			string name = category_node->first_attribute("name") ? category_node->first_attribute("name")->value() : "";
			string parent_category = category_node->first_attribute("parent_category") ? category_node->first_attribute("parent_category")->value() : "";
			category new_category(name,parent_category);
			categories.push_back(new_category);
		}
		return categories;
	}

	string create_scilog_file_from_entries(const vector<shared_ptr<entry>>& entries)
	{
		ostringstream out;
		out << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
		out << "<scilog>" << endl;
		for (const shared_ptr<entry>& entry : entries)
		{
			out << "<" << entry->get_kind() << " type='" << entry->get_type() << "'";
			if (entry->get_topic() != "")
			{
				out << " topic='" << entry->get_topic() << "'";
			}
			string entry_date = entry->get_date();
			out << "' day='" << entry_date.substr(0,entry_date.find_first_of("-")) << "'>" << entry->get_description() << "</entry>";
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
		map<string,shared_ptr<topic>> topics = get_all_topics_map();
		vector<string> printed_topics = vector<string>();
		for (rapidxml::xml_node<>* entry_node = root_node->first_node(); entry_node; entry_node = entry_node->next_sibling())
		{
			string node_name = string(entry_node->name());
			if (node_name != "learn" and node_name != "project")
			{
				out << "Invalid tag name '" << string(entry_node->name()) << "'. Only <learn> and <project> is allowed" << endl;
				continue;
			}
			bool has_type = false;
			bool repeated_type = false;
			bool has_topic = false;
			bool repeated_topic = false;
			bool unespecific_topic = false;
			bool exists_topic = false;
			bool already_printed_topic = false;
			bool has_day = false;
			bool repeated_day = false;
			bool invalid_page_point = false;
			bool has_page_point = false;
			bool repeated_page_point = false;
			for (rapidxml::xml_attribute<>* node_attribute = entry_node->first_attribute(); node_attribute; node_attribute = node_attribute->next_attribute())
			{
				string attribute_name = string(node_attribute->name());
				if (!(attribute_name == "type" or attribute_name == "topic" or attribute_name == "day" or attribute_name == "page_point"))
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
					string attribute_value = string(node_attribute->value());
					if (topics.count(attribute_value) > 0)
					{
						exists_topic = true;
					}
				}
				else if (attribute_name == "day")
				{
					if (has_day)
					{
						repeated_day = true;
					}
					else
					{
						has_day = true;
					}
				}
				else if (attribute_name == "page_point")
				{
					if (node_name == "project")
					{
						invalid_page_point = true;
					}
					if (has_page_point)
					{
						repeated_page_point = true;
					}
					else
					{
						has_page_point = true;
					}
				}
				if (attribute_name == "type" and string(node_attribute->value()) == "planification")
				{
					has_topic = true;
					unespecific_topic = true;
				}
			}
			string error_sentence;
			if (has_topic and !unespecific_topic)
			{
				error_sentence = "The entry '" + string(entry_node->first_attribute("topic")->value()) + "'";
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
				out << error_sentence << " has a type repeated" << endl;
			}
			if (!has_topic)
			{
				out << error_sentence << " doesn't has topic" << endl;
			}
			if (repeated_topic)
			{
				out << error_sentence << " has a topic repeated" << endl;
			}
			if (!exists_topic and !unespecific_topic)
			{
				if (printed_topics.size() > 0)
				{
					for (const string& printed_topic : printed_topics)
					{
						if (printed_topic == string(entry_node->first_attribute("topic")->value()))
						{
							already_printed_topic = true;
						}
					}
				}
				if (!already_printed_topic)
				{
					out << "The topic " << scilog_cli::green_text << string(entry_node->first_attribute("topic")->value()) << scilog_cli::normal_text << " doesn't exists" << endl;
					printed_topics.push_back(string(entry_node->first_attribute("topic")->value()));
				}
			}
			if (!has_day)
			{
				out << error_sentence << " doesn't has day" << endl;
			}
			if (repeated_day)
			{
				out << error_sentence << " has a day repeated" << endl;
			}
			if (invalid_page_point)
			{
				out << error_sentence << " has a <project> entry with a page_point attribute" << endl;
			}
			if (repeated_page_point)
			{
				out << error_sentence << " has a page_point repeated" << endl;
			}
			string description = entry_node->value();
			if (description == "")
			{
				out << error_sentence << " has an empty description" << endl;
			}
			bool entry_has_child_nodes = false;
			for (rapidxml::xml_node<>* child_node = entry_node->first_node(); child_node; child_node = child_node->next_sibling())
			{
				string node_name = string(child_node->name());
				if (node_name != "")
				{
					entry_has_child_nodes = true;
				}
			}
			if (entry_has_child_nodes)
			{
				out << string(entry_node->name()) << " cannot have child nodes" << endl;
			}
		}
		return out.str();
	}

	string validate_topics_xml_file(const string& filename)
	{
		rapidxml::file<> file(filename.c_str());
		rapidxml::xml_document<> xml_file;
		xml_file.parse<0>(file.data());
		rapidxml::xml_node<> * root_node;
		root_node = xml_file.first_node("scilog");
		ostringstream out;
		for (rapidxml::xml_node<>* category_node = root_node->first_node(); category_node; category_node = category_node->next_sibling())
		{
			string node_name = string(category_node->name());
			if (!(node_name == "learn" or node_name == "project" or node_name == "category"))
			{
				out << "Invalid tag name '" << node_name << "'. Only <learn> and <project> is allowed" << endl;
				continue;
			}
			if (node_name == "category")
			{
				bool has_name = false;
				bool repeated_name = false;
				bool has_parent_category = false;
				bool repeated_parent_category = false;
				for (rapidxml::xml_attribute<>* node_attribute = category_node->first_attribute(); node_attribute; node_attribute = node_attribute->next_attribute())
				{
					string attribute_name = string(node_attribute->name());
					if (!(attribute_name == "name" or attribute_name == "parent_category"))
					{
						out << "Invalid attribute name '" << attribute_name << "'" << endl;
					}
					else if (attribute_name == "name")
					{
						if (has_name)
						{
							repeated_name = true;
						}
						else
						{
							has_name = true;
						}
					}
					else if (attribute_name == "parent_category")
					{
						if (has_parent_category)
						{
							repeated_parent_category = true;
						}
						else
						{
							has_parent_category = true;
						}
					}
				}
				string error_sentence;
				if (has_name)
				{
					error_sentence = "The category '" + string(category_node->first_attribute("name")->value()) + "'";
				}
				else
				{
					error_sentence = "An anonymous category";
				}
				if (!has_name)
				{
					out << error_sentence << " doesn't has name" << endl;
				}
				if (repeated_name)
				{
					out << error_sentence << "' has a name repeated" << endl;
				}
				if (!has_parent_category)
				{
					out << error_sentence << " doesn't has parent category" << endl;
				}
				if (repeated_parent_category)
				{
					out << error_sentence << "' has a parent category repeated" << endl;
				}
				bool entry_has_child_nodes = false;
				for (rapidxml::xml_node<>* child_node = category_node->first_node(); child_node; child_node = child_node->next_sibling())
				{
					string node_name = string(child_node->name());
					if (node_name != "")
					{
						entry_has_child_nodes = true;
					}
				}
				if (entry_has_child_nodes)
				{
					out << node_name << " cannot have child nodes" << endl;
				}
				continue;
			}
			if (node_name == "learn" or node_name == "project")
			{
				for (rapidxml::xml_attribute<>* node_attribute = category_node->first_attribute(); node_attribute; node_attribute = node_attribute->next_attribute())
				{
					string attribute_name = string(node_attribute->name());
					out << "Invalid attribute name '" << attribute_name << "'" << endl;
				}
			}
			for (rapidxml::xml_node<>* entry_node = category_node->first_node(); entry_node; entry_node = entry_node->next_sibling())
			{
				if (string(entry_node->name()) != "topic")
				{
					out << "Invalid tag name '" << string(category_node->name()) << "'. Only <topic> is allowed" << endl;
					continue;
				}
				bool has_type = false;
				bool repeated_type = false;
				bool has_category = false;
				bool repeated_category = false;
				bool has_parent_category = false;
				bool repeated_parent_category = false;
				bool has_name = false;
				bool repeated_name = false;
				bool has_start_date = false;
				bool repeated_start_date = false;
				for (rapidxml::xml_attribute<>* node_attribute = entry_node->first_attribute(); node_attribute; node_attribute = node_attribute->next_attribute())
				{
					string attribute_name = string(node_attribute->name());
					if (!(attribute_name == "type" or attribute_name == "category" or attribute_name == "parent_category" or attribute_name == "name" or attribute_name == "start_date"))
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
					else if (attribute_name == "category")
					{
						if (has_category)
						{
							repeated_category = true;
						}
						else
						{
							has_category = true;
						}
					}
					else if (attribute_name == "parent_category")
					{
						if (has_parent_category)
						{
							repeated_parent_category = true;
						}
						else
						{
							has_parent_category = true;
						}
					}
					else if (attribute_name == "name")
					{
						if (has_name)
						{
							repeated_name = true;
						}
						else
						{
							has_name = true;
						}
					}
					else if (attribute_name == "start_date")
					{
						if (has_start_date)
						{
							repeated_start_date = true;
						}
						else
						{
							has_start_date = true;
						}
					}
				}
				string error_sentence;
				if (has_name)
				{
					error_sentence = "The entry '" + string(entry_node->first_attribute("name")->value()) + "'";
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
				if (!has_category)
				{
					out << error_sentence << " doesn't has category" << endl;
				}
				if (repeated_category)
				{
					out << error_sentence << "' has a category repeated" << endl;
				}
				if (!has_parent_category)
				{
					out << error_sentence << " doesn't has parent category" << endl;
				}
				if (repeated_parent_category)
				{
					out << error_sentence << "' has a parent category repeated" << endl;
				}
				if (!has_name)
				{
					out << error_sentence << " doesn't has name" << endl;
				}
				if (repeated_name)
				{
					out << error_sentence << "' has a name repeated" << endl;
				}
				if (!has_start_date)
				{
					out << error_sentence << " doesn't has start date" << endl;
				}
				if (repeated_start_date)
				{
					out << error_sentence << "' has a start date repeated" << endl;
				}
			}
		}
		return out.str();
	}
}
