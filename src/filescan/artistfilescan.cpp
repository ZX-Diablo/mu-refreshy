#include <filescan/artistfilescan.h>

#include <algorithm>

ifilescan::path_list_t artistfilescan::scan (const path_t& root)
{
	path_list_t result;

	if (boost::filesystem::exists(root) && boost::filesystem::is_directory(root))
	{
		std::for_each(dit_t(root), dit_t(), [this, &result](const path_t& p)
		{
			if (boost::filesystem::is_directory(p))
			{
				std::for_each(dit_t(p), dit_t(), [this, &result](const path_t& f)
				{
					if (boost::filesystem::is_regular_file(f) && f.extension() == ".mp3")
					{
						result.push_back(f);
					}
				});
			}
		});
	}

	return result;
}
