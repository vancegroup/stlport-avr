// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <vector>
#include <string>
#include <iostream>

#ifdef MAIN 
#define move_construct_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

void check_result(bool cond) {
  cout<<(cond?"success":"failure")<<endl;
}

int move_construct_test(int, char**)
{
  cout<<"Results of move_construct: "<<endl;

  cout<<"vector<vector<int>>: ";
  vector<int> const ref_vec(10, 0);
  vector<vector<int> > v_v_ints(1, ref_vec);

  int *pint = &(v_v_ints.front().front());

  size_t cur_capacity = v_v_ints.capacity();
  while (v_v_ints.capacity() <= cur_capacity) {
    v_v_ints.push_back(ref_vec);
  }

  //v_v_ints has been resized
  check_result((pint == &v_v_ints.front().front()));

  cout<<"vector<vector<int>>::erase: ";
  //We need at least 3 elements:
  while (v_v_ints.size() < 3) {
    v_v_ints.push_back(ref_vec);
  }

  //We erase the 2nd
  pint = &v_v_ints[2].front();
  v_v_ints.erase(v_v_ints.begin() + 1);
  check_result((pint == &v_v_ints[1].front()));

  cout<<"vector<string>: ";
  string const ref_str("ref string");
  vector<string> vec_strs(1, ref_str);

  char const* pstr = vec_strs.front().c_str();
  cur_capacity = vec_strs.capacity();
  while (vec_strs.capacity() <= cur_capacity) {
    vec_strs.push_back(ref_str);
  }

  //vec_str has been resized
  check_result((pstr == vec_strs.front().c_str()));

  cout<<"vector<string>::erase: ";
  //We need at least 3 elements:
  while (vec_strs.size() < 3) {
    vec_strs.push_back(ref_str);
  }

  //We erase the 2nd
  pstr = vec_strs[2].c_str();
  vec_strs.erase(vec_strs.begin() + 1);
  check_result((pstr == vec_strs[1].c_str()));

  cout<<"swap(vector<int>, vector<int>): ";
  vector<int> elem1(10, 0), elem2(10, 0);
  int *p1 = &elem1.front();
  int *p2 = &elem2.front();
  swap(elem1, elem2);
  check_result(((p1 == &elem2.front()) && (p2 == &elem1.front())));

  return 0;
}
