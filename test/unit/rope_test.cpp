//Small header to get STLport numerous defines:
#include <utility>

#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS) && !defined (__DMC__)
#  include <rope>

#  if !defined (_STLP_USE_NO_IOSTREAMS)
#    include <sstream>
#  endif

#  include "cppunit/cppunit_proxy.h"

#  if defined (_STLP_USE_NAMESPACES)
using namespace std;
#  endif

//
// TestCase class
//
class RopeTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(RopeTest);
#  if !defined (_STLP_USE_NO_IOSTREAMS)
  CPPUNIT_TEST(io);
#  endif
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
#  if !defined (_STLP_USE_NO_IOSTREAMS)
void RopeTest::io()
{
  char const* cstr = "rope test string";
  crope rstr(cstr);

  {
    ostringstream ostr;
    ostr << rstr;

    CPPUNIT_ASSERT( ostr );
    CPPUNIT_ASSERT( ostr.str() == cstr );
  }
}
#  endif

void RopeTest::find1()
{
  crope r("Fuzzy Wuzzy was a bear");
  crope::size_type n = r.find( "hair" );
  CPPUNIT_ASSERT( n == crope::npos );

  n = r.find("ear");

  CPPUNIT_ASSERT( n == (r.size() - 3) );
}

void RopeTest::find2()
{
  crope r("Fuzzy Wuzzy was a bear");
  crope::size_type n = r.find( 'e' );
  CPPUNIT_ASSERT( n == (r.size() - 3) );
}

#endif
