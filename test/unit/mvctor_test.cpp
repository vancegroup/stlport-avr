#include <vector>
#include <algorithm>
#include <vector>
#include <string>
#include <slist>
#include <list>
#include <deque>
#include <iostream>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class MoveConstructorTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(MoveConstructorTest);
  CPPUNIT_TEST(move_construct_test);
  CPPUNIT_TEST_SUITE_END();

protected:
  void move_construct_test();

  template <class _Container>
  void standard_test1(_Container const& ref_cont) {
    vector<_Container> vec_cont(1, ref_cont);
    typedef typename _Container::value_type value_type;
    value_type *pvalue = &(*vec_cont.front().begin());
    size_t cur_capacity= vec_cont.capacity();
    //force reallocation
    while (cur_capacity == vec_cont.capacity()) {
      vec_cont.push_back(ref_cont);
    }
    bool b=( (pvalue==(&(*vec_cont.front().begin()))) );
    CPPUNIT_ASSERT(b);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MoveConstructorTest);

//
// tests implementation
//
void MoveConstructorTest::move_construct_test()
{
  //cout << "vector<vector<int>>";
  vector<int> const ref_vec(10, 0);
  vector<vector<int> > v_v_ints(1, ref_vec);

  int *pint = &(v_v_ints.front().front());

  size_t cur_capacity = v_v_ints.capacity();
  while (v_v_ints.capacity() <= cur_capacity) {
    v_v_ints.push_back(ref_vec);
  }

  //v_v_ints has been resized
  CPPUNIT_ASSERT((pint == &v_v_ints.front().front()));

  //cout << "vector<vector<int>>::erase";
  //We need at least 3 elements:
  while (v_v_ints.size() < 3) {
    v_v_ints.push_back(ref_vec);
  }

  //We erase the 2nd
  pint = &v_v_ints[2].front();
  v_v_ints.erase(v_v_ints.begin() + 1);
  CPPUNIT_ASSERT((pint == &v_v_ints[1].front()));

  //cout << "vector<string>";
  string const ref_str("ref string, big enougth to be a dynamic one");
  vector<string> vec_strs(1, ref_str);

  char const* pstr = vec_strs.front().c_str();
  cur_capacity = vec_strs.capacity();
  while (vec_strs.capacity() <= cur_capacity) {
    vec_strs.push_back(ref_str);
  }

  //vec_str has been resized
  CPPUNIT_ASSERT((pstr == vec_strs.front().c_str()));

  //cout << "vector<string>::erase";
  //We need at least 3 elements:
  while (vec_strs.size() < 3) {
    vec_strs.push_back(ref_str);
  }

  //We erase the 2nd
  pstr = vec_strs[2].c_str();
  vec_strs.erase(vec_strs.begin() + 1);
  CPPUNIT_ASSERT((pstr == vec_strs[1].c_str()));

  //cout << "swap(vector<int>, vector<int>)";
  vector<int> elem1(10, 0), elem2(10, 0);
  int *p1 = &elem1.front();
  int *p2 = &elem2.front();
  swap(elem1, elem2);
  CPPUNIT_ASSERT(((p1 == &elem2.front()) && (p2 == &elem1.front())));


  // zero: don't like this kind of tests
  // because of template test function 
  // we should find another way to provide
  // move constructor testing...

/*
  standard_test1(list<int>(10));


  standard_test1(slist<int>(10));

  standard_test1(deque<int>(10));
*/

  /*
  int int_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  
  set<int> int_set(int_values, int_values + sizeof(in_values) / sizeof(int));
  standard_test1(int_set);
  
  multiset<int> int_multiset(int_values, int_values + sizeof(in_values) / sizeof(int));
  standard_test1(int_multiset);
  */

  /*
  CheckFullMoveSupport(string());
  CheckFullMoveSupport(vector<int>());
  CheckFullMoveSupport(deque<int>());
  CheckFullMoveSupport(list<int>());
  CheckFullMoveSupport(slist<int>());
  */
}
