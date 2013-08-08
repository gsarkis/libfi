#include <boost/preprocessor/list/for_each_product.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <cstdlib>

#include "fi/Fixed.hpp"
#define OVERFLOW_TYPES  (Wrap, (Saturate, (Throw, (Undefined, BOOST_PP_NIL))))
#include "fi/overflow/Wrap.hpp"
#include "fi/overflow/Saturate.hpp"
#include "fi/overflow/Throw.hpp"
#include "fi/overflow/Undefined.hpp"

#define ROUNDING_TYPES  (Ceil, (Classic, (Fix, (Floor, BOOST_PP_NIL))))
#include "fi/rounding/Ceil.hpp"
#include "fi/rounding/Classic.hpp"
#include "fi/rounding/Fix.hpp"
#include "fi/rounding/Floor.hpp"

#define SIGNEDNESS_TYPES  (UNSIGNED, (SIGNED, BOOST_PP_NIL))
#define W 5
#define F_VALS (1, (2, (3, (4, BOOST_PP_NIL))))


#define MACRO1(r, p) { \
	typedef Fixed<W, BOOST_PP_TUPLE_ELEM(4,0,p), BOOST_PP_TUPLE_ELEM(4,1,p), \
	BOOST_PP_TUPLE_ELEM(4,2,p), BOOST_PP_TUPLE_ELEM(4,3,p)> fi_t; \
	fi_t var; \
	std::string v_f          = BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(4,0,p)); \
	boost::to_lower(v_f); \
	std::string v_signedness = BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(4,1,p)); \
	boost::to_lower(v_signedness); \
	std::string v_overflow   = BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(4,2,p)); \
	boost::to_lower(v_overflow); \
	std::string v_rounding   = BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(4,3,p)); \
	boost::to_lower(v_rounding); \
	if ( \
	     (p_f          == v_f) \
	     && \
	     (p_signedness == v_signedness) \
	     && \
	     (p_overflow   == v_overflow) \
	     && \
	     (p_rounding   == v_rounding) \
	   ) \
	{ \
		var = fi_t(p_val); \
		std::cout << var << std::endl; \
		return 0; \
	} \
}

using namespace Fi;

void usage(char *argv0) {
	std::cout << "LibFi test program with W=" << W << std::endl << std::endl
	          << "Usage: " << std::string(argv0) << " <f> <signedness> <overflow> <rounding> <value>"
	          << std::endl
	          << "  Where:" << std::endl
	          << "    f          : number of fractional bits (1-" << W << ")" << std::endl
	          << "    signedness : overflow behavior "
	          << BOOST_PP_STRINGIZE(BOOST_PP_LIST_TO_TUPLE(SIGNEDNESS_TYPES)) << std::endl
	          << "    overflow   : overflow behavior "
	          << BOOST_PP_STRINGIZE(BOOST_PP_LIST_TO_TUPLE(OVERFLOW_TYPES)) << std::endl
	          << "    rounding   : rounding behavior "
	          << BOOST_PP_STRINGIZE(BOOST_PP_LIST_TO_TUPLE(ROUNDING_TYPES)) << std::endl
	          << "    value      : value to be converted to fixed point"
	          << std::endl;
	exit(1);
}

int main(int argc, char* argv[]) {
	if (argc < 6) {
		usage(argv[0]);
	}

	//command-line parameters
	std::string p_f          = argv[1];
	std::string p_signedness = argv[2];
	std::string p_overflow   = argv[3];
	std::string p_rounding   = argv[4];
	std::string p_val        = argv[5];

	boost::to_lower(p_f);
	boost::to_lower(p_signedness);
	boost::to_lower(p_overflow);
	boost::to_lower(p_rounding);

	BOOST_PP_LIST_FOR_EACH_PRODUCT(MACRO1, 4, (F_VALS,SIGNEDNESS_TYPES,OVERFLOW_TYPES,ROUNDING_TYPES))

	std::cout << "ERROR: Invalid parameter combination" << std::endl;
	usage(argv[0]);

	return 1;
}

