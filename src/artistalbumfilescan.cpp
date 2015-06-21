#include "../include/artistalbumfilescan.h"

artistalbumfilescan::artistalbumfilescan ()
{
}

artistalbumfilescan::~artistalbumfilescan ()
{
}

ifilescan::path_list_t artistalbumfilescan::scan (const path_t& root)
{
	path_list_t result;

	if (boost::filesystem::exists(root) && boost::filesystem::is_directory(root))
	{
		std::for_each(dit_t(root), dit_t(), [this, &result](const path_t& p)
		{
			if (boost::filesystem::is_directory(p))
			{
				std::for_each(dit_t(p), dit_t(), [this, &result](const path_t& p2)
				{
					if (boost::filesystem::is_directory(p2))
					{
						auto it = std::find_if(dit_t(p2), dit_t(), [](const path_t& f)
						{
							return boost::filesystem::is_regular_file(f) && f.extension() == ".mp3";
						});
						
						if (it != dit_t())
						{
							result.push_back(*it);
						}
					}
				});
			}
		});
	}
	
	return result;
}
