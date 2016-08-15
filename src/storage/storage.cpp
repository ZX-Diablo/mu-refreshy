#include <storage/storage.h>

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
	lock_t lock(this->m);
	
	auto& index = this->s.get<name_tag_t>();
	auto it = index.find(artist->get_name());
	
	if (it == index.end())
	{
		this->s.insert(artist);
		return true;
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

void storage::print_all () const
{
	auto& index = this->s.get<name_tag_t>();
	for (auto it = index.begin(); it != index.end(); ++it)
	{
		auto r = (*it)->get_releases();
		auto lr = (*it)->get_local_releases();
		auto jt = r.upper_bound(*lr.rbegin());

		std::cout << "local: " << std::endl;
		for (auto kt = lr.begin(); kt != lr.end(); ++kt)
		{
			std::cout << "\t" << (*kt)->get_date() << "\t" << (*kt)->get_title() << std::endl;
		}
		
		std::cout << "all: " << std::endl;
		for (auto kt = r.begin(); kt != r.end(); ++kt)
		{
			std::cout << "\t" << (*kt)->get_date() << "\t" << (*kt)->get_title() << std::endl;
		}
		
		if (jt != r.end())
		{
			std::cout << (*it)->get_name() << std::endl;
			for (; jt != r.end(); ++jt)
			{
				std::cout << "\t" << (*jt)->get_date() << "\t" << (*jt)->get_title() << std::endl;
			}
		}
	}
}
