// -*- C++ -*- Time-stamp: <09/04/06 20:21:51 ptr>

/*
 * Copyright (c) 2004-2008
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#include "stream_test.h"

#include <sstream>
#include <iomanip>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(iostream_test::manipulators)
{
  {
    istringstream istr;
    istr.str("bar");

    istr >> ws;
    EXAM_CHECK( istr.good() );

    string foo;
    istr >> foo;
    EXAM_CHECK( istr.eof() );
    EXAM_CHECK( !istr.fail() );
    EXAM_CHECK( foo == "bar" );

    istr >> ws;
    EXAM_CHECK( istr.eof() );
    EXAM_CHECK( !istr.fail() );
    istr.clear();
  }

  {
    istringstream istr;
    istr.str("  bar  ");

    istr >> ws;
    EXAM_CHECK( istr.good() );

    string foo;
    istr >> foo;
    EXAM_CHECK( !istr.eof() );
    EXAM_CHECK( !istr.fail() );
    EXAM_CHECK( foo == "bar" );

    istr >> ws;
    EXAM_CHECK( istr.eof() );
    EXAM_CHECK( !istr.fail() );
    istr.clear();
  }

  return EXAM_RESULT;
}

#include <iostream>

int EXAM_IMPL(iostream_test::in_avail)
{
  EXAM_CHECK( cin.rdbuf()->in_avail() == 0 );
  EXAM_CHECK( cout.rdbuf()->in_avail() == -1 );
  EXAM_CHECK( clog.rdbuf()->in_avail() == -1 );
  EXAM_CHECK( cerr.rdbuf()->in_avail() == -1 );

#if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  EXAM_CHECK( wcin.rdbuf()->in_avail() == 0 );
  EXAM_CHECK( wcout.rdbuf()->in_avail() == 0 );
  EXAM_CHECK( wclog.rdbuf()->in_avail() == 0 );
  EXAM_CHECK( wcerr.rdbuf()->in_avail() == 0 );
#endif

  return EXAM_RESULT;
}

//int EXAM_IMPL(iostream_test::wimbue)
//{
//#if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
//  locale loc;
//  try {
//    locale tmp(".866");
//    loc = tmp;
//  }
//  catch (const runtime_error&) {
//    return;
//  }
//
//  wcout.imbue(loc);
//  wcout << L"Hello world" << endl;
//  wcout.imbue(loc);
//  wcout << L"Hello world" << endl;
//#endif
//
//  return EXAM_RESULT;
//}

#include <string>
#include "math_aux.h"
#include <memory>
#include "full_streambuf.h"

int EXAM_IMPL(sstream_test::output)
{
  {
    ostringstream s;

    s << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";
    EXAM_CHECK( s.good() );
    EXAM_CHECK( s.str() == "1\n2\nabcd\nghk lm\nabcd ef" );
  }

  //Following tests are mostly used to reveal problem with the MSVC /Wp64 option
  //used to track 64 bits portability issue:
  {
    ostringstream s;
    size_t i = 0;
    s << i;
    EXAM_CHECK( s.good() );
    EXAM_CHECK( s.str() == "0" );
  }
  {
    ostringstream s;
    ptrdiff_t i = 0;
    s << i;
    EXAM_CHECK( s.good() );
    EXAM_CHECK( s.str() == "0" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::input)
{
  {
    istringstream s( "1\n2\nabcd\nghk lm\nabcd ef" );
    int i = 0;
    s >> i;
    EXAM_CHECK( s.good() );
    EXAM_CHECK( i == 1 );
    double d = 0.0;
    s >> d;
    EXAM_CHECK( s.good() );
    EXAM_CHECK( d == 2.0 );
    string str;
    s >> str;
    EXAM_CHECK( s.good() );
    EXAM_CHECK( str == "abcd" );
    char c;
    s.get(c); // extract newline, that not extracted by operator >>
    EXAM_CHECK( s.good() );
    EXAM_CHECK( c == '\n' );
    getline( s, str );
    EXAM_CHECK( s.good() );
    EXAM_CHECK( str == "ghk lm" );
    getline( s, str );
    EXAM_CHECK( s.eof() );
    EXAM_CHECK( str == "abcd ef" );
  }
  {
    istringstream s("0");
    size_t i = 1;
    s >> i;
    EXAM_CHECK( !s.fail() );
    EXAM_CHECK( s.eof() );
    EXAM_CHECK( i == 0 );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::input_char)
{
  char buf[16] = { 0, '1', '2', '3' };
  istringstream s( "0" );
  s >> buf;

  EXAM_CHECK( buf[0] == '0' );
  EXAM_CHECK( buf[1] == 0 );
  EXAM_CHECK( buf[2] == '2' );

  return EXAM_RESULT;
}


int EXAM_IMPL(sstream_test::io)
{
  stringstream s;
  s << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";
  EXAM_CHECK( s.good() );

  int i = 0;
  s >> i;
  EXAM_CHECK( i == 1 );
  EXAM_CHECK( s.good() );
  double d = 0.0;
  s >> d;
  EXAM_CHECK( d == 2.0 );
  EXAM_CHECK( s.good() );
  string str;
  s >> str;
  EXAM_CHECK( str == "abcd" );
  EXAM_CHECK( s.good() );
  char c;
  s.get(c); // extract newline, that not extracted by operator >>
  EXAM_CHECK( s.good() );
  EXAM_CHECK( c == '\n' );
  getline( s, str );
  EXAM_CHECK( s.good() );
  EXAM_CHECK( str == "ghk lm" );
  getline( s, str );
  EXAM_CHECK( str == "abcd ef" );
  EXAM_CHECK( s.eof() );

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::err)
{
  stringstream s( "9" );

  int i = 0;
  s >> i;
  EXAM_CHECK( !s.fail() );
  EXAM_CHECK( i == 9 );
  s >> i;
  EXAM_CHECK( s.fail() );
  EXAM_CHECK( s.eof() );
  EXAM_CHECK( i == 9 );

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::err_long)
{
  stringstream s( "9" );

  long i = 0;
  s >> i;
  EXAM_CHECK( !s.fail() );
  EXAM_CHECK( i == 9 );
  s >> i;
  EXAM_CHECK( s.fail() );
  EXAM_CHECK( s.eof() );
  EXAM_CHECK( i == 9 );

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::maxint)
{
  stringstream s;

  s << INT_MAX << " " << UINT_MAX << " " << LONG_MAX << " " << ULONG_MAX << " "
    << INT_MIN << " " << LONG_MIN;
  EXAM_CHECK( s.good() );

  int i = 0;
  unsigned int u = 0;
  long l = 0;
  unsigned long ul = 0;

  s >> i >> u >> l >> ul;
  EXAM_CHECK( s.good() );
  EXAM_CHECK( i == INT_MAX );
  EXAM_CHECK( u == UINT_MAX );
  EXAM_CHECK( l == LONG_MAX );
  EXAM_CHECK( ul == ULONG_MAX );

  s >> i >> l;
  EXAM_CHECK( !s.fail() );
  EXAM_CHECK( i == INT_MIN );
  EXAM_CHECK( l == LONG_MIN );

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::init_in)
{
  istringstream is( "12345" );
  int n;

  is >> n;
  EXAM_CHECK( !is.fail() );
  EXAM_CHECK( n == 12345 );

  istringstream dis( "1.2345" );
  double d;

  dis >> d;
  EXAM_CHECK( !dis.fail() );
  EXAM_CHECK( are_equals(d, 1.2345) );

  istringstream fis( "1.2345" );
  float f;

  fis >> f;
  EXAM_CHECK( !fis.fail() );
  EXAM_CHECK( are_equals(f, 1.2345f) );

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::init_out)
{
  ostringstream os( "12345" );
  EXAM_CHECK( os.str() == "12345" );

  os << 67;
  EXAM_CHECK( os.good() );

  // This satisfy to the Standard:
  // EXAM_CHECK( os.str() == "67345" );
  // But we don't know the reason, why standard state that.

  /*
   * 27.7.1.1: ... then copies the content of str into the basic_sringbuf
   * underlying character sequence and initializes the input and output
   * sequences according to which. If which & ios_base::out is true, initializes
   * the output sequence with underlying sequence. ...
   *
   * I can treat this as 'like output was performed', and then I should bump
   * put pointer... Looks like more useful then my previous treatment.
   *
   *          - ptr
   */

  EXAM_CHECK( os.str() == "1234567" );
  

  os.str( "89ab" );
  EXAM_CHECK( os.str() == "89ab" );

  os << 10;
  EXAM_CHECK( os.good() );
  // EXAM_CHECK( os.str() == "10ab" );
  EXAM_CHECK( os.str() == "89ab10" );

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::buf)
{
  stringstream ss;

  ss << "1234567\n89\n";
  char buf[10];
  buf[7] = 'x';
  ss.get( buf, 10 );
  EXAM_CHECK( !ss.fail() );
  EXAM_CHECK( buf[0] == '1' );
  EXAM_CHECK( buf[1] == '2' );
  EXAM_CHECK( buf[2] == '3' );
  EXAM_CHECK( buf[3] == '4' );
  EXAM_CHECK( buf[4] == '5' );
  EXAM_CHECK( buf[5] == '6' );
  EXAM_CHECK( buf[6] == '7' ); // 27.6.1.3 paragraph 10, paragraph 7
  EXAM_CHECK( buf[7] == 0 ); // 27.6.1.3 paragraph 8
  char c;
  ss.get(c);
  EXAM_CHECK( !ss.fail() );
  EXAM_CHECK( c == '\n' ); // 27.6.1.3 paragraph 10, paragraph 7
  ss.get(c);
  EXAM_CHECK( !ss.fail() );
  EXAM_CHECK( c == '8' );

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::rdbuf)
{
  stringstream ss;

  ss << "1234567\n89\n";

  ostringstream os;
  ss.get( *os.rdbuf(), '\n' );
  EXAM_CHECK( !ss.fail() );
  char c;
  ss.get(c);
  EXAM_CHECK( !ss.fail() );
  EXAM_CHECK( c == '\n' ); // 27.6.1.3 paragraph 12
  EXAM_CHECK( os.str() == "1234567" );

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::streambuf_output)
{
  {
    istringstream in("01234567890123456789");
    EXAM_CHECK( in );

    full_streambuf full_buf(10);
    ostream out(&full_buf);
    EXAM_CHECK( out );

    out << in.rdbuf();
    EXAM_CHECK( out );
    EXAM_CHECK( in );
    //out is good we can check what has been extracted:
    EXAM_CHECK( full_buf.str() == "0123456789" );

    out << in.rdbuf();
    EXAM_CHECK( out.fail() );
    EXAM_CHECK( in );

    ostringstream ostr;
    ostr << in.rdbuf();
    EXAM_CHECK( ostr );
    EXAM_CHECK( in );
    EXAM_CHECK( ostr.str() == "0123456789" );
  }

#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  {
    //If the output stream buffer throws:
    istringstream in("01234567890123456789");
    EXAM_CHECK( in );

    full_streambuf full_buf(10, true);
    ostream out(&full_buf);
    EXAM_CHECK( out );

    out << in.rdbuf();
    EXAM_CHECK( out.bad() );
    EXAM_CHECK( in );
    //out is bad we have no guaranty on what has been extracted:
    //EXAM_CHECK( full_buf.str() == "0123456789" );

    out.clear();
    out << in.rdbuf();
    EXAM_CHECK( out.fail() && out.bad() );
    EXAM_CHECK( in );

    ostringstream ostr;
    ostr << in.rdbuf();
    EXAM_CHECK( ostr );
    EXAM_CHECK( in );
    EXAM_CHECK( ostr.str() == "01234567890123456789" );
  }
#  endif

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::seek)
{
  stringstream s( "0123456789" );

  EXAM_CHECK( s.tellg() == stringstream::pos_type(0) );
  s.seekg( 6, ios::beg );
  EXAM_CHECK( s.tellg() == stringstream::pos_type(6) );
  s.seekg( -3, ios::cur );
  EXAM_CHECK( s.tellg() == stringstream::pos_type(3) );

  istringstream is( "0123456789" );
  EXAM_CHECK( is.tellg() == stringstream::pos_type(0) );
  is.seekg( 6, ios::beg );
  EXAM_CHECK( is.tellg() == stringstream::pos_type(6) );
  is.seekg( -3, ios::cur );
  EXAM_CHECK( is.tellg() == stringstream::pos_type(3) );

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::seekp)
{
  ostringstream s;

  s << "1234567";
  EXAM_CHECK( s.tellp() == stringstream::pos_type(7) );
  EXAM_CHECK( s.str() == "1234567" );
  s.seekp( 0 );
  s << "X";
  EXAM_CHECK( s.str() == "X234567" );
  s.seekp( 0, ios::beg );
  s << "Y";
  EXAM_CHECK( s.str() == "Y234567" );

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::seek_gp)
{
  stringstream ss( "1" );

  /* ISO/IEC 14882 2003 (and 1998 too) assume change as get as put positions
     with seekg and seekp (27.6.1.3, par 38; 27.6.2.4 par 2),
     but this contradict to common practice and proposed draft N2588
     (27.6.1.3, par 41; 27.6.2.5, par 4)

     Now STLport implement (i.e. change behaviour ) the draft's point of view.
   */

  ss.seekg( 0, ios::beg );
  ss.seekp( 0, ios::end );
  
  ss << "2";

  string str;

  ss >> str;

  /*  EXAM_CHECK( str == "2" ); --- according ISO/IEC 14882 2003 */
  EXAM_CHECK( str == "12" );

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::tellp)
{
  {
    ostringstream o( "1" );

    o << "23456";

    EXAM_CHECK( o.rdbuf()->pubseekoff( 0, ios_base::cur, ios_base::out ) == stringstream::pos_type(6) );
    EXAM_CHECK( o.tellp() == stringstream::pos_type(6) );
  }
  {
    ostringstream o;

    o << "123456";

    EXAM_CHECK( o.rdbuf()->pubseekoff( 0, ios_base::cur, ios_base::out ) == stringstream::pos_type(6) );
    EXAM_CHECK( o.tellp() == stringstream::pos_type(6) );
  }
  {
    ostringstream o( "1" );

    o << "23456789";

    EXAM_CHECK( o.rdbuf()->pubseekoff( 0, ios_base::cur, ios_base::out ) == stringstream::pos_type(9) );
    EXAM_CHECK( o.tellp() == stringstream::pos_type(9) );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(sstream_test::extra0_bug_id_2728232) // bug ID: 2728232
{
  stringstream s;
  string str_ref( "b4209c9d-2091-48fd-8078-19176d692692" );
  string spaces( "   " );

  s << str_ref;

  string str;

  s >> str;

  EXAM_CHECK( str == str_ref );
  EXAM_CHECK( s.str() == str_ref );

  /*
    Current state of 's' has eof flag up, i.e. not good.
    If missed s.clear() below, then after input string (spaces)
    s.str() would return 'b4209c9d-2091-48fd-8078-19176d6926920   '
    i.e. extra 0 after uid string; get pointer would point to this '0',
    so next input return '0' first.

    Resolution: not a bug.
  */

  s.clear(); // <-- Required here, to clear eof flag.

  s << spaces.c_str();

  EXAM_CHECK( s.str() == (str_ref + spaces) );

  return EXAM_RESULT;
}

template < class T >
string to_string( const T& v )
{
  ostringstream oss;
  oss << v;
  return oss.str();
}

int EXAM_IMPL(sstream_test::negative)
{
  EXAM_CHECK( to_string<int>(-1) == "-1" );
  EXAM_CHECK( to_string<long>(-1) == "-1" );

  return EXAM_RESULT;
}

/*
 * Note: Strstreams are really broken in STLport. But strstreams are 
 * obsolete, and even if ones was mentioned in D7.1--D7.4 of 
 * Standard, we have no wish to spent time with repair ones.
 */

#if !defined (_STLP_USE_NO_IOSTREAMS) || !defined (_STLP_NO_IOSTREAMS)
#  include <strstream>
#  include <limits>
#endif

int EXAM_IMPL(strstream_buffer_test::read_from_buffer)
{
#if !defined (_STLP_NO_IOSTREAMS)
  char hello[] = "Hello";
  strstream stream(hello, sizeof(hello), ios_base::in);
  char cur;
  stream >> cur;
  EXAM_CHECK(cur == 'H');
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(strstream_test::input)
{
#  if defined (STLPORT) && defined (_STLP_LONG_LONG) && !defined (_STLP_USE_NO_IOSTREAMS)
  {
    istrstream is("652208307");
    _STLP_LONG_LONG rval = 0;
    is >> rval;
    EXAM_CHECK( rval == 652208307 );
  }
  {
    istrstream is("-652208307");
    _STLP_LONG_LONG rval = 0;
    is >> rval;
    EXAM_CHECK( rval == -652208307 );
  }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

