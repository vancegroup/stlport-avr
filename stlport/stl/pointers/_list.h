/*
 *
 * Copyright (c) 2003
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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef _STLP_SPECIALIZED_LIST_H
#define _STLP_SPECIALIZED_LIST_H

#include <stl/pointers/_void_ptr_traits.h>


template <class _Alloc>
class list<void*, _Alloc> : public _List_base<void*, _Alloc> _STLP_STLPORT_CLASS_N
{
  typedef _List_base<void*, _Alloc> _Base;
  typedef list<void*, _Alloc> _Self;
public:
  typedef void* value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef value_type const_reference;
  typedef _List_node<void*> _Node;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  _STLP_FORCE_ALLOCATORS(void*, _Alloc)
  typedef typename _Base::allocator_type allocator_type;
  typedef bidirectional_iterator_tag _Iterator_category;

public:
  typedef _List_iterator<void*, _Nonconst_traits<void*> > iterator;
  typedef _List_iterator<void*, _Const_traits<void*> >    const_iterator;
  _STLP_DECLARE_BIDIRECTIONAL_REVERSE_ITERATORS;

protected:
#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  _Node* _M_create_node(const_reference __x = 0)
#else
  _Node* _M_create_node(const_reference __x)
#endif /*!_STLP_DONT_SUP_DFLT_PARAM*/
  {
    _Node* __p = this->_M_node.allocate(1);
    __p->_M_data = __x;
    return __p;
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  _Node* _M_create_node() {
    _Node* __p = this->_M_node.allocate(1);
    __p->_M_data = 0;
    return __p;
  }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

public:
# if !(defined(__MRC__)||(defined(__SC__) && !defined(__DMC__)))
  explicit
# endif
  list(const allocator_type& __a = allocator_type()) :
    _List_base<void*, _Alloc>(__a) {}

  iterator begin()                      { return iterator(this->_M_node._M_data->_M_next); }
  const_iterator begin() const          { return const_iterator(this->_M_node._M_data->_M_next); }

  iterator end()                        { return this->_M_node._M_data; }
  const_iterator end() const            { return this->_M_node._M_data; }

  reverse_iterator rbegin()             { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

  reverse_iterator rend()               { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); }

  bool empty() const { return this->_M_node._M_data->_M_next == this->_M_node._M_data; }
  size_type size() const {
    size_type __result = distance(begin(), end());
    return __result;
  }
  size_type max_size() const { return size_type(-1); }

  reference front()             { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back()              { return *(--end()); }
  const_reference back() const  { return *(--end()); }

  void swap(_Self &__x) {
    _STLP_STD::swap(this->_M_node, __x._M_node);
  }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __pos, const_reference __x = 0)
#else
  iterator insert(iterator __pos, const_reference __x)
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
  {
    _Node* __tmp = _M_create_node(__x);
    _List_node_base* __n = __pos._M_node;
    _List_node_base* __p = __n->_M_prev;
    __tmp->_M_next = __n;
    __tmp->_M_prev = __p;
    __p->_M_next = __tmp;
    __n->_M_prev = __tmp;
    return __tmp;
  }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_insert_dispatch(__pos, __first, __last, _Integral());
  }
  // Check whether it's an integral type.  If so, it's not an iterator.
  template<class _Integer>
  void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __x,
                          const __true_type& /*_IsIntegral*/) {
    _M_fill_insert(__pos, (size_type) __n, (void*) __x);
  }
  template <class _InputIter>
  void _M_insert_dispatch(iterator __pos, _InputIter __first, _InputIter __last,
                          const __false_type& /*_IsIntegral*/)
#else /* _STLP_MEMBER_TEMPLATES */
  void insert(iterator __pos, const_pointer __first, const_pointer __last) {
    for ( ; __first != __last; ++__first)
      insert(__pos, *__first);
  }
  void insert(iterator __pos, const_iterator __first, const_iterator __last)
#endif /* _STLP_MEMBER_TEMPLATES */
  {
    for ( ; __first != __last; ++__first)
      insert(__pos, *__first);
  }
  void insert(iterator __pos, size_type __n, const_reference __x) { _M_fill_insert(__pos, __n, __x); }

  void _M_fill_insert(iterator __pos, size_type __n, const_reference __x) {
    for ( ; __n > 0; --__n)
      insert(__pos, __x);
  }
  void push_front(const_reference __x) { insert(begin(), __x); }
  void push_back(const_reference __x)  { insert(end(), __x); }

#if defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __pos) { return insert(__pos, __STATIC_CAST(void*, 0)); }
  void push_front() {insert(begin());}
  void push_back() {insert(end());}
# endif /*_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/

  iterator erase(iterator __pos) {
    _List_node_base* __next_node = __pos._M_node->_M_next;
    _List_node_base* __prev_node = __pos._M_node->_M_prev;
    _Node* __n = static_cast<_Node*>(__pos._M_node);
    __prev_node->_M_next = __next_node;
    __next_node->_M_prev = __prev_node;
    this->_M_node.deallocate(__n, 1);
    return iterator(__next_node);
  }

  iterator erase(iterator __first, iterator __last) {
    while (__first != __last)
      erase(__first++);
    return __last;
  }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size, const_reference __x = 0);
#else
  void resize(size_type __new_size, const_reference __x);
  void resize(size_type __new_size) { this->resize(__new_size, __STATIC_CAST(void*, 0)); }
#endif /*!_STLP_DONT_SUP_DFLT_PARAM*/

  void pop_front() { erase(begin()); }
  void pop_back() {
    iterator __tmp = end();
    erase(--__tmp);
  }
#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit list(size_type __n, const_reference __val = 0,
#else
  list(size_type __n, const_reference __val,
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
       const allocator_type& __a = allocator_type())
    : _List_base<void*, _Alloc>(__a)
    { this->insert(begin(), __n, __val); }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit list(size_type __n)
    : _List_base<void*, _Alloc>(allocator_type())
    { this->insert(begin(), __n, __STATIC_CAST(void*, 0)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

#ifdef _STLP_MEMBER_TEMPLATES
  // We don't need any dispatching tricks here, because insert does all of
  // that anyway.
# ifdef _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
  template <class _InputIterator>
  list(_InputIterator __first, _InputIterator __last)
    : _List_base<void*, _Alloc>(allocator_type())
  { insert(begin(), __first, __last); }
# endif
  template <class _InputIterator>
  list(_InputIterator __first, _InputIterator __last,
       const allocator_type& __a _STLP_ALLOCATOR_TYPE_DFL)
    : _List_base<void*, _Alloc>(__a)
  { insert(begin(), __first, __last); }

#else /* _STLP_MEMBER_TEMPLATES */

  list(const_pointer __first, const_pointer __last,
       const allocator_type& __a = allocator_type())
    : _List_base<void*, _Alloc>(__a)
    { insert(begin(), __first, __last); }
  list(const_iterator __first, const_iterator __last,
       const allocator_type& __a = allocator_type())
    : _List_base<void*, _Alloc>(__a)
    { insert(begin(), __first, __last); }

#endif /* _STLP_MEMBER_TEMPLATES */
  list(const _Self& __x) : _List_base<void*, _Alloc>(__x.get_allocator())
    { insert(begin(), __x.begin(), __x.end()); }

  /*explicit list(__full_move_source<_Self> src)
	  : _List_base<void*, _Alloc>(_FullMoveSource<_List_base<void*, _Alloc> >(src.get())) {
  }*/

  explicit list(__partial_move_source<_Self> src)
    : _List_base<void*, _Alloc>(src.get()) {
    src.get()._M_node._M_data = 0;
  }

  ~list() { }

  _Self& operator=(const _Self& __x);

public:
  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, const_reference __val) { _M_fill_assign(__n, __val); }

  void _M_fill_assign(size_type __n, const_reference __val);

#ifdef _STLP_MEMBER_TEMPLATES

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_assign_dispatch(__first, __last, _Integral());
  }

  template <class _Integer>
  void _M_assign_dispatch(_Integer __n, _Integer __val, const __true_type& /*_IsIntegral*/)
    { assign((size_type) __n, __STATIC_CAST(void*, 0)); }

  template <class _InputIterator>
  void _M_assign_dispatch(_InputIterator __first2, _InputIterator __last2,
                          const __false_type& /*_IsIntegral*/) {
    iterator __first1 = begin();
    iterator __last1 = end();
    for ( ; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
      *__first1 = *__first2;
    if (__first2 == __last2)
      erase(__first1, __last1);
    else
      insert(__last1, __first2, __last2);
  }

#endif /* _STLP_MEMBER_TEMPLATES */

public:
  void splice(iterator __pos, _Self& __x) {
    if (!__x.empty())
      _List_global_inst::_Transfer(__pos._M_node, __x.begin()._M_node, __x.end()._M_node);
  }
  void splice(iterator __pos, _Self&, iterator __i) {
    iterator __j = __i;
    ++__j;
    if (__pos == __i || __pos == __j) return;
    _List_global_inst::_Transfer(__pos._M_node, __i._M_node, __j._M_node);
  }
  void splice(iterator __pos, _Self&, iterator __first, iterator __last) {
    if (__first != __last)
      _List_global_inst::_Transfer(__pos._M_node, __first._M_node, __last._M_node);
  }

  void remove(const_reference __val) {
    iterator __first = begin();
    iterator __last = end();
    while (__first != __last) {
      iterator __next = __first;
      ++__next;
      if (__val == *__first) erase(__first);
      __first = __next;
    }
  }

  void unique() {
    _S_unique(*this, equal_to<void*>());
  }

  void merge(_Self& __x) {
    _S_merge(*this, __x, less<void*>());
  }

  void reverse() {
    _List_node_base* __p = this->_M_node._M_data;
    _List_node_base* __tmp = __p;
    do {
      _STLP_STD::swap(__tmp->_M_next, __tmp->_M_prev);
      __tmp = __tmp->_M_prev;     // Old next node is now prev.
    } while (__tmp != __p);
  }

  void sort() {
    _S_sort(*this, less<void*>());
  }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _Predicate> void remove_if(_Predicate __pred)  {
    _S_remove_if(*this, __pred);
  }
  template <class _BinaryPredicate>
    void unique(_BinaryPredicate __binary_pred) {
    _S_unique(*this, __binary_pred);
  }

  template <class _StrictWeakOrdering>
    void merge(_Self &__x,
	  _StrictWeakOrdering __comp) {
    _S_merge(*this, __x, __comp);
  }

  template <class _StrictWeakOrdering>
    void sort(_StrictWeakOrdering __comp) {
    _S_sort(*this, __comp);
  }
#endif /* _STLP_MEMBER_TEMPLATES */

};

# if !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/pointers/_list.c>
# endif

# if defined (_STLP_USE_TEMPLATE_EXPORT)
_STLP_EXPORT_TEMPLATE_CLASS _List_node<void*>;
typedef _List_node<void*> _VoidPtr_Node;
_STLP_EXPORT_TEMPLATE_CLASS _STLP_alloc_proxy<_VoidPtr_Node*, _VoidPtr_Node, allocator<_VoidPtr_Node> >;
_STLP_EXPORT_TEMPLATE_CLASS _List_base<void*,allocator<void*> >;
_STLP_EXPORT_TEMPLATE_CLASS list<void*,allocator<void*> >;
# endif


template <class _Tp, class _Alloc>
class list<_Tp*, _Alloc> _STLP_STLPORT_CLASS_1
{
  //Member datas as a void* list:
  typedef typename _Alloc_traits<void*, _Alloc>::allocator_type _VoidAlloc;
  typedef list<void*, _VoidAlloc> _Base;
  _Base _M_container;

  typedef __void_ptr_traits<_Tp> cast_traits;

  typedef list<_Tp*, _Alloc> _Self;

public:
  typedef _Tp* value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef value_type const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  _STLP_FORCE_ALLOCATORS(_Tp*, _Alloc)
  typedef typename _List_base<_Tp*, _Alloc>::allocator_type allocator_type;
  typedef bidirectional_iterator_tag _Iterator_category;

  typedef _List_iterator<_Tp*, _Nonconst_traits<_Tp*> > iterator;
  typedef _List_iterator<_Tp*, _Const_traits<_Tp*> >    const_iterator;
  _STLP_DECLARE_BIDIRECTIONAL_REVERSE_ITERATORS;

# if !(defined(__MRC__)||(defined(__SC__) && !defined(__DMC__)))
  explicit
# endif
  list(const allocator_type& __a = allocator_type()) : _M_container(__a) {}

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit list(size_type __n, const_reference __val = 0,
#else
  list(size_type __n, const_reference __val,
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
       const allocator_type& __a = allocator_type())
    : _M_container(__n, cast_traits::cast(__val), __a) {}

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit list(size_type __n)
    : _M_container(__n) {}
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

#ifdef _STLP_MEMBER_TEMPLATES
  // We don't need any dispatching tricks here, because insert does all of
  // that anyway.
# ifdef _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
  template <class _InputIterator>
  list(_InputIterator __first, _InputIterator __last)
    : _M_container(__iterator_wrapper<_Tp, _InputIterator>(__first), __iterator_wrapper<_Tp, _InputIterator>(__last)) {}
# endif
  template <class _InputIterator>
  list(_InputIterator __first, _InputIterator __last,
       const allocator_type& __a _STLP_ALLOCATOR_TYPE_DFL)
    : _M_container(__iterator_wrapper<_Tp, _InputIterator>(__first), __iterator_wrapper<_Tp, _InputIterator>(__last), __a) {}

#else /* _STLP_MEMBER_TEMPLATES */

  list(const_pointer __first, const_pointer __last,
       const allocator_type& __a = allocator_type())
    : _M_container(__first, __last, __a) {}
  list(const_iterator __first, const_iterator __last,
       const allocator_type& __a = allocator_type())
    : _M_container(base_const_ite((_Node_Base*)__first._M_node), base_const_ite((_Node_Base*)__last._M_node), __a) {}

#endif /* _STLP_MEMBER_TEMPLATES */
  list(const _Self& __x) : _M_container(__x._M_container) {}

  /*explicit list(__full_move_source<_Self> src)
	  : _List_base<void*, _Alloc>(_FullMoveSource<_List_base<void*, _Alloc> >(src.get())) {
  }*/

  explicit list(__partial_move_source<_Self> src)
	  : _M_container(__partial_move_source<_Base>(src.get()._M_container)) {}

  ~list() { }

  iterator begin()             { return iterator(_M_container.begin()._M_node); }
  const_iterator begin() const { return const_iterator(_M_container.begin()._M_node); }

  iterator end()             { return iterator(_M_container.end()._M_node); }
  const_iterator end() const { return const_iterator(_M_container.end()._M_node); }

  reverse_iterator rbegin()             { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

  reverse_iterator rend()               { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); }

  bool empty() const { return _M_container.empty(); }
  size_type size() const { return _M_container.size(); }
  size_type max_size() const { return _M_container.max_size(); }

  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(--end()); }
  const_reference back() const { return *(--end()); }

  void swap(_Self &__x) { _M_container.swap(__x._M_container); }
  void clear() { _M_container.clear(); }


#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __pos, const_reference __x = 0)
#else
  iterator insert(iterator __pos, const_reference __x)
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
  { return iterator(_M_container.insert(__pos._M_node, cast_traits::cast(__x))._M_node); }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    _M_container.insert(__pos._M_node,
                        __iterator_wrapper<_Tp, _InputIterator>(__first), __iterator_wrapper<_Tp, _InputIterator>(__last));
  }
#else /* _STLP_MEMBER_TEMPLATES */
  void insert(iterator __pos, const_pointer __first, const_pointer __last)
  { _M_container.insert(__pos._M_node, __first._M_node, __last._M_node); }
  void insert(iterator __pos, const_iterator __first, const_iterator __last)
  { _M_container.insert(__pos._M_node, __first._M_node, __last._M_node); }
#endif /* _STLP_MEMBER_TEMPLATES */

  void insert(iterator __pos, size_type __n, const_reference __x)
  { _M_container.insert(__pos._M_node, __n, cast_traits::cast(__x)); }

  void push_front(const_reference __x) { insert(begin(), __x); }
  void push_back(const_reference __x) { insert(end(), __x); }

#if defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __pos) { return insert(__pos, __STATIC_CAST(_Tp*, 0)); }
  void push_front() {insert(begin());}
  void push_back() {insert(end());}
# endif /*_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/

  iterator erase(iterator __pos) { return iterator(_M_container.erase(__pos._M_node)._M_node); }
  iterator erase(iterator __first, iterator __last) { return iterator(_M_container.erase(__first._M_node, __last._M_node)._M_node); }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size, const_reference __x = 0)
#else
  void resize(size_type __new_size) { this->resize(__new_size, __STATIC_CAST(void*, 0)); }
  void resize(size_type __new_size, const_reference __x)
#endif /*!_STLP_DONT_SUP_DFLT_PARAM*/
  {_M_container.resize(__new_size, cast_traits::cast(__x));}

  void pop_front() { _M_container.pop_front(); }
  void pop_back() { _M_container.pop_back(); }

  _Self& operator=(const _Self& __x) {_M_container = __x._M_container; return *this;}
  void assign(size_type __n, const_reference __val) { _M_container.assign(__n, cast_traits::cast(__val)); }

#ifdef _STLP_MEMBER_TEMPLATES

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    _M_container.assign(__iterator_wrapper<_Tp, _InputIterator>(__first), __iterator_wrapper<_Tp, _InputIterator>(__last));
  }

#endif /* _STLP_MEMBER_TEMPLATES */

  void splice(iterator __pos, _Self& __x) { _M_container.splice(__pos._M_node, __x._M_container); }
  void splice(iterator __pos, _Self& __x, iterator __i) { _M_container.splice(__pos._M_node, __x._M_container, __i._M_node); }
  void splice(iterator __pos, _Self& __x, iterator __first, iterator __last) {
    _M_container.splice(__pos._M_node, __x._M_container, __first._M_node, __last._M_node);
  }

  void remove(const_reference __val) { _M_container.remove(cast_traits::cast(__val)); }
  void unique() { _M_container.unique(); }
  void merge(_Self& __x) { _M_container.merge(__x._M_container); }
  void reverse() { _M_container.reverse(); }
  void sort() { _M_container.sort(); }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _Predicate>
  void remove_if(_Predicate __pred)  { _M_container.remove_if(__unary_pred_wrapper<_Tp, _Predicate>(__pred)); }
  template <class _BinaryPredicate>
  void unique(_BinaryPredicate __bin_pred) { _M_container.unique(__binary_pred_wrapper<_Tp, _BinaryPredicate>(__bin_pred)); }

  template <class _StrictWeakOrdering>
  void merge(_Self &__x, _StrictWeakOrdering __comp) {
    _M_container.merge(__x._M_container, __binary_pred_wrapper<_Tp, _StrictWeakOrdering>(__comp));
  }

  template <class _StrictWeakOrdering>
  void sort(_StrictWeakOrdering __comp) { _M_container.sort(__binary_pred_wrapper<_Tp, _StrictWeakOrdering>(__comp)); }
#endif /* _STLP_MEMBER_TEMPLATES */

};

#endif /* _STLP_SPECIALIZED_LIST_H */

// Local Variables:
// mode:C++
// End:
