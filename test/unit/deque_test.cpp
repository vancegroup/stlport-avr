// -*- C++ -*- Time-stamp: <08/10/27 09:34:20 ptr>

/*
 * Copyright (c) 2004-2008
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#include "deque_test.h"

//Has to be first for StackAllocator swap overload to be taken
//into account (at least using GCC 4.0.1)
#include "stack_allocator.h"

#include <deque>
#include <queue>
#include <stack>

#include <algorithm>
#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
# include <stdexcept>
#endif

#include <type_traits>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(deque_test::deque1)
{
  deque<int> d;
  d.push_back(4);
  d.push_back(9);
  d.push_back(16);
  d.push_front(1);

  EXAM_CHECK( d[0] == 1 );
  EXAM_CHECK( d[1] == 4 );
  EXAM_CHECK( d[2] == 9 );
  EXAM_CHECK( d[3] == 16 );

  d.pop_front();
  d[2] = 25;

  EXAM_CHECK( d[0] == 4 );
  EXAM_CHECK( d[1] == 9 );
  EXAM_CHECK( d[2] == 25 );

  //Some compile time tests:
  deque<int>::iterator dit = d.begin();
  deque<int>::const_iterator cdit(d.begin());
  EXAM_CHECK( (dit - cdit) == 0 );
  EXAM_CHECK( (cdit - dit) == 0 );
  EXAM_CHECK( (dit - dit) == 0 );
  EXAM_CHECK( (cdit - cdit) == 0 );
  EXAM_CHECK(!((dit < cdit) || (dit > cdit) || (dit != cdit) || !(dit <= cdit) || !(dit >= cdit)));

  return EXAM_RESULT;
}

int EXAM_IMPL(deque_test::insert)
{
  deque<int> d;
  d.push_back(0);
  d.push_back(1);
  d.push_back(2);
  EXAM_CHECK( d.size() == 3 );

  deque<int>::iterator dit;

  //Insertion before begin:
  dit = d.insert(d.begin(), 3);
  EXAM_CHECK( dit != d.end() );
  EXAM_CHECK( *dit == 3 );
  EXAM_CHECK( d.size() == 4 );
  EXAM_CHECK( d[0] == 3 );

  //Insertion after begin:
  dit = d.insert(d.begin() + 1, 4);
  EXAM_CHECK( dit != d.end() );
  EXAM_CHECK( *dit == 4 );
  EXAM_CHECK( d.size() == 5 );
  EXAM_CHECK( d[1] == 4 );

  //Insertion at end:
  dit = d.insert(d.end(), 5);
  EXAM_CHECK( dit != d.end() );
  EXAM_CHECK( *dit == 5 );
  EXAM_CHECK( d.size() == 6 );
  EXAM_CHECK( d[5] == 5 );

  //Insertion before last element:
  dit = d.insert(d.end() - 1, 6);
  EXAM_CHECK( dit != d.end() );
  EXAM_CHECK( *dit == 6 );
  EXAM_CHECK( d.size() == 7 );
  EXAM_CHECK( d[5] == 6 );

  //Insertion of several elements before begin
  d.insert(d.begin(), 2, 7);
  EXAM_CHECK( d.size() == 9 );
  EXAM_CHECK( d[0] == 7 );
  EXAM_CHECK( d[1] == 7 );

  //Insertion of several elements after begin
  //There is more elements to insert than elements before insertion position
  d.insert(d.begin() + 1, 2, 8);
  EXAM_CHECK( d.size() == 11 );
  EXAM_CHECK( d[1] == 8 );
  EXAM_CHECK( d[2] == 8 );

  //There is less elements to insert than elements before insertion position
  d.insert(d.begin() + 3, 2, 9);
  EXAM_CHECK( d.size() == 13 );
  EXAM_CHECK( d[3] == 9 );
  EXAM_CHECK( d[4] == 9 );

  //Insertion of several elements at end:
  d.insert(d.end(), 2, 10);
  EXAM_CHECK( d.size() == 15 );
  EXAM_CHECK( d[14] == 10 );
  EXAM_CHECK( d[13] == 10 );

  //Insertion of several elements before last:
  //There is more elements to insert than elements after insertion position
  d.insert(d.end() - 1, 2, 11);
  EXAM_CHECK( d.size() == 17 );
  EXAM_CHECK( d[15] == 11 );
  EXAM_CHECK( d[14] == 11 );

  //There is less elements to insert than elements after insertion position
  d.insert(d.end() - 3, 2, 12);
  EXAM_CHECK( d.size() == 19 );
  EXAM_CHECK( d[15] == 12 );
  EXAM_CHECK( d[14] == 12 );

  return EXAM_RESULT;
}

int EXAM_IMPL(deque_test::at)
{
  deque<int> d;
  deque<int> const& cd = d;

  d.push_back(10);
  EXAM_CHECK( d.at(0) == 10 );
  d.at(0) = 20;
  EXAM_CHECK( cd.at(0) == 20 );

#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    d.at(1) = 20;
    EXAM_ERROR( "out_of_range exception expected" );
  }
  catch ( out_of_range const& ) {
    EXAM_MESSAGE( "out_of_range exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "out_of_range exception expected" );
  }
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(deque_test::auto_ref)
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
    EXAM_CHECK( d_d_int[i] == ref );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(deque_test::allocator_with_state)
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

    EXAM_CHECK( dint1.get_allocator().swaped() );
    EXAM_CHECK( dint2.get_allocator().swaped() );

    EXAM_CHECK( dint1 == dint2Cpy );
    EXAM_CHECK( dint2 == dint1Cpy );
    EXAM_CHECK( dint1.get_allocator() == stack2 );
    EXAM_CHECK( dint2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );

  return EXAM_RESULT;
}

struct Point {
  int x, y;
};

struct PointEx : public Point {
  PointEx() : builtFromBase(false) {}
  PointEx(const Point&) : builtFromBase(true) {}

  bool builtFromBase;
};

#if defined (STLPORT)
#  if defined (_STLP_USE_NAMESPACES)
namespace std {
#  endif
namespace tr1 {

  template <>
  struct has_trivial_default_constructor<PointEx> :
        public false_type
  { };

  template <>
  struct has_trivial_copy_constructor<PointEx> :
        public true_type
  { };

  template <>
  struct has_trivial_assign<PointEx> :
        public true_type
  { };

  template <>
  struct has_trivial_destructor<PointEx> :
        public true_type
  { };
} // namespace tr1

#  if defined (_STLP_USE_NAMESPACES)
}
#  endif
#endif

//This test check that deque implementation do not over optimize
//operation as PointEx copy constructor is trivial
int EXAM_IMPL(deque_test::optimizations_check)
{
  deque<Point> d1(1);
  EXAM_CHECK( d1.size() == 1 );

  deque<PointEx> d2(d1.begin(), d1.end());
  EXAM_CHECK( d2.size() == 1 );
  EXAM_CHECK( d2[0].builtFromBase == true );

  d2.insert(d2.end(), d1.begin(), d1.end());
  EXAM_CHECK( d2.size() == 2 );
  EXAM_CHECK( d2[1].builtFromBase == true );

  return EXAM_RESULT;
}

int EXAM_IMPL(deque_test::erase)
{
  deque<int> dint;
  dint.push_back(3);
  dint.push_front(2);
  dint.push_back(4);
  dint.push_front(1);
  dint.push_back(5);
  dint.push_front(0);
  dint.push_back(6);

  deque<int>::iterator it(dint.begin() + 1);
  EXAM_CHECK( *it == 1 );

  dint.erase(dint.begin());
  EXAM_CHECK( *it == 1 );

  it = dint.end() - 2;
  EXAM_CHECK( *it == 5 );

  dint.erase(dint.end() - 1);
  EXAM_CHECK( *it == 5 );

  dint.push_back(6);
  dint.push_front(0);

  it = dint.begin() + 2;
  EXAM_CHECK( *it == 2 );

  dint.erase(dint.begin(), dint.begin() + 2);
  EXAM_CHECK( *it == 2 );

  it = dint.end() - 3;
  EXAM_CHECK( *it == 4 );

  dint.erase(dint.end() - 2, dint.end());
  EXAM_CHECK( *it == 4 );

  return EXAM_RESULT;
}

#if (!defined (STLPORT) || \
    (!defined (_STLP_USE_PTR_SPECIALIZATIONS) || defined (_STLP_CLASS_PARTIAL_SPECIALIZATION))) && \
     (!defined (_MSC_VER) || (_MSC_VER > 1400)) && \
     (!defined(__GNUC__) || (__GNUC__ < 4) || (__GNUC_MINOR__ < 3))
/* Simple compilation test: Check that nested types like iterator
 * can be access even if type used to instanciate container is not
 * yet completely defined.
 */
class IncompleteClass
{
  deque<IncompleteClass> instances;
  typedef deque<IncompleteClass>::size_type size;
};
#endif

int EXAM_IMPL(queue_test::pqueue1)
{
  priority_queue<int, deque<int>, less<int> > q;
  q.push(42);
  q.push(101);
  q.push(69);

  EXAM_CHECK( q.top()==101 );
  q.pop();
  EXAM_CHECK( q.top()==69 );
  q.pop();
  EXAM_CHECK( q.top()==42 );
  q.pop();

  EXAM_CHECK(q.empty());

  return EXAM_RESULT;
}

int EXAM_IMPL(queue_test::queue1)
{
  queue<int, list<int> > q;
  q.push(42);
  q.push(101);
  q.push(69);

  EXAM_CHECK( q.front()==42 );
  q.pop();
  EXAM_CHECK( q.front()==101 );
  q.pop();
  EXAM_CHECK( q.front()==69 );
  q.pop();

  EXAM_CHECK(q.empty());

  return EXAM_RESULT;
}

int EXAM_IMPL(stack_test::stack1)
{
  stack<int, deque<int> > s;
  s.push(42);
  s.push(101);
  s.push(69);
  EXAM_CHECK(s.top()==69);
  s.pop();
  EXAM_CHECK(s.top()==101);
  s.pop();
  EXAM_CHECK(s.top()==42);
  s.pop();
  EXAM_CHECK(s.empty());

  return EXAM_RESULT;
}

int EXAM_IMPL(stack_test::stack2)
{
  stack<int, list<int> > s;
  s.push(42);
  s.push(101);
  s.push(69);
  EXAM_CHECK(s.top()==69);
  s.pop();
  EXAM_CHECK(s.top()==101);
  s.pop();
  EXAM_CHECK(s.top()==42);
  s.pop();
  EXAM_CHECK(s.empty());

  return EXAM_RESULT;
}
