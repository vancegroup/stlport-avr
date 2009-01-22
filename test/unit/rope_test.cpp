#include "rope_test.h"

//Small header to get STLport numerous defines:
#include <utility>

#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
#  include <rope>

#  if !defined (_STLP_USE_NO_IOSTREAMS)
#    include <sstream>
#  endif
#endif

// #include <stdlib.h> // for rand etc

#if defined (_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(rope_test::io)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS) && !defined (_STLP_USE_NO_IOSTREAMS) 
  char const* cstr = "rope test string";
  crope rstr(cstr);

  {
    ostringstream ostr;
    ostr << rstr;

    EXAM_CHECK( ostr );
    EXAM_CHECK( ostr.str() == cstr );
  }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(rope_test::find1)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS) 
  crope r("Fuzzy Wuzzy was a bear");
  crope::size_type n = r.find( "hair" );
  EXAM_CHECK( n == crope::npos );

  n = r.find("ear");

  EXAM_CHECK( n == (r.size() - 3) );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(rope_test::find2)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS) 
  crope r("Fuzzy Wuzzy was a bear");
  crope::size_type n = r.find( 'e' );
  EXAM_CHECK( n == (r.size() - 3) );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(rope_test::construct_from_char)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS) 
  crope r('1');
  char const* s = r.c_str();
  EXAM_CHECK( '1' == s[0] && '\0' == s[1] );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

// Test used for a bug report from Peter Hercek
int EXAM_IMPL(rope_test::bug_report)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS) 
  //first create a rope bigger than crope::_S_copy_max = 23
  // so that any string addition is added to a new leaf
  crope evilRope("12345678901234567890123_");
  //crope* pSevenCharRope( new TRope("1234567") );
  crope sevenCharRope0("12345678");
  crope sevenCharRope1("1234567");
  // add _Rope_RopeRep<c,a>::_S_alloc_granularity-1 = 7 characters
  evilRope += "1234567"; // creates a new leaf
  crope sevenCharRope2("1234567");
  // add one more character to the leaf
  evilRope += '8'; // here is the write beyond the allocated memory
  EXAM_CHECK( strcmp(sevenCharRope2.c_str(), "1234567") == 0 );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
const char str[] = "ilcpsklryvmcpjnbpbwllsrehfmxrkecwitrsglrexvtjmxypu\
nbqfgxmuvgfajclfvenhyuhuorjosamibdnjdbeyhkbsomblto\
uujdrbwcrrcgbflqpottpegrwvgajcrgwdlpgitydvhedtusip\
pyvxsuvbvfenodqasajoyomgsqcpjlhbmdahyviuemkssdslde\
besnnngpesdntrrvysuipywatpfoelthrowhfexlwdysvspwlk\
fblfdf";

crope create_rope( int len )
{
   int l = len/2;
   crope result;
   if(l <= 2)
   {
      static int j = 0;
      for(int i = 0; i < len; ++i)
      {
         // char c = 'a' + rand() % ('z' - 'a');
         result.append(1, /* c */ str[j++] );
         j %= sizeof(str);
      }
   }
   else
   {
      result = create_rope(len/2);
      result.append(create_rope(len/2));
   }
   return result;
}

#endif

int EXAM_IMPL(rope_test::test_saved_rope_iterators)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS) 
   //
   // Try and create a rope with a complex tree structure:
   //
   // srand(0);
   crope r = create_rope(300);
   string expected(r.begin(), r.end());
   EXAM_CHECK(expected.size() == r.size());
   EXAM_CHECK(equal(expected.begin(), expected.end(), r.begin()));
   crope::const_iterator i(r.begin()), j(r.end());
   int pos = 0;
   while(i != j)
   {
      crope::const_iterator k;
      // This initial read triggers the bug:
      EXAM_CHECK(*i);
      k = i;
      int newpos = pos;
      // Now make sure that i is incremented into the next leaf:
      while(i != j)
      {
         EXAM_CHECK(*i == expected[newpos]);
         ++i;
         ++newpos;
      }
      // Back up from stored value and continue:
      i = k;
      ++i;
      ++pos;
   }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
