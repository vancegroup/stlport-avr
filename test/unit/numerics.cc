// -*- C++ -*- Time-stamp: <08/10/26 22:28:23 ptr>

/*
 * Copyright (c) 2008
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#include "numerics.h"
#include <vector>
#include <numeric>

#include "iota.h"

using namespace std;

int EXAM_IMPL(numerics::times)
{
  int input[4] = { 1, 5, 7, 2 };
  EXAM_CHECK( accumulate(input, input + 4, 1, multiplies<int>()) == 70 );

  return EXAM_RESULT;
}

int EXAM_IMPL(numerics::accum1)
{
  vector<int> v(5);

  for( int i = 0; (size_t)i < v.size(); ++i ) {
    v[i] = i + 1;
  }

  EXAM_CHECK( accumulate(v.begin(), v.end(), 0) == 15 );

  return EXAM_RESULT;
}

int mult( int a, int b )
{
  return a * b;
}

int add( int a, int b )
{
  return a + b;
}

int EXAM_IMPL(numerics::accum2)
{
  vector<int> v(5);

  for( int i = 0; (size_t)i < v.size(); ++i ) {
    v[i] = i + 1;
  }

  EXAM_CHECK( accumulate(v.begin(), v.end(), 1, mult) == 120 );

  return EXAM_RESULT;
}

int EXAM_IMPL(numerics::partsum0)
{
  int numbers[6] = { 1, 2, 3, 4, 5, 6 };

  int result[6];
  partial_sum((int*)numbers, (int*)numbers + 6, (int*)result);

  // 1 3 6 10 15 21
  EXAM_CHECK(result[0]==1);
  EXAM_CHECK(result[1]==3);
  EXAM_CHECK(result[2]==6);
  EXAM_CHECK(result[3]==10);
  EXAM_CHECK(result[4]==15);
  EXAM_CHECK(result[5]==21);

  return EXAM_RESULT;
}

int EXAM_IMPL(numerics::partsum1)
{
  vector <int> v1(10);
  __iota(v1.begin(), v1.end(), 0);
  vector <int> v2(v1.size());
  partial_sum(v1.begin(), v1.end(), v2.begin());

  // 0 1 3 6 10 15 21 28 36 45
  EXAM_CHECK(v2[0]==0);
  EXAM_CHECK(v2[1]==1);
  EXAM_CHECK(v2[2]==3);
  EXAM_CHECK(v2[3]==6);
  EXAM_CHECK(v2[4]==10);
  EXAM_CHECK(v2[5]==15);
  EXAM_CHECK(v2[6]==21);
  EXAM_CHECK(v2[7]==28);
  EXAM_CHECK(v2[8]==36);
  EXAM_CHECK(v2[9]==45);

  return EXAM_RESULT;
}

int EXAM_IMPL(numerics::partsum2)
{
  vector <int> v1(5);
  __iota(v1.begin(), v1.end(), 1);
  vector <int> v2(v1.size());
  partial_sum(v1.begin(), v1.end(), v2.begin(), multiplies<int>());
  // 1 2 6 24 120
  EXAM_CHECK(v2[0]==1);
  EXAM_CHECK(v2[1]==2);
  EXAM_CHECK(v2[2]==6);
  EXAM_CHECK(v2[3]==24);
  EXAM_CHECK(v2[4]==120);

  return EXAM_RESULT;
}

int EXAM_IMPL(numerics::innprod0)
{
  int vector1[5] = { 1, 2, 3, 4, 5 };
  int vector2[5] = { 1, 2, 3, 4, 5 };

  EXAM_CHECK( inner_product(vector1, vector1 + 5, vector2, 0) == 55 );

  return EXAM_RESULT;
}

int EXAM_IMPL(numerics::innprod1)
{
  vector<int> v1(3);
  vector<int> v2(v1.size());

  for ( int i = 0; (size_t)i < v1.size(); ++i ) {
    v1[i] = i + 1;
    v2[i] = v1.size() - i;
  }

  EXAM_CHECK( inner_product(v1.begin(), v1.end(), v2.begin(), 0) == 10 );

  return EXAM_RESULT;
}

int EXAM_IMPL(numerics::innprod2)
{
  vector<int> v1(3);
  vector<int> v2(v1.size());

  for ( int i = 0; (size_t)i < v1.size(); ++i ) {
    v1[i] = i + 1;
    v2[i] = v1.size() - i;
  }

  EXAM_CHECK( inner_product( v1.begin(), v1.end(), v2.begin(), (size_t)1, mult, add) == 64 );

  return EXAM_RESULT;
}
