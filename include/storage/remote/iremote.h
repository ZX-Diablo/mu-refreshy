#pragma once

#include <data/artist.h>

class iremote
{
public:
	virtual ~iremote () = default;
	virtual artist_list_t search_artists (const std::string& artist, const std::string& release) const = 0;
	virtual release_set_t search_releases (const std::string& artist_id) const = 0;
};
