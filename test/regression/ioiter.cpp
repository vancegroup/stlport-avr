// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <string>
#include <iostream>
#include <sstream>
#include <iterator>

#ifdef MAIN
#define ioiter_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int ioiter_test( int, char ** )
{
  cout << "Results of ioiter: " << endl;
  char c;
  char *pc;
  char *strorg = "abcd";
  string expected( "abcd" );
  string tmp;

  string objStr(strorg);

  istringstream objIStrStrm1(objStr);
  istringstream objIStrStrm2(objStr);
  istringstream objIStrStrm3(objStr);

  cout << "plain C-string postfix increment operator and indirection: ";
  pc = strorg;
  string::size_type sz = strlen(strorg);
  string::size_type i = 0;
  for ( i = 0; i < sz; ++i ) {
    c = *pc++;
    tmp += c;
    cout << c;
  }
  cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << endl;

  cout << "postfix increment operator and indirection: ";

  istreambuf_iterator<char> objIStrmbIt1( objIStrStrm1.rdbuf() );
  istreambuf_iterator<char> end;

  // objIStrmbIt1 != end;

  tmp.clear();

  for ( i = 0; i < sz /* objIStrmbIt1 != end */; ++i ) {
    c = *objIStrmbIt1++;
    tmp += c;
    cout << c;
  }
  cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << endl;

  cout << "indirection, then postfix increment operator: ";

  tmp.clear();

  istreambuf_iterator<char> objIStrmbIt2( objIStrStrm2.rdbuf() );
  for ( i = 0; i < sz; ++i ) {
    c = *objIStrmbIt2;
    tmp += c;
    cout << c;
    objIStrmbIt2++;
  }
  cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << endl;

  tmp.clear();

  cout << "compare, then postfix increment operator and indirection: ";

  istreambuf_iterator<char> objIStrmbIt3( objIStrStrm3.rdbuf() );

  while ( objIStrmbIt3 != end ) {
    c = *objIStrmbIt3++;
    tmp += c;
    cout << c;
  }
  cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << endl;

  return 0;
}
