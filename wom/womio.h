/* The Wombling General Purpose Library
 * Copyright (c) 2018 Daniel Boulton
 *
 * https://github.com/Dandigit/wombling
 */

/* womio.h
 * Functions and classes for IO manipulation
 * and control, for applications like console
 * pausing and pretty printing.
 */

#ifndef WOMIO_H
#define WOMIO_H

#include <iostream>
#include <limits>

#undef max

namespace wom
{
	inline void pause()
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n').get();
	}
}

#endif