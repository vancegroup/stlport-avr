#include "config_test.h"

#include <new>
#include <vector>

#if defined (_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(config_test::placement_new_bug)
{
#if defined (STLPORT)
  int int_val = 1;
  int *pint;
  pint = new(&int_val) int();
  EXAM_CHECK( pint == &int_val );
#  if defined (_STLP_DEF_CONST_PLCT_NEW_BUG)
  EXAM_CHECK( int_val != 0 );
#  else
  EXAM_CHECK( int_val == 0 );
#  endif
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(config_test::endianess)
{
#if defined (STLPORT)
  int val = 0x01020304;
  char *ptr = (char*)(&val);
#  if defined (_STLP_BIG_ENDIAN)
  //This test only work if sizeof(int) == 4, this is a known limitation
  //that will be handle the day we find a compiler for which it is false.
  EXAM_CHECK( *ptr == 0x01 ||
              sizeof(int) > 4 && *ptr == 0x00 );
#  elif defined (_STLP_LITTLE_ENDIAN)
  EXAM_CHECK( *ptr == 0x04 );
#  endif
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(config_test::template_function_partial_ordering)
{
#if defined (STLPORT)
  vector<int> vect1(10, 0);
  int* pvect1Front = &vect1.front();
  vector<int> vect2(10, 0);
  int* pvect2Front = &vect2.front();

  swap(vect1, vect2);

#  if defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER) || defined (_STLP_USE_PARTIAL_SPEC_WORKAROUND)
  EXAM_CHECK( pvect1Front == &vect2.front() );
  EXAM_CHECK( pvect2Front == &vect1.front() );
#  else
  EXAM_CHECK( pvect1Front != &vect2.front() );
  EXAM_CHECK( pvect2Front != &vect1.front() );
#  endif
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(config_test::new_throw_bad_alloc)
{
#if defined (STLPORT) && defined (_STLP_USE_EXCEPTIONS)
  try
  {
  /* We try to exhaust heap memory. However, we don't actually use the
    largest possible size_t value bus slightly less in order to avoid
    triggering any overflows due to the allocator adding some more for
    its internal data structures. */
    size_t const huge_amount = size_t(-1) - 1024;
    void* pvoid = operator new (huge_amount);
#if !defined (_STLP_NEW_DONT_THROW_BAD_ALLOC)
    // Allocation should have fail
    EXAM_CHECK( pvoid != 0 );
#endif
    // Just in case it succeeds:
    operator delete(pvoid);
  }
  catch (const bad_alloc&)
  {
#if defined (_STLP_NEW_DONT_THROW_BAD_ALLOC)
    // Looks like your compiler new operator finally throw bad_alloc, you can fix
    // configuration.
    EXAM_ERROR("bad_alloc error");
#endif
  }
  catch (...)
  {
    //We shouldn't be there:
    //Not bad_alloc exception thrown.
    EXAM_ERROR("bad_alloc error");
  }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
