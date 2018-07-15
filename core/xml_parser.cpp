#include "xml_parser.hpp"

#include "cli/cli.hpp"
#include "core/filesystem.hpp"

#include "core/learn_topic.hpp"
#include "core/project_topic.hpp"

#include "core/learn_entry.hpp"
#include "core/project_entry.hpp"

#include "core/categories.hpp"

#include <iostream>
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

		const map<string,shared_ptr<topic>>& topics = get_all_topics_map();

		vector<shared_ptr<entry>> entries = vector<shared_ptr<entry>>();
		for (rapidxml::xml_node<>* entry_node = root_node->first_node(); entry_node; entry_node = entry_node->next_sibling())
		{
			string node_name = string(entry_node->name());
			if (node_name == "project" or node_name == "learn")
			{
				string type = entry_node->first_attribute("type") ? entry_node->first_attribute("type")->value() : "";
				string data_topic = entry_node->first_attribute("topic") ? entry_node->first_attribute("topic")->value() : "";
				string day = entry_node->first_attribute("day") ? entry_node->first_attribute("day")->value() : "";
				string description = entry_node->value() ? entry_node->value() : "";

				if (type == "")
				{
					type = default_topic_type(topics,data_topic,node_name);
				}

				if (type == "" or data_topic == "" or day == "")
				{
					continue;
				}

				if (type.find_first_of(",") != string::npos)
				{
					type = type.substr(0,type.find_first_of(","));
				}

				if (stoi(day) < 10)
				{
					day = "0" + day;
				}
				string entry_month;
				if (stoi(month) < 10)
				{
					entry_month = "0" + month;
				}
				else
				{
					entry_month = month;
				}
				string date = year + "-" + entry_month + "-" + day;

				shared_ptr<entry> new_entry;
				if (node_name == "learn")
				{
					string string_page_point = entry_node->first_attribute("page_point") ? entry_node->first_attribute("page_point")->value() : "";
					if (string_page_point == "")
					{
						continue;
					}

					int page_point;
					if (string_page_point != "")
					{
						page_point = stoi(string_page_point);
					}
					else
					{
						page_point = 0;
					}
					new_entry = make_shared<learn_entry>(type,data_topic,date,description,page_point);
				}
				else if (node_name == "project")
				{
					new_entry = make_shared<project_entry>(type,data_topic,date,description);
				}
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
		bool is_learn_topic;
		for (rapidxml::xml_node<>* category_node = root_node->first_node(); category_node; category_node = category_node->next_sibling())
		{
			string node_name = string(category_node->name());
			if (node_name == "category")
			{
				continue;
			}
			if (node_name == "learn")
			{
				is_learn_topic = true;
			}
			else if (node_name == "project")
			{
				is_learn_topic = false;
			}
			for (rapidxml::xml_node<>* topic_node = category_node->first_node(); topic_node; topic_node = topic_node->next_sibling())
			{
				string name = topic_node->first_attribute("name") ? topic_node->first_attribute("name")->value() : "";
				string start_date = topic_node->first_attribute("start_date") ? topic_node->first_attribute("start_date")->value() : "";
				string end_date = topic_node->first_attribute("end_date") ? topic_node->first_attribute("end_date")->value() : "";
				string category = topic_node->first_attribute("category") ? topic_node->first_attribute("category")->value() : "";
				string description = topic_node->value() ? topic_node->value() : "";
				string parent_topic = topic_node->first_attribute("parent") ? topic_node->first_attribute("parent")->value() : "";
				shared_ptr<topic> new_topic;
				if (is_learn_topic)
				{
					string type = topic_node->first_attribute("type") ? topic_node->first_attribute("type")->value() : "";
					string pages = topic_node->first_attribute("pages") ? topic_node->first_attribute("pages")->value() : "";
					int number_of_pages;
					if (pages != "")
					{
						number_of_pages = stoi(pages);
					}
					else
					{
						number_of_pages = 0;
					}
					new_topic = make_shared<learn_topic>(type,category,name,start_date,end_date,description,parent_topic,number_of_pages);
				}
				else
				{
					new_topic = make_shared<project_topic>(category,name,start_date,end_date,description,parent_topic);
				}
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
		const map<string,shared_ptr<topic>>& topics = get_all_topics_map();
		vector<string> printed_topics = vector<string>();
		for (rapidxml::xml_node<>* entry_node = root_node->first_node(); entry_node; entry_node = entry_node->next_sibling())
		{
			string node_name = string(entry_node->name());
			if (node_name != "learn" and node_name != "project")
			{
				out << "Invalid tag name '" << string(entry_node->name()) << "'. Only <learn> and <project> are allowed" << endl;
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
			if (has_type == false and default_topic_type(topics,entry_node->first_attribute("topic")->value(),node_name) != "")
			{
				has_type = true;
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
					out << "The topic " << scilog_cli::cyan_text << string(entry_node->first_attribute("topic")->value()) << scilog_cli::normal_text << " doesn't exists" << endl;
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
		map<string,category> categories = get_all_categories_map();
		vector<string> printed_categories = vector<string>();
		for (rapidxml::xml_node<>* category_node = root_node->first_node(); category_node; category_node = category_node->next_sibling())
		{
			string node_name = string(category_node->name());
			if (!(node_name == "learn" or node_name == "project" or node_name == "category"))
			{
				out << "Invalid tag name '" << node_name << "'. Only <learn>, <project> and <category> are allowed" << endl;
				continue;
			}
			if (node_name == "category")
			{
				bool has_name = false;
				bool repeated_name = false;
				bool has_parent_category = false;
				bool repeated_parent_category = false;
				bool exists_parent_category = false;
				bool already_printed_parent_category = false;
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
						string attribute_value = string(node_attribute->value());
						if (categories.count(attribute_value) > 0)
						{
							exists_parent_category = true;
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
				if (!exists_parent_category)
				{
					if (printed_categories.size() > 0)
					{
						for (const string& printed_category : printed_categories)
						{
							if (printed_category == string(category_node->first_attribute("parent_category")->value()))
							{
								already_printed_parent_category = true;
							}
						}
					}
					if (!already_printed_parent_category and string(category_node->first_attribute("parent_category")->value()) != "")
					{
						out << error_sentence << " has the parent category " << scilog_cli::cyan_text << string(category_node->first_attribute("parent_category")->value()) << scilog_cli::normal_text << " that doesn't exists" << endl;
						printed_categories.push_back(string(category_node->first_attribute("parent_category")->value()));
					}
				}
				bool entry_has_child_nodes = false;
				for (rapidxml::xml_node<>* child_node = category_node->first_node(); child_node; child_node = child_node->next_sibling())
				{
					string node_child_name = string(child_node->name());
					if (node_child_name != "")
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
				string topic_tag_name = string(entry_node->name());
				if (topic_tag_name != "topic")
				{
					out << "Invalid tag name '" << topic_tag_name << "'. Only <topic> is allowed" << endl;
					continue;
				}
				bool has_type = false;
				bool repeated_type = false;
				bool has_category = false;
				bool repeated_category = false;
				bool exists_category = false;
				bool already_printed_category = false;
				bool has_name = false;
				bool repeated_name = false;
				bool has_start_date = false;
				bool repeated_start_date = false;
				bool has_end_date = false;
				bool repeated_end_date = false;
				bool has_pages = false;
				bool repeated_pages = false;
				bool has_parent = false;
				bool repeated_parent = false;
				for (rapidxml::xml_attribute<>* node_attribute = entry_node->first_attribute(); node_attribute; node_attribute = node_attribute->next_attribute())
				{
					string attribute_name = string(node_attribute->name());
					if (!(attribute_name == "type" or attribute_name == "category" or attribute_name == "name" or attribute_name == "start_date" or attribute_name == "end_date" or attribute_name == "pages" or attribute_name == "parent"))
					{
						out << "Invalid attribute name '" << attribute_name << "'" << endl;
					}
					else if (attribute_name == "type" and node_name == "learn")
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
						string attribute_value = string(node_attribute->value());
						if (categories.count(attribute_value) > 0)
						{
							exists_category = true;
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
					else if (attribute_name == "end_date")
					{
						if (has_end_date)
						{
							repeated_end_date = true;
						}
						else
						{
							has_end_date = true;
						}
					}
					else if (attribute_name == "pages")
					{
						if (has_pages)
						{
							repeated_pages = true;
						}
						else
						{
							has_pages = true;
						}
					}
					else if (attribute_name == "parent")
					{
						if (has_parent)
						{
							repeated_parent = true;
						}
						else
						{
							has_parent = true;
						}
					}
				}
				string error_sentence;
				if (has_name)
				{
					error_sentence = "The topic '" + string(entry_node->first_attribute("name")->value()) + "'";
				}
				else
				{
					error_sentence = "An anonymous topic";
				}
				if (!has_type and node_name == "learn")
				{
					out << error_sentence << " doesn't has type" << endl;
				}
				if (repeated_type and node_name == "learn")
				{
					out << error_sentence << " has a type repeated" << endl;
				}
				if (!has_category)
				{
					out << error_sentence << " doesn't has category" << endl;
				}
				if (repeated_category)
				{
					out << error_sentence << " has a category repeated" << endl;
				}
				if (!exists_category)
				{
					if (printed_categories.size() > 0)
					{
						for (const string& printed_category : printed_categories)
						{
							if (printed_category == string(entry_node->first_attribute("category")->value()))
							{
								already_printed_category = true;
							}
						}
					}
					if (!already_printed_category)
					{
						out << error_sentence << " has the category " << scilog_cli::cyan_text << string(entry_node->first_attribute("category")->value()) << scilog_cli::normal_text << " that doesn't exists" << endl;
						printed_categories.push_back(string(entry_node->first_attribute("category")->value()));
					}
				}
				if (!has_name)
				{
					out << error_sentence << " doesn't has name" << endl;
				}
				if (repeated_name)
				{
					out << error_sentence << " has a name repeated" << endl;
				}
				if (!has_start_date)
				{
					out << error_sentence << " doesn't has start date" << endl;
				}
				if (repeated_start_date)
				{
					out << error_sentence << " has a start date repeated" << endl;
				}
				if (!has_end_date)
				{
					out << error_sentence << " doesn't has end date" << endl;
				}
				if (repeated_end_date)
				{
					out << error_sentence << " has a end date repeated" << endl;
				}
				if (has_type)
				{
					string type = string(entry_node->first_attribute("type")->value());
					if (!has_pages and type == "book")
					{
						out << error_sentence << " doesn't has pages attribute" << endl;
					}
					if (repeated_pages)
					{
						out << error_sentence << " has a pages attribute repeated" << endl;
					}
				}
				if (repeated_parent)
				{
					out << error_sentence << " has a parent repeated" << endl;
				}
			}
		}
		return out.str();
	}
}
