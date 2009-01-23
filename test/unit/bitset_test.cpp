#include "bitset_test.h"

#include <bitset>
#include <algorithm>
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <sstream>
#endif

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(bitset_test::bitset1)
{
  bitset<13U> b1(0xFFFF);
  bitset<13U> b2(0x1111);
  EXAM_CHECK(b1.size() == 13);
  EXAM_CHECK(b1 == 0x1FFF);
  EXAM_CHECK(b2.size() == 13);
  EXAM_CHECK(b2 == 0x1111);

#if !defined (STLPORT) || !defined (_STLP_NON_TYPE_TMPL_PARAM_BUG)
  b1 = b1 ^ (b2 << 2);
  EXAM_CHECK(b1 == 0x1BBB);

  EXAM_CHECK(b1.count() == 10);
  EXAM_CHECK(b2.count() == 4);

#  if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  size_t __pos = b2._Find_first();
  EXAM_CHECK( __pos == 0 );
  __pos = b2._Find_next(__pos);
  EXAM_CHECK( __pos == 4 );
  __pos = b2._Find_next(__pos);
  EXAM_CHECK( __pos == 8 );
  __pos = b2._Find_next(__pos);
  EXAM_CHECK( __pos == 12 );
  __pos = b2._Find_next(__pos);
  EXAM_CHECK( __pos == 13 );
#  endif
#endif

#if !defined (_STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS)
  string representation = b2.to_string<char, char_traits<char>, allocator<char> >();
  EXAM_CHECK( representation == "1000100010001" );
#  if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  wstring wrepresentation = b2.to_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >();
  EXAM_CHECK( wrepresentation == L"1000100010001" );
#  endif
#else
  EXAM_CHECK( b2.to_string() == "1000100010001" );
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(bitset_test::iostream)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
  {
    stringstream sstr;
    bitset<13U> b(0x1111);
    sstr << b;
    EXAM_CHECK( sstr.str() == "1000100010001" );

    bitset<13U> b1;
    sstr >> b1;
    EXAM_CHECK( b1.test(0) );
    EXAM_CHECK( b1.test(4) );
    EXAM_CHECK( b1.test(8) );
    EXAM_CHECK( b1.test(12) );
  }
#  if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  {
    wstringstream sstr;
    bitset<13U> b(0x1111);
    sstr << b;
    EXAM_CHECK( sstr.str() == L"1000100010001" );

    bitset<13U> b1;
    sstr >> b1;
    EXAM_CHECK( b1.test(0) );
    EXAM_CHECK( b1.test(4) );
    EXAM_CHECK( b1.test(8) );
    EXAM_CHECK( b1.test(12) );
  }
#  endif
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
