// -*- C++ -*- Time-stamp: <2010-11-17 13:52:40 ptr>

/*
 * Copyright (c) 2004-2009, 2010
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

//Has to be first for StackAllocator swap overload to be taken
//into account (at least using GCC 4.0.1)
#include "stack_allocator.h"

#include "list_test.h"

#include <list>
#include <algorithm>
#include <functional>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(list_test::list1)
{
  int array1 [] = { 9, 16, 36 };
  int array2 [] = { 1, 4 };

  list<int> l1(array1, array1 + 3);
  list<int> l2(array2, array2 + 2);
  list<int>::iterator i1 = l1.begin();
  list<int>::iterator i2 = l2.begin();
  list<int>::const_iterator ci(i1);
  list<int>::const_iterator ci1(ci);
  l1.splice(i1, l2);
  i1 = l1.begin();
  EXAM_CHECK( *i1++ == 1 );
  EXAM_CHECK( *i1++ == 4 );
  EXAM_CHECK( *i1++ == 9 );
  EXAM_CHECK( *i1++ == 16 );
  EXAM_CHECK( *i1++ == 36 );

#if defined (STLPORT) && \
   (!defined (_STLP_DEBUG) || (_STLP_DEBUG_LEVEL != _STLP_STANDARD_DBG_LEVEL))
  EXAM_CHECK( i2 == l1.begin() );
#endif

  //Default construct check (_STLP_DEF_CONST_PLCT_NEW_BUG)
  list<int> l(2);
  i1 = l.begin();
  EXAM_CHECK( *(i1++) == 0 );
  EXAM_CHECK( *i1 == 0 );
#if 0
  //A small compilation time check to be activated from time to time,
  //compilation should fail.
  {
    list<char>::iterator l_char_ite;
    list<int>::iterator l_int_ite;
    EXAM_CHECK( l_char_ite != l_int_ite );
  }
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(list_test::list2)
{
  int array1 [] = { 1, 16 };
  int array2 [] = { 4, 9 };

  list<int> l1(array1, array1 + 2);
  list<int> l2(array2, array2 + 2);
  list<int>::iterator i = l1.begin();
  i++;
  l1.splice(i, l2, l2.begin(), l2.end());
  i = l1.begin();
  EXAM_CHECK(*i++==1);
  EXAM_CHECK(*i++==4);
  EXAM_CHECK(*i++==9);
  EXAM_CHECK(*i++==16);

  return EXAM_RESULT;
}

int EXAM_IMPL(list_test::list3)
{
  char array [] = { 'x', 'l', 'x', 't', 's', 's' };

  list<char> str(array, array + 6);
  list<char>::iterator i;

  str.reverse();
  i = str.begin();
  EXAM_CHECK(*i++=='s');
  EXAM_CHECK(*i++=='s');
  EXAM_CHECK(*i++=='t');
  EXAM_CHECK(*i++=='x');
  EXAM_CHECK(*i++=='l');
  EXAM_CHECK(*i++=='x');

  str.remove('x');
  i = str.begin();
  EXAM_CHECK(*i++=='s');
  EXAM_CHECK(*i++=='s');
  EXAM_CHECK(*i++=='t');
  EXAM_CHECK(*i++=='l');

  str.unique();
  i = str.begin();
  EXAM_CHECK(*i++=='s');
  EXAM_CHECK(*i++=='t');
  EXAM_CHECK(*i++=='l');

  str.sort();
  i = str.begin();
  EXAM_CHECK(*i++=='l');
  EXAM_CHECK(*i++=='s');
  EXAM_CHECK(*i++=='t');

  return EXAM_RESULT;
}

int EXAM_IMPL(list_test::list4)
{
  int array1 [] = { 1, 3, 6, 7 };
  int array2 [] = { 2, 4 };

  list<int> l1(array1, array1 + 4);
  list<int> l2(array2, array2 + 2);
  l1.merge(l2);
  list<int>::iterator i = l1.begin();
  EXAM_CHECK(*i++==1);
  EXAM_CHECK(*i++==2);
  EXAM_CHECK(*i++==3);
  EXAM_CHECK(*i++==4);
  EXAM_CHECK(*i++==6);
  EXAM_CHECK(*i++==7);

  //We use distance to avoid a simple call to an internal counter
  EXAM_CHECK(distance(l1.begin(), l1.end()) == 6);
  EXAM_CHECK(distance(l2.begin(), l2.end()) == 0);

  l1.swap(l2);

  EXAM_CHECK(distance(l1.begin(), l1.end()) == 0);
  EXAM_CHECK(distance(l2.begin(), l2.end()) == 6);

  return EXAM_RESULT;
}

int EXAM_IMPL(list_test::erase)
{
  list<int> l;
  l.push_back( 1 );
  l.erase(l.begin());
  EXAM_CHECK( l.empty() );

  int array[] = { 0, 1, 2, 3 };
  l.assign(array, array + 4);
  list<int>::iterator lit;
  lit = l.erase(l.begin());
  EXAM_CHECK( *lit == 1 );

  lit = l.erase(l.begin(), --l.end());
  EXAM_CHECK( *lit == 3 );

  l.clear();
  EXAM_CHECK( l.empty() );

  return EXAM_RESULT;
}


int EXAM_IMPL(list_test::resize)
{
  {
    list<int> l;
    l.resize(5, 1);

    size_t i;
    list<int>::iterator lit(l.begin());
    for (i = 0; i < 5; ++i) {
      EXAM_CHECK( lit != l.end() );
      EXAM_CHECK( *(lit++) == 1 );
    }
    EXAM_CHECK( lit == l.end() );

    l.resize(3);
    lit = l.begin();
    for (i = 0; i < 3; ++i) {
      EXAM_CHECK( lit != l.end() );
      EXAM_CHECK( *(lit++) == 1 );
    }
    EXAM_CHECK( lit == l.end() );
  }

  {
    list<int> l;
    l.resize(5);

    size_t i;
    list<int>::iterator lit(l.begin());
    for (i = 0; i < 5; ++i) {
      EXAM_CHECK( lit != l.end() );
      EXAM_CHECK( *(lit++) == 0 );
    }
    EXAM_CHECK( lit == l.end() );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(list_test::push_back)
{
  list<int> l;
  l.push_back( 1 );
  l.push_back( 2 );
  l.push_back( 3 );

  list<int>::reverse_iterator r = l.rbegin();

  EXAM_CHECK( *r == 3 );
  l.push_back( 4 );
  /*
   * Following lines are commented, because ones show standard contradiction
   * (24.4.1 and 23.2.2.3); but present behaviour is valid, 24.4.1, paragraphs 1 and 2,
   * 24.4.1.3.3 and 23.1 paragraph 9 (Table 66). The 24.4.1 is more common rule,
   * so it has preference under 23.2.2.3, by my opinion.
   *
   *      - ptr
   */
  // EXAM_CHECK( *r == 3 );
  // ++r;
  // EXAM_CHECK( *r == 2 );

  return EXAM_RESULT;
}

int EXAM_IMPL(list_test::push_front)
{
  list<int> l;
  l.push_back( 1 );
  l.push_back( 2 );
  l.push_back( 3 );

  list<int>::iterator i = l.begin();

  EXAM_CHECK( *i == 1 );
  l.push_front( 0 );
  EXAM_CHECK( *i == 1 );
  ++i;
  EXAM_CHECK( *i == 2 );

  return EXAM_RESULT;
}

int EXAM_IMPL(list_test::allocator_with_state)
{
  char buf1[1024];
  StackAllocator<int> stack1(buf1, buf1 + sizeof(buf1));

  char buf2[1024];
  StackAllocator<int> stack2(buf2, buf2 + sizeof(buf2));

  typedef list<int, StackAllocator<int> > ListInt;
  {
    //Swap with both list non empty
    ListInt lint1(10, 0, stack1);
    ListInt lint1Cpy(lint1);

    ListInt lint2(10, 1, stack2);
    ListInt lint2Cpy(lint2);

    lint1.swap(lint2);

    EXAM_CHECK( lint1.get_allocator().swaped() );
    EXAM_CHECK( lint2.get_allocator().swaped() );

    EXAM_CHECK( lint1 == lint2Cpy );
    EXAM_CHECK( lint2 == lint1Cpy );
    EXAM_CHECK( lint1.get_allocator() == stack2 );
    EXAM_CHECK( lint2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();

  {
    //Swap with empty calle list
    ListInt lint1(10, 0, stack1);
    ListInt lint1Cpy(lint1);

    ListInt lint2(stack2);
    ListInt lint2Cpy(lint2);

    lint1.swap(lint2);

    EXAM_CHECK( lint1.get_allocator().swaped() );
    EXAM_CHECK( lint2.get_allocator().swaped() );

    EXAM_CHECK( lint1 == lint2Cpy );
    EXAM_CHECK( lint2 == lint1Cpy );
    EXAM_CHECK( lint1.get_allocator() == stack2 );
    EXAM_CHECK( lint2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();

  {
    //Swap with empty caller list
    ListInt lint1(stack1);
    ListInt lint1Cpy(lint1);

    ListInt lint2(10, 0, stack2);
    ListInt lint2Cpy(lint2);

    lint1.swap(lint2);

    EXAM_CHECK( lint1.get_allocator().swaped() );
    EXAM_CHECK( lint2.get_allocator().swaped() );

    EXAM_CHECK( lint1 == lint2Cpy );
    EXAM_CHECK( lint2 == lint1Cpy );
    EXAM_CHECK( lint1.get_allocator() == stack2 );
    EXAM_CHECK( lint2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();

  {
    ListInt lint1(10, 0, stack1);
    ListInt lint2(10, 1, stack2);

    lint1.splice(lint1.begin(), lint2);
    EXAM_CHECK( lint1.size() == 20 );
    EXAM_CHECK( lint2.empty() );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();

  {
    ListInt lint1(10, 0, stack1);
    ListInt lint2(10, 1, stack2);

    lint1.splice(lint1.begin(), lint2, lint2.begin());
    EXAM_CHECK( lint1.size() == 11 );
    EXAM_CHECK( lint2.size() == 9 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();

  {
    ListInt lint1(10, 0, stack1);
    ListInt lint2(10, 1, stack2);

    ListInt::iterator lit(lint2.begin());
    advance(lit, 5);
    lint1.splice(lint1.begin(), lint2, lint2.begin(), lit);
    EXAM_CHECK( lint1.size() == 15 );
    EXAM_CHECK( lint2.size() == 5 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();

  {
    ListInt lint1(10, 0, stack1);
    ListInt lint2(10, 1, stack2);

    ListInt lintref(stack2);
    lintref.insert(lintref.begin(), 10, 1);
    lintref.insert(lintref.begin(), 10, 0);

    lint1.merge(lint2);
    EXAM_CHECK( lint1.size() == 20 );
    EXAM_CHECK( lint1 == lintref );
    EXAM_CHECK( lint2.empty() );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );

#if defined (STLPORT) && \
    (!defined (_MSC_VER) || (_MSC_VER >= 1300))
  {
    //This is a compile time test.
    //We check that sort implementation is correct when list is instanciated
    //with an allocator that do not have a default constructor.
    ListInt lint1(10, 0, stack1);
    lint1.sort();
    lint1.sort(greater<int>());
  }
#endif

  return EXAM_RESULT;
}

/*
int EXAM_IMPL(list_test::const_list)
{
  list<const int> cint_list;
  cint_list.push_back(1);
  cint_list.push_front(2);

  return EXAM_RESULT;
}
*/

int EXAM_IMPL(list_test::swap)
{
  list<int> lst1;
  list<int> lst2;

  lst1.push_back(1);
  lst2.push_back(2);

  lst1.swap( lst2 );

  EXAM_CHECK( lst1.front() == 2 );
  EXAM_CHECK( lst2.front() == 1 );
  EXAM_CHECK( lst1.size() == 1 );
  EXAM_CHECK( lst2.size() == 1 );

  lst1.pop_front();
  lst2.pop_front();

  EXAM_CHECK( lst1.empty() );
  EXAM_CHECK( lst2.empty() );

  return EXAM_RESULT;
}

namespace foo {
  class bar {};

  template <class _It>
  size_t distance(_It, _It);
}

int EXAM_IMPL(list_test::adl)
{
  list<foo::bar> lbar;
  EXAM_CHECK( lbar.size() == 0);

  return EXAM_RESULT;
}

#if !defined (STLPORT) || \
    !defined (_STLP_USE_PTR_SPECIALIZATIONS) || defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
/* Simple compilation test: Check that nested types like iterator
 * can be access even if type used to instanciate container is not
 * yet completely defined.
 */
class IncompleteClass
{
  list<IncompleteClass> instances;
  typedef list<IncompleteClass>::iterator it;
};
#endif

int EXAM_IMPL(list_test::insert)
{
  list<int> l;

  l.insert( l.end(), 0 );
  l.insert( l.end(), 1 );

  list<int>::const_iterator i = l.begin();

  EXAM_CHECK( *i == 0 );

  ++i;

  EXAM_CHECK( *i == 1 );

  return EXAM_RESULT;
}
