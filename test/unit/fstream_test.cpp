#include <string>
#include <fstream>
#include <iostream>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class FstreamTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(FstreamTest);
  CPPUNIT_TEST(output);
  CPPUNIT_TEST(input);
  CPPUNIT_TEST(io);
  CPPUNIT_TEST(err);
  CPPUNIT_TEST_SUITE_END();

  protected:
    void output();
    void input();
    void io();
    void err();
};

CPPUNIT_TEST_SUITE_REGISTRATION(FstreamTest);

//
// tests implementation
//
void FstreamTest::output()
{
  ofstream f( "test_file.txt" );

  f << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";
  // CPPUNIT_ASSERT( s.str() == "1\n2\nabcd\nghk lm\nabcd ef" );
}

void FstreamTest::input()
{
  ifstream f( "test_file.txt" );
  int i = 0;
  f >> i;
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( i == 1 );
  double d = 0.0;
  f >> d;
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( d == 2.0 );
  string str;
  f >> str;
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( str == "abcd" );
  char c = f.get(); // extract newline, that not extracted by operator >>
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( c == '\n' );
  getline( f, str );
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( str == "ghk lm" );
  getline( f, str );
  CPPUNIT_ASSERT( f.eof() );
  CPPUNIT_ASSERT( str == "abcd ef" );
}

void FstreamTest::io()
{
  basic_fstream<char,char_traits<char> > f( "test_file.txt", ios_base::in | ios_base::out | ios_base::trunc );

  CPPUNIT_ASSERT( f.is_open() );

  f << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";

  // f.flush();
  f.seekg( 0, ios_base::beg );

  int i = 0;
  f >> i;
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( i == 1 );
  double d = 0.0;
  f >> d;
  CPPUNIT_ASSERT( d == 2.0 );
  string s;
  f >> s;
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( s == "abcd" );
  char c = f.get(); // extract newline, that not extracted by operator >>
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( c == '\n' );
  getline( f, s );
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( s == "ghk lm" );
  getline( f, s );
  CPPUNIT_ASSERT( s == "abcd ef" );
  CPPUNIT_ASSERT( f.eof() );
}

void FstreamTest::err()
{
  basic_fstream<char,char_traits<char> > f( "test_file.txt", ios_base::in | ios_base::out | ios_base::trunc );

  CPPUNIT_ASSERT( f.is_open() );

  int i = 9;
  f << i;
  i = 0;
  f.seekg( 0, ios_base::beg );
  f >> i;
  CPPUNIT_ASSERT( i == 9 );
  f >> i;
  CPPUNIT_ASSERT( f.fail() );
  CPPUNIT_ASSERT( f.eof() );
  CPPUNIT_ASSERT( i == 9 );
}
