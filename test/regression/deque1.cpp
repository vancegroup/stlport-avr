
// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <deque>
#include <algorithm>
#include <iostream>

#ifdef MAIN 
#define deque1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int deque1_test(int, char**)
{
  cout<<"Results of deque1_test:"<<endl;
  deque<int> d;
  d.push_back(4); // Add after end.
  d.push_back(9);
  d.push_back(16);
  d.push_front(1); // Insert at beginning.
  size_t i;
  for(i = 0; i < d.size(); i++)
    cout << "d[" << i << "] = " << d[i] << endl;
  cout << endl;

  d.pop_front(); // Erase first element.

  d[2] = 25; // Replace last element.
  for(i = 0; i < d.size(); i++)
    cout << "d[" << i << "] = " << d[i] << endl;

  //Some compile time tests:
  deque<int>::iterator dit(d.begin());
  deque<int>::const_iterator cdit(d.begin());
  size_t nb;
  nb = dit - cdit;
  nb = cdit - dit;
  nb = dit - dit;
  nb = cdit - cdit;
  if ((dit < cdit) || (dit > cdit) || (dit != cdit) ||
      !(dit <= cdit) || !(dit >= cdit))
    cout << "Iterator comparison failed" << endl;

  return 0;

}




