// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <string>
#include <vector>

#include "stl_test.h"

#ifdef MAIN 
#include <iostream>

#define string1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int string1_test(int, char**)
{
#ifdef MAIN 
  cout<<"Results of string1_test:"<<endl;
#endif
  int res = 0;
  char* array = "Hello, World!";
  std::string v(array);
  size_t i;
#ifdef MAIN 
  cout << v << endl;
#else
  res += v == array ? 0 : 1;
#endif
  v.erase(v.begin() + 1, v.end() - 1); // Erase all but first and last.
#ifdef MAIN 
  for(i = 0; i < v.size(); i++)
    cout << "v[" << i << "] = " << v[i] << endl;
#else
  for( i = 0; i < v.size(); i++ ) {
    switch ( i ) {
      case 0:
        res += v[i] == 'H' ? 0 : 1;
        break;
      case 1:
        res += v[i] == '!' ? 0 : 1;
        break;
      default:
        res += 1;
        break;
    }
  } 
#endif
  v.insert(1, (char*)array);
  v.erase(v.begin()); // Erase first element.
  v.erase(v.end() - 1); // Erase last element.
#ifdef MAIN 
  cout << v << endl;
#else
  res += v == array ? 0 : 1;
#endif
  v.clear(); // Erase all.

  const char* strorg = "This is test string for string calls";
  string str;
  //size it correctly to avoid reallocation
  str.reserve(100);
  str = strorg;

  //test self insertion:
  str.insert(10, str.c_str() + 5, 15);
  //Should be: This is teis test string st string for string calls
#ifdef MAIN 
  cout << str;
  stlp_test(str == "This is teis test string st string for string calls");
#else
  res += str == "This is teis test string st string for string calls" ? 0 : 1;
#endif

  //An other one using an other implementation
  str = strorg;
  str.insert(15, str.c_str() + 5, 25);
  //Should be: This is test stis test string for stringring for string calls
#ifdef MAIN 
  cout << str;
  stlp_test(str == "This is test stis test string for stringring for string calls");
#else
  res += str == "This is test stis test string for stringring for string calls" ? 0 : 1;
#endif


  str = strorg;
  str.insert(0, str.c_str() + str.size() - 4, 4);
  //Should be: allsThis is test string for string calls
#ifdef MAIN 
  cout << str;
  stlp_test(str == "allsThis is test string for string calls");
#else
  res += str == "allsThis is test string for string calls" ? 0 : 1;
#endif

  str = strorg;
  str.insert(0, str.c_str() + str.size() / 2 - 1, str.size() / 2 + 1);
  //Should be: ng for string callsThis is test string for string calls
#ifdef MAIN 
  cout << str;
  stlp_test(str == "ng for string callsThis is test string for string calls");
#else
  res += str == "ng for string callsThis is test string for string calls" ? 0 : 1;
#endif

  str = strorg;
  str.replace(5, 15, str.c_str(), 10);
  //Should be: This This is tefor string calls
#ifdef MAIN 
  cout << str;
  stlp_test(str == "This This is tefor string calls");
#else
  res += str == "This This is tefor string calls" ? 0 : 1;
#endif

  str = strorg;
  str.replace(5, 5, str.c_str(), 10);
  //Should be: This This is test string for string calls
#ifdef MAIN 
  cout << str;
  stlp_test(str == "This This is test string for string calls");
#else
  res += str == "This This is test string for string calls" ? 0 : 1;
#endif

#ifdef _STLP_MEMBER_TEMPLATES
  vector<int> int_vect;
  //Just a compile time test:
  str.insert(str.end(), int_vect.begin(), int_vect.end());
#endif

  
#ifdef MAIN 
  cout << endl;
#endif

  return res;
}

int string_data_test( int, char ** )
{
  string xx;

  if ( xx.data() == 0 ) { // ISO-IEC-14882:1998(E), 21.3.6, paragraph 3
    return -1;
  }
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

  return 0;
}

int string_c_str_test( int, char ** )
{
  string low( "2004-01-01" );
  string xx;
  string yy;

  if ( *(yy.c_str()) != '\0' ) { // ISO-IEC-14882:1998(E), 21.3.6, paragraph 1
    return -1;
  }

  // Blocks A and B should follow each other.
  // Block A:
  xx = "123456";
  xx += low;
  if ( strcmp( xx.c_str(), "1234562004-01-01" ) != 0 ) {
    return -1;
  }
  // End of block A

  // Block B:
  xx = "1234";
  xx += ";";

  if ( strcmp( xx.c_str(), "1234;" ) != 0 ) {
    return -1;
  }
  // End of block B

  return 0;
}

int string_replace_test(int, char**)
{
  string v( "78" );
  string s( "123456" );

  string::iterator i = s.begin() + 1;
  s.replace( i, i + 3, v.begin(), v.end() );

  if ( s != "17856" ) {
    return -1;
  }

  s = "123456";
  s.replace( i, i + 3, i + 5, s.end() );

  if ( s != "15656" ) {
    return -1;
  }

  s = "123456";
  s.replace( i, i + 3, i, i + 2 );

  if ( s != "12356" ) {
    return -1;
  }
 
  s = "123456";
  s.replace( i, i + 3, i + 1, s.end() );

  if ( s != "1345656" ) {
    return -1;
  }

  return 0;
}

