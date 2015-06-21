#pragma once

#include "ifilescan.h"

class artistalbumfilescan : public ifilescan
{
public:
	artistalbumfilescan ();
	~artistalbumfilescan ();
	
	virtual ifilescan::path_list_t scan (const path_t& root);
};
