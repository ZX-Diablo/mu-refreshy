#pragma once

#include <data/artist.h>

#include <string>

#include <musicbrainz5/Query.h>

class musicdb
{
public:
	musicdb (const std::string& user_agent);
	~musicdb ();
	
	void fill (const artist_ptr_t& artist);
	
private:
	MusicBrainz5::CQuery query;
};
