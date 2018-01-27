#include "sql_parser.hpp"

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
			<< "type ENUM(learn,project) NOT NULL,"
			<< "id_category VARCHAR(100) NOT NULL,"
			<< "start_date TIMESTAMP NOT NULL,"
			<< "end_date TIMESTAMP NOT NULL,"
			<< "description LONGTEXT NOT NULL"
			<< ") "
			<< "FOREIGN KEY id_category REFERENCES " << table_prefix << "categories(id)" << ";" << endl << endl;
		out << "CREATE TABLE IF NOT EXISTS " << table_prefix << "entries ("
			<< "id BIGINT UNSIGNED PRIMARY KEY AUTO_INCREMENT,"
			<< "type VARCHAR(100) NOT NULL,"
			<< "subtype VARCHAR(100) NOT NULL,"
			<< "id_topic BIGINT UNSIGNED NOT NULL,"
			<< "date TIMESTAMP NOT NULL,"
			<< "description LONGTEXT NOT NULL"
			<< ") "
			<< "FOREIGN KEY id_topic REFERENCES " << table_prefix << "topics(id)" << ";" << endl << endl;
		for (const shared_ptr<entry>& x_entry : entries)
		{
		}
		cout << out.str() << endl;
	}
}
