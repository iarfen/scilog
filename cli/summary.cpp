#include "summary.hpp"
#include "core/entry.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <vector>


#include "core/xml_parser.hpp"

using namespace std;

namespace scilog_cli
{
	void command_summary_month(const string& filename)
	{
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filename);
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

	void command_summary_month_by_topics(const string& filename)
	{
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filename);
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

	void command_summary_year()
	{
		int total_entries = 0;

		int total_learn_entries = 0;
		int total_project_entries = 0;

		int total_learn_book_entries = 0;
		int total_learn_documentation_entries = 0;
		int total_learn_planification_entries = 0;

		int total_project_theory_entries = 0;
		int total_project_design_entries = 0;
		int total_project_programming_entries = 0;
		int total_project_planification_entries = 0;

		vector<string> filenames = {/*"01-january","02-february","03-march","04-april","05-may","06-june","07-july","08-august","09-september","10-october",*/"11-november","12-december"};

		for (const string& filename : filenames)
		{
			vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filename + ".xml");
			total_entries += entries.size();
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
		}
		cout << "total entries: " << total_entries << endl;

		cout << "total learn entries: " << total_learn_entries << "    " << (100 * total_learn_entries / total_entries) << " %" << endl;
		cout << "total project entries: " << total_project_entries << "    " << (100 * total_project_entries / total_entries) << " %" << endl << endl;

		cout << "learn book entries: " << total_learn_book_entries << "    " << (100 * total_learn_book_entries / total_learn_entries) << " %" << endl;
		cout << "learn documentation entries: " << total_learn_documentation_entries << "    " << (100 * total_learn_documentation_entries / total_learn_entries) << " %" << endl;
		cout << "learn planification entries: " << total_learn_planification_entries << "    " << (100 * total_learn_planification_entries / total_learn_entries) << " %" << endl << endl;

		cout << "project theory entries: " << total_project_theory_entries << "    " << (100 * total_project_theory_entries / total_project_entries) << " %" << endl;
		cout << "project design entries: " << total_project_design_entries << "    " << (100 * total_project_design_entries / total_project_entries) << " %" << endl;
		cout << "project programming entries: " << total_project_programming_entries << "    " << (100 * total_project_programming_entries / total_project_entries) << " %" << endl;
		cout << "project planification entries: " << total_project_planification_entries << "    " << (100 * total_project_planification_entries / total_project_entries) << " %" << endl << endl;
	}
}
