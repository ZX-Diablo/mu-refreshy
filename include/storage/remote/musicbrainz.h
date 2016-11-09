#pragma once

#include <storage/remote/iremote.h>

#include <musicbrainz5/Query.h>

class musicbrainz : public iremote
{
public:
	musicbrainz (const std::string& user_agent);
	virtual ~musicbrainz () = default;

	virtual artist_list_t search_artists (const std::string& artist, const std::string& release) const override;
	virtual release_set_t search_releases (const std::string& artist_id) const override;

private:
	mutable MusicBrainz5::CQuery query;
};
