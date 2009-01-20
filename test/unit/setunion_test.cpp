#include "set_operations_test.h"

#include <numeric>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>

#include "iota.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(set_union_test::setunon0)
{
  int v1[3] = { 13, 18, 23 };
  int v2[4] = { 10, 13, 17, 23 };
  int result[7] = { 0, 0, 0, 0, 0, 0, 0 };

  set_union((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);

  EXAM_CHECK(result[0]==10);
  EXAM_CHECK(result[1]==13);
  EXAM_CHECK(result[2]==17);
  EXAM_CHECK(result[3]==18);
  EXAM_CHECK(result[4]==23);
  EXAM_CHECK(result[5]==0);
  EXAM_CHECK(result[6]==0);

  return EXAM_RESULT;
}

int EXAM_IMPL(set_union_test::setunon1)
{
  vector <int> v1(10);
  __iota(v1.begin(), v1.end(), 0);
  vector <int> v2(10);
  __iota(v2.begin(), v2.end(), 7);

  vector<int> diff;
  set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(diff));
  EXAM_CHECK( diff.size() == 17 );
  for (int i = 0; i < 17; ++i) {
    EXAM_CHECK( diff[i] == i );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(set_union_test::setunon2)
{
  const char* word1 = "ABCDEFGHIJKLMNO";
  const char* word2 = "LMNOPQRSTUVWXYZ";

  string diff;
  set_union(word1, word1 + ::strlen(word1), word2, word2 + ::strlen(word2),
            back_inserter(diff), less<char>());
  EXAM_CHECK( diff.size() == 26 );
  for (int i = 0; i < 26; ++i) {
    EXAM_CHECK( diff[i] == ('A' + i) );
  }

  return EXAM_RESULT;
}
