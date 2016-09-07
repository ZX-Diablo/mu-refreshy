#pragma once

#include <data/artist.h>

#include <taglib/tag.h>
#include <musicbrainz5/Artist.h>

class artistfactory
{
public:
	static artist_ptr_t get (const TagLib::Tag* tag);
	static artist_ptr_t get (const MusicBrainz5::CArtist* a);
};
