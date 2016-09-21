#pragma once

#include <data/artist.h>

class imusicbrainz
{
public:
	virtual ~imusicbrainz () = default;
	virtual artist_list_t search (const std::string& artist, const std::string& release) const = 0;
	virtual void fill_releases (const artist_ptr_t& artist) const = 0;
};
