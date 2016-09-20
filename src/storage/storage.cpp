#include <storage/storage.h>

#include <iostream>

storage::storage ()
	: s()
	, m()
{
}

storage::~storage ()
{
}

bool storage::add (const artist_ptr_t& artist)
{
	if (artist)
	{
		lock_t lock(this->m);

		auto& index = this->s.get<name_tag_t>();
		auto it = index.find(artist->get_name());

		if (it == index.end())
		{
			this->s.insert(artist);
			return true;
		}
	}

	return false;
}

bool storage::replace (const artist_ptr_t& artist)
{
	lock_t lock(this->m);
	
	auto& index = this->s.get<name_tag_t>();
	auto it = index.find(artist->get_name());
	
	if (it != index.end())
	{
		index.replace(it, artist);
		return true;
	}
	
	return false;
}

artist_ptr_t storage::get_by_name (const std::string& name) const
{
	lock_t lock(this->m);
	auto& index = this->s.get<name_tag_t>();
	auto it = index.find(name);
	return (it != index.end() ? (*it) : nullptr);
}

artist_ptr_t storage::get_by_id (const std::string& id) const
{
	lock_t lock(this->m);
	auto& index = this->s.get<id_tag_t>();
	auto it = index.find(id);
	return (it != index.end() ? (*it) : nullptr);
}

void storage::print_all (std::ostream& stream) const
{
	auto& index = this->s.get<name_tag_t>();
	for (auto it = index.begin(); it != index.end(); ++it)
	{
		auto r = (*it)->get_releases();
		auto lr = (*it)->get_local_releases();

		if (!r.empty() && !lr.empty())
		{
			auto jt = r.upper_bound(*lr.rbegin());

			stream << "local: " << std::endl;
			for (auto kt = lr.begin(); kt != lr.end(); ++kt)
			{
				stream << "\t" << **kt << std::endl;
			}

			stream << "all: " << std::endl;
			for (auto kt = r.begin(); kt != r.end(); ++kt)
			{
				stream << "\t" << **kt << std::endl;
			}

			if (jt != r.end())
			{
				stream << (*it)->get_name() << std::endl;
				for (; jt != r.end(); ++jt)
				{
					stream << "\t" << **jt << std::endl;
				}
			}
		}
	}
}
