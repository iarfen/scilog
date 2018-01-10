#include "summary.hpp"
#include "core/entry.hpp"
#include "core/topic.hpp"
#include "core/categories.hpp"
#include "core/xml_parser.hpp"
#include "core/filesystem.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void command_summary_month(const string& x,const string& directory_path)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		string filepath = directory_path + "/" + filename;
		if (!boost::filesystem::exists(filepath))
		{
			cout << filepath << " doesn't exist" << endl;
			return;
		}
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath);
		print_summary(entries);
	}

	void command_summary_month_by_topics(const string& x,const string& directory_path)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		string filepath = directory_path + "/" + filename;
		if (!boost::filesystem::exists(filepath))
		{
			cout << filepath << " doesn't exist" << endl;
			return;
		}
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath);
		print_topics(entries);
	}

	void command_summary_month_by_sciences(const string& x,const string& directory_path)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		string filepath = directory_path + "/" + filename;
		string topicspath = directory_path + "/topics.xml";
		if (!boost::filesystem::exists(filepath))
		{
			cout << filepath << " doesn't exist" << endl;
			return;
		}
		if (!boost::filesystem::exists(topicspath))
		{
			cout << topicspath << " doesn't exist" << endl;
			return;
		}
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath);
		vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(topicspath);
		print_sciences(entries,topics);
	}

	vector<shared_ptr<entry>> get_year_entries(const string& directory_path)
	{
		vector<shared_ptr<entry>> out_entries;
		vector<string> filenames = {"01-january","02-february","03-march","04-april","05-may","06-june","07-july","08-august","09-september","10-october","11-november","12-december"};

		for (const string& filename : filenames)
		{
			string filepath = directory_path + "/" + filename + ".xml";
			if (!boost::filesystem::exists(filepath))
			{
				continue;
			}
			vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath);
			out_entries.insert(out_entries.begin(),entries.begin(),entries.end());
		}
		return out_entries;
	}

	vector<shared_ptr<entry>> get_all_years_entries(vector<string> year_paths)
	{
		vector<shared_ptr<entry>> out_entries;
		for (const string& year_path : year_paths)
		{
			vector<shared_ptr<entry>> entries = get_year_entries(year_path);
			out_entries.insert(out_entries.begin(),entries.begin(),entries.end());
		}
		return out_entries;
	}

	vector<string> get_years_path(const string& directory_path)
	{
		vector<string> paths;
		boost::filesystem::directory_iterator end_itr;
		for (boost::filesystem::directory_iterator itr(directory_path); itr != end_itr; ++itr)
		{
			if (is_directory(itr->status()))
			{
				paths.push_back(itr->path().generic_string());
			}
		}
		return paths;
	}

	void command_summary_year(const string& directory_path)
	{
		vector<shared_ptr<entry>> entries = get_year_entries(directory_path);
		print_summary(entries);
	}

	void command_summary_year_by_topics(const string& directory_path)
	{
		vector<shared_ptr<entry>> entries = get_year_entries(directory_path);
		print_topics(entries);
	}

	void command_summary_year_by_sciences(const string& directory_path)
	{
		vector<shared_ptr<entry>> entries = get_year_entries(directory_path);
		string topicspath = directory_path + "/topics.xml";
		if (!boost::filesystem::exists(topicspath))
		{
			cout << topicspath << " doesn't exist" << endl;
			return;
		}
		vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(topicspath);
		print_sciences(entries,topics);
	}

	void command_summary_all_years(const string& directory_path)
	{
		vector<string> paths = get_years_path(directory_path);
		vector<shared_ptr<entry>> entries = get_all_years_entries(paths);
		print_summary(entries);
	}

	void command_summary_all_years_by_topics(const string& directory_path)
	{
		vector<string> paths = get_years_path(directory_path);
		vector<shared_ptr<entry>> entries = get_all_years_entries(paths);
		print_topics(entries);
	}

	void command_summary_all_years_by_sciences(const string& directory_path)
	{
		vector<string> paths = get_years_path(directory_path);
		vector<shared_ptr<entry>> entries = get_all_years_entries(paths);
		string topicspath = directory_path + "/topics.xml";
		if (!boost::filesystem::exists(topicspath))
		{
			cout << topicspath << " doesn't exist" << endl;
			return;
		}
		vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(topicspath);
		print_sciences(entries,topics);
	}

	void print_summary(const vector<shared_ptr<entry>>& entries)
	{
		int total_learn_entries = 0;
		int total_project_entries = 0;

		int total_learn_book_entries = 0;
		int total_learn_documentation_entries = 0;
		int total_learn_planification_entries = 0;

		int total_project_theory_entries = 0;
		int total_project_design_entries = 0;
		int total_project_programming_entries = 0;
		int total_project_planification_entries = 0;

		for (const shared_ptr<entry>& entry : entries)
		{
			if (entry->get_type() == "learn")
			{
				total_learn_entries++;
				if (entry->get_subtype() == "book")
				{
					total_learn_book_entries++;
				}
				else if (entry->get_subtype() == "documentation")
				{
					total_learn_documentation_entries++;
				}
				else if (entry->get_subtype() == "planification")
				{
					total_learn_planification_entries++;
				}
			}
			else if (entry->get_type() == "project")
			{
				total_project_entries++;
				if (entry->get_subtype() == "theory")
				{
					total_project_theory_entries++;
				}
				else if (entry->get_subtype() == "design")
				{
					total_project_design_entries++;
				}
				else if (entry->get_subtype() == "programming")
				{
					total_project_programming_entries++;
				}
				else if (entry->get_subtype() == "planification")
				{
					total_project_planification_entries++;
				}
			}
		}
		cout << "total entries: " << entries.size() << endl;

		cout << "total learn entries: " << total_learn_entries << "    " << (100 * total_learn_entries / entries.size()) << " %" << endl;
		cout << "total project entries: " << total_project_entries << "    " << (100 * total_project_entries / entries.size()) << " %" << endl << endl;

		cout << "learn book entries: " << total_learn_book_entries << "    " << (100 * total_learn_book_entries / total_learn_entries) << " %" << endl;
		cout << "learn documentation entries: " << total_learn_documentation_entries << "    " << (100 * total_learn_documentation_entries / total_learn_entries) << " %" << endl;
		cout << "learn planification entries: " << total_learn_planification_entries << "    " << (100 * total_learn_planification_entries / total_learn_entries) << " %" << endl << endl;

		cout << "project theory entries: " << total_project_theory_entries << "    " << (100 * total_project_theory_entries / total_project_entries) << " %" << endl;
		cout << "project design entries: " << total_project_design_entries << "    " << (100 * total_project_design_entries / total_project_entries) << " %" << endl;
		cout << "project programming entries: " << total_project_programming_entries << "    " << (100 * total_project_programming_entries / total_project_entries) << " %" << endl;
		cout << "project planification entries: " << total_project_planification_entries << "    " << (100 * total_project_planification_entries / total_project_entries) << " %" << endl;
	}

	void print_topics(const vector<shared_ptr<entry>>& entries)
	{
		map<string,int> learn_topics_count = map<string,int>();
		map<string,int> project_topics_count = map<string,int>();
		for (const shared_ptr<entry>& entry : entries)
		{
			if (entry->get_topic() != "")
			{
				if (entry->get_type() == "learn")
				{
					if (learn_topics_count.count(entry->get_topic()) == 0)
					{
						learn_topics_count[entry->get_topic()] = 0;
					}
					learn_topics_count[entry->get_topic()]++;
				}
				else if (entry->get_type() == "project")
				{
					if (project_topics_count.count(entry->get_topic()) == 0)
					{
						project_topics_count[entry->get_topic()] = 0;
					}
					project_topics_count[entry->get_topic()]++;
				}
			}
		}
		cout << "total entries: " << entries.size() << endl << endl;
		for (auto learn_topic_count : learn_topics_count)
		{
			cout << "learn " << learn_topic_count.first << ": " << learn_topic_count.second << endl;
		}
		cout << endl;
		for (auto project_topic_count : project_topics_count)
		{
			cout << "project " << project_topic_count.first << ": " << project_topic_count.second << endl;
		}
	}

	void print_sciences(const vector<shared_ptr<entry>>& entries,vector<shared_ptr<topic>>& topics)
	{
		map<string,int> learn_sciences_count = map<string,int>();
		map<string,int> project_sciences_count = map<string,int>();
		bool learn_entry;
		map<string,category> categories = get_all_categories_map();
		for (const shared_ptr<entry>& log_entry : entries)
		{
			if (log_entry->get_type() == "learn")
			{
				learn_entry = true;
			}
			else
			{
				learn_entry = false;
			}
			vector<shared_ptr<topic>>::iterator actual_topic = find_if(topics.begin(),topics.end(),[log_entry](const shared_ptr<topic>& x) -> bool { return x->get_name() == log_entry->get_topic(); });
			if (actual_topic == topics.end())
			{
				continue;
			}
			if (learn_entry)
			{
				if (learn_sciences_count[(*actual_topic)->get_category()] == 0)
				{
					learn_sciences_count[(*actual_topic)->get_category()] = 0;
				}
				learn_sciences_count[(*actual_topic)->get_category()]++;
			}
			else
			{
				if (project_sciences_count[(*actual_topic)->get_category()] == 0)
				{
					project_sciences_count[(*actual_topic)->get_category()] = 0;
				}
				project_sciences_count[(*actual_topic)->get_category()]++;
			}
			if ((*actual_topic)->get_category() != "")
			{
				category& actual_category = categories[(*actual_topic)->get_category()];
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
		cout << "total of topics to learn: " << learn_sciences_count.size() << endl;
		for (const auto& learn_science_count : learn_sciences_count)
		{
			cout << "learn " << learn_science_count.first << ": " << learn_science_count.second << endl;
		}
		cout << endl;
		cout << "total of projects: " << project_sciences_count.size() << endl;
		for (const auto& project_science_count : project_sciences_count)
		{
			cout << "project " << project_science_count.first << ": " << project_science_count.second << endl;
		}
	}
}
