#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class TransformTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(TransformTest);
  CPPUNIT_TEST(trnsfrm1);
  CPPUNIT_TEST(trnsfrm2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void trnsfrm1();
  void trnsfrm2();

  static int negate_int(int a_)
  {
    return -a_;
  }
  static char map_char(char a_, int b_)
  {
    return char(a_ + b_);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TransformTest);

//
// tests implementation
//
void TransformTest::trnsfrm1()
{
  int numbers[6] = { -5, -1, 0, 1, 6, 11 };

  int result[6];
  transform((int*)numbers, (int*)numbers + 6, (int*)result, negate_int);

  CPPUNIT_ASSERT(result[0]==5);
  CPPUNIT_ASSERT(result[1]==1);
  CPPUNIT_ASSERT(result[2]==0);
  CPPUNIT_ASSERT(result[3]==-1);
  CPPUNIT_ASSERT(result[4]==-6);
  CPPUNIT_ASSERT(result[5]==-11);
}
void TransformTest::trnsfrm2()
{
#if defined (__MVS__)
  int trans[] = {-11, 4, -6, -6, -18, 0, 18, -14, 6, 0, -1, -59};
#else
  int trans[] = {-4, 4, -6, -6, -10, 0, 10, -6, 6, 0, -1, -77};
#endif
  char n[] = "Larry Mullen";
  const unsigned count = ::strlen(n);

  ostringstream os;
  ostream_iterator <char> iter(os);

  transform(n, n + count, trans, iter, map_char);

  stringbuf* buff=os.rdbuf();
  string result=buff->str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(), "Hello World!"))
}
