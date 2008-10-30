// -*- C++ -*- Time-stamp: <08/10/30 00:20:32 ptr>

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

#include "map_test.h"

//Has to be first for StackAllocator swap overload to be taken
//into account (at least using GCC 4.0.1)
#include "stack_allocator.h"

#include <set>
#include <algorithm>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(set_test::set1)
{
  set<int, less<int> > s;
  EXAM_CHECK (s.count(42) == 0);
  s.insert(42);
  EXAM_CHECK (s.count(42) == 1);
  s.insert(42);
  EXAM_CHECK (s.count(42) == 1);
  size_t count = s.erase(42);
  EXAM_CHECK (count == 1);

  return EXAM_RESULT;
}

int EXAM_IMPL(set_test::set2)
{
  typedef set<int, less<int> > int_set;
  int_set s;
  pair<int_set::iterator, bool> p = s.insert(42);
  EXAM_CHECK (p.second == true);
  p = s.insert(42);
  EXAM_CHECK (p.second == false);

  int array1 [] = { 1, 3, 6, 7 };
  s.insert(array1, array1 + 4);
  EXAM_CHECK (distance(s.begin(), s.end()) == 5);

  int_set s2;
  s2.swap(s);
  EXAM_CHECK (distance(s2.begin(), s2.end()) == 5);
  EXAM_CHECK (distance(s.begin(), s.end()) == 0);

  int_set s3;
  s3.swap(s);
  s3.swap(s2);
  EXAM_CHECK (distance(s.begin(), s.end()) == 0);
  EXAM_CHECK (distance(s2.begin(), s2.end()) == 0);
  EXAM_CHECK (distance(s3.begin(), s3.end()) == 5);

  return EXAM_RESULT;
}

int EXAM_IMPL(set_test::erase)
{
  set<int, less<int> > s;
  s.insert(1);
  s.erase(s.begin());
  EXAM_CHECK( s.empty() );

  size_t nb = s.erase(1);
  EXAM_CHECK(nb == 0);

  return EXAM_RESULT;
}

int EXAM_IMPL(set_test::insert)
{
  set<int> s;
  set<int>::iterator i = s.insert( s.end(), 0 );
  EXAM_CHECK( *i == 0 );

  return EXAM_RESULT;
}

int EXAM_IMPL(set_test::find)
{
  set<int> s;

  EXAM_CHECK( s.find(0) == s.end() );

  set<int> const& crs = s;

  EXAM_CHECK( crs.find(0) == crs.end() );

  return EXAM_RESULT;
}

int EXAM_IMPL(set_test::bounds)
{
  int array1 [] = { 1, 3, 6, 7 };
  set<int> s(array1, array1 + sizeof(array1) / sizeof(array1[0]));
  set<int> const& crs = s;

  set<int>::iterator sit;
  set<int>::const_iterator scit;
  pair<set<int>::iterator, set<int>::iterator> pit;
  pair<set<int>::const_iterator, set<int>::const_iterator> pcit;

  //Check iterator on mutable set
  sit = s.lower_bound(2);
  EXAM_CHECK( sit != s.end() );
  EXAM_CHECK( *sit == 3 );

  sit = s.upper_bound(5);
  EXAM_CHECK( sit != s.end() );
  EXAM_CHECK( *sit == 6 );

  pit = s.equal_range(6);
  EXAM_CHECK( pit.first != pit.second );
  EXAM_CHECK( pit.first != s.end() );
  EXAM_CHECK( *pit.first == 6 );
  EXAM_CHECK( pit.second != s.end() );
  EXAM_CHECK( *pit.second == 7 );

  pit = s.equal_range(4);
  EXAM_CHECK( pit.first == pit.second );
  EXAM_CHECK( pit.first != s.end() );
  EXAM_CHECK( *pit.first == 6 );
  EXAM_CHECK( pit.second != s.end() );
  EXAM_CHECK( *pit.second == 6 );

  //Check const_iterator on mutable set
  scit = s.lower_bound(2);
  EXAM_CHECK( scit != s.end() );
  EXAM_CHECK( *scit == 3 );

  scit = s.upper_bound(5);
  EXAM_CHECK( scit != s.end() );
  EXAM_CHECK( *scit == 6 );

  pcit = s.equal_range(6);
  EXAM_CHECK( pcit.first != pcit.second );
  EXAM_CHECK( pcit.first != s.end() );
  EXAM_CHECK( *pcit.first == 6 );
  EXAM_CHECK( pcit.second != s.end() );
  EXAM_CHECK( *pcit.second == 7 );

  //Check const_iterator on const set
  scit = crs.lower_bound(2);
  EXAM_CHECK( scit != crs.end() );
  EXAM_CHECK( *scit == 3 );

  scit = crs.upper_bound(5);
  EXAM_CHECK( scit != crs.end() );
  EXAM_CHECK( *scit == 6 );

  pcit = crs.equal_range(6);
  EXAM_CHECK( pcit.first != pcit.second );
  EXAM_CHECK( pcit.first != crs.end() );
  EXAM_CHECK( *pcit.first == 6 );
  EXAM_CHECK( pcit.second != crs.end() );
  EXAM_CHECK( *pcit.second == 7 );

  return EXAM_RESULT;
}


class SetTestClass {
public:
  SetTestClass (int data) : _data(data)
  {}

  int data() const {
    return _data;
  }

private:
  int _data;
};

#if !defined (STLPORT) || defined (_STLP_USE_NAMESPACES)
namespace std {
#endif
#if defined (STLPORT)
  _STLP_TEMPLATE_NULL
#else
  template <>
#endif
  struct less<SetTestClass> {
    bool operator () (SetTestClass const& lhs, SetTestClass const& rhs) const {
      return lhs.data() < rhs.data();
    }
  };
#if !defined (STLPORT) || defined (_STLP_USE_NAMESPACES)
}
#endif

int EXAM_IMPL(set_test::specialized_less)
{
  set<SetTestClass> s;
  s.insert(SetTestClass(1));
  s.insert(SetTestClass(3));
  s.insert(SetTestClass(2));
  s.insert(SetTestClass(0));

  set<SetTestClass>::iterator sit(s.begin()), sitEnd(s.end());
  int i = 0;
  for (; sit != sitEnd; ++sit, ++i) {
    EXAM_CHECK( sit->data() == i );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(set_test::implementation_check)
{
  set<int> tree;
  tree.insert(1);
  set<int>::iterator it = tree.begin();
  int const& int_ref = *it++;
  EXAM_CHECK( int_ref == 1 );

  EXAM_CHECK( it == tree.end() );
  EXAM_CHECK( it != tree.begin() );

  set<int>::const_iterator cit = tree.begin();
  int const& int_cref = *cit++;
  EXAM_CHECK( int_cref == 1 );

  return EXAM_RESULT;
}

int EXAM_IMPL(set_test::reverse_iterator_test)
{
  set<int> tree;
  tree.insert(1);
  tree.insert(2);

  {
    set<int>::reverse_iterator rit(tree.rbegin());
    EXAM_CHECK( *(rit++) == 2 );
    EXAM_CHECK( *(rit++) == 1 );
    EXAM_CHECK( rit == tree.rend() );
  }

  {
    set<int> const& ctree = tree;
    set<int>::const_reverse_iterator rit(ctree.rbegin());
    EXAM_CHECK( *(rit++) == 2 );
    EXAM_CHECK( *(rit++) == 1 );
    EXAM_CHECK( rit == ctree.rend() );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(set_test::allocator_with_state)
{
  char buf1[1024];
  StackAllocator<int> stack1(buf1, buf1 + sizeof(buf1));

  char buf2[1024];
  StackAllocator<int> stack2(buf2, buf2 + sizeof(buf2));

  int i;
  typedef set<int, less<int>, StackAllocator<int> > SetInt;
  less<int> intLess;

  {
    SetInt sint1(intLess, stack1);
    for (i = 0; i < 5; ++i)
      sint1.insert(i);
    SetInt sint1Cpy(sint1);

    SetInt sint2(intLess, stack2);
    for (; i < 10; ++i)
      sint2.insert(i);
    SetInt sint2Cpy(sint2);

    sint1.swap(sint2);

    EXAM_CHECK( sint1.get_allocator().swaped() );
    EXAM_CHECK( sint2.get_allocator().swaped() );

    EXAM_CHECK( sint1 == sint2Cpy );
    EXAM_CHECK( sint2 == sint1Cpy );
    EXAM_CHECK( sint1.get_allocator() == stack2 );
    EXAM_CHECK( sint2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();

  {
    SetInt sint1(intLess, stack1);
    SetInt sint1Cpy(sint1);

    SetInt sint2(intLess, stack2);
    for (i = 0; i < 10; ++i)
      sint2.insert(i);
    SetInt sint2Cpy(sint2);

    sint1.swap(sint2);

    EXAM_CHECK( sint1.get_allocator().swaped() );
    EXAM_CHECK( sint2.get_allocator().swaped() );

    EXAM_CHECK( sint1 == sint2Cpy );
    EXAM_CHECK( sint2 == sint1Cpy );
    EXAM_CHECK( sint1.get_allocator() == stack2 );
    EXAM_CHECK( sint2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();

  {
    SetInt sint1(intLess, stack1);
    for (i = 0; i < 10; ++i)
      sint1.insert(i);
    SetInt sint1Cpy(sint1);

    SetInt sint2(intLess, stack2);
    SetInt sint2Cpy(sint2);

    sint1.swap(sint2);

    EXAM_CHECK( sint1.get_allocator().swaped() );
    EXAM_CHECK( sint2.get_allocator().swaped() );

    EXAM_CHECK( sint1 == sint2Cpy );
    EXAM_CHECK( sint2 == sint1Cpy );
    EXAM_CHECK( sint1.get_allocator() == stack2 );
    EXAM_CHECK( sint2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();

  return EXAM_RESULT;
}

struct Key
{
  Key() : m_data(0) {}
  explicit Key(int data) : m_data(data) {}

  int m_data;
};

struct KeyCmp
{
  bool operator () (Key lhs, Key rhs) const
  { return lhs.m_data < rhs.m_data; }

  bool operator () (Key lhs, int rhs) const
  { return lhs.m_data < rhs; }

  bool operator () (int lhs, Key rhs) const
  { return lhs < rhs.m_data; }
};

struct KeyCmpPtr
{
  bool operator () (Key const volatile *lhs, Key const volatile *rhs) const
  { return (*lhs).m_data < (*rhs).m_data; }

  bool operator () (Key const volatile *lhs, int rhs) const
  { return (*lhs).m_data < rhs; }

  bool operator () (int lhs, Key const volatile *rhs) const
  { return lhs < (*rhs).m_data; }
};

int EXAM_IMPL(set_test::template_methods)
{
#if defined (STLPORT) && defined (_STLP_USE_CONTAINERS_EXTENSION)
  {
    typedef set<Key, KeyCmp> KeySet;
    KeySet keySet;
    keySet.insert(Key(1));
    keySet.insert(Key(2));
    keySet.insert(Key(3));
    keySet.insert(Key(4));

    EXAM_CHECK( keySet.count(Key(1)) == 1 );
    EXAM_CHECK( keySet.count(1) == 1 );
    EXAM_CHECK( keySet.count(5) == 0 );

    EXAM_CHECK( keySet.find(2) != keySet.end() );
    EXAM_CHECK( keySet.lower_bound(2) != keySet.end() );
    EXAM_CHECK( keySet.upper_bound(2) != keySet.end() );
    EXAM_CHECK( keySet.equal_range(2) != make_pair(keySet.begin(), keySet.end()) );

    KeySet const& ckeySet = keySet;
    EXAM_CHECK( ckeySet.find(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.lower_bound(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.upper_bound(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.equal_range(2) != make_pair(ckeySet.begin(), ckeySet.end()) );
  }

  {
    typedef set<Key*, KeyCmpPtr> KeySet;
    KeySet keySet;
    Key key1(1), key2(2), key3(3), key4(4);
    keySet.insert(&key1);
    keySet.insert(&key2);
    keySet.insert(&key3);
    keySet.insert(&key4);

    EXAM_CHECK( keySet.count(1) == 1 );
    EXAM_CHECK( keySet.count(5) == 0 );

    EXAM_CHECK( keySet.find(2) != keySet.end() );
    EXAM_CHECK( keySet.lower_bound(2) != keySet.end() );
    EXAM_CHECK( keySet.upper_bound(2) != keySet.end() );
    EXAM_CHECK( keySet.equal_range(2) != make_pair(keySet.begin(), keySet.end()) );

    KeySet const& ckeySet = keySet;
    EXAM_CHECK( ckeySet.find(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.lower_bound(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.upper_bound(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.equal_range(2) != make_pair(ckeySet.begin(), ckeySet.end()) );
  }
  {
    typedef multiset<Key, KeyCmp> KeySet;
    KeySet keySet;
    keySet.insert(Key(1));
    keySet.insert(Key(2));
    keySet.insert(Key(3));
    keySet.insert(Key(4));

    EXAM_CHECK( keySet.count(Key(1)) == 1 );
    EXAM_CHECK( keySet.count(1) == 1 );
    EXAM_CHECK( keySet.count(5) == 0 );

    EXAM_CHECK( keySet.find(2) != keySet.end() );
    EXAM_CHECK( keySet.lower_bound(2) != keySet.end() );
    EXAM_CHECK( keySet.upper_bound(2) != keySet.end() );
    EXAM_CHECK( keySet.equal_range(2) != make_pair(keySet.begin(), keySet.end()) );

    KeySet const& ckeySet = keySet;
    EXAM_CHECK( ckeySet.find(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.lower_bound(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.upper_bound(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.equal_range(2) != make_pair(ckeySet.begin(), ckeySet.end()) );
  }

  {
    typedef multiset<Key const volatile*, KeyCmpPtr> KeySet;
    KeySet keySet;
    Key key1(1), key2(2), key3(3), key4(4);
    keySet.insert(&key1);
    keySet.insert(&key2);
    keySet.insert(&key3);
    keySet.insert(&key4);

    EXAM_CHECK( keySet.count(1) == 1 );
    EXAM_CHECK( keySet.count(5) == 0 );

    EXAM_CHECK( keySet.find(2) != keySet.end() );
    EXAM_CHECK( keySet.lower_bound(2) != keySet.end() );
    EXAM_CHECK( keySet.upper_bound(2) != keySet.end() );
    EXAM_CHECK( keySet.equal_range(2) != make_pair(keySet.begin(), keySet.end()) );

    KeySet const& ckeySet = keySet;
    EXAM_CHECK( ckeySet.find(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.lower_bound(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.upper_bound(2) != ckeySet.end() );
    EXAM_CHECK( ckeySet.equal_range(2) != make_pair(ckeySet.begin(), ckeySet.end()) );
  }
#else
  throw exam::skip_exception();
#endif

  return EXAM_RESULT;
}

#if !defined (STLPORT) || \
    !defined (_STLP_USE_PTR_SPECIALIZATIONS) || defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
#  if !defined (__DMC__)
/* Simple compilation test: Check that nested types like iterator
 * can be access even if type used to instanciate container is not
 * yet completely defined.
 */
class IncompleteClass
{
  set<IncompleteClass> instances;
  typedef set<IncompleteClass>::iterator it;
  multiset<IncompleteClass> minstances;
  typedef multiset<IncompleteClass>::iterator mit;
};
#  endif
#endif
