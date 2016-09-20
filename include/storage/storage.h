#pragma once

#include <data/artist.h>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>

#include <mutex>
#include <ostream>

class storage
{
public:
	storage ();
	~storage ();

	bool add (const artist_ptr_t& artist);
	bool replace (const artist_ptr_t& artist);

	artist_ptr_t get_by_name (const std::string& name) const;
	artist_ptr_t get_by_id (const std::string& id) const;

	void print_all (std::ostream& stream) const;

private:
	struct id_tag_t {};
	struct name_tag_t {};
	
private:
	typedef boost::multi_index::multi_index_container<
		artist_ptr_t,
		boost::multi_index::indexed_by<
			boost::multi_index::ordered_unique<
				boost::multi_index::tag<name_tag_t>,
				boost::multi_index::const_mem_fun<artist, const std::string&, &artist::get_name>
			>,
			boost::multi_index::ordered_non_unique<
				boost::multi_index::tag<id_tag_t>,
				boost::multi_index::const_mem_fun<artist, const std::string&, &artist::get_id>
			>
		>
	> storage_t;
	
	typedef std::lock_guard<std::mutex> lock_t;
	
private:
	storage_t s;
	mutable std::mutex m;
};
