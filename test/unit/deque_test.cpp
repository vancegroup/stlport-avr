//Has to be first for StackAllocator swap overload to be taken
//into account (at least using GCC 4.0.1)
#include "stack_allocator.h"

#include <deque>
#include <algorithm>
#if defined (_STLP_USE_EXCEPTIONS)
# include <stdexcept>
#endif

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
  CPPUNIT_TEST(at);
  CPPUNIT_TEST(auto_ref);
  CPPUNIT_TEST(allocator_with_state);
  CPPUNIT_TEST_SUITE_END();

protected:
  void deque1();
  void at();
  void auto_ref();
  void allocator_with_state();
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
  CPPUNIT_ASSERT( (dit - cdit) == 0 );
  CPPUNIT_ASSERT( (cdit - dit) == 0 );
  CPPUNIT_ASSERT( (dit - dit) == 0 );
  CPPUNIT_ASSERT( (cdit - cdit) == 0 );
  CPPUNIT_ASSERT(!((dit < cdit) || (dit > cdit) || (dit != cdit) || !(dit <= cdit) || !(dit >= cdit)));
}

void DequeTest::at() {
  deque<int> d;
  deque<int> const& cd = d;

  d.push_back(10);
  CPPUNIT_ASSERT( d.at(0) == 10 );
  d.at(0) = 20;
  CPPUNIT_ASSERT( cd.at(0) == 20 );

#if defined (_STLP_USE_EXCEPTIONS)
  for (;;) {
    try {
      d.at(1) = 20;
      CPPUNIT_ASSERT(false);
    }
    catch (std::out_of_range const&) {
      CPPUNIT_ASSERT(true);
      return;
    }
    catch (...) {
      CPPUNIT_ASSERT(false);
      return;
    }
  }
#endif
}

void DequeTest::auto_ref()
{
  int i;
  deque<int> ref;
  for (i = 0; i < 5; ++i) {
    ref.push_back(i);
  }

  deque<deque<int> > d_d_int(1, ref);
  d_d_int.push_back(d_d_int[0]);
  d_d_int.push_back(ref);
  d_d_int.push_back(d_d_int[0]);
  d_d_int.push_back(d_d_int[0]);
  d_d_int.push_back(ref);

  for (i = 0; i < 5; ++i) {
    CPPUNIT_ASSERT( d_d_int[i] == ref );
  }
}

void DequeTest::allocator_with_state()
{
  char buf1[1024];
  StackAllocator<int> stack1(buf1, buf1 + sizeof(buf1));

  char buf2[1024];
  StackAllocator<int> stack2(buf2, buf2 + sizeof(buf2));

  {
    typedef deque<int, StackAllocator<int> > DequeInt;
    DequeInt dint1(10, 0, stack1);
    DequeInt dint1Cpy(dint1);

    DequeInt dint2(10, 1, stack2);
    DequeInt dint2Cpy(dint2);

    dint1.swap(dint2);

    CPPUNIT_ASSERT( dint1.get_allocator().swaped() );
    CPPUNIT_ASSERT( dint2.get_allocator().swaped() );

    CPPUNIT_ASSERT( dint1 == dint2Cpy );
    CPPUNIT_ASSERT( dint2 == dint1Cpy );
    CPPUNIT_ASSERT( dint1.get_allocator() == stack2 );
    CPPUNIT_ASSERT( dint2.get_allocator() == stack1 );
  }
  CPPUNIT_ASSERT( stack1.ok() );
  CPPUNIT_ASSERT( stack2.ok() );
}
