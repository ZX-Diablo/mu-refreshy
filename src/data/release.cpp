#include <data/release.h>

release::release (const std::string& id, const std::string& title, const std::string& type, const date& d)
	: id(id)
	, title(title)
	, type(type)
	, d(d)
{
}

release::release (TagLib::Tag* tag)
	: id()
	, title()
	, type()
	, d()
{
	if (tag)
	{
		this->title = tag->album().toCString();
		this->d = date(std::to_string(tag->year()));
	}
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

bool operator< (const release& lhs, const release& rhs)
{
	if (!lhs.get_id().empty() && !rhs.get_id().empty() && lhs.get_id() == rhs.get_id())
	{
		return false;
	}
	
	return lhs.get_date() < rhs.get_date();
}

bool release_comparator::operator() (const release_ptr_t& lhs, const release_ptr_t& rhs)
{
	if (lhs == nullptr || rhs == nullptr)
	{
		return false;
	}
	
	return *lhs < *rhs;
}
