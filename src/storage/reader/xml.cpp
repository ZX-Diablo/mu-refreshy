#include <storage/reader/xml.h>

namespace reader
{

void xml::read (storage& s, std::istream& in) const
{
	pugi::xml_document doc;
	auto result = doc.load(in);

	if (!result)
	{
		return;
	}

	pugi::xml_node xml_artists = doc.child("storage").child("artists");

	for (const auto& xml_artist : xml_artists.children("artist"))
	{
		std::string name = xml_artist.attribute("name").value();
		std::string default_id = xml_artist.attribute("id").value();
		auto a = s.get_by_id(default_id);

		if (!a)
		{
			a = std::make_shared<artist>(default_id, name);
		}

		pugi::xml_node xml_ids = xml_artist.child("ids");

		for (const auto& xml_id : xml_ids.children("id"))
		{
			std::string id = xml_id.child_value();

			a->add_id(id, id == default_id);
		}

		pugi::xml_node xml_releases = xml_artist.child("releases");

		for (const auto& xml_release : xml_releases.children("release"))
		{
			std::string id = xml_release.child_value("id");
			std::string title = xml_release.child_value("title");
			std::string type = xml_release.child_value("type");
			std::string d = xml_release.child_value("date");
			auto r = std::make_shared<release>(id, title, type, date(d));

			// all releases are added as local despite their type
			a->add_local_release(r);
		}

		if (!s.add(a))
		{
			s.replace(a);
		}
	}
}

}
