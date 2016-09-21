#pragma once

#include <storage/remote/imusicbrainz.h>

#include <musicbrainz5/Query.h>

class musicbrainz : public imusicbrainz
{
public:
	musicbrainz (const std::string& user_agent);
	virtual ~musicbrainz () = default;

	virtual artist_list_t search (const std::string& artist, const std::string& release) const override;
	virtual void fill_releases (const artist_ptr_t& artist) const override;

private:
	mutable MusicBrainz5::CQuery query;
};
