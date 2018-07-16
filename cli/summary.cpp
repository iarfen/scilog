#include "summary.hpp"
#include "cli/cli.hpp"
#include "core/conf.hpp"
#include "core/entry.hpp"
#include "core/topic.hpp"
#include "core/learn_topic.hpp"
#include "core/project_topic.hpp"
#include "core/learn_entry.hpp"
#include "core/project_entry.hpp"
#include "core/categories.hpp"
#include "core/xml_parser.hpp"
#include "core/filesystem.hpp"

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <map>
#include <memory>
#include <vector>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/filesystem.hpp"
#include "cafi/cafi.hpp"

using namespace std;

namespace scilog_cli
{
	void command_summary_month(const string& x,const string& year,bool month_case)
	{
		string filename = cafi::get_filename_from_month(x);
		if (!check_scilog_file(filename,year,month_case,month_case))
		{
			return;
		}
		string filepath = cafi::root_dir + "/" + year + "/" + filename;
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath,x,year);
		print_summary(entries);
		cout << endl;
	}

	void command_summary_month_by_topics(const string& x,const string& year,bool month_case)
	{
		string filename = cafi::get_filename_from_month(x);
		if (!check_scilog_file(filename,year,month_case,month_case))
		{
			return;
		}
		string filepath = cafi::root_dir + "/" + year + "/" + filename;
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath,x,year);
		print_topics(entries);
		cout << endl;
	}

	void command_summary_month_by_sciences(const string& x,const string& year,bool month_case)
	{
		string filename = cafi::get_filename_from_month(x);
		if (!check_scilog_file(filename,year,month_case,month_case))
		{
			return;
		}
		string filepath = cafi::root_dir + "/" + year + "/" + filename;
		check_scilog_topics_file("topics.scilog_topics",year,false,true);
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath,x,year);
		const map<string,shared_ptr<topic>>& topics = get_all_topics_map();
		print_sciences(entries,topics);
		cout << endl;
	}

	void command_summary_year(const string& year,bool each)
	{
		vector<string> year_months = cafi::get_year_months();
		for (const string& x_month : year_months)
		{
			string filename = cafi::get_filename_from_month(x_month);
			check_scilog_file(filename,year,false,true);
		}
		if (!each)
		{
			vector<shared_ptr<entry>> entries = get_year_entries(year);
			print_summary(entries);
		}
		else
		{
			command_summary_month("1",year,false);
			command_summary_month("2",year,false);
			command_summary_month("3",year,false);
			command_summary_month("4",year,false);
			command_summary_month("5",year,false);
			command_summary_month("6",year,false);
			command_summary_month("7",year,false);
			command_summary_month("8",year,false);
			command_summary_month("9",year,false);
			command_summary_month("10",year,false);
			command_summary_month("11",year,false);
			command_summary_month("12",year,false);
		}
	}

	void command_summary_year_by_topics(const string& year,bool each)
	{
		vector<string> year_months = cafi::get_year_months();
		for (const string& x_month : year_months)
		{
			string filename = cafi::get_filename_from_month(x_month);
			check_scilog_file(filename,year,false,true);
		}
		vector<shared_ptr<entry>> entries = get_year_entries(year);
		print_topics(entries);
	}

	void command_summary_year_by_sciences(const string& year,bool each)
	{
		vector<string> year_months = cafi::get_year_months();
		for (const string& x_month : year_months)
		{
			string filename = cafi::get_filename_from_month(x_month);
			check_scilog_file(filename,year,false,true);
		}
		check_scilog_topics_file("topics.scilog_topics",year,false,true);
		vector<shared_ptr<entry>> entries = get_year_entries(year);
		const map<string,shared_ptr<topic>>& topics = get_all_topics_map();
		print_sciences(entries,topics);
	}

	void command_summary_all_years()
	{
		map<string,vector<string>> months = cafi::get_all_years_months();
		for (const auto& x : months)
		{
			for (const string& x_month : x.second)
			{
				string filename = cafi::get_filename_from_month(x_month);
				check_scilog_file(filename,x.first,false,true);
			}
		}
		vector<string> paths = cafi::get_years_path(cafi::root_dir);
		vector<shared_ptr<entry>> entries = get_all_years_entries(paths);
		print_summary(entries);
	}

	void command_summary_all_years_by_topics()
	{
		map<string,vector<string>> months = cafi::get_all_years_months();
		for (const auto& x : months)
		{
			for (const string& x_month : x.second)
			{
				string filename = cafi::get_filename_from_month(x_month);
				check_scilog_file(filename,x.first,false,true);
			}
		}
		vector<string> paths = cafi::get_years_path(cafi::root_dir);
		vector<shared_ptr<entry>> entries = get_all_years_entries(paths);
		print_topics(entries);
	}

	void command_summary_all_years_by_sciences()
	{
		map<string,vector<string>> months = cafi::get_all_years_months();
		for (const auto& x : months)
		{
			for (const string& x_month : x.second)
			{
				string filename = cafi::get_filename_from_month(x_month);
				check_scilog_file(filename,x.first,false,true);
			}
			check_scilog_topics_file("topics.scilog_topics",x.first,false,true);
		}
		vector<string> paths = cafi::get_years_path(cafi::root_dir);
		vector<shared_ptr<entry>> entries = get_all_years_entries(paths);
		const map<string,shared_ptr<topic>>& topics = get_all_topics_map();
		print_sciences(entries,topics);
	}

	void print_summary(vector<shared_ptr<entry>>& entries)
	{
		sort(entries.begin(),entries.end(),[](const shared_ptr<entry>& a,const shared_ptr<entry>& b) -> bool { return a->get_date() < b->get_date(); });
		int total_worked_days = 0;
		int total_of_pages = 0;

		int total_learn_entries = 0;
		int total_project_entries = 0;

		map<string,int> learn_entries = map<string,int>();
		int total_learn_book_entries = 0;
		int total_learn_documentation_entries = 0;
		int total_learn_planification_entries = 0;

		map<string,int> project_entries = map<string,int>();

		map<string,shared_ptr<topic>> topics = get_all_topics_map();

		for (const shared_ptr<entry>& entry : entries)
		{
			if (entry->get_kind() == "learn")
			{
				total_learn_entries++;
				if (topics.count(entry->get_topic()) > 0)
				{
					const shared_ptr<learn_topic>& actual_topic = dynamic_pointer_cast<learn_topic>(topics.at(entry->get_topic()));
					if (actual_topic->get_type() == "book")
					{
						total_learn_book_entries++;
						continue;
					}
					else if (actual_topic->get_type() == "documentation")
					{
						total_learn_documentation_entries++;
						continue;
					}
					else if (actual_topic->get_type() == "planification")
					{
						total_learn_planification_entries++;
						continue;
					}
				}
				if (learn_entries.count(entry->get_type()) == 0)
				{
					learn_entries[entry->get_type()] = 0;
				}
				learn_entries[entry->get_type()]++;
			}
			else if (entry->get_kind() == "project")
			{
				total_project_entries++;
				if (project_entries.count(entry->get_type()) == 0)
				{
					project_entries[entry->get_type()] = 0;
				}
				project_entries[entry->get_type()]++;
			}
		}

		map<int,map<int,map<int,bool>>> worked_days;
		for (const shared_ptr<entry>& x_entry : entries)
		{
			boost::gregorian::date x_date = boost::gregorian::from_string(x_entry->get_date());
			worked_days[x_date.year()][x_date.year_month_day().month][x_date.day()] = true;
		}

		int total_of_days = 0;
		for (const auto& x_year : worked_days)
		{
			for (const auto& x_month : x_year.second)
			{
				boost::gregorian::date x_date = boost::gregorian::from_string(to_string(x_year.first)+"-"+to_string(x_month.first)+"-01");
				boost::gregorian::date x_end_month = x_date.end_of_month();
				total_of_days += x_end_month.day();
				total_worked_days += x_month.second.size();
			}
		}

		map<string,map<string,int>> page_points = map<string,map<string,int>>();
		for (const shared_ptr<entry>& x_entry : entries)
		{
			if (x_entry->get_kind() == "learn")
			{
				const shared_ptr<learn_entry>& x_learn_entry = dynamic_pointer_cast<learn_entry>(x_entry);
				page_points[x_learn_entry->get_topic()][x_learn_entry->get_date()] = x_learn_entry->get_page_point();
			}
		}

		if (page_points.size() > 0)
		{
			for (const auto& x : page_points)
			{
				int previous_page_point = -1;
				string x_topic = x.first;
				string x_date = x.second.begin()->first;
				int previous_month_page_point = previous_pages(x_topic,x_date);
				if (previous_month_page_point != 0)
				{
					total_of_pages += (x.second.at(x_date) - previous_month_page_point);
				}
				else
				{
					total_of_pages += x.second.at(x_date);
				}
				for (const auto& y : page_points[x.first])
				{
					if (previous_page_point > 0 and y.second > 0)
					{
						total_of_pages += (y.second - previous_page_point);
					}
					previous_page_point = y.second;
				}
			}
		}

		cout << scilog_cli::normal_text << "total entries: " << scilog_cli::cyan_text << entries.size() << endl;

		cout << scilog_cli::normal_text << "total worked days: " << scilog_cli::cyan_text << (100 * total_worked_days / total_of_days) << " %" << endl;

		cout << scilog_cli::normal_text << "readed pages: " << scilog_cli::cyan_text << total_of_pages << endl;

		cout << scilog_cli::normal_text << "total learn entries: " << scilog_cli::cyan_text << total_learn_entries << "    " << (100 * total_learn_entries / entries.size()) << " %" << endl;
		cout << scilog_cli::normal_text << "total project entries: " << scilog_cli::cyan_text << total_project_entries << "    " << (100 * total_project_entries / entries.size()) << " %" << endl << endl;

		cout << scilog_cli::normal_text << "learn book entries: " << scilog_cli::cyan_text << total_learn_book_entries << "    " << (100 * total_learn_book_entries / total_learn_entries) << " %" << endl;
		cout << scilog_cli::normal_text << "learn documentation entries: " << scilog_cli::cyan_text << total_learn_documentation_entries << "    " << (100 * total_learn_documentation_entries / total_learn_entries) << " %" << endl;
		cout << scilog_cli::normal_text << "learn planification entries: " << scilog_cli::cyan_text << total_learn_planification_entries << "    " << (100 * total_learn_planification_entries / total_learn_entries) << " %" << endl;

		for (const auto& learn_entry : learn_entries)
		{
			cout << scilog_cli::normal_text << "learn " << learn_entry.first << " entries: " << scilog_cli::cyan_text << learn_entry.second << "    " << (100 * learn_entry.second / total_learn_entries) << " %" << endl;
		}

		cout << endl;

		for (const auto& project_entry : project_entries)
		{
			cout << scilog_cli::normal_text << "project " << project_entry.first << " entries: " << scilog_cli::cyan_text << project_entry.second << "    " << (100 * project_entry.second / total_project_entries) << " %" << endl;
		}
	}

	void print_topics(const vector<shared_ptr<entry>>& entries)
	{
		map<string,int> learn_topics_count = map<string,int>();
		map<string,int> project_topics_count = map<string,int>();
		map<string,shared_ptr<topic>> topics = get_all_topics_map();
		for (const shared_ptr<entry>& entry : entries)
		{
			if (entry->get_topic() != "")
			{
				string parent_topic;
				if (topics.count(entry->get_topic()) > 0)
				{
					parent_topic = topics[entry->get_topic()]->get_parent_topic();
				}
				else
				{
					parent_topic = "";
				}
				if (entry->get_kind() == "learn")
				{
					if (learn_topics_count.count(entry->get_topic()) == 0)
					{
						learn_topics_count[entry->get_topic()] = 0;
					}
					if (parent_topic != "")
					{
						if (learn_topics_count.count(parent_topic) == 0)
						{
							learn_topics_count[parent_topic] = 0;
						}
						learn_topics_count[parent_topic]++;
					}
					learn_topics_count[entry->get_topic()]++;
				}
				else if (entry->get_kind() == "project")
				{
					if (project_topics_count.count(entry->get_topic()) == 0)
					{
						project_topics_count[entry->get_topic()] = 0;
					}
					if (parent_topic != "")
					{
						if (project_topics_count.count(parent_topic) == 0)
						{
							project_topics_count[parent_topic] = 0;
						}
						project_topics_count[parent_topic]++;
					}
					project_topics_count[entry->get_topic()]++;
				}
			}
		}
		cout << scilog_cli::normal_text << "total entries: " << scilog_cli::cyan_text << entries.size() << endl << endl;
		for (auto learn_topic_count : learn_topics_count)
		{
			if (topics.count(learn_topic_count.first) and topics[learn_topic_count.first]->get_parent_topic() != "")
			{
				continue;
			}
			cout << scilog_cli::normal_text << "learn " << scilog_cli::cyan_text << learn_topic_count.first << ": " << learn_topic_count.second << endl;
			for (const auto& x_topic : topics)
			{
				if (x_topic.second->get_parent_topic() != "" and x_topic.second->get_parent_topic() == learn_topic_count.first)
				{
					cout << scilog_cli::normal_text << "--learn " << scilog_cli::cyan_text << x_topic.second->get_name() << ": " << learn_topics_count[x_topic.second->get_name()] << endl;
				}
			}
		}
		cout << endl;
		for (const auto& project_topic_count : project_topics_count)
		{
			if (topics.count(project_topic_count.first) and topics[project_topic_count.first]->get_parent_topic() != "")
			{
				continue;
			}
			cout << scilog_cli::normal_text << "project " << scilog_cli::cyan_text << project_topic_count.first << ": " << project_topic_count.second << endl;
			for (const auto& x_topic : topics)
			{
				if (x_topic.second->get_parent_topic() != "" and x_topic.second->get_parent_topic() == project_topic_count.first)
				{
					cout << scilog_cli::normal_text << "--project " << scilog_cli::cyan_text << x_topic.second->get_name() << ": " << project_topics_count[x_topic.second->get_name()] << endl;
				}
			}
		}
	}

	void print_sciences(const vector<shared_ptr<entry>>& entries,const map<string,shared_ptr<topic>>& topics)
	{
		map<string,int> learn_sciences_count = map<string,int>();
		map<string,int> project_sciences_count = map<string,int>();
		bool learn_entry;
		map<string,category> categories = get_all_categories_map();
		for (const shared_ptr<entry>& log_entry : entries)
		{
			if (log_entry->get_kind() == "learn")
			{
				learn_entry = true;
			}
			else
			{
				learn_entry = false;
			}
			if (topics.count(log_entry->get_topic()) == 0)
			{
				continue;
			}
			const shared_ptr<topic>& actual_topic = topics.at(log_entry->get_topic());
			/*vector<shared_ptr<topic>>::iterator actual_topic = find_if(topics.begin(),topics.end(),[log_entry](const shared_ptr<topic>& x) -> bool { return x->get_name() == log_entry->get_topic(); });
			if (actual_topic == topics.end())
			{
				continue;
			}*/
			if (learn_entry)
			{
				if (learn_sciences_count[actual_topic->get_category()] == 0)
				{
					learn_sciences_count[actual_topic->get_category()] = 0;
				}
				learn_sciences_count[actual_topic->get_category()]++;
			}
			else
			{
				if (project_sciences_count[actual_topic->get_category()] == 0)
				{
					project_sciences_count[actual_topic->get_category()] = 0;
				}
				project_sciences_count[actual_topic->get_category()]++;
			}
			if (actual_topic->get_category() != "")
			{
				category& actual_category = categories[actual_topic->get_category()];
				while (true)
				{
					if (actual_category.get_name() == "")
					{
						break;
					}
					if (learn_entry)
					{
						if (learn_sciences_count[actual_category.get_name()] == 0)
						{
							learn_sciences_count[actual_category.get_name()] = 0;
						}
						learn_sciences_count[actual_category.get_name()]++;
					}
					else
					{
						if (project_sciences_count[actual_category.get_name()] == 0)
						{
							project_sciences_count[actual_category.get_name()] = 0;
						}
						project_sciences_count[actual_category.get_name()]++;
					}
					actual_category = categories[actual_category.get_parent_category()];
					if (actual_category.get_parent_category() == "")
					{
						break;
					}
				}
			}
		}
		cout << scilog_cli::normal_text << "total of topics to learn: " << scilog_cli::cyan_text << learn_sciences_count.size() << endl;
		for (const auto& learn_science_count : learn_sciences_count)
		{
			cout << scilog_cli::normal_text << "learn " << learn_science_count.first << ": " << scilog_cli::cyan_text << learn_science_count.second << endl;
		}
		cout << endl;
		cout << scilog_cli::normal_text << "total of projects: " << scilog_cli::cyan_text << project_sciences_count.size() << endl;
		for (const auto& project_science_count : project_sciences_count)
		{
			cout << scilog_cli::normal_text << "project " << project_science_count.first << ": " << scilog_cli::cyan_text << project_science_count.second << endl;
		}
	}
}
