// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include "stlp_test.h"

#include <algorithm>
#include <set>

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int set1_test()
{
  set<int, less<int> > s;
  STLP_CHECK (s.count(42) == 0);
  s.insert(42);
  STLP_CHECK (s.count(42) == 1);
  s.insert(42);
  STLP_CHECK (s.count(42) == 1);
  int count = s.erase(42);
  STLP_CHECK (count == 1);
  return 0;
}


int set2_test()
{
  typedef set<int, less<int> > int_set;
  int_set s;
  pair<int_set::const_iterator, bool> p = s.insert(42);
  STLP_CHECK (p.second == true);
  p = s.insert(42);
  STLP_CHECK (p.second == false);

  int array1 [] = { 1, 3, 6, 7 };
  s.insert(array1, array1 + 4);
  STLP_CHECK (distance(s.begin(), s.end()) == 5);

  int_set s2;
  s2.swap(s);
  STLP_CHECK (distance(s2.begin(), s2.end()) == 5);
  STLP_CHECK (distance(s.begin(), s.end()) == 0);

  int_set s3;
  s3.swap(s);
  s3.swap(s2);
  STLP_CHECK (distance(s.begin(), s.end()) == 0);
  STLP_CHECK (distance(s2.begin(), s2.end()) == 0);
  STLP_CHECK (distance(s3.begin(), s3.end()) == 5);

  return 0;
}
