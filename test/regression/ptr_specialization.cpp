// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

//#define _STLP_DONT_USE_PTR_SPECIALIZATIONS

#include <vector>
#include <list>
#include <slist>
#include <deque>

#include "stlp_test.h"

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

/*
 * Some instanciation to test most of the specialization implementation
 */

#define TEST_INSTANCIATE_CONTAINER(cont) \
  template class cont<int*>; \
  template class cont<int const*>; \
  template class cont<int volatile*>; \
  template class cont<int const volatile*>

# if !defined(_MSC_VER) || (_MSC_VER > 1200)  // including MSVC 6.0
TEST_INSTANCIATE_CONTAINER(vector);
TEST_INSTANCIATE_CONTAINER(list);
TEST_INSTANCIATE_CONTAINER(slist);
TEST_INSTANCIATE_CONTAINER(deque);
#endif

template <class _Tp>
struct unary_pred {
  bool operator () (_Tp *__ptr) const {
   return *__ptr == 0;}
};

template <class _Tp>
struct binary_pred {
  bool operator () (_Tp *__first, _Tp *__second) const {
    return *__first < *__second;
  }
};

int ptr_specialization_test()
{
  vector<int*> pint_vect;
  vector<int const*> pcint_vect;
  list<int*> pint_list;
  list<int const*> pcint_list;
  slist<int*> pint_slist;
  slist<int const*> pcint_slist;
  deque<int*> pint_deque;
  deque<int const*> pcint_deque;

  vector<int*> pint_vect_from_list(pint_list.begin(), pint_list.end());
  pint_vect.insert(pint_vect.begin(), pint_vect.begin(), pint_vect.end());
  pcint_vect.insert(pcint_vect.begin(), pint_vect.begin(), pint_vect.end());
  pint_vect.insert(pint_vect.end(), pint_list.begin(), pint_list.end());
  pcint_vect.insert(pcint_vect.end(), pint_list.begin(), pint_list.end());
  pcint_vect.insert(pcint_vect.end(), pcint_list.begin(), pcint_list.end());
  pint_vect.assign(pint_list.begin(), pint_list.end());
  pcint_vect.assign(pint_list.begin(), pint_list.end());

  pint_list.sort(binary_pred<int>());
  pcint_list.sort(binary_pred<int const>());
  pint_list.unique(binary_pred<int>());
  pcint_list.unique(binary_pred<int const>());
  pint_list.merge(pint_list, binary_pred<int>());
  pcint_list.merge(pcint_list, binary_pred<int const>());
  pint_list.remove_if(unary_pred<int>());
  pcint_list.remove_if(unary_pred<int const>());

  pint_list.insert(pint_list.end(), pint_list.begin(), pint_list.end());
  pcint_list.insert(pcint_list.end(), pint_list.begin(), pint_list.end());
  pint_list.insert(pint_list.end(), pint_vect.begin(), pint_vect.end());
  pcint_list.insert(pcint_list.end(), pint_vect.begin(), pint_vect.end());
  pcint_list.insert(pcint_list.end(), pcint_vect.begin(), pcint_vect.end());
  list<int*> pint_list_from_vect(pint_vect.begin(), pint_vect.end());
  pint_list.assign(pint_vect.begin(), pint_vect.end());
  pcint_list.assign(pint_vect.begin(), pint_vect.end());
  //pint_list.assign(pcint_vect.begin(), pcint_vect.end());

  pint_slist.insert(pint_slist.end(), pint_slist.begin(), pint_slist.end());
  pcint_slist.insert(pcint_slist.end(), pint_slist.begin(), pint_slist.end());
  pint_slist.insert(pint_slist.end(), pint_vect.begin(), pint_vect.end());
  pcint_slist.insert(pcint_slist.end(), pint_vect.begin(), pint_vect.end());
  pcint_slist.insert(pcint_slist.end(), pcint_vect.begin(), pcint_vect.end());
  slist<int*> pint_slist_from_vect(pint_vect.begin(), pint_vect.end());
  pint_slist.assign(pint_vect.begin(), pint_vect.end());
  pcint_slist.assign(pint_vect.begin(), pint_vect.end());
  //pint_slist.assign(pcint_vect.begin(), pcint_vect.end());

  pint_deque.insert(pint_deque.end(), pint_deque.begin(), pint_deque.end());
  pcint_deque.insert(pcint_deque.end(), pint_deque.begin(), pint_deque.end());
  pint_deque.insert(pint_deque.end(), pint_vect.begin(), pint_vect.end());
  pcint_deque.insert(pcint_deque.end(), pint_vect.begin(), pint_vect.end());
  pcint_deque.insert(pcint_deque.end(), pcint_vect.begin(), pcint_vect.end());
  deque<int*> pint_deque_from_vect(pint_deque.begin(), pint_deque.end());
  pint_deque.assign(pint_vect.begin(), pint_vect.end());
  pcint_deque.assign(pint_vect.begin(), pint_vect.end());

  return 0;
}
