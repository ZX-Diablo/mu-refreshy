#pragma once

#include "date.h"

#include <string>
#include <memory>
#include <set>

#include <musicbrainz5/ReleaseGroup.h>

class release
{
public:
	release (const std::string& id, const std::string& title, const std::string& type, const date& d);
	release (MusicBrainz5::CReleaseGroup* rg);
	~release ();
	
	const std::string& get_id () const;
	const std::string& get_title () const;
	const std::string& get_type () const;
	const date& get_date () const;
	
private:
	std::string id;
	std::string title;
	std::string type;
	date d;
};

bool operator== (const release& lhs, const release& rhs);
bool operator< (const release& lhs, const release& rhs);

typedef std::shared_ptr<release> release_ptr_t;
typedef std::set<release_ptr_t> release_set_t;
