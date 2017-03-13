#include <storage/storage.h>

#include <iostream>

storage::storage (const artist_ptr_t& artist)
	: s()
	, m()
{
	if (artist)
	{
		this->s.insert(artist);
	}
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
	if (artist)
	{
		lock_t lock(this->m);

		auto& index = this->s.get<name_tag_t>();
		auto it = index.find(artist->get_name());

		if (it != index.end())
		{
			index.replace(it, artist);
			return true;
		}
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

storage::const_iterator storage::begin () const
{
	auto& index = this->s.get<name_tag_t>();
	return index.begin();
}

storage::const_iterator storage::end () const
{
	auto& index = this->s.get<name_tag_t>();
	return index.end();
}
