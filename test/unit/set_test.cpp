#include <set>
#include <vector>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class SetTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(SetTest);
  CPPUNIT_TEST(set1);
  CPPUNIT_TEST(set2);
  CPPUNIT_TEST(erase);
  CPPUNIT_TEST_SUITE_END();

protected:
  void set1();
  void set2();
  void erase();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SetTest);

//
// tests implementation
//
void SetTest::set1()
{
  set<int, less<int> > s;
  CPPUNIT_ASSERT (s.count(42) == 0);
  s.insert(42);
  CPPUNIT_ASSERT (s.count(42) == 1);
  s.insert(42);
  CPPUNIT_ASSERT (s.count(42) == 1);
  int count = s.erase(42);
  CPPUNIT_ASSERT (count == 1);
}
void SetTest::set2()
{
  typedef set<int, less<int> > int_set;
  int_set s;
  pair<int_set::const_iterator, bool> p = s.insert(42);
  CPPUNIT_ASSERT (p.second == true);
  p = s.insert(42);
  CPPUNIT_ASSERT (p.second == false);

  int array1 [] = { 1, 3, 6, 7 };
  s.insert(array1, array1 + 4);
  CPPUNIT_ASSERT (distance(s.begin(), s.end()) == 5);

  int_set s2;
  s2.swap(s);
  CPPUNIT_ASSERT (distance(s2.begin(), s2.end()) == 5);
  CPPUNIT_ASSERT (distance(s.begin(), s.end()) == 0);

  int_set s3;
  s3.swap(s);
  s3.swap(s2);
  CPPUNIT_ASSERT (distance(s.begin(), s.end()) == 0);
  CPPUNIT_ASSERT (distance(s2.begin(), s2.end()) == 0);
  CPPUNIT_ASSERT (distance(s3.begin(), s3.end()) == 5);
}

void SetTest::erase()
{
  set<int, less<int> > s;
  s.insert(1);
  s.erase(s.begin());
  CPPUNIT_ASSERT( s.empty() );
  
  unsigned int nb = s.erase(1);
  CPPUNIT_ASSERT(nb == 0);
}

