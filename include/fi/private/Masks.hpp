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

#ifndef FI_PRIVATE_MASKS_HPP
#define FI_PRIVATE_MASKS_HPP

#include "Fi.hpp"

#include <cstddef>
#include <cstdint>
#include <stdint.h>

namespace Fi {

    /**\internal
	 *\brief Creates a mask with zeros in the NUM_LSB_ZEROS least significant
	 * bits and ones in the most significant bits.

	 *\tparam T Underlying type.
	 *\tparam NUM_LSB_ZEROS number of least significant bits set to zeros.
	 */
    template<typename T, std::size_t NUM_LSB_ZEROS>
    struct MSB_ONES_LSB_ZEROS {
        static const T value = static_cast<T>((~static_cast<uint64_t>(0)) << NUM_LSB_ZEROS);
    };

    /**\internal
	 *\brief Creates a mask with ones in the NUM_LSB_ONES least significant
	 * bits and zeros in the most significant bits.

	 *\tparam T Underlying type.
	 *\tparam NUM_LSB_ONES number of least significant bits set to ones.
	 */
    template<typename T, std::size_t NUM_LSB_ONES>
    struct MSB_ZEROS_LSB_ONES {
        static const T value = static_cast<T>(~((~static_cast<uint64_t>(0)) << NUM_LSB_ONES));
    };

	/**\internal
	 *\brief Calculates the mask needed to select the entire fixed-point number.

	 *The mask will contain the integer and fractional bits, and the sign bit
	 *if the number is signed.

	 *\tparam T Underlying type.
	 *\tparam W Width of the fixed-point number including sign.
	 */
	template<typename T, std::size_t W>
	struct TMask {
		static const T value = MSB_ZEROS_LSB_ONES<T, W>::value;
	};


	/**\internal
	 *\brief Calculates the mask needed to select the sign bit.

	 *\tparam T Underlying type.
	 *\tparam W Width of the fixed-point number including sign.
	 *\tparam S Fi::SIGNED or Fi::UNSIGNED determines whether the
	 *type is signed or not.
	 */
	template<typename T, std::size_t W, Signedness S>
	struct SMask { };

	template<typename T, std::size_t W>
	struct SMask<T, W, SIGNED> {
		static const T value = MSB_ONES_LSB_ZEROS<T, W -1>::value;
	};

	template<typename T, std::size_t W>
	struct SMask<T, W, UNSIGNED> {
		static const T value = 0;
	};


	/**\internal
	 *\brief Calculates the mask needed to select the fractional bits.

	 *\tparam T Underlying type.
	 *\tparam W Width of the fixed-point number including sign.
	 *\tparam F Number of fractional bits.
	 */
	template<typename T, std::size_t W, std::size_t F>
	struct FMask {
		static const T value = (F == 8*sizeof(T)) ?
		static_cast<T>(~static_cast<uint64_t>(0))
		: MSB_ZEROS_LSB_ONES<T, F>::value;
	};

}

#endif
