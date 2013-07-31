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

#ifndef FI_PRIVATE_LIMITS_HPP
#define FI_PRIVATE_LIMITS_HPP

#include "Fi.hpp"

#include <cstddef>

namespace Fi {
	/**\internal
	 *\brief The minimum value that can be represented by a fixed-point number
	 *of a given width.

	 *If the fixed-point number is unsigned, the minimum value will be zero;
	 *otherwise, it will be the most negative number that can be represented.

	 *\tparam T Value type.
	 *\tparam W Width of the fixed-point number.
	 *\tparam S Fi::SIGNED or Fi::UNSIGNED determines whether the type is
	 *signed or not.
	 */
	template<typename T, std::size_t W, Signedness S>
	struct MinVal { };


	template<typename T, std::size_t W> struct MinVal<T, W, UNSIGNED> {
		static const T value = 0;
	};

	template<typename T, std::size_t W> struct MinVal<T, W, SIGNED> {
		static const T value = (T(1) << (W-1)) | (T(-1) << (W-1));
	};


	/**\internal
	 *\brief The maximum value that can be represented by a fixed-point number
	 *of a given width.

	 *\note sizeof(T) must be greater than W.

	 *\tparam T Value type.
	 *\tparam W Width of the fixed-point number.
	 *\tparam S Fi::SIGNED or Fi::UNSIGNED determines whether the
	 *type is signed or not.
	 */
	template<typename T, std::size_t W, Signedness S>
	struct MaxVal { };

	template<typename T, std::size_t W>
	struct MaxVal<T, W, UNSIGNED> {
		static const T value = (T(1) << W) - 1;
	};

	template<typename T, std::size_t W>
	struct MaxVal<T, W, SIGNED> {
		static const T value = (T(1) << (W-1)) - 1;
	};

	template<typename T, Signedness S>
	struct MaxVal<T, std::size_t(0), S> {
		static const T value = T(0);
	};

}

#endif
