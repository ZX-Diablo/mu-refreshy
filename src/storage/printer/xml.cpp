#include <storage/printer/xml.h>

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

		pugi::xml_node xml_releases = xml_artist.append_child("releases");
		auto r = (*it)->get_releases();
		auto lr = (*it)->get_local_releases();

		for (const auto& jt : lr)
		{
			pugi::xml_node xml_release = xml_releases.append_child("release");

			xml_release.append_attribute("type").set_value("local");
			this->print_release(xml_release, jt);
		}

		auto jt = (!lr.empty() ? r.upper_bound(*lr.rbegin()) : r.begin());

		for (; jt != r.end(); ++jt)
		{
			pugi::xml_node xml_release = xml_releases.append_child("release");

			xml_release.append_attribute("type").set_value("remote");
			this->print_release(xml_release, *jt);
		}
	}

	doc.save(out);
}

void xml::print_release (pugi::xml_node& xml_release, const release_ptr_t& release) const
{
	xml_release.append_child("id").append_child(pugi::node_pcdata).set_value(release->get_id().c_str());
	xml_release.append_child("title").append_child(pugi::node_pcdata).set_value(release->get_title().c_str());
	xml_release.append_child("type").append_child(pugi::node_pcdata).set_value(release->get_type().c_str());
	xml_release.append_child("date").append_child(pugi::node_pcdata).set_value(release->get_date().get().c_str());
}
