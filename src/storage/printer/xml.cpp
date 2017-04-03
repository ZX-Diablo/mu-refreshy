#include <storage/printer/xml.h>

#include <pugixml.hpp>

void xml::print (const storage& s, std::ostream& out) const
{
	pugi::xml_document doc;
	pugi::xml_node xml_storage = doc.append_child("storage");
	pugi::xml_node xml_artists = xml_storage.append_child("artists");

	for (auto it = s.begin(); it != s.end(); ++it)
	{
		pugi::xml_node xml_artist = xml_artists.append_child("artist");

		xml_artist.append_attribute("id").set_value((*it)->get_id().c_str());
		xml_artist.append_attribute("name").set_value((*it)->get_name().c_str());

		pugi::xml_node xml_ids = xml_artist.append_child("ids");
		const auto& ids = (*it)->get_ids();

		for (const auto& jt : ids)
		{
			pugi::xml_node xml_id = xml_ids.append_child("id");

			xml_id.append_child(pugi::node_pcdata).set_value(jt.c_str());
		}

		//pugi::xml_node xml_releases = xml_artist.append_child("releases");
		//auto r = (*it)->get_releases();
		//auto lr = (*it)->get_local_releases();

		
	}

	doc.save(out);
}
