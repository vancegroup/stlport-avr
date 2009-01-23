#include "uninitialized_test.h"

#include <memory>
#include <vector>
#include <list>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

struct NotTrivialCopyStruct {
  NotTrivialCopyStruct() : member(0) {}
  NotTrivialCopyStruct(NotTrivialCopyStruct const&) : member(1) {}

  int member;
};

struct TrivialCopyStruct {
  TrivialCopyStruct() : member(0) {}
  TrivialCopyStruct(TrivialCopyStruct const&) : member(1) {}

  int member;
};

struct TrivialInitStruct {
  TrivialInitStruct()
  { ++nbConstructorCalls; }

  static size_t nbConstructorCalls;
};

size_t TrivialInitStruct::nbConstructorCalls = 0;

#if defined (STLPORT)
#  if defined (_STLP_USE_NAMESPACES)
namespace std {
#  endif
namespace tr1 {

  template <>
  struct has_trivial_default_constructor<TrivialCopyStruct> :
        public false_type
  { };

  //This is a wrong declaration just to check that internaly a simple memcpy is called:
  template <>
  struct has_trivial_copy_constructor<TrivialCopyStruct> :
        public true_type
  { };

  template <>
  struct has_trivial_assign<TrivialCopyStruct> :
        public true_type
  { };

  template <>
  struct has_trivial_destructor<TrivialCopyStruct> :
        public true_type
  { };

  //This is a wrong declaration just to check that internaly no initialization is done:
  template <>
  struct has_trivial_default_constructor<TrivialInitStruct> :
        public true_type
  { };

  template <>
  struct has_trivial_copy_constructor<TrivialInitStruct> :
        public true_type
  { };

  template <>
  struct has_trivial_assign<TrivialInitStruct> :
        public true_type
  { };

  template <>
  struct has_trivial_destructor<TrivialInitStruct> :
        public true_type
  { };

} // namespace tr1

#  if defined (_STLP_USE_NAMESPACES)
}
#  endif
#endif

struct base {};
struct derived : public base {};

int EXAM_IMPL(uninitialized_test::copy_test)
{
  {
    //Random iterators
    {
      vector<NotTrivialCopyStruct> src(10);
      vector<NotTrivialCopyStruct> dst(10);
      uninitialized_copy(src.begin(), src.end(), dst.begin());
      vector<NotTrivialCopyStruct>::const_iterator it(dst.begin()), end(dst.end());
      for (; it != end; ++it) {
        EXAM_CHECK( (*it).member == 1 );
      }
    }
    {
      /** Note: we use static arrays here so the iterators are always
      pointers, even in debug mode. */
      size_t const count = 10;
      TrivialCopyStruct src[count];
      TrivialCopyStruct dst[count];

      TrivialCopyStruct* it = src + 0;
      TrivialCopyStruct* end = src + count;
      for (; it != end; ++it) {
        (*it).member = 0;
      }

      uninitialized_copy(src+0, src+count, dst+0);
      for (it = dst+0, end = dst+count; it != end; ++it) {
#if defined (STLPORT)
        /* If the member is 1, it means that library has not found any
        optimization oportunity and called the regular copy-ctor instead. */
        EXAM_CHECK( (*it).member == 0 );
#else
        EXAM_CHECK( (*it).member == 1 );
#endif
      }
    }
  }

  {
    //Bidirectional iterator
    {
      vector<NotTrivialCopyStruct> src(10);
      list<NotTrivialCopyStruct> dst(10);

      list<NotTrivialCopyStruct>::iterator it(dst.begin()), end(dst.end());
      for (; it != end; ++it) {
        (*it).member = -1;
      }

      uninitialized_copy(src.begin(), src.end(), dst.begin());

      for (it = dst.begin(); it != end; ++it) {
        EXAM_CHECK( (*it).member == 1 );
      }
    }

    {
      list<NotTrivialCopyStruct> src(10);
      vector<NotTrivialCopyStruct> dst(10);

      vector<NotTrivialCopyStruct>::iterator it(dst.begin()), end(dst.end());
      for (; it != end; ++it) {
        (*it).member = -1;
      }

      uninitialized_copy(src.begin(), src.end(), dst.begin());

      for (it = dst.begin(); it != end; ++it) {
        EXAM_CHECK( (*it).member == 1 );
      }
    }
  }

  {
    //Using containers of native types:
    {
      vector<int> src;
      int i;
      for (i = -5; i < 6; ++i) {
        src.push_back(i);
      }

      //Building a vector result in a uninitialized_copy call internally
      vector<unsigned int> dst(src.begin(), src.end());
      vector<unsigned int>::const_iterator it(dst.begin());
      for (i = -5; i < 6; ++i, ++it) {
        EXAM_CHECK( *it == (unsigned int)i );
      }
    }

    {
      vector<char> src;
      char i;
      for (i = -5; i < 6; ++i) {
        src.push_back(i);
      }

      //Building a vector result in a uninitialized_copy call internally
      vector<unsigned int> dst(src.begin(), src.end());
      vector<unsigned int>::const_iterator it(dst.begin());
      for (i = -5; i < 6; ++i, ++it) {
        EXAM_CHECK( *it == (unsigned int)i );
      }
    }

    {
      vector<int> src;
      int i;
      for (i = -5; i < 6; ++i) {
        src.push_back(i);
      }

      //Building a vector result in a uninitialized_copy call internally
      vector<float> dst(src.begin(), src.end());
      vector<float>::const_iterator it(dst.begin());
      for (i = -5; i < 6; ++i, ++it) {
        EXAM_CHECK( *it == (float)i );
      }
    }

    {
      vector<vector<float>*> src(10);
      vector<vector<float>*> dst(src.begin(), src.end());
    }

    {
      derived d;
      //base *pb = &d;
      derived *pd = &d;
      //base **ppb = &pd;
      vector<derived*> src(10, pd);
      vector<base*> dst(src.begin(), src.end());
      vector<base*>::iterator it(dst.begin()), end(dst.end());
      for (; it != end; ++it) {
        EXAM_CHECK( (*it) == pd );
      }
    }
  }

  {
    //Vector initialization:
    vector<TrivialInitStruct> vect(10);
    //Just 1 constructor call for the default value:
    EXAM_CHECK( TrivialInitStruct::nbConstructorCalls == 1  );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(uninitialized_test::fill_test)
{
  throw exam::skip_exception();
  return EXAM_RESULT;
}

int EXAM_IMPL(uninitialized_test::fill_n_test)
{
  throw exam::skip_exception();
  return EXAM_RESULT;
}
