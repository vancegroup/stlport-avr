#include "search_test.h"

#include <vector>
#include <numeric>
#include <algorithm>

#include "iota.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(search_test::search0)
{
  int v1[6] = { 1, 1, 2, 3, 5, 8 };
  int v2[6] = { 0, 1, 2, 3, 4, 5 };
  int v3[2] = { 3, 4 };

  int* location;
  location = search((int*)v1, (int*)v1 + 6, (int*)v3, (int*)v3 + 2);
  EXAM_CHECK(location == v1 + 6);

  location = search((int*)v2, (int*)v2 + 6, (int*)v3, (int*)v3 + 2);
  EXAM_CHECK(location != v2 + 6);
  EXAM_CHECK(location - v2 == 3);

  return EXAM_RESULT;
}

int EXAM_IMPL(search_test::search1)
{
  typedef vector <int> IntVec;
  IntVec v1(10);
  __iota(v1.begin(), v1.end(), 0);
  IntVec v2(3);
  __iota(v2.begin(), v2.end(), 50);

  IntVec::iterator location;
  location = search(v1.begin(), v1.end(), v2.begin(), v2.end());

  EXAM_CHECK(location == v1.end());

  __iota(v2.begin(), v2.end(), 4);

  location = search(v1.begin(), v1.end(), v2.begin(), v2.end());

  EXAM_CHECK(location != v1.end());
  EXAM_CHECK(location - v1.begin() == 4);

  return EXAM_RESULT;
}

int EXAM_IMPL(search_test::search2)
{
  char const* grades[] = { "A", "B", "C", "D", "F" };
  char const* letters[] = { "Q", "E", "D" };
  const unsigned gradeCount = sizeof(grades) / sizeof(grades[0]);
  const unsigned letterCount = sizeof(letters) / sizeof(letters[0]);
  char const** location = search((char const**)grades, (char const**)grades + gradeCount, (char const**)letters, (char const**)letters + letterCount, str_equal);

  EXAM_CHECK(location == grades + gradeCount);

  copy((char const**)grades + 1, (char const**)grades + 1 + letterCount, (char const**)letters);
  location = search((char const**)grades, (char const**)grades + gradeCount, (char const**)letters, (char const**)letters + letterCount, str_equal);

  EXAM_CHECK(location != grades + gradeCount);
  EXAM_CHECK(location - grades == 1);

  return EXAM_RESULT;
}
