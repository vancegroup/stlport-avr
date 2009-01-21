#include "iter_test.h"

#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

#include "iota.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(iter_test::iter1)
{
  vector<const char*> v; // Vector of character strings.
  v.push_back("zippy"); // First element.
  v.push_back("motorboy"); // Second element.
  typedef vector<const char*> vec;
  unsigned counter = 0;
  for (vec::iterator i = v.begin(); i != v.end(); ++i, ++counter) {
    switch (counter) {
      case 0:
        EXAM_CHECK(!strcmp(*i, "zippy"));
        break;
      case 1:
        EXAM_CHECK(!strcmp(*i, "motorboy"));
        break;
      default:
        EXAM_ERROR("Out of range");
    }
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(iter_test::iter2)
{
  typedef vector<const char*> Vec;
  Vec v; // Vector of character strings.
  v.push_back("zippy"); // First element.
  v.push_back("motorboy"); // Second element.
  Vec::reverse_iterator it;
  unsigned counter = 0;
  for (it = v.rbegin(); it != v.rend(); ++it, ++counter) {
    switch (counter) {
      case 1:
        EXAM_CHECK(!strcmp(*it, "zippy"));
        break;
      case 0:
        EXAM_CHECK(!strcmp(*it, "motorboy"));
        break;
      default:
        EXAM_ERROR("Out of range");
    }
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(iter_test::iter3)
{
  vector<int> v; // Empty vector of integers.
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  // Position immediately after last item.
  vector<int>::iterator i = v.end();
  // Move back one and then access.
  EXAM_CHECK((*--i)==3);
  i -= 2; // Jump back two items.
  EXAM_CHECK((*i)==1);

  return EXAM_RESULT;
}

int EXAM_IMPL(iter_test::iterswp0)
{
  int numbers[6] = { 0, 1, 2, 3, 4, 5 };

  iter_swap(numbers, numbers + 3);

  EXAM_CHECK(numbers[0]==3);
  EXAM_CHECK(numbers[1]==1);
  EXAM_CHECK(numbers[2]==2);
  EXAM_CHECK(numbers[3]==0);
  EXAM_CHECK(numbers[4]==4);
  EXAM_CHECK(numbers[5]==5);

  return EXAM_RESULT;
}

int EXAM_IMPL(iter_test::iterswp1)
{
  vector<int> v1(6);
  __iota(v1.begin(), v1.end(), 0);
  iter_swap( v1.begin(), v1.begin() + 3 );

  EXAM_CHECK(v1[0]==3);
  EXAM_CHECK(v1[1]==1);
  EXAM_CHECK(v1[2]==2);
  EXAM_CHECK(v1[3]==0);
  EXAM_CHECK(v1[4]==4);
  EXAM_CHECK(v1[5]==5);

  return EXAM_RESULT;
}

int EXAM_IMPL(iter_test::iterswp2)
{
  vector<bool> boolVector;

  boolVector.push_back( true );
  boolVector.push_back( false );

  vector<bool>::iterator i1 = boolVector.begin();
  vector<bool>::iterator i2 = boolVector.begin();
  ++i2;

  bool v0 = *i1;
  bool v1 = *i2;

  iter_swap( i1, i2 );

  EXAM_CHECK(( *i1 == v1 && *i2 == v0 ));

  return EXAM_RESULT;
}

int EXAM_IMPL(iter_test::iterswp3)
{
  vector<int> vvref(10, 10);
  vector<int> lvref(10, 20);

  vector<vector<int> > vvints(4, vvref);
  list<vector<int> > lvints(4, lvref);

  iter_swap(vvints.begin(), lvints.begin());
  EXAM_CHECK( vvints.front() == lvref );
  EXAM_CHECK( lvints.front() == vvref );

  //const vector<vector<int> > &cvvints = vvints;
  //iter_swap(cvvints.begin(), lvints.begin());
  //iter_swap(lvints.begin(), cvvints.begin());

#if defined (STLPORT) && defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
  int *pvvint = &vvints.front().front();
  int *plvint = &lvints.front().front();

  iter_swap(vvints.begin(), lvints.begin());
  //Check that elements have been swaped:
  EXAM_CHECK( pvvint == &lvints.front().front() );
  EXAM_CHECK( plvint == &vvints.front().front() );
#endif

  return EXAM_RESULT;
}
