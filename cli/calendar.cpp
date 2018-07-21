#include "calendar.hpp"

#include "core/entry.hpp"
#include "core/filesystem.hpp"
#include "core/xml_parser.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "cafi/cafi.hpp"

using namespace std;

namespace scilog_cli
{
	void command_calendar_month(const string& x,const string& year)
	{
		string filename = cafi::get_filename_from_month(x);
		if (!check_scilog_file(filename,year,true,true))
		{
			return;
		}
		string filepath = cafi::root_dir + "/" + year + "/" + filename;
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath,x,year);
		print_calendar(x,year);
		cout << endl;
	}

	void print_calendar(const string& x,const string& year)
	{
		string filename = cafi::get_filename_from_month(x);
		string filepath = cafi::root_dir + "/" + year + "/" + filename;
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath,x,year);
		string month;
		if (!(x == "10" or x == "11" or x == "12"))
		{
			month = "0" + x;
		}
		else
		{
			month = x;
		}
		boost::gregorian::date x_date = boost::gregorian::from_string(year + "-" + month + "-01");
		int first_day_type = x_date.day_of_week().as_number();
		int total_days = x_date.end_of_month().day();
		cafi::calendar_table x_calendar = cafi::calendar_table(stoi(year),stoi(month),true,22);
		for (const shared_ptr<entry>& x_entry : entries)
		{
			string x_day = x_entry->get_date();
			x_calendar.add_cell(stoi(x_day.substr(8,2)),x_entry->get_topic());
		}
		cout << x_calendar.display();
	}
}
