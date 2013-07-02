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

#ifndef FI_PRIVATE_PARSER_HPP
#define FI_PRIVATE_PARSER_HPP

#include "Fi.hpp"

#include <string>
#include <stdexcept>

namespace Fi {
  /**\internal
   *\brief Determines whether a character is a digit.
   *\param character Character.
   *\return \c true if Character is a digit, \c false otherwise.
   */
  inline bool isDigit(char character) {
    return (character >= '0') && (character <= '9');
  }

  /**\internal
   *\brief Parses a string representing a fixed-point number.

   *\param number String to be parsed.
   *\param signedness Whether the number is signed or unsigned.
   *\param sign Sign of parsed number.
   *\param integer Integer part of number without any leading zeros.
   *\param fractional Fractional part of number without any trailing zeros.
   *\tparam T Data type to hold the sign value.
   *\throw  std::invalid_argument when the provided number is not a valid 
   *fixed-point number. All parameters are reset on error.
   */
  template<typename T>
  void parseNumber(const std::string& number,
                   Signedness signedness,
                   T& sign,
                   std::string& integer,
                   std::string& fractional)
  {

    char dec_point = '.';

    enum {PS_SIGN, PS_INT, PS_POINT, PS_FRAC} state;

    state = PS_SIGN;

    std::string iNumber(number);

    if (iNumber.empty()) {
      iNumber = "0";
    }

    T iSign = T(1);
    std::string iInteger;
    std::string iFractional;

    sign = T(1);
    integer = "0";
    fractional = "0";

    std::size_t idx = 0;

    if ((iNumber[idx] == '-') && (signedness == Fi::SIGNED)) {
      iSign = T(-1);
      ++idx;
      state = PS_INT;
    }
    else if ((iNumber[idx] == '-') && (signedness == Fi::UNSIGNED)) {
      throw std::invalid_argument("An unsigned number cannot have a "
                                  "negative sign!");
    }
    else if (iNumber[idx] == '+') {
      iSign = T(1);
      ++idx;
      state = PS_INT;
    }
    else if (isDigit(iNumber[idx])) {
      iSign = T(1);
      state = PS_INT;
    }
    else if (iNumber[idx] == dec_point) {
      iSign = T(1);
      ++idx;
      state = PS_FRAC;
    }
    else {
      throw std::invalid_argument("Invalid number format: " + number);
    }

    for (; idx < iNumber.length(); ++idx) {
      if (isDigit(iNumber[idx]) && (state == PS_INT)) {
        iInteger.push_back(iNumber[idx]);
      }
      else if (isDigit(iNumber[idx]) && (state == PS_FRAC)) {
        iFractional.push_back(iNumber[idx]);
      }
      else if ((iNumber[idx] == dec_point) && (state == PS_INT)) {
        state = PS_FRAC;
      }
      else {
        throw std::invalid_argument("Invalid number format: " + number);
      }
    }

    if (iInteger.empty() && iFractional.empty()) {
      throw std::invalid_argument("A number must have at least one digit!");
    }

    size_t firstNZ = iInteger.find_first_not_of('0');
    if (firstNZ > 0) {
      iInteger.erase(0, firstNZ);
    }
    size_t lastNZ = iFractional.find_last_not_of('0');
    if (lastNZ == std::string::npos) {
      iFractional = "0";
    }
    else {
      iFractional.erase(lastNZ + 1);
    }

    if (iInteger.empty()) {
      iInteger = "0";
    }
    if (iFractional.empty()) {
      iFractional = "0";
    }

    sign = iSign;
    integer = iInteger;
    fractional = iFractional;

  }
}

#endif
