// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include "stlp_test.h"

#include <set>
#include <functional>

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

typedef multiset<int, less<int> > mset;

int mset1_test()
{
  mset s;
  STLP_CHECK(s.count(42) == 0);
  s.insert(42);
  STLP_CHECK(s.count(42) == 1);
  s.insert(42);
  STLP_CHECK(s.count(42) == 2);

  mset::iterator i = s.find(40);
  STLP_CHECK(i == s.end());

  i = s.find(42);
  STLP_CHECK(i != s.end());
  int count = s.erase(42);
  STLP_CHECK(count == 2);
  return 0;
}

int mset3_test()
{
  int array [] = { 3, 6, 1, 2, 3, 2, 6, 7, 9 };

  mset s(array, array + 9);
  mset::iterator i;
  i = s.lower_bound(3);
  STLP_CHECK(*i == 3);
  i = s.upper_bound(3);
  STLP_CHECK(*i == 6);
  pair<mset::const_iterator, mset::const_iterator> p = s.equal_range(5);
  STLP_CHECK(*(p.first) == 6);
  STLP_CHECK(*(p.second) == 6);
  return 0;
}

int mset4_test()
{
  //moved to mset3_test
  return 0;
}

static bool less_than(int a_, int b_)
{
  return a_ < b_;
}
 
static bool greater_than(int a_, int b_)
{
  return a_ > b_;
}

int mset5_test()
{
  int array [] = { 3, 6, 1, 9 };
  int j;
  
  typedef pointer_to_binary_function<int, int, bool> fn_type;
  typedef multiset<int, fn_type, allocator<int> > fn_mset;
  
  fn_type f(less_than);
  fn_mset s1(array+0, array + 4 , f );
  fn_mset::const_iterator i = s1.begin();
  for (j = 0; i != s1.end(); ++i, ++j) {
    STLP_CHECK(j != 0 || *i == 1);
    STLP_CHECK(j != 1 || *i == 3);
    STLP_CHECK(j != 2 || *i == 6);
    STLP_CHECK(j != 3 || *i == 9);
  }
  
  fn_type g(greater_than);
  fn_mset s2(array, array + 4, g);
  i = s2.begin();
  for (j = 0; i != s2.end(); ++i, ++j) {
    STLP_CHECK(j != 0 || *i == 9);
    STLP_CHECK(j != 1 || *i == 6);
    STLP_CHECK(j != 2 || *i == 3);
    STLP_CHECK(j != 3 || *i == 1);
  }

  return 0;
}

