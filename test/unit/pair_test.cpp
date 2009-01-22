#include "pair_test.h"

#include <utility>
#include <vector>
#include <algorithm>
#include <string>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(pair_test::pair0)
{
  pair<int, int> p = make_pair(1, 10);

  EXAM_CHECK(p.first==1);
  EXAM_CHECK(p.second==10);

  return EXAM_RESULT;
}

int EXAM_IMPL(pair_test::init)
{
  pair<int, string> PAIR_ARRAY[] = { pair<int, string>(0, "0") };

  int PAIR_ARRAY_SIZE = sizeof(PAIR_ARRAY) > 0 ? sizeof(PAIR_ARRAY) / sizeof(PAIR_ARRAY[0]) : 0;

  for ( int i = 0; i < PAIR_ARRAY_SIZE; i++ ) {
    EXAM_CHECK( PAIR_ARRAY[i].first == 0 );
    EXAM_CHECK( PAIR_ARRAY[i].second == "0" );
    PAIR_ARRAY[i].second = "1";
  }

  return EXAM_RESULT;
}
