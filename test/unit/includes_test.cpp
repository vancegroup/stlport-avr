#include "includes_test.h"

#include <cstring>
#include <vector>
#include <algorithm>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(includes_test::incl0)
{
  int numbers1[5] = { 1, 2, 3, 4, 5 };
  //int numbers2[5] = { 1, 2, 4, 8, 16 };
  int numbers3[2] = { 4, 8 };
  bool r1=includes(numbers1, numbers1 + 5, numbers3, numbers3 + 2);
  EXAM_CHECK(!r1);

  return EXAM_RESULT;
}

int EXAM_IMPL(includes_test::incl1)
{
  vector<int> v1(10);
  vector<int> v2(3);
  int i;
  for (i = 0; (size_t)i < v1.size(); ++i) {
    v1[i] = i;
  }

  bool r1=includes(v1.begin(), v1.end(), v2.begin(), v2.end());
  EXAM_CHECK(!r1);

  for (i = 0; (size_t)i < v2.size(); ++i)
    v2[i] = i + 3;

  bool r2=includes(v1.begin(), v1.end(), v2.begin(), v2.end());
  EXAM_CHECK(r2);

  return EXAM_RESULT;
}

int EXAM_IMPL(includes_test::incl2)
{
  char const* names[] = {  "Todd", "Mike", "Graham", "Jack", "Brett"};

  const unsigned nameSize = sizeof(names)/sizeof(names[0]);
  vector <char const*> v1(nameSize);
  for (int i = 0; (size_t)i < v1.size(); ++i) {
    v1[i] = names[i];
  }
  vector <char const*> v2(2);

  v2[0] = "foo";
  v2[1] = "bar";
  sort(v1.begin(), v1.end(), compare_strings);
  sort(v2.begin(), v2.end(), compare_strings);

  bool r1 = includes(v1.begin(), v1.end(), v2.begin(), v2.end(), compare_strings);
  EXAM_CHECK(!r1);

  v2[0] = "Brett";
  v2[1] = "Todd";
  bool r2 = includes(v1.begin(), v1.end(), v2.begin(), v2.end(), compare_strings);
  EXAM_CHECK(r2);

  return EXAM_RESULT;
}
