#include <deque>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class DequeTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(DequeTest);
  CPPUNIT_TEST(deque1);
  CPPUNIT_TEST_SUITE_END();

protected:
  void deque1();
};

CPPUNIT_TEST_SUITE_REGISTRATION(DequeTest);

//
// tests implementation
//
void DequeTest::deque1()
{
  deque<int> d;
  d.push_back(4);
  d.push_back(9);
  d.push_back(16);
  d.push_front(1);

  CPPUNIT_ASSERT(d[0]==1);
  CPPUNIT_ASSERT(d[1]==4);
  CPPUNIT_ASSERT(d[2]==9);
  CPPUNIT_ASSERT(d[3]==16);

  d.pop_front();
  d[2] = 25;

  CPPUNIT_ASSERT(d[0]==4);
  CPPUNIT_ASSERT(d[1]==9);
  CPPUNIT_ASSERT(d[2]==25);

  //Some compile time tests:
  deque<int>::iterator dit(d.begin());
  deque<int>::const_iterator cdit(d.begin());
  size_t nb;
  nb = dit - cdit;
  nb = cdit - dit;
  nb = dit - dit;
  nb = cdit - cdit;
  CPPUNIT_ASSERT(!((dit < cdit) || (dit > cdit) || (dit != cdit) || !(dit <= cdit) || !(dit >= cdit)));
}
