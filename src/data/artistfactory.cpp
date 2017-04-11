#include <data/artistfactory.h>
#include <data/releasefactory.h>
#include <taglib/tag.h>
#include <musicbrainz5/Artist.h>

artist_ptr_t artistfactory::get (const TagLib::Tag* tag)
{
	if (tag)
	{
		release_ptr_t r = releasefactory::get(tag);
		artist_ptr_t a = std::make_shared<artist>(tag->artist().toCString());

		a->add_local_release(r);

		return a;
	}

	return nullptr;
}

artist_ptr_t artistfactory::get (const MusicBrainz5::CArtist* a)
{
	return a != nullptr
	       ? std::make_shared<artist>(a->ID(), a->Name())
	       : nullptr;
}
