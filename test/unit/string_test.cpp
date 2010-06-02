// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2004-2009
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

//Has to be first for StackAllocator swap overload to be taken
//into account (at least using GCC 4.0.1)
#include "stack_allocator.h"

#include "string_test.h"

//To make GLib C++ closer to STLport behavior we need this macro:
//Only mandatory when building unit tests without STLport, do not change
//anything when building with STLport
#define _GLIBCXX_FULLY_DYNAMIC_STRING

#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <sstream>
#endif

#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
#  include <stdexcept>
#endif

#if !defined (STLPORT) || defined (_STLP_THREADS)
#  if defined (STLPORT) && defined (_STLP_PTHREADS) || \
      defined (__GNUC__) && !defined (__MINGW32__)
#    define USE_PTHREAD_API
#    include <pthread.h>
#  endif

#  if defined (STLPORT) && defined (_STLP_WIN32THREADS) || \
      defined (__GNUC__) && defined (__MINGW32__) || \
      defined (_MSC_VER)
#    define USE_WINDOWS_API
#    include <windows.h>
#  endif
#endif

#include "stack_allocator.h"

#ifdef __unix__
#include <sys/mman.h>
#include <unistd.h>
#endif

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

static string func( const string& par )
{
  string tmp( par );
  return tmp;
}

#if defined (USE_PTHREAD_API) || defined (USE_WINDOWS_API)
#  if defined (USE_PTHREAD_API)
static void* f(void*)
#  else
static DWORD __stdcall f(void*)
#  endif
{
  string s( "qyweyuewunfkHBUKGYUGL,wehbYGUW^(@T@H!BALWD:h^&@#*@(#:JKHWJ:CND" );

  for ( int i = 0; i < 2000000; ++i ) {
    string sx = func( s );
  }

  return 0;
}
#endif

int EXAM_IMPL(string_test::constructor)
{
#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    string s((size_t)-1, 'a');
    EXAM_ERROR( "length_error exception expected" );
  }
  catch (length_error const&) {
    EXAM_MESSAGE( "length_error exception, as expected" );
  }
  catch (...) {
    //Expected exception is length_error:
    EXAM_ERROR( "length_error exception expected" );
  }
#else
  // throw exam::skip_exception();
  EXAM_ERROR( "Bad platform. Exception required" );
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::trivial_char_compare)
{
  string s( "message" );

  EXAM_CHECK( s == "message" );
  EXAM_CHECK( "message" == s );

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::reserve)
{
  string s;
#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    s.reserve(s.max_size() + 1);
    EXAM_ERROR( "length_error exception expected" );
  }
  catch (length_error const&) {
    EXAM_MESSAGE( "length_error exception, as expected" );
  }
  catch (...) {
    //Expected exception is length_error:
    EXAM_ERROR( "length_error exception expected" );
  }
#else
  // throw exam::skip_exception();
  EXAM_ERROR( "Bad platform. Exception required" );
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::mt)
{
#if defined (USE_PTHREAD_API) || defined (USE_WINDOWS_API)
  const int nth = 2;
#  if defined (USE_PTHREAD_API)
  pthread_t t[nth];

  for ( int i = 0; i < nth; ++i ) {
    pthread_create( &t[i], 0, f, 0 );
  }

  for ( int i = 0; i < nth; ++i ) {
    pthread_join( t[i], 0 );
  }
#  endif // PTHREAD

#  if defined (USE_WINDOWS_API)
  //DWORD start = GetTickCount();

  HANDLE t[nth];

  int i; // VC6 not support in-loop scope of cycle var
  for ( i = 0; i < nth; ++i ) {
    t[i] = CreateThread(NULL, 0, f, 0, 0, NULL);
  }

  if (WaitForMultipleObjects(nth, t, TRUE, INFINITE) == WAIT_FAILED) {
    // On some platforms (evc3/evc4) WaitForMultipleObjects() with fWaitAll == TRUE
    // is not supported. We then wait with a loop on each thread:
    for ( i = 0; i < nth; ++i ) {
      WaitForSingleObject(t[i], INFINITE);
    }
  }

  /*
  DWORD duration = GetTickCount() - start;
  ostringstream ostr;
  ostr << "Duration: " << duration << endl;
  EXAM_MESSAGE(ostr.str().c_str());
  */
#  endif
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::short_string)
{
  string const ref_short_str1("str1"), ref_short_str2("str2");
  string short_str1(ref_short_str1), short_str2(ref_short_str2);
  string const ref_long_str1("str                                                  1");
  string const ref_long_str2("str                                                  2");
  string long_str1(ref_long_str1), long_str2(ref_long_str2);

  EXAM_CHECK(short_str1 == ref_short_str1);
  EXAM_CHECK(long_str1 == ref_long_str1);

  {
    string str1(short_str1);
    str1 = long_str1;
    EXAM_CHECK(str1 == ref_long_str1);
  }

  {
    string str1(long_str1);
    str1 = short_str1;
    EXAM_CHECK(str1 == ref_short_str1);
  }

  {
    short_str1.swap(short_str2);
    EXAM_CHECK((short_str1 == ref_short_str2) && (short_str2 == ref_short_str1));
    short_str1.swap(short_str2);
  }

  {
    long_str1.swap(long_str2);
    EXAM_CHECK((long_str1 == ref_long_str2) && (long_str2 == ref_long_str1));
    long_str1.swap(long_str2);
  }

  {
    short_str1.swap(long_str1);
    EXAM_CHECK((short_str1 == ref_long_str1) && (long_str1 == ref_short_str1));
    short_str1.swap(long_str1);
  }

  {
    long_str1.swap(short_str1);
    EXAM_CHECK((short_str1 == ref_long_str1) && (long_str1 == ref_short_str1));
    long_str1.swap(short_str1);
  }

  {
    string a(256, 'a');
    string b(256, 'b');
    const char* as = a.c_str();
    const char* bs = b.c_str();
    swap(a, b);
    EXAM_CHECK( a.c_str() == bs );
    EXAM_CHECK( b.c_str() == as );
  }

  {
    //This is to test move constructor
    vector<string> str_vect;
    str_vect.push_back(short_str1);
    str_vect.push_back(long_str1);
    str_vect.push_back(short_str2);
    str_vect.push_back(long_str2);
    EXAM_CHECK((str_vect[0] == ref_short_str1) &&
                   (str_vect[1] == ref_long_str1) &&
                   (str_vect[2] == ref_short_str2) &&
                   (str_vect[3] == ref_long_str2));
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::erase)
{
  char const* c_str = "Hello, World!";
  string str(c_str);
  EXAM_CHECK( str == c_str );

  str.erase(str.begin() + 1, str.end() - 1); // Erase all but first and last.

  size_t i;
  for (i = 0; i < str.size(); ++i) {
    switch ( i ) {
      case 0:
        EXAM_CHECK( str[i] == 'H' );
        break;
      case 1:
        EXAM_CHECK( str[i] == '!' );
        break;
      default:
        EXAM_ERROR( "unexpected" );
    }
  }

  str.insert(1, c_str);
  str.erase(str.begin()); // Erase first element.
  str.erase(str.end() - 1); // Erase last element.
  EXAM_CHECK( str == c_str );
  str.clear(); // Erase all.
  EXAM_CHECK( str.empty() );

  str = c_str;
  EXAM_CHECK( str == c_str );

  str.erase(1, str.size() - 1); // Erase all but first and last.
  for (i = 0; i < str.size(); i++) {
    switch ( i ) {
      case 0:
        EXAM_CHECK( str[i] == 'H' );
        break;
      case 1:
        EXAM_CHECK( str[i] == '!' );
        break;
      default:
        EXAM_ERROR( "unexpected" );
    }
  }

  str.erase(1);
  EXAM_CHECK( str == "H" );

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::data)
{
  string xx;

  EXAM_CHECK( xx.data() != 0 );  // ISO-IEC-14882:1998(E), 21.3.6, paragraph 3
#if 0
  /* This test really not required: in ISO-IEC-14882:1998(E) paragraph 3 stated:
   * '... and can have zero added to it', again: 'CAN', but not 'MUST'.
   * That's why I am comment this test. But I don't remove it due to I had
   * unevident problem with misinterpretation of data() return (i.e. data()
   * and c_str() provide different functionality!) and expect that this is
   * more-or-less common pitfall.
   *    - ptr
   */
  string low( "2004-01-01" );
  // Blocks A and B should follow each other.
  // Block A:
  xx = "123456";
  xx += low;
  if ( strcmp( xx.data(), "1234562004-01-01" ) != 0 ) {
    return -1;
  }
  // End of block A

  // Block B:
  xx = "1234";
  xx += ";";

  if ( strcmp( xx.data(), "1234;" ) != 0 ) {
    return -1;
  }
  // End of block B
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::c_str)
{
  string low( "2004-01-01" );
  string xx;
  string yy;

  EXAM_CHECK( *(yy.c_str()) == '\0' ); // ISO-IEC-14882:1998(E), 21.3.6, paragraph 1

  // Blocks A and B should follow each other.
  // Block A:
  xx = "123456";
  xx += low;
  EXAM_CHECK( strcmp( xx.c_str(), "1234562004-01-01" ) == 0 );
  // End of block A

  // Block B:
  xx = "1234";
  xx += ";";
  EXAM_CHECK( strcmp( xx.c_str(), "1234;" ) == 0 );
  // End of block B

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::null_char)
{
  // ISO/IEC 14882:1998(E), ISO/IEC 14882:2003(E), 21.3.4 ('... the const version')
  const string s( "123456" );

  EXAM_CHECK( s[s.size()] == '\0' );

#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    //Check is only here to avoid warning about value of expression not used
    EXAM_CHECK( s.at(s.size()) == '\0' );
    EXAM_ERROR( "out_of_range exception expected" );
  }
  catch (out_of_range const&) {
    EXAM_MESSAGE( "out_of_range exception, as expected" );
  }
  catch ( ... ) {
    EXAM_ERROR( "out_of_range exception expected" );
  }
#else
  // throw exam::skip_exception();
  EXAM_ERROR( "Bad platform. Exception required" );
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::insert)
{
  string strorg = "This is test string for string calls";
  string str;
  /*
   * In case of reallocation there is no auto reference problem
   * so we reserve a big enough string to be sure to test this
   * particular point.
   */
  str.reserve(100);
  str = strorg;

  //test self insertion:
  str.insert(10, str.c_str() + 5, 15);
  EXAM_CHECK( str == "This is teis test string st string for string calls" );

  str = strorg;
  str.insert(15, str.c_str() + 5, 25);
  EXAM_CHECK( str == "This is test stis test string for stringring for string calls" );

  str = strorg;
  str.insert(0, str.c_str() + str.size() - 4, 4);
  EXAM_CHECK( str == "allsThis is test string for string calls" );

  str = strorg;
  str.insert(0, str.c_str() + str.size() / 2 - 1, str.size() / 2 + 1);
  EXAM_CHECK( str == "ng for string callsThis is test string for string calls" );

  str = strorg;
  string::iterator b = str.begin();
  string::const_iterator s = str.begin() + str.size() / 2 - 1;
  string::const_iterator e = str.end();
  str.insert( b, s, e );
  EXAM_CHECK( str == "ng for string callsThis is test string for string calls" );

  str = strorg;
  str.insert(str.begin(), str.begin() + str.size() / 2 - 1, str.end());
  EXAM_CHECK( str == "ng for string callsThis is test string for string calls" );

  vector<int> int_vect;
  //Just a compile time test:
  str.insert(str.end(), int_vect.begin(), int_vect.end());

  string str0;
  str0.insert(str0.begin(), 5, '0');
  EXAM_CHECK( str0 == "00000" );

  string str1;
  {
    string::size_type pos = 0, nb = 2;
    str1.insert(pos, nb, '1');
  }
  EXAM_CHECK( str1 == "11" );

  str0.insert(0, str1);
  EXAM_CHECK( str0 == "1100000" );

  string str2("2345");
  str0.insert(str0.size(), str2, 1, 2);
  EXAM_CHECK( str0 == "110000034" );

  str1.insert(str1.begin() + 1, 2, '2');
  EXAM_CHECK( str1 == "1221" );

  str1.insert(2, "333333", 3);
  EXAM_CHECK( str1 == "1233321" );

  str1.insert(4, "4444");
  EXAM_CHECK( str1 == "12334444321" );

  str1.insert(str1.begin() + 6, '5');
  EXAM_CHECK( str1 == "123344544321" );

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::replace)
{
  /*
   * This test case is for the non template basic_string::replace method,
   * this is why we play with the const iterators and reference to guaranty
   * that the right method is called.
   */
  const string v( "78" );
  string s( "123456" );
  string const& cs = s;

  string::iterator i = s.begin() + 1;
  s.replace(i, i + 3, v.begin(), v.end());
  EXAM_CHECK( s == "17856" );

  s = "123456";
  i = s.begin() + 1;
  s.replace(i, i + 1, v.begin(), v.end());
  EXAM_CHECK( s == "1783456" );

  s = "123456";
  i = s.begin() + 1;
  string::const_iterator ci = s.begin() + 1;
  s.replace(i, i + 3, ci + 3, cs.end());
  EXAM_CHECK( s == "15656" );

  s = "123456";
  i = s.begin() + 1;
  ci = s.begin() + 1;
  s.replace(i, i + 3, ci, ci + 2);
  EXAM_CHECK( s == "12356" );

  s = "123456";
  i = s.begin() + 1;
  ci = s.begin() + 1;
  s.replace(i, i + 3, ci + 1, cs.end());
  EXAM_CHECK( s == "1345656" );

  s = "123456";
  i = s.begin();
  ci = s.begin() + 1;
  s.replace(i, i, ci, ci + 1);
  EXAM_CHECK( s == "2123456" );

  s = "123456";
  s.replace(s.begin() + 4, s.end(), cs.begin(), cs.end());
  EXAM_CHECK( s == "1234123456" );

  /*
   * This is the test for the template replace method.
   */
  s = "123456";
  string::iterator b = s.begin() + 4;
  string::iterator e = s.end();
  string::const_iterator rb = s.begin();
  string::const_iterator re = s.end();
  s.replace(b, e, rb, re);
  EXAM_CHECK( s == "1234123456" );

  s = "123456";
  s.replace(s.begin() + 4, s.end(), s.begin(), s.end());
  EXAM_CHECK( s == "1234123456" );

  string strorg("This is test string for string calls");
  string str = strorg;
  str.replace(5, 15, str.c_str(), 10);
  EXAM_CHECK( str == "This This is tefor string calls" );

  str = strorg;
  str.replace(5, 5, str.c_str(), 10);
  EXAM_CHECK( str == "This This is test string for string calls" );

// #if ( !defined (STLPORT) && !defined(__GNUC__) )
  deque<char> cdeque;
  cdeque.push_back('I');
  str.replace(str.begin(), str.begin() + 11, cdeque.begin(), cdeque.end());
  EXAM_CHECK( str == "Is test string for string calls" );
// #endif

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::resize)
{
  string s;

  s.resize(0);

  EXAM_CHECK( *s.c_str() == 0 );

  s = "1234567";

  s.resize(0);
  EXAM_CHECK( *s.c_str() == 0 );

  s = "1234567";
  s.resize(1);
  EXAM_CHECK( s.size() == 1 );
  EXAM_CHECK( *s.c_str() == '1' );
  EXAM_CHECK( *(s.c_str() + 1) == 0 );

  s = "1234567";
  s.resize(10);
  EXAM_CHECK( s.size() == 10 );
  EXAM_CHECK( s[6] == '7' );
  EXAM_CHECK( s[7] == 0 );
  EXAM_CHECK( s[8] == 0 );
  EXAM_CHECK( s[9] == 0 );

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::find)
{
  string s("one two three one two three");
  EXAM_CHECK( s.find("one") == 0 );
  EXAM_CHECK( s.find('t') == 4 );
  EXAM_CHECK( s.find('t', 5) == 8 );
  //We are trying to get a const reference to the npos string static member to
  //force the compiler to allocate memory for this variable. It is used to reveal
  //a bug of STLport which was simply declaring npos without instanciating it.
#if defined (STLPORT) && defined (_STLP_STATIC_CONST_INIT_BUG)
  string::size_type const& npos_local = string::npos;
#else
#  define npos_local string::npos
#endif
  EXAM_CHECK( s.find("four") == npos_local );
  EXAM_CHECK( s.find("one", string::npos) == npos_local );

  EXAM_CHECK( s.find_first_of("abcde") == 2 );

  EXAM_CHECK( s.find_first_not_of("enotw ") == 9 );

  string empty;
  EXAM_CHECK( s.substr(s.find(empty), empty.size()) == empty );

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::bogus_edge_find)
{
  /* ISO/IEC 14882 2003, 21.3.6.1 basic_string::find [lib.string::find]
   *
   * size_type find(const basic_string<charT,traits,Allocator>& str,
   *                size_type pos = 0) const;
   * Effects: Determines the lowest position xpos, if possible, such that
   * both of the following conditions obtain:
   *    pos <= xpos and xpos + str.size() <= size();
   *    at(xpos+I) == str.at(I) for all elements I of the string controlled by str.
   * Returns: xpos if the function can determine such a value for xpos. Otherwise,
   * returns npos.
   * Notes: Uses traits::eq().
   *
   * ===
   * So, from formal point of view 
   *   string s; string::size_type p = s.find( "", 0, 0 );
   * should return 0 in p, i.e. position out-of-bound of string, so 
   * code like following is bad:
   * string s; 
   *  
   * string::size_type p = s.find( "", 0, 0 ); 
   *
   * ... 
   *
   * if ( p != string::npos ) { // normal 
   *   char ch = s[p]; // Arghhhhhhhhhh 
   * }
   *
   * People near Standard commete has opinion opposite to my. Even if it looks
   * like bogus behaviour for me, it should be fixed.
   */

  {
    string s;
    string::size_type p = s.find( "", 0, 0 );

    /* EXAM_CHECK( p == string::npos ); */
    EXAM_CHECK( p == 0 ); // bogus result, isn't it?
  }
  {
    string s( "123" );
    string::size_type p = s.find( "", 0, 0 );

    EXAM_CHECK( p == 0 );
  }
  {
    string s( "123" );
    string::size_type p = s.find( "", 1, 0 );

    EXAM_CHECK( p == 1 );
  }
  {
    string s( "" );
    string::size_type p = s.find( "", 1, 0 );

    EXAM_CHECK( p == string::npos );
  }
  {
    string s( "123" );
    string::size_type p = s.find( "", 3, 0 );

    EXAM_CHECK( p == 3 ); // bogus result, isn't it?
  }
  {
    string s;
    string::size_type p = s.rfind( "", 0, 0 );

    /* EXAM_CHECK( p == string::npos ); */
    EXAM_CHECK( p == 0 ); // bogus result, isn't it?
  }
  {
    string s( "123" );
    string::size_type p = s.rfind( "", 0, 0 );

    EXAM_CHECK( p == 0 );
  }
  {
    string s( "123" );
    string::size_type p = s.rfind( "", 1, 0 );

    EXAM_CHECK( p == 1 );
  }
  {
    string s( "" );
    string::size_type p = s.rfind( "", 1, 0 );

    EXAM_CHECK( p == 0 ); // bogus result, isn't it?
  }
  {
    string s( "123" );
    string::size_type p = s.rfind( "", 3, 0 );

    EXAM_CHECK( p == 3 ); // bogus result, isn't it?
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::rfind)
{
  // 21.3.6.2
  string s("one two three one two three");

  EXAM_CHECK( s.rfind("two") == 18 );
  EXAM_CHECK( s.rfind("two", 0) == string::npos );
  EXAM_CHECK( s.rfind("two", 11) == 4 );
  EXAM_CHECK( s.rfind('w') == 19 );

  string test( "aba" );

  EXAM_CHECK( test.rfind( "a", 2, 1 ) == 2 );
  EXAM_CHECK( test.rfind( "a", 1, 1 ) == 0 );
  EXAM_CHECK( test.rfind( "a", 0, 1 ) == 0 );

  EXAM_CHECK( test.rfind( 'a', 2 ) == 2 );
  EXAM_CHECK( test.rfind( 'a', 1 ) == 0 );
  EXAM_CHECK( test.rfind( 'a', 0 ) == 0 );

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::find_last_of)
{
  // 21.3.6.4
  string s("one two three one two three");

  EXAM_CHECK( s.find_last_of("abcde") == 26 );

  string test( "aba" );

  EXAM_CHECK( test.find_last_of( "a", 2, 1 ) == 2 );
  EXAM_CHECK( test.find_last_of( "a", 1, 1 ) == 0 );
  EXAM_CHECK( test.find_last_of( "a", 0, 1 ) == 0 );

  EXAM_CHECK( test.find_last_of( 'a', 2 ) == 2 );
  EXAM_CHECK( test.find_last_of( 'a', 1 ) == 0 );
  EXAM_CHECK( test.find_last_of( 'a', 0 ) == 0 );

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::find_last_not_of)
{
  // 21.3.6.6
  string s("one two three one two three");

  EXAM_CHECK( s.find_last_not_of("ehortw ") == 15 );

  string test( "aba" );

  EXAM_CHECK( test.find_last_not_of( "a", 2, 1 ) == 1 );
  EXAM_CHECK( test.find_last_not_of( "b", 2, 1 ) == 2 );
  EXAM_CHECK( test.find_last_not_of( "a", 1, 1 ) == 1 );
  EXAM_CHECK( test.find_last_not_of( "b", 1, 1 ) == 0 );
  EXAM_CHECK( test.find_last_not_of( "a", 0, 1 ) == string::npos );
  EXAM_CHECK( test.find_last_not_of( "b", 0, 1 ) == 0 );

  EXAM_CHECK( test.find_last_not_of( 'a', 2 ) == 1 );
  EXAM_CHECK( test.find_last_not_of( 'b', 2 ) == 2 );
  EXAM_CHECK( test.find_last_not_of( 'a', 1 ) == 1 );
  EXAM_CHECK( test.find_last_not_of( 'b', 1 ) == 0 );
  EXAM_CHECK( test.find_last_not_of( 'a', 0 ) == string::npos );
  EXAM_CHECK( test.find_last_not_of( 'b', 0 ) == 0 );

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::copy)
{
  string s("foo");
  char dest[4];
  dest[0] = dest[1] = dest[2] = dest[3] = 1;
  s.copy(dest, 4);
  int pos = 0;
  EXAM_CHECK( dest[pos++] == 'f' );
  EXAM_CHECK( dest[pos++] == 'o' );
  EXAM_CHECK( dest[pos++] == 'o' );
  EXAM_CHECK( dest[pos++] == 1 );

  dest[0] = dest[1] = dest[2] = dest[3] = 1;
  s.copy(dest, 4, 2);
  pos = 0;
  EXAM_CHECK( dest[pos++] == 'o' );
  EXAM_CHECK( dest[pos++] == 1 );

#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    s.copy(dest, 4, 5);
    EXAM_ERROR( "out_of_range exception expected" );
  }
  catch (out_of_range const&) {
    EXAM_MESSAGE( "out_of_range exception, as expected" );
  }
  catch ( ... ) {
    EXAM_ERROR( "out_of_range exception expected" );
  }
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::assign)
{
  string s;
  char const* cstr = "test string for assign";

  s.assign(cstr, cstr + 22);
  EXAM_CHECK( s == "test string for assign" );

  string s2("other test string");
  s.assign(s2);
  EXAM_CHECK( s == s2 );

  static string str1;
  static string str2;

  // short string optim:
  str1 = "123456";
  // longer than short string:
  str2 = "1234567890123456789012345678901234567890";

  EXAM_CHECK(str1[5] == '6');
  EXAM_CHECK(str2[29] == '0');

  return EXAM_RESULT;
}

/* This test is to check if string properly supports the short string
 * optimization. It has been found out that eMbedded Visual C++ 3.0 and .NET
 * compilers for the ARM platform fail to pass structs and classes of certain
 * size per value. This seems to be a known compiler bug. For other processors
 * (e.g. x86) the error doesn't occur.
 * (The ARM compiler creates a temporary object from teststr on the stack, to
 * pass it to the helper function. It uses the copy constructor for this.
 * After this the temporary object is copied to another place on the stack.
 * The result is that the _M_finish pointer then points to the wrong buffer
 * end and the size of the short string is incorrectly calculated.)
 */
int EXAM_IMPL(string_test::short_string_optim_bug)
{
   string teststr("shortest");

   bool short_string_optim_bug_helper(string teststr);

   EXAM_CHECK(true == short_string_optim_bug_helper(teststr));

  return EXAM_RESULT;
}

bool short_string_optim_bug_helper(string teststr)
{
   size_t ss = teststr.size();
   return (ss == 8);
}

int EXAM_IMPL(string_test::compare)
{
  string str1("abcdef");
  string str2;

  str2 = "abcdef";
  EXAM_CHECK( str1.compare(str2) == 0 );
  str2 = "abcde";
  EXAM_CHECK( str1.compare(str2) > 0 );
  str2 = "abcdefg";
  EXAM_CHECK( str1.compare(str2) < 0 );

  EXAM_CHECK( str1.compare("abcdef") == 0 );
  EXAM_CHECK( str1.compare("abcde") > 0 );
  EXAM_CHECK( str1.compare("abcdefg") < 0 );

  str2 = "cde";
  EXAM_CHECK( str1.compare(2, 3, str2) == 0 );
  str2 = "cd";
  EXAM_CHECK( str1.compare(2, 3, str2) > 0 );
  str2 = "cdef";
  EXAM_CHECK( str1.compare(2, 3, str2) < 0 );

  str2 = "abcdef";
  EXAM_CHECK( str1.compare(2, 3, str2, 2, 3) == 0 );
  EXAM_CHECK( str1.compare(2, 3, str2, 2, 2) > 0 );
  EXAM_CHECK( str1.compare(2, 3, str2, 2, 4) < 0 );

  EXAM_CHECK( str1.compare(2, 3, "cdefgh", 3) == 0 );
  EXAM_CHECK( str1.compare(2, 3, "cdefgh", 2) > 0 );
  EXAM_CHECK( str1.compare(2, 3, "cdefgh", 4) < 0 );

  return EXAM_RESULT;
}

/*
class mystring : public string {
public:
  mystring() {}
  mystring(string const& s) : string(s) {}

  mystring& operator = (string const& s) {
    string::operator = (s);
    return *this;
  };
};
*/

int EXAM_IMPL(string_test::template_expression)
{
  string one("one"), two("two"), three("three");
  string space(1, ' ');

  // check availability of [un]equality operators
  {
      // string-string
      one == two;
      one != two;
      // string-literal
      one == "two";
      one != "two";
      // literal-string
      "one" == two;
      "one" != two;
      // strsum-string
      (one + two) == three;
      (one + two) != three;
      // string-strsum
      one == (two + three);
      one != (two + three);
      // strsum-literal
      (one + two) == "three";
      (one + two) != "three";
      // literal-strsum
      "one" == (two + three);
      "one" != (two + three);
      // strsum-strsum
      (one + two) == (two + three);
      (one + two) != (two + three);
  }

  {
    string result(one + ' ' + two + ' ' + three);
    EXAM_CHECK( result == "one two three" );
  }

  {
    string result(one + ' ' + two + ' ' + three, 4);
    EXAM_CHECK( result == "two three" );
  }

  {
    string result(one + ' ' + two + ' ' + three, 4, 3);
    EXAM_CHECK( result == "two" );
  }

  //2 members expressions:
  EXAM_CHECK( (' ' + one) == " one" );
  EXAM_CHECK( (one + ' ') == "one " );
  EXAM_CHECK( (one + " two") == "one two" );
  EXAM_CHECK( ("one " + two) == "one two" );
  EXAM_CHECK( (one + space) == "one " );

  //3 members expressions:
  EXAM_CHECK( ((one + space) + "two") == "one two" );
  EXAM_CHECK( ("one" + (space + two)) == "one two" );
  EXAM_CHECK( ((one + space) + two) == "one two" );
  EXAM_CHECK( (one + (space + two)) == "one two" );
  EXAM_CHECK( ((one + space) + 't') == "one t" );
  EXAM_CHECK( ('o' + (space + two)) == "o two" );

  //4 members expressions:
  EXAM_CHECK( ((one + space) + (two + space)) == "one two " );

  //special operators
  {
    string result;
    result = one + space + two;
    EXAM_CHECK( result == "one two" );

    result += space + three;
    EXAM_CHECK( result == "one two three" );
  }

  //special append method
  {
    string result;
    //Use reserve to avoid reallocation and really test auto-referencing problems:
    result.reserve(64);

    result.append(one + space + two);
    EXAM_CHECK( result == "one two" );

    result.append(space + result + space + three);
    EXAM_CHECK( result == "one two one two three" );

    result = "one two";
    result.append(space + three, 1, 2);
    EXAM_CHECK( result == "one twoth" );

    result.append(space + result);
    EXAM_CHECK( result == "one twoth one twoth" );
  }

  //special assign method
  {
    string result;
    //Use reserve to avoid reallocation and really test auto-referencing problems:
    result.reserve(64);

    result.assign(one + space + two + space + three);
    EXAM_CHECK( result == "one two three" );

    result.assign(one + space + two + space + three, 3, 5);
    EXAM_CHECK( result == " two " );

    result.assign(one + result + three);
    EXAM_CHECK( result == "one two three" );
  }

  {
    EXAM_CHECK( !(one + ' ' + two).empty() );

    char result = (one + ' ' + two)[3];
    EXAM_CHECK( result == ' ' );

    result = (one + ' ' + two).at(3);
    EXAM_CHECK( result == ' ' );

#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
    try {
      result = (one + ' ' + two).at(10);
      EXAM_ERROR( "out_of_range exception expected" );
    }
    catch (out_of_range const&) {
      EXAM_CHECK( result == ' ' );
    }
    catch (...) {
      EXAM_ERROR( "out_of_range exception expected" );
    }
#else
    // throw exam::skip_exception();
    EXAM_ERROR( "Bad platform. Exception required" );
#endif
  }

  /*
  mystring a("ing");
  //gcc failed to compile following expression when template expressions are activated.
  //MSVC sees no problem. gcc limitation or MSVC is too cool ??
  mystring b = "str" + a;
  */

  return EXAM_RESULT;
}

#if !defined (TE_TMP_TEST_IGNORED)
class superstring
{
  public:
    superstring() :
      s("super")
    {}

    superstring( const string& str ) :
      s( str )
    {}

  superstring operator / (const string& str )
    { return superstring( s + "/" + str ); }

  superstring operator / (const char* str )
    { return superstring( s + "/" + str ); }

  private:
    string s;
};
#endif

int EXAM_IMPL(string_test::te_tmp)
{
#if !defined (TE_TMP_TEST_IGNORED)
  superstring s;
  string more( "more" );
  string less( "less" );

  superstring r = s / (more + less);
#endif

  return EXAM_RESULT;
}

class mypath
{
  public:
    mypath( const string& s ) :
        p( s )
      { }

    const mypath& operator / ( const string& );
    const string& str() const
      { return p; }
 
  private:
    string p;
};

const mypath& mypath::operator /( const string& s )
{
  p += '/';
  p += s;
  return *this;
}

int EXAM_IMPL(string_test::oper_tmp)
{
  string s1( "path1" );
  string s2( ".ext" );

  string& rs1 = s1;
  string& rs2 = s2;

  EXAM_CHECK( (mypath( string( "/root" ) ) / (rs1 + rs2)).str() == "/root/path1.ext" );

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::template_wexpression)
{
#if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
#  if !defined (__CYGWIN__) || defined (STLPORT)
  wstring one(L"one"), two(L"two"), three(L"three");
  wstring space(L" ");

  {
    wstring result(one + L' ' + two + L' ' + three);
    EXAM_CHECK( result == L"one two three" );
  }

  {
    wstring result(one + L' ' + two + L' ' + three, 4);
    EXAM_CHECK( result == L"two three" );
  }

  {
    wstring result(one + L' ' + two + L' ' + three, 4, 3);
    EXAM_CHECK( result == L"two" );
  }

  //2 members expressions:
  EXAM_CHECK( (L' ' + one) == L" one" );
  EXAM_CHECK( (one + L' ') == L"one " );
  EXAM_CHECK( (one + L" two") == L"one two" );
  EXAM_CHECK( (L"one " + two) == L"one two" );
  EXAM_CHECK( (one + space) == L"one " );

  //3 members expressions:
  EXAM_CHECK( ((one + space) + L"two") == L"one two" );
  EXAM_CHECK( (L"one" + (space + two)) == L"one two" );
  EXAM_CHECK( ((one + space) + two) == L"one two" );
  EXAM_CHECK( (one + (space + two)) == L"one two" );
  EXAM_CHECK( ((one + space) + L't') == L"one t" );
  EXAM_CHECK( (L'o' + (space + two)) == L"o two" );

  //4 members expressions:
  EXAM_CHECK( ((one + space) + (two + space)) == L"one two " );

  //special operators
  {
    wstring result;
    result = one + space + two;
    EXAM_CHECK( result == L"one two" );

    result += space + three;
    EXAM_CHECK( result == L"one two three" );
  }

  //special append method
  {
    wstring result;
    //Use reserve to avoid reallocation and really test auto-referencing problems:
    result.reserve(64);

    result.append(one + space + two);
    EXAM_CHECK( result == L"one two" );

    result.append(space + result + space + three);
    EXAM_CHECK( result == L"one two one two three" );

    result = L"one two";
    result.append(space + three, 1, 2);
    EXAM_CHECK( result == L"one twoth" );

    result.append(space + result);
    EXAM_CHECK( result == L"one twoth one twoth" );
  }

  //special assign method
  {
    wstring result;
    //Use reserve to avoid reallocation and really test auto-referencing problems:
    result.reserve(64);

    result.assign(one + space + two + space + three);
    EXAM_CHECK( result == L"one two three" );

    result.assign(one + space + two + space + three, 3, 5);
    EXAM_CHECK( result == L" two " );

    result.assign(one + result + three);
    EXAM_CHECK( result == L"one two three" );
  }

  {
    EXAM_CHECK( !(one + L' ' + two).empty() );

    wchar_t result = (one + L' ' + two)[3];
    EXAM_CHECK( result == L' ' );

    result = (one + L' ' + two).at(3);
    EXAM_CHECK( result == L' ' );

#    if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
    try {
      result = (one + L' ' + two).at(10);
      EXAM_ERROR( "out_of_range exception expected" );
    }
    catch (out_of_range const&) {
      EXAM_CHECK( result == L' ' );
    }
    catch (...) {
      EXAM_ERROR( "out_of_range exception expected" );
    }
#    else
    // throw exam::skip_exception();
    EXAM_ERROR( "Bad platform. Exception required" );
#    endif
  }
#  else
  throw exam::skip_exception();
#  endif
#else
  throw exam::skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::io)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
  string str("STLport");
  {
    ostringstream ostr;
    ostr << str;
    EXAM_CHECK( ostr.good() );
    EXAM_CHECK( ostr.str() == str );
  }
  {
    istringstream istr(str);
    string istr_content;
    istr >> istr_content;
    EXAM_CHECK( !istr.fail() && istr.eof() );
    EXAM_CHECK( istr_content == str );
  }
  {
    istringstream istr(str);
    istr.width(3);
    string istr_content;
    istr >> istr_content;
    EXAM_CHECK( !istr.fail() && !istr.eof() );
    EXAM_CHECK( istr_content == "STL" );
  }
#else
  throw exam::skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::allocator_with_state)
{
#if !(defined (STLPORT) && defined (_STLP_NO_CUSTOM_IO)) 

  char buf1[1024];
  StackAllocator<char> stack1(buf1, buf1 + sizeof(buf1));

  char buf2[1024];
  StackAllocator<char> stack2(buf2, buf2 + sizeof(buf2));

  typedef basic_string<char, char_traits<char>, StackAllocator<char> > StackString;
  {
    StackString str1("string stack1", stack1);
    StackString str1Cpy(str1);

    StackString str2("string stack2", stack2);
    StackString str2Cpy(str2);

    str1.swap(str2);

    EXAM_CHECK( str1.get_allocator().swaped() );
    EXAM_CHECK( str2.get_allocator().swaped() );

    EXAM_CHECK( str1 == str2Cpy );
    EXAM_CHECK( str2 == str1Cpy );
    EXAM_CHECK( str1.get_allocator() == stack2 );
    EXAM_CHECK( str2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();

  {
    StackString str1("longer string from stack1 allocator instance for dynamic allocation", stack1);
    StackString str1Cpy(str1);

    StackString str2("longer string from stack2 allocator instance for dynamic allocation", stack2);
    StackString str2Cpy(str2);

    str1.swap(str2);

    EXAM_CHECK( str1.get_allocator().swaped() );
    EXAM_CHECK( str2.get_allocator().swaped() );

    EXAM_CHECK( str1 == str2Cpy );
    EXAM_CHECK( str2 == str1Cpy );
    EXAM_CHECK( str1.get_allocator() == stack2 );
    EXAM_CHECK( str2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();


  {
    StackString str1("string stack1", stack1);
    StackString str1Cpy(str1);

    StackString str2("longer string from stack2 allocator instance for dynamic allocation", stack2);
    StackString str2Cpy(str2);

    str1.swap(str2);

    EXAM_CHECK( str1.get_allocator().swaped() );
    EXAM_CHECK( str2.get_allocator().swaped() );

    EXAM_CHECK( str1 == str2Cpy );
    EXAM_CHECK( str2 == str1Cpy );
    EXAM_CHECK( str1.get_allocator() == stack2 );
    EXAM_CHECK( str2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();


  {
    StackString str1("longer string from stack1 allocator instance for dynamic allocation", stack1);
    StackString str1Cpy(str1);

    StackString str2("string stack2", stack2);
    StackString str2Cpy(str2);

    str1.swap(str2);

    EXAM_CHECK( str1.get_allocator().swaped() );
    EXAM_CHECK( str2.get_allocator().swaped() );

    EXAM_CHECK( str1 == str2Cpy );
    EXAM_CHECK( str2 == str1Cpy );
    EXAM_CHECK( str1.get_allocator() == stack2 );
    EXAM_CHECK( str2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );
  stack1.reset(); stack2.reset();
#else
  throw exam::skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::capacity)
{
  string s;

  EXAM_CHECK( s.capacity() > 0 );
  EXAM_CHECK( s.capacity() < s.max_size() );
  EXAM_CHECK( s.capacity() >= s.size() );

#ifndef _STLP_SHORT_STRING_SZ
#  define _STLP_SHORT_STRING_SZ 16 // see stlport/stl/_string_base.h
#endif

  for ( int i = 0; i < _STLP_SHORT_STRING_SZ + 2; ++i ) {
    s += ' ';
    EXAM_CHECK( s.capacity() > 0 );
    EXAM_CHECK( s.capacity() < s.max_size() );
    EXAM_CHECK( s.capacity() >= s.size() );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::concat24)
{
  string s = string( "123456789012345678901234" ) + string( "123456789012345678901234" );

  EXAM_CHECK( s.length() == 48 );
  EXAM_CHECK( s[23] == '4' );
  EXAM_CHECK( s[24] == '1' );
  EXAM_CHECK( s[47] == '4' );

  return EXAM_RESULT;
}

int EXAM_IMPL(string_test::assign_from_char)
{
#ifdef __unix__

  /*
    From bugreport ID 2495252:

    The test works by allocating two pages of virtual memory, and then using
    mprotect to make the second page read-inaccessible. The first page is
    still read-accessible, and we only try to read 10 characters from it, but
    the strlen call searches past that for a zero-terminator and encounters the
    read-inaccessible page, leading to a segfault.

    ptr: Not confirmed. STLport 5.1 problem?
   */

  void* v = ::mmap( 0, getpagesize()*2, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);                                                               
     
  char* p = reinterpret_cast<char*>(v);
  memset( p, 'A', 2 * getpagesize() );
  ::mprotect( p + getpagesize(), getpagesize(), PROT_NONE );

  std::string s;

  s.assign( p, 10 ); // was report about SEG fault here, see bug ID 2495252. Not confirmed.

  EXAM_CHECK( s == "AAAAAAAAAA" );
#else
  throw exam::skip_exception();
#endif

  return EXAM_RESULT;
}
