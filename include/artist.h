#pragma once

#include "release.h"

#include <memory>

#include <musicbrainz5/Artist.h>

class artist
{
public:
	artist (const std::string& name);
	artist (MusicBrainz5::CArtist* a);
	~artist ();
	
	void add_release (const release_ptr_t& release);
	
	const std::string& get_id () const;
	const std::string& get_name () const;
	
private:
	std::string id;
	std::string name;
	release_set_t releases;
};

typedef std::shared_ptr<artist> artist_ptr_t;
