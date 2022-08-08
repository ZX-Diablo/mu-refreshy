#include <filescan/allfilescan.h>

#include <algorithm>

ifilescan::path_list_t allfilescan::scan (const path_t& root)
{
	path_list_t result;

	if (boost::filesystem::exists(root) && boost::filesystem::is_directory(root))
	{
		this->scan(root, result);
	}

	return result;
}

void allfilescan::scan (const path_t& root, path_list_t& result)
{
	std::for_each(dit_t(root), dit_t(), [this, &result](const path_t& p)
	{
		if (boost::filesystem::is_directory(p))
		{
			this->scan(p, result);
		}
		else if (boost::filesystem::is_regular_file(p) && p.extension() == ".mp3")
		{
			result.push_back(p);
		}
	});
}
