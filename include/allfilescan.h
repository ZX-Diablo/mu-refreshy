#pragma once

#include "ifilescan.h"

class allfilescan : public ifilescan
{
public:
	allfilescan ();
	~allfilescan ();
	
	virtual ifilescan::path_list_t scan (const path_t& root);
	
private:
	void scan (const path_t& root, path_list_t& result);	
};
