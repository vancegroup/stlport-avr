#include "iter_test.h"

#include <string>
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <sstream>
#  include <vector>
#  include <iterator>
#endif

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(ioiter_test::ioiterat_test)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
  char c;
  const char *pc;
  const char *strorg = "abcd";
  string tmp;

  string objStr(strorg);

  istringstream objIStrStrm1(objStr);
  istringstream objIStrStrm2(objStr);
  istringstream objIStrStrm3(objStr);

  pc = strorg;
  string::size_type sz = strlen(strorg);
  string::size_type i;
  for ( i = 0; i < sz; ++i ) {
    c = *pc++;
    tmp += c;
  }
  EXAM_CHECK( tmp == "abcd" );

  istreambuf_iterator<char, char_traits<char> > objIStrmbIt1( objIStrStrm1.rdbuf() );
  istreambuf_iterator<char, char_traits<char> > end;

  tmp.clear();

  for ( i = 0; i < sz /* objIStrmbIt1 != end */; ++i ) {
    c = *objIStrmbIt1++;
    tmp += c;
  }
  EXAM_CHECK( tmp == "abcd" );

  tmp.clear();

  istreambuf_iterator<char, char_traits<char> > objIStrmbIt2( objIStrStrm2.rdbuf() );
  for ( i = 0; i < sz; ++i ) {
    c = *objIStrmbIt2;
    tmp += c;
    objIStrmbIt2++;
  }
  EXAM_CHECK( tmp == "abcd" );

  tmp.clear();

  istreambuf_iterator<char, char_traits<char> > objIStrmbIt3( objIStrStrm3.rdbuf() );

  while ( objIStrmbIt3 != end ) {
    c = *objIStrmbIt3++;
    tmp += c;
  }
  EXAM_CHECK( tmp == "abcd" );

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(ioiter_test::assign_test)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
  stringstream s( "1234567890" );
  vector<char> v;

  v.assign( istreambuf_iterator<char>(s), istreambuf_iterator<char>() );
  EXAM_CHECK( v.size() == 10 );
  if ( v.size() == 10 ) {
    EXAM_CHECK( v[0] == '1' );
    EXAM_CHECK( v[9] == '0' );
  }

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(ioiter_test::assign2_test)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
  stringstream s( "1234567890" );
  vector<char> v;

  v.assign( istreambuf_iterator<char>(s.rdbuf()), istreambuf_iterator<char>() );
  EXAM_CHECK( v.size() == 10 );
  if ( v.size() == 10 ) {
    EXAM_CHECK( v[0] == '1' );
    EXAM_CHECK( v[9] == '0' );
  }

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
