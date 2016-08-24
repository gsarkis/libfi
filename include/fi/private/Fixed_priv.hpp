/*

 *Copyright © 2011-2013 Gabi Sarkis.
 *Copyright © 2012 Alexandre Raymond.

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

#ifndef PRIVATE_FI_FIXED_PRIV_HPP
#define PRIVATE_FI_FIXED_PRIV_HPP

#include "StringConversion.hpp"
#include "DoubleConversion.hpp"
#include "FixedConversion.hpp"

#include <cmath>

namespace Fi {

	//Member functions
	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>::Fixed()
		: _val(0)
	{ }


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>::Fixed(const Fixed<W, F, S, OF, R>& a)
		: _val(a._val)
	{ }


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>::Fixed(double f)
	{

		typename TR::SignedType s = DoubleConversion::toFixedPoint<TR>(f);

		std::pair<valtype, int> rounded =
			RH::round(f, static_cast<valtype>(s));
		double roundAmnt =
			static_cast<double>(rounded.second)/std::pow(2.0, FRACTION_LENGTH);

		_val = OFH::fromDouble(f, rounded.first, roundAmnt);

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>::Fixed(const std::string& number) {

		typedef Traits<2*W, OF<Info>::WIDTH_MULT*W, 2*F, S> TR2;

		std::pair<valtype, std::string> conv
			= StringConversion::fromString<TR2>(number);

		valtype s = conv.first;

		std::string fStr = conv.second;

		std::pair<valtype, int> rounded =
			RH::round(fStr, static_cast<valtype>(s));

		_val = OFH::fromString(fStr, rounded.first, rounded.second);

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	template<std::size_t W2, std::size_t F2, Signedness S2,
	         template <typename> class OF2,
	         template <typename> class R2>
	Fixed<W, F, S, OF, R>
	Fixed<W, F, S, OF, R>::
	fromFixed(const Fixed<W2, F2, S2, OF2, R2>& src) {

		typedef Fixed<W2, F2, S2, OF2, R2> SrcType;
		typedef Fixed<W, F, S, OF, R> DstType;

		return FixedConversion<SrcType, DstType>::convert(src);

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R> Fixed<W, F, S, OF, R>::
	fromBinary(Fixed<W, F, S, OF, R>::valtype value) {

		Fixed ret;
		ret._val = value & TR::T_MASK;

		if ((S == SIGNED) && ((value & TR::S_BIT) != 0)) {
			ret._val |= TR::S_MASK;
		}

		return ret;

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>& Fixed<W, F, S, OF, R>::
	operator=(const Fixed<W, F, S, OF, R>& that) {
		this->_val = that._val;
		return *this;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	bool Fixed<W, F, S, OF, R>::
	operator<(const Fixed<W, F, S, OF, R>& x) const {
		return _val < x._val;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	bool Fixed<W, F, S, OF, R>::
	operator==(const Fixed<W, F, S, OF, R>& x) const {
		return _val == x._val;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>& Fixed<W, F, S, OF, R>::
	operator+=(const Fixed<W, F, S, OF, R>& x) {
		_val += x._val;
		_val = OFH::fromFixedPoint(_val);
		return *this;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>& Fixed<W, F, S, OF, R>::
	operator-=(const Fixed<W, F, S, OF, R>& x) {
		_val -= x._val;
		_val = OFH::fromFixedPoint(_val);
		return *this;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>& Fixed<W, F, S, OF, R>::
	operator*=(const Fixed<W, F, S, OF, R>& x) {

		//Since overflow behavior is undefined for OverflowImpossible
		//and all other overflow mechanisms guarantee 2W bits for internal
		//type, it is ok to not explicitly use a larger type.
		_val *= x._val;
		_val = RH::round(_val).first;
		_val = OFH::fromFixedPoint(_val);
		return *this;

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	template<std::size_t W2, std::size_t F2, Signedness S2,
	         template <typename> class OF2,
	         template <typename> class R2>
	Fixed<W, F, S, OF, R>& Fixed<W, F, S, OF, R>::
	operator*=(const Fixed<W2,F2,S2,OF2,R2>& x) {
		typedef Fixed<W2, F2, S2, OF2, R2> ArgType;
		typedef Fixed<W,F,S,OF,R> ResultType;
		//typedef Fixed<W+std::max<size_t>(F2-F,0),std::max<size_t>(F,F2),S,OF,R> WorkType;
		typedef Fixed<W+W2,F+F2,S,OF,R> WorkType;

		WorkType a = FixedConversion<ArgType, WorkType>::convert(x);
		WorkType b = FixedConversion<ResultType, WorkType>::convert(*this);

		WorkType c= a * b;
		ResultType result= FixedConversion<WorkType, ResultType>::convert(c);
		_val= result._val;
		return *this;
	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>& Fixed<W, F, S, OF, R>::
	operator/=(const Fixed<W, F, S, OF, R>& x) {

		//Since overflow behavior is undefined for OverflowImpossible and
		//all other overflow mechanisms guarantee 2W bits for internal type,
		//it is ok to not explicitly use a larger type.
		valtype res = (_val * (valtype(1) << FRACTION_LENGTH)) / x._val;
		_val = OFH::fromFixedPoint(res);
		return *this;

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R> Fixed<W, F, S, OF, R>::
	operator~() const {

		Fixed a(*this);
		a._val = ~a._val;
		a._val &= T_MASK;
		return a;

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>& Fixed<W, F, S, OF, R>::
	operator|=(const Fixed<W, F, S, OF, R>& x) {
		_val |= x._val;
		return *this;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>& Fixed<W, F, S, OF, R>::
	operator&=(const Fixed<W, F, S, OF, R>& x) {
		_val &= x._val;
		return *this;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>& Fixed<W, F, S, OF, R>::
	operator^=(const Fixed<W, F, S, OF, R>& x) {
		_val ^= x._val;
		return *this;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>& Fixed<W, F, S, OF, R>::
	operator>>=(std::size_t pos) {
		_val >>= pos;
		return *this;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R>& Fixed<W, F, S, OF, R>::
	operator<<=(std::size_t pos) {
		_val <<= pos;
		_val = OFH::fromFixedPoint(_val);
		return *this;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	float Fixed<W, F, S, OF, R>::
	toFloat() const {
		//Using powf instead of shifting to avoid overflow and the need
		//to know the next largest type.
		return static_cast<float>(_val)/ powf(2.0, FRACTION_LENGTH);
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	double Fixed<W, F, S, OF, R>::
	toDouble() const {
		//Using pow instead of shifting to avoid overflow and the need
		//to know the next largest type.
		return static_cast<double>(_val)/ pow(2.0, FRACTION_LENGTH);
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	std::string Fixed<W, F, S, OF, R>::
	integer() const {

		return StringConversion::integerString<TR>(_val);

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	std::string Fixed<W, F, S, OF, R>::
	fraction() const {

		return StringConversion::fractionalString<TR>(_val);

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	std::string Fixed<W, F, S, OF, R>::
	toString() const {

		return StringConversion::toString<TR>(_val);

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	std::string Fixed<W, F, S, OF, R>::
	toString(unsigned int nbDigits) const {
		return StringConversion::toString<TR>(_val, nbDigits);
	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	std::string Fixed<W, F, S, OF, R>::
	toBinaryString() const {

		std::string ret;

		for (std::size_t i = W; i > 0; --i) {
			ret.push_back('0' + ((_val >> (i-1)) & 1));
		}

		return ret;

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	typename Fixed<W, F, S, OF, R>::valtype Fixed<W, F, S, OF, R>::
	toBinary(bool extendSign) const {

		return extendSign ? _val : (_val & TR::T_MASK);

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R> Fixed<W, F, S, OF, R>::
	MaxVal() {
		Fixed ret;
		ret._val = TR::MAX_VAL;
		return ret;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W, F, S, OF, R> Fixed<W, F, S, OF, R>::
	MinVal() {
		Fixed ret;
		ret._val = TR::MIN_VAL;
		return ret;
	}


	////////////////////////////////////////////////////////////////////////////////
	//Non-member functions

	//Comparison operators

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator==(const Fixed<W, F, S, OF, R>& x,
	                       const Fixed<W, F, S, OF, R>& y)
	{

		return x.operator==(y);

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator!=(const Fixed<W, F, S, OF, R>& x,
	                       const Fixed<W, F, S, OF, R>& y)
	{

		return !(x == y);

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator<(const Fixed<W, F, S, OF, R>& x,
	                      const Fixed<W, F, S, OF, R>& y)
	{

		return x.operator<(y);

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator<=(const Fixed<W, F, S, OF, R>& x,
	                       const Fixed<W, F, S, OF, R>& y)
	{

		return (x < y) || (x == y);

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator>(const Fixed<W, F, S, OF, R>& x,
	                      const Fixed<W, F, S, OF, R>& y)
	{

		return !(x <= y);

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>

	inline bool operator>=(const Fixed<W, F, S, OF, R>& x,
	                       const Fixed<W, F, S, OF, R>& y)
	{

		return !(x < y);

	}


	// Arithmetic operators

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	operator+(const Fixed<W, F, S, OF, R>& x,
	          const Fixed<W, F, S, OF, R>& y)
	{

		Fixed<W, F, S, OF, R> ret(x);
		ret += y;
		return ret;

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	operator-(const Fixed<W, F, S, OF, R>& x,
	          const Fixed<W, F, S, OF, R>& y)
	{

		Fixed<W, F, S, OF, R> ret(x);
		ret -= y;
		return ret;

	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	operator-(const Fixed<W, F, S, OF, R>& a)
	{
		//TODO #60: figure out what to do for unsigned types...
		return Fixed<W, F, S, OF, R>(0.0) - a;
	}


	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	operator*(const Fixed<W, F, S, OF, R>& x,
	          const Fixed<W, F, S, OF, R>& y)
	{

		Fixed<W, F, S, OF, R> ret(x);
		ret *= y;
		return ret;

	}


	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	operator/(const Fixed<W, F, S, OF, R>& x,
	          const Fixed<W, F, S, OF, R>& y)
	{

		Fixed<W, F, S, OF, R> ret(x);
		ret /= y;
		return ret;

	}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	min(const Fixed<W, F, S, OF, R>& x,
	    const Fixed<W, F, S, OF, R>& y)
	{

		return (x < y) ? x : y;

	}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	max(const Fixed<W, F, S, OF, R>& x,
	    const Fixed<W, F, S, OF, R>& y)
	{

		return (x > y) ? x : y;

	}


	// Bit-wise manipulation
	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	operator~(const Fixed<W, F, S, OF, R>& x)
	{

		return ~x;

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	operator|(const Fixed<W, F, S, OF, R>& x,
	          const Fixed<W, F, S, OF, R>& y)
	{

		Fixed<W, F, S, OF, R> ret(x);
		ret |= y;
		return ret;

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	operator&(const Fixed<W, F, S, OF, R>& x,
	          const Fixed<W, F, S, OF, R>& y)
	{

		Fixed<W, F, S, OF, R> ret(x);
		ret &= y;
		return ret;

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	operator^(const Fixed<W, F, S, OF, R>& x,
	          const Fixed<W, F, S, OF, R>& y)
	{

		Fixed<W, F, S, OF, R> ret(x);
		ret ^= y;
		return ret;

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R>
	operator<<(const Fixed<W, F, S, OF, R>& x, std::size_t pos)
	{

		Fixed<W, F, S, OF, R> ret(x);
		ret <<= pos;
		return ret;

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fixed<W, F, S, OF, R> operator>>(const Fixed<W, F, S, OF, R>& x,
	                                       std::size_t pos)
	{

		Fixed<W, F, S, OF, R> ret(x);
		ret >>= pos;
		return ret;

	}

	template<std::size_t W, std::size_t F, Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	std::ostream&
	operator<<(std::ostream& os, const Fixed<W, F, S, OF, R>& x)
	{
		os << x.toString();
		return os;
	}

}

template<std::size_t W, std::size_t F, Fi::Signedness S,
         template <typename> class OF,
         template <typename> class R>
Fi::Fixed<W, F, S, OF, R> std::abs(const Fi::Fixed<W, F, S, OF, R>& x)
{

	if (x < Fi::Fixed<W, F, S, OF, R>::fromBinary(0)) {
		return -x;
	}
	else {
		return x;
	}

}

#endif
