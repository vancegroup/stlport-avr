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
  CPPUNIT_TEST(string1_test);
  CPPUNIT_TEST(string_data_test);
  CPPUNIT_TEST(string_c_str_test);
  CPPUNIT_TEST(string_replace_test);
  CPPUNIT_TEST(string_resize1);
  CPPUNIT_TEST(short_string_test);
  CPPUNIT_TEST(string_mt_test);
  CPPUNIT_TEST_SUITE_END();

protected:
  void string1_test();
  void string_data_test();
  void string_c_str_test();
  void string_replace_test();
  void string_resize1();
  void short_string_test();
  void string_mt_test();

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
void StringTest::string_mt_test()
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
void StringTest::short_string_test()
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
void StringTest::string1_test()
{
//#ifdef MAIN 
//  cout<<"Results of string1_test:"<<endl;
//#endif
  int res = 0;
  char* array = "Hello, World!";
  std::string v(array);
  size_t i;
//#ifdef MAIN 
//  cout << v << endl;
//#else
  CPPUNIT_ASSERT( v == array );
  // res += v == array ? 0 : 1;
//#endif
  v.erase(v.begin() + 1, v.end() - 1); // Erase all but first and last.
//#ifdef MAIN 
//  for(i = 0; i < v.size(); i++)
//    cout << "v[" << i << "] = " << v[i] << endl;
//#else
  for( i = 0; i < v.size(); i++ ) {
    switch ( i ) {
      case 0:
        CPPUNIT_ASSERT( v[i] == 'H' );
        // res += v[i] == 'H' ? 0 : 1;
        break;
      case 1:
        CPPUNIT_ASSERT( v[i] == '!' );
        // res += v[i] == '!' ? 0 : 1;
        break;
      default:
        CPPUNIT_ASSERT( false );
        // res += 1;
        break;
    }
  } 
//#endif
  v.insert(1, (char*)array);
  v.erase(v.begin()); // Erase first element.
  v.erase(v.end() - 1); // Erase last element.
//#ifdef MAIN 
//  cout << v << endl;
//#else
//  res += v == array ? 0 : 1;
//#endif
  CPPUNIT_ASSERT( v == array );
  v.clear(); // Erase all.

  const char* strorg = "This is test string for string calls";
  string str;
  //size it correctly to avoid reallocation
  str.reserve(100);
  str = strorg;

  //test self insertion:
  str.insert(10, str.c_str() + 5, 15);
  //Should be: This is teis test string st string for string calls
//#ifdef MAIN 
//  cout << str;
//  stlp_test(str == "This is teis test string st string for string calls");
//#else
//  res += str == "This is teis test string st string for string calls" ? 0 : 1;
//#endif
  CPPUNIT_ASSERT( str == "This is teis test string st string for string calls" );

  //An other one using an other implementation
  str = strorg;
  str.insert(15, str.c_str() + 5, 25);
  //Should be: This is test stis test string for stringring for string calls
//#ifdef MAIN 
//  cout << str;
//  stlp_test(str == "This is test stis test string for stringring for string calls");
//#else
//  res += str == "This is test stis test string for stringring for string calls" ? 0 : 1;
//#endif
  CPPUNIT_ASSERT( str == "This is test stis test string for stringring for string calls" );


  str = strorg;
  str.insert(0, str.c_str() + str.size() - 4, 4);
  //Should be: allsThis is test string for string calls
//#ifdef MAIN 
//  cout << str;
//  stlp_test(str == "allsThis is test string for string calls");
//#else
//  res += str == "allsThis is test string for string calls" ? 0 : 1;
//#endif
  CPPUNIT_ASSERT( str == "allsThis is test string for string calls" );

  str = strorg;
  str.insert(0, str.c_str() + str.size() / 2 - 1, str.size() / 2 + 1);
  //Should be: ng for string callsThis is test string for string calls
//#ifdef MAIN 
//  cout << str;
//  stlp_test(str == "ng for string callsThis is test string for string calls");
//#else
//  res += str == "ng for string callsThis is test string for string calls" ? 0 : 1;
//#endif
  CPPUNIT_ASSERT( str == "ng for string callsThis is test string for string calls" );

  str = strorg;
  str.replace(5, 15, str.c_str(), 10);
  //Should be: This This is tefor string calls
//#ifdef MAIN 
//  cout << str;
//  stlp_test(str == "This This is tefor string calls");
//#else
//  res += str == "This This is tefor string calls" ? 0 : 1;
//#endif
  CPPUNIT_ASSERT( str == "This This is tefor string calls" );

  str = strorg;
  str.replace(5, 5, str.c_str(), 10);
  //Should be: This This is test string for string calls
//#ifdef MAIN 
//  cout << str;
//  stlp_test(str == "This This is test string for string calls");
//#else
//  res += str == "This This is test string for string calls" ? 0 : 1;
//#endif
  CPPUNIT_ASSERT( str == "This This is test string for string calls" );

#ifdef _STLP_MEMBER_TEMPLATES
  vector<int> int_vect;
  //Just a compile time test:
  str.insert(str.end(), int_vect.begin(), int_vect.end());
#endif

  
//#ifdef MAIN 
//  cout << endl;
//#endif

//  return res;
}

void StringTest::string_data_test()
{
  string xx;

  CPPUNIT_ASSERT( xx.data() != 0 );  // ISO-IEC-14882:1998(E), 21.3.6, paragraph 3
#if 0
  /* This test really not required: in ISO-IEC-14882:1998(E) paragraph 3 stated:
   * '... and can have zero added to it', again: 'CAN', but not 'MUST'.
   * That's why I am comment this test. But I don't remove it due to I had
   * unevident problem with misinterpretation of data() return (i.e. data()
   * and c_str() provide different functionality!) and expect thast this is
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

void StringTest::string_c_str_test()
{
  string low( "2004-01-01" );
  string xx;
  string yy;

  CPPUNIT_ASSERT( *(yy.c_str()) == '\0' ); // ISO-IEC-14882:1998(E), 21.3.6, paragraph 1

//  if ( *(yy.c_str()) != '\0' ) { // ISO-IEC-14882:1998(E), 21.3.6, paragraph 1
//    return -1;
//  }

  // Blocks A and B should follow each other.
  // Block A:
  xx = "123456";
  xx += low;

  CPPUNIT_ASSERT( strcmp( xx.c_str(), "1234562004-01-01" ) == 0 );

//  if ( strcmp( xx.c_str(), "1234562004-01-01" ) != 0 ) {
//    return -1;
//  }
  // End of block A

  // Block B:
  xx = "1234";
  xx += ";";

  CPPUNIT_ASSERT( strcmp( xx.c_str(), "1234;" ) == 0 );

//  if ( strcmp( xx.c_str(), "1234;" ) != 0 ) {
//    return -1;
//  }
  // End of block B

}

void StringTest::string_replace_test()
{
  string v( "78" );
  string s( "123456" );

  string::iterator i = s.begin() + 1;
  s.replace( i, i + 3, v.begin(), v.end() );

  CPPUNIT_ASSERT( s == "17856" );

//  if ( s != "17856" ) {
//    return -1;
//  }

  s = "123456";
  i = s.begin() + 1;
  s.replace( i, i + 3, i + 3, s.end() );
  
  CPPUNIT_ASSERT( s == "15656" );

//  if ( s != "15656" ) {
//    return -1;
//  }

  s = "123456";
  i = s.begin() + 1;
  s.replace( i, i + 3, i, i + 2 );

  CPPUNIT_ASSERT( s == "12356" );

//  if ( s != "12356" ) {
//    return -1;
//  }
 
  s = "123456";
  i = s.begin() + 1;
  s.replace( i, i + 3, i + 1, s.end() );

  CPPUNIT_ASSERT( s == "1345656" );

//  if ( s != "1345656" ) {
//    return -1;
//  }

}

void StringTest::string_resize1()
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
  CPPUNIT_ASSERT( *(s.c_str() + 6) == '7' );
  CPPUNIT_ASSERT( *(s.c_str() + 7) == 0 );
  CPPUNIT_ASSERT( *(s.c_str() + 8) == 0 );
  CPPUNIT_ASSERT( *(s.c_str() + 9) == 0 );
  CPPUNIT_ASSERT( *(s.c_str() + 10) == 0 ); // terminate null
}
