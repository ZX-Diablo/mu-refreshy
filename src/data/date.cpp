#include <data/date.h>

date::date (const std::string& d)
	: d(!d.empty() ? d : "1970-01-01")
{
	std::string::size_type pos = this->d.find("-");

	if (pos != std::string::npos)
	{
		pos = this->d.find("-", pos + 1);
		if (pos == std::string::npos)
		{
			this->d += "-01";
		}
	}
	else
	{
		this->d += "-01-01";
	}
}

date::date (const date& other)
	: d(other.d)
{
}

date::date(date&& other)
	: d(std::move(other.d))
{
}

date& date::operator= (const date& other)
{
	if (this != &other)
	{
		this->d = other.d;
	}

	return *this;
}

date& date::operator= (date&& other)
{
	if (this != &other)
	{
		this->d = std::move(other.d);
	}
	
	return *this;
}

const std::string& date::get () const
{
	return this->d;
}

bool operator< (const date& lhs, const date& rhs)
{
	return lhs.get() < rhs.get();
}

std::ostream& operator<< (std::ostream& out, const date& d)
{
	return out << d.get();
}
