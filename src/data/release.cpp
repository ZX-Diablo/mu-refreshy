#include <data/release.h>

release::release (const std::string& id, const std::string& title, const std::string& type, const date& d)
	: id(id)
	, title(title)
	, type(type)
	, d(d)
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

bool operator< (const release& lhs, const release& rhs)
{
	if (!lhs.get_id().empty() && !rhs.get_id().empty() && lhs.get_id() == rhs.get_id())
	{
		return false;
	}

	if (!(lhs.get_date() < rhs.get_date()) && !(rhs.get_date() < lhs.get_date()))
	{
		return lhs.get_title() < rhs.get_title();
	}

	return lhs.get_date() < rhs.get_date();
}

std::ostream& operator<< (std::ostream& out, const release& r)
{
	return out << r.get_date() << " " << r.get_title();
}

bool release_comparator::operator() (const release_ptr_t& lhs, const release_ptr_t& rhs)
{
	if (lhs == nullptr || rhs == nullptr)
	{
		return false;
	}

	return *lhs < *rhs;
}
