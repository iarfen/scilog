#include "scilog_file.hpp"
#include "categories.hpp"
#include "xml_parser.hpp"

#include <chrono>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	string get_filename_from_month_number(const string& x)
	{
		if (x == "1" or x == "01" or x == "january")
		{
			return "01-january.xml";
		}
		else if (x == "2" or x == "02" or x == "february")
		{
			return "02-february.xml";
		}
		else if (x == "3" or x == "03" or x == "march")
		{
			return "03-march.xml";
		}
		else if (x == "4" or x == "04" or x == "april")
		{
			return "04-april.xml";
		}
		else if (x == "5" or x == "05" or x == "may")
		{
			return "05-may.xml";
		}
		else if (x == "6" or x == "06" or x == "june")
		{
			return "06-june.xml";
		}
		else if (x == "7" or x == "07" or x == "july")
		{
			return "07-july.xml";
		}
		else if (x == "8" or x == "08" or x == "august")
		{
			return "08-august.xml";
		}
		else if (x == "9" or x == "09" or x == "september")
		{
			return "09-september.xml";
		}
		else if (x == "10" or x == "october")
		{
			return "10-october.xml";
		}
		else if (x == "11" or x == "november")
		{
			return "11-november.xml";
		}
		else if (x == "12" or x == "december")
		{
			return "12-december.xml";
		}
		else if (x == "now")
		{
			time_t current_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
			tm* current_tm = localtime(&current_time);
			return get_filename_from_month_number(to_string(current_tm->tm_mon + 1));
		}
		else
		{
			return x;
		}
	}

	vector<category> get_all_categories()
	{
		vector<category> categories;
		if (boost::filesystem::exists("topics.xml"))
		{
			categories = create_categories_from_scilog_file("topics.xml");
		}
		for (const auto& default_category : default_categories)
		{
			categories.push_back(default_category.second);
		}
		return categories;
	}

	map<string,category> get_all_categories_map()
	{
		map<string,category> categories = default_categories;
		if (boost::filesystem::exists("topics.xml"))
		{
			vector<category> topic_categories = create_categories_from_scilog_file("topics.xml");
			if (topic_categories.size() > 0)
			{
				for (const category& x_category : topic_categories)
				{
					categories[x_category.get_name()] = x_category;
				}
			}
		}
		return categories;
	}

	bool is_year_directory(const string& directory_path)
	{
		vector<string> filenames = {"01-january","02-february","03-march","04-april","05-may","06-june","07-july","08-august","09-september","10-october","11-november","12-december"};
		for (const string& filename : filenames)
		{
			if (boost::filesystem::exists(directory_path + "/" + filename + ".xml"))
			{
				return true;
			}
		}
		if (boost::filesystem::exists(directory_path + "/" + "topics.xml"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
