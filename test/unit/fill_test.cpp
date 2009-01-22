#include "fill_test.h"

#include <vector>
#include <algorithm>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(fill_test::fill1)
{
  vector <int> v(10);
  fill(v.begin(), v.end(), 42);

  EXAM_CHECK(v[0]==42);
  EXAM_CHECK(v[1]==42);
  EXAM_CHECK(v[2]==42);
  EXAM_CHECK(v[3]==42);
  EXAM_CHECK(v[4]==42);
  EXAM_CHECK(v[5]==42);
  EXAM_CHECK(v[6]==42);
  EXAM_CHECK(v[7]==42);
  EXAM_CHECK(v[8]==42);
  EXAM_CHECK(v[9]==42);

  return EXAM_RESULT;
}

int EXAM_IMPL(fill_test::filln1)
{
  vector <int> v(10);
  fill_n(v.begin(), v.size(), 42);

  EXAM_CHECK(v[0]==42);
  EXAM_CHECK(v[1]==42);
  EXAM_CHECK(v[2]==42);
  EXAM_CHECK(v[3]==42);
  EXAM_CHECK(v[4]==42);
  EXAM_CHECK(v[5]==42);
  EXAM_CHECK(v[6]==42);
  EXAM_CHECK(v[7]==42);
  EXAM_CHECK(v[8]==42);
  EXAM_CHECK(v[9]==42);

  return EXAM_RESULT;
}
