// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <stdexcept>
#include <iostream>
#include <bitset>
#include <algorithm>

#ifdef __STL_MSVC
#define __STL_NON_TYPE_TMPL_PARAM_BUG
#endif

#ifdef MAIN 
#define bitset1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int bitset1_test(int, char**)
{
  cout<<"Results of bitset1_test:"<<endl;
  bitset<13U> b1(0xFFFF);
  bitset<13U> b2(0x1111);
  cout << "b1 size = " << b1.size() << endl;
# if !defined (__STL_NON_TYPE_TMPL_PARAM_BUG)
  cout << "b1 = "<<b1<<endl;
# else
  cout << "b1 = "<<b1.to_string()<<endl;
# endif
  cout << "b2 size = " << b2.size() << endl;
# if defined (__STL_NON_TYPE_TMPL_PARAM_BUG)
  cout << "b2 = "<<b2.to_string()<<endl;
# else
  cout << "b2 = "<<b2<<endl;
# endif
  b1 = b1^(b2<<2);
# ifdef __STL_NON_TYPE_TMPL_PARAM_BUG
  cout << "b1 = "<<b1.to_string()<<endl;
# else
  cout << "b1 = "<<b1<<endl;
# endif
  return 0;
}

