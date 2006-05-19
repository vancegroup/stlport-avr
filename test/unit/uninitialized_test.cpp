#include <memory>
#include <vector>
#include <list>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class UninitializedTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(UninitializedTest);
  CPPUNIT_TEST(copy_test);
  //CPPUNIT_TEST(fill_test);
  //CPPUNIT_TEST(fill_n_test);
  CPPUNIT_TEST_SUITE_END();

protected:
  void copy_test();
  void fill_test();
  void fill_n_test();
};

CPPUNIT_TEST_SUITE_REGISTRATION(UninitializedTest);

struct NotTrivialData {
  NotTrivialData() : member(0) {}
  NotTrivialData(NotTrivialData const&) : member(1) {}

  int member;
};

struct TrivialData {
  TrivialData() : member(0) {}
  TrivialData(TrivialData const&) : member(1) {}

  int member;
};

#if defined (STLPORT)
namespace std
{
  _STLP_TEMPLATE_NULL
  struct __type_traits<TrivialData> {
     typedef __false_type has_trivial_default_constructor;
     //This is a wrong declaration just to check that internaly a simple memcpy is called:
     typedef __true_type has_trivial_copy_constructor;
     typedef __true_type has_trivial_assignment_operator;
     typedef __true_type has_trivial_destructor;
     typedef __false_type is_POD_type;
  };
}
#endif

//
// tests implementation
//
void UninitializedTest::copy_test()
{
  {
    //Random iterators
    {
      vector<NotTrivialData> src(10);
      vector<NotTrivialData> dst(10);
      uninitialized_copy(src.begin(), src.end(), dst.begin());
      vector<NotTrivialData>::const_iterator it(dst.begin()), end(dst.end());
      for (; it != end; ++it) {
        CPPUNIT_ASSERT( (*it).member == 1 );
      }
    }
    {
      /** Note: we use static arrays here so the iterators are always 
      pointers, even in debug mode. */
      size_t const count = 10;
      TrivialData src[count];
      TrivialData dst[count];

      TrivialData* it(src+0);
      TrivialData* end(src+count);
      for (; it != end; ++it) {
        (*it).member = 0;
      }

      uninitialized_copy(src+0, src+count, dst+0);
      for (it = dst+0, end = dst+count; it != end; ++it) {
#if defined (STLPORT)
        /* If the member is 1, it means that library has not found any 
        optimization oportunity and called the regular copy-ctor instead. */
        CPPUNIT_ASSERT( (*it).member == 0 );
#else
        CPPUNIT_ASSERT( (*it).member == 1 );
#endif
      }
    }
  }

  {
    //Bidirectional iterator
    {
      vector<NotTrivialData> src(10);
      list<NotTrivialData> dst(10);

      list<NotTrivialData>::iterator it(dst.begin()), end(dst.end());
      for (; it != end; ++it) {
        (*it).member = -1;
      }

      uninitialized_copy(src.begin(), src.end(), dst.begin());

      for (it = dst.begin(); it != end; ++it) {
        CPPUNIT_ASSERT( (*it).member == 1 );
      }
    }

    {
      list<NotTrivialData> src(10);
      vector<NotTrivialData> dst(10);

      vector<NotTrivialData>::iterator it(dst.begin()), end(dst.end());
      for (; it != end; ++it) {
        (*it).member = -1;
      }

      uninitialized_copy(src.begin(), src.end(), dst.begin());

      for (it = dst.begin(); it != end; ++it) {
        CPPUNIT_ASSERT( (*it).member == 1 );
      }
    }
  }
}

/*
void UninitializedTest::fill_test()
{
}

void UninitializedTest::fill_n_test()
{
}
*/
