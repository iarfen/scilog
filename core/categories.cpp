#include "categories.hpp"

#include "core/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	map<string,category> default_categories
	{
		{"informatics",category("informatics","")},
		{"application",category("application","informatics")},
		{"cli-application",category("cli-application","application")},
		{"desktop-application",category("desktop-application","application")},
		{"library",category("library","informatics")},
		{"internet",category("internet","informatics")},
		{"open-source",category("open-source","informatics")},
		{"website",category("website","internet")},
		{"internet-theory",category("internet-theory","internet")},
		{"w3c-standards",category("w3c-standards","internet-theory")},
		{"videogame",category("videogame","informatics")},
		{"os",category("os","informatics")},
		{"linux",category("linux","os")},
		{"ios",category("ios","os")},
		{"windows",category("windows","os")},
		{"ubuntu",category("ubuntu","linux")},
		{"fedora",category("fedora","linux")},
		{"chemistry",category("chemistry","")},
		{"organic-chemistry",category("organic-chemistry","chemistry")},
		{"inorganic-chemistry",category("inorganic-chemistry","chemistry")},
		{"biochemistry",category("biochemistry","chemistry")},
		{"analytical-chemistry",category("analytical-chemistry","chemistry")},
		{"physical-chemistry",category("physical-chemistry","chemistry")},
		{"biology",category("biology","")},
		{"cell-biology",category("cell-biology","biology")},
		{"nutrition",category("nutrition","biology")},
		{"genetics",category("genetics","biology")},
		{"medicine-research",category("medicine-research","biology")},
		{"zoology",category("zoology","biology")},
		{"botanics",category("botanics","biology")},
		{"microbiology",category("microbiology","biology")},
		{"physics",category("physics","")},
		{"acoustics",category("acoustics","physics")},
		{"agrophysics",category("agrophysics","physics")},
		{"soil-physics",category("soil-physics","agrophysics")},
		{"astrophysics",category("astrophysics","physics")},
		{"astronomy",category("astronomy","physics")},
		{"astrodynamics",category("astrodynamics","astronomy")},
		{"astrometry",category("astrometry","astronomy")},
		{"extragalactic-astronomy",category("extragalactic-astronomy","astronomy")},
		{"galactic-astronomy",category("galactic-astronomy","astronomy")},
		{"physical-cosmology",category("physical-cosmology","astronomy")},
		{"planetary-science",category("planetary-science","astronomy")},
		{"stellar-astronomy",category("stellar-astronomy","astronomy")},
		{"atmospheric-physics",category("atmospheric-physics","physics")},
		{"AMO-physics",category("AMO-physics","physics")},
		{"biophysics",category("biophysics","physics")},
		{"medical-physics",category("medical-physics","biophysics")},
		{"neurophysics",category("neurophysics","biophysics")},
		{"chemical-physics",category("chemical-physics","physics")},
		{"classical-physics",category("classical-physics","physics")},
		{"computational-physics",category("computational-physics","physics")},
		{"condensed-matter-physics",category("condensed-matter-physics","physics")},
		{"cryogenics",category("cryogenics","physics")},
		{"thermodynamics",category("thermodynamics","physics")},
		{"electromagnetism",category("electromagnetism","physics")},
		{"geophysics",category("geophysics","physics")},
		{"homeokinetics",category("homeokinetics","physics")},
		{"materials-physics",category("materials-physics","physics")},
		{"mathematical-physics",category("mathematical-physics","physics")},
		{"mechanics",category("mechanics","physics")},
		{"aerodynamics",category("aerodynamics","mechanics")},
		{"biomechanics",category("biomechanics","mechanics")},
		{"classical-mechanics",category("classical-mechanics","mechanics")},
		{"kinematics",category("kinematics","classical-mechanics")},
		{"continuum-mechanics",category("continuum-mechanics","mechanics")},
		{"fluid-mechanics",category("fluid-mechanics","mechanics")},
		{"fluid-statics",category("fluid-statics","fluid-mechanics")},
		{"fluid-kinematics",category("fluid-kinematics","fluid-mechanics")},
		{"fluid-dynamics",category("fluid-dynamics","fluid-mechanics")},
		{"quantum-mechanics",category("quantum-mechanics","mechanics")},
		{"nuclear-physics",category("nuclear-physics","physics")},
		{"optics",category("optics","physics")},
		{"particle-physics",category("particle-physics","physics")},
		{"psychophysics",category("psychophysics","physics")},
		{"plasma-physics",category("plasma-physics","physics")},
		{"polymer-physics",category("polymer-physics","physics")},
		{"quantum-physics",category("quantum-physics","physics")},
		{"relativity",category("relativity","physics")},
		{"statics",category("statics","physics")},
		{"solid-state-physics",category("solid-state-physics","physics")},
		{"theoretical-physics",category("theoretical-physics","physics")},
		{"vehicle-dynamics",category("vehicle-dynamics","physics")},
		{"mathematics",category("mathematics","")},
		{"pure-mathematics",category("pure-mathematics","mathematics")},
		{"algebra",category("algebra","pure-mathematics")},
		{"calculus-and-analysis",category("calculus-and-analysis","pure-mathematics")},
		{"geometry-and-topology",category("geometry-and-topology","pure-mathematics")},
		{"combinatorics",category("combinatorics","pure-mathematics")},
		{"logic",category("logic","pure-mathematics")},
		{"number-theory",category("number-theory","pure-mathematics")},
		{"applied-mathematics",category("applied-mathematics","mathematics")},
		{"differential-equations",category("differential-equations","applied-mathematics")},
		{"computation",category("computation","applied-mathematics")},
		{"information-theory",category("information-theory","applied-mathematics")},
		{"probability-and-statistics",category("probability-and-statistics","applied-mathematics")},
		{"game-theory",category("game-theory","applied-mathematics")},
		{"operations-research",category("operations-research","applied-mathematics")},
		{"language",category("language","")}
	};

	map<string,category> all_categories = map<string,category>();

	bool is_parent_category(const string& actual_category,const string& parent_category)
	{
		if (all_categories[actual_category].get_parent_category() == parent_category)
		{
			return true;
		}
		else if (all_categories[actual_category].get_parent_category() == "")
		{
			return false;
		}
		else
		{
			return is_parent_category(all_categories[actual_category].get_parent_category(),parent_category);
		}
	}

	void initialize_all_categories()
	{
		all_categories = default_categories;
		vector<string> years_path = get_years_path(get_current_source_path());
		vector<category> vector_categories = get_all_years_categories(years_path);
		for (const category& x_category : vector_categories)
		{
			all_categories[x_category.get_name()] = x_category;
		}
	}
}
