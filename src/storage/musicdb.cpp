#include <storage/musicdb.h>

#include <data/releasefactory.h>

#include <musicbrainz5/Artist.h>
#include <musicbrainz5/ArtistCredit.h>
#include <musicbrainz5/NameCredit.h>
#include <musicbrainz5/NameCreditList.h>
#include <musicbrainz5/ReleaseGroup.h>
#include <musicbrainz5/ReleaseGroupList.h>

musicdb::musicdb (const iremote_t& remote)
	: remote(remote)
{
}

musicdb::~musicdb ()
{
}

void musicdb::fill (const artist_ptr_t& artist)
{
	if (this->remote && artist && artist->has_local_releases())
	{
		std::string artist_name = artist->get_name();
		artist_list_t artists;

		for (const auto& it : artist->get_local_releases())
		{
			artists = this->remote->search_artists(artist_name, it->get_title());
			if (!artists.empty())
			{
				break;
			}
		}

		if (artists.empty())
		{
			return;
		}

		for (const auto& it : artists)
		{
			artist->add_id(it->get_id(), false); // the first ID would be default, still no ambiguity mechanism
		}

		release_set_t releases = this->remote->search_releases(artist->get_id());

		if (releases.empty())
		{
			return;
		}

		artist->clear_releases();

		for (const auto& it : releases)
		{
			artist->add_release(it);
		}
	}
}
