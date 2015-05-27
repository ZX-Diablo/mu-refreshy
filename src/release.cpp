#include "../include/release.h"

release::release (const std::string& id, const std::string& title, const std::string& type, const date& d)
	: id(id)
	, title(title)
	, type(type)
	, d(d)
{
}

release::release (MusicBrainz5::CReleaseGroup* rg)
	: id()
	, title()
	, type()
	, d()
{
	if (rg)
	{
		this->id = rg->ID();
		this->title = rg->Title();
		this->type = rg->PrimaryType();
		this->d = date(rg->FirstReleaseDate());
	}
}

release::~release ()
{
}

const std::string& release::get_id () const
{
	return this->id;
}

const std::string& release::get_title () const
{
	return this->title;
}

const std::string& release::get_type () const
{
	return this->type;
}

const date& release::get_date () const
{
	return this->d;
}

bool operator== (const release& lhs, const release& rhs)
{
	return lhs.get_id() == rhs.get_id();
}

bool operator< (const release& lhs, const release& rhs)
{
	return lhs.get_date() < rhs.get_date();
}
