#include <atomic>
#include <fstream>
#include <iostream>

#include <boost/program_options.hpp>
#include <taglib/fileref.h>

#include <data/artistfactory.h>
#include <filescan/filescanfactory.h>
#include <storage/musicdb.h>
#include <storage/printer/printerfactory.h>
#include <storage/reader/xml.h>
#include <storage/remote/musicbrainz.h>
#include <storage/storage.h>
#include <thread/pool.h>

int main (int argc, char** argv)
{
	boost::program_options::positional_options_description pos_flag;
	pos_flag.add("root", 1);

	boost::program_options::options_description flags("Allowed options");

	flags.add_options()
		("help,h", "Show this help")
		("root,r", boost::program_options::value<std::string>()->required(), "Root directory")
		("scan,s", boost::program_options::value<std::string>()->default_value("all"), "Directory scan method (all|artist|album)")
		("file,i", boost::program_options::value<std::string>()->default_value(std::string()), "Input xml file")
		("format,f", boost::program_options::value<std::string>()->default_value("txt"), "Output format (txt|xml)")
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
		std::cerr << e.what() << std::endl;
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

	storage db;
	std::string input_file = options["file"].as<std::string>();

	if (!input_file.empty())
	{
		std::ifstream in(input_file);
		reader::xml reader;

		reader.read(db, in);
	}

	std::cerr << "Start scanning " << root << "..." << std::endl;

	auto files = fs->scan(root);

	std::cerr << "Total " << files.size() << " files" << std::endl;

	musicdb mb(std::make_shared<musicbrainz>("mu-refreshy/0.5.1 (https://github.com/ZX-Diablo/mu-refreshy)"));
	pool tp(options["thread"].as<unsigned int>());
	std::atomic_int counter(0);

	for (auto& it : files)
	{
		tp.add_task([&mb, &db, &counter, it]()
		{
			TagLib::FileRef file(it.c_str());
			TagLib::Tag* tag = file.tag();
			artist_ptr_t a = artistfactory::get(tag);
			bool need_update = false;

			if (!db.add(a))
			{
				auto main = db.get_by_name(a->get_name());

				main->add_local_release(*a->get_local_releases().begin());
				a = main;
				need_update = true;
			}

			if (!a->has_releases())
			{
				mb.fill(a);
				need_update = a->has_releases();
			}

			if (need_update)
			{
				db.replace(a);
			}

			counter++;
			std::cerr << "\rDone: " << counter;
		});
	}

	std::cerr << "WAITING" << std::endl;
	tp.wait();

	std::cerr << std::endl << "PRINTING" << std::endl;

	auto printer = printer::printerfactory::get(options["format"].as<std::string>());

	if (printer == nullptr)
	{
		std::cerr << "Invalid format option" << std::endl << flags;

		printer = printer::printerfactory::get("txt");
		printer->print(db, std::cout);

		return -1;
	}

	printer->print(db, std::cout);

	return 0;
}
