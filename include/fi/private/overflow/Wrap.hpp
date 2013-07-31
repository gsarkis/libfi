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

#ifndef FI_PRIVATE_OVERFLOW_WRAP_HPP
#define FI_PRIVATE_OVERFLOW_WRAP_HPP

#include "fi/private/Fi.hpp"
#include "fi/private/Info.hpp"
#include "fi/private/Arithmetic.hpp"

#include <string>
#include <cmath>

namespace Fi {

	/**
	 *\ingroup overflow
	 *\brief A wrap-around (modulus) overflow handler.

	 *If overflow occurs, the assigned value is the original value modulo 2^(W+1).

	 *\tparam T Fi::Traits of the fixed-point type.
	 */
	template <typename T>
	struct Wrap {

		/**
		 *\internal
		 *\brief Handle positive overflow from an integer type representing
		 *a fixed-point number.
		 *
		 *\param n Integer representing a fixed-point number.
		 *\return The number after wrapping is applied.
		 */
		static typename T::valtype positiveOverflow(const typename T::valtype& n);

		/**
		 *\internal
		 *\brief Handle negative overflow from an integer type representing
		 *a fixed-point number.
		 *
		 *\param n Integer representing a fixed-point number.
		 *\return The number after wrapping is applied.
		 */
		static typename T::valtype negativeOverflow(const typename T::valtype& n);

	};

	/**\internal
	 *\brief A specialization to retrieve information about the overflow handler.
	 */
	template<>
	struct Wrap<Fi::Info> {
		static const std::size_t WIDTH_MULT = 2;
	};

	template<typename T>
	inline typename T::valtype Wrap<T>::
	positiveOverflow(const typename T::valtype& n) {

		typename T::valtype ret = static_cast<typename T::valtype>(n);

		if (isNegative<T>(n)) {
			ret = (T::T_MASK & ret) | T::S_MASK;
		}
		else {
			ret = (T::T_MASK & ret);
		}

		return ret;

	}

	template<typename T>
	inline typename T::valtype Wrap<T>::
	negativeOverflow(const typename T::valtype& n) {

		typename T::valtype ret = static_cast<typename T::valtype>(n);

		if (isNegative<T>(n)) {
			ret = (T::T_MASK & ret) | T::S_MASK;
		}
		else {
			ret = (T::T_MASK & ret);
		}

		return ret;

	}


}

#endif
