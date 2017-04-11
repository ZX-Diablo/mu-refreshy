#pragma once

#include <filescan/ifilescan.h>

#include <memory>
#include <string>

class filescanfactory
{
public:
	typedef std::shared_ptr<ifilescan> ifilescan_t;

public:
	static ifilescan_t get (const std::string& type);
};
