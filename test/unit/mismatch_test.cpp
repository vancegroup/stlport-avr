#include "mismatch_test.h"

#include <numeric>
#include <vector>
#include <algorithm>

#include "iota.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

bool str_equal(const char* a_, const char* b_)
{
  return strcmp(a_, b_) == 0 ? 1 : 0;
}

int EXAM_IMPL(mismatch_test::mismatch0)
{
  int n1[5] = { 1, 2, 3, 4, 5 };
  int n2[5] = { 1, 2, 3, 4, 5 };
  int n3[5] = { 1, 2, 3, 2, 1 };

  pair <int*, int*> result = mismatch((int*)n1, (int*)n1 + 5, (int*)n2);
  EXAM_CHECK(result.first ==(n1 + 5) && result.second ==(n2 + 5));

  result = mismatch((int*)n1, (int*)n1 + 5, (int*)n3);
  EXAM_CHECK(!(result.first ==(n1 + 5) && result.second ==(n3 + 5)));
  EXAM_CHECK((result.first - n1)==3);

  return EXAM_RESULT;
}

int EXAM_IMPL(mismatch_test::mismatch1)
{
  typedef vector<int> IntVec;
  IntVec v1(10);
  __iota(v1.begin(), v1.end(), 0);
  IntVec v2(v1);

  pair <IntVec::iterator, IntVec::iterator> result = mismatch(v1.begin(), v1.end(), v2.begin());

  EXAM_CHECK(result.first == v1.end() && result.second == v2.end());

  v2[v2.size()/2] = 42;
  result = mismatch(v1.begin(), v1.end(), v2.begin());
  EXAM_CHECK(!(result.first == v1.end() && result.second == v2.end()));
  EXAM_CHECK((result.first - v1.begin())==5);

  return EXAM_RESULT;
}

int EXAM_IMPL(mismatch_test::mismatch2)
{
  const unsigned size = 5;
  char const* n1[size] = { "Brett", "Graham", "Jack", "Mike", "Todd" };

  char const* n2[size];
  copy(n1, n1 + 5, (char const**)n2);
  pair <char const**, char const**> result = mismatch((char const**)n1, (char const**)n1 + size, (char const**)n2, str_equal);

  EXAM_CHECK(result.first == n1 + size && result.second == n2 + size);

  n2[2] = "QED";
  result = mismatch((char const**)n1, (char const**)n1 + size, (char const**)n2, str_equal);
  EXAM_CHECK(!(result.first == n2 + size && result.second == n2 + size));
  EXAM_CHECK((result.first - n1)==2);

  return EXAM_RESULT;
}
