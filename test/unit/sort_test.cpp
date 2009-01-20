#include "sort_test.h"

#include <vector>
#include <algorithm>
#include <functional>

#if defined (STLPORT) && defined (_STLP_DEBUG) && defined (_STLP_DEBUG_MODE_THROWS)
#  define _STLP_DO_CHECK_BAD_PREDICATE
#  include <stdexcept>
#endif

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(sort_test::stblsrt1)
{
  //Check that stable_sort do sort
  int numbers[6] = { 1, 50, -10, 11, 42, 19 };
  stable_sort(numbers, numbers + 6);
  //-10 1 11 19 42 50
  EXAM_CHECK(numbers[0]==-10);
  EXAM_CHECK(numbers[1]==1);
  EXAM_CHECK(numbers[2]==11);
  EXAM_CHECK(numbers[3]==19);
  EXAM_CHECK(numbers[4]==42);
  EXAM_CHECK(numbers[5]==50);

  char const* letters[6] = {"bb", "aa", "ll", "dd", "qq", "cc" };
  stable_sort(letters, letters + 6, string_less);
  // aa bb cc dd ll qq
  EXAM_CHECK( strcmp(letters[0], "aa") == 0 );
  EXAM_CHECK( strcmp(letters[1], "bb") == 0 );
  EXAM_CHECK( strcmp(letters[2], "cc") == 0 );
  EXAM_CHECK( strcmp(letters[3], "dd") == 0 );
  EXAM_CHECK( strcmp(letters[4], "ll") == 0 );
  EXAM_CHECK( strcmp(letters[5], "qq") == 0 );

  return EXAM_RESULT;
}

struct Data {
  Data(int index, int value)
    : m_index(index), m_value(value) {}

  bool operator == (const Data& other) const
  { return m_index == other.m_index && m_value == other.m_value; }
  bool operator < (const Data& other) const
  { return m_value < other.m_value; }

private:
  int m_index, m_value;
};

int EXAM_IMPL(sort_test::stblsrt2)
{
  //Check that stable_sort is stable:
  Data datas[] = {
    Data(0, 10),
    Data(1, 8),
    Data(2, 6),
    Data(3, 6),
    Data(4, 6),
    Data(5, 4),
    Data(6, 9)
  };
  stable_sort(datas, datas + 7);

  EXAM_CHECK( datas[0] == Data(5, 4) );
  EXAM_CHECK( datas[1] == Data(2, 6) );
  EXAM_CHECK( datas[2] == Data(3, 6) );
  EXAM_CHECK( datas[3] == Data(4, 6) );
  EXAM_CHECK( datas[4] == Data(1, 8) );
  EXAM_CHECK( datas[5] == Data(6, 9) );
  EXAM_CHECK( datas[6] == Data(0, 10) );

  return EXAM_RESULT;
}

int EXAM_IMPL(sort_test::sort1)
{
  int numbers[6] = { 1, 50, -10, 11, 42, 19 };

  sort(numbers, numbers + 6);
  // -10 1 11 19 42 50
  EXAM_CHECK(numbers[0]==-10);
  EXAM_CHECK(numbers[1]==1);
  EXAM_CHECK(numbers[2]==11);
  EXAM_CHECK(numbers[3]==19);
  EXAM_CHECK(numbers[4]==42);
  EXAM_CHECK(numbers[5]==50);

  return EXAM_RESULT;
}

int EXAM_IMPL(sort_test::sort2)
{
  int numbers[] = { 1, 50, -10, 11, 42, 19 };

  int count = sizeof(numbers) / sizeof(numbers[0]);
  sort(numbers, numbers + count, greater<int>());

  //  50 42 19 11 1 -10
  EXAM_CHECK(numbers[5]==-10);
  EXAM_CHECK(numbers[4]==1);
  EXAM_CHECK(numbers[3]==11);
  EXAM_CHECK(numbers[2]==19);
  EXAM_CHECK(numbers[1]==42);
  EXAM_CHECK(numbers[0]==50);

  return EXAM_RESULT;
}

int EXAM_IMPL(sort_test::sort3)
{
  vector<bool> boolVector;

  boolVector.push_back( true );
  boolVector.push_back( false );

  sort( boolVector.begin(), boolVector.end() );

  EXAM_CHECK(boolVector[0]==false);
  EXAM_CHECK(boolVector[1]==true);

  return EXAM_RESULT;
}

/*
 * A small utility class to check a potential compiler bug
 * that can result in a bad sort algorithm behavior. The type
 * _Tp of the SortTestFunc has to be SortTestAux without any
 * reference qualifier.
 */
struct SortTestAux {
  SortTestAux (bool &b) : _b(b)
  {}

  SortTestAux (SortTestAux const&other) : _b(other._b) {
    _b = true;
  }

  bool &_b;

private:
  //explicitely defined as private to avoid warnings:
  SortTestAux& operator = (SortTestAux const&);
};

template <class _Tp>
void SortTestFunc (_Tp) {
}

int EXAM_IMPL(sort_test::sort4)
{
  bool copy_constructor_called = false;
  SortTestAux instance(copy_constructor_called);
  SortTestAux &r_instance = instance;
  SortTestAux const& rc_instance = instance;

  SortTestFunc(r_instance);
  EXAM_CHECK(copy_constructor_called);
  copy_constructor_called = false;
  SortTestFunc(rc_instance);
  EXAM_CHECK(copy_constructor_called);

  return EXAM_RESULT;
}

int EXAM_IMPL(sort_test::bad_predicate_detected)
{
#if defined _STLP_DO_CHECK_BAD_PREDICATE
  int numbers[] = { 0, 0, 1, 0, 0, 1, 0, 0 };
  try {
    sort(numbers, numbers + sizeof(numbers) / sizeof(numbers[0]), less_equal<int>());

    //Here is means that no exception has been raised
    EXAM_ERROR("bad predicate detection");
  }
  catch (runtime_error const&)
  { /*OK bad predicate has been detected.*/ }

  try {
    stable_sort(numbers, numbers + sizeof(numbers) / sizeof(numbers[0]), less_equal<int>());

    //Here is means that no exception has been raised
    EXAM_ERROR("bad predicate detection");
  }
  catch (runtime_error const&)
  { /*OK bad predicate has been detected.*/ }

#  else  // _STLP_DO_CHECK_BAD_PREDICATE
  throw exam::skip_exception();
#  endif // _STLP_DO_CHECK_BAD_PREDICATE

  return EXAM_RESULT;
}
