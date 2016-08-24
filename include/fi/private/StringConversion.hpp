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

#ifndef FI_PRIVATE_STRING_CONVERSION_HPP
#define FI_PRIVATE_STRING_CONVERSION_HPP

#include "Parser.hpp"
#include "StringMath.hpp"

#include <utility>
#include <string>
#include <algorithm>
#include <iostream>

namespace Fi {

	namespace StringConversion {

		/**
		 *\internal
		 *\brief Convert the integer part of a fixed-point number to string

		 *\tparam T Traits of target fixed-point type.
		 *\param val An integer representing a fixed-point number.

		 *\return String representation of the integer part.
		 */
		template<typename T>
		std::string integerString(const typename T::valtype& val);

		/**
		 *\internal
		 *\brief Convert the fractional part of a fixed-point number to string

		 *\tparam T Traits of target fixed-point type.
		 *\param val An integer representing a fixed-point number.

		 *\return String representation of the fractional part.
		 */
		template<typename T>
		std::string fractionalString(const typename T::valtype& val);

		/**
		 *\internal
		 *\brief Convert the fractional part of a fixed-point number to string, 
		 *       with the ability to adjust the string length.

		 *\tparam T Traits of target fixed-point type.
		 *\param val An integer representing a fixed-point number.
		 *\param length Desired number of digits in the string.

		 *\return String representation of the fractional part.
		 */
		template<typename T>
		std::string fractionalString(const typename T::valtype& val,
		                             unsigned int length);		

		/**
		 *\internal
		 *\brief Convert the fractional part of a fixed-point number to string
		 *assuming the input is unsigned.

		 *\tparam T Traits of target fixed-point type. Signedness will be ignored
		 *\param val An integer representing an unsigned fixed-point number.

		 *\return String representation of the fractional part.
		 */
		template<typename T>
		std::string unsignedFractionalString(const typename T::UnsignedType& val);

		/**
		 *\internal
		 *\brief Convert a fixed-point number to string

		 *\tparam T Traits of target fixed-point type.
		 *\param val An integer representing a fixed-point number.

		 *\return String representation of the fixed-point number.
		 */
		template<typename T>
		std::string toString(const typename T::valtype& val);

		/**
		 *\internal
		 *\brief Convert a fixed-point number to string with the ability to
		 *       adjust the length of the fractional part.

		 *\tparam T Traits of target fixed-point type.
		 *\param val An integer representing a fixed-point number.
		 *\param nbDigits The total number of digits, including the integer part.

		 *\return String representation of the fixed-point number.
		 */
		template<typename T>
		std::string toString(const typename T::valtype& val,
		                     unsigned int nbDigits);		

		/**
		 *\internal
		 *\brief Convert a string to fixed-point number.

		 *\tparam T Traits of target fixed-point type.
		 *\param number A string representing a fixed-point number.

		 *\return An integer representing a fixed-point number and
		 *properly formatted version of the input string.
		 *\throw  std::invalid_argument when the provided number is not a valid
		 *fixed-point number.
		 */
		template<typename T>
		std::pair<typename T::valtype, std::string>
		fromString(const std::string& number);

	}


	template<typename T>
	inline std::string StringConversion::
	integerString(const typename T::valtype& val) {

		std::string ret;

		if (T::FRACTION_LENGTH == T::WORD_LENGTH) {
			ret = "0";
		}
		else {
			typename T::valtype absVal = (val > 0) ? val : -val;

			typename T::valtype i = absVal >> T::FRACTION_LENGTH;

			do {
				ret.push_back((i % 10) + '0');
				i /= 10;
			} while (i != 0);
		}
		//if (val < 0) ret.push_back('-');
		//get rid of compiler errors for unsigned types
		if ((val & T::S_MASK) != 0) ret.push_back('-');

		std::reverse(ret.begin(), ret.end());

		return ret;

	}

	template<typename T>
	inline std::string StringConversion::
	fractionalString(const typename T::valtype& val) {

		std::string ret;
		typedef typename T::UnsignedType utype;

		utype absfrac = (val > 0) ? val : -val;
		absfrac &= T::F_MASK;

		if (T::FRACTION_LENGTH == 0) {
			ret = "0";
		}
		else if (T::FRACTION_LENGTH == 8*sizeof(typename T::valtype)) {
			const utype LSB_MASK = static_cast<utype>(T::F_MASK) >> (T::FRACTION_LENGTH/2);

			utype msb = absfrac >> (T::FRACTION_LENGTH/2);
			utype lsb = absfrac & LSB_MASK;

			do {
				lsb *= 10;
				msb *= 10;
				msb += (lsb >> (T::FRACTION_LENGTH/2));
				utype digit = msb >> (T::FRACTION_LENGTH/2);
				ret.push_back(digit + '0');
				lsb &= LSB_MASK;
				msb &= LSB_MASK;
			} while ((msb != 0) || (lsb != 0));
		}
		else {
			do {
				absfrac *= 10;
				utype digit = absfrac >> T::FRACTION_LENGTH;

				ret.push_back(digit + '0');
				absfrac &= T::F_MASK;
			} while (absfrac != 0);
		}

		return ret;

	}

	template<typename T>
	inline std::string StringConversion::
	fractionalString(const typename T::valtype& val,
	                 unsigned int length) {
		std::string str= fractionalString<T>(val);
		if(str.length() > length) {
			// truncate
			return str.substr(0, length);
		}
		// otherwise pad with zeroes
		while(str.length() < length) {
			str= str + "0";
		}
		return str;
	}

	//This is required to avoid compiler warnings when shifting down by 4 (in TOO_SMALL = true)
	template<typename T, bool TOO_SMALL>
	struct Digits;

	template<typename T>
	struct Digits<T, false> {

		static std::string calculate(typename T::UnsignedType absfrac) {

			std::string ret;

			do {
				absfrac *= 10;
				typename T::UnsignedType digit = absfrac >> T::FRACTION_LENGTH;

				ret.push_back(digit + '0');
				absfrac &= T::F_MASK;
			} while (absfrac != 0);

			return ret;

		}

	};

	template<typename T>
	struct Digits<T, true> {

		static std::string calculate(typename T::UnsignedType absfrac) {

			std::string ret;

			do {
				typename T::UnsignedType digit =
					(absfrac >> 4)*10 >> (T::FRACTION_LENGTH - 4);

				absfrac *= 10;

				ret.push_back(digit + '0');
				absfrac &= T::F_MASK;
			} while (absfrac != 0);

			return ret;

		}

	};

	template<typename T>
	inline std::string StringConversion::
	unsignedFractionalString(const typename T::UnsignedType& val) {

		std::string ret;
		typedef typename T::UnsignedType utype;

		utype absfrac = val & T::F_MASK;

		if (T::FRACTION_LENGTH == 0) {
			ret = "0";
		}
		else if (T::FRACTION_LENGTH == 8*sizeof(utype)) {
			const utype LSB_MASK = static_cast<utype>(T::F_MASK) >> (T::FRACTION_LENGTH/2);

			utype msb = absfrac >> (T::FRACTION_LENGTH/2);
			utype lsb = absfrac & LSB_MASK;

			do {
				lsb *= 10;
				msb *= 10;
				msb += (lsb >> (T::FRACTION_LENGTH/2));
				utype digit = msb >> (T::FRACTION_LENGTH/2);
				ret.push_back(digit + '0');
				lsb &= LSB_MASK;
				msb &= LSB_MASK;
			} while ((msb != 0) || (lsb != 0));
		}
		else {
			ret = Digits<T, ((T::FRACTION_LENGTH + 4) > 8*sizeof(utype))>::calculate(absfrac);
		}
		/*
		else if ((T::FRACTION_LENGTH + 4) > 8*sizeof(utype)) {
			do {
				utype digit = (absfrac >> 4)*10 >> (T::FRACTION_LENGTH - 4);
				absfrac *= 10;

				ret.push_back(digit + '0');
				absfrac &= T::F_MASK;
			} while (absfrac != 0);
		}
		else {
			do {
				absfrac *= 10;
				utype digit = absfrac >> T::FRACTION_LENGTH;

				ret.push_back(digit + '0');
				absfrac &= T::F_MASK;
			} while (absfrac != 0);
		}
		*/

		return ret;

	}


	template<typename T>
	inline std::string StringConversion::
	toString(const typename T::valtype& val) {

		return integerString<T>(val) + "." + fractionalString<T>(val);

	}

	template<typename T>
	inline std::string StringConversion::
	toString(const typename T::valtype& val, unsigned int nbDigits) {

		std::string intPart= integerString<T>(val);
		unsigned int nbIntDigits= intPart.length();
		if ((val & T::S_MASK) != 0) nbIntDigits--; // don't count the "-" sign
		std::string fracPart= fractionalString<T>(val,
		                                          nbDigits - nbIntDigits);
		return intPart + "." + fracPart;
		
	}

	template<typename T>
	inline std::pair<typename T::valtype, std::string> StringConversion::
	fromString(const std::string& number) {

		typename T::valtype val = 0;
		typename T::valtype sign = 1;

		std::string intS;
		std::string targetF;

		parseNumber(number, T::SIGNEDNESS, sign, intS, targetF);

		for (std::size_t i = 0; i < intS.size(); ++i) {
			val *= 10;
			val += (intS[i] - '0');
		}

		//make room for the fractional part
		if (T::FRACTION_LENGTH > 0) {
			//Broken into two pieces to get rid of compiler warnings when W=F
			val <<= (T::FRACTION_LENGTH - 1);
			val <<= 1;
		}

		typename T::valtype f;
		std::string sf;
		f = 0;
		unsigned int i = 0;
		std::string fullTargetF = "0." + targetF;
		while ((i < T::FRACTION_LENGTH) && (sf != fullTargetF)) {
			f |= 1 << (T::FRACTION_LENGTH - i - 1);
			sf = "0." + unsignedFractionalString<T>(f);

			if (StringMath::less(fullTargetF, sf)) {
				f &= ~(1 << (T::FRACTION_LENGTH - i - 1));
			}

			++i;
		}
		val |= (f & T::F_MASK);
		val *= sign;

		std::string formattedString = ((sign == 1) ? "" : "-") + intS + "." + targetF;
		return std::make_pair(val, formattedString);

	}

}

#endif
