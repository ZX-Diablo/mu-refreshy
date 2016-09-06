#pragma once

#include <data/release.h>

#include <taglib/tag.h>
#include <musicbrainz5/ReleaseGroup.h>

class releasefactory
{
public:
	static release_ptr_t get (const TagLib::Tag* tag);
	static release_ptr_t get (const MusicBrainz5::CReleaseGroup* rg);
};
