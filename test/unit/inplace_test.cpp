#include "inplace_test.h"

#include <vector>
#include <algorithm>
#include <functional>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(inplace_test::inplmrg1)
{
  int numbers[6] = { 1, 10, 42, 3, 16, 32 };
  inplace_merge(numbers, numbers + 3, numbers + 6);

  EXAM_CHECK(numbers[0]==1);
  EXAM_CHECK(numbers[1]==3);
  EXAM_CHECK(numbers[2]==10);
  EXAM_CHECK(numbers[3]==16);
  EXAM_CHECK(numbers[4]==32);
  EXAM_CHECK(numbers[5]==42);

  return EXAM_RESULT;
}

int EXAM_IMPL(inplace_test::inplmrg2)
{
  vector<size_t> v1(10);
  for(size_t i = 0; i < v1.size(); ++i)
    v1[i] =(v1.size() - i - 1) % 5;

  inplace_merge(v1.begin(), v1.begin() + 5, v1.end(), greater<size_t>());

  EXAM_CHECK(v1[0]==4);
  EXAM_CHECK(v1[1]==4);
  EXAM_CHECK(v1[2]==3);
  EXAM_CHECK(v1[3]==3);
  EXAM_CHECK(v1[4]==2);
  EXAM_CHECK(v1[5]==2);
  EXAM_CHECK(v1[6]==1);
  EXAM_CHECK(v1[7]==1);
  EXAM_CHECK(v1[8]==0);
  EXAM_CHECK(v1[9]==0);

  return EXAM_RESULT;
}
