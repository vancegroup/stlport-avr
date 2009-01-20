#include "copy_test.h"

#include <algorithm>
#include <cstring>
#include <vector>
#include <iterator>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(copy_test::copy_array)
{
  char string[23] = "A string to be copied.";
  char result[23];
  copy(string, string + 23, result);
  EXAM_CHECK(!strncmp(string, result, 23));

  return EXAM_RESULT;
}

int EXAM_IMPL(copy_test::copy_volatile)
{
  {
    int a[] = {0, 1, 2, 3, 4, 5};
    const size_t size = sizeof(a) / sizeof(a[0]);
    volatile int va[size]; 
    copy(a, a + size, va);
    for (size_t i = 0; i != size; ++i) {
      EXAM_CHECK( a[i] == va[i] );
    }
  }

  {
    const int a[] = {0, 1, 2, 3, 4, 5};
    const size_t size = sizeof(a) / sizeof(a[0]);
    volatile int va[size]; 
    copy(a, a + size, va);
    for (size_t i = 0; i != size; ++i) {
      EXAM_CHECK( a[i] == va[i] );
    }
  }

  // Following code can be activated to check that it doesn't compiled
#if 0
  {
    int a[] = {0, 1, 2, 3, 4, 5};
    const size_t size = sizeof(a) / sizeof(a[0]);
    const volatile int va[size] = {5, 4, 3, 2, 1, 0}; 
    copy(a, a + size, va);
    for (size_t i = 0; i != size; ++i) {
      EXAM_CHECK( a[i] == va[i] );
    }
  }
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(copy_test::copy_vector)
{
  vector<int> v1(10);
  for (int i = 0; (size_t)i < v1.size(); ++i)
    v1[i] = i;

  vector<int> v2(v1.size());
  copy(v1.begin(), v1.end(), v2.begin());

  EXAM_CHECK( v2 == v1 );

  return EXAM_RESULT;
}

int EXAM_IMPL(copy_test::copy_insert)
{
  vector<int> v1(10);
  for (int loc = 0; (size_t)loc < v1.size(); ++loc)
    v1[loc] = loc;
  vector<int> v2;
  insert_iterator<vector<int> > i(v2, v2.begin());
  copy(v1.begin(), v1.end(), i);

  EXAM_CHECK( v2 == v1 );

  return EXAM_RESULT;
}

int EXAM_IMPL(copy_test::copy_back)
{
  vector<int> v1(10);
  for (int i = 0; (size_t)i < v1.size(); ++i)
    v1[i] = i;
  vector<int> v2(v1.size());
  copy_backward(v1.begin(), v1.end(), v2.end());

  EXAM_CHECK( v2 == v1 );

  return EXAM_RESULT;
}

int EXAM_IMPL(copy_test::copy_back_array)
{
  int numbers[5] = { 1, 2, 3, 4, 5 };

  int result[5];
  copy_backward(numbers, numbers + 5, (int*)result + 5);
  EXAM_CHECK(result[0]==numbers[0]);
  EXAM_CHECK(result[1]==numbers[1]);
  EXAM_CHECK(result[2]==numbers[2]);
  EXAM_CHECK(result[3]==numbers[3]);
  EXAM_CHECK(result[4]==numbers[4]);

  return EXAM_RESULT;
}
