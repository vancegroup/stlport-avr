#include "unary_test.h"

#include <vector>
#include "unary.h"
#include <algorithm>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(unary_test::unegate1)
{
  int array [3] = { 1, 2, 3 };
  //unary_negate<odd>::argument_type arg_val = 0;
  int* p = find_if((int*)array, (int*)array + 3, unary_negate<odd>(odd()));
  EXAM_CHECK((p != array + 3));
  EXAM_CHECK(*p==2);

  return EXAM_RESULT;
}

int EXAM_IMPL(unary_test::unegate2)
{
  int array [3] = { 1, 2, 3 };
  int* p = find_if((int*)array, (int*)array + 3, not1(odd()));
  EXAM_CHECK(p != array + 3);
  EXAM_CHECK(*p==2);

  return EXAM_RESULT;
}

bool test_func(int param) {
  return param < 3;
}

int EXAM_IMPL(unary_test::unegate3)
{
#if !defined (STLPORT) || defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
  int array [3] = { 1, 2, 3 };
  int* p = find_if((int*)array, (int*)array + 3, not1(ptr_fun(test_func)));
  EXAM_CHECK(p != array + 3);
  EXAM_CHECK(*p==3);
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(unary_test::ucompose1)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  int input [3] = { -1, -4, -16 };

  double output[3];
  transform((int*)input, (int*)input + 3, output, unary_compose<square_root, negate<int> >(square_root(), negate<int>()));

  EXAM_CHECK(output[0]==1);
  EXAM_CHECK(output[1]==2);
  EXAM_CHECK(output[2]==4);
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(unary_test::ucompose2)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  int input [3] = { -1, -4, -16 };

  double output [3];
  transform((int*)input, (int*)input + 3, output, compose1(square_root(), negate<int>()));

  EXAM_CHECK(output[0]==1);
  EXAM_CHECK(output[1]==2);
  EXAM_CHECK(output[2]==4);
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
