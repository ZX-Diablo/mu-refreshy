#pragma once

#include <storage/printer/iprinter.h>

class xml : public iprinter
{
public:
	virtual ~xml () = default;
	virtual void print (const storage& s, std::ostream& out) const override;
};
