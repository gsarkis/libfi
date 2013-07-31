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


#ifndef FI_PRIVATE_STRING_MATH_HPP
#define FI_PRIVATE_STRING_MATH_HPP

#include "Parser.hpp"

#include <string>
#include <stdint.h>
#include <sstream>

namespace Fi {
	/**\internal
	 *\brief Numerically compare strings.
	 */
	namespace StringMath {

		/**\internal
		 *\brief Numerically check if a string is less than another (lhs < rhs).
		 *\param lhs Left hand side operand
		 *\param rhs Right hand side operand
		 *\throw std::invalid_argument if an operand is invalid.
		 */
		bool less(const std::string& lhs, const std::string& rhs);

		/**\internal
		 *\brief Numerically check if a string is greater than another (lhs > rhs).
		 *\param lhs Left hand side operand
		 *\param rhs Right hand side operand
		 *\throw std::invalid_argument if an operand is invalid.
		 */
		bool greater(const std::string& lhs, const std::string& rhs);

		/**\internal
		 *\brief Numerically check if a string is equal to another (lhs == rhs).
		 *\param lhs Left hand side operand
		 *\param rhs Right hand side operand
		 *\throw std::invalid_argument if an operand is invalid.
		 */
		bool equal(const std::string& lhs, const std::string& rhs);

		/**\internal
		 *\brief Increment an integer represented by a string.
		 *\param number Integer to increment.
		 *\return Incremented value.
		 */
		std::string plusOne(const std::string& number);

	}

	inline bool StringMath::
	less(const std::string& lhs, const std::string& rhs) {

		int signL = 0;
		int signR = 0;
		std::string intL, intR;
		std::string fracL, fracR;
		parseNumber(lhs, Fi::SIGNED, signL, intL, fracL);
		parseNumber(rhs, Fi::SIGNED, signR, intR, fracR);

		if ((intL == "0") && (fracL == "0")) signL = 1;
		if ((intR == "0") && (fracR == "0")) signR = 1;

		while (fracL.length() < fracR.length()) fracL.push_back('0');
		while (fracL.length() > fracR.length()) fracR.push_back('0');

		bool ret = false;

		if (signL < signR) {
			ret = true;
		}
		else if (signL > signR) {
			ret = false;
		}
		//Same sign
		else if (intL.length() < intR.length()) {
			//flip result when comparing negative numbers
			ret = true ^ (signL == -1);
		}
		else if (intL.length() > intR.length()) {
			ret = false ^ (signL == -1);
		}
		//Same sign and integer length
		else if (intL < intR) {
			ret = true ^ (signL == -1);
		}
		else if (intL > intR) {
			ret = false ^ (signL == -1);
		}
		//same sign and integer part
		else if (fracL < fracR) {
			ret = true ^ (signL == -1);
		}
		else if (fracL > fracR) {
			ret = false ^ (signL == -1);
		}


		return ret;

	}

	inline bool StringMath::
	greater(const std::string& lhs, const std::string& rhs) {

		return !(less(lhs, rhs) || equal(lhs, rhs));

	}

	inline bool StringMath::
	equal(const std::string& lhs, const std::string& rhs) {

		int signL = 0;
		int signR = 0;
		std::string intL, intR;
		std::string fracL, fracR;

		parseNumber(lhs, Fi::SIGNED, signL, intL, fracL);
		parseNumber(rhs, Fi::SIGNED, signR, intR, fracR);

		if ((intL == "0") && (fracL == "0")) signL = 1;
		if ((intR == "0") && (fracR == "0")) signR = 1;

		return (signL == signR)
			&& (intL == intR)
			&& (fracL == fracR);

	}


	inline std::string StringMath::
	plusOne(const std::string& number) {

		std::stringstream stream;
		int64_t integer;

		stream << number;
		stream >> integer;

		++integer;

		stream.str("");
		stream.clear();
		stream << integer;

		return stream.str();

	}

}

#endif
