#include <vector>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class BoundTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(BoundTest);
  CPPUNIT_TEST(lwrbnd1);
  CPPUNIT_TEST(lwrbnd2);
  CPPUNIT_TEST(uprbnd1);
  CPPUNIT_TEST(uprbnd2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void lwrbnd1();
  void lwrbnd2();
  void uprbnd1();
  void uprbnd2();

  static bool char_str_less(const char* a_, const char* b_)
  {
    return strcmp(a_, b_) < 0 ? 1 : 0;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(BoundTest);

//
// tests implementation
//
void BoundTest::uprbnd1()
{
  int array[20];
  for(int i = 0; i < 20; i++)
  {
    array[i] = i/4;
  }
  int location = upper_bound((int*)array, (int*)array + 20, 3) - array;
  CPPUNIT_ASSERT(location==16);
}
void BoundTest::uprbnd2()
{
  char* str [] = { "a", "a", "b", "b", "q", "w", "z" };

  const unsigned strCt = sizeof(str)/sizeof(str[0]);

  int location = (upper_bound((char**)str,  (char**)str + strCt, (const char *)"d", char_str_less) - str);
  CPPUNIT_ASSERT(location==4);
}
void BoundTest::lwrbnd1()
{
  std::vector <int> v1(20);
  for(size_t i = 0; i < v1.size(); i++)
  {
    v1[i] = i/4;
  }
  // 0 0 0 0 1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 
  std::vector<int>::iterator location = lower_bound(v1.begin(), v1.end(), 3);

  CPPUNIT_ASSERT((location - v1.begin())==12);
}
void BoundTest::lwrbnd2()
{
  char* str [] = { "a", "a", "b", "b", "q", "w", "z" };

  const unsigned strCt = sizeof(str)/sizeof(str[0]);
  char** location = lower_bound((char**)str,  (char**)str + strCt, (const char *)"d", char_str_less);

  CPPUNIT_ASSERT((location - str) == 4);
}
