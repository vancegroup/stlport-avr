#define _STLP_DO_IMPORT_CSTD_FUNCTIONS
#include <cmath>

#if !defined (STLPORT) || defined (_STLP_USE_NAMESPACES)

namespace NS1 {

bool f()
{
  double d( 1.0 );

  d = sqrt( d );
  d = ::sqrt( d );
#if !defined (STLPORT) || !defined (_STLP_MSVC) || (_STLP_MSVC >= 1300)
  //MSVC6 complains about ambiguity between the float and long double versions
  d = std::sqrt( d );
#endif
  return d == 1.0;
}

}

namespace {

bool g()
{
  double d( 1.0 );

  d = sqrt( d );
  d = ::sqrt( d );
#if !defined (STLPORT) || !defined (_STLP_MSVC) || (_STLP_MSVC >= 1300)
  //MSVC6 complains about ambiguity between the float and long double versions
  d = std::sqrt( d );
#endif
  return d == 1.0;
}

}

#if !defined (STLPORT) || !defined (_STLP_MSVC) || (_STLP_MSVC >= 1300) // I'm sorry, VC6 still can't resolve name below
using namespace std;
#endif

bool h()
{
  double d( 1.0 );

  d = sqrt( d );
  d = ::sqrt( d );
#if !defined (STLPORT) || !defined (_STLP_MSVC) || (_STLP_MSVC >= 1300)
  //MSVC6 complains about ambiguity between the float and long double versions
  d = std::sqrt( d );
#endif
  return d == 1.0;
}

struct sq
{
  sq() {}

  double sqroot( double x ) {
#if !defined (STLPORT) || !defined (_STLP_MSVC) || (_STLP_MSVC >= 1300)
    //MSVC6 complains about ambiguity between the float and long double versions
    using std::sqrt;
    return sqrt(x);
#endif
  }
};

#endif


#if 0 // Do nothing, this should be compiled only

#include "cppunit/cppunit_proxy.h"

class ResolveNameTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(ResolveNameTest);
  CPPUNIT_TEST(cstyle);
  CPPUNIT_TEST_SUITE_END();

protected:
  void cstyle();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ResolveNameTest);

void ResolveNameTest::cstyle()
{
}

#endif
