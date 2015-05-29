#include "../include/storage.h"

storage::storage ()
	: s()
{
}

storage::~storage ()
{
}

void storage::add (const artist_ptr_t& artist)
{
	this->s.insert(artist);
}

bool storage::name_exists (const std::string& name) const
{
	auto& index = this->s.get<name_tag_t>();
	return index.find(name) != index.end();
}

bool storage::id_exists (const std::string& id) const
{
	auto& index = this->s.get<id_tag_t>();
	return index.find(id) != index.end();
}

artist_ptr_t storage::get_by_name (const std::string& name) const
{
	auto& index = this->s.get<name_tag_t>();
	auto it = index.find(name);
	return (it != index.end() ? (*it) : nullptr);
}

artist_ptr_t storage::get_by_id (const std::string& id) const
{
	auto& index = this->s.get<id_tag_t>();
	auto it = index.find(id);
	return (it != index.end() ? (*it) : nullptr);
}
