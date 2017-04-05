#pragma once

#include <storage/storage.h>

#include <ostream>

class iprinter
{
public:
	virtual ~iprinter () = default;
	virtual void print (const storage& s, std::ostream& out) const = 0;
};
