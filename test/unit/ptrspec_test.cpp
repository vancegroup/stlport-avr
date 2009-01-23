#include "ptrspec_test.h"

#include <vector>
#include <list>
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
#  include <slist>
#endif
#include <deque>
#include <set>
#include <iterator>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

#define TEST_INSTANCIATE_CONTAINER(cont) \
  template class cont<int*>; \
  template class cont<int const*>; \
  template class cont<int volatile*>; \
  template class cont<int const volatile*>

#if !defined(_MSC_VER) || (_MSC_VER > 1200)  // excluding MSVC 6.0
TEST_INSTANCIATE_CONTAINER(vector);
TEST_INSTANCIATE_CONTAINER(list);
#  if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
TEST_INSTANCIATE_CONTAINER(slist);
#  endif
TEST_INSTANCIATE_CONTAINER(deque);
TEST_INSTANCIATE_CONTAINER(set);
TEST_INSTANCIATE_CONTAINER(multiset);
#endif

//Function to test pointer to function support:
void FTypeInstance() {}

//Class to test pointer to member method support:
class AClass {
public:
  void func() {}
};

int EXAM_IMPL(ptrspec_test::ptr_specialization_test)
{
  int *int_array[] = {0, 0, 0};
  int const* cint_array[] = {0, 0, 0};

  {
    vector<void*> void_vect;
    deque<void*> void_deque;
    list<void*> void_list;
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
    slist<void*> void_slist;
#endif
  }

  {
    typedef void (*FType)();
    vector<FType> func_vector;
    func_vector.push_back(&FTypeInstance);
  }

#if !defined(__GNUC__) || (__GNUC__ > 2)
  {
    typedef void (AClass::*MFType)();
    vector<MFType> mem_func_vector;
    mem_func_vector.push_back(&AClass::func);
  }
#endif

  vector<int*> pint_vect;
  vector<int*> pint_vect2;
  vector<int const*> pcint_vect;
  list<int*> pint_list;
  list<int*> pint_list2;
  list<int const*> pcint_list;
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  slist<int*> pint_slist;
  slist<int*> pint_slist2;
  slist<int const*> pcint_slist;
#endif
  deque<int*> pint_deque;
  deque<int*> pint_deque2;
  deque<int const*> pcint_deque;

  vector<int*> pint_vect_from_list(pint_list.begin(), pint_list.end());
  pint_vect.insert(pint_vect.end(), pint_vect2.begin(), pint_vect2.end());
  pint_vect.insert(pint_vect.end(), int_array, int_array + 3);
  pint_vect2.insert(pint_vect2.end(), int_array, int_array + 3);
  pcint_vect.insert(pcint_vect.end(), int_array, int_array + 3);
  pcint_vect.insert(pcint_vect.end(), cint_array, cint_array + 3);
  pcint_vect.insert(pcint_vect.end(), pint_vect2.begin(), pint_vect2.end());
  pcint_vect.insert(pcint_vect.end(), int_array, int_array + 3);
  pint_vect.insert(pint_vect.end(), pint_list.begin(), pint_list.end());
  pcint_vect.insert(pcint_vect.end(), pint_list.begin(), pint_list.end());
  pcint_vect.insert(pcint_vect.end(), pcint_list.begin(), pcint_list.end());
  pint_vect.assign(pint_list.begin(), pint_list.end());
  pcint_vect.assign(pint_list.begin(), pint_list.end());
  pint_vect.assign(int_array, int_array + 3);
  pcint_vect.assign(int_array, int_array + 3);
  pcint_vect.assign(cint_array, cint_array + 3);
  copy(int_array, int_array + 3, back_inserter(pint_vect));

  pint_list.sort(binary_pred<int>());
  pcint_list.sort(binary_pred<int const>());
  pint_list.unique(binary_pred<int>());
  pcint_list.unique(binary_pred<int const>());
  pint_list.merge(pint_list, binary_pred<int>());
  pcint_list.merge(pcint_list, binary_pred<int const>());
  pint_list.remove_if(unary_pred<int>());
  pcint_list.remove_if(unary_pred<int const>());

  copy(int_array, int_array + 3, back_inserter(pint_list));
  copy(int_array, int_array + 3, back_inserter(pint_list2));
  pint_list.insert(pint_list.end(), pint_list2.begin(), pint_list2.end());
  pcint_list.insert(pcint_list.end(), pint_list.begin(), pint_list.end());
  pint_list.insert(pint_list.end(), pint_vect.begin(), pint_vect.end());
  pcint_list.insert(pcint_list.end(), pint_vect.begin(), pint_vect.end());
  pcint_list.insert(pcint_list.end(), pcint_vect.begin(), pcint_vect.end());
  list<int*> pint_list_from_vect(pint_vect.begin(), pint_vect.end());
  pint_list.assign(pint_vect.begin(), pint_vect.end());
  pcint_list.assign(pint_vect.begin(), pint_vect.end());
  pint_list.insert(pint_list.begin(), int_array, int_array + 3);
  pint_list.insert(pint_list.end(), int_array, int_array + 3);
  pcint_list.insert(pcint_list.end(), int_array, int_array + 3);
  pcint_list.insert(pcint_list.end(), cint_array, cint_array + 3);
  pint_list.assign(int_array, int_array + 3);
  pcint_list.assign(int_array, int_array + 3);
  pcint_list.assign(cint_array, cint_array + 3);
  //pint_list.assign(pcint_vect.begin(), pcint_vect.end());

#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  copy(int_array, int_array + 3, front_inserter(pint_slist));
  copy(int_array, int_array + 3, front_inserter(pint_slist2));
  pint_slist.insert(pint_slist.end(), pint_slist2.begin(), pint_slist2.end());
  pcint_slist.insert(pcint_slist.end(), pint_slist.begin(), pint_slist.end());
  pint_slist.insert(pint_slist.end(), pint_vect.begin(), pint_vect.end());
  pcint_slist.insert(pcint_slist.end(), pint_vect.begin(), pint_vect.end());
  pcint_slist.insert(pcint_slist.end(), pcint_vect.begin(), pcint_vect.end());
  slist<int*> pint_slist_from_vect(pint_vect.begin(), pint_vect.end());
  pint_slist.assign(pint_vect.begin(), pint_vect.end());
  pcint_slist.assign(pint_vect.begin(), pint_vect.end());
  pint_slist.insert(pint_slist.end(), int_array, int_array + 3);
  pcint_slist.insert(pcint_slist.end(), int_array, int_array + 3);
  pcint_slist.insert(pcint_slist.end(), cint_array, cint_array + 3);
  pint_slist.assign(int_array, int_array + 3);
  pcint_slist.assign(int_array, int_array + 3);
  pcint_slist.assign(cint_array, cint_array + 3);
  //pint_slist.assign(pcint_vect.begin(), pcint_vect.end());
#endif

  copy(int_array, int_array + 3, back_inserter(pint_deque));
  copy(int_array, int_array + 3, back_inserter(pint_deque2));
  pint_deque.insert(pint_deque.end(), pint_deque2.begin(), pint_deque2.end());
  pcint_deque.insert(pcint_deque.end(), pint_deque.begin(), pint_deque.end());
  pint_deque.insert(pint_deque.end(), pint_vect.begin(), pint_vect.end());
  pcint_deque.insert(pcint_deque.end(), pint_vect.begin(), pint_vect.end());
  pcint_deque.insert(pcint_deque.end(), pcint_vect.begin(), pcint_vect.end());
  deque<int*> pint_deque_from_vect(pint_vect.begin(), pint_vect.end());
  pint_deque.assign(pint_vect.begin(), pint_vect.end());
  pcint_deque.assign(pint_vect.begin(), pint_vect.end());
  pint_deque.insert(pint_deque.end(), int_array, int_array + 3);
  pcint_deque.insert(pcint_deque.end(), int_array, int_array + 3);
  pcint_deque.insert(pcint_deque.end(), cint_array, cint_array + 3);
  pint_deque.assign(int_array, int_array + 3);
  pcint_deque.assign(int_array, int_array + 3);
  pcint_deque.assign(cint_array, cint_array + 3);

  return EXAM_RESULT;
}

typedef void (*Func)(int);
void f1(int) {}

int EXAM_IMPL(ptrspec_test::function_pointer)
{
  vector<Func> fs;
  fs.push_back(&f1);
  EXAM_CHECK( !fs.empty() );

  return EXAM_RESULT;
}
