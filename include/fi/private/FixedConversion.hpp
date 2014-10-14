/*

 *Copyright © 2013 Gabi Sarkis.

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

#ifndef FI_PRIVATE_FIXED_CONVERSION_HPP
#define FI_PRIVATE_FIXED_CONVERSION_HPP

namespace Fi {

	template<bool W_FIT, bool F_FIT, bool S_SAME, typename SrcT, typename DstT>
	struct FixedConversionInternal {
		static DstT convert(SrcT src) {
			DstT dst;

			dst = DstT(src.toString());

			return dst;
		}
	};

	template<typename SrcT, typename DstT>
	struct FixedConversionInternal<true, true, true, SrcT, DstT> {
		static DstT convert(SrcT src) {


			DstT dst =
				DstT::fromBinary(src.toBinary(true) <<
				                 (DstT::FRACTION_LENGTH - SrcT::FRACTION_LENGTH));
			return dst;

		}
	};

	template<typename SrcT, typename DstT>
	struct FixedConversionInternal<true, false, true, SrcT, DstT> {
		static DstT convert(SrcT src) {

			typename DstT::valtype val =
				static_cast<typename DstT::valtype>(src.toBinary(true)) <<
				(2*DstT::FRACTION_LENGTH - SrcT::FRACTION_LENGTH);

			val = DstT::RH::round(val).first;

			DstT dst = DstT::fromBinary(val);

			return dst;
		}
	};

	template<typename SrcT, typename DstT>
	struct FixedConversion {
		static DstT convert(SrcT src);
	};

}


template<typename SrcT, typename DstT>
DstT Fi::FixedConversion<SrcT, DstT>::convert(SrcT src) {

	return
		Fi::FixedConversionInternal<
		(DstT::WORD_LENGTH >= SrcT::WORD_LENGTH),
		(DstT::FRACTION_LENGTH >= SrcT::FRACTION_LENGTH),
		(DstT::SIGNEDNESS == SrcT::SIGNEDNESS),
		SrcT,
		DstT>::convert(src);

}

#endif
