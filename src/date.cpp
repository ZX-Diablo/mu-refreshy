#include "../include/date.h"

#include <ctime>
#include <sstream>
#include <string.h>

date::date (unsigned int year, unsigned int month, unsigned int day)
	: datetime()
{
	struct tm timeinfo;
	memset(&timeinfo, 0, sizeof(timeinfo));
		
	timeinfo.tm_year = (year >= 1900 ? year - 1900 : 0);
	timeinfo.tm_mon = (month > 0 ? month - 1 : 0);
	timeinfo.tm_mday = day;
	
	this->datetime = std::chrono::system_clock::from_time_t(mktime(&timeinfo));
}

date::date (const std::string& d)
	: datetime()
{
	struct tm timeinfo;
	memset(&timeinfo, 0, sizeof(timeinfo));
	
	if (!d.empty())
	{
		std::string::size_type pos = d.find("-");
		std::string year = d.substr(0, pos);
		
		timeinfo.tm_year = atoi(year.c_str()) - 1900;
		
		if (pos != std::string::npos)
		{
			pos++;
			std::string::size_type end_pos = d.find("-", pos);
			std::string month = d.substr(pos, end_pos - pos);
			
			timeinfo.tm_mon = atoi(month.c_str()) - 1;
			
			if (end_pos != std::string::npos)
			{
				std::string day = d.substr(end_pos + 1);
				
				timeinfo.tm_mday = atoi(day.c_str());
			}
			else
			{
				timeinfo.tm_mday = 1;
			}
		}
		else
		{
			timeinfo.tm_mon = 0;
			timeinfo.tm_mday = 1;
		}

		this->datetime = std::chrono::system_clock::from_time_t(mktime(&timeinfo));
	}
}

date::date (const date& other)
	: datetime(other.datetime)
{
}

date::date(date&& other)
	: datetime(std::move(other.datetime))
{
}

date::~date ()
{
}

date& date::operator= (const date& other)
{
	if (this != &other)
	{
		this->datetime = other.datetime;
	}
	
	return *this;
}

date& date::operator= (date&& other)
{
	if (this != &other)
	{
		this->datetime = std::move(other.datetime);
	}
	
	return *this;
}

std::string date::to_string () const
{
	std::time_t t = std::chrono::system_clock::to_time_t(this->datetime);
	struct tm* timeinfo = localtime(&t);
	std::stringstream ss;
	
	ss << (timeinfo->tm_year + 1900) << "-" << (timeinfo->tm_mon + 1) << "-" << timeinfo->tm_mday;
	
	return ss.str();
}

const date::datetime_t& date::get () const
{
	return this->datetime;
}

bool operator< (const date& lhs, const date& rhs)
{
	return lhs.get() < rhs.get();
}

std::ostream& operator<< (std::ostream& out, const date& d)
{
	return out << d.to_string();
}
