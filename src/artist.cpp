#include "../include/artist.h"

artist::artist (const std::string& id, const std::string& name)
	: id(id)
	, name(name)
	, releases()
{
}

artist::artist (TagLib::Tag* tag)
	: id()
	, name()
	, releases()
{
	if (tag)
	{
		this->name = tag->artist().toCString();
		this->releases.insert(std::make_shared<release>(tag));
	}
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

void artist::clear_releases ()
{
	this->releases.clear();
}

void artist::set_id (const std::string& id)
{
	this->id = id;
}

bool artist::has_releases () const
{
	return this->releases.size() > 0;
}

const std::string& artist::get_id () const
{
	return this->id;
}

const std::string& artist::get_name () const
{
	return this->name;
}

const release_set_t& artist::get_releases () const
{
	return this->releases;
}
