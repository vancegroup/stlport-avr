// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <string>
#include <sstream>
#include <iterator>

#ifdef MAIN
#include <iostream>

#define ioiter_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int ioiter_test( int, char ** )
{
#ifdef MAIN
  cout << "Results of ioiter: " << endl;
#endif

  char c;
  char *pc;
  char *strorg = "abcd";
  string expected( "abcd" );
  string tmp;
  int res = 0;

  string objStr(strorg);

  istringstream objIStrStrm1(objStr);
  istringstream objIStrStrm2(objStr);
  istringstream objIStrStrm3(objStr);

#ifdef MAIN
  cout << "plain C-string postfix increment operator and indirection: ";
#endif

  pc = strorg;
  string::size_type sz = strlen(strorg);
  string::size_type i = 0;
  for ( i = 0; i < sz; ++i ) {
    c = *pc++;
    tmp += c;
#ifdef MAIN
    cout << c;
#endif
  }
#ifdef MAIN
  cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << endl;
#else
  res = tmp == expected ? 0 : -1;
#endif

#ifdef MAIN
  cout << "postfix increment operator and indirection: ";
#endif

  istreambuf_iterator<char> objIStrmbIt1( objIStrStrm1.rdbuf() );
  istreambuf_iterator<char> end;

  // objIStrmbIt1 != end;

  tmp.clear();

  for ( i = 0; i < sz /* objIStrmbIt1 != end */; ++i ) {
    c = *objIStrmbIt1++;
    tmp += c;
#ifdef MAIN
    cout << c;
#endif
  }
#ifdef MAIN
  cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << endl;
#else
  res = tmp == expected ? 0 : -1;
#endif

#ifdef MAIN
  cout << "indirection, then postfix increment operator: ";
#endif

  tmp.clear();

  istreambuf_iterator<char> objIStrmbIt2( objIStrStrm2.rdbuf() );
  for ( i = 0; i < sz; ++i ) {
    c = *objIStrmbIt2;
    tmp += c;
#ifdef MAIN
    cout << c;
#endif
    objIStrmbIt2++;
  }
#ifdef MAIN
  cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << endl;
#else
  res = tmp == expected ? 0 : -1;
#endif

  tmp.clear();

#ifdef MAIN
  cout << "compare, then postfix increment operator and indirection: ";
#endif

  istreambuf_iterator<char> objIStrmbIt3( objIStrStrm3.rdbuf() );

  while ( objIStrmbIt3 != end ) {
    c = *objIStrmbIt3++;
    tmp += c;
#ifdef MAIN
    cout << c;
#endif
  }
#ifdef MAIN
  cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << endl;
#else
  res = tmp == expected ? 0 : -1;
#endif

  return res;
}
