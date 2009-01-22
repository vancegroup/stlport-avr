#include "iter_test.h"

#include <iterator>
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <string>
#  include <sstream>
#  include <algorithm>
#endif

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(ostream_iterator_test::ostmit0)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
  // not necessary, tested in copy_test
  int array [] = { 1, 5, 2, 4 };

  const char* text = "hello";

  ostringstream os;

  ostream_iterator<char> iter(os);
  copy(text, text + 5, iter);
  EXAM_CHECK(os.good());
  os << ' ';
  EXAM_CHECK(os.good());

  ostream_iterator<int> iter2(os);
  copy(array, array + 4, iter2);
  EXAM_CHECK(os.good());
  EXAM_CHECK(os.str() == "hello 1524");
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
