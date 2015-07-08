#include <iostream>
#include <atomic>

#include <boost/program_options.hpp>

#include <taglib/fileref.h>

#include "../include/filescanfactory.h"
#include "../include/musicdb.h"
#include "../include/pool.h"
#include "../include/storage.h"
#include "../include/artist.h"

int main (int argc, char** argv)
{
	boost::program_options::positional_options_description pos_flag;
	pos_flag.add("root", 1);
	
	boost::program_options::options_description flags("Allowed options");
	
	flags.add_options()
		("help,h", "Show this help")
		("root,r", boost::program_options::value<std::string>()->required(), "Root directory")
		("scan,s", boost::program_options::value<std::string>()->default_value("all"), "Directory scan method (all|artist|album)")
		("thread,t", boost::program_options::value<unsigned int>()->default_value(8), "Amount of threads")
	;
	
	boost::program_options::command_line_parser parser(argc, argv);
	boost::program_options::variables_map options;
	
	parser.options(flags);
	parser.positional(pos_flag);
	
	try
	{
		boost::program_options::store(parser.run(), options);
	}
	catch (boost::program_options::error& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
	
	if (options.count("root") == 0)
	{
		std::cerr << "Must specify root directory" << std::endl << flags;
		return -1;
	}
	
	ifilescan::path_t root(options["root"].as<std::string>());
	auto fs = filescanfactory::get(options["scan"].as<std::string>());
	
	if (fs == nullptr)
	{
		std::cerr << "Invalid scan option" << std::endl << flags;
		return -1;
	}

	std::cout << "Start scanning " << root << "..." << std::endl;
	
	auto files = fs->scan(root);
	
	std::cout << "Total " << files.size() << " files" << std::endl;

	musicdb mb("mu-refreshy-0.0.1");
	storage db;
	pool tp(options["thread"].as<unsigned int>());
	std::atomic_int counter(0);
	
	for (auto& it : files)
	{
		tp.add_task([&mb, &db, &counter, it]()
		{
			TagLib::FileRef file(it.c_str());
			TagLib::Tag* tag = file.tag();
			
			artist_ptr_t a = std::make_shared<artist>(tag);
			if (db.add(a))
			{
				mb.fill(a);
				db.replace(a);
			}
			else
			{
				auto main = db.get_by_name(a->get_name());
				main->add_local_release(*a->get_local_releases().begin());
				db.replace(main);
			}
			
			counter++;
			std::cout << "\rDone: " << counter;
		});
	}

	std::cout << "WAITING" << std::endl;
	tp.wait();
		
	std::cout << std::endl << "PRINTING" << std::endl;
	db.print_all();
	
	return 0;
}
