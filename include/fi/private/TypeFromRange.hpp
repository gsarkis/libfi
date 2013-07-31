/*

 *Copyright © 2011-2012 Gabi Sarkis.
 *Copyright © 2012 Alexandre Raymond.

 *This file is part of the C++ Fixed-Point Library (LibFi).

 *LibFi is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.

 *LibFi is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.

 *You should have received a copy of the GNU General Public License
 *along with LibFi.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef FI_PRIVATE_TYPE_FROM_RANGE_HPP
#define FI_PRIVATE_TYPE_FROM_RANGE_HPP

#include "fi/private/Fi.hpp"
#include "fi/private/StaticAssert.hpp"

#include <cstddef>
#include <stdint.h>

namespace Fi {

	/**\internal
	 *\brief Give the results from Fi::range a nice name
	 */
	enum RangeType {R0_8, R9_16, R17_32, R33_64, R65_INF};

	/**\internal
	 *\brief Determine which range S is in.

	 *Supported ranges are [0, 8], [9, 16], [17, 32], [33, 64], [65, +inf)
	 *\tparam S Number whose range is to be found.
	 */
	template<std::size_t S> struct Range {
		static const RangeType R = (S >= 0  && S <= 8)  ? R0_8 :
			(S >= 9  && S <= 16) ? R9_16 :
			(S >= 17 && S <= 32) ? R17_32 :
			(S >= 33 && S <= 64) ? R33_64 :
			R65_INF;
	};

	/**\internal
	 *\brief Return the smallest type with at least y bits given a range [x, y].
	 *\tparam R Range from Fi::RangeType
	 *\tparam S Fi::SIGNED or Fi::UNSIGNED determines whether the type is
	 *signed or not.
	 */
	template<RangeType R, Signedness S>
	struct TypeFromRange;

	template<> struct TypeFromRange<R0_8, SIGNED> {
		typedef int8_t valtype;
	};

	template<> struct TypeFromRange<R0_8, UNSIGNED> {
		typedef uint8_t valtype;
	};

	template<> struct TypeFromRange<R9_16, SIGNED> {
		typedef int16_t valtype;
	};

	template<> struct TypeFromRange<R9_16, UNSIGNED> {
		typedef uint16_t valtype;
	};

	template<> struct TypeFromRange<R17_32, SIGNED> {
		typedef int32_t valtype;
	};

	template<> struct TypeFromRange<R17_32, UNSIGNED> {
		typedef uint32_t valtype;
	};

	template<> struct TypeFromRange<R33_64, SIGNED> {
		typedef int64_t valtype;
	};

	template<> struct TypeFromRange<R33_64, UNSIGNED> {
		typedef uint64_t valtype;
	};

}
#endif
