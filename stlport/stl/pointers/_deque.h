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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef _STLP_SPECIALIZED_DEQUE_H
#define _STLP_SPECIALIZED_DEQUE_H

#ifndef _STLP_VOID_PTR_TRAITS_H
# include <stl/pointers/_void_ptr_traits.h>
#endif

/*
 * void* specialization to break the potential loop instanciation with pointer specialization
 */
template <class _Alloc >
class deque<void*, _Alloc> : protected _Deque_base<void*, _Alloc> _STLP_STLPORT_CLASS_N
{
  typedef _Deque_base<void*, _Alloc> _Base;
  typedef deque<void*, _Alloc> _Self;
public:                         // Basic types
  typedef void* value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag _Iterator_category;
  _STLP_FORCE_ALLOCATORS(void*, _Alloc)
  typedef typename _Base::allocator_type allocator_type;

public:                         // Iterators
  typedef typename _Base::iterator       iterator;
  typedef typename _Base::const_iterator const_iterator;

  _STLP_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS;

protected:                      // Internal typedefs
  typedef pointer* _Map_pointer;
  typedef __true_type _TrivialAss;
  typedef __true_type _IsPODType;

public:                         // Basic accessors
  iterator begin() { return this->_M_start; }
  iterator end() { return this->_M_finish; }
  const_iterator begin() const { return const_iterator(this->_M_start); }
  const_iterator end() const { return const_iterator(this->_M_finish); }

  reverse_iterator rbegin() { return reverse_iterator(this->_M_finish); }
  reverse_iterator rend() { return reverse_iterator(this->_M_start); }
  const_reverse_iterator rbegin() const
    { return const_reverse_iterator(this->_M_finish); }
  const_reverse_iterator rend() const
    { return const_reverse_iterator(this->_M_start); }

  reference operator[](size_type __n)
    { return this->_M_start[difference_type(__n)]; }
  const_reference operator[](size_type __n) const
    { return this->_M_start[difference_type(__n)]; }

  void _M_range_check(size_type __n) const {
    if (__n >= this->size())
      __stl_throw_out_of_range("deque");
  }
  reference at(size_type __n)
    { _M_range_check(__n); return (*this)[__n]; }
  const_reference at(size_type __n) const
    { _M_range_check(__n); return (*this)[__n]; }

  reference front() { return *this->_M_start; }
  reference back() {
    iterator __tmp = this->_M_finish;
    --__tmp;
    return *__tmp;
  }
  const_reference front() const { return *this->_M_start; }
  const_reference back() const {
    const_iterator __tmp = this->_M_finish;
    --__tmp;
    return *__tmp;
  }

  size_type size() const { return this->_M_finish - this->_M_start; }
  size_type max_size() const { return size_type(-1); }
  bool empty() const { return this->_M_finish == this->_M_start; }
  allocator_type get_allocator() const { return this->_M_map_size; }

public:                         // Constructor, destructor.
  explicit deque(const allocator_type& __a = allocator_type())
    : _Deque_base<void*, _Alloc>(__a, 0) {}

  deque(const _Self& __x) :
    _Deque_base<void*, _Alloc>(__x.get_allocator(), __x.size()) {
      __uninitialized_copy(__x.begin(), __x.end(), this->_M_start, _IsPODType());
  }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit deque(size_type __n, value_type __val = 0,
#else
  deque(size_type __n, value_type __val,
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
        const allocator_type& __a = allocator_type()) :
    _Deque_base<void*, _Alloc>(__a, __n) {
    _M_fill_initialize(__val);
  }
  // int,long variants may be needed
#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit deque(size_type __n) : _Deque_base<void*, _Alloc>(allocator_type(), __n)
  { _M_fill_initialize(__STATIC_CAST(void*, 0)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

#ifdef _STLP_MEMBER_TEMPLATES

  template <class _Integer>
  void _M_initialize_dispatch(_Integer __n, _Integer __x, const __true_type&) {
    this->_M_initialize_map(__n);
    _M_fill_initialize(__x);
  }

  template <class _InputIter>
  void _M_initialize_dispatch(_InputIter __first, _InputIter __last,
                              const __false_type&) {
    _M_range_initialize(__first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIter));
  }

# ifdef _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
  // VC++ needs this
  template <class _InputIterator>
  deque(_InputIterator __first, _InputIterator __last) :
    _Deque_base<void*, _Alloc>(allocator_type()) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_initialize_dispatch(__first, __last, _Integral());
  }
# endif

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  deque(_InputIterator __first, _InputIterator __last,
        const allocator_type& __a _STLP_ALLOCATOR_TYPE_DFL) :
    _Deque_base<void*, _Alloc>(__a) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_initialize_dispatch(__first, __last, _Integral());
  }

# else
  deque(const value_type* __first, const value_type* __last,
        const allocator_type& __a = allocator_type() )
    : _Deque_base<void*, _Alloc>(__a, __last - __first) {
    __uninitialized_copy(__first, __last, this->_M_start, _IsPODType());
  }

  deque(const_iterator __first, const_iterator __last,
        const allocator_type& __a = allocator_type() )
    : _Deque_base<void*, _Alloc>(__a, __last - __first) {
    __uninitialized_copy(__first, __last, this->_M_start, _IsPODType());
  }
#endif /* _STLP_MEMBER_TEMPLATES */

  deque(__move_source<_Self> src)
    : _Deque_base<void*, _Alloc>(__move_source<_Base>(src.get())) {
  }

  ~deque() {
  }

  _Self& operator= (const _Self& __x);

  void swap(_Self& __x) {
    _STLP_STD::swap(this->_M_start, __x._M_start);
    _STLP_STD::swap(this->_M_finish, __x._M_finish);
    _STLP_STD::swap(this->_M_map, __x._M_map);
    _STLP_STD::swap(this->_M_map_size, __x._M_map_size);
  }

public:
  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void _M_fill_assign(size_type __n, void *__val) {
    if (__n > size()) {
      _STLP_STD::fill(begin(), end(), __val);
      insert(end(), __n - size(), __val);
    }
    else {
      erase(begin() + __n, end());
      _STLP_STD::fill(begin(), end(), __val);
    }
  }

  void assign(size_type __n, void *__val) {
    _M_fill_assign(__n, __val);
  }

#ifdef _STLP_MEMBER_TEMPLATES

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_assign_dispatch(__first, __last, _Integral());
  }

private:                        // helper functions for assign()

  template <class _Integer>
  void _M_assign_dispatch(_Integer __n, _Integer __val,
                          const __true_type& /*_IsIntegral*/)
  { _M_fill_assign((size_type) __n, (void*) __val); }

  template <class _InputIterator>
  void _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
                          const __false_type& /*_IsIntegral*/) {
    _M_assign_aux(__first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIterator));
  }

  template <class _InputIter>
  void _M_assign_aux(_InputIter __first, _InputIter __last, const input_iterator_tag &) {
    iterator __cur = begin();
    for ( ; __first != __last && __cur != end(); ++__cur, ++__first)
      *__cur = *__first;
    if (__first == __last)
      erase(__cur, end());
    else
      insert(end(), __first, __last);
  }

  template <class _ForwardIterator>
  void _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
                     const forward_iterator_tag &) {
    size_type __len = distance(__first, __last);
    if (__len > size()) {
      _ForwardIterator __mid = __first;
      advance(__mid, size());
      copy(__first, __mid, begin());
      insert(end(), __mid, __last);
    }
    else
      erase(copy(__first, __last, begin()), end());
  }

#endif /* _STLP_MEMBER_TEMPLATES */

public:                         // push_* and pop_*

#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_back(void *__t = 0) {
#else
  void push_back(void *__t) {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    if (this->_M_finish._M_cur != this->_M_finish._M_last - 1) {
      *this->_M_finish._M_cur = __t;
      ++this->_M_finish._M_cur;
    }
    else
      _M_push_back_aux_v(__t);
  }
#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_front(void *__t = 0)   {
#else
  void push_front(void *__t)   {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    if (this->_M_start._M_cur != this->_M_start._M_first) {
      *(this->_M_start._M_cur - 1) = __t;
      --this->_M_start._M_cur;
    }
    else
      _M_push_front_aux_v(__t);
  }

# if defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_back() {
    if (this->_M_finish._M_cur != this->_M_finish._M_last - 1) {
      *this->_M_finish._M_cur = 0;
      ++this->_M_finish._M_cur;
    }
    else
      _M_push_back_aux();
  }
  void push_front() {
    if (this->_M_start._M_cur != this->_M_start._M_first) {
      *(this->_M_start._M_cur - 1) = 0;
      --this->_M_start._M_cur;
    }
    else
      _M_push_front_aux();
  }
# endif /*_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/

  void pop_back() {
    if (this->_M_finish._M_cur != this->_M_finish._M_first) {
      --this->_M_finish._M_cur;
    }
    else
      _M_pop_back_aux();
  }

  void pop_front() {
    if (this->_M_start._M_cur != this->_M_start._M_last - 1) {
      ++this->_M_start._M_cur;
    }
    else
      _M_pop_front_aux();
  }

public:                         // Insert

#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __position, void *__x = 0) {
#else
  iterator insert(iterator __position, void *__x) {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    if (__position._M_cur == this->_M_start._M_cur) {
      push_front(__x);
      return this->_M_start;
    }
    else if (__position._M_cur == this->_M_finish._M_cur) {
      push_back(__x);
      iterator __tmp = this->_M_finish;
      --__tmp;
      return __tmp;
    }
    else {
      return _M_insert_aux(__position, __x);
    }
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __position)
  { return insert(__position, _STATIC_CAST(void*, 0)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/

  void insert(iterator __pos, size_type __n, void *__x) {
    _M_fill_insert(__pos, __n, __x);
  }

  void _M_fill_insert(iterator __pos, size_type __n, void *__x);

#ifdef _STLP_MEMBER_TEMPLATES

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_insert_dispatch(__pos, __first, __last, _Integral());
  }

  template <class _Integer>
  void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __x,
                          const __true_type& /*_IsIntegral*/) {
    _M_fill_insert(__pos, (size_type) __n, (value_type) __x);
  }

  template <class _InputIterator>
  void _M_insert_dispatch(iterator __pos,
                          _InputIterator __first, _InputIterator __last,
                          const __false_type& /*_IsIntegral*/) {
    insert(__pos, __first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIterator));
  }

#else /* _STLP_MEMBER_TEMPLATES */

  void insert(iterator __pos,
              const value_type* __first, const value_type* __last);
  void insert(iterator __pos,
              const_iterator __first, const_iterator __last);

#endif /* _STLP_MEMBER_TEMPLATES */

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size, void *__x = 0) {
#else
  void resize(size_type __new_size, void *__x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    const size_type __len = size();
    if (__new_size < __len)
      erase(this->_M_start + __new_size, this->_M_finish);
    else
      insert(this->_M_finish, __new_size - __len, __x);
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type new_size) { resize(new_size, _STATIC_CAST(void*, 0)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

public:                         // Erase
  iterator erase(iterator __pos) {
    iterator __next = __pos;
    ++__next;
    difference_type __index = __pos - this->_M_start;
    if (size_type(__index) < this->size() >> 1) {
      copy_backward(this->_M_start, __pos, __next);
      pop_front();
    }
    else {
      copy(__next, this->_M_finish, __pos);
      pop_back();
    }
    return this->_M_start + __index;
  }

  iterator erase(iterator __first, iterator __last);
  void clear();

protected:                        // Internal construction/destruction

  void _M_fill_initialize(value_type __val);

#ifdef _STLP_MEMBER_TEMPLATES

  template <class _InputIterator>
  void _M_range_initialize(_InputIterator __first,
                           _InputIterator __last,
                           const input_iterator_tag &) {
    this->_M_initialize_map(0);
    _STLP_TRY {
      for ( ; __first != __last; ++__first)
        push_back(*__first);
    }
    _STLP_UNWIND(clear())
  }
  template <class _ForwardIterator>
  void  _M_range_initialize(_ForwardIterator __first,
                            _ForwardIterator __last,
                            const forward_iterator_tag &)  {
   size_type __n = distance(__first, __last);
   this->_M_initialize_map(__n);
   _Map_pointer __cur_node;
   _STLP_TRY {
    for (__cur_node = this->_M_start._M_node;
         __cur_node < this->_M_finish._M_node;
         ++__cur_node) {
      _ForwardIterator __mid = __first;
      advance(__mid, this->buffer_size());
      uninitialized_copy(__first, __mid, *__cur_node);
      __first = __mid;
    }
    uninitialized_copy(__first, __last, this->_M_finish._M_first);
   }
  _STLP_UNWIND(_STLP_STD::_Destroy_Range(this->_M_start, iterator(*__cur_node, __cur_node)))
 }
#endif /* _STLP_MEMBER_TEMPLATES */

protected:                        // Internal push_* and pop_*

  void _M_push_back_aux_v(void*);
  void _M_push_front_aux_v(void*);
# if defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void _M_push_back_aux();
  void _M_push_front_aux();
# endif /*_STLP_DONT_SUP_DFLT_PARAM !_STLP_NO_ANACHRONISMS*/
  void _M_pop_back_aux();
  void _M_pop_front_aux();

protected:                        // Internal insert functions

#ifdef _STLP_MEMBER_TEMPLATES

template <class _InputIterator>
void insert(iterator __pos,
            _InputIterator __first,
            _InputIterator __last,
            const input_iterator_tag &) {
  copy(__first, __last, inserter(*this, __pos));
}

template <class _ForwardIterator>
void  insert(iterator __pos,
             _ForwardIterator __first,
             _ForwardIterator __last,
             const forward_iterator_tag &) {
  size_type __n = distance(__first, __last);
  if (__pos._M_cur == this->_M_start._M_cur) {
    iterator __new_start = _M_reserve_elements_at_front(__n);
    _STLP_TRY {
      uninitialized_copy(__first, __last, __new_start);
      this->_M_start = __new_start;
    }
    _STLP_UNWIND(this->_M_destroy_nodes(__new_start._M_node, this->_M_start._M_node))
  }
  else if (__pos._M_cur == this->_M_finish._M_cur) {
    iterator __new_finish = _M_reserve_elements_at_back(__n);
    _STLP_TRY {
      uninitialized_copy(__first, __last, this->_M_finish);
      this->_M_finish = __new_finish;
    }
    _STLP_UNWIND(this->_M_destroy_nodes(this->_M_finish._M_node + 1, __new_finish._M_node + 1))
  }
  else
    _M_insert_aux(__pos, __first, __last, __n);
}
#endif /* _STLP_MEMBER_TEMPLATES */

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator _M_insert_aux(iterator __pos, void *__x = 0);
#else
  iterator _M_insert_aux(iterator __pos, void *__x);
  iterator _M_insert_aux(iterator __pos);
#endif /*!_STLP_DONT_SUP_DFLT_PARAM*/
  iterator _M_insert_aux_prepare(iterator __pos);

  void _M_insert_aux(iterator __pos, size_type __n, void *__x);

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _ForwardIterator>
  void _M_insert_aux(iterator __pos,
                     _ForwardIterator __first,
                     _ForwardIterator __last,
                     size_type __n) {
    const difference_type __elemsbefore = __pos - this->_M_start;
    size_type __length = size();
    if (__elemsbefore < difference_type(__length / 2)) {
      iterator __new_start = _M_reserve_elements_at_front(__n);
      iterator __old_start = this->_M_start;
      __pos = this->_M_start + __elemsbefore;
      _STLP_TRY {
        if (__elemsbefore >= difference_type(__n)) {
          iterator __start_n = this->_M_start + difference_type(__n);
          uninitialized_copy(this->_M_start, __start_n, __new_start);
          this->_M_start = __new_start;
          copy(__start_n, __pos, __old_start);
          copy(__first, __last, __pos - difference_type(__n));
        }
        else {
          _ForwardIterator __mid = __first;
          advance(__mid, difference_type(__n) - __elemsbefore);
          __uninitialized_copy_copy(this->_M_start, __pos, __first, __mid,
                                    __new_start, _IsPODType());
          this->_M_start = __new_start;
          copy(__mid, __last, __old_start);
        }
      }
      _STLP_UNWIND(this->_M_destroy_nodes(__new_start._M_node, this->_M_start._M_node))
    }
    else {
      iterator __new_finish = _M_reserve_elements_at_back(__n);
      iterator __old_finish = this->_M_finish;
      const difference_type __elemsafter =
      difference_type(__length) - __elemsbefore;
      __pos = this->_M_finish - __elemsafter;
      _STLP_TRY {
        if (__elemsafter > difference_type(__n)) {
          iterator __finish_n = this->_M_finish - difference_type(__n);
          uninitialized_copy(__finish_n, this->_M_finish, this->_M_finish);
          this->_M_finish = __new_finish;
          copy_backward(__pos, __finish_n, __old_finish);
          copy(__first, __last, __pos);
        }
        else {
          _ForwardIterator __mid = __first;
          advance(__mid, __elemsafter);
          __uninitialized_copy_copy(__mid, __last, __pos, this->_M_finish, this->_M_finish, _IsPODType());
          this->_M_finish = __new_finish;
          copy(__first, __mid, __pos);
        }
      }
      _STLP_UNWIND(this->_M_destroy_nodes(this->_M_finish._M_node + 1, __new_finish._M_node + 1))
    }
  }
#else /* _STLP_MEMBER_TEMPLATES */

  void _M_insert_aux(iterator __pos,
                     const_pointer __first, const_pointer __last,
                     size_type __n);

  void _M_insert_aux(iterator __pos,
                     const_iterator __first, const_iterator __last,
                     size_type __n);

#endif /* _STLP_MEMBER_TEMPLATES */

  iterator _M_reserve_elements_at_front(size_type __n) {
    size_type __vacancies = this->_M_start._M_cur - this->_M_start._M_first;
    if (__n > __vacancies)
      _M_new_elements_at_front(__n - __vacancies);
    return this->_M_start - difference_type(__n);
  }

  iterator _M_reserve_elements_at_back(size_type __n) {
    size_type __vacancies = (this->_M_finish._M_last - this->_M_finish._M_cur) - 1;
    if (__n > __vacancies)
      _M_new_elements_at_back(__n - __vacancies);
    return this->_M_finish + difference_type(__n);
  }

  void _M_new_elements_at_front(size_type __new_elements);
  void _M_new_elements_at_back(size_type __new_elements);

protected:                      // Allocation of _M_map and nodes

  // Makes sure the _M_map has space for new nodes.  Does not actually
  //  add the nodes.  Can invalidate _M_map pointers.  (And consequently,
  //  deque iterators.)

  void _M_reserve_map_at_back (size_type __nodes_to_add = 1) {
    if (__nodes_to_add + 1 > this->_M_map_size._M_data - (this->_M_finish._M_node - this->_M_map._M_data))
      _M_reallocate_map(__nodes_to_add, false);
  }

  void _M_reserve_map_at_front (size_type __nodes_to_add = 1) {
    if (__nodes_to_add > size_type(this->_M_start._M_node - this->_M_map._M_data))
      _M_reallocate_map(__nodes_to_add, true);
  }

  void _M_reallocate_map(size_type __nodes_to_add, bool __add_at_front);
};

# if !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/pointers/_deque.c>
# endif

# if defined (_STLP_USE_TEMPLATE_EXPORT)
_STLP_EXPORT_TEMPLATE_CLASS _STLP_alloc_proxy<size_t, void*,  allocator<void*> >;
_STLP_EXPORT_TEMPLATE_CLASS _STLP_alloc_proxy<void***, void**,  allocator<void**> >;
_STLP_EXPORT_TEMPLATE_CLASS _Deque_base<void*,allocator<void*> >;
_STLP_EXPORT_TEMPLATE_CLASS deque<void*,allocator<void*> >;
# endif

template <class _Tp, class _Alloc>
class deque<_Tp*, _Alloc> _STLP_STLPORT_CLASS_1
{
  typedef typename _Alloc_traits<void*, _Alloc>::allocator_type _VoidAlloc;
  typedef deque<void*, _VoidAlloc> _Base;
  _Base _M_container;
  
  typedef __void_ptr_traits<_Tp> cast_traits;
  
  typedef deque<_Tp*, _Alloc> _Self;

public:                         // Basic types
  typedef _Tp* value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag _Iterator_category;
  _STLP_FORCE_ALLOCATORS(_Tp, _Alloc)
  typedef typename _Alloc_traits<value_type, _Alloc>::allocator_type allocator_type;

public:                         // Iterators
  typedef _Deque_iterator<value_type, _Nonconst_traits<value_type> > iterator;
  typedef _Deque_iterator<value_type, _Const_traits<value_type> >    const_iterator;

  _STLP_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS;

private:
  typedef typename _Base::iterator _BaseIterator;
  static iterator _M_ite_cast (_BaseIterator const&__void_ite) {
    iterator tmp;
    tmp._M_cur = cast_traits::ptr_cast(__void_ite._M_cur);
    tmp._M_first = cast_traits::ptr_cast(__void_ite._M_first);
    tmp._M_last = cast_traits::ptr_cast(__void_ite._M_last);
    tmp._M_node = cast_traits::ptr_ptr_cast(__void_ite._M_node);
    return tmp;
  }
  static _BaseIterator _M_ite_cast (iterator const&__t_ite) {
    _BaseIterator tmp;
    tmp._M_cur = cast_traits::ptr_cast(__t_ite._M_cur);
    tmp._M_first = cast_traits::ptr_cast(__t_ite._M_first);
    tmp._M_last = cast_traits::ptr_cast(__t_ite._M_last);
    tmp._M_node = cast_traits::ptr_ptr_cast(__t_ite._M_node);
    return tmp;
  }

  typedef typename _Base::const_iterator _BaseCIterator;
  static const_iterator _M_const_ite_cast (_BaseCIterator const&__void_ite) {
    const_iterator tmp;
    tmp._M_cur = cast_traits::ptr_cast(__void_ite._M_cur);
    tmp._M_first = cast_traits::ptr_cast(__void_ite._M_first);
    tmp._M_last = cast_traits::ptr_cast(__void_ite._M_last);
    tmp._M_node = cast_traits::ptr_ptr_cast(__void_ite._M_node);
    return tmp;
  }
  static _BaseCIterator _M_const_ite_cast (const_iterator const&__t_ite) {
    _BaseCIterator tmp;
    tmp._M_cur = cast_traits::ptr_cast(__t_ite._M_cur);
    tmp._M_first = cast_traits::ptr_cast(__t_ite._M_first);
    tmp._M_last = cast_traits::ptr_cast(__t_ite._M_last);
    tmp._M_node = cast_traits::ptr_ptr_cast(__t_ite._M_node);
    return tmp;
  }

public:                         // Basic accessors
  iterator begin() { return _M_ite_cast(_M_container.begin()); }
  iterator end() { return _M_ite_cast(_M_container.end()); }
  const_iterator begin() const { return _M_const_ite_cast(_M_container.begin()); }
  const_iterator end() const { return _M_const_ite_cast(_M_container.end()); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rbegin() const 
    { return const_reverse_iterator(end()); }
  const_reverse_iterator rend() const 
    { return const_reverse_iterator(begin()); }

  reference operator[](size_type __n)
    { return cast_traits::ref_cast(_M_container[__n]); }
  const_reference operator[](size_type __n) const 
    { return cast_traits::const_ref_cast(_M_container[__n]); }

  reference at(size_type __n)
    { return cast_traits::ref_cast(_M_container.at(__n)); }
  const_reference at(size_type __n) const
    { return cast_traits::const_ref_cast(_M_container.at(__n)); }

  reference front() { return cast_traits::ref_cast(_M_container.front()); }
  reference back() { return cast_traits::ref_cast(_M_container.back()); }
  const_reference front() const { return cast_traits::const_ref_cast(_M_container.front()); }
  const_reference back() const { return cast_traits::const_ref_cast(_M_container.back()); }

  size_type size() const { return _M_container.size(); }
  size_type max_size() const { return _M_container.max_size(); }
  bool empty() const { return _M_container.empty(); }
  allocator_type get_allocator() const { return allocator_type(); }

public:                         // Constructor, destructor.
  explicit deque(const allocator_type& __a = allocator_type()) 
    : _M_container(__a) {}

  deque(const _Self& __x) : 
    _M_container(__x._M_container) {}

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit deque(size_type __n, value_type __val = 0,
#else
  deque(size_type __n, value_type __val,
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
        const allocator_type& __a = allocator_type()) : 
    _M_container(__n, cast_traits::cast(__val), __a) {}
  // int,long variants may be needed 
#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit deque(size_type __n) : _M_container(__n) {}
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

#ifdef _STLP_MEMBER_TEMPLATES

# ifdef _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
  // VC++ needs this
  template <class _InputIterator>
  deque(_InputIterator __first, _InputIterator __last) : 
    _M_container(__first, __last) {}
# endif

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  deque(_InputIterator __first, _InputIterator __last,
        const allocator_type& __a _STLP_ALLOCATOR_TYPE_DFL) : 
    _M_container(__iterator_wrapper<_Tp, _InputIterator>(__first),
                 __iterator_wrapper<_Tp, _InputIterator>(__last), __a) {}
# else
  deque(const_pointer __first, const_pointer __last,
        const allocator_type& __a = allocator_type() ) 
    : _M_container(cast_traits::const_ptr_cast(__first), cast_traits::const_ptr_cast(__last), __a) {}

  deque(const_iterator __first, const_iterator __last,
        const allocator_type& __a = allocator_type() ) 
    : _M_container(__first, __last, __a) {}
#endif /* _STLP_MEMBER_TEMPLATES */

  deque(__move_source<_Self> src)
    : _M_container(__move_source<_Base>(src.get()._M_container)) {}

  _Self& operator= (const _Self& __x) {
    _M_container = __x._M_container;
    return *this;
  }

  void swap(_Self& __x) {
    _M_container.swap(__x._M_container);
  }

public: 
  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, value_type __val) {
    _M_container.assign(__n, cast_traits::cast(__val));
  }

#ifdef _STLP_MEMBER_TEMPLATES

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    _M_container.assign(__iterator_wrapper<_Tp, _InputIterator>(__first),
                        __iterator_wrapper<_Tp, _InputIterator>(__last));
  }

#endif /* _STLP_MEMBER_TEMPLATES */

public:                         // push_* and pop_*
  
#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_back(value_type __t = 0) {
#else
  void push_back(value_type __t) {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    _M_container.push_back(cast_traits::cast(__t));
  }
#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_front(value_type __t = 0)   {
#else
  void push_front(value_type __t)   {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    _M_container.push_front(cast_traits::cast(__t));
  }

# if defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_back() { _M_container.push_back(0); }
  void push_front() { _M_container.push_front(0); }
# endif /*_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/

  void pop_back() { _M_container.pop_back(); }
  void pop_front() { _M_container.pop_front(); }

public:                         // Insert

#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __position, value_type __x = 0) {
#else
  iterator insert(iterator __position, value_type __x) {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    _M_ite_cast(_M_container.insert(_M_ite_cast(__position), cast_traits::cast(__x)));
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __position)
  { return insert(__position, __STATIC_CAST(value_type, 0)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/

  void insert(iterator __pos, size_type __n, value_type __x) {
    _M_container.insert(_M_ite_cast(__pos), __n, cast_traits::cast(__x));
  }

#ifdef _STLP_MEMBER_TEMPLATES  

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    _M_container.insert(_M_ite_cast(__pos), __iterator_wrapper<_Tp, _InputIterator>(__first),
                                            __iterator_wrapper<_Tp, _InputIterator>(__last));
  }

#else /* _STLP_MEMBER_TEMPLATES */

  void insert(iterator __pos,
              const_pointer __first, const_pointer __last) {
    _M_container.insert(_M_ite_cast(__pos), cast_traits::const_ptr_cast(__first),
                                            cast_traits::const_ptr_cast(__last));
  }
  void insert(iterator __pos,
              const_iterator __first, const_iterator __last) {
    _M_container.insert(_M_ite_cast(__pos), _M_const_ite_cast(__first),
                                            _M_const_ite_cast(__last));
  }

#endif /* _STLP_MEMBER_TEMPLATES */

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size, value_type __x = 0) {
#else
  void resize(size_type __new_size, value_type __x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    _M_container.resize(__new_size, cast_traits::cast(__x));
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type new_size) { resize(new_size, __STATIC_CAST(value_type, 0)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

public:                         // Erase
  iterator erase(iterator __pos) {
    return _M_ite_cast(_M_container.erase(_M_ite_cast(__pos)));
  }

  iterator erase(iterator __first, iterator __last) {
    return _M_ite_cast(_M_container.erase(_M_ite_cast(__first), _M_ite_cast(__last)));
  }
  void clear() { _M_container.clear(); }
};


#endif /* _STLP_SPECIALIZED_DEQUE_H */

// Local Variables:
// mode:C++
// End:

