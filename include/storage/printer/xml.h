#pragma once

#include <storage/printer/iprinter.h>

#include <pugixml.hpp>

class xml : public iprinter
{
public:
	virtual ~xml () = default;
	virtual void print (const storage& s, std::ostream& out) const override;

private:
	void print_release (pugi::xml_node& xml_release, const release_ptr_t& release) const;
};
