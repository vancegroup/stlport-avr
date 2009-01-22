// -*- C++ -*- Time-stamp: <09/01/23 00:36:06 ptr>

/*
 * Copyright (c) 2004-2009
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#include "transform_test.h"

#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

static int negate_int( int a_ )
{ return -a_; }

static char map_char( char a_, int b_ )
{ return char(a_ + b_); }

static char shift( char c )
{ return char(((int)c + 1) % 256); }

int EXAM_IMPL(transform_test::trnsfrm1)
{
  int numbers[6] = { -5, -1, 0, 1, 6, 11 };

  int result[6];
  transform((int*)numbers, (int*)numbers + 6, (int*)result, negate_int);

  EXAM_CHECK(result[0]==5);
  EXAM_CHECK(result[1]==1);
  EXAM_CHECK(result[2]==0);
  EXAM_CHECK(result[3]==-1);
  EXAM_CHECK(result[4]==-6);
  EXAM_CHECK(result[5]==-11);

  return EXAM_RESULT;
}

int EXAM_IMPL(transform_test::trnsfrm2)
{
#if defined (__MVS__)
  int trans[] = {-11, 4, -6, -6, -18, 0, 18, -14, 6, 0, -1, -59};
#else
  int trans[] = {-4, 4, -6, -6, -10, 0, 10, -6, 6, 0, -1, -77};
#endif
  char n[] = "Larry Mullen";
  const size_t count = ::strlen(n);

  string res;
  transform(n, n + count, trans, back_inserter(res), map_char);
  EXAM_CHECK( res == "Hello World!" );

  return EXAM_RESULT;
}

int EXAM_IMPL(transform_test::self_str)
{
  string s( "0123456789abcdefg" );
  string r( "123456789:bcdefgh" );
  transform( s.begin(), s.end(), s.begin(), shift );
  EXAM_CHECK( s == r );

  return EXAM_RESULT;
}

int EXAM_IMPL(neq_test::negate0)
{
  int input [3] = { 1, 2, 3 };

  int output[3];
  transform((int*)input, (int*)input + 3, (int*)output, negate<int>());

  EXAM_CHECK(output[0]==-1);
  EXAM_CHECK(output[1]==-2);
  EXAM_CHECK(output[2]==-3);

  return EXAM_RESULT;
}

int EXAM_IMPL(neq_test::nequal0)
{
  int input1 [4] = { 1, 7, 2, 2 };
  int input2 [4] = { 1, 6, 2, 3 };

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, not_equal_to<int>());

  EXAM_CHECK(output[0]==0);
  EXAM_CHECK(output[1]==1);
  EXAM_CHECK(output[2]==0);
  EXAM_CHECK(output[3]==1);

  return EXAM_RESULT;
}

int EXAM_IMPL(modulus_test::modulus0)
{
  int input1 [4] = { 6, 8, 10, 2 };
  int input2 [4] = { 4, 2, 11, 3 };

  int output [4];

  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, modulus<int>());
  EXAM_CHECK(output[0]==2);
  EXAM_CHECK(output[1]==0);
  EXAM_CHECK(output[2]==10);
  EXAM_CHECK(output[3]==2);

  return EXAM_RESULT;
}
