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

int EXAM_IMPL(set_intersection_test::setintr0)
{
  int v1[3] = { 13, 18, 23 };
  int v2[4] = { 10, 13, 17, 23 };
  int result[4] = { 0, 0, 0, 0 };

  set_intersection((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);

  EXAM_CHECK(result[0]==13);
  EXAM_CHECK(result[1]==23);
  EXAM_CHECK(result[2]==0);
  EXAM_CHECK(result[3]==0);

  return EXAM_RESULT;
}

int EXAM_IMPL(set_intersection_test::setintr1)
{
  vector <int> v1(10);
  __iota(v1.begin(), v1.end(), 0);
  vector <int> v2(10);
  __iota(v2.begin(), v2.end(), 7);

  vector<int> inter;
  set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(inter));
  EXAM_CHECK( inter.size() == 3 );
  EXAM_CHECK( inter[0] == 7 );
  EXAM_CHECK( inter[1] == 8 );
  EXAM_CHECK( inter[2] == 9 );

  return EXAM_RESULT;
}

int EXAM_IMPL(set_intersection_test::setintr2)
{
  const char* word1 = "ABCDEFGHIJKLMNO";
  const char* word2 = "LMNOPQRSTUVWXYZ";

  string inter;
  set_intersection(word1, word1 + ::strlen(word1), word2, word2 + ::strlen(word2),
                   back_inserter(inter), less<char>());
  EXAM_CHECK( inter.size() == 4 );
  EXAM_CHECK( inter[0] == 'L' );
  EXAM_CHECK( inter[1] == 'M' );
  EXAM_CHECK( inter[2] == 'N' );
  EXAM_CHECK( inter[3] == 'O' );

  return EXAM_RESULT;
}
