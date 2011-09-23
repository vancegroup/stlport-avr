// -*- C++ -*- Time-stamp: <2011-09-23 20:29:11 ptr>

/*
 * Copyright (c) 2004-2010
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

#include "utility_test.h"

#include <utility>
#include <vector>
#include <algorithm>
#include <string>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(utility_test::pair0)
{
  pair<int, int> p = make_pair(1, 10);

  EXAM_CHECK(p.first==1);
  EXAM_CHECK(p.second==10);

  return EXAM_RESULT;
}

int EXAM_IMPL(utility_test::init)
{
  pair<int, string> PAIR_ARRAY[] = { pair<int, string>(0, "0") };

  int PAIR_ARRAY_SIZE = sizeof(PAIR_ARRAY) > 0 ? sizeof(PAIR_ARRAY) / sizeof(PAIR_ARRAY[0]) : 0;

  for ( int i = 0; i < PAIR_ARRAY_SIZE; i++ ) {
    EXAM_CHECK( PAIR_ARRAY[i].first == 0 );
    EXAM_CHECK( PAIR_ARRAY[i].second == "0" );
    PAIR_ARRAY[i].second = "1";
  }

  return EXAM_RESULT;
}

struct A
{
    A( int&, const double& )
      { }
};

#ifdef _STLP_CPP_0X

template <class T, class A1, class A2>
T* factory( A1&& a1, A2&& a2 )
{ return new T( std::forward<A1>(a1), std::forward<A2>(a2) ); }

#endif

int EXAM_IMPL(utility_test::forward)
{
#ifndef _STLP_CPP_0X
  throw exam::skip_exception( /* "no rvalue reference" */ );
#else

  int i = -1;
  A* a = factory<A>( i, 3.1415 );
  // A* b = factory<A>( -1, 3.1415 ); // shouldn't compile
  delete a;

#endif

  return EXAM_RESULT;
}

#ifdef _STLP_CPP_0X

template <class T, class A1>
T* yet_another_factory( A1&& a )
{ return new T( std::forward<A1>(a) ); }

#endif

int EXAM_IMPL(utility_test::move)
{
#ifndef _STLP_CPP_0X
  throw exam::skip_exception( /* "no rvalue reference" */ );
#else

  struct B
  {
      B() :
          flag( 0 )
        { }
      B( const B& ) : // copies from lvalue
          flag( 1 )
        { }
      B( B&& b ) :    // moves from rvalue
          flag( 2 )
        { b.flag = 3; }

      int flag;
  };

  B b;

  EXAM_CHECK( b.flag == 0 );

  B* b1 = yet_another_factory<B>( b );              // b binds to B( const B& )

  EXAM_CHECK( b1->flag == 1 );

  delete b1;

  B* b2 = yet_another_factory<B>( std::move( b ) ); // b binds to B( B&& )

  EXAM_CHECK( b2->flag == 2 );
  EXAM_CHECK( b.flag == 3 );

  delete b2;

#endif

  return EXAM_RESULT;
}
