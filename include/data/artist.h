#pragma once

#include <data/release.h>

#include <memory>
#include <list>
#include <set>

class artist
{
public:
	typedef std::set<std::string> id_set_t;

public:
	explicit artist (const std::string& name);
	artist (const std::string& id, const std::string& name);
	artist (const release_set_t& releases, const release_set_t& local_releases);

	void add_release (const release_ptr_t& release);
	void add_local_release (const release_ptr_t& release);
	void clear_releases ();

	void add_id (const std::string& id, bool default_ = true);

	bool has_id () const;
	bool has_releases () const;
	bool has_local_releases () const;

	const std::string& get_id () const;
	const std::string& get_name () const;
	const id_set_t& get_ids () const;
	const release_set_t& get_releases () const;
	const release_set_t& get_local_releases () const;

private:
	std::string default_id;
	id_set_t ids;
	std::string name;

	release_set_t releases;
	release_set_t local_releases;
};

typedef std::shared_ptr<artist> artist_ptr_t;
typedef std::list<artist_ptr_t> artist_list_t;
