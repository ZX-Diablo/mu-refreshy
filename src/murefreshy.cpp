#include <iostream>

#include <boost/filesystem.hpp>

#include <taglib/fileref.h>
#include <musicbrainz5/Query.h>
#include <musicbrainz5/Artist.h>

#include "../include/pool.h"
#include "../include/storage.h"
#include "../include/artist.h"

typedef boost::filesystem::path path_t;
typedef boost::filesystem::directory_iterator dit_t;

int main (int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: mu-refreshy <path>" << std::endl;
		return -1;
	}
	
	std::string root_str = argv[1];
	path_t root(root_str);
	
	MusicBrainz5::CQuery mb("mu-refreshy-0.0.1");
	storage db;
	pool tp(20);
	
	try
	{
		if (boost::filesystem::exists(root) && boost::filesystem::is_directory(root))
		{
			std::cout << "Start scanning " << root << " ..." << std::endl;
			std::for_each(dit_t(root), dit_t(), [&mb, &db, &tp](const path_t& p)
			{
				if (boost::filesystem::is_directory(p))
				{
					std::for_each(dit_t(p), dit_t(), [&mb, &db, &tp](const path_t& f)
					{
						if (boost::filesystem::is_regular_file(f) && f.extension() == ".mp3")
						{
							tp.add_task([&mb, &db, f]()
							{
								TagLib::FileRef file(f.c_str());
								TagLib::Tag* tag = file.tag();
								
								artist_ptr_t a = std::make_shared<artist>(tag->artist().toCString());
								if (db.add(a))
								{
									MusicBrainz5::CMetadata data = mb.Query("artist", "", "",
										{ {"query", "artist:\"" + a->get_name() + "\" AND type:group"} });
									MusicBrainz5::CArtistList* list = data.ArtistList();
									for (int i = 0; i < list->NumItems(); i++)
									{
										MusicBrainz5::CArtist* art = list->Item(i);
										std::cout << art->Name() << std::endl;
									}
								}
							});
						}
					});
				}
			});
			
			std::cout << "WAITING" << std::endl;
			tp.wait();
			
			std::cout << "PRINTING" << std::endl;
			db.print_all();
		}
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		std::cerr << "Boost filesystem error: " << e.what() << std::endl;
		return -1;
	}
	
	return 0;
}
