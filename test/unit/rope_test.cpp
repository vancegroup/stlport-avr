//Small header to get STLport numerous defines:
#include <utility>

#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
#  include <rope>

#  if !defined (_STLP_USE_NO_IOSTREAMS)
#    include <sstream>
#  endif
#endif

#include "cppunit/cppunit_proxy.h"

#if defined (_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class RopeTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(RopeTest);
#if !defined (STLPORT) || defined (_STLP_NO_EXTENSIONS) || defined (_STLP_USE_NO_IOSTREAMS)
  CPPUNIT_IGNORE;
#endif
  CPPUNIT_TEST(io);
#if defined (_STLP_USE_NO_IOSTREAMS)
  CPPUNIT_STOP_IGNORE;
#endif
  CPPUNIT_TEST(find1);
  CPPUNIT_TEST(find2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void io();
  void find1();
  void find2();
};

CPPUNIT_TEST_SUITE_REGISTRATION(RopeTest);

//
// tests implementation
//
void RopeTest::io()
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS) && !defined (_STLP_USE_NO_IOSTREAMS) && \
    !defined (__DMC__)
  char const* cstr = "rope test string";
  crope rstr(cstr);

  {
    ostringstream ostr;
    ostr << rstr;

    CPPUNIT_ASSERT( ostr );
    CPPUNIT_ASSERT( ostr.str() == cstr );
  }
#endif
}

void RopeTest::find1()
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS) && \
    !defined (__DMC__)
  crope r("Fuzzy Wuzzy was a bear");
  crope::size_type n = r.find( "hair" );
  CPPUNIT_ASSERT( n == crope::npos );

  n = r.find("ear");

  CPPUNIT_ASSERT( n == (r.size() - 3) );
#endif
}

void RopeTest::find2()
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS) && \
    !defined (__DMC__)
  crope r("Fuzzy Wuzzy was a bear");
  crope::size_type n = r.find( 'e' );
  CPPUNIT_ASSERT( n == (r.size() - 3) );
#endif
}
