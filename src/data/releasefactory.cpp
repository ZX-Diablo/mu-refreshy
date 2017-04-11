#include <data/releasefactory.h>

release_ptr_t releasefactory::get (const TagLib::Tag* tag)
{
	return tag != nullptr
	       ? std::make_shared<release>(
	               std::string()
	               , tag->album().toCString()
	               , std::string()
	               , date(std::to_string(tag->year())))
	       : nullptr;
}

release_ptr_t releasefactory::get (const MusicBrainz5::CReleaseGroup* rg)
{
	return rg != nullptr
	       ? std::make_shared<release>(
	               rg->ID()
	               , rg->Title()
	               , rg->PrimaryType()
	               , date(rg->FirstReleaseDate()))
	       : nullptr;
}
