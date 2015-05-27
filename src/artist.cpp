#include "../include/artist.h"

artist::artist (const std::string& id, const std::string& name)
	: id(id)
	, name(name)
	, releases()
{
}

artist::artist (MusicBrainz5::CArtist* a)
	: id()
	, name()
	, releases()
{
	if (a)
	{
		this->id = a->ID();
		this->name = a->Name();
	}
}

artist::~artist ()
{
}

void artist::add_release (const release_ptr_t& release)
{
	this->releases.insert(release);
}

const std::string& artist::get_id () const
{
	return this->id;
}

const std::string& artist::get_name () const
{
	return this->name;
}
