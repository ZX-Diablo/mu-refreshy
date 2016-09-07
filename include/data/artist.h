#pragma once

#include <data/release.h>

#include <memory>

class artist
{
public:
	artist (const std::string& id, const std::string& name);

	void add_release (const release_ptr_t& release);
	void add_local_release (const release_ptr_t& release);
	void clear_releases ();
	
	void set_id (const std::string& id);
	
	bool has_id () const;
	bool has_releases () const;
	bool has_local_releases () const;
	
	const std::string& get_id () const;
	const std::string& get_name () const;
	const release_set_t& get_releases () const;
	const release_set_t& get_local_releases () const;
	
private:
	std::string id;
	std::string name;
	
	release_set_t releases;
	release_set_t local_releases;
};

typedef std::shared_ptr<artist> artist_ptr_t;
