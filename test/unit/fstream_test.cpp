// -*- C++ -*- Time-stamp: <09/10/23 08:28:43 ptr>

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

#include <string>


#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <stdio.h>

#ifdef __unix__
#include <unistd.h>
#endif

#include "full_streambuf.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//The macro value gives approximately the generated file
//size in Go
//#define CHECK_BIG_FILE 4

int EXAM_IMPL(fstream_test::output)
{
  ofstream f( "test_file.txt" );

  f << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";
  EXAM_CHECK (f.good());
  // EXAM_CHECK( s.str() == "1\n2\nabcd\nghk lm\nabcd ef" );

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::input)
{
  {
    ifstream f( "test_file.txt" );
    int i = 0;
    f >> i;
    EXAM_CHECK( f.good() );
    EXAM_CHECK( i == 1 );
    double d = 0.0;
    f >> d;
    EXAM_CHECK( f.good() );
    EXAM_CHECK( d == 2.0 );
    string str;
    f >> str;
    EXAM_CHECK( f.good() );
    EXAM_CHECK( str == "abcd" );
    char c;
    f.get(c); // extract newline, that not extracted by operator >>
    EXAM_CHECK( f.good() );
    EXAM_CHECK( c == '\n' );
    getline( f, str );
    EXAM_CHECK( f.good() );
    EXAM_CHECK( str == "ghk lm" );
    getline( f, str );
    EXAM_CHECK( f.eof() );
    EXAM_CHECK( str == "abcd ef" );
  }
#if defined (STLPORT) && !defined (_STLP_USE_WIN32_IO)
  {
    ifstream in("/tmp");
    if (in.good()) {
      string s;
      getline(in, s);
      EXAM_CHECK( in.fail() );
    }
  }
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::input_char)
{
  char buf[16] = { 0, '1', '2', '3' };
  ifstream s( "test_file.txt" );
  s >> buf;

  EXAM_CHECK( buf[0] == '1' );
  EXAM_CHECK( buf[1] == 0 );
  EXAM_CHECK( buf[2] == '2' );

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::io)
{
  basic_fstream<char,char_traits<char> > f( "test_file.txt", ios_base::in | ios_base::out | ios_base::trunc );

  EXAM_CHECK( f.is_open() );

  f << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";

  // f.flush();
  f.seekg( 0, ios_base::beg );

  int i = 0;
  f >> i;
  EXAM_CHECK( f.good() );
  EXAM_CHECK( i == 1 );
  double d = 0.0;
  f >> d;
  EXAM_CHECK( d == 2.0 );
  string s;
  f >> s;
  EXAM_CHECK( f.good() );
  EXAM_CHECK( s == "abcd" );
  char c;
  f.get(c); // extract newline, that not extracted by operator >>
  EXAM_CHECK( f.good() );
  EXAM_CHECK( c == '\n' );
  getline( f, s );
  EXAM_CHECK( f.good() );
  EXAM_CHECK( s == "ghk lm" );
  getline( f, s );
  EXAM_CHECK( !f.fail() );
  EXAM_CHECK( s == "abcd ef" );
  EXAM_CHECK( f.eof() );

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::err)
{
  basic_fstream<char,char_traits<char> > f( "test_file.txt", ios_base::in | ios_base::out | ios_base::trunc );

  EXAM_CHECK( f.is_open() );

  int i = 9;
  f << i;
  EXAM_CHECK( f.good() );
  i = 0;
  f.seekg( 0, ios_base::beg );
  f >> i;
  EXAM_CHECK( !f.fail() );
  EXAM_CHECK( i == 9 );
  f >> i;
  EXAM_CHECK( f.fail() );
  EXAM_CHECK( f.eof() );
  EXAM_CHECK( i == 9 );

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::tellg)
{
  {
    // bogus ios_base::binary is for Wins
    ofstream of("test_file.txt", ios_base::out | ios_base::binary | ios_base::trunc);
    EXAM_CHECK( of.is_open() );

    for (int i = 0; i < 50; ++i) {
      of << "line " << setiosflags(ios_base::right) << setfill('0') << setw(2) << i << "\n";
      EXAM_CHECK( !of.fail() );
    }
    of.close();
  }

  {
    // bogus ios_base::binary is for Wins
    ifstream is("test_file.txt", ios_base::in | ios_base::binary);
    EXAM_CHECK( is.is_open() );
    char buf[64];

    // EXAM_CHECK( is.tellg() == 0 );
    streampos p = 0;
    for (int i = 0; i < 50; ++i) {
      is.read(buf, 0);
      EXAM_CHECK( is.gcount() == 0 );
      EXAM_CHECK( is.tellg() == p );
      is.read( buf, 8 );
      EXAM_CHECK( !is.fail() );
      EXAM_CHECK( is.gcount() == 8 );
      p += 8;
    }
  }

  {
    // bogus ios_base::binary is for Wins
    ifstream is("test_file.txt", ios_base::in | ios_base::binary);
    EXAM_CHECK( is.is_open() );

    streampos p = 0;
    for (int i = 0; i < 50; ++i) {
      EXAM_CHECK( !is.fail() );
      is.tellg();
      EXAM_CHECK( is.tellg() == p );
      p += 8;
      is.seekg( p, ios_base::beg  );
      EXAM_CHECK( !is.fail() );
    }
  }

  {
    // bogus ios_base::binary is for Wins
    ifstream is("test_file.txt", ios_base::in | ios_base::binary);
    EXAM_CHECK( is.is_open() );

    streampos p = 0;
    for (int i = 0; i < 50; ++i) {
      EXAM_CHECK( is.tellg() == p );
      p += 8;
      is.seekg( 8, ios_base::cur );
      EXAM_CHECK( !is.fail() );
    }
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::tellp)
{
  {
    ofstream o( "test_file.txt" );

    o << "123456";

    EXAM_CHECK( o.rdbuf()->pubseekoff( 0, ios_base::cur, ios_base::out ) == ofstream::pos_type(6) );
    EXAM_CHECK( o.tellp() == ofstream::pos_type(6) );
  }
  {
    ofstream o( "test_file.txt" );

    o << "123456789";

    EXAM_CHECK( o.rdbuf()->pubseekoff( 0, ios_base::cur, ios_base::out ) == ofstream::pos_type(9) );
    EXAM_CHECK( o.tellp() == ofstream::pos_type(9) );
  }
  /* According to the standard
     ofstream o( "test_file.txt", ios_base::app | ios_base::out )
     should give the same effect as fopen( "test_file.txt", "a" ).
     Problem is fopen( "test_file.txt", "a" ) has a bit different behaviour
     on different platforms, and this difference is not covered by specification.
     After fopen( "test_file.txt", "a" ) in this context ftell( f ) == 9 for
     Linux and Mac OS X (I expect the same for others POSIX-like platforms too);
     on Windows (independently from version?) ftell( f ) == 0, i.e. write pointer not
     shifted to EOF (but shifted to EOF just before write, as described in the specs).

     It isn't specifications violation, neither for Linux and Mac OS X nor for Windows.

     The code below is intended to demonstrate ambiguity (dependance from fopen implementation).
   */
  {
    #ifdef WIN32
    //In Windows, stlport and fopen use kernel32.CreateFile for open. 
    //File position is at BOF after open, unless we open with ios_base::ate
    long expected_pos = 0; 
    #else
    //On UNIX flavours, stlport and fopen use unix's open
    //File position is at EOF after open
    //
    //3rd possible scenario, "other platforms" - _STLP_USE_STDIO_IO
    //stlport uses fopen here. This case may fail this test, since the file position after 
    //fopen is implementation-dependent
    long expected_pos = 9;
    #endif
    ofstream o( "test_file.txt", ios_base::app | ios_base::out );
    EXAM_CHECK( o.rdbuf()->pubseekoff( 0, ios_base::cur, ios_base::out ) == ofstream::pos_type(expected_pos) );
    EXAM_CHECK( o.tellp() == ofstream::pos_type(expected_pos) );
  }
  { // for reference, to test fopen/ftell behaviour in append mode:
    #ifdef WIN32
    long expected_pos = 0;
    #else
    long expected_pos = 9;
    #endif
    FILE* f = fopen( "test_file.txt", "a" );
    EXAM_CHECK( ftell( f ) == expected_pos );
    fclose( f );
  }
  {
    //In append mode, file is positioned at EOF just before a write. 
    // After a write, file is at EOF. This is implementation-independent.  
    ofstream o( "test_file.txt", ios_base::app | ios_base::out );
    o << "X";
    EXAM_CHECK( o.rdbuf()->pubseekoff( 0, ios_base::cur, ios_base::out ) == ofstream::pos_type(10) );
    EXAM_CHECK( o.tellp() == ofstream::pos_type(10) );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::rewind)
{
#ifdef __unix__
  /* Bug ID 2881622: write fail after failed read-and-recovery */
  const char fname[] = "/tmp/stlport.test";
  {
    // Create empty file for read and write
    fstream f( fname, ios_base::in | ios_base::out | ios_base::trunc | ios_base::binary );

    int n = 0;

    EXAM_CHECK( f.is_open() );
    EXAM_CHECK( f.good() );

    // write to this file
    f.write( (const char*)&n, sizeof(int) );
    EXAM_CHECK( f.good() );
    // rewind 'get' pointer to end
    f.seekg( sizeof(int), ios_base::beg );
    EXAM_CHECK( f.good() );
    // try to read
    f.read( (char *)&n, sizeof(int) );
    // read operation fail, as expected
    EXAM_CHECK( f.fail() );
    // clear stream state
    f.clear();
    EXAM_CHECK( f.good() );
    n = 0;
    // continue append to EOF
    f.write( (const char*)&n, sizeof(int) );
    // if  bug #2881622 present, operation fail
    EXAM_CHECK( f.good() );
  }
  // check that we indeed wrote what expected:
  {
    ifstream f( fname );
    char c = -1;
    for ( int i = 0; i < 2 * sizeof(int); ++i ) {
      f.get( c );
      EXAM_CHECK( !f.fail() );
      EXAM_CHECK( c == '\0' );
    }
    f.get( c );
    EXAM_CHECK( f.fail() );
  }

  unlink( fname );
#else
  throw exam::skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::buf)
{
  fstream ss( "test_file.txt", ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc );

  ss << "1234567\n89\n";
  ss.seekg( 0, ios_base::beg );
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

int EXAM_IMPL(fstream_test::seek_binary)
{
  // Test in binary mode:
  {
    fstream s( "test_file.txt", ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc );
    EXAM_REQUIRE( s );

    s << "1234567890\n";
    EXAM_REQUIRE( s );
  }

  char b1[] = { 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x' };
  fstream s( "test_file.txt", ios_base::in | ios_base::out | ios_base::binary );
  EXAM_REQUIRE( s );

  int chars_read = (int)s.rdbuf()->sgetn( b1, sizeof(b1) );
  EXAM_CHECK( chars_read == 11 );
  EXAM_CHECK( b1[9] == '0' );
  EXAM_CHECK( s.rdbuf()->pubseekoff( 0, ios_base::cur ) == fstream::pos_type(chars_read) );
  EXAM_CHECK( s.rdbuf()->pubseekoff( -chars_read, ios_base::cur ) == fstream::pos_type(0) );

  char b2[10] = { 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y' };

  EXAM_CHECK( s.rdbuf()->sgetn( b2, 10 ) == 10 );
  EXAM_CHECK( b2[9] == '0' );

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::seek_text)
{
  // Test in text mode:
  {
    fstream s( "test_file.txt", ios_base::in | ios_base::out | ios_base::trunc );
    EXAM_REQUIRE( s );

    s << "1234567890\n";
    EXAM_REQUIRE( s );
  }

  char b1[] = { 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x' };
  fstream s( "test_file.txt", ios_base::in | ios_base::out );
  EXAM_REQUIRE( s );

  int chars_read = (int)s.rdbuf()->sgetn( b1, sizeof(b1) );
  EXAM_CHECK( chars_read == 11 );
  EXAM_CHECK( b1[9] == '0' );

  fstream::pos_type pos = s.rdbuf()->pubseekoff(0, ios_base::cur);
  // Depending on how '\n' is written in file, file position can be greater or equal to the number of chars_read read.
  streamoff offset = pos;
  EXAM_CHECK( offset >= chars_read );
  offset = s.rdbuf()->pubseekoff( -offset, ios_base::cur );
  EXAM_CHECK( offset == 0 );

  char b2[10] = { 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y' };

  EXAM_CHECK( s.rdbuf()->sgetn( b2, 5 ) == 5 );
  EXAM_CHECK( b2[4] == '5' );

  pos = s.rdbuf()->pubseekoff(0, ios_base::cur);
  EXAM_CHECK( pos == fstream::pos_type(5) );
  EXAM_CHECK( s.rdbuf()->pubseekoff(-5, ios_base::cur) == fstream::pos_type(0) );

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::seek_wide_stream)
{
#if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  // Test with a wariable encoding:
  locale loc;
  try {
    locale tmp(locale::classic(), new codecvt_byname<wchar_t, char, mbstate_t>(".UTF-8"));
    loc = tmp;
  }
  catch ( const runtime_error& err ) {
    // Localization no supported so no test:
    EXAM_ERROR( err.what() );
    // throw exam::skip_exception();

    return EXAM_RESULT;
  }

  {
    wfstream s( "test_file.txt", ios_base::in | ios_base::out | ios_base::trunc );
    EXAM_REQUIRE( s );
    s.imbue(loc);
    EXAM_REQUIRE( s );

    s << L"1234567890\n";
    EXAM_REQUIRE( s );
  }

  wchar_t b1[] = { L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x', L'x' };
  wfstream s( "test_file.txt", ios_base::in | ios_base::out );
  EXAM_REQUIRE( s );
  s.imbue(loc);
  EXAM_REQUIRE( s );

  int chars_read = (int)s.rdbuf()->sgetn( b1, sizeof(b1) / sizeof(wchar_t) );
  EXAM_CHECK( chars_read == 11 );
  EXAM_CHECK( b1[9] == L'0' );

  fstream::pos_type pos = s.rdbuf()->pubseekoff(0, ios_base::cur);
  // Depending on how '\n' is written in file, file position can be greater or equal to the number of chars_read read.
  streamoff off = pos;
  EXAM_CHECK( off >= chars_read );
  off = s.rdbuf()->pubseekoff(-off, ios_base::cur);
  EXAM_CHECK( off == -1 );
  off = s.rdbuf()->pubseekoff(0, ios_base::beg);
  EXAM_CHECK( off == 0 );

  wchar_t b2[10] = { L'y', L'y', L'y', L'y', L'y', L'y', L'y', L'y', L'y', L'y' };

  EXAM_CHECK( s.rdbuf()->sgetn( b2, 5 ) == 5 );
  EXAM_CHECK( b2[4] == L'5' );

  pos = s.rdbuf()->pubseekoff(0, ios_base::cur);
  EXAM_CHECK( pos == fstream::pos_type(5) );
  //EXAM_CHECK( s.rdbuf()->pubseekoff(-5, ios_base::cur) == fstream::pos_type(0) );
#else
  throw exam::skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::rdbuf)
{
  fstream ss( "test_file.txt", ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc );

  ss << "1234567\n89\n";
  ss.seekg( 0, ios_base::beg );

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

int EXAM_IMPL(fstream_test::streambuf_output)
{
  {
    ofstream ofstr("test_file.txt", ios_base::binary);

    EXAM_REQUIRE( ofstr ); // No test if we cannot create the file

    ofstr << "01234567890123456789";
    EXAM_CHECK( ofstr );
  }

  {
    ifstream in("test_file.txt", ios_base::binary);
    EXAM_CHECK( in );

    full_streambuf full_buf(10);
    ostream out(&full_buf);
    EXAM_CHECK( out );

    out << in.rdbuf();
    EXAM_CHECK( out );
    EXAM_CHECK( in );
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

  {
    //If the output stream buffer throws:
    ifstream in("test_file.txt", ios_base::binary);
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
    EXAM_CHECK( ostr.str() == "0123456789" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::win32_file_format)
{
  const char* file_name = "win32_file_format.tmp";
  const size_t nb_lines = 2049;
  {
    ofstream out(file_name);
    EXAM_CHECK( out.good() );
    out << 'a';
    for (size_t i = 0; i < nb_lines - 1; ++i) {
      out << '\n';
    }
    out << '\r';
    EXAM_CHECK( out.good() );
  }
  {
    ifstream in(file_name);
    EXAM_CHECK( in.good() );
    string line, last_line;
    size_t nb_read_lines = 0;
    while (getline(in, line)) {
      ++nb_read_lines;
      last_line = line;
    }
    EXAM_CHECK( in.eof() );
    EXAM_CHECK( nb_read_lines == nb_lines );
    EXAM_CHECK( !last_line.empty() && (last_line[0] == '\r') );
  }

  return EXAM_RESULT;
}

struct my_state {
  char dummy;
};

struct my_traits : public char_traits<char> {
  typedef my_state state_type;
  typedef fpos<state_type> pos_type;
};

#if !defined (STLPORT)
//STLport grant a default implementation, other Standard libs implementation
//do not necessarily do the same:
namespace std {
  template <>
  class codecvt<char, char, my_state>
    : public locale::facet, public codecvt_base {
  public:
    typedef char intern_type;
    typedef char extern_type;
    typedef my_state state_type;

    explicit codecvt(size_t __refs = 0) : locale::facet(__refs) {}
    result out(state_type&,
               const intern_type*  __from,
               const intern_type*,
               const intern_type*& __from_next,
               extern_type*        __to,
               extern_type*,
               extern_type*&       __to_next) const
    { __from_next = __from; __to_next   = __to; return noconv; }

    result in (state_type&,
               const extern_type*  __from,
               const extern_type*,
               const extern_type*& __from_next,
               intern_type*        __to,
               intern_type*,
               intern_type*&       __to_next) const
    { __from_next = __from; __to_next = __to; return noconv; }

    result unshift(state_type&,
                   extern_type* __to,
                   extern_type*,
                   extern_type*& __to_next) const
    { __to_next = __to; return noconv; }

    int encoding() const throw()
    { return 1; }

    bool always_noconv() const throw()
    { return true; }

    int length(const state_type&,
               const extern_type* __from,
               const extern_type* __end,
               size_t __max) const
    { return (int)min(static_cast<size_t>(__end - __from), __max); }

    int max_length() const throw()
    { return 1; }

    static locale::id id;
  };

  locale::id codecvt<char, char, my_state>::id;
}
#  else
#    if defined (__BORLANDC__) && (__BORLANDC__ < 0x590)
template <>
locale::id codecvt<char, char, my_state>::id;
#    endif
#  endif

int EXAM_IMPL(fstream_test::custom_facet)
{
#  if (!defined(STLPORT) && (defined (__GNUC__) && (__GNUC__ > 3))) || \
      (defined (STLPORT) && !defined (_STLP_NO_CUSTOM_IO) && \
                            !((defined (_STLP_MSVC) && (_STLP_MSVC < 1300)) || \
                              (defined (__GNUC__) && (__GNUC__ < 3)) || \
                              (defined (__SUNPRO_CC)) || \
                              (defined (__DMC__) && defined (_DLL))))
  const char* fileName = "test_file.txt";
  //File preparation:
  {
    ofstream ofstr(fileName, ios_base::binary);
    ofstr << "0123456789";
    EXAM_CHECK( ofstr );
  }

  {
    typedef basic_ifstream<char, my_traits> my_ifstream;
    typedef basic_string<char, my_traits> my_string;

    my_ifstream ifstr(fileName);
    EXAM_CHECK( ifstr );

#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
    ifstr.imbue(locale::classic());
    EXAM_CHECK( ifstr.fail() && !ifstr.bad() );
    ifstr.clear();
#  endif
    typedef codecvt<char, char, my_state> my_codecvt;
    locale my_loc(locale::classic(), new my_codecvt());
    // Check that my_codecvt has not replace default codecvt:
    EXAM_CHECK( (has_facet<my_codecvt>(my_loc)) );
    EXAM_CHECK( (has_facet<codecvt<char, char, mbstate_t> >(my_loc)) );
#  if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
    EXAM_CHECK( (has_facet<codecvt<wchar_t, char, mbstate_t> >(my_loc)) );
#  endif
    ifstr.imbue(my_loc);
    EXAM_CHECK( ifstr.good() );
    /*
    my_string res;
    ifstr >> res;
    EXAM_CHECK( !ifstr.fail() );
    EXAM_CHECK( !ifstr.bad() );
    EXAM_CHECK( ifstr.eof() );
    EXAM_CHECK( res == "0123456789" );
    */
  }
#  else
  throw exam::skip_exception();
#  endif

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::big_file)
{
#  if defined (CHECK_BIG_FILE)
  vector<pair<streamsize, streamoff> > file_pos;

  //Big file creation:
  {
    ofstream out("big_file.txt");
    EXAM_CHECK( out );

    //We are going to generate a file with the following schema for the content:
    //0(1019 times)0000  //1023 characters + 1 charater for \n (for some platforms it will be a 1 ko line)
    //0(1019 times)0001
    //...
    //0(1019 times)1234
    //...

    //Generation of the number of loop:
    streamoff nb = 1;
    for (int i = 0; i < 20; ++i) {
      //This assertion check that the streamoff can at least represent the necessary integers values
      //for this test:
      EXAM_CHECK( (nb << 1) > nb );
      nb <<= 1;
    }
    EXAM_CHECK( nb * CHECK_BIG_FILE >= nb );
    nb *= CHECK_BIG_FILE;

    //Preparation of the ouput stream state:
    out << setiosflags(ios_base::right) << setfill('*');
    for (streamoff index = 0; index < nb; ++index) {
      if (index % 1024 == 0) {
        file_pos.push_back(make_pair(out.tellp(), index));
        EXAM_CHECK( file_pos.back().first != streamsize(-1) );
        if (file_pos.size() > 1) {
          EXAM_CHECK( file_pos[file_pos.size() - 1].first > file_pos[file_pos.size() - 2].first );
        }
      }
      out << setw(1023) << index << '\n';
    }
  }

  {
    ifstream in("big_file.txt");
    EXAM_CHECK( in );

    string line;
    vector<pair<streamsize, streamsize> >::const_iterator pit(file_pos.begin()),
                                                          pitEnd(file_pos.end());
    for (; pit != pitEnd; ++pit) {
      in.seekg((*pit).first);
      EXAM_CHECK( in );
      in >> line;
      size_t lastStarPos = line.rfind('*');
      EXAM_CHECK( atoi(line.substr(lastStarPos + 1).c_str()) == (*pit).second );
    }
  }

  /*
  The following test has been used to check that STLport do not generate
  an infinite loop when the file size is larger than the streamsize and
  streamoff representation (32 bits or 64 bits).
  {
    ifstream in("big_file.txt");
    EXAM_CHECK( in );
    char tmp[4096];
    streamsize nb_reads = 0;
    while ((!in.eof()) && in.good()){
      in.read(tmp, 4096);
      nb_reads += in.gcount();
    }
  }
  */
#  else
  throw exam::skip_exception();
#  endif

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::null_stream)
{
#  if defined (_STLP_USE_WIN32_IO) || defined (WIN32) || defined (_WIN32)
  const char* nullStreamName = "NUL";
#  else
  const char* nullStreamName = "/dev/null";
#  endif
  {
    ofstream nullStream(nullStreamName);
    EXAM_CHECK( nullStream );
  }

  {
    ofstream nullStream(nullStreamName, ios_base::ate);
    EXAM_CHECK( nullStream );
  }

  {
    ofstream nullStream(nullStreamName, ios_base::trunc);
    EXAM_CHECK( nullStream );
  }

  {
    ofstream nullStream(nullStreamName, ios_base::app);
    EXAM_CHECK( nullStream );
  }

  {
    ifstream nullStream(nullStreamName);
    EXAM_CHECK( nullStream );
  }

  {
    ifstream nullStream(nullStreamName, ios_base::ate);
    EXAM_CHECK( nullStream );
  }

  {
    fstream nullStream(nullStreamName);
    EXAM_CHECK( nullStream );
  }

  {
    fstream nullStream(nullStreamName, ios_base::in | ios_base::out | ios_base::ate);
    EXAM_CHECK( nullStream );
  }

  {
    fstream nullStream(nullStreamName, ios_base::in | ios_base::out | ios_base::trunc);
    EXAM_CHECK( nullStream );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::null_buf)
{
  /* **********************************************************************************

  testcase for bug #1830513:
  in _istream.c
 
  template < class _CharT, class _Traits, class _Is_Delim>
  streamsize _STLP_CALL __read_unbuffered(basic_istream<_CharT, _Traits>* __that,
                                          basic_streambuf<_CharT, _Traits>* __buf,
                                          streamsize _Num, _CharT* __s,
                                          _Is_Delim __is_delim,
                                          bool __extract_delim, bool __append_null,
                                          bool __is_getline)

  can't accept _Num == 0; this is legal case, and may happen from

  template <class _CharT, class _Traits>
  basic_istream<_CharT, _Traits>&
  basic_istream<_CharT, _Traits>::getline(_CharT* __s, streamsize __n, _CharT __delim)

  *********************************************************************************** */

  fstream f( "test.txt", ios_base::in | ios_base::out | ios_base::trunc );
  // string line;

  for ( int i = 0; i < 0x200; ++i ) {
    f.put( ' ' );
  }

  // const streambuf *b = f.rdbuf();

  // string s;
  char buf[1024];
  buf[0] = 'a';
  buf[1] = 'b';
  buf[2] = 'c';

  // getline( f, s );
  // cerr << f.good() << endl;
  f.seekg( 0, ios_base::beg );
  // f.seekg( 0, ios_base::end );
  // buf[0] = f.get();

  // cerr << (void *)(b->_M_gptr()) << " " << (void *)(b->_M_egptr()) << endl;
  // cerr << f.good() << endl;
  // getline( f, s );
  f.getline( buf, 1 ); // <-- key line
  EXAM_CHECK( buf[0] == 0 );
  EXAM_CHECK( f.fail() ); // due to delimiter not found while buffer was exhausted

  return EXAM_RESULT;
}

int EXAM_IMPL(fstream_test::offset)
{
#  if !defined (STLPORT) || !defined (_STLP_WIN32)
#    if (defined(_LARGEFILE_SOURCE) || defined(_LARGEFILE64_SOURCE)) && !defined(_STLP_USE_DEFAULT_FILE_OFFSET)
  EXAM_CHECK( sizeof(streamoff) == 8 );
#    else
  EXAM_CHECK( sizeof(streamoff) == sizeof(off_t) );
#    endif
#  else
  throw exam::skip_exception();
#  endif

  return EXAM_RESULT;
}
