#include <string>
#include <sstream>
#include <iostream>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class SstreamTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(SstreamTest);
  CPPUNIT_TEST(output);
  CPPUNIT_TEST(input);
  CPPUNIT_TEST(io);
  CPPUNIT_TEST_SUITE_END();

protected:
  void output();
  void input();
  void io();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SstreamTest);

//
// tests implementation
//
void SstreamTest::output()
{
  ostringstream s;

  s << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";
  CPPUNIT_ASSERT( s.str() == "1\n2\nabcd\nghk lm\nabcd ef" );
}

void SstreamTest::input()
{
  istringstream s( "1\n2\nabcd\nghk lm\nabcd ef" );
  int i = 0;
  s >> i;
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( i == 1 );
  double d = 0.0;
  s >> d;
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( d == 2.0 );
  string str;
  s >> str;
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( str == "abcd" );
  char c = s.get(); // extract newline, that not extracted by operator >>
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( c == '\n' );
  getline( s, str );
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( str == "ghk lm" );
  getline( s, str );
  CPPUNIT_ASSERT( s.eof() );
  CPPUNIT_ASSERT( str == "abcd ef" );
}

void SstreamTest::io()
{
  stringstream s;

  s << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";

  int i = 0;
  s >> i;
  CPPUNIT_ASSERT( i == 1 );
  CPPUNIT_ASSERT( s.good() );
  double d = 0.0;
  s >> d;
  CPPUNIT_ASSERT( d == 2.0 );
  CPPUNIT_ASSERT( s.good() );
  string str;
  s >> str;
  CPPUNIT_ASSERT( str == "abcd" );
  CPPUNIT_ASSERT( s.good() );
  char c = s.get(); // extract newline, that not extracted by operator >>
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( c == '\n' );
  getline( s, str );
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( str == "ghk lm" );
  getline( s, str );
  CPPUNIT_ASSERT( str == "abcd ef" );
  CPPUNIT_ASSERT( s.eof() );
}
