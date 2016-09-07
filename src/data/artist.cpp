#include <data/artist.h>
#include <data/releasefactory.h>

artist::artist (const std::string& id, const std::string& name)
	: id(id)
	, name(name)
	, releases()
	, local_releases()
{
}

artist::artist (TagLib::Tag* tag)
	: id()
	, name()
	, releases()
	, local_releases()
{
	if (tag)
	{
		this->name = tag->artist().toCString();
		this->local_releases.insert(releasefactory::get(tag));
	}
}

artist::artist (MusicBrainz5::CArtist* a)
	: id()
	, name()
	, releases()
	, local_releases()
{
	if (a)
	{
		this->id = a->ID();
		this->name = a->Name();
	}
}

void artist::add_release (const release_ptr_t& release)
{
	if (release)
	{
		this->releases.insert(release);
	}
}

void artist::add_local_release (const release_ptr_t& release)
{
	if (release)
	{
		this->local_releases.insert(release);
	}
}

void artist::clear_releases ()
{
	this->releases.clear();
}

void artist::set_id (const std::string& id)
{
	this->id = id;
}

bool artist::has_id () const
{
	return !this->id.empty();
}

bool artist::has_releases () const
{
	return !this->releases.empty();
}

bool artist::has_local_releases () const
{
	return !this->local_releases.empty();
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

const release_set_t& artist::get_local_releases () const
{
	return this->local_releases;
}
