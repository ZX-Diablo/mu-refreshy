#pragma once

#include <string>
#include <chrono>

class date
{
public:
	typedef std::chrono::system_clock::time_point datetime_t;
	
public:
	date ();
	date (const std::string& d);
	date (const date& other);
	date (date&& other);
	~date ();
	
	date& operator= (const date& other);
	date& operator= (date&& other);
	
	const datetime_t& get () const;
	
private:
	datetime_t datetime;
};

bool operator< (const date& lhs, const date& rhs);
