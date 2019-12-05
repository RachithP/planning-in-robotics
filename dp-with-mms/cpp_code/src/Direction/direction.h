//! \file direction.h

#pragma once

/** @brief Direction sets constant char values for directions
 * @param NORTH = North direction of maze area
 * @param EAST = East direction of maze area
 * @param SOUTH = South direction of maze area
 * @param WEST = West direction of maze area
 */

namespace fp{
	struct Direction {
	    static const char NORTH = 'n';
	    static const char EAST  = 'e';
	    static const char SOUTH = 's';
	    static const char WEST  = 'w';
	};
}