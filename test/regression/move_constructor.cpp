// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <vector>
#include <string>
//#include <slist>
#include <list>
//#include <deque>
//#include <set>
#include <iostream>

#include "stl_test.h"

#ifdef MAIN 
#define move_construct_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

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
  stlp_test(pvalue == &(*vec_cont.front().begin()));
}

template <class _Container>
void standard_test2(_Container const& ref_cont) {
  vector<_Container> vec_cont(1, ref_cont);
  typedef typename _Container::value_type value_type;
  value_type *pvalue = &(*vec_cont.front().begin()).first;
  size_t cur_capacity= vec_cont.capacity();
  //force reallocation
  while (cur_capacity == vec_cont.capacity()) {
    vec_cont.push_back(ref_cont);
  }
  stlp_test(pvalue == &(*vec_cont.front().begin()).first);
}


int move_construct_test(int, char**)
{
  cout << "Results of move_construct: "<<endl;

  cout << "vector<vector<int>>";
  vector<int> const ref_vec(10, 0);
  vector<vector<int> > v_v_ints(1, ref_vec);

  int *pint = &(v_v_ints.front().front());

  size_t cur_capacity = v_v_ints.capacity();
  while (v_v_ints.capacity() <= cur_capacity) {
    v_v_ints.push_back(ref_vec);
  }

  //v_v_ints has been resized
  stlp_test((pint == &v_v_ints.front().front()));

  cout << "vector<vector<int>>::erase";
  //We need at least 3 elements:
  while (v_v_ints.size() < 3) {
    v_v_ints.push_back(ref_vec);
  }

  //We erase the 2nd
  pint = &v_v_ints[2].front();
  v_v_ints.erase(v_v_ints.begin() + 1);
  stlp_test((pint == &v_v_ints[1].front()));

  cout << "vector<string>";
  string const ref_str("ref string");
  vector<string> vec_strs(1, ref_str);

  char const* pstr = vec_strs.front().c_str();
  cur_capacity = vec_strs.capacity();
  while (vec_strs.capacity() <= cur_capacity) {
    vec_strs.push_back(ref_str);
  }

  //vec_str has been resized
  stlp_test((pstr == vec_strs.front().c_str()));

  cout << "vector<string>::erase";
  //We need at least 3 elements:
  while (vec_strs.size() < 3) {
    vec_strs.push_back(ref_str);
  }

  //We erase the 2nd
  pstr = vec_strs[2].c_str();
  vec_strs.erase(vec_strs.begin() + 1);
  stlp_test((pstr == vec_strs[1].c_str()));

  cout << "swap(vector<int>, vector<int>)";
  vector<int> elem1(10, 0), elem2(10, 0);
  int *p1 = &elem1.front();
  int *p2 = &elem2.front();
  swap(elem1, elem2);
  stlp_test(((p1 == &elem2.front()) && (p2 == &elem1.front())));

  cout << "vector<list<int>>";
  standard_test1(list<int>(10));
/*
  cout << "vector<slist<int>>";
  standard_test1(slist<int>(10));

  cout << "vector<deque<int>>";
  standard_test1(deque<int>(10));

  int int_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  
  cout << "vector<set<int>>";

  set<int> int_set(int_values, int_values + sizeof(in_values) / sizeof(int));
  standard_test1(int_set);
  
  cout << "vector<multiset<int>>";
  multiset<int> int_multiset(int_values, int_values + sizeof(in_values) / sizeof(int));
  standard_test1(int_multiset);
*/

  cout << endl;
  return 0;
}
