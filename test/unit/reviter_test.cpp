#include "iter_test.h"

#include <vector>
#include <list>
#include <algorithm>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(reviter_test::reviter1)
{
  int array [] = { 1, 5, 2, 3 };

  vector<int> v(array, array + 4);
  typedef vector<int>::reverse_iterator reviter;
  reviter r(v.rend());
  r--;

  EXAM_CHECK(*r-- == 1);
  EXAM_CHECK(*r-- == 5);
  EXAM_CHECK(*r-- == 2);
  EXAM_CHECK(*r == 3);
  EXAM_CHECK(r==v.rbegin());

  return EXAM_RESULT;
}

int EXAM_IMPL(reviter_test::reviter2)
{
  int array [] = { 1, 5, 2, 3 };

  vector<int> v(array, array + 4);
  vector<int>::reverse_iterator r;
  r = v.rbegin();
  EXAM_CHECK(*r++ == 3);
  EXAM_CHECK(*r++ == 2);
  EXAM_CHECK(*r++ == 5);
  EXAM_CHECK(*r++ == 1);
  EXAM_CHECK(r==v.rend());

  return EXAM_RESULT;
}

int EXAM_IMPL(reviter_test::revbit1)
{
  int array [] = { 1, 5, 2, 3 };

  list<int> v(array, array + 4);
  list<int>::reverse_iterator r(v.rbegin());
  EXAM_CHECK(*r++ == 3);
  EXAM_CHECK(*r++ == 2);
  EXAM_CHECK(*r++ == 5);
  EXAM_CHECK(*r++ == 1);
  EXAM_CHECK(r==v.rend());

  return EXAM_RESULT;
}
