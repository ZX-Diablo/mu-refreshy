#pragma once

#include <storage/printer/iprinter.h>

class text : public iprinter
{
public:
	virtual ~text () = default;
	virtual void print (const storage& s, std::ostream& out) const override;
};
