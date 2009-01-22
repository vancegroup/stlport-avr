#include "rndshf_test.h"

#include <numeric>
#include <vector>
#include <algorithm>

#include "iota.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(rnd_shuffle_test::rndshuf0)
{
  int numbers[6] = { 1, 2, 3, 4, 5, 6 };

  random_shuffle(numbers, numbers + 6);

  EXAM_CHECK(count(numbers, numbers+6, 1)==1);
  EXAM_CHECK(count(numbers, numbers+6, 2)==1);
  EXAM_CHECK(count(numbers, numbers+6, 3)==1);
  EXAM_CHECK(count(numbers, numbers+6, 4)==1);
  EXAM_CHECK(count(numbers, numbers+6, 5)==1);
  EXAM_CHECK(count(numbers, numbers+6, 6)==1);

  return EXAM_RESULT;
}

int EXAM_IMPL(rnd_shuffle_test::rndshuf1)
{
  vector <int> v1(10);
  __iota(v1.begin(), v1.end(), 0);

  MyRandomGenerator r;
  for(int i = 0; i < 3; i++)
  {
    random_shuffle(v1.begin(), v1.end(), r);
    EXAM_CHECK(count(v1.begin(), v1.end(), 0)==1);
    EXAM_CHECK(count(v1.begin(), v1.end(), 1)==1);
    EXAM_CHECK(count(v1.begin(), v1.end(), 2)==1);
    EXAM_CHECK(count(v1.begin(), v1.end(), 3)==1);
    EXAM_CHECK(count(v1.begin(), v1.end(), 4)==1);
    EXAM_CHECK(count(v1.begin(), v1.end(), 5)==1);
    EXAM_CHECK(count(v1.begin(), v1.end(), 6)==1);
    EXAM_CHECK(count(v1.begin(), v1.end(), 7)==1);
    EXAM_CHECK(count(v1.begin(), v1.end(), 8)==1);
    EXAM_CHECK(count(v1.begin(), v1.end(), 9)==1);
  }

  return EXAM_RESULT;
}
