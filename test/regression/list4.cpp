// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <iostream>
#include <list>
#include <algorithm>

#ifdef MAIN 
#define list4_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int list4_test(int, char**)
{
  cout<<"Results of list4_test:"<<endl;
  int array1 [] = { 1, 3, 6, 7 };
  int array2 [] = { 2, 4 };

  list<int> l1(array1, array1 + 4);
  list<int> l2(array2, array2 + 2);
  l1.merge(l2);
  for(std::list<int>::iterator i = l1.begin(); i != l1.end(); i++)
    cout << *i;
  //We use distance to avoid a simple call to an internal counter
  if (distance(l1.begin(), l1.end()) != 6)
    return 1;
  if (distance(l2.begin(), l2.end()) != 2)
    return 1;

  l1.swap(l2);
  
  if (distance(l1.begin(), l1.end()) != 2)
    return 1;
  if (distance(l2.begin(), l2.end()) != 6)
    return 1;

    
  cout << endl;
  return 0;
}
