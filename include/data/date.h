#pragma once

#include <string>
#include <ostream>

class date
{
public:
	static const std::string default_date;

public:
	date (const std::string& d = std::string());
	date (const date& other);
	date (date&& other);

	date& operator= (const date& other);
	date& operator= (date&& other);

	const std::string& get () const;

private:
	std::string d;
};

bool operator< (const date& lhs, const date& rhs);
std::ostream& operator<< (std::ostream& out, const date& d);
