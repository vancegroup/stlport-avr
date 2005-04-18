#include <string>
#if !defined (STLPORT) || !defined (_STLP_NO_IOSTREAMS)
#  include <fstream>
#  include <iostream>
#  include <iomanip>
#  include <sstream>
#  include <vector>

#  include "full_streambuf.h"
#  include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//The macro value gives approximately the generated file
//size in Go
//#define CHECK_BIG_FILE 4

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
  CPPUNIT_TEST(tellg);
  CPPUNIT_TEST(buf);
  CPPUNIT_TEST(rdbuf);
  CPPUNIT_TEST(streambuf_output);
  //CPPUNIT_TEST(file_traits);
#if defined (CHECK_BIG_FILE)
  CPPUNIT_TEST(big_file);
#endif
  CPPUNIT_TEST_SUITE_END();

  protected:
    void output();
    void input();
    void io();
    void err();
    void tellg();
    void buf();
    void rdbuf();
    void streambuf_output();
    //void file_traits();
#if defined (CHECK_BIG_FILE)
    void big_file();
#endif
};

CPPUNIT_TEST_SUITE_REGISTRATION(FstreamTest);

//
// tests implementation
//
void FstreamTest::output()
{
  ofstream f( "test_file.txt" );

  f << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";
  CPPUNIT_ASSERT (f.good());
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
  char c;
  f.get(c); // extract newline, that not extracted by operator >>
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
  char c;
  f.get(c); // extract newline, that not extracted by operator >>
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( c == '\n' );
  getline( f, s );
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( s == "ghk lm" );
  getline( f, s );
  CPPUNIT_ASSERT( !f.fail() );
  CPPUNIT_ASSERT( s == "abcd ef" );
  CPPUNIT_ASSERT( f.eof() );
}

void FstreamTest::err()
{
  basic_fstream<char,char_traits<char> > f( "test_file.txt", ios_base::in | ios_base::out | ios_base::trunc );

  CPPUNIT_ASSERT( f.is_open() );

  int i = 9;
  f << i;
  CPPUNIT_ASSERT( f.good() );
  i = 0;
  f.seekg( 0, ios_base::beg );
  f >> i;
  CPPUNIT_ASSERT( !f.fail() );
  CPPUNIT_ASSERT( i == 9 );
  f >> i;
  CPPUNIT_ASSERT( f.fail() );
  CPPUNIT_ASSERT( f.eof() );
  CPPUNIT_ASSERT( i == 9 );
}

void FstreamTest::tellg()
{
  // bogus ios_base::binary is for Wins
  ofstream of( "test_file.txt", ios_base::out | ios_base::binary | ios_base::trunc );
  CPPUNIT_ASSERT( of.is_open() );
  int i;

  for ( i = 0; i < 50; ++i ) {
    of << "line " << setiosflags(ios_base::right) << setfill('0') << setw(2) << i << "\n";
  }
  of.close();
  // bogus ios_base::binary is for Wins
  ifstream is( "test_file.txt", ios_base::in | ios_base::binary );
  CPPUNIT_ASSERT( is.is_open() );
  string line;
  char buf[64];

  // CPPUNIT_ASSERT( is.tellg() == 0 );
  streampos p = 0;
  for ( i = 0; i < 50; ++i ) {
    CPPUNIT_ASSERT( is.tellg() == p );
    // getline( is, line, '\n' );
    is.read( buf, 8 );
    CPPUNIT_ASSERT( !is.fail() );
    p += 8;
  }
}

void FstreamTest::buf()
{
  fstream ss( "test_file.txt", ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc );

  ss << "1234567\n89\n";
  ss.seekg( 0, ios_base::beg );
  char buf[10];
  buf[7] = 'x';
  ss.get( buf, 10 );
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( buf[0] == '1' );
  CPPUNIT_ASSERT( buf[1] == '2' );
  CPPUNIT_ASSERT( buf[2] == '3' );
  CPPUNIT_ASSERT( buf[3] == '4' );
  CPPUNIT_ASSERT( buf[4] == '5' );
  CPPUNIT_ASSERT( buf[5] == '6' );
  CPPUNIT_ASSERT( buf[6] == '7' ); // 27.6.1.3 paragraph 10, paragraph 7
  CPPUNIT_ASSERT( buf[7] == 0 ); // 27.6.1.3 paragraph 8
  char c;
  ss.get(c);
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( c == '\n' ); // 27.6.1.3 paragraph 10, paragraph 7
  ss.get(c);
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( c == '8' );
}

void FstreamTest::rdbuf()
{
  fstream ss( "test_file.txt", ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc );

  ss << "1234567\n89\n";
  ss.seekg( 0, ios_base::beg );

  ostringstream os;
  ss.get( *os.rdbuf(), '\n' );
  CPPUNIT_ASSERT( !ss.fail() );
  char c;
  ss.get(c);
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( c == '\n' ); // 27.6.1.3 paragraph 12
  CPPUNIT_ASSERT( os.str() == "1234567" );
}

void FstreamTest::streambuf_output()
{
  {
    ofstream ofstr("test_file.txt", ios_base::binary);
    if (!ofstr)
      //No test if we cannot create the file
      return;
    ofstr << "01234567890123456789";
    CPPUNIT_ASSERT( ofstr );
  }

  {
    ifstream in("test_file.txt", ios_base::binary);
    CPPUNIT_ASSERT( in );

    auto_ptr<full_streambuf> pfull_buf(new full_streambuf(10));
    ostream out(pfull_buf.get());
    CPPUNIT_ASSERT( out );

    out << in.rdbuf();
    CPPUNIT_ASSERT( out );
    CPPUNIT_ASSERT( in );
    CPPUNIT_ASSERT( pfull_buf->str() == "0123456789" );

    out << in.rdbuf();
    CPPUNIT_ASSERT( out.fail() );
    CPPUNIT_ASSERT( in );

    ostringstream ostr;
    ostr << in.rdbuf();
    CPPUNIT_ASSERT( ostr );
    CPPUNIT_ASSERT( in );
    CPPUNIT_ASSERT( ostr.str() == "0123456789" );
  }

#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  {
    //If the output stream buffer throws:
    ifstream in("test_file.txt", ios_base::binary);
    CPPUNIT_ASSERT( in );

    auto_ptr<full_streambuf> pfull_buf(new full_streambuf(10, true));
    ostream out(pfull_buf.get());
    CPPUNIT_ASSERT( out );

    out << in.rdbuf();
    CPPUNIT_ASSERT( out.bad() );
    CPPUNIT_ASSERT( in );
    //out is bad we have no guaranty on what has been extracted:
    //CPPUNIT_ASSERT( pfull_buf->str() == "0123456789" );

    out.clear();
    out << in.rdbuf();
    CPPUNIT_ASSERT( out.fail() && out.bad() );
    CPPUNIT_ASSERT( in );

    ostringstream ostr;
    ostr << in.rdbuf();
    CPPUNIT_ASSERT( ostr );
    CPPUNIT_ASSERT( in );
    CPPUNIT_ASSERT( ostr.str() == "0123456789" );
  }
#  endif
}

/*
template <typename _CharT>
struct file_test_traits : public char_traits<_CharT> {
};

void FstreamTest::file_traits()
{
  //File preparation:
  {
    ofstream ofstr("test_file.txt", ios_base::binary);
    //if (!ofstr)
      //No test if we cannot create the file
      //return;
    ofstr << "0123456789";
    CPPUNIT_ASSERT( ofstr );
  }

  {
    typedef file_test_traits<char> ftraits;
    typedef std::basic_ifstream<char, ftraits> ft_ifstreams;
    typedef std::basic_string<char, ftraits> ft_string;

    ft_ifstreams infile("test_file.txt");
    CPPUNIT_ASSERT( infile );
    ft_string res;
    infile >> res;
    CPPUNIT_ASSERT( infile );
    CPPUNIT_ASSERT( res == "0123456789" );
  }
}
*/

#  if defined (CHECK_BIG_FILE)
void FstreamTest::big_file()
{
  vector<pair<streamsize, streamoff> > file_pos;

  //Big file creation:
  {
    ofstream out("big_file.txt");
    CPPUNIT_ASSERT( out );

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
      CPPUNIT_ASSERT( (nb << 1) > nb );
      nb <<= 1;
    }
    CPPUNIT_ASSERT( nb * CHECK_BIG_FILE >= nb );
    nb *= CHECK_BIG_FILE;

    //Preparation of the ouput stream state:
    out << setiosflags(ios_base::right) << setfill('*');
    for (streamoff index = 0; index < nb; ++index) {
      if (index % 1024 == 0) {
        file_pos.push_back(make_pair(out.tellp(), index));
        CPPUNIT_ASSERT( file_pos.back().first != streamsize(-1) );
        if (file_pos.size() > 1) {
          CPPUNIT_ASSERT( file_pos[file_pos.size() - 1].first > file_pos[file_pos.size() - 2].first );
        }
      }
      out << setw(1023) << index << '\n';
    }
  }

  {
    ifstream in("big_file.txt");
    CPPUNIT_ASSERT( in );

    string line;
    vector<pair<streamsize, streamsize> >::const_iterator pit(file_pos.begin()),
                                                          pitEnd(file_pos.end());
    for (; pit != pitEnd; ++pit) {
      in.seekg((*pit).first);
      CPPUNIT_ASSERT( in );
      in >> line;
      size_t lastStarPos = line.rfind('*');
      CPPUNIT_ASSERT( atoi(line.substr(lastStarPos + 1).c_str()) == (*pit).second );
    }
  }

  /*
  The following test has been used to check that STLport do not generate
  an infinite loop when the file size is larger than the streamsize and
  streamoff representation (32 bits or 64 bits).
  {
    ifstream in("big_file.txt");
    CPPUNIT_ASSERT( in );
    char tmp[4096];
    streamsize nb_reads = 0;
    while ((!in.eof()) && in.good()){
      in.read(tmp, 4096);
      nb_reads += in.gcount();
    }
  }
  */
}
#  endif

#endif
