#pragma once

#include <data/artist.h>
#include <storage/remote/iremote.h>

class musicdb
{
public:
	musicdb (const iremote_t& remote);
	~musicdb ();

	void fill (const artist_ptr_t& artist);

private:
	iremote_t remote;
};
