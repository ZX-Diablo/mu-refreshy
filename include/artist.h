#pragma once

#include "release.h"

#include <memory>

#include <taglib/tag.h>
#include <musicbrainz5/Artist.h>

class artist
{
public:
	artist (const std::string& id, const std::string& name);
	artist (TagLib::Tag* tag);
	artist (MusicBrainz5::CArtist* a);
	~artist ();
	
	void add_release (const release_ptr_t& release);
	void clear_releases ();
	
	void set_id (const std::string& id);
	
	bool has_releases () const;
	
	const std::string& get_id () const;
	const std::string& get_name () const;
	const release_set_t& get_releases () const;
	
private:
	std::string id;
	std::string name;
	release_set_t releases;
};

typedef std::shared_ptr<artist> artist_ptr_t;
