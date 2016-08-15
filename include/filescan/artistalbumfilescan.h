#pragma once

#include <filescan/ifilescan.h>

class artistalbumfilescan : public ifilescan
{
public:
	artistalbumfilescan () = default;
	~artistalbumfilescan () = default;
	
	virtual ifilescan::path_list_t scan (const path_t& root) override;
};
