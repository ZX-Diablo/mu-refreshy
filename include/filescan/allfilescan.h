#pragma once

#include <filescan/ifilescan.h>

class allfilescan : public ifilescan
{
public:
	allfilescan () = default;
	~allfilescan () = default;

	virtual ifilescan::path_list_t scan (const path_t& root) override;

private:
	void scan (const path_t& root, path_list_t& result);
};
