#pragma once

#include "ifilescan.h"

class artistfilescan : public ifilescan
{
public:
	artistfilescan ();
	~artistfilescan ();
	
	virtual ifilescan::path_list_t scan (const path_t& root);
};
