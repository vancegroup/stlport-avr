// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <iostream>
#include <algorithm>
#include <set>

#ifdef MAIN 
#define set2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int set2_test(int, char**)
{
  cout<<"Results of set2_test:"<<endl;
  typedef set<int, less<int> > int_set;
  int_set s;
  pair<int_set::const_iterator, bool> p = s.insert(42);
  if(p.second)
   cout << "Inserted new element " << *(p.first) << endl;
  else
   cout << "Existing element = " << *(p.first) << endl;
  p = s.insert(42);
  if(p.second)
   cout << "Inserted new element " << *(p.first) << endl;
  else
   cout << "Existing element = " << *(p.first) << endl;

  int array1 [] = { 1, 3, 6, 7 };
  s.insert(array1, array1 + 4);
  if (distance(s.begin(), s.end()) != 5)
    return 1;
  int_set s2;
  s2.swap(s);
  if (distance(s2.begin(), s2.end()) != 5)
    return 1;
  if (distance(s.begin(), s.end()) != 0)
    return 1;

  return 0;
}
