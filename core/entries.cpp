#include "entries.hpp"

#include "core/xml_parser.hpp"

#include "boost/filesystem.hpp"
#include "cafi/cafi.hpp"

using namespace std;

namespace scilog_cli
{
	map<string,map<string,vector<shared_ptr<entry>>>> all_entries = map<string,map<string,vector<shared_ptr<entry>>>>();

	void load_entries(const string& month,const string& year)
	{
		string filename = cafi::get_filename_from_month(month);
		string filepath = cafi::root_dir + "/" + year + "/" + filename;
		if (all_entries[year][month].size() == 0 and boost::filesystem::exists(filepath))
		{
			all_entries[year][month] = create_entries_from_scilog_file(filepath,month,year);
		}
	}

	const vector<shared_ptr<entry>>& get_entries(const string& month,const string& year)
	{
		load_entries(month,year);
		return all_entries[year][month];
	}
}
