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

#ifndef FI_PRIVATE_OVERFLOW_SATURATE_HPP
#define FI_PRIVATE_OVERFLOW_SATURATE_HPP

#include "fi/private/Fi.hpp"
#include "fi/private/Info.hpp"

#include <string>

namespace Fi {

	/**
	 *\ingroup overflow
	 *\brief A saturating overflow handler.

	 *If overflow occurs, the assigned value is set to nearest representable
	 *value.

	 *\tparam T Fi::Traits of the fixed-point type.
	 */
	template <typename T>
	struct Saturate {

		/**
		 *\internal
		 *\brief Handle positive overflow from an integer type representing
		 *a fixed-point number.
		 *
		 *\param n Integer representing a fixed-point number.
		 *\return The number after saturation is applied.
		 */
		static typename T::valtype positiveOverflow(const typename T::valtype& n);

		/**
		 *\internal
		 *\brief Handle negative overflow from an integer type representing
		 *a fixed-point number.
		 *
		 *\param n Integer representing a fixed-point number.
		 *\return The number after saturation is applied.
		 */
		static typename T::valtype negativeOverflow(const typename T::valtype& n);

	};


	/**\internal
	 *\brief A specialization to retrieve information about the overflow handler.
	 */
	template<>
	struct Saturate<Fi::Info> {
		static const std::size_t WIDTH_MULT = 2;
	};

	template<typename T>
	inline typename T::valtype Saturate<T>::
	positiveOverflow(const typename T::valtype& /*n*/) {

		return T::MAX_VAL;

	}

	template<typename T>
	inline typename T::valtype Saturate<T>::
	negativeOverflow(const typename T::valtype& /*n*/) {

		return T::MIN_VAL;

	}

}

#endif
