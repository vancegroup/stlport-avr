// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.
// #include <cstdlib>

#include "stlp_test.h"

#include <algorithm>
#include <vector>

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int vec_test_1()
{
  vector<int> v1; // Empty vector of integers.

  STLP_CHECK( v1.empty() == true );
  STLP_CHECK( v1.size() == 0 );

  // STLP_CHECK( v1.max_size() == INT_MAX / sizeof(int) );
  // cout << "max_size = " << v1.max_size() << endl;
  v1.push_back(42); // Add an integer to the vector.

  STLP_CHECK( v1.size() == 1 );

  STLP_CHECK( v1[0] == 42 );

  return 0;
}

int vec_test_2()
{
  vector<double> v1; // Empty vector of doubles.
  v1.push_back(32.1);
  v1.push_back(40.5);
  vector<double> v2; // Another empty vector of doubles.
  v2.push_back(3.56);

  STLP_CHECK( v1.size() == 2 );
  STLP_CHECK( v1[0] == 32.1 );
  STLP_CHECK( v1[1] == 40.5 );

  STLP_CHECK( v2.size() == 1 );
  STLP_CHECK( v2[0] == 3.56 );
  v1.swap(v2); // Swap the vector's contents.

  STLP_CHECK( v1.size() == 1 );
  STLP_CHECK( v1[0] == 3.56 );
 
  STLP_CHECK( v2.size() == 2 );
  STLP_CHECK( v2[0] == 32.1 );
  STLP_CHECK( v2[1] == 40.5 );

  v2 = v1; // Assign one vector to another.

  STLP_CHECK( v2.size() == 1 );
  STLP_CHECK( v2[0] == 3.56 );
  
  return 0;
}

int vec_test_3()
{
  typedef  vector<char> vec_type;

  vec_type v1; // Empty vector of characters.
  v1.push_back('h');
  v1.push_back('i');

  STLP_CHECK( v1.size() == 2 );
  STLP_CHECK( v1[0] == 'h' );
  STLP_CHECK( v1[1] == 'i' );

  vec_type v2(v1.begin(), v1.end());
  v2[1] = 'o'; // Replace second character.

  STLP_CHECK( v2.size() == 2 );
  STLP_CHECK( v2[0] == 'h' );
  STLP_CHECK( v2[1] == 'o' );
  
  STLP_CHECK( (v1 == v2) == false );

  STLP_CHECK( (v1 < v2) == true );

  return 0;
}

int vec_test_4()
{
  vector<int> v(4);

  v[0] = 1;
  v[1] = 4;
  v[2] = 9;
  v[3] = 16;

  STLP_CHECK( v.front() == 1 );
  STLP_CHECK( v.back() == 16 );

  v.push_back(25);

  STLP_CHECK( v.back() == 25 );
  STLP_CHECK( v.size() == 5 );

  v.pop_back();

  STLP_CHECK( v.back() == 16 );
  STLP_CHECK( v.size() == 4 );

  return 0;
}

int vec_test_5()
{
  int array [] = { 1, 4, 9, 16 };

  vector<int> v(array, array + 4);

  STLP_CHECK( v.size() == 4 );

  STLP_CHECK( v[0] == 1 );
  STLP_CHECK( v[1] == 4 );
  STLP_CHECK( v[2] == 9 );
  STLP_CHECK( v[3] == 16 );

  return 0;
}

int vec_test_6()
{
  int array [] = { 1, 4, 9, 16, 25, 36 };

  vector<int> v(array, array + 6);

  STLP_CHECK( v.size() == 6 );
  STLP_CHECK( v[0] == 1 );
  STLP_CHECK( v[1] == 4 );
  STLP_CHECK( v[2] == 9 );
  STLP_CHECK( v[3] == 16 );
  STLP_CHECK( v[4] == 25 );
  STLP_CHECK( v[5] == 36 );

  v.erase( v.begin() ); // Erase first element.
  
  STLP_CHECK( v.size() == 5 );
  STLP_CHECK( v[0] == 4 );
  STLP_CHECK( v[1] == 9 );
  STLP_CHECK( v[2] == 16 );
  STLP_CHECK( v[3] == 25 );
  STLP_CHECK( v[4] == 36 );

  v.erase(v.end() - 1); // Erase last element.

  STLP_CHECK( v.size() == 4 );
  STLP_CHECK( v[0] == 4 );
  STLP_CHECK( v[1] == 9 );
  STLP_CHECK( v[2] == 16 );
  STLP_CHECK( v[3] == 25 );


  v.erase(v.begin() + 1, v.end() - 1); // Erase all but first and last.

  STLP_CHECK( v.size() == 2 );
  STLP_CHECK( v[0] == 4 );
  STLP_CHECK( v[1] == 25 );

  return 0;
}

int vec_test_7()
{
  int array1 [] = { 1, 4, 25 };
  int array2 [] = { 9, 16 };

  vector<int> v(array1, array1 + 3);
  v.insert(v.begin(), 0); // Insert before first element.
  v.insert(v.end(), 36);  // Insert after last element.

  STLP_CHECK( v.size() == 5 );
  STLP_CHECK( v[0] == 0 );
  STLP_CHECK( v[1] == 1 );
  STLP_CHECK( v[2] == 4 );
  STLP_CHECK( v[3] == 25 );
  STLP_CHECK( v[4] == 36 );

  // Insert contents of array2 before fourth element.
  v.insert(v.begin() + 3, array2, array2 + 2);

  STLP_CHECK( v.size() == 7 );

  STLP_CHECK( v[0] == 0 );
  STLP_CHECK( v[1] == 1 );
  STLP_CHECK( v[2] == 4 );
  STLP_CHECK( v[3] == 9 );
  STLP_CHECK( v[4] == 16 );
  STLP_CHECK( v[5] == 25 );
  STLP_CHECK( v[6] == 36 );

  return 0;
}

int vec_test_8()
{
  vector<int> v;

  STLP_CHECK( v.capacity() == 0 );
  v.push_back(42);
  STLP_CHECK( v.capacity() == 1 );
  v.reserve(5000);
  STLP_CHECK( v.capacity() == 5000 );

  return 0;
}
