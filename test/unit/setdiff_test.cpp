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

int EXAM_IMPL(set_difference_test::setsymd0)
{
  int v1[3] = { 13, 18, 23 };
  int v2[4] = { 10, 13, 17, 23 };
  int result[4] = { 0, 0, 0, 0 };

  set_symmetric_difference((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);
  EXAM_CHECK(result[0]==10);
  EXAM_CHECK(result[1]==17);
  EXAM_CHECK(result[2]==18);
  EXAM_CHECK(result[3]==0);

  return EXAM_RESULT;
}

int EXAM_IMPL(set_difference_test::setsymd1)
{
  vector<int> v1(10);
  __iota(v1.begin(), v1.end(), 0);
  vector<int> v2(10);
  __iota(v2.begin(), v2.end(), 7);

  vector<int> diff;
  set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(diff));
  EXAM_CHECK( diff.size() == 14 );
  int int_res[] = {0, 1, 2, 3, 4, 5, 6, 10, 11, 12, 13, 14, 15, 16};
  for (int i = 0; i < 14; ++i) {
    EXAM_CHECK( diff[i] == int_res[i] );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(set_difference_test::setsymd2)
{
  const char* word1 = "ABCDEFGHIJKLMNO";
  const char* word2 = "LMNOPQRSTUVWXYZ";

  string diff;
  set_symmetric_difference(word1, word1 + ::strlen(word1), word2, word2 + ::strlen(word2),
                           back_inserter(diff), less<char>());
  EXAM_CHECK( diff.size() == 22 );
  char char_res[] = "ABCDEFGHIJKPQRSTUVWXYZ";
  for (int i = 0; i < 22; ++i) {
    EXAM_CHECK( diff[i] == char_res[i] );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(set_difference_test::setdiff0)
{
  int v1[3] = { 13, 18, 23 };
  int v2[4] = { 10, 13, 17, 23 };
  int result[4] = { 0, 0, 0, 0 };
  //18 0 0 0
  //10 17 23 0

  set_difference((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);
  EXAM_CHECK( result[0] == 18 );
  EXAM_CHECK( result[1] == 0 );
  EXAM_CHECK( result[2] == 0 );
  EXAM_CHECK( result[3] == 0 );

  set_difference((int*)v2, (int*)v2 + 4, (int*)v1, (int*)v1 + 2, (int*)result);
  EXAM_CHECK( result[0] == 10 );
  EXAM_CHECK( result[1] == 17 );
  EXAM_CHECK( result[2] == 23 );
  EXAM_CHECK( result[3] == 0 );

  return EXAM_RESULT;
}

int EXAM_IMPL(set_difference_test::setdiff1)
{
  vector<int> v1(10);
  __iota(v1.begin(), v1.end(), 0);
  vector<int> v2(10);
  __iota(v2.begin(), v2.end(), 7);

  vector<int> diff;
  set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(diff));
  EXAM_CHECK( diff.size() == 7 );
  for (int i = 0; i < 7; ++i) {
    EXAM_CHECK( diff[i] == i );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(set_difference_test::setdiff2)
{
  const char* word1 = "ABCDEFGHIJKLMNO";
  const char* word2 = "LMNOPQRSTUVWXYZ";

  string diff;
  set_difference(word1, word1 + ::strlen(word1), word2, word2 + ::strlen(word2), back_inserter(diff), less<char>());
  EXAM_CHECK( diff.size() == 11 );
  for (int i = 0; i < 11; ++i) {
    EXAM_CHECK( diff[i] == ('A' + i) );
  }

  return EXAM_RESULT;
}
