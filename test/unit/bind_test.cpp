#include <algorithm>
#include <functional>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class BindTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(BindTest);
  CPPUNIT_TEST(bind1st1);
  CPPUNIT_TEST(bind2nd1);
  CPPUNIT_TEST(bind2nd2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void bind1st1();
  void bind2nd1();
  void bind2nd2();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BindTest);

//
// tests implementation
//
void BindTest::bind1st1()
{
  int array [3] = { 1, 2, 3 };
  int* p = remove_if((int*)array, (int*)array + 3, bind1st(less<int>(), 2));
  
  CPPUNIT_ASSERT(p==&array[2]);
  CPPUNIT_ASSERT(array[0]==1);
  CPPUNIT_ASSERT(array[1]==2);
}
void BindTest::bind2nd1()
{
  int array [3] = { 1, 2, 3 };
  replace_if(array, array + 3, binder2nd<greater<int> >(greater<int>(), 2), 4);

  CPPUNIT_ASSERT(array[0]==1);
  CPPUNIT_ASSERT(array[1]==2);
  CPPUNIT_ASSERT(array[2]==4);
}
void BindTest::bind2nd2()
{
  int array [3] = { 1, 2, 3 };
  replace_if(array, array + 3, bind2nd(greater<int>(), 2), 4);
  CPPUNIT_ASSERT(array[0]==1);
  CPPUNIT_ASSERT(array[1]==2);
  CPPUNIT_ASSERT(array[2]==4);
}
