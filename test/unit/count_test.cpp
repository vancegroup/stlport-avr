#include "count_test.h"

#include <algorithm>
#include <vector>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(count_test::count0)
{
  int numbers[10] = { 1, 2, 4, 1, 2, 4, 1, 2, 4, 1 };

  int result = count(numbers, numbers + 10, 1);
  EXAM_CHECK(result==4);
#if defined (STLPORT) && !defined (_STLP_NO_ANACHRONISMS)
  result = 0;
  count(numbers, numbers + 10, 1, result);
  EXAM_CHECK(result==4);
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(count_test::count1)
{
  vector <int> numbers(100);
  for(int i = 0; i < 100; i++)
  numbers[i] = i % 3;
  int elements = count(numbers.begin(), numbers.end(), 2);
  EXAM_CHECK(elements==33);
#if defined (STLPORT) && !defined (_STLP_NO_ANACHRONISMS)
  elements = 0;
  count(numbers.begin(), numbers.end(), 2, elements);
  EXAM_CHECK(elements==33);
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(count_test::countif1)
{
  vector <int> numbers(100);
  for(int i = 0; i < 100; i++)
    numbers[i] = i % 3;
  int elements = count_if(numbers.begin(), numbers.end(), odd);
  EXAM_CHECK(elements==33);
#if defined (STLPORT) && !defined (_STLP_NO_ANACHRONISMS)
  elements = 0;
  count_if(numbers.begin(), numbers.end(), odd, elements);
  EXAM_CHECK(elements==33);
#endif

  return EXAM_RESULT;
}

int count_test::odd(int a_)
{
  return a_ % 2;
}
