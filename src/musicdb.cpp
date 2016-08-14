#include "../include/musicdb.h"

#include <musicbrainz5/Artist.h>
#include <musicbrainz5/ArtistCredit.h>
#include <musicbrainz5/NameCredit.h>
#include <musicbrainz5/NameCreditList.h>
#include <musicbrainz5/ReleaseGroup.h>
#include <musicbrainz5/ReleaseGroupList.h>

musicdb::musicdb (const std::string& user_agent)
	: query(user_agent)
{
}

musicdb::~musicdb ()
{
}

void musicdb::fill (const artist_ptr_t& artist)
{
	if (artist && artist->has_local_releases())
	{
		MusicBrainz5::CMetadata data = this->query.Query("release-group", "", "",
			{ {"query", "artist:\"" + artist->get_name() + "\" AND releasegroup:\""
				+ (*artist->get_local_releases().begin())->get_title() + "\""} });
		MusicBrainz5::CReleaseGroupList* releases = data.ReleaseGroupList();
		
		if (releases == nullptr || releases->NumItems() == 0)
		{
			return;
		}
		
		MusicBrainz5::CReleaseGroup* rg = releases->Item(0);
		MusicBrainz5::CArtistCredit* artist_credit = rg->ArtistCredit();
		
		if (artist_credit == nullptr || artist_credit->NameCreditList() == nullptr || artist_credit->NameCreditList()->NumItems() == 0)
		{
			return;
		}
		
		MusicBrainz5::CNameCredit* name_credit = artist_credit->NameCreditList()->Item(0);
		
		if (name_credit == nullptr)
		{
			return;
		}
		
		MusicBrainz5::CArtist* a = name_credit->Artist();
		
		if (a == nullptr)
		{
			return;
		}
		
		artist->set_id(a->ID());	
		
		MusicBrainz5::CMetadata releases_data = this->query.Query("release-group", "", "", { {"artist", a->ID()} });
		releases = releases_data.ReleaseGroupList();
		
		if (releases == nullptr)
		{
			return;
		}
		
		artist->clear_releases();
		for (unsigned int i = 0; i < static_cast<unsigned int>(releases->NumItems()); i++)
		{
			rg = releases->Item(i);
			artist->add_release(std::make_shared<release>(rg));
		}
	}
}
