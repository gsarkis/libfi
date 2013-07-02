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

#ifndef FI_OVERFLOW_EXCEPTIONS_HPP
#define FI_OVERFLOW_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace Fi {

  /**
   *\brief An exception thrown when positive overflow occurs.
   */
  class PositiveOverflow : public std::overflow_error {
  public:

    /*
     *\brief Constructor accepting a string message.
     *\param what_arg Message stored in the exception object and used
     *to generate the C-string return by the what() function.
     */
    explicit PositiveOverflow (const std::string& what_arg);

  };

  /**
   *\brief An exception thrown when negative overflow occurs.
   */
  class NegativeOverflow : public std::overflow_error {
  public:

    /*
     *\brief Constructor accepting a string message.
     *\param what_arg Message stored in the exception object and used
     *to generate the C-string return by the what() function.
     */
    explicit NegativeOverflow (const std::string& what_arg);

  };

}

#include "fi/private/overflow/Exceptions_impl.hpp"

#endif
