#include <storage/printer/text.h>

namespace printer
{

void text::print (const storage& s, std::ostream& out) const
{
	for (auto it = s.begin(); it != s.end(); ++it)
	{
		auto r = (*it)->get_releases();
		auto lr = (*it)->get_local_releases();

		if (!r.empty() && !lr.empty())
		{
			auto jt = r.upper_bound(*lr.rbegin());

			out << (*it)->get_name() << std::endl;

			out << "local: " << std::endl;

			for (auto kt = lr.begin(); kt != lr.end(); ++kt)
			{
				out << "\t" << **kt << std::endl;
			}

			out << "all: " << std::endl;

			for (auto kt = r.begin(); kt != r.end(); ++kt)
			{
				out << "\t" << **kt << std::endl;
			}

			if (jt != r.end())
			{
				out << "new: " << std::endl;

				for (; jt != r.end(); ++jt)
				{
					out << "\t" << **jt << std::endl;
				}
			}
		}
	}
}

}
