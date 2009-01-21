#include "bind_test.h"

#include <algorithm>
#include <functional>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

class pre_increment : public binary_function<int, int, int> {
public:
  int operator()(int incr, int& val) const
  { return val += incr; }
};

class post_increment : public binary_function<int, int, int> {
public:
  int operator()(int& val, int incr) const
  { return val += incr; }
};

int EXAM_IMPL(bind_test::bind1st1)
{
  int array [3] = { 1, 2, 3 };
  int* p = remove_if((int*)array, (int*)array + 3, bind1st(less<int>(), 2));

  EXAM_CHECK(p == &array[2]);
  EXAM_CHECK(array[0] == 1);
  EXAM_CHECK(array[1] == 2);

  for_each((int*)array, (int*)array + 3, bind1st(pre_increment(), 1));
  EXAM_CHECK(array[0] == 2);
  EXAM_CHECK(array[1] == 3);
  EXAM_CHECK(array[2] == 4);

  for_each((int*)array, (int*)array + 3, bind2nd(post_increment(), 1));
  EXAM_CHECK(array[0] == 3);
  EXAM_CHECK(array[1] == 4);
  EXAM_CHECK(array[2] == 5);

  return EXAM_RESULT;
}

int EXAM_IMPL(bind_test::bind2nd1)
{
  int array [3] = { 1, 2, 3 };
  replace_if(array, array + 3, binder2nd<greater<int> >(greater<int>(), 2), 4);

  EXAM_CHECK(array[0]==1);
  EXAM_CHECK(array[1]==2);
  EXAM_CHECK(array[2]==4);

  return EXAM_RESULT;
}

int EXAM_IMPL(bind_test::bind2nd2)
{
  int array [3] = { 1, 2, 3 };
  replace_if(array, array + 3, bind2nd(greater<int>(), 2), 4);
  EXAM_CHECK(array[0]==1);
  EXAM_CHECK(array[1]==2);
  EXAM_CHECK(array[2]==4);

  return EXAM_RESULT;
}

int test_func1 (const int &param1, const int &param2) {
  return param1 + param2;
}

int test_func2 (int &param1, int param2) {
  param1 += param2;
  return param1 + param2;
}

int EXAM_IMPL(bind_test::bind2nd3)
{
#if defined (STLPORT) && \
    !defined (_STLP_NO_EXTENSIONS) && defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
  int array[3] = { 1, 2, 3 };
  transform(array, array + 3, array, bind2nd(ptr_fun(test_func1), 1));
  transform(array, array + 3, array, bind1st(ptr_fun(test_func1), -1));
  EXAM_CHECK(array[0] == 1);
  EXAM_CHECK(array[1] == 2);
  EXAM_CHECK(array[2] == 3);

  transform(array, array + 3, array, bind2nd(ptr_fun(test_func2), 10));
  EXAM_CHECK(array[0] == 21);
  EXAM_CHECK(array[1] == 22);
  EXAM_CHECK(array[2] == 23);
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

class A
{
  public:
    A() : m_n( 0 )
    {}

    void f( int n ) const {
#if defined (STLPORT)
      _STLP_MUTABLE(A, m_n) = n;
#else
      m_n = n;
#endif
    }

    int v() const
    { return m_n; }

  private:
    mutable int m_n;
};

int EXAM_IMPL(bind_test::bind_memfn)
{
#if defined (STLPORT) && \
    !defined (_STLP_NO_EXTENSIONS) && defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
  A array[3];

  for_each( array, array + 3, bind2nd( mem_fun_ref(&A::f), 12 ) );

  EXAM_CHECK( array[0].v() == 12 );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
