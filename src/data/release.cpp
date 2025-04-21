#include <data/release.h>

#include <boost/locale.hpp>

std::locale release::loc = boost::locale::generator()("en_US.UTF-8");

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
		return std::use_facet<boost::locale::collator<char>>(release::loc).compare(boost::locale::collate_level::primary, lhs.get_title(), rhs.get_title()) < 0;
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

release_similar_comparator::release_similar_comparator (const release_ptr_t& release)
	: release(release)
{
}

bool release_similar_comparator::operator() (const release_ptr_t& similar)
{
	if (release == nullptr || similar == nullptr)
	{
		return false;
	}

	std::string similar_year = similar->get_date().get().substr(0, 4);
	if (release->get_date().get().find(similar_year) == 0)
	{
		return std::use_facet<boost::locale::collator<char>>(release::loc).compare(boost::locale::collate_level::primary, release->get_title(), similar->get_title()) == 0;
	}

	return false;
}
