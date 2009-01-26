#include "shared_ptr_test.h"

#include <memory>
// #include <typeinfo>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

#if !defined(_STLP_NO_EXTENSIONS) && defined(_STLP_USE_BOOST_SUPPORT)
struct X;

struct X :
    public std::tr1::enable_shared_from_this<X>
{
};
#endif /* !_STLP_NO_EXTENSIONS && _STLP_USE_BOOST_SUPPORT */

int EXAM_IMPL(shared_ptr_test::shared_from_this)
{
#if !defined(_STLP_NO_EXTENSIONS) && defined(_STLP_USE_BOOST_SUPPORT)
  std::tr1::shared_ptr<X> p( new X );
  std::tr1::shared_ptr<X> q = p->shared_from_this();

  EXAM_CHECK( p == q );
  EXAM_CHECK( !(p < q) && !(q < p) ); // p and q share ownership
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
