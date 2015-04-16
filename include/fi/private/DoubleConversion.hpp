/*

 *Copyright © 2012 Gabi Sarkis.

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

#ifndef FI_PRIVATE_DOUBLE_CONVERSION_HPP
#define FI_PRIVATE_DOUBLE_CONVERSION_HPP

#include <cmath>

namespace Fi {

	/**\internal
	 *\brief Functions to help in conversion from floating-point to
	 *fixed-point numbers.
	 */
	namespace DoubleConversion {

		/**\internal
		 *\brief Convert a fixed-point number to a double-precision
		 *floating-point number without applying any rounding or overflow
		 *handling
		 *\param fi Binary representation of fixed-point number.
		 *\return Double-precision floating-point number.
		 *\warning Precision of the fixed-point number might be higher than
		 *the result.
		 */
		template<typename TR>
		double toDouble(typename TR::valtype fi);

		/**\internal
		 *\brief Convert a floating-point number to a fixed-point number without
		 *applying any rounding or overflow handling.
		 *\param number The number to convert.
		 *\return The fixed-point number stored in an integer type.
		 */
		template<typename TR>
		typename TR::SignedType toFixedPoint(double number);

		/**\internal
		 *\brief Limit a floating-point number to the range [lower, upper)
		 *using modulo operations.
		 *\param number The number to limit.
		 *\param lower Smaller number in the range.
		 *\param upper Largest number in the range.
		 *\return The number limited to the range [lower, upper)
		 */
		double limitToRange(double number, double lower, double upper);

	}

	template<typename TR>
	inline double DoubleConversion::toDouble(typename TR::valtype fi) {

		return static_cast<double>(fi)/ pow(2.0, TR::FRACTION_LENGTH);

	}

	template<typename TR>
	inline typename TR::SignedType DoubleConversion::
	toFixedPoint(double number) {

		typedef typename TR::SignedType sType;
		typedef typename TR::UnsignedType uType;

		double step = 1.0/std::pow(2.0, TR::FRACTION_LENGTH);
		//Safe to multiply by 2.0 since we ensure the type fits below.
		//The multiplication is needed to handle cases where the number
		//would overflow without rounding.
		double lower = 2.0*TR::minDoubleValue();
		double upper = 2.0*(TR::maxDoubleValue() + step);

		double g = DoubleConversion::limitToRange(number, lower, upper);

		uType one = 1;
		sType s = 0;
		if (2*TR::FRACTION_LENGTH == 8*sizeof(sType)) {
			//Subtracting 1 from 2*FRACTION_LENGTH to avoid overflow to 0.
			s = g*(one << (2*TR::FRACTION_LENGTH-1));
			s <<= 1;
		}
		else {
			s = g*(one << (2*TR::FRACTION_LENGTH));
		}

		return s;

	}


	inline double DoubleConversion::
	limitToRange(double number, double lower, double upper) {

		double ret = number;

		if ((number < lower) || (number >= upper)) {
			double small = std::fmod(number, upper - lower) + (upper - lower);
			ret = std::fmod(small - lower, upper - lower);
			ret += lower;
		}

		return ret;

	}

}

#endif
