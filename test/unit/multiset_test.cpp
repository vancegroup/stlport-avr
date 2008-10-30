// -*- C++ -*- Time-stamp: <08/10/30 00:29:04 ptr>

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

#include <set>
#include <functional>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

typedef multiset<int, less<int> > mset;

static bool less_than(int a_, int b_)
{
  return a_ < b_;
}

static bool greater_than(int a_, int b_)
{
  return a_ > b_;
}

int EXAM_IMPL(multiset_test::mset1)
{
  mset s;
  EXAM_CHECK(s.count(42) == 0);
  s.insert(42);
  EXAM_CHECK(s.count(42) == 1);
  s.insert(42);
  EXAM_CHECK(s.count(42) == 2);

  mset::iterator i = s.find(40);
  EXAM_CHECK(i == s.end());

  i = s.find(42);
  EXAM_CHECK(i != s.end());
  size_t count = s.erase(42);
  EXAM_CHECK(count == 2);

  return EXAM_RESULT;
}

int EXAM_IMPL(multiset_test::mset3)
{
  int array [] = { 3, 6, 1, 2, 3, 2, 6, 7, 9 };

  //Check iterator on a mutable set
  mset s(array, array + 9);
  mset::iterator i;
  i = s.lower_bound(3);
  EXAM_CHECK(*i == 3);
  i = s.upper_bound(3);
  EXAM_CHECK(*i == 6);
  pair<mset::iterator, mset::iterator> p = s.equal_range(5);
  EXAM_CHECK(*(p.first) == 6);
  EXAM_CHECK(*(p.second) == 6);

  //Check const_iterator on a mutable multiset
  mset::const_iterator ci;
  ci = s.lower_bound(3);
  EXAM_CHECK(*ci == 3);
  ci = s.upper_bound(3);
  EXAM_CHECK(*ci == 6);
  pair<mset::const_iterator, mset::const_iterator> cp;
  cp = s.equal_range(5);
  EXAM_CHECK(*(cp.first) == 6);
  EXAM_CHECK(*(cp.second) == 6);

  //Check const_iterator on a const multiset
  mset const& crs = s;
  ci = crs.lower_bound(3);
  EXAM_CHECK(*ci == 3);
  ci = crs.upper_bound(3);
  EXAM_CHECK(*ci == 6);
  cp = crs.equal_range(5);
  EXAM_CHECK(*(cp.first) == 6);
  EXAM_CHECK(*(cp.second) == 6);

  return EXAM_RESULT;
}

int EXAM_IMPL(multiset_test::mset5)
{
  int array [] = { 3, 6, 1, 9 };
  int j;

  typedef pointer_to_binary_function<int, int, bool> fn_type;
  typedef multiset<int, fn_type, allocator<int> > fn_mset;

  fn_type f(less_than);
  fn_mset s1(array+0, array + 4 , f );
  fn_mset::const_iterator i = s1.begin();
  for (j = 0; i != s1.end(); ++i, ++j) {
    EXAM_CHECK(j != 0 || *i == 1);
    EXAM_CHECK(j != 1 || *i == 3);
    EXAM_CHECK(j != 2 || *i == 6);
    EXAM_CHECK(j != 3 || *i == 9);
  }

  fn_type g(greater_than);
  fn_mset s2(array, array + 4, g);
  i = s2.begin();
  for (j = 0; i != s2.end(); ++i, ++j) {
    EXAM_CHECK(j != 0 || *i == 9);
    EXAM_CHECK(j != 1 || *i == 6);
    EXAM_CHECK(j != 2 || *i == 3);
    EXAM_CHECK(j != 3 || *i == 1);
  }

  return EXAM_RESULT;
}
