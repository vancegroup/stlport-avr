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

#ifndef _STLP_SPECIALIZED_SLIST_H
#define _STLP_SPECIALIZED_SLIST_H

#include <stl/pointers/_void_ptr_traits.h>

template <class _Alloc>
class slist<void*, _Alloc> : protected _Slist_base<void*, _Alloc> _STLP_STLPORT_CLASS_N
{
private:
  typedef _Slist_base<void*,_Alloc> _Base;
  typedef slist<void*, _Alloc> _Self;
public:
  typedef void*             value_type;

  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef value_type        const_reference;
  typedef size_t            size_type;
  typedef ptrdiff_t         difference_type;
  typedef forward_iterator_tag _Iterator_category;

  typedef _Slist_iterator<void*, _Nonconst_traits<void*> >  iterator;
  typedef _Slist_iterator<void*, _Const_traits<void*> >     const_iterator;

  _STLP_FORCE_ALLOCATORS(void*, _Alloc)
  typedef typename _Base::allocator_type allocator_type;

private:
  typedef _Slist_node<void*>    _Node;
  typedef _Slist_node_base      _Node_base;

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  _Node* _M_create_node(const_reference __x = static_cast<void*>(0)) {
#else
  _Node* _M_create_node(const_reference __x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    _Node* __node = this->_M_head.allocate(1);
    __node->_M_data = __x;
    __node->_M_next = 0;
    return __node;
  }
  

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  _Node* _M_create_node() {
    _Node* __node = this->_M_head.allocate(1);
    __node->_M_data = 0;
    __node->_M_next = 0;
    return __node;
  }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

public:
  allocator_type get_allocator() const { return _Base::get_allocator(); }

  explicit slist(const allocator_type& __a = allocator_type()) : _Slist_base<void*,_Alloc>(__a) {}

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit slist(size_type __n, const_reference __x = 0,
#else
  slist(size_type __n, const_reference __x,
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
        const allocator_type& __a =  allocator_type()) : _Slist_base<void*,_Alloc>(__a)
    { _M_insert_after_fill(&this->_M_head._M_data, __n, __x); }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit slist(size_type __n) : _Slist_base<void*,_Alloc>(allocator_type())
    { _M_insert_after_fill(&this->_M_head._M_data, __n, static_cast<void*>(0)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

#ifdef _STLP_MEMBER_TEMPLATES
  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InputIterator>
  slist(_InputIterator __first, _InputIterator __last,
        const allocator_type& __a _STLP_ALLOCATOR_TYPE_DFL) : 
    _Slist_base<void*,_Alloc>(__a)

  { _M_insert_after_range(&this->_M_head._M_data, __first, __last); }
# ifdef _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
  // VC++ needs this crazyness
  template <class _InputIterator>
  slist(_InputIterator __first, _InputIterator __last) :
    _Slist_base<void*,_Alloc>(allocator_type())
  { _M_insert_after_range(&this->_M_head._M_data, __first, __last); }
# endif  
#else /* _STLP_MEMBER_TEMPLATES */
  slist(const_iterator __first, const_iterator __last,
        const allocator_type& __a =  allocator_type() ) :
    _Slist_base<void*,_Alloc>(__a)
    { _M_insert_after_range(&this->_M_head._M_data, __first, __last); }
  slist(const value_type* __first, const value_type* __last,
        const allocator_type& __a =  allocator_type()) : 
    _Slist_base<void*,_Alloc>(__a)
    { _M_insert_after_range(&this->_M_head._M_data, __first, __last); }
#endif /* _STLP_MEMBER_TEMPLATES */

  slist(const _Self& __x) : _Slist_base<void*,_Alloc>(__x.get_allocator())
    { _M_insert_after_range(&this->_M_head._M_data, __x.begin(), __x.end()); }

  /*explicit slist(__full_move_source<_Self> src)
    : _Slist_base<void*, _Alloc>(_FullMoveSource<_Slist_base<void*, _Alloc> >(src.get())) {
  }*/

  explicit slist(__partial_move_source<_Self> src)
    : _Slist_base<void*, _Alloc>(src.get()) {
    src.get()._M_head._M_data._M_next = 0;
  }

  _Self& operator= (const _Self& __x);

  ~slist() {}

public:
  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, const_reference __val)
    { _M_fill_assign(__n, __val); }

  void _M_fill_assign(size_type __n, const_reference __val);

#ifdef _STLP_MEMBER_TEMPLATES

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_assign_dispatch(__first, __last, _Integral());
  }

  template <class _Integer>
  void _M_assign_dispatch(_Integer __n, _Integer __val, const __true_type& /*_IsIntegral*/) {
    _M_fill_assign((size_type) __n, static_cast<void*>(__val));
  }

  template <class _InputIter>
  void _M_assign_dispatch(_InputIter __first, _InputIter __last,
                          const __false_type& /*_IsIntegral*/) {
    _Node_base* __prev = &this->_M_head._M_data;
    _Node_base* __node = this->_M_head._M_data._M_next;
    while (__node != 0 && __first != __last) {
      static_cast<_Node*>(__node)->_M_data = *__first;
      __prev = __node;
      __node = __node->_M_next;
      ++__first;
    }
    if (__first != __last)
      _M_insert_after_range(__prev, __first, __last);
    else
      this->_M_erase_after(__prev, 0);
  }
#endif /* _STLP_MEMBER_TEMPLATES */

public:

  // Experimental new feature: before_begin() returns a
  // non-dereferenceable iterator that, when incremented, yields
  // begin().  This iterator may be used as the argument to
  // insert_after, erase_after, etc.  Note that even for an empty 
  // slist, before_begin() is not the same iterator as end().  It 
  // is always necessary to increment before_begin() at least once to
  // obtain end().
  iterator before_begin() { return iterator(&this->_M_head._M_data); }
  const_iterator before_begin() const
    { return const_iterator(const_cast<_Slist_node_base*>(&this->_M_head._M_data)); }

  iterator begin() { return iterator(this->_M_head._M_data._M_next); }
  const_iterator begin() const 
    { return const_iterator(const_cast<_Slist_node_base*>(this->_M_head._M_data._M_next));}

  iterator end() { return iterator(0); }
  const_iterator end() const { return const_iterator(0); }

  size_type size() const { return _Sl_global_inst::size(this->_M_head._M_data._M_next); }
  
  size_type max_size() const { return size_type(-1); }

  bool empty() const { return this->_M_head._M_data._M_next == 0; }

  void swap(_Self& __x) { 
    _STLP_STD::swap(this->_M_head, __x._M_head); 
  }

public:
  reference front()             { return *begin(); }
  const_reference front() const { return *begin(); }
#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_front(const_reference __x = 0)   {
#else
  void push_front(const_reference __x)   {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    __slist_make_link(&this->_M_head._M_data, _M_create_node(__x));
  }

# if defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_front() { __slist_make_link(&this->_M_head._M_data, _M_create_node());}
# endif /*_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/

  void pop_front() {
    _Node* __node = static_cast<_Node*>(this->_M_head._M_data._M_next);
    this->_M_head._M_data._M_next = __node->_M_next;
    this->_M_head.deallocate(__node, 1);
  }

  iterator previous(const_iterator __pos) {
    return iterator(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node));
  }
  const_iterator previous(const_iterator __pos) const {
    return const_iterator(const_cast<_Slist_node_base*>(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node)));
  }

private:
#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  _Node* _M_insert_after(_Node_base* __pos, const_reference __x = 0) {
#else
  _Node* _M_insert_after(_Node_base* __pos, const_reference __x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    return static_cast<_Node*>(__slist_make_link(__pos, _M_create_node(__x)));
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  _Node* _M_insert_after(_Node_base* __pos) {
    return static_cast<_Node*>(__slist_make_link(__pos, _M_create_node()));
  }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void _M_insert_after_fill(_Node_base* __pos,
                            size_type __n, const_reference __x) {
    for (size_type __i = 0; __i < __n; ++__i)
      __pos = __slist_make_link(__pos, _M_create_node(__x));
  }

#ifdef _STLP_MEMBER_TEMPLATES

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InIter>
  void _M_insert_after_range(_Node_base* __pos, 
                             _InIter __first, _InIter __last) {
    typedef typename _Is_integer<_InIter>::_Integral _Integral;
    _M_insert_after_range(__pos, __first, __last, _Integral());
  }

  template <class _Integer>
  void _M_insert_after_range(_Node_base* __pos, _Integer __n, _Integer __x,
                             const __true_type& /*_IsIntegral*/) {
    _M_insert_after_fill(__pos, __n, __x);
  }


  template <class _InIter>
  void _M_insert_after_range(_Node_base* __pos, _InIter __first, _InIter __last,
                             const __false_type& /*_IsIntegral*/) {
    while (__first != __last) {
      __pos = __slist_make_link(__pos, _M_create_node(*__first));
      ++__first;
    }
  }

#else /* _STLP_MEMBER_TEMPLATES */

  void _M_insert_after_range(_Node_base* __pos,
                             const_iterator __first, const_iterator __last) {
    while (__first != __last) {

      __pos = __slist_make_link(__pos, _M_create_node(*__first));
      ++__first;
    }
  }
  void _M_insert_after_range(_Node_base* __pos,
                             const value_type* __first, const value_type* __last) {
    while (__first != __last) {
      __pos = __slist_make_link(__pos, _M_create_node(*__first));
      ++__first;
    }
  }

#endif /* _STLP_MEMBER_TEMPLATES */

public:

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert_after(iterator __pos, const_reference __x = 0) {
#else
  iterator insert_after(iterator __pos, const_reference __x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    return iterator(_M_insert_after(__pos._M_node, __x));
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert_after(iterator __pos) {
    return insert_after(__pos, static_cast<void*>(0));
  }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void insert_after(iterator __pos, size_type __n, const_reference __x) {
    _M_insert_after_fill(__pos._M_node, __n, __x);
  }

#ifdef _STLP_MEMBER_TEMPLATES

  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InIter>
  void insert_after(iterator __pos, _InIter __first, _InIter __last) {
    _M_insert_after_range(__pos._M_node, __first, __last);
  }

#else /* _STLP_MEMBER_TEMPLATES */

  void insert_after(iterator __pos,
                    const_iterator __first, const_iterator __last) {
    _M_insert_after_range(__pos._M_node, __first, __last);
  }
  void insert_after(iterator __pos,
                    const value_type* __first, const value_type* __last) {
    _M_insert_after_range(__pos._M_node, __first, __last);
  }

#endif /* _STLP_MEMBER_TEMPLATES */

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert(iterator __pos, const_reference __x = 0) {
#else
  iterator insert(iterator __pos, const_reference __x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    return iterator(_M_insert_after(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node),
                    __x));
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert(iterator __pos) {
    return iterator(_M_insert_after(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node),
                                    static_cast<void*>(0)));
  }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void insert(iterator __pos, size_type __n, const_reference __x) {
    _M_insert_after_fill(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node), __n, __x);
  } 
    
#ifdef _STLP_MEMBER_TEMPLATES

  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InIter>
  void insert(iterator __pos, _InIter __first, _InIter __last) {
    _M_insert_after_range(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node), 
                          __first, __last);
  }

#else /* _STLP_MEMBER_TEMPLATES */

  void insert(iterator __pos, const_iterator __first, const_iterator __last) {
    _M_insert_after_range(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node), 
                          __first, __last);
  }
  void insert(iterator __pos, const value_type* __first, 
                              const value_type* __last) {
    _M_insert_after_range(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node), 
                          __first, __last);
  }

#endif /* _STLP_MEMBER_TEMPLATES */


public:
  iterator erase_after(iterator __pos) {
    return iterator(this->_M_erase_after(__pos._M_node));
  }
  iterator erase_after(iterator __before_first, iterator __last) {
    return iterator(this->_M_erase_after(__before_first._M_node, __last._M_node));
  } 

  iterator erase(iterator __pos) {
    return iterator(this->_M_erase_after(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node)));
  }
  iterator erase(iterator __first, iterator __last) {
    return iterator(this->_M_erase_after(_Sl_global_inst::__previous(&this->_M_head._M_data, __first._M_node),
                                         __last._M_node));
  }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type new_size, const_reference __x = 0);
#else
  void resize(size_type new_size, const_reference __x);
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type new_size) { resize(new_size, static_cast<void*>(0)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void clear() {
    this->_M_erase_after(&this->_M_head._M_data, 0); 
  }

public:
  // Moves the range [__before_first + 1, __before_last + 1) to *this,
  //  inserting it immediately after __pos.  This is constant time.
  void splice_after(iterator __pos, 
                    iterator __before_first, iterator __before_last) {
    if (__before_first != __before_last) {
      _Sl_global_inst::__splice_after(__pos._M_node,
                                      __before_first._M_node, 
                                      __before_last._M_node);
    }
  }

  // Moves the element that follows __prev to *this, inserting it immediately
  //  after __pos.  This is constant time.
  void splice_after(iterator __pos, iterator __prev) {
    _Sl_global_inst::__splice_after(__pos._M_node,
                                    __prev._M_node,
                                    __prev._M_node->_M_next);
  }

  // Removes all of the elements from the list __x to *this, inserting
  // them immediately after __pos.  __x must not be *this.  Complexity:
  // linear in __x.size().
  void splice_after(iterator __pos, _Self& __x) {
    _Sl_global_inst::__splice_after(__pos._M_node,
                                    &__x._M_head._M_data);
  }

  // Linear in distance(begin(), __pos), and linear in __x.size().

  void splice(iterator __pos, _Self& __x) {
    if (__x._M_head._M_data._M_next)
      _Sl_global_inst::__splice_after(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node),
                                      &__x._M_head._M_data,
                                      _Sl_global_inst::__previous(&__x._M_head._M_data, 0));
  }

  // Linear in distance(begin(), __pos), and in distance(__x.begin(), __i).
  void splice(iterator __pos, _Self& __x, iterator __i) {
    _Sl_global_inst::__splice_after(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node),
                                    _Sl_global_inst::__previous(&__x._M_head._M_data, __i._M_node),
                                    __i._M_node);
  }

  // Linear in distance(begin(), __pos), in distance(__x.begin(), __first),
  // and in distance(__first, __last).
  void splice(iterator __pos, _Self& __x, iterator __first, iterator __last) {
    if (__first != __last)
      _Sl_global_inst::__splice_after(_Sl_global_inst::__previous(&this->_M_head._M_data, __pos._M_node),
                                      _Sl_global_inst::__previous(&__x._M_head._M_data, __first._M_node),
                                      _Sl_global_inst::__previous(__first._M_node, __last._M_node));
  }

public:
  void reverse() { 
    if (this->_M_head._M_data._M_next)
      this->_M_head._M_data._M_next = _Sl_global_inst::__reverse(this->_M_head._M_data._M_next);
  }

  void remove(const_reference __val); 
  void unique(); 
  void merge(_Self& __x);
  void sort();     

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _Predicate>
  void remove_if(_Predicate __pred) {
    _Node_base* __cur = &this->_M_head._M_data;
    while (__cur->_M_next) {
      if (__pred(static_cast<_Node*>(__cur->_M_next)->_M_data))
        this->_M_erase_after(__cur);
      else
        __cur = __cur->_M_next;
    }
  }


  template <class _BinaryPredicate> 
  void unique(_BinaryPredicate __pred) {
    _Node_base* __cur = this->_M_head._M_data._M_next;
    if (__cur) {
      while (__cur->_M_next) {
        if (__pred(static_cast<_Node*>(__cur)->_M_data,
                   static_cast<_Node*>(__cur->_M_next)->_M_data))
          this->_M_erase_after(__cur);
        else
          __cur = __cur->_M_next;
      }
    }
  }

  template <class _StrictWeakOrdering>
  void merge(_Self& __x, _StrictWeakOrdering __comp) {
    _Node_base* __n1 = &this->_M_head._M_data;
    while (__n1->_M_next && __x._M_head._M_data._M_next) {
      if (__comp(static_cast<_Node*>(__x._M_head._M_data._M_next)->_M_data,
                 static_cast<_Node*>(__n1->_M_next)->_M_data))
        _Sl_global_inst::__splice_after(__n1, &__x._M_head._M_data, __x._M_head._M_data._M_next);
      __n1 = __n1->_M_next;
    }
    if (__x._M_head._M_data._M_next) {
      __n1->_M_next = __x._M_head._M_data._M_next;
      __x._M_head._M_data._M_next = 0;
    }
  }

  template <class _StrictWeakOrdering> 
  void sort(_StrictWeakOrdering __comp) {
    if (this->_M_head._M_data._M_next && this->_M_head._M_data._M_next->_M_next) {
      slist __carry;
      slist __counter[64];
      int __fill = 0;
      while (!empty()) {
        _Sl_global_inst::__splice_after(&__carry._M_head._M_data, &this->_M_head._M_data, this->_M_head._M_data._M_next);
        int __i = 0;
        while (__i < __fill && !__counter[__i].empty()) {
          __counter[__i].merge(__carry, __comp);
          __carry.swap(__counter[__i]);
          ++__i;
        }
        __carry.swap(__counter[__i]);
        if (__i == __fill)
          ++__fill;
      }
      
      for (int __i = 1; __i < __fill; ++__i)
        __counter[__i].merge(__counter[__i-1], __comp);
      this->swap(__counter[__fill-1]);
    }
  }
#endif /* _STLP_MEMBER_TEMPLATES */
};

# if !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/pointers/_slist.c>
# endif

# if defined (_STLP_USE_TEMPLATE_EXPORT)
_STLP_EXPORT_TEMPLATE_CLASS _Slist_node<void*>;
typedef _Slist_node<void*> _VoidPtrSNode;
_STLP_EXPORT_TEMPLATE_CLASS _STLP_alloc_proxy<_Slist_node_base, _VoidPtrSNode, allocator<_VoidPtrSNode> >;
_STLP_EXPORT_TEMPLATE_CLASS _Slist_base<void*, allocator<void*> >;
_STLP_EXPORT_TEMPLATE_CLASS slist<void*, allocator<void*> >;
# endif

template <class _Tp, class _Alloc>
class slist<_Tp*, _Alloc> _STLP_STLPORT_CLASS_1 {
private:
  //Member datas as a void* slist:
  typedef typename _Alloc_traits<void*, _Alloc>::allocator_type _VoidAlloc;
  typedef slist<void*, _VoidAlloc> _Base;
  typedef _Slist_iterator<void*, _Nonconst_traits<void*> >  void_iterator;
  typedef _Slist_iterator<void*, _Const_traits<void*> >     const_void_iterator;
  _Base _M_container;

  typedef __void_ptr_traits<_Tp> cast_traits;

  typedef slist<_Tp*, _Alloc> _Self;

public:
  typedef _Tp*              value_type;

  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef value_type        const_reference;
  typedef size_t            size_type;
  typedef ptrdiff_t         difference_type;
  typedef forward_iterator_tag _Iterator_category;

  typedef _Slist_iterator<value_type, _Nonconst_traits<value_type> >  iterator;
  typedef _Slist_iterator<value_type, _Const_traits<value_type> >     const_iterator;

  _STLP_FORCE_ALLOCATORS(value_type, _Alloc)
  typedef typename _Base::allocator_type allocator_type;

public:
  allocator_type get_allocator() const { return _M_container.get_allocator(); }

  explicit slist(const allocator_type& __a = allocator_type()) : _M_container(__a) {}

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit slist(size_type __n, const_reference __x = 0,
#else
  slist(size_type __n, const_reference __x,
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
        const allocator_type& __a =  allocator_type()) : _M_container(__n, cast_traits::cast(__x), __a) {}

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit slist(size_type __n) : _M_container(__n) {}
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

#ifdef _STLP_MEMBER_TEMPLATES
  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InputIte>
  slist(_InputIte __first, _InputIte __last,
        const allocator_type& __a _STLP_ALLOCATOR_TYPE_DFL) :
    _M_container(__iterator_wrapper<_Tp, _InputIte>(__first), __iterator_wrapper<_Tp, _InputIte>(__last), __a) {}
# ifdef _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
  // VC++ needs this crazyness
  template <class _InputIte>
  slist(_InputIte __first, _InputIte __last) :
    _M_container(__iterator_wrapper<_Tp, _InputIte>(__first), __iterator_wrapper<_Tp, _InputIte>(__last)) {}
# endif
#else /* _STLP_MEMBER_TEMPLATES */
  slist(const_iterator __first, const_iterator __last,
        const allocator_type& __a =  allocator_type() ) :
    _M_container(const_void_iterator(__first._M_node), const_void_iterator(__last._M_node), __a) {}
  slist(const value_type* __first, const value_type* __last,
        const allocator_type& __a =  allocator_type()) :
    _M_container(__first, __last, __a) {}
#endif /* _STLP_MEMBER_TEMPLATES */

  slist(const _Self& __x) : _M_container(__x._M_container) {}

  /*explicit slist(__full_move_source<_Self> src)
    : _Slist_base<void*, _Alloc>(_FullMoveSource<_Slist_base<void*, _Alloc> >(src.get())) {
  }*/

  explicit slist(__partial_move_source<_Self> src)
    : _M_container(__partial_move_source<_Base>(src.get()._M_container)) {}

  _Self& operator= (const _Self& __x) {
    _M_container = __x._M_container;
    return *this;
  }

public:
  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, const_reference __val) { _M_container.assign(__n, cast_traits::cast(__val)); }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _InputIte>
  void assign(_InputIte __first, _InputIte __last) {
    _M_container.assign(__iterator_wrapper<_Tp, _InputIte>(__first), __iterator_wrapper<_Tp, _InputIte>(__last));
  }
#endif /* _STLP_MEMBER_TEMPLATES */

  iterator before_begin()             { return iterator(_M_container.before_begin()._M_node); }
  const_iterator before_begin() const { return const_iterator(const_cast<_Slist_node_base*>(_M_container.before_begin()._M_node)); }

  iterator begin()                    { return iterator(_M_container.begin()._M_node); }
  const_iterator begin() const        { return const_iterator(const_cast<_Slist_node_base*>(_M_container.begin()._M_node));}

  iterator end()                      { return iterator(0); }
  const_iterator end() const          { return const_iterator(0); }

  size_type size() const      { return _M_container.size(); }
  size_type max_size() const  { return size_type(-1); }

  bool empty() const { return _M_container.empty(); }

  void swap(_Self& __x) { _M_container.swap(__x._M_container); }

public:
  reference front()             { return *begin(); }
  const_reference front() const { return *begin(); }
#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_front(const_reference __x = 0)   {
#else
  void push_front(const_reference __x)   {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    _M_container.push_front(cast_traits::cast(__x));
  }

# if defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_front() { _M_container.push_front();}
# endif /*_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/

  void pop_front() { _M_container.pop_front(); }

  iterator previous(const_iterator __pos) { return iterator(_M_container.previous(const_void_iterator(__pos._M_node))._M_node); }
  const_iterator previous(const_iterator __pos) const
    { return const_iterator(const_cast<_Slist_node_base*>(_M_container.previous(const_void_iterator(__pos._M_node))._M_node)); }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert_after(iterator __pos, const_reference __x = 0) {
#else
  iterator insert_after(iterator __pos, const_reference __x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    return iterator(_M_container.insert_after(void_iterator(__pos._M_node), cast_traits::cast(__x))._M_node);
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert_after(iterator __pos) { return iterator(_M_container.insert_after(void_iterator(__pos._M_node))._M_node);}
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void insert_after(iterator __pos, size_type __n, const_reference __x) {
    _M_container.insert_after(void_iterator(__pos._M_node), __n, cast_traits::cast(__x));
  }

#ifdef _STLP_MEMBER_TEMPLATES

  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InIter>
  void insert_after(iterator __pos, _InIter __first, _InIter __last) {
    _M_container.insert_after(void_iterator(__pos._M_node), __iterator_wrapper<_Tp, _InIter>(__first),
                                                            __iterator_wrapper<_Tp, _InIter>(__last));
  }

#else /* _STLP_MEMBER_TEMPLATES */

  void insert_after(iterator __pos,
                    const_iterator __first, const_iterator __last) {
    _M_container.insert_after(void_iterator(__pos._M_node),
                              const_void_iterator(__first._M_node), const_void_iterator(__last._M_node));
  }
  void insert_after(iterator __pos,
                    const value_type* __first, const value_type* __last) {
    _M_container.insert_after(void_iterator(__pos._M_node), __first, __last);
  }

#endif /* _STLP_MEMBER_TEMPLATES */

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert(iterator __pos, const_reference __x = 0) {
#else
  iterator insert(iterator __pos, const_reference __x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    return iterator(_M_container.insert(void_iterator(__pos._M_node), cast_traits::cast(__x))._M_node);
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert(iterator __pos) {
    return iterator(_M_container.insert(void_iterator(__pos._M_node)));
  }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void insert(iterator __pos, size_type __n, const_reference __x) {
    _M_container.insert(void_iterator(__pos._M_node), __n, cast_traits::cast(__x));
  }

#ifdef _STLP_MEMBER_TEMPLATES

  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InIter>
  void insert(iterator __pos, _InIter __first, _InIter __last) {
    _M_container.insert(void_iterator(__pos._M_node), __iterator_wrapper<_Tp, _InIter>(__first),
                                                      __iterator_wrapper<_Tp, _InIter>(__last));
  }

#else /* _STLP_MEMBER_TEMPLATES */

  void insert(iterator __pos, const_iterator __first, const_iterator __last) {
    _M_container.insert(void_iterator(__pos._M_node),
                        const_void_iterator(__first._M_node), const_void_iterator(__last._M_node));
  }
  void insert(iterator __pos, const value_type* __first, const value_type* __last) {
    _M_container.insert(void_iterator(__pos._M_node), __first, __last);
  }

#endif /* _STLP_MEMBER_TEMPLATES */


public:
  iterator erase_after(iterator __pos) {
    return iterator(_M_container.erase_after(void_iterator(__pos._M_node))._M_node);
  }
  iterator erase_after(iterator __before_first, iterator __last) {
    return iterator(_M_container.erase_after(void_iterator(__before_first._M_node),
                                             void_iterator(__last._M_node))._M_node);
  }

  iterator erase(iterator __pos) {
    return iterator(_M_container.erase(void_iterator(__pos._M_node))._M_node);
  }
  iterator erase(iterator __first, iterator __last) {
    return iterator(_M_container.erase(void_iterator(__first._M_node),
                                       void_iterator(__last._M_node))._M_node);
  }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size, const_reference __x = 0)
#else
  void resize(size_type __new_size, const_reference __x)
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
  { _M_container.resize(__new_size, cast_traits::cast(__x));}

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size) { _M_container.resize(__new_size); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void clear() { _M_container.clear(); }

  void splice_after(iterator __pos,
                    iterator __before_first, iterator __before_last) {
    _M_container.splice_after(void_iterator(__pos._M_node),
                              void_iterator(__before_first._M_node), void_iterator(__before_last._M_node));
  }
  void splice_after(iterator __pos, iterator __prev) {
    _M_container.splice_after(void_iterator(__pos._M_node), void_iterator(__prev._M_node));
  }
  void splice_after(iterator __pos, _Self& __x) {
    _M_container.splice_after(void_iterator(__pos._M_node), __x._M_container);
  }
  void splice(iterator __pos, _Self& __x) {
    _M_container.splice(void_iterator(__pos._M_node), __x._M_container);
  }
  void splice(iterator __pos, _Self& __x, iterator __i) {
    _M_container.splice(void_iterator(__pos._M_node), __x._M_container, void_iterator(__i._M_node));
  }
  void splice(iterator __pos, _Self& __x, iterator __first, iterator __last) {
    _M_container.splice(void_iterator(__pos._M_node), __x._M_container,
                        void_iterator(__first._M_node), void_iterator(__last._M_node));
  }

public:
  void reverse() { _M_container.reverse(); }

  void remove(const_reference __val) { _M_container.remove(cast_traits::cast(__val)); }
  void unique() { _M_container.unique(); }
  void merge(_Self& __x) { _M_container.merge(__x._M_container); }
  void sort() {_M_container.sort(); }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _Predicate>
  void remove_if(_Predicate __pred) {
    _M_container.remove_if(__unary_pred_wrapper<_Tp, _Predicate>(__pred));
  }

  template <class _BinaryPredicate>
  void unique(_BinaryPredicate __pred) {
    _M_container.unique(__binary_pred_wrapper<_Tp, _BinaryPredicate>(__pred));
  }

  template <class _StrictWeakOrdering>

  void merge(_Self& __x, _StrictWeakOrdering __comp) {
    _M_container.merge(__x._M_container, __binary_pred_wrapper<_Tp, _StrictWeakOrdering>(__comp));
  }

  template <class _StrictWeakOrdering>
  void sort(_StrictWeakOrdering __comp) {
    _M_container.sort(__binary_pred_wrapper<_Tp, _StrictWeakOrdering>(__comp));
  }
#endif /* _STLP_MEMBER_TEMPLATES */

};


#endif /* _STLP_SPECIALIZED_SLIST_H */

// Local Variables:
// mode:C++
// End:

