#pragma once

#include <data/date.h>

#include <string>
#include <locale>
#include <ostream>
#include <memory>
#include <set>

class release
{
public:
	static std::locale loc;

public:
	release (const std::string& id, const std::string& title, const std::string& type, const date& d);

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

bool operator< (const release& lhs, const release& rhs);
std::ostream& operator<< (std::ostream& out, const release& r);

typedef std::shared_ptr<release> release_ptr_t;

struct release_comparator
{
	bool operator() (const release_ptr_t& lhs, const release_ptr_t& rhs);
};

typedef std::set<release_ptr_t, release_comparator> release_set_t;

struct release_similar_comparator
{
	explicit release_similar_comparator (const release_ptr_t& release);
	bool operator() (const release_ptr_t& similar);
private:
	release_ptr_t release;
};
