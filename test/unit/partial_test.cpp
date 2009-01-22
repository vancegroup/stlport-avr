#include "partial_test.h"

#include <numeric>
#include <vector>
#include <algorithm>
#include <functional>

#if defined (STLPORT) && defined (_STLP_DEBUG) && defined (_STLP_DEBUG_MODE_THROWS)
#  define _STLP_DO_CHECK_BAD_PREDICATE
#  include <stdexcept>
#endif

#include "iota.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(partial_test::parsrt0)
{
  int numbers[6] = { 5, 2, 4, 3, 1, 6 };

  partial_sort((int*)numbers, (int*)numbers + 3, (int*)numbers + 6);

  // 1 2 3 5 4 6
  EXAM_CHECK(numbers[0]==1);
  EXAM_CHECK(numbers[1]==2);
  EXAM_CHECK(numbers[2]==3);
  EXAM_CHECK(numbers[3]==5);
  EXAM_CHECK(numbers[4]==4);
  EXAM_CHECK(numbers[5]==6);

  return EXAM_RESULT;
}

int EXAM_IMPL(partial_test::parsrt1)
{
  // 8 8 5 3 7 6 5 3 2 4
  // 2 3 3 4 5 8 8 7 6 5
  int numbers[10] ={ 8, 8, 5, 3, 7, 6, 5, 3, 2, 4 };

  vector <int> v1(numbers, numbers+10);
  partial_sort(v1.begin(), v1.begin() + v1.size() / 2, v1.end());

  EXAM_CHECK(v1[0]==2);
  EXAM_CHECK(v1[1]==3);
  EXAM_CHECK(v1[2]==3);
  EXAM_CHECK(v1[3]==4);
  EXAM_CHECK(v1[4]==5);
  EXAM_CHECK(v1[5]==8);
  EXAM_CHECK(v1[6]==8);
  EXAM_CHECK(v1[7]==7);
  EXAM_CHECK(v1[8]==6);
  EXAM_CHECK(v1[9]==5);

  return EXAM_RESULT;
}

int EXAM_IMPL(partial_test::parsrt2)
{
  char const* names[] = { "aa", "ff", "dd", "ee", "cc", "bb" };

  const unsigned nameSize = sizeof(names) / sizeof(names[0]);
  vector <char const*> v1(nameSize);
  for(size_t i = 0; i < v1.size(); i++)
    v1[i] = names[i];

  partial_sort(v1.begin(), v1.begin() + nameSize / 2, v1.end(), str_compare);

  // aa bb cc ff ee dd
  EXAM_CHECK( strcmp(v1[0], "aa") == 0 );
  EXAM_CHECK( v1[0] == names[0] );
  EXAM_CHECK( strcmp(v1[1], "bb") == 0 );
  EXAM_CHECK( v1[1] == names[5] );
  EXAM_CHECK( strcmp(v1[2], "cc") == 0 );
  EXAM_CHECK( v1[2] == names[4] );
  EXAM_CHECK( strcmp(v1[3], "ff") == 0 );
  EXAM_CHECK( v1[3] == names[1] );
  EXAM_CHECK( strcmp(v1[4], "ee") == 0 );
  EXAM_CHECK( v1[4] == names[3] );
  EXAM_CHECK( strcmp(v1[5], "dd") == 0 );
  EXAM_CHECK( v1[5] == names[2] );

  return EXAM_RESULT;
}

int EXAM_IMPL(partial_test::parsrtc0)
{
  int numbers[6] = { 5, 2, 4, 3, 1, 6 };

  int result[3];
  partial_sort_copy((int*)numbers, (int*)numbers + 6, (int*)result, (int*)result + 3);
  //1 2 3
  EXAM_CHECK(result[0]==1);
  EXAM_CHECK(result[1]==2);
  EXAM_CHECK(result[2]==3);

  return EXAM_RESULT;
}

int EXAM_IMPL(partial_test::parsrtc1)
{
  int numbers[10] ={ 3, 0, 4, 3, 2, 8, 2, 7, 7, 5 };

  //3 0 4 3 2 8 2 7 7 5
  //0 2 2 3 3

  vector <int> v1(numbers, numbers+10);
  vector <int> result(5);

  partial_sort_copy(v1.begin(), v1.end(), result.begin(), result.end());
  EXAM_CHECK(result[0]==0);
  EXAM_CHECK(result[1]==2);
  EXAM_CHECK(result[2]==2);
  EXAM_CHECK(result[3]==3);
  EXAM_CHECK(result[4]==3);

  return EXAM_RESULT;
}

int EXAM_IMPL(partial_test::parsrtc2)
{
  char const* names[] = { "aa", "ff", "dd", "ee", "cc", "bb" };

  const unsigned nameSize = sizeof(names) / sizeof(names[0]);
  vector <char const*> v1(nameSize);
  for(size_t i = 0; i < v1.size(); i++)
    v1[i] = names[i];
  vector <char const*> result(3);
  partial_sort_copy(v1.begin(), v1.end(), result.begin(), result.end(), str_compare);

  // aa bb cc
  EXAM_CHECK( strcmp( result[0], "aa" ) == 0 );
  EXAM_CHECK( result[0] == names[0] );
  EXAM_CHECK( strcmp( result[1], "bb" ) == 0 );
  EXAM_CHECK( result[1] == names[5] );
  EXAM_CHECK( strcmp( result[2], "cc" ) == 0 );
  EXAM_CHECK( result[2] == names[4] );

  return EXAM_RESULT;
}

int EXAM_IMPL(partial_test::bad_predicate_detected)
{
#if defined (_STLP_DO_CHECK_BAD_PREDICATE)
  int numbers[] = { 0, 0, 1, 0, 0, 1, 0, 0 };
  const size_t s = sizeof(numbers) / sizeof(numbers[0]);

  try {
    partial_sort(numbers, numbers + s / 2, numbers + s, less_equal<int>());

    //Here is means that no exception has been raised
    EXAM_ERROR( "Predicate exception expected" );
  }
  catch (runtime_error const&)
  { /*OK bad predicate has been detected.*/ }

  try {
    vector<int> result(s);
    partial_sort_copy(numbers, numbers + s, result.begin(), result.end(), less_equal<int>());

    //Here is means that no exception has been raised
    EXAM_ERROR( "Predicate exception expected" );
  }
  catch (runtime_error const&)
  { /*OK bad predicate has been detected.*/ }

#else  // _STLP_DO_CHECK_BAD_PREDICATE
  throw exam::skip_exception();
#endif // _STLP_DO_CHECK_BAD_PREDICATE
  return EXAM_RESULT;
}
