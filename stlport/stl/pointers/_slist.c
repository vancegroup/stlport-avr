/*
 *
 * Copyright (c) 2004
 * Francois Dumont
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
#ifndef _STLP_SLIST_SPECIALIZED_C
#define _STLP_SLIST_SPECIALIZED_C

#ifndef _STLP_SPECIALIZED_SLIST_H
# include <stl/specialized/_slist.h>
#endif


template <class _Alloc>
slist<void*,_Alloc>& slist<void*,_Alloc>::operator=(const slist<void*,_Alloc>& __x)
{
  if (&__x != this) {
    _Node_base* __p1 = &this->_M_head._M_data;
    _Node* __n1 = static_cast<_Node*>(this->_M_head._M_data._M_next);
    const _Node* __n2 = static_cast<const _Node*>(__x._M_head._M_data._M_next);
    while (__n1 && __n2) {
      __n1->_M_data = __n2->_M_data;
      __p1 = __n1;
      __n1 = static_cast<_Node*>(__n1->_M_next);
      __n2 = static_cast<const _Node*>(__n2->_M_next);
    }
    if (__n2 == 0)
      this->_M_erase_after(__p1, 0);
    else
      _M_insert_after_range(__p1, const_iterator(const_cast<_Node*>(__n2)), 
                                  const_iterator(0));
  }
  return *this;
}

template <class _Alloc>
void slist<void*, _Alloc>::_M_fill_assign(size_type __n, const_reference __val) {
  _Node_base* __prev = &this->_M_head._M_data;
  _Node* __node = static_cast<_Node*>(this->_M_head._M_data._M_next);
  for ( ; __node != 0 && __n > 0 ; --__n) {
    __node->_M_data = __val;
    __prev = __node;
    __node = static_cast<_Node*>(__node->_M_next);
  }
  if (__n > 0)
    _M_insert_after_fill(__prev, __n, __val);
  else
    this->_M_erase_after(__prev, 0);
}


template <class _Alloc>
void slist<void*, _Alloc>::resize(size_type __len, const_reference __x) {
  _Node_base* __cur = &this->_M_head._M_data;
  while (__cur->_M_next != 0 && __len > 0) {
    --__len;
    __cur = __cur->_M_next;
  }
  if (__cur->_M_next) 
    this->_M_erase_after(__cur, 0);
  else
    _M_insert_after_fill(__cur, __len, __x);
}

template <class _Alloc>
void slist<void*, _Alloc>::remove(const_reference __val) {
  _Node_base* __cur = &this->_M_head._M_data;
  while (__cur && __cur->_M_next) {
    if (static_cast<_Node*>(__cur->_M_next)->_M_data == __val)
      this->_M_erase_after(__cur);
    else
      __cur = __cur->_M_next;
  }
}

template <class _Alloc> 
void slist<void*, _Alloc>::unique() {
  _Node_base* __cur = this->_M_head._M_data._M_next;
  if (__cur) {
    while (__cur->_M_next) {
      if (static_cast<_Node*>(__cur)->_M_data == static_cast<_Node*>(__cur->_M_next)->_M_data)
        this->_M_erase_after(__cur);
      else
        __cur = __cur->_M_next;
    }
  }
}

template <class _Alloc>
void slist<void*, _Alloc>::merge(slist<void*, _Alloc>& __x) {
  _Node_base* __n1 = &this->_M_head._M_data;
  while (__n1->_M_next && __x._M_head._M_data._M_next) {
    if (static_cast<_Node*>(__x._M_head._M_data._M_next)->_M_data < static_cast<_Node*>(__n1->_M_next)->_M_data) 
      _Sl_global_inst::__splice_after(__n1, &__x._M_head._M_data, __x._M_head._M_data._M_next);
    __n1 = __n1->_M_next;
  }
  if (__x._M_head._M_data._M_next) {
    __n1->_M_next = __x._M_head._M_data._M_next;
    __x._M_head._M_data._M_next = 0;
  }
}

template <class _Alloc>
void slist<void*, _Alloc>::sort() {
  if (this->_M_head._M_data._M_next && this->_M_head._M_data._M_next->_M_next) {
    _Self __carry;
    _Self __counter[64];
    int __fill = 0;
    while (!empty()) {
      _Sl_global_inst::__splice_after(&__carry._M_head._M_data, &this->_M_head._M_data, this->_M_head._M_data._M_next);
      int __i = 0;
      while (__i < __fill && !__counter[__i].empty()) {
        __counter[__i].merge(__carry);
        __carry.swap(__counter[__i]);
        ++__i;
      }
      __carry.swap(__counter[__i]);
      if (__i == __fill)
        ++__fill;
    }

    for (int __i = 1; __i < __fill; ++__i)
      __counter[__i].merge(__counter[__i-1]);
    this->swap(__counter[__fill-1]);
  }
}

#endif /*  _STLP_SLIST_SPECIALIZED_C */

// Local Variables:
// mode:C++
// End:
