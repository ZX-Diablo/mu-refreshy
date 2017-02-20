#include <data/artist.h>
#include <data/releasefactory.h>

artist::artist (const std::string& name)
	: default_id()
	, ids()
	, name(name)
	, releases()
	, local_releases()
{
}

artist::artist (const std::string& id, const std::string& name)
	: default_id(id)
	, ids({ id })
	, name(name)
	, releases()
	, local_releases()
{
}

artist::artist (const release_set_t& releases, const release_set_t& local_releases)
	: default_id()
	, ids()
	, name()
	, releases(releases)
	, local_releases(local_releases)
{
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

void artist::add_id (const std::string& id, bool default_)
{
	this->ids.insert(id);

	if (this->default_id.empty() || default_)
	{
		this->default_id = id;
	}
}

bool artist::has_id () const
{
	return !this->default_id.empty();
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
	return this->default_id;
}

const std::string& artist::get_name () const
{
	return this->name;
}

const artist::id_set_t& artist::get_ids () const
{
	return this->ids;
}

const release_set_t& artist::get_releases () const
{
	return this->releases;
}

const release_set_t& artist::get_local_releases () const
{
	return this->local_releases;
}
