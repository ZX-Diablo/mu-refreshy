#pragma once

#include "artist.h"

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>

class storage
{
public:
	storage ();
	~storage ();
	
	void add (const artist_ptr_t& artist);
	
	bool name_exists (const std::string& name) const;
	bool id_exists (const std::string& id) const;
	
	artist_ptr_t get_by_name (const std::string& name) const;
	artist_ptr_t get_by_id (const std::string& id) const;
	
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
	
private:
	storage_t s;
};
