#include "sql_parser.hpp"
#include "categories.hpp"

#include <iostream>
#include <sstream>

using namespace std;

namespace scilog_cli
{
	void print_sql_dump(const vector<shared_ptr<entry>>& entries,const vector<shared_ptr<topic>>& topics,string table_prefix)
	{
		ostringstream out;
		if (table_prefix != "")
		{
			table_prefix = table_prefix + "_";
		}
		out << "CREATE TABLE IF NOT EXISTS " << table_prefix << "categories ("
			<< "id BIGINT UNSIGNED PRIMARY KEY AUTO_INCREMENT,"
			<< "name VARCHAR(100) NOT NULL,"
			<< "id_parent_category VARCHAR(100) NOT NULL"
			<< ");" << endl << endl;
		out << "CREATE TABLE IF NOT EXISTS " << table_prefix << "topics ("
			<< "id BIGINT UNSIGNED PRIMARY KEY AUTO_INCREMENT,"
			<< "type ENUM('learn','project') NOT NULL,"
			<< "id_category BIGINT UNSIGNED NOT NULL,"
			<< "start_date TIMESTAMP NOT NULL,"
			<< "end_date TIMESTAMP NOT NULL,"
			<< "description LONGTEXT NOT NULL,"
			<< "FOREIGN KEY(id_category) REFERENCES " << table_prefix << "categories(id)"
			<< ");" << endl << endl;
		out << "CREATE TABLE IF NOT EXISTS " << table_prefix << "entries ("
			<< "id BIGINT UNSIGNED PRIMARY KEY AUTO_INCREMENT,"
			<< "type VARCHAR(100) NOT NULL,"
			<< "id_topic BIGINT UNSIGNED NOT NULL,"
			<< "date TIMESTAMP NOT NULL,"
			<< "description LONGTEXT NOT NULL,"
			<< "FOREIGN KEY(id_topic) REFERENCES " << table_prefix << "topics(id)"
			<< ");" << endl << endl;
		for (const auto& x : default_categories)
		{
			out << "SELECT id INTO @id_parent_category_value FROM " << table_prefix << "categories WHERE name = '" << x.second.get_name() << "';" << endl;
			out << "INSERT INTO " << table_prefix << "categories (name,id_parent_category) VALUES (\""
				<< x.second.get_name() << "\",@id_parent_category_value);" << endl;
		}
		for (const shared_ptr<topic>& x_topic : topics)
		{
			out << "SELECT id INTO @id_category_value FROM " << table_prefix << "categories WHERE name = '" << x_topic->get_category() << "';" << endl;
			out << "INSERT INTO " << table_prefix << "topics (type,id_category,start_date,end_date,description) VALUES ('"
				<< x_topic->get_type() << "',@id_category_value,UNIX_TIMESTAMP(STR_TO_DATE('" << x_topic->get_start_date() << "', '%d-%m-%Y')),UNIX_TIMESTAMP(STR_TO_DATE('" << x_topic->get_end_date() << "', '%d-%m-%Y')),'" << x_topic->get_description() << "');" << endl;
		}
		for (const shared_ptr<entry>& x_entry : entries)
		{
			out << "SELECT id INTO @id_topic_value FROM " << table_prefix << "topics WHERE name = '" << x_entry->get_topic() << "';" << endl;
			out << "INSERT INTO " << table_prefix << "entries (type,id_topic,date,description) VALUES (\"" << x_entry->get_type() << "\",@id_topic_value,UNIX_TIMESTAMP(STR_TO_DATE('" << x_entry->get_date() << "', '%d-%m-%Y')),\"" << x_entry->get_description() << "\");" << endl;
		}
		cout << out.str() << endl;
	}
}
