#include "reference_wrapper_test.h"

#include <functional>

#if !defined(_STLP_NO_EXTENSIONS) && defined(_STLP_USE_BOOST_SUPPORT)
#  include <typeinfo>
#endif

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(ref_wrapper_test::ref)
{
#if !defined(_STLP_NO_EXTENSIONS) && defined(_STLP_USE_BOOST_SUPPORT)
  typedef std::tr1::reference_wrapper<int> rr_type;

  EXAM_CHECK( (::boost::is_convertible<rr_type, int&>::value) );
  EXAM_CHECK( (::boost::is_same<rr_type::type, int>::value) );

  int i = 1;
  int j = 2;

  rr_type r1 = std::tr1::ref(i);

  EXAM_CHECK( r1.get() == 1 );

  r1 = std::tr1::ref(j);

  EXAM_CHECK( r1.get() == 2 );

  i = 3;

  EXAM_CHECK( r1.get() == 2 );

  j = 4;

  EXAM_CHECK( r1.get() == 4 );

  r1.get() = 5;

  EXAM_CHECK( j == 5 );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(ref_wrapper_test::cref)
{
#if !defined(_STLP_NO_EXTENSIONS) && defined(_STLP_USE_BOOST_SUPPORT)
  typedef std::tr1::reference_wrapper<const int> crr_type;

  EXAM_CHECK( (::boost::is_convertible<crr_type, const int&>::value) );
  EXAM_CHECK( (::boost::is_same<crr_type::type, const int>::value) );

  int i = 1;
  int j = 2;

  crr_type r1 = std::tr1::cref(i);

  EXAM_CHECK( r1.get() == 1 );

  r1 = std::tr1::cref(j);

  EXAM_CHECK( r1.get() == 2 );

  i = 3;

  EXAM_CHECK( r1.get() == 2 );

  j = 4;

  EXAM_CHECK( r1.get() == 4 );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
