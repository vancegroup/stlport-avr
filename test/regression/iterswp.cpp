// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <sstream>

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int iterswp0_test(int, char**)
{
  cout << "Results of iterswp0_test: ";
  int numbers[6] = { 0, 1, 2, 3, 4, 5 };
  stringstream s0;

  iter_swap(numbers, numbers + 3);

  for( int i = 0; i < 6; i++ )
    s0 << numbers[i] << ' ';

  if ( s0.str() != "3 1 2 0 4 5 " ) {
    cout << "fail" << endl;
    return 1;
  }

  cout << "pass" << endl;
  return 0;
}

int iterswp1_test(int, char**)
{
  cout << "Results of iterswp1_test: ";
  vector<int> v1(6);
  stringstream s0;

  iota( v1.begin(), v1.end(), 0);

  iter_swap( v1.begin(), v1.begin() + 3 );

  ostream_iterator<int> iter( s0, " " );
  copy( v1.begin(), v1.end(), iter );

  if ( s0.str() != "3 1 2 0 4 5 " ) {
    cout << "fail" << endl;
    return 1;
  }

  cout << "pass" << endl;
  return 0;
}

int iterswp2_test(int, char**)
{
  cout << "Results of iterswp2_test: ";

  vector<bool> boolVector;

  boolVector.push_back( true );
  boolVector.push_back( false );

  vector<bool>::iterator i1 = boolVector.begin();
  vector<bool>::iterator i2 = boolVector.begin();
  ++i2;

  // cout << bool(*i1) << " " << bool(*i2) << endl;
  bool v0 = *i1;
  bool v1 = *i2;

  iter_swap( i1, i2 );

  // cout << bool(*i1) << " " << bool(*i2) << endl;
  if ( *i1 == v1 && *i2 == v0 ) {
    cout << "pass" << endl;
    return 0;
  }

  cout << "fail" << endl;
  return 1;
}

int iterswp3_test(int, char**)
{
  cout << "Results of iterswp3_test: ";
  stringstream s0;
  stringstream s1;

  vector<bool> boolVector;

  boolVector.push_back( true );
  boolVector.push_back( false );

  copy ( boolVector.begin(), boolVector.end(), ostream_iterator<bool>( s0, " " ) );

  if ( s0.str() != "1 0 " ) {
    cout << "fail '" << s0.str() << "'"<< endl;
    return 1;
  }

  sort( boolVector.begin(), boolVector.end() );

  copy ( boolVector.begin(), boolVector.end(), ostream_iterator<bool>( s1, " " ) );

  if ( s1.str() != "0 1 " ) {
    // cout << "fail" << endl;
    cout << "fail '" << s1.str() << "'"<< endl;
    return 1;
  }

  cout << "pass" << endl;
  return 0;
}

#ifdef MAIN
int main( int argc, char **argv )
{
  int res = 0;

  res |= iterswp0_test( argc, argv );
  res |= iterswp1_test( argc, argv );
  res |= iterswp2_test( argc, argv );
  res |= iterswp3_test( argc, argv );

  return res;
}
#endif
