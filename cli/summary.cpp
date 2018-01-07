#include "summary.hpp"
#include "core/entry.hpp"
#include "core/topic.hpp"
#include "core/categories.hpp"
#include "core/xml_parser.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void command_summary_month(const string& filename,const string& directory_path)
	{
		if (!boost::filesystem::exists(filename))
		{
			cout << "The requested month doesn't has a file" << endl;
			return;
		}
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(directory_path + "/" + filename);
		print_summary(entries);
	}

	void command_summary_month_by_topics(const string& filename)
	{
		if (!boost::filesystem::exists(filename))
		{
			cout << "The requested month doesn't has a file" << endl;
			return;
		}
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filename);
		print_topics(entries);
	}

	void command_summary_month_by_sciences(const string& filename)
	{
		if (!boost::filesystem::exists(filename))
		{
			cout << "The requested month doesn't has a file" << endl;
			return;
		}
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filename);
		vector<shared_ptr<topic>> topics = create_topics_from_scilog_file("topics.xml");
		print_sciences(entries,topics);
	}

	vector<shared_ptr<entry>> get_year_entries()
	{
		vector<shared_ptr<entry>> out_entries;
		vector<string> filenames = {"01-january","02-february","03-march","04-april","05-may","06-june","07-july","08-august","09-september","10-october","11-november","12-december"};

		for (const string& filename : filenames)
		{
			if (!boost::filesystem::exists(filename + ".xml"))
			{
				continue;
			}
			vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filename + ".xml");
			out_entries.insert(out_entries.begin(),entries.begin(),entries.end());
		}
		return out_entries;
	}

	void command_summary_year(const string& x)
	{
		vector<shared_ptr<entry>> entries = get_year_entries();
		print_summary(entries);
	}

	void command_summary_year_by_topics()
	{
		vector<shared_ptr<entry>> entries = get_year_entries();
		print_topics(entries);
	}

	/*void summary_all_year_files()
	{
		boost::filesystem::directory_iterator end_itr;
		for (boost::filesystem::directory_iterator itr("."); itr != end_itr; ++itr)
		{
			if (is_directory(itr->status()))
			{
				command_summary_year(itr->path().generic_string());
			}
		}
	}*/

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
		cout << "project planification entries: " << total_project_planification_entries << "    " << (100 * total_project_planification_entries / total_project_entries) << " %" << endl << endl;
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
				category& actual_category = default_categories[(*actual_topic)->get_category()];
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
					actual_category = default_categories[actual_category.get_parent_category()];
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
