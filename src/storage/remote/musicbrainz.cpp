#include <storage/remote/musicbrainz.h>
#include <data/artistfactory.h>

#include <musicbrainz5/Artist.h>
#include <musicbrainz5/ArtistCredit.h>
#include <musicbrainz5/NameCredit.h>
#include <musicbrainz5/NameCreditList.h>
#include <musicbrainz5/ReleaseGroup.h>
#include <musicbrainz5/ReleaseGroupList.h>

musicbrainz::musicbrainz (const std::string& user_agent)
	: query(user_agent)
{
}

artist_list_t musicbrainz::search (const std::string& artist, const std::string& release) const
{
	artist_list_t result;
	MusicBrainz5::CMetadata data = this->query.Query("release-group", "", "",
		{ {"query", "artist:\"" + artist + "\" AND releasegroup:\"" + release + "\""} }); // No way to search for exact name match?
	MusicBrainz5::CReleaseGroupList* releases = data.ReleaseGroupList();

	if (releases == nullptr || releases->NumItems() == 0)
	{
		return result;
	}

	for (int i = 0; i < releases->NumItems(); i++)
	{
		MusicBrainz5::CReleaseGroup* rg = releases->Item(i);
		MusicBrainz5::CArtistCredit* ac = rg->ArtistCredit();

		if (ac == nullptr || ac->NameCreditList() == nullptr || ac->NameCreditList()->NumItems() == 0)
		{
			continue;
		}

		MusicBrainz5::CNameCredit* nc = ac->NameCreditList()->Item(0); // Hopefully it's ok to take the first artist

		if (nc == nullptr)
		{
			continue;
		}

		MusicBrainz5::CArtist* a = nc->Artist();

		if (a == nullptr)
		{
			continue;
		}

		result.push_back(artistfactory::get(a));
	}

	return result;
}

void musicbrainz::fill_releases (const artist_ptr_t& artist) const
{
	if (artist)
	{
		// TODO
	}
}
