#include <deque>
#include <vector>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class AlgTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(AlgTest);
  CPPUNIT_TEST(alg1);
  CPPUNIT_TEST(alg2);
  CPPUNIT_TEST(alg3);
  CPPUNIT_TEST(alg4);
  CPPUNIT_TEST(alg5);
  CPPUNIT_TEST_SUITE_END();

protected:
  void alg1();
  void alg2();
  void alg3();
  void alg4();
  void alg5();
};

CPPUNIT_TEST_SUITE_REGISTRATION(AlgTest);

//
// tests implementation
//
void AlgTest::alg1()
{
  int i = min(4, 7);
  CPPUNIT_ASSERT(i==4);
  char c = max('a', 'z');
  CPPUNIT_ASSERT(c=='z');
}
void AlgTest::alg2()
{
  int n = 0;
  int i [] = { 1, 4, 2, 8, 2, 2 };
  count(i, i + 6, 2, n);
  CPPUNIT_ASSERT(n==3);
}
void AlgTest::alg3()
{
  int n=0;
  vector<int> i;
  i.push_back(1);
  i.push_back(4);
  i.push_back(2);
  i.push_back(8);
  i.push_back(2);
  i.push_back(2);
  count(i.begin(), i.end(), 2, n);
  CPPUNIT_ASSERT(n==3);
}
void AlgTest::alg4()
{
  vector<int> years;
  years.push_back(1962);
  years.push_back(1992);
  years.push_back(2001);
  years.push_back(1999);
  sort(years.begin(), years.end());
  CPPUNIT_ASSERT(years[0]=1962);
  CPPUNIT_ASSERT(years[1]=1992);
  CPPUNIT_ASSERT(years[2]=1999);
  CPPUNIT_ASSERT(years[3]=2001);
}
void AlgTest::alg5()
{
  deque<int> years;
  years.push_back(1962);
  years.push_back(1992);
  years.push_back(2001);
  years.push_back(1999);
  sort(years.begin(), years.end()); // <-- changed!
  CPPUNIT_ASSERT(years[0]=1962);
  CPPUNIT_ASSERT(years[1]=1992);
  CPPUNIT_ASSERT(years[2]=1999);
  CPPUNIT_ASSERT(years[3]=2001);
}
