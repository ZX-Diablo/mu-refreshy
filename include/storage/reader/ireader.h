#pragma once

#include <storage/storage.h>

#include <istream>

namespace reader
{
	class ireader
	{
	public:
		virtual ~ireader () = default;
		virtual void read (storage& s, std::istream& in) const = 0;
	};
}
