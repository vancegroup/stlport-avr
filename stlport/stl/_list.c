/*
 *
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */
#ifndef __STL_LIST_C
#define __STL_LIST_C

#if defined(__MRC__) || defined(__SC__) || defined (__WATCOMC__)
//*TY 05/25/2000 - needed for the mpw workaround in sort()
#include <vector>
#endif

# undef list
# define  list  __WORKAROUND_DBG_RENAME(list)

__STL_BEGIN_NAMESPACE

# if defined (__STL_EXPOSE_GLOBALS_IMPLEMENTATION)

template <class _Dummy>
void __STL_CALL
_List_global<_Dummy>::_Transfer(_List_node_base* __position, 
				_List_node_base* __first, _List_node_base* __last) {
  if (__position != __last) {
    // Remove [first, last) from its old position.
    ((_Node*) (__last->_M_prev))->_M_next = __position;
    ((_Node*) (__first->_M_prev))->_M_next    = __last;
    ((_Node*) (__position->_M_prev))->_M_next = __first; 
    
    // Splice [first, last) into its new position.
    _Node* __tmp = (_Node*) (__position->_M_prev);
    __position->_M_prev = __last->_M_prev;
    __last->_M_prev      = __first->_M_prev; 
    __first->_M_prev    = __tmp;
  }
}

#endif /* defined (__BUILDING_STLPORT) || ! defined (__SGI_STL_OWN_IOSTREAMS) */


template <class _Tp, class _Alloc>
void 
_List_base<_Tp,_Alloc>::clear() 
{
  _List_node<_Tp>* __cur = (_List_node<_Tp>*) this->_M_node._M_data->_M_next;
  while (__cur != this->_M_node._M_data) {
    _List_node<_Tp>* __tmp = __cur;
    __cur = (_List_node<_Tp>*) __cur->_M_next;
    _Destroy(&__tmp->_M_data);
    this->_M_node.deallocate(__tmp, 1);
  }
  this->_M_node._M_data->_M_next = this->_M_node._M_data;
  this->_M_node._M_data->_M_prev = this->_M_node._M_data;
}

# if defined (__STL_NESTED_TYPE_PARAM_BUG) 
#  define size_type      size_t
# endif

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::resize(size_type __new_size, const _Tp& __x)
{
  iterator __i = begin();
  size_type __len = 0;
  for ( ; __i != end() && __len < __new_size; ++__i, ++__len)
    ;
  if (__len == __new_size)
    erase(__i, end());
  else                          // __i == end()
    insert(end(), __new_size - __len, __x);
}

template <class _Tp, class _Alloc>
list<_Tp, _Alloc>& list<_Tp, _Alloc>::operator=(const list<_Tp, _Alloc>& __x)
{
  if (this != &__x) {
    iterator __first1 = begin();
    iterator __last1 = end();
    const_iterator __first2 = __x.begin();
    const_iterator __last2 = __x.end();
    while (__first1 != __last1 && __first2 != __last2) 
      *__first1++ = *__first2++;
    if (__first2 == __last2)
      erase(__first1, __last1);
    else
      insert(__last1, __first2, __last2);
  }
  return *this;
}

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::_M_fill_assign(size_type __n, const _Tp& __val) {
  iterator __i = begin();
  for ( ; __i != end() && __n > 0; ++__i, --__n)
    *__i = __val;
  if (__n > 0)
    insert(end(), __n, __val);
  else
    erase(__i, end());
}

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::sort()
{
  // Do nothing if the list has length 0 or 1.
  if (this->_M_node._M_data->_M_next != this->_M_node._M_data &&
      ((_Node*) (this->_M_node._M_data->_M_next))->_M_next != this->_M_node._M_data) {
    list<_Tp, _Alloc> __carry;
#if !(defined(__MRC__) || defined(__SC__) || defined (__WATCOMC__))
    list<_Tp, _Alloc> __counter[64];
#else
    __vector__<list<_Tp, _Alloc>, _Alloc> __counter(64);		
#endif		//*TY 05/25/2000 - 
    int __fill = 0;
    while (!empty()) {
      __carry.splice(__carry.begin(), *this, begin());
      int __i = 0;
      while(__i < __fill && !__counter[__i].empty()) {
        __counter[__i].merge(__carry);
        __carry.swap(__counter[__i++]);
      }
      __carry.swap(__counter[__i]);         
      if (__i == __fill) ++__fill;
    } 

    for (int __i = 1; __i < __fill; ++__i)
      __counter[__i].merge(__counter[__i-1]);
    swap(__counter[__fill-1]);
  }
}

# undef  list
# undef  size_type

__STL_END_NAMESPACE

#endif /*  __STL_LIST_C */

// Local Variables:
// mode:C++
// End:
