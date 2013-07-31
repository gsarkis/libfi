/*

 *Copyright © 2011-2012 Gabi Sarkis.

 *This file is part of the C++ Fixed-Point Library (LibFi).

 *LibFi is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.

 *LibFi is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *GNU General Public License for more details.

 *You should have received a copy of the GNU General Public License
 *along with LibFi.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef FI_OVERFLOW_SATURATE_HPP
#define FI_OVERFLOW_SATURATE_HPP

namespace Fi {

	/**
	 *\ingroup overflow
	 *\brief A saturating overflow handler.

	 *If overflow occurs, the assigned value is set to nearest representable
	 *value.

	 *\tparam T Fi::Traits of the fixed-point type.
	 */
	template <typename T>
	struct Saturate;

}

#include "fi/private/overflow/Saturate.hpp"

#endif
