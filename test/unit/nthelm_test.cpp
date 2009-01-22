#include "nthelm_test.h"

#include <vector>
#include <algorithm>
#include <functional>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(nth_elem_test::nthelem0)
{
  int numbers[7] = { 5, 2, 4, 1, 0, 3 ,77};
  nth_element(numbers, numbers + 3, numbers + 6);

  EXAM_CHECK(numbers[0]==1);
  EXAM_CHECK(numbers[1]==0);
  EXAM_CHECK(numbers[2]==2);
  EXAM_CHECK(numbers[3]==3);
  EXAM_CHECK(numbers[4]==4);
  EXAM_CHECK(numbers[5]==5);

  return EXAM_RESULT;
}

int EXAM_IMPL(nth_elem_test::nthelem1)
{
  //6 8 5 1 7 4 1 5 2 6
  //1 1 4 2 5 5 6 7 8 6
  int numbers[10] = { 6, 8, 5, 1, 7, 4, 1, 5, 2, 6 };

  vector <int> v1(numbers, numbers+10);
  nth_element(v1.begin(), v1.begin() + v1.size() / 2, v1.end());

  EXAM_CHECK(v1[0]==1);
  EXAM_CHECK(v1[1]==1);
  EXAM_CHECK(v1[2]==4);
  EXAM_CHECK(v1[3]==2);
  EXAM_CHECK(v1[4]==5);
  EXAM_CHECK(v1[5]==5);
  EXAM_CHECK(v1[6]==6);
  EXAM_CHECK(v1[7]==7);
  EXAM_CHECK(v1[8]==8);
  EXAM_CHECK(v1[9]==6);

  return EXAM_RESULT;
}

int EXAM_IMPL(nth_elem_test::nthelem2)
{
  //4 5 4 2 1 7 4 3 1 6
  //6 7 4 4 5 4 3 2 1 1
  int numbers[10] = { 4, 5, 4, 2, 1, 7, 4, 3, 1, 6 };

  vector <int> v1(numbers, numbers+10);
  nth_element(v1.begin(), v1.begin() + v1.size() / 2, v1.end(), greater<int>());

  EXAM_CHECK(v1[0]==6);
  EXAM_CHECK(v1[1]==7);
  EXAM_CHECK(v1[2]==4);
  EXAM_CHECK(v1[3]==4);
  EXAM_CHECK(v1[4]==5);
  EXAM_CHECK(v1[5]==4);
  EXAM_CHECK(v1[6]==3);
  EXAM_CHECK(v1[7]==2);
  EXAM_CHECK(v1[8]==1);
  EXAM_CHECK(v1[9]==1);

  return EXAM_RESULT;
}
