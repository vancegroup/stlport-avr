#include <vector>
#include <string>
#include <algorithm>

#ifdef _STLP_PTHREADS
# include <pthread.h>
#endif

#ifdef _STLP_WIN32THREADS
# include <windows.h>
#endif

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class StringTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(StringTest);
  CPPUNIT_TEST(erase);
  CPPUNIT_TEST(data);
  CPPUNIT_TEST(c_str);
  CPPUNIT_TEST(insert);
  CPPUNIT_TEST(replace);
  CPPUNIT_TEST(resize);
  CPPUNIT_TEST(short_string);
  CPPUNIT_TEST(find);
  CPPUNIT_TEST(mt);
  CPPUNIT_TEST_SUITE_END();

protected:
  void erase();
  void data();
  void c_str();
  void insert();
  void replace();
  void resize();
  void short_string();
  void find();
  void mt();

  static string func( const string& par )
  {
    string tmp( par );

    return tmp;
  }

#if defined (_STLP_PTHREADS)
  static void *f( void * )
#elif defined (_STLP_WIN32THREADS)
  static DWORD __stdcall f (void *)
#endif
  {
    string s( "qyweyuewunfkHBUKGYUGL,wehbYGUW^(@T@H!BALWD:h^&@#*@(#:JKHWJ:CND" );

    for ( int i = 0; i < 2000000; ++i ) {
      string sx = func( s );
    }

    return 0;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(StringTest);

//
// tests implementation
//
void StringTest::mt()
{
  const int nth = 2;
#if defined(_STLP_PTHREADS)
  pthread_t t[nth];

  for ( int i = 0; i < nth; ++i ) {
    pthread_create( &t[i], 0, f, 0 );
  }

  for ( int i = 0; i < nth; ++i ) {
    pthread_join( t[i], 0 );
  }
#endif // _STLP_PTHREADS

#if defined (_STLP_WIN32THREADS)
  HANDLE t[nth];

  int i; // VC6 not support in-loop scope of cycle var
  for ( i = 0; i < nth; ++i ) {
    t[i] = CreateThread(NULL, 0, f, 0, 0, NULL);
  }

  for ( i = 0; i < nth; ++i ) {
    WaitForSingleObject(t[i], INFINITE);
  }
#endif

#if !defined(_STLP_PTHREADS) && !defined(_STLP_WIN32THREADS)
  // this test if useless without thrad support!
  CPPUNIT_ASSERT(false);
#endif
}
void StringTest::short_string()
{
  string const ref_short_str1("str1"), ref_short_str2("str2");
  string short_str1(ref_short_str1), short_str2(ref_short_str2);
  string const ref_long_str1("str                                                  1");
  string const ref_long_str2("str                                                  2");
  string long_str1(ref_long_str1), long_str2(ref_long_str2);

  CPPUNIT_ASSERT(short_str1 == ref_short_str1);
  CPPUNIT_ASSERT(long_str1 == ref_long_str1);

  {
    string str1(short_str1);
    str1 = long_str1;
    CPPUNIT_ASSERT(str1 == ref_long_str1);
  }

  {
    string str1(long_str1);
    str1 = short_str1;
    CPPUNIT_ASSERT(str1 == ref_short_str1);
  }

  {
    short_str1.swap(short_str2);
    CPPUNIT_ASSERT((short_str1 == ref_short_str2) && (short_str2 == ref_short_str1));
    short_str1.swap(short_str2);
  }

  {
    long_str1.swap(long_str2);
    CPPUNIT_ASSERT((long_str1 == ref_long_str2) && (long_str2 == ref_long_str1));
    long_str1.swap(long_str2);
  }

  {
    short_str1.swap(long_str1);
    CPPUNIT_ASSERT((short_str1 == ref_long_str1) && (long_str1 == ref_short_str1));
    short_str1.swap(long_str1);
  }

  {
    long_str1.swap(short_str1);
    CPPUNIT_ASSERT((short_str1 == ref_long_str1) && (long_str1 == ref_short_str1));
    long_str1.swap(short_str1);
  }

  {
    //This is to test move constructor
    vector<string> str_vect;
    str_vect.push_back(short_str1);
    str_vect.push_back(long_str1);
    str_vect.push_back(short_str2);
    str_vect.push_back(long_str2);
    CPPUNIT_ASSERT((str_vect[0] == ref_short_str1) &&
                                                  (str_vect[1] == ref_long_str1) &&
                                                  (str_vect[2] == ref_short_str2) &&
                                                  (str_vect[3] == ref_long_str2));
  }
}

void StringTest::erase()
{
  char const* array = "Hello, World!";
  std::string v(array);
  
  CPPUNIT_ASSERT( v == array );
  
  v.erase(v.begin() + 1, v.end() - 1); // Erase all but first and last.
  
  for( size_t i = 0; i < v.size(); i++ ) {
    switch ( i ) {
      case 0:
        CPPUNIT_ASSERT( v[i] == 'H' );
        break;
      case 1:
        CPPUNIT_ASSERT( v[i] == '!' );
        break;
      default:
        CPPUNIT_ASSERT( false );
        break;
    }
  } 
  
  v.insert(1, (char*)array);
  v.erase(v.begin()); // Erase first element.
  v.erase(v.end() - 1); // Erase last element.
  CPPUNIT_ASSERT( v == array );
  v.clear(); // Erase all.
  CPPUNIT_ASSERT( v.empty() );
}

void StringTest::data()
{
  string xx;

  CPPUNIT_ASSERT( xx.data() != 0 );  // ISO-IEC-14882:1998(E), 21.3.6, paragraph 3
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
}

void StringTest::c_str()
{
  string low( "2004-01-01" );
  string xx;
  string yy;

  CPPUNIT_ASSERT( *(yy.c_str()) == '\0' ); // ISO-IEC-14882:1998(E), 21.3.6, paragraph 1

  // Blocks A and B should follow each other.
  // Block A:
  xx = "123456";
  xx += low;
  CPPUNIT_ASSERT( strcmp( xx.c_str(), "1234562004-01-01" ) == 0 );
  // End of block A

  // Block B:
  xx = "1234";
  xx += ";";
  CPPUNIT_ASSERT( strcmp( xx.c_str(), "1234;" ) == 0 );
  // End of block B
}

void StringTest::insert()
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
  CPPUNIT_ASSERT( str == "This is teis test string st string for string calls" );

  str = strorg;
  str.insert(15, str.c_str() + 5, 25);
  CPPUNIT_ASSERT( str == "This is test stis test string for stringring for string calls" );

  str = strorg;
  str.insert(0, str.c_str() + str.size() - 4, 4);
  CPPUNIT_ASSERT( str == "allsThis is test string for string calls" );

  str = strorg;
  str.insert(0, str.c_str() + str.size() / 2 - 1, str.size() / 2 + 1);
  CPPUNIT_ASSERT( str == "ng for string callsThis is test string for string calls" );
  
  str = strorg;
  str.insert(str.begin(), str.begin() + str.size() / 2 - 1, str.end());
  CPPUNIT_ASSERT( str == "ng for string callsThis is test string for string calls" );

#ifdef _STLP_MEMBER_TEMPLATES
  vector<int> int_vect;
  //Just a compile time test:
  str.insert(str.end(), int_vect.begin(), int_vect.end());
#endif
}

void StringTest::replace()
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
  CPPUNIT_ASSERT( s == "17856" );
  
  s = "123456";
  i = s.begin() + 1;
  s.replace(i, i + 1, v.begin(), v.end());
  CPPUNIT_ASSERT( s == "1783456" );

  s = "123456";
  i = s.begin() + 1;
  string::const_iterator ci = s.begin() + 1;
  s.replace(i, i + 3, ci + 3, cs.end());
  CPPUNIT_ASSERT( s == "15656" );

  s = "123456";
  i = s.begin() + 1;
  ci = s.begin() + 1;
  s.replace(i, i + 3, ci, ci + 2);
  CPPUNIT_ASSERT( s == "12356" );

  s = "123456";
  i = s.begin() + 1;
  ci = s.begin() + 1;
  s.replace(i, i + 3, ci + 1, cs.end());
  CPPUNIT_ASSERT( s == "1345656" );
  
  s = "123456";
  s.replace(s.begin() + 4, s.end(), cs.begin(), cs.end());
  CPPUNIT_ASSERT( s == "1234123456" );
  
  /*
   * This is the test for the template replace method.
   */
  s = "123456";
  s.replace(s.begin() + 4, s.end(), s.begin(), s.end());
  CPPUNIT_ASSERT( s == "1234123456" );
  
  string strorg("This is test string for string calls");
  string str = strorg;
  str.replace(5, 15, str.c_str(), 10);
  CPPUNIT_ASSERT( str == "This This is tefor string calls" );

  str = strorg;
  str.replace(5, 5, str.c_str(), 10);
  CPPUNIT_ASSERT( str == "This This is test string for string calls" );
}

void StringTest::resize()
{
  string s;

  s.resize(0);

  CPPUNIT_ASSERT( *s.c_str() == 0 );

  s = "1234567";

  s.resize(0);
  CPPUNIT_ASSERT( *s.c_str() == 0 );

  s = "1234567";
  s.resize(1);
  CPPUNIT_ASSERT( s.size() == 1 );
  CPPUNIT_ASSERT( *s.c_str() == '1' );
  CPPUNIT_ASSERT( *(s.c_str() + 1) == 0 );

  s = "1234567";
  s.resize(10);
  CPPUNIT_ASSERT( s.size() == 10 );
  CPPUNIT_ASSERT( s[6] == '7' );
  CPPUNIT_ASSERT( s[7] == 0 );
  CPPUNIT_ASSERT( s[8] == 0 );
  CPPUNIT_ASSERT( s[9] == 0 );
  CPPUNIT_ASSERT( s[10] == 0 ); // terminate null
}

void StringTest::find()
{
  string s("one two three one two three");
  CPPUNIT_ASSERT( s.find("one") == 0 );
  CPPUNIT_ASSERT( s.find('t') == 4 );
  CPPUNIT_ASSERT( s.find('t', 5) == 8 );
  CPPUNIT_ASSERT( s.find("four") == string::npos );
  CPPUNIT_ASSERT( s.find("one", string::npos) == string::npos );

  CPPUNIT_ASSERT( s.rfind("two") == 18 );
  CPPUNIT_ASSERT( s.rfind("two", 0) == string::npos );
  CPPUNIT_ASSERT( s.rfind("two", 11) == 4 );
  CPPUNIT_ASSERT( s.rfind('w') == 19 );

  CPPUNIT_ASSERT( s.find_first_of("abcde") == 2 );
  CPPUNIT_ASSERT( s.find_last_of("abcde") == 26 );
  
  CPPUNIT_ASSERT( s.find_first_not_of("enotw ") == 9 );
  CPPUNIT_ASSERT( s.find_last_not_of("ehortw ") == 15 );
}
