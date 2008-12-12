// -*- C++ -*- Time-stamp: <08/12/12 22:33:39 ptr>

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

#include "functor_test.h"

#include <algorithm>
#include <vector>
#include <functional>
#include <numeric> // for inner_product

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(functor_test::equal0)
{
  int numbers1[5] = { 1, 2, 3, 4, 5 };
  int numbers2[5] = { 1, 2, 4, 8, 16 };
  int numbers3[2] = { 1, 2 };

  EXAM_CHECK( !equal(numbers1, numbers1 + 5, numbers2) );
  EXAM_CHECK( equal(numbers3, numbers3 + 2, numbers1) );

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::equal1)
{
  vector <int> v1(10);
  for (int i = 0; (size_t)i < v1.size(); ++i)
    v1[i] = i;
  vector <int> v2(10);
  EXAM_CHECK( !equal(v1.begin(), v1.end(), v2.begin()) );

  copy(v1.begin(), v1.end(), v2.begin());
  EXAM_CHECK( equal(v1.begin(), v1.end(), v2.begin()) );

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::equal2)
{
  vector <int> v1(10);
  vector <int> v2(10);
  for (int i = 0; (size_t)i < v1.size(); ++i) {
    v1[i] = i;
    v2[i] = i * i;
  }
  EXAM_CHECK( equal(v1.begin(), v1.end(), v2.begin(), values_squared) );

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::equalto)
{
  int input1 [4] = { 1, 7, 2, 2 };
  int input2 [4] = { 1, 6, 2, 3 };

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, equal_to<int>());
  EXAM_CHECK( output[0] == 1 );
  EXAM_CHECK( output[1] == 0 );
  EXAM_CHECK( output[2] == 1 );
  EXAM_CHECK( output[3] == 0 );

  return EXAM_RESULT;
}

bool functor_test::values_squared(int a_, int b_)
{
  return (a_ * a_ == b_);
}

int EXAM_IMPL(functor_test::bnegate1)
{
  int array [4] = { 4, 9, 7, 1 };

  sort(array, array + 4, binary_negate<greater<int> >(greater<int>()));
  EXAM_CHECK(array[0]==1);
  EXAM_CHECK(array[1]==4);
  EXAM_CHECK(array[2]==7);
  EXAM_CHECK(array[3]==9);

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::bnegate2)
{
  int array [4] = { 4, 9, 7, 1 };
  sort(array, array + 4, not2(greater<int>()));
  EXAM_CHECK(array[0]==1);
  EXAM_CHECK(array[1]==4);
  EXAM_CHECK(array[2]==7);
  EXAM_CHECK(array[3]==9);

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::logicand)
{
  bool input1 [4] = { true, true, false, true };
  bool input2 [4] = { false, true, false, false };

  bool output [4];
  transform((bool*)input1, (bool*)input1 + 4, (bool*)input2, (bool*)output, logical_and<bool>());

  EXAM_CHECK(output[0]==false);
  EXAM_CHECK(output[1]==true);
  EXAM_CHECK(output[2]==false);
  EXAM_CHECK(output[3]==false);

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::logicnot)
{
  bool input [7] = { 1, 0, 0, 1, 1, 1, 1 };

  int n = count_if(input, input + 7, logical_not<bool>());
  EXAM_CHECK( n == 2 );

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::logicor)
{
  bool input1 [4] = { true, true, false, true };
  bool input2 [4] = { false, true, false, false };

  bool output [4];
  transform((bool*)input1, (bool*)input1 + 4, (bool*)input2, (bool*)output, logical_or<bool>());

  EXAM_CHECK(output[0]==true);
  EXAM_CHECK(output[1]==true);
  EXAM_CHECK(output[2]==false);
  EXAM_CHECK(output[3]==true);

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::lesst)
{
  int array [4] = { 3, 1, 4, 2 };
  sort(array, array + 4, less<int>());

  EXAM_CHECK(array[0]==1);
  EXAM_CHECK(array[1]==2);
  EXAM_CHECK(array[2]==3);
  EXAM_CHECK(array[3]==4);

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::lesseqt)
{
  int array [4] = { 3, 1, 4, 2 };
  sort(array, array + 4, less_equal<int>());

  EXAM_CHECK(array[0]==1);
  EXAM_CHECK(array[1]==2);
  EXAM_CHECK(array[2]==3);
  EXAM_CHECK(array[3]==4);

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::greatert)
{
  int array[4] = { 3, 1, 4, 2 };
  sort(array, array + 4, greater<int>() );

  EXAM_CHECK(array[0]==4);
  EXAM_CHECK(array[1]==3);
  EXAM_CHECK(array[2]==2);
  EXAM_CHECK(array[3]==1);

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::greatereq)
{
  int array [4] = { 3, 1, 4, 2 };
  sort(array, array + 4, greater_equal<int>());
  EXAM_CHECK(array[0]==4);
  EXAM_CHECK(array[1]==3);
  EXAM_CHECK(array[2]==2);
  EXAM_CHECK(array[3]==1);

  return EXAM_RESULT;
}

bool functor_test::bigger(int i_)
{
  return i_ > 3;
}

bool functor_test::bigger_than(int x_, int y_)
{
    return x_ > y_;
}

int EXAM_IMPL(functor_test::func1)
{
  vector<int>v;
  v.push_back(4);
  v.push_back(1);
  v.push_back(5);
  int n = count_if(v.begin(), v.end(), bigger);
  EXAM_CHECK( n == 2 );

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::func2)
{
  vector<int> v;
  v.push_back(4);
  v.push_back(1);
  v.push_back(5);
  sort(v.begin(), v.end(), bigger_than);

  EXAM_CHECK( v[0] == 5 );
  EXAM_CHECK( v[1] == 4 );
  EXAM_CHECK( v[2] == 1 );

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::func3)
{
  vector<int> v;
  v.push_back(4);
  v.push_back(1);
  v.push_back(5);
  sort(v.begin(), v.end(), greater<int>());

  EXAM_CHECK( v[0] == 5 );
  EXAM_CHECK( v[1] == 4 );
  EXAM_CHECK( v[2] == 1 );

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::plus0)
{
  int input1 [4] = { 1, 6, 11, 8 };
  int input2 [4] = { 1, 5, 2, 3 };

  int total = inner_product(input1, input1 + 4, input2, 0, plus<int>(), multiplies <int>
());

  EXAM_CHECK(total==77);

  return EXAM_RESULT;
}

int EXAM_IMPL(functor_test::minus0)
{
  int input1 [4] = { 1, 5, 7, 8 };
  int input2 [4] = { 1, 4, 8, 3 };

  int output [4];

  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, minus<int>());
  EXAM_CHECK(output[0]==0);
  EXAM_CHECK(output[1]==1);
  EXAM_CHECK(output[2]==-1);
  EXAM_CHECK(output[3]==5);

  return EXAM_RESULT;
}
