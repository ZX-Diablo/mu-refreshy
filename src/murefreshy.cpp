#include <iostream>

#include <boost/filesystem.hpp>
#include <taglib/fileref.h>

int main (int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: mu-refreshy <path>" << std::endl;
		return -1;
	}
	
	std::string root_str = argv[1];
	boost::filesystem::path root(root_str);
	
	try
	{
		if (boost::filesystem::exists(root) && boost::filesystem::is_directory(root))
		{
			std::cout << "Start scanning " << root << " ..." << std::endl;
			std::for_each(
				boost::filesystem::directory_iterator(root),
				boost::filesystem::directory_iterator(),
				[](const boost::filesystem::path& p)
			{
				if (boost::filesystem::is_directory(p))
				{
					std::cout << "Subdirectory " << p << std::endl;
					std::for_each(
						boost::filesystem::directory_iterator(p),
						boost::filesystem::directory_iterator(),
						[](const boost::filesystem::path& f)
					{
						if (boost::filesystem::is_regular_file(f) && f.extension() == ".mp3")
						{
							TagLib::FileRef file(f.c_str());
							TagLib::Tag* tag = file.tag();
							
							std::cout << tag->artist() << " - " << tag->year() << " - " << tag->album() << std::endl;
						}
					});
				}
			});
		}
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		std::cerr << "Boost filesystem error: " << e.what() << std::endl;
		return -1;
	}
	
	return 0;
}
