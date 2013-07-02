#include "fi/Fixed.hpp"
#include "fi/overflow/Saturate.hpp"
#include "fi/overflow/Throw.hpp"
#include "fi/overflow/Wrap.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE w_eq_f
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

typedef Fi::Fixed<4, 4, Fi::SIGNED, Fi::Saturate> fi4s;

BOOST_AUTO_TEST_SUITE(Saturate)
BOOST_AUTO_TEST_CASE( saturate_flp_construction )
{

  CHECK_EQ(fi4s(9.0)   , "0.4375");
  CHECK_EQ(fi4s(7.9375), "0.4375");
  CHECK_EQ(fi4s(1.0f)  , "0.4375");
  CHECK_EQ(fi4s(0.5)   , "0.4375");
  CHECK_EQ(fi4s(0.4)   , "0.375");
  CHECK_EQ(fi4s(0.37)  , "0.3125");
  CHECK_EQ(fi4s(0.1875), "0.1875");
  CHECK_EQ(fi4s(0.1)   , "0.0625");
  CHECK_EQ(fi4s(0.0)   , "0.0");
  CHECK_EQ(fi4s(-0.0)  , "0.0");
  CHECK_EQ(fi4s(-0.1)   , "-0.0625");
  CHECK_EQ(fi4s(-0.1875), "-0.1875");
  CHECK_EQ(fi4s(-0.37)  , "-0.3125");
  CHECK_EQ(fi4s(-0.4)   , "-0.375");
  CHECK_EQ(fi4s(-0.5)   , "-0.5");
  CHECK_EQ(fi4s(-1.0f)  , "-0.5");
  CHECK_EQ(fi4s(-7.9375), "-0.5");
  CHECK_EQ(fi4s(-9.0)   , "-0.5");

  CHECK_EQ(fi4s(-0.416178622003067), "-0.375" );
  CHECK_EQ(fi4s(-0.271023031283181), "-0.25"  );
  CHECK_EQ(fi4s( 0.413337361501670),  "0.375" );
  CHECK_EQ(fi4s(-0.347621981030777), "-0.3125");
  CHECK_EQ(fi4s( 0.325816977489547),  "0.3125");
  CHECK_EQ(fi4s( 0.038342435260057),  "0.0"   );
  CHECK_EQ(fi4s( 0.496134716626885), "0.4375" );
  CHECK_EQ(fi4s(-0.421824471246816), "-0.375" );
  CHECK_EQ(fi4s(-0.057321730224554),  "0.0"   );
  CHECK_EQ(fi4s(-0.393347229819416), "-0.375" );

}

BOOST_AUTO_TEST_CASE( saturate_str_construction )
{

  CHECK_EQ(fi4s("9.0")   , "0.4375");
  CHECK_EQ(fi4s("7.9375"), "0.4375");
  CHECK_EQ(fi4s("1.0")  , "0.4375");
  CHECK_EQ(fi4s("0.5")   , "0.4375");
  CHECK_EQ(fi4s("0.4")   , "0.375");
  CHECK_EQ(fi4s("0.37")  , "0.3125");
  CHECK_EQ(fi4s("0.1")   , "0.0625");
  CHECK_EQ(fi4s("0.0")   , "0.0");
  CHECK_EQ(fi4s("-0.0")  , "0.0");
  CHECK_EQ(fi4s("-0.1")   , "-0.0625");
  CHECK_EQ(fi4s("-0.37")  , "-0.3125");
  CHECK_EQ(fi4s("-0.4")   , "-0.375");
  CHECK_EQ(fi4s("-0.5")   , "-0.5");
  CHECK_EQ(fi4s("-1.0")  , "-0.5");
  CHECK_EQ(fi4s("-7.9375"), "-0.5");
  CHECK_EQ(fi4s("-9.0")   , "-0.5");

  CHECK_EQ(fi4s("-0.416178622003067"), "-0.375" );
  CHECK_EQ(fi4s("-0.271023031283181"), "-0.25"  );
  CHECK_EQ(fi4s( "0.413337361501670"),  "0.375" );
  CHECK_EQ(fi4s("-0.347621981030777"), "-0.3125");
  CHECK_EQ(fi4s( "0.325816977489547"),  "0.3125");
  CHECK_EQ(fi4s( "0.038342435260057"),  "0.0"   );
  CHECK_EQ(fi4s( "0.496134716626885"), "0.4375" );
  CHECK_EQ(fi4s("-0.421824471246816"), "-0.375" );
  CHECK_EQ(fi4s("-0.057321730224554"),  "0.0"   );
  CHECK_EQ(fi4s("-0.393347229819416"), "-0.375" );

  BOOST_CHECK_THROW(fi4s("abc"), std::invalid_argument);
  BOOST_CHECK_THROW(fi4s("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( saturate_add )
{

  CHECK_EQ(fi4s("-0.375")  + fi4s( "0.4375"),  "0.0625");
  CHECK_EQ(fi4s("-0.25")   + fi4s("-0.4375"), "-0.5");
  CHECK_EQ(fi4s( "0.375")  + fi4s( "0.25"),    "0.4375");
  CHECK_EQ(fi4s("-0.3125") + fi4s( "0.3125"),  "0.0");
  CHECK_EQ(fi4s( "0.3125") + fi4s( "0.3125"),  "0.4375");
  CHECK_EQ(fi4s( "0.0")    + fi4s("-0.375"),  "-0.375");
  CHECK_EQ(fi4s( "0.4375") + fi4s("-0.0625"),  "0.375");
  CHECK_EQ(fi4s("-0.375")  + fi4s("-0.1875"), "-0.5");
  CHECK_EQ(fi4s( "0.25")   + fi4s( "0.0"),     "0.25");
  CHECK_EQ(fi4s("-0.375")  + fi4s("-0.0625"), "-0.4375");

}

BOOST_AUTO_TEST_CASE( saturate_sub )
{

  CHECK_EQ(fi4s("-0.375")  - fi4s( "0.4375"), "-0.5");
  CHECK_EQ(fi4s("-0.25")   - fi4s("-0.4375"),  "0.1875");
  CHECK_EQ(fi4s( "0.375")  - fi4s( "0.25"),    "0.125");
  CHECK_EQ(fi4s("-0.3125") - fi4s( "0.3125"),  "-0.5");
  CHECK_EQ(fi4s( "0.3125") - fi4s( "0.3125"),  "0.0");
  CHECK_EQ(fi4s( "0.0")    - fi4s("-0.375"),  "0.375");
  CHECK_EQ(fi4s( "0.4375") - fi4s("-0.0625"),  "0.4375");
  CHECK_EQ(fi4s("-0.375")  - fi4s("-0.1875"), "-0.1875");
  CHECK_EQ(fi4s( "0.0")    - fi4s( "0.25"),    "-0.25");
  CHECK_EQ(fi4s("-0.375")  - fi4s("-0.0625"), "-0.3125");

}

BOOST_AUTO_TEST_CASE( saturate_mul )
{

  //Directed
  CHECK_EQ(fi4s("0") * fi4s("6.234"), "0.0");
  CHECK_EQ(fi4s("-1.234") * fi4s("0.0"), "0.0");
  CHECK_EQ(fi4s("7.9375") * fi4s("7.9375"), "0.1875");
  CHECK_EQ(fi4s("-8.0") * fi4s("7.9375"), "-0.1875");
  CHECK_EQ(fi4s("7.9375") * fi4s("-8.0"), "-0.1875");
  CHECK_EQ(fi4s("-8.0") * fi4s("-8.0"), "0.25");
  //Random

  CHECK_EQ(fi4s( "0.410647594429523") * fi4s( "0.122055131485066"), "0.0");
  CHECK_EQ(fi4s("-0.318152971697148") * fi4s("-0.149047619107729"), "0.0");
  CHECK_EQ(fi4s("-0.236197083478010") * fi4s( "0.013249539867053"), "0.0");
  CHECK_EQ(fi4s("-0.354461019615283") * fi4s("-0.098191966248058"), "0.0");
  CHECK_EQ(fi4s("-0.363931441291336") * fi4s("-0.424033308309158"), "0.0625");
  CHECK_EQ(fi4s( "0.369292207640089") * fi4s("-0.260083846446342"), "-0.0625");
  CHECK_EQ(fi4s( "0.079704587365570") * fi4s("-0.376681065164834"), "0.0");
  CHECK_EQ(fi4s( "0.049860201836332") * fi4s("-0.316092211717583"), "0.0");
  CHECK_EQ(fi4s("-0.355045201776273") * fi4s("-0.260047474335097"), "0.0625");
  CHECK_EQ(fi4s( "0.353031117721894") * fi4s("-0.082732930915630"), "0.0");
  
}

BOOST_AUTO_TEST_CASE( saturate_div )
{

  CHECK_EQ(fi4s("0") / fi4s("0.234"), "0.0");

  CHECK_EQ(fi4s( "0.410647594429523") / fi4s( "0.122055131485066"), "0.4375");
  CHECK_EQ(fi4s("-0.318152971697148") / fi4s("-0.149047619107729"), "0.4375");
  CHECK_EQ(fi4s("-0.354461019615283") / fi4s("-0.098191966248058"), "0.4375");
  CHECK_EQ(fi4s("-0.363931441291336") / fi4s("-0.424033308309158"), "0.4375");
  CHECK_EQ(fi4s( "0.369292207640089") / fi4s("-0.260083846446342"), "-0.5");
  CHECK_EQ(fi4s( "0.079704587365570") / fi4s("-0.376681065164834"), "-0.125");
  CHECK_EQ(fi4s( "0.049860201836332") / fi4s("-0.316092211717583"), "0.0");
  CHECK_EQ(fi4s("-0.355045201776273") / fi4s("-0.260047474335097"), "0.4375");
  CHECK_EQ(fi4s( "0.353031117721894") / fi4s("-0.082732930915630"), "-0.5");
  
  CHECK_EQ(fi4s( "0.122055131485066") / fi4s( "0.410647594429523"), "0.125");
  CHECK_EQ(fi4s("-0.149047619107729") / fi4s("-0.318152971697148"), "0.375");
  CHECK_EQ(fi4s( "0.013249539867053") / fi4s("-0.236197083478010"), "0.0");
  CHECK_EQ(fi4s("-0.098191966248058") / fi4s("-0.354461019615283"), "0.1875");
  CHECK_EQ(fi4s("-0.424033308309158") / fi4s("-0.363931441291336"), "0.4375");
  CHECK_EQ(fi4s("-0.260083846446342") / fi4s( "0.369292207640089"), "-0.5");
  CHECK_EQ(fi4s("-0.376681065164834") / fi4s( "0.079704587365570"), "-0.5");
  CHECK_EQ(fi4s("-0.260047474335097") / fi4s("-0.355045201776273"), "0.4375");
  CHECK_EQ(fi4s("-0.082732930915630") / fi4s( "0.353031117721894"), "-0.1875");
  
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

typedef Fi::Fixed<4, 4, Fi::SIGNED, Fi::Wrap> fi4w;

BOOST_AUTO_TEST_SUITE(Wrap)

BOOST_AUTO_TEST_CASE( wrap_flp_construction )
{

  CHECK_EQ(fi4w(9.0)   , "0.0");
  CHECK_EQ(fi4w(1000.0)   , "0.0");
  CHECK_EQ(fi4w(7.9375), "-0.0625");
  CHECK_EQ(fi4w(1.0f)  , "0.0");
  CHECK_EQ(fi4w(0.5)   , "-0.5");
  CHECK_EQ(fi4w(0.4)   , "0.375");
  CHECK_EQ(fi4w(0.37)  , "0.3125");
  CHECK_EQ(fi4w(0.1875), "0.1875");
  CHECK_EQ(fi4w(0.1)   , "0.0625");
  CHECK_EQ(fi4w(0.0)   , "0.0");
  CHECK_EQ(fi4w(-0.0)  , "0.0");
  CHECK_EQ(fi4w(-0.1)   , "-0.0625");
  CHECK_EQ(fi4w(-0.1875), "-0.1875");
  CHECK_EQ(fi4w(-0.37)  , "-0.3125");
  CHECK_EQ(fi4w(-0.4)   , "-0.375");
  CHECK_EQ(fi4w(-0.5)   , "-0.5");
  CHECK_EQ(fi4w(-1.0f)  , "0.0");
  CHECK_EQ(fi4w(-7.9375), "0.0625");
  CHECK_EQ(fi4w(-9.0)   , "0.0");

  CHECK_EQ(fi4w(-0.416178622003067), "-0.375" );
  CHECK_EQ(fi4w(-0.271023031283181), "-0.25"  );
  CHECK_EQ(fi4w( 0.413337361501670),  "0.375" );
  CHECK_EQ(fi4w(-0.347621981030777), "-0.3125");
  CHECK_EQ(fi4w( 0.325816977489547),  "0.3125");
  CHECK_EQ(fi4w( 0.038342435260057),  "0.0"   );
  CHECK_EQ(fi4w( 0.496134716626885), "0.4375" );
  CHECK_EQ(fi4w(-0.421824471246816), "-0.375" );
  CHECK_EQ(fi4w(-0.057321730224554),  "0.0"   );
  CHECK_EQ(fi4w(-0.393347229819416), "-0.375" );

}

BOOST_AUTO_TEST_CASE( wrap_str_construction )
{

  CHECK_EQ(fi4w("9.0")   , "0.0");
  CHECK_EQ(fi4w("7.9375"), "-0.0625");
  CHECK_EQ(fi4w("1.0")  , "0.0");
  CHECK_EQ(fi4w("0.5")   , "-0.5");
  CHECK_EQ(fi4w("0.4")   , "0.375");
  CHECK_EQ(fi4w("0.37")  , "0.3125");
  CHECK_EQ(fi4w("0.1875"), "0.1875");
  CHECK_EQ(fi4w("0.1")   , "0.0625");
  CHECK_EQ(fi4w("0.0")   , "0.0");
  CHECK_EQ(fi4w("-0.0")  , "0.0");
  CHECK_EQ(fi4w("-0.1")   , "-0.0625");
  CHECK_EQ(fi4w("-0.1875"), "-0.1875");
  CHECK_EQ(fi4w("-0.37")  , "-0.3125");
  CHECK_EQ(fi4w("-0.4")   , "-0.375");
  CHECK_EQ(fi4w("-0.5")   , "-0.5");
  CHECK_EQ(fi4w("-1.0")  , "0.0");
  CHECK_EQ(fi4w("-7.9375"), "0.0625");
  CHECK_EQ(fi4w("-9.0")   , "0.0");

  CHECK_EQ(fi4w("-0.416178622003067"), "-0.375" );
  CHECK_EQ(fi4w("-0.271023031283181"), "-0.25"  );
  CHECK_EQ(fi4w( "0.413337361501670"),  "0.375" );
  CHECK_EQ(fi4w("-0.347621981030777"), "-0.3125");
  CHECK_EQ(fi4w( "0.325816977489547"),  "0.3125");
  CHECK_EQ(fi4w( "0.038342435260057"),  "0.0"   );
  CHECK_EQ(fi4w( "0.496134716626885"), "0.4375" );
  CHECK_EQ(fi4w("-0.421824471246816"), "-0.375" );
  CHECK_EQ(fi4w("-0.057321730224554"),  "0.0"   );
  CHECK_EQ(fi4w("-0.393347229819416"), "-0.375" );

  BOOST_CHECK_THROW(fi4w("abc"), std::invalid_argument);
  BOOST_CHECK_THROW(fi4w("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( wrap_add )
{

  CHECK_EQ(fi4w("-0.375")  + fi4w( "0.4375"), "0.0625"  );
  CHECK_EQ(fi4w("-0.25")   + fi4w("-0.4375"), "0.3125"  );
  CHECK_EQ(fi4w( "0.375")  + fi4w( "0.25"),   "-0.375"  );
  CHECK_EQ(fi4w("-0.3125") + fi4w( "0.3125"), "0.0"     );
  CHECK_EQ(fi4w( "0.3125") + fi4w( "0.3125"), "-0.375"  );
  CHECK_EQ(fi4w( "0.0")    + fi4w("-0.375"),  "-0.375"  );
  CHECK_EQ(fi4w( "0.4375") + fi4w("-0.0625"), "0.375"   );
  CHECK_EQ(fi4w("-0.375")  + fi4w("-0.1875"), "0.4375"  );
  CHECK_EQ(fi4w( "0.25")   + fi4w( "0.0"),    "0.25"    );
  CHECK_EQ(fi4w("-0.375")  + fi4w("-0.0625"), "-0.4375" );

}

BOOST_AUTO_TEST_CASE( wrap_sub )
{

  CHECK_EQ(fi4w("-0.375")  - fi4w( "0.4375"),  "0.1875" );
  CHECK_EQ(fi4w("-0.25")   - fi4w("-0.4375"),  "0.1875" );
  CHECK_EQ(fi4w( "0.375")  - fi4w( "0.25"),    "0.125"  );
  CHECK_EQ(fi4w("-0.3125") - fi4w( "0.3125"),  "0.375"  );
  CHECK_EQ(fi4w( "0.3125") - fi4w( "0.3125"),  "0.0"    );
  CHECK_EQ(fi4w( "0.0")    - fi4w("-0.375"),   "0.375"  );
  CHECK_EQ(fi4w( "0.4375") - fi4w("-0.0625"), "-0.5"    );
  CHECK_EQ(fi4w("-0.375")  - fi4w("-0.1875"), "-0.1875" );
  CHECK_EQ(fi4w( "0.25")   - fi4w( "0.0"),     "0.25"   );
  CHECK_EQ(fi4w("-0.375")  - fi4w("-0.0625"), "-0.3125" );

  CHECK_EQ(fi4w( "0.4375") - fi4w("-0.375") , "-0.1875" );
  CHECK_EQ(fi4w("-0.4375") - fi4w("-0.25")  , "-0.1875" );
  CHECK_EQ(fi4w( "0.25")   - fi4w( "0.375") , "-0.125"  );
  CHECK_EQ(fi4w( "0.3125") - fi4w("-0.3125"), "-0.375"  );
  CHECK_EQ(fi4w( "0.3125") - fi4w( "0.3125"),  "0.0"    );
  CHECK_EQ(fi4w("-0.375")  - fi4w( "0.0")   , "-0.375"  );
  CHECK_EQ(fi4w("-0.0625") - fi4w( "0.4375"), "-0.5"    );
  CHECK_EQ(fi4w("-0.1875") - fi4w("-0.375") ,  "0.1875" );
  CHECK_EQ(fi4w( "0.0")    - fi4w( "0.25")  , "-0.25"   );
  CHECK_EQ(fi4w("-0.0625") - fi4w("-0.375") ,  "0.3125" );

}

BOOST_AUTO_TEST_CASE( wrap_mul )
{

  //Directed
  CHECK_EQ(fi4w("0") * fi4w("6.234"), "0.0");
  CHECK_EQ(fi4w("-1.234") * fi4w("0.0"), "0.0");
  CHECK_EQ(fi4w("7.9375") * fi4w("7.9375"), "0.0");
  CHECK_EQ(fi4w("-8.0") * fi4w("7.9375"), "0.0");
  CHECK_EQ(fi4w("7.9375") * fi4w("-8.0"), "0.0");
  CHECK_EQ(fi4w("-8.0") * fi4w("-8.0"), "0.0");

  //Random
  CHECK_EQ(fi4w( "0.410647594429523") * fi4w( "0.122055131485066"), "0.0");
  CHECK_EQ(fi4w("-0.318152971697148") * fi4w("-0.149047619107729"), "0.0");
  CHECK_EQ(fi4w("-0.236197083478010") * fi4w( "0.013249539867053"), "0.0");
  CHECK_EQ(fi4w("-0.354461019615283") * fi4w("-0.098191966248058"), "0.0");
  CHECK_EQ(fi4w("-0.363931441291336") * fi4w("-0.424033308309158"), "0.0625");
  CHECK_EQ(fi4w( "0.369292207640089") * fi4w("-0.260083846446342"), "-0.0625");
  CHECK_EQ(fi4w( "0.079704587365570") * fi4w("-0.376681065164834"), "0.0");
  CHECK_EQ(fi4w( "0.049860201836332") * fi4w("-0.316092211717583"), "0.0");
  CHECK_EQ(fi4w("-0.355045201776273") * fi4w("-0.260047474335097"), "0.0625");
  CHECK_EQ(fi4w( "0.353031117721894") * fi4w("-0.082732930915630"), "0.0");

}

BOOST_AUTO_TEST_CASE( wrap_div )
{

  CHECK_EQ(fi4w("0") / fi4w("0.234"), "0.0");

  CHECK_EQ(fi4w( "0.410647594429523") / fi4w( "0.122055131485066"), "0.0");
  CHECK_EQ(fi4w("-0.318152971697148") / fi4w("-0.149047619107729"), "-0.5");
  CHECK_EQ(fi4w("-0.354461019615283") / fi4w("-0.098191966248058"), "0.0");
  CHECK_EQ(fi4w("-0.363931441291336") / fi4w("-0.424033308309158"), "-0.1875");
  CHECK_EQ(fi4w( "0.369292207640089") / fi4w("-0.260083846446342"), "-0.25");
  CHECK_EQ(fi4w( "0.079704587365570") / fi4w("-0.376681065164834"), "-0.125");
  CHECK_EQ(fi4w( "0.049860201836332") / fi4w("-0.316092211717583"), "0.0");
  CHECK_EQ(fi4w("-0.355045201776273") / fi4w("-0.260047474335097"), "0.25");
  CHECK_EQ(fi4w( "0.353031117721894") / fi4w("-0.082732930915630"), "0.0");
  
  CHECK_EQ(fi4w( "0.122055131485066") / fi4w( "0.410647594429523"), "0.125");
  CHECK_EQ(fi4w("-0.149047619107729") / fi4w("-0.318152971697148"), "0.375");
  CHECK_EQ(fi4w( "0.013249539867053") / fi4w("-0.236197083478010"), "0.0");
  CHECK_EQ(fi4w("-0.098191966248058") / fi4w("-0.354461019615283"), "0.1875");
  CHECK_EQ(fi4w("-0.424033308309158") / fi4w("-0.363931441291336"), "0.1875");
  CHECK_EQ(fi4w("-0.260083846446342") / fi4w( "0.369292207640089"), "0.25");
  CHECK_EQ(fi4w("-0.376681065164834") / fi4w( "0.079704587365570"), "0.0");
  CHECK_EQ(fi4w("-0.260047474335097") / fi4w("-0.355045201776273"), "-0.25");
  CHECK_EQ(fi4w("-0.082732930915630") / fi4w( "0.353031117721894"), "-0.1875");

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

typedef Fi::Fixed<4, 4, Fi::SIGNED, Fi::Throw> fi4of;

BOOST_AUTO_TEST_SUITE(Throw)
BOOST_AUTO_TEST_CASE( overflowexception_flp_construction )
{
  BOOST_CHECK_THROW(fi4of(9.0)   , std::overflow_error);
  BOOST_CHECK_THROW(fi4of(7.9375), std::overflow_error);
  BOOST_CHECK_THROW(fi4of(1.0f)  , std::overflow_error);
  BOOST_CHECK_THROW(fi4of(0.5)   , std::overflow_error);
  CHECK_EQ(fi4of(0.4)   , "0.375");
  CHECK_EQ(fi4of(0.37)  , "0.3125");
  CHECK_EQ(fi4of(0.1875), "0.1875");
  CHECK_EQ(fi4of(0.1)   , "0.0625");
  CHECK_EQ(fi4of(0.0)   , "0.0");
  CHECK_EQ(fi4of(-0.0)  , "0.0");
  CHECK_EQ(fi4of(-0.1)   , "-0.0625");
  CHECK_EQ(fi4of(-0.1875), "-0.1875");
  CHECK_EQ(fi4of(-0.37)  , "-0.3125");
  CHECK_EQ(fi4of(-0.4)   , "-0.375");
  CHECK_EQ(fi4of(-0.5)   , "-0.5");
  BOOST_CHECK_THROW(fi4of(-1.0f)  , std::overflow_error);
  BOOST_CHECK_THROW(fi4of(-7.9375), std::overflow_error);
  BOOST_CHECK_THROW(fi4of(-9.0)   , std::overflow_error);

  CHECK_EQ(fi4of(-0.416178622003067), "-0.375" );
  CHECK_EQ(fi4of(-0.271023031283181), "-0.25"  );
  CHECK_EQ(fi4of( 0.413337361501670),  "0.375" );
  CHECK_EQ(fi4of(-0.347621981030777), "-0.3125");
  CHECK_EQ(fi4of( 0.325816977489547),  "0.3125");
  CHECK_EQ(fi4of( 0.038342435260057),  "0.0"   );
  BOOST_CHECK_THROW(fi4of( 0.5), std::overflow_error);
  CHECK_EQ(fi4of(-0.421824471246816), "-0.375" );
  CHECK_EQ(fi4of(-0.057321730224554),  "0.0"   );
  CHECK_EQ(fi4of(-0.393347229819416), "-0.375" );

}

BOOST_AUTO_TEST_CASE( overflowexception_str_construction )
{

  BOOST_CHECK_THROW(fi4of("9.0")   , std::overflow_error);
  BOOST_CHECK_THROW(fi4of("7.9375"), std::overflow_error);
  BOOST_CHECK_THROW(fi4of("1.0")  , std::overflow_error);
  BOOST_CHECK_THROW(fi4of("0.5")   , std::overflow_error);
  CHECK_EQ(fi4of("0.4")   , "0.375");
  CHECK_EQ(fi4of("0.37")  , "0.3125");
  CHECK_EQ(fi4of("0.1")   , "0.0625");
  CHECK_EQ(fi4of("0.0")   , "0.0");
  CHECK_EQ(fi4of("-0.0")  , "0.0");
  CHECK_EQ(fi4of("-0.1")   , "-0.0625");
  CHECK_EQ(fi4of("-0.37")  , "-0.3125");
  CHECK_EQ(fi4of("-0.4")   , "-0.375");
  CHECK_EQ(fi4of("-0.5")   , "-0.5");
  BOOST_CHECK_THROW(fi4of("-1.0")  , std::overflow_error);
  BOOST_CHECK_THROW(fi4of("-7.9375"), std::overflow_error);
  BOOST_CHECK_THROW(fi4of("-9.0")   , std::overflow_error);

  CHECK_EQ(fi4of("-0.416178622003067"), "-0.375" );
  CHECK_EQ(fi4of("-0.271023031283181"), "-0.25"  );
  CHECK_EQ(fi4of( "0.413337361501670"),  "0.375" );
  CHECK_EQ(fi4of("-0.347621981030777"), "-0.3125");
  CHECK_EQ(fi4of( "0.325816977489547"),  "0.3125");
  CHECK_EQ(fi4of( "0.038342435260057"),  "0.0"   );

  //> Ok due to rounding rule.
  CHECK_EQ(fi4of( "0.496134716626885"), "0.4375");
  CHECK_EQ(fi4of("-0.421824471246816"),"-0.375" );
  CHECK_EQ(fi4of("-0.057321730224554"), "0.0"   );
  CHECK_EQ(fi4of("-0.393347229819416"),"-0.375" );

  BOOST_CHECK_THROW(fi4of("abc"), std::invalid_argument);
  BOOST_CHECK_THROW(fi4of("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( overflowexception_add )
{

  CHECK_EQ(fi4of("-0.375")  + fi4of( "0.4375"),  "0.0625");
  BOOST_CHECK_THROW(fi4of("-0.25")   + fi4of("-0.4375"), std::overflow_error);
  BOOST_CHECK_THROW(fi4of( "0.375")  + fi4of( "0.25"),    std::overflow_error);
  CHECK_EQ(fi4of("-0.3125") + fi4of( "0.3125"),  "0.0");
  BOOST_CHECK_THROW(fi4of( "0.3125") + fi4of( "0.3125"),  std::overflow_error);
  CHECK_EQ(fi4of( "0.0")    + fi4of("-0.375"),  "-0.375");
  CHECK_EQ(fi4of( "0.4375") + fi4of("-0.0625"),  "0.375");
  BOOST_CHECK_THROW(fi4of("-0.375")  + fi4of("-0.1875"), std::overflow_error);
  CHECK_EQ(fi4of( "0.25")   + fi4of( "0.0"),     "0.25");
  CHECK_EQ(fi4of("-0.375")  + fi4of("-0.0625"), "-0.4375");

}

BOOST_AUTO_TEST_CASE( overflowexception_sub )
{

  BOOST_CHECK_THROW(fi4of("-0.375")  - fi4of( "0.4375"), std::overflow_error);
  CHECK_EQ(fi4of("-0.25")   - fi4of("-0.4375"),  "0.1875");
  CHECK_EQ(fi4of( "0.375")  - fi4of( "0.25"),    "0.125");
  BOOST_CHECK_THROW(fi4of("-0.3125") - fi4of( "0.3125"),  std::overflow_error);
  CHECK_EQ(fi4of( "0.3125") - fi4of( "0.3125"),  "0.0");
  CHECK_EQ(fi4of( "0.0")    - fi4of("-0.375"),  "0.375");
  BOOST_CHECK_THROW(fi4of( "0.4375") - fi4of("-0.0625"),  std::overflow_error);
  CHECK_EQ(fi4of("-0.375")  - fi4of("-0.1875"), "-0.1875");
  CHECK_EQ(fi4of( "0.0")    - fi4of( "0.25"),    "-0.25");
  CHECK_EQ(fi4of("-0.375")  - fi4of("-0.0625"), "-0.3125");

}

BOOST_AUTO_TEST_CASE( overflowexception_mul )
{

  //Directed
  CHECK_EQ(fi4of("0") * fi4of("0.234"), "0.0");
  CHECK_EQ(fi4of("-0.234") * fi4of("0.0"), "0.0");
 
  //Random

  CHECK_EQ(fi4of( "0.410647594429523") * fi4of( "0.122055131485066"), "0.0");
  CHECK_EQ(fi4of("-0.318152971697148") * fi4of("-0.149047619107729"), "0.0");
  CHECK_EQ(fi4of("-0.236197083478010") * fi4of( "0.013249539867053"), "0.0");
  CHECK_EQ(fi4of("-0.354461019615283") * fi4of("-0.098191966248058"), "0.0");
  CHECK_EQ(fi4of("-0.363931441291336") * fi4of("-0.424033308309158"), "0.0625");
  CHECK_EQ(fi4of( "0.369292207640089") * fi4of("-0.260083846446342"), "-0.0625");
  CHECK_EQ(fi4of( "0.079704587365570") * fi4of("-0.376681065164834"), "0.0");
  CHECK_EQ(fi4of( "0.049860201836332") * fi4of("-0.316092211717583"), "0.0");
  CHECK_EQ(fi4of("-0.355045201776273") * fi4of("-0.260047474335097"), "0.0625");
  CHECK_EQ(fi4of( "0.353031117721894") * fi4of("-0.082732930915630"), "0.0");
  
}

BOOST_AUTO_TEST_CASE( overflowexception_div )
{

  CHECK_EQ(fi4of("0") / fi4of("0.234"), "0.0");

  BOOST_CHECK_THROW(fi4of( "0.410647594429523") / fi4of( "0.122055131485066"), std::overflow_error);
  BOOST_CHECK_THROW(fi4of("-0.318152971697148") / fi4of("-0.149047619107729"), std::overflow_error);
  BOOST_CHECK_THROW(fi4of("-0.354461019615283") / fi4of("-0.098191966248058"), std::overflow_error);
  BOOST_CHECK_THROW(fi4of("-0.363931441291336") / fi4of("-0.424033308309158"), std::overflow_error);
  BOOST_CHECK_THROW(fi4of( "0.369292207640089") / fi4of("-0.260083846446342"), std::overflow_error);
  CHECK_EQ(fi4of( "0.079704587365570") / fi4of("-0.376681065164834"), "-0.125");
  CHECK_EQ(fi4of( "0.049860201836332") / fi4of("-0.316092211717583"), "0.0");
  BOOST_CHECK_THROW(fi4of("-0.355045201776273") / fi4of("-0.260047474335097"), std::overflow_error);
  BOOST_CHECK_THROW(fi4of( "0.353031117721894") / fi4of("-0.082732930915630"), std::overflow_error);
  
  CHECK_EQ(fi4of( "0.122055131485066") / fi4of( "0.410647594429523"), "0.125");
  CHECK_EQ(fi4of("-0.149047619107729") / fi4of("-0.318152971697148"), "0.375");
  CHECK_EQ(fi4of( "0.013249539867053") / fi4of("-0.236197083478010"), "0.0");
  CHECK_EQ(fi4of("-0.098191966248058") / fi4of("-0.354461019615283"), "0.1875");
  BOOST_CHECK_THROW(fi4of("-0.424033308309158") / fi4of("-0.363931441291336"), std::overflow_error);
  BOOST_CHECK_THROW(fi4of("-0.260083846446342") / fi4of( "0.369292207640089"), std::overflow_error);
  BOOST_CHECK_THROW(fi4of("-0.376681065164834") / fi4of( "0.079704587365570"), std::overflow_error);
  BOOST_CHECK_THROW(fi4of("-0.260047474335097") / fi4of("-0.355045201776273"), std::overflow_error);
  CHECK_EQ(fi4of("-0.082732930915630") / fi4of( "0.353031117721894"), "-0.1875");
  
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

