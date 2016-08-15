#pragma once

#include <filescan/ifilescan.h>

class artistfilescan : public ifilescan
{
public:
	artistfilescan () = default;
	~artistfilescan () = default;
	
	virtual ifilescan::path_list_t scan (const path_t& root) override;
};
