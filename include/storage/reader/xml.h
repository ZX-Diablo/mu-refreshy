#pragma once

#include <storage/reader/ireader.h>

#include <pugixml.hpp>

namespace reader
{
	class xml : public ireader
	{
	public:
		virtual ~xml () = default;
		virtual void read(storage& s, std::istream& in) const override;
	};
}
