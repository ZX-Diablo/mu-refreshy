#pragma once

#include <boost/filesystem.hpp>

#include <list>

class ifilescan
{
public:
	typedef boost::filesystem::path path_t;
	typedef std::list<path_t> path_list_t;

public:
	virtual ~ifilescan () = default;

	virtual path_list_t scan (const path_t& root) = 0;

protected:
	typedef boost::filesystem::directory_iterator dit_t;
};
