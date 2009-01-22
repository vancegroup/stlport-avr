#include "heap_test.h"

#include <vector>
#include <algorithm>
#include <functional>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(heap_test::mkheap1)
{
  int numbers[6] = { 5, 10, 4, 13, 11, 19 };

  make_heap(numbers, numbers + 6);
  EXAM_CHECK(numbers[0]==19);
  pop_heap(numbers, numbers + 6);
  EXAM_CHECK(numbers[0]==13);
  pop_heap(numbers, numbers + 5);
  EXAM_CHECK(numbers[0]==11);
  pop_heap(numbers, numbers + 4);
  EXAM_CHECK(numbers[0]==10);
  pop_heap(numbers, numbers + 3);
  EXAM_CHECK(numbers[0]==5);
  pop_heap(numbers, numbers + 2);
  EXAM_CHECK(numbers[0]==4);
  pop_heap(numbers, numbers + 1);

  return EXAM_RESULT;
}

int EXAM_IMPL(heap_test::mkheap2)
{
  int numbers[6] = { 5, 10, 4, 13, 11, 19 };

  make_heap(numbers, numbers + 6, greater<int>());

  EXAM_CHECK(numbers[0]==4);
  pop_heap(numbers, numbers + 6, greater<int>());
  EXAM_CHECK(numbers[0]==5);
  pop_heap(numbers, numbers + 5, greater<int>());
  EXAM_CHECK(numbers[0]==10);
  pop_heap(numbers, numbers + 4, greater<int>());
  EXAM_CHECK(numbers[0]==11);
  pop_heap(numbers, numbers + 3, greater<int>());
  EXAM_CHECK(numbers[0]==13);
  pop_heap(numbers, numbers + 2, greater<int>());
  EXAM_CHECK(numbers[0]==19);

  return EXAM_RESULT;
}

int EXAM_IMPL(heap_test::pheap1)
{
  vector<int> v;

  v.push_back(1);
  v.push_back(20);
  v.push_back(4);
  make_heap(v.begin(), v.end());

  v.push_back(7);
  push_heap(v.begin(), v.end());

  sort_heap(v.begin(), v.end());

  EXAM_CHECK(v[0]==1);
  EXAM_CHECK(v[1]==4);
  EXAM_CHECK(v[2]==7);
  EXAM_CHECK(v[3]==20);

  return EXAM_RESULT;
}

int EXAM_IMPL(heap_test::pheap2)
{
  vector<int> v;

  v.push_back(1);
  v.push_back(20);
  v.push_back(4);
  make_heap(v.begin(), v.end(), greater<int>());

  v.push_back(7);
  push_heap(v.begin(), v.end(), greater<int>());

  sort_heap(v.begin(), v.end(), greater<int>());

  EXAM_CHECK(v[0]==20);
  EXAM_CHECK(v[1]==7);
  EXAM_CHECK(v[2]==4);
  EXAM_CHECK(v[3]==1);

  return EXAM_RESULT;
}
