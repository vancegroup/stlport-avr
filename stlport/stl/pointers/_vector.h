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

#ifndef _STLP_SPECIALIZED_VECTOR_H
#define _STLP_SPECIALIZED_VECTOR_H

#include <stl/pointers/_void_ptr_traits.h>

/*
 * void* specialization to break the potential loop instanciation with pointer specialization
 */
template <class _Alloc>
class vector<void*, _Alloc> : protected _Vector_base<void*, _Alloc> _STLP_STLPORT_CLASS_N
{
private:
  typedef _Vector_base<void*, _Alloc> _Base;
  typedef vector<void*, _Alloc> _Self;
public:
  typedef void* value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;

public:
  typedef value_type& reference;
  typedef value_type const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag _Iterator_category;

  _STLP_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS;
  _STLP_FORCE_ALLOCATORS(void*, _Alloc)
  typedef typename _Vector_base<void*, _Alloc>::allocator_type allocator_type;

  allocator_type get_allocator() const {
    return _STLP_CONVERT_ALLOCATOR((const allocator_type&)this->_M_end_of_storage, void*);
  }
protected:
  typedef __true_type _TrivialAss;
  typedef __true_type _IsPODType;

  void _M_insert_overflow(pointer __position, void* __x,
			                    size_type __fill_len, bool __atend = false) {
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);

    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = (pointer)__copy_trivial(this->_M_start, __position, __new_start);
      // handle insertion
    __new_finish = fill_n(__new_finish, __fill_len, __x);
    if (!__atend)
      // copy remainder
      __new_finish = (pointer)__copy_trivial(__position, this->_M_finish, __new_finish);
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
  }

  void _M_range_check(size_type __n) const {
    if (__n >= size_type(this->_M_finish-this->_M_start))
      this->_M_throw_out_of_range();
  }

public:
  iterator begin()             { return this->_M_start; }
  const_iterator begin() const { return this->_M_start; }
  iterator end()               { return this->_M_finish; }
  const_iterator end() const   { return this->_M_finish; }

  reverse_iterator rbegin()              { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const  { return const_reverse_iterator(end()); }
  reverse_iterator rend()                { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const    { return const_reverse_iterator(begin()); }

  size_type size() const        { return size_type(this->_M_finish - this->_M_start); }
  size_type max_size() const {
    size_type __vector_max_size = size_type(-1) / sizeof(void*);
    typename allocator_type::size_type __alloc_max_size = this->_M_end_of_storage.max_size();
    return (__alloc_max_size < __vector_max_size)?__alloc_max_size:__vector_max_size;
  }

  size_type capacity() const    { return size_type(this->_M_end_of_storage._M_data - this->_M_start); }
  bool empty() const            { return this->_M_start == this->_M_finish; }

  reference operator[](size_type __n) { return *(begin() + __n); }
  const_reference operator[](size_type __n) const { return *(begin() + __n); }

  reference front()             { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back()              { return *(end() - 1); }
  const_reference back() const  { return *(end() - 1); }

  reference at(size_type __n) { _M_range_check(__n); return (*this)[__n]; }
  const_reference at(size_type __n) const { _M_range_check(__n); return (*this)[__n]; }

  explicit vector(const allocator_type& __a = allocator_type()) :
    _Vector_base<void*, _Alloc>(__a) {}

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit vector(size_type __n, void *__val = 0,
#else
  vector(size_type __n, void *__val,
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
         const allocator_type& __a = allocator_type())
    : _Vector_base<void*, _Alloc>(__n, __a) {
    this->_M_finish = uninitialized_fill_n(this->_M_start, __n, __val);
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit vector(size_type __n)
    : _Vector_base<void*, _Alloc>(__n, allocator_type() ) {
    this->_M_finish = uninitialized_fill_n(this->_M_start, __n, __STATIC_CAST(void*, 0));
  }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  vector(const _Self& __x)
    : _Vector_base<void*, _Alloc>(__x.size(), __x.get_allocator()) {
    this->_M_finish = reinterpret_cast<void**>(__ucopy_trivial(__x._M_start, __x._M_finish, this->_M_start));
  }

  /*explicit vector(__full_move_source<_Self> src)
    : _Vector_base<void*, _Alloc>(_FullMoveSource<_Vector_base<void*, _Alloc> >(src.get())) {
  }*/

  explicit vector(__partial_move_source<_Self> src)
    : _Vector_base<void*, _Alloc>(_AsPartialMoveSource<_Vector_base<void*, _Alloc> >(src.get())) {
	  //Set the source destroyable:
	  src.get()._M_start = 0;
	  //This one is usefull for the hashtable Move_Constructor:
	  src.get()._M_finish = 0;
  }

#if defined (_STLP_MEMBER_TEMPLATES)

  template <class _Integer>
  void _M_initialize_aux(_Integer __n, _Integer __val, const __true_type& /*_IsIntegral*/) {
    this->_M_start = this->_M_end_of_storage.allocate(__n);
    this->_M_end_of_storage._M_data = this->_M_start + __n;
    this->_M_finish = uninitialized_fill_n(this->_M_start, __n, __val);
  }

  template <class _InputIterator>
  void _M_initialize_aux(_InputIterator __first, _InputIterator __last,
                         const __false_type&/*_IsIntegral*/) {
    _M_range_initialize(__first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIterator));
  }

  // Check whether it's an integral type.  If so, it's not an iterator.
 # ifdef _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
  template <class _InputIterator>
  vector(_InputIterator __first, _InputIterator __last) :
    _Vector_base<void*, _Alloc>(allocator_type()) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_initialize_aux(__first, __last, _Integral());
  }
 # endif
  template <class _InputIterator>
  vector(_InputIterator __first, _InputIterator __last,
         const allocator_type& __a _STLP_ALLOCATOR_TYPE_DFL ) :
    _Vector_base<void*, _Alloc>(__a) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_initialize_aux(__first, __last, _Integral());
  }

#else
  vector(void *__first, void *__last,
         const allocator_type& __a = allocator_type())
    : _Vector_base<void*, _Alloc>(__last - __first, __a) {
      this->_M_finish = __ucopy_trivial(__first, __last, this->_M_start);
  }
#endif /* _STLP_MEMBER_TEMPLATES */

  ~vector() {}

  _Self& operator=(const _Self& __x);

  void reserve(size_type __n);

  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, void *__val) { _M_fill_assign(__n, __val); }
  void _M_fill_assign(size_type __n, void *__val);

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _ForwardIter>
  void _M_assign_aux(_ForwardIter __first, _ForwardIter __last, const forward_iterator_tag &)
#else
  void assign(const_iterator __first, const_iterator __last)
#endif
  {
    size_type __len = distance(__first, __last);

    if (__len > capacity()) {
      iterator __tmp = _M_allocate_and_copy(__len, __first, __last);
      _M_clear();
      _M_set(__tmp, __tmp + __len, __tmp + __len);
    }
    else if (size() >= __len) {
      this->_M_finish = copy(__first, __last, this->_M_start);
    }
    else {
# if defined ( _STLP_MEMBER_TEMPLATES )
      _ForwardIter __mid = __first;
      advance(__mid, size());
# else
      const_iterator __mid = __first + size() ;
# endif
      copy(__first, __mid, this->_M_start);
      this->_M_finish = __uninitialized_copy(__mid, __last, this->_M_finish, _IsPODType());
    }
  }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _InputIter>
  void _M_assign_aux(_InputIter __first, _InputIter __last,
		                 const input_iterator_tag &) {
    iterator __cur = begin();
    for ( ; __first != __last && __cur != end(); ++__cur, ++__first)
      *__cur = *__first;
    if (__first == __last)
      erase(__cur, end());
    else
      insert(end(), __first, __last);
  }

  template <class _Integer>
  void _M_assign_dispatch(_Integer __n, _Integer __val, const __true_type& /*_IsIntegral*/)
    { assign((size_type) __n, (void*) __val); }

  template <class _InputIter>
  void _M_assign_dispatch(_InputIter __first, _InputIter __last, const __false_type& /*_IsIntegral*/)
    { _M_assign_aux(__first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIter)); }

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_assign_dispatch(__first, __last, _Integral());
  }
#endif /* _STLP_MEMBER_TEMPLATES */

#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_back(void *__x = 0) {
#else
  void push_back(void *__x) {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    if (this->_M_finish != this->_M_end_of_storage._M_data) {
      *this->_M_finish = __x;
      ++this->_M_finish;
    }
    else
      _M_insert_overflow(this->_M_finish, __x, 1UL, true);
  }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __position, void *__x = 0) {
#else
  iterator insert(iterator __position, void *__x) {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    size_type __n = __position - begin();
    if (this->_M_finish != this->_M_end_of_storage._M_data) {
      if (__position == end()) {
        *this->_M_finish = __x;
        ++this->_M_finish;
      } else {
        this->_M_finish = this->_M_finish - 1;
        ++this->_M_finish;
        __copy_backward_ptrs(__position, this->_M_finish - 2, this->_M_finish - 1, _TrivialAss());
        *__position = __x;
      }
    }
    else
      _M_insert_overflow(__position, __x, 1UL);
    return begin() + __n;
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_back() { push_back(__STATIC_CAST(void*, 0)); }
  iterator insert(iterator __position) { return insert(__position, __STATIC_CAST(void*, 0)); }
# endif /*_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/

  void swap(_Self& __x) {
    _STLP_STD::swap(this->_M_start, __x._M_start);
    _STLP_STD::swap(this->_M_finish, __x._M_finish);
    _STLP_STD::swap(this->_M_end_of_storage, __x._M_end_of_storage);
  }

  void _M_fill_insert (iterator __pos, size_type __n, void *__x);

#if defined ( _STLP_MEMBER_TEMPLATES)

  template <class _Integer>
  void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
                          const __true_type& /*_IsIntegral*/) {
    _M_fill_insert(__pos, (size_type) __n, (void*) __val);
  }

  template <class _InputIterator>
  void _M_insert_dispatch(iterator __pos,
                          _InputIterator __first, _InputIterator __last,
                          const __false_type& /*_IsIntegral*/) {
    _M_range_insert(__pos, __first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIterator));
  }

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_insert_dispatch(__pos, __first, __last, _Integral());
  }

  template <class _InputIterator>
  void _M_range_insert(iterator __pos, _InputIterator __first, _InputIterator __last,
                       const input_iterator_tag &) {
    for ( ; __first != __last; ++__first) {
      __pos = insert(__pos, *__first);
      ++__pos;
    }
  }

  template <class _ForwardIterator>
  void _M_range_insert(iterator __position, _ForwardIterator __first, _ForwardIterator __last,
                       const forward_iterator_tag &)
#else /* _STLP_MEMBER_TEMPLATES */
  void insert(iterator __position,
              const_iterator __first, const_iterator __last)
#endif /* _STLP_MEMBER_TEMPLATES */
  {
    if (__first != __last) {
      size_type __n = distance(__first, __last);

      if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
        const size_type __elems_after = this->_M_finish - __position;
        pointer __old_finish = this->_M_finish;
        if (__elems_after > __n) {
          __copy_trivial(this->_M_finish - __n, this->_M_finish, this->_M_finish);
          this->_M_finish += __n;
          __copy_backward_ptrs(__position, __old_finish - __n, __old_finish, _TrivialAss());
          copy(__first, __last, __position);
        }
        else {
# if defined ( _STLP_MEMBER_TEMPLATES )
          _ForwardIterator __mid = __first;
          advance(__mid, __elems_after);
# else
          const_pointer __mid = __first + __elems_after;
# endif
          __uninitialized_copy(__mid, __last, this->_M_finish, _IsPODType());
          this->_M_finish += __n - __elems_after;
          __copy_trivial(__position, __old_finish, this->_M_finish);
          this->_M_finish += __elems_after;
          copy(__first, __mid, __position);
        } /* elems_after */
      }
      else {
        const size_type __old_size = size();
        const size_type __len = __old_size + (max)(__old_size, __n);
        pointer __new_start = this->_M_end_of_storage.allocate(__len);
        pointer __new_finish = __new_start;
        _STLP_TRY {
          __new_finish = reinterpret_cast<pointer>(__ucopy_trivial(this->_M_start, __position, __new_start));
          __new_finish = __uninitialized_copy(__first, __last, __new_finish, _IsPODType());
          __new_finish = reinterpret_cast<pointer>(__ucopy_trivial(__position, this->_M_finish, __new_finish));
        }
        _STLP_UNWIND(this->_M_end_of_storage.deallocate(__new_start,__len));
        _M_clear();
        _M_set(__new_start, __new_finish, __new_start + __len);
      }
    }
  }
  void insert (iterator __pos, size_type __n, void *__x)
  { _M_fill_insert(__pos, __n, __x); }

  void pop_back() {
    --this->_M_finish;
  }
  iterator erase(iterator __position) {
    if (__position + 1 != end())
      __move_ptrs(__position + 1, this->_M_finish, __position, _TrivialAss());
    --this->_M_finish;
    return __position;
  }
  iterator erase(iterator __first, iterator __last) {
    this->_M_finish = __move_ptrs(__last, this->_M_finish, __first, _TrivialAss());
    return __first;
  }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size, void *__x = 0) {
#else
  void resize(size_type __new_size, void *__x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    if (__new_size < size())
      erase(begin() + __new_size, end());
    else
      insert(end(), __new_size - size(), __x);
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size) { resize(__new_size, static_cast<void*>(0)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void clear() {
    erase(begin(), end());
  }

protected:

  void _M_clear() {
    this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
  }

  void _M_set(pointer __s, pointer __f, pointer __e) {
    this->_M_start = __s;
    this->_M_finish = __f;
    this->_M_end_of_storage._M_data = __e;
  }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _ForwardIterator>
  pointer _M_allocate_and_copy(size_type __n, _ForwardIterator __first,
				                       _ForwardIterator __last)
#else /* _STLP_MEMBER_TEMPLATES */
  pointer _M_allocate_and_copy(size_type __n, const_pointer __first,
			                         const_pointer __last)
#endif /* _STLP_MEMBER_TEMPLATES */
  {
    pointer __result = this->_M_end_of_storage.allocate(__n);
    _STLP_TRY {
#if !defined(__MRC__)		//*TY 12/17/2000 - added workaround for MrCpp. it confuses on nested try/catch block
      __uninitialized_copy(__first, __last, __result, _IsPODType());
#else
      uninitialized_copy(__first, __last, __result);
#endif
      return __result;
    }
    _STLP_UNWIND(this->_M_end_of_storage.deallocate(__result, __n));
    _STLP_RET_AFTER_THROW(__result);
  }


#ifdef _STLP_MEMBER_TEMPLATES
  template <class _InputIterator>
  void _M_range_initialize(_InputIterator __first,
                           _InputIterator __last, const input_iterator_tag &) {
    for ( ; __first != __last; ++__first)
      push_back(*__first);
  }
  // This function is only called by the constructor.
  template <class _ForwardIterator>
  void _M_range_initialize(_ForwardIterator __first,
                           _ForwardIterator __last, const forward_iterator_tag &) {
    size_type __n = distance(__first, __last);
    this->_M_start = this->_M_end_of_storage.allocate(__n);
    this->_M_end_of_storage._M_data = this->_M_start + __n;
    this->_M_finish = __uninitialized_copy(__first, __last, this->_M_start, _IsPODType());
  }

#endif /* _STLP_MEMBER_TEMPLATES */
};

# if !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/pointers/_vector.c>
# endif


template <class _Tp, class _Alloc>
class vector<_Tp*, _Alloc> _STLP_STLPORT_CLASS_1
{
  //Member datas as a void* vector:
  typedef typename _Alloc_traits<void*, _Alloc>::allocator_type _VoidAlloc;
  typedef vector<void*, _VoidAlloc> _Base;
  _Base _M_container;

  typedef __void_ptr_traits<_Tp> cast_traits;

  typedef vector<_Tp*, _Alloc> _Self;
public:
  typedef _Tp* value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;

public:
  typedef value_type& reference;
  typedef value_type const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag _Iterator_category;

  _STLP_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS;
  _STLP_FORCE_ALLOCATORS(value_type, _Alloc)
  typedef typename _Vector_base<value_type, _Alloc>::allocator_type allocator_type;

  /*
  allocator_type get_allocator() const {
    return _STLP_CONVERT_ALLOCATOR((const allocator_type&)this->_M_end_of_storage, value_type);
  }
  */
public:
  iterator begin()             { return cast_traits::ite_cast(_M_container.begin()); }
  const_iterator begin() const { return cast_traits::const_ite_cast(_M_container.begin()); }
  iterator end()               { return cast_traits::ite_cast(_M_container.end()); }
  const_iterator end() const   { return cast_traits::const_ite_cast(_M_container.end()); }

  reverse_iterator rbegin()              { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const  { return const_reverse_iterator(end()); }
  reverse_iterator rend()                { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const    { return const_reverse_iterator(begin()); }

  size_type size() const        { return _M_container.size(); }
  size_type max_size() const    { return _M_container.max_size(); }

  size_type capacity() const    { return _M_container.capacity(); }
  bool empty() const            { return _M_container.empty(); }

  reference operator[](size_type __n) { return cast_traits::ref_cast(_M_container[__n]); }
  const_reference operator[](size_type __n) const { return cast_traits::cast(_M_container[__n]); }

  reference front()             { return cast_traits::ref_cast(_M_container.front()); }
  const_reference front() const { return cast_traits::cast(_M_container.front()); }
  reference back()              { return cast_traits::ref_cast(_M_container.back()); }
  const_reference back() const  { return cast_traits::cast(_M_container.back()); }

  reference at(size_type __n) { return cast_traits::ref_cast(_M_container.at(__n)); }
  const_reference at(size_type __n) const { return cast_traits::cast(_M_container.at(__n)); }

  explicit vector(const allocator_type& __a = allocator_type()) :
  _M_container(__a) {}

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit vector(size_type __n, value_type __val = 0,
#else
  vector(size_type __n, value_type __val,
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
         const allocator_type& __a = allocator_type()) 
    : _M_container(__n, cast_traits::cast(__val), __a) {}

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit vector(size_type __n)
    : _M_container(__n, allocator_type() ) {}
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  vector(const _Self& __x) 
    : _M_container(__x._M_container) {}

  /*explicit vector(__full_move_source<_Self> src)
    : _Vector_base<value_type, _Alloc>(_FullMoveSource<_Vector_base<value_type, _Alloc> >(src.get())) {
  }*/
  
  explicit vector(__partial_move_source<_Self> src)
    : _M_container(__partial_move_source<_Base>(src.get()._M_container)) {}
  
#if defined (_STLP_MEMBER_TEMPLATES)

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  vector(_InputIterator __first, _InputIterator __last,
         const allocator_type& __a _STLP_ALLOCATOR_TYPE_DFL ) :
  _M_container(__iterator_wrapper<_Tp, _InputIterator>(__first), __iterator_wrapper<_Tp, _InputIterator>(__last), __a) {}

 # ifdef _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
  template <class _InputIterator>
  vector(_InputIterator __first, _InputIterator __last) :
  _M_container(__iterator_wrapper<_Tp, _InputIterator>(__first), __iterator_wrapper<_Tp, _InputIterator>(__last)) {}
 # endif

#else
  vector(const value_type* __first, const value_type* __last,
         const allocator_type& __a = allocator_type())
    : _M_container(__first, __last, __a) {}
#endif /* _STLP_MEMBER_TEMPLATES */

  _Self& operator=(const _Self& __x) {
    _M_container = __x._M_container;
    return *this;
  }

  void reserve(size_type __n) {_M_container.reserve(__n);}
  void assign(size_type __n, value_type __val) { _M_container.assign(__n, cast_traits::cast(__val)); }
  
#ifdef _STLP_MEMBER_TEMPLATES
  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    _M_container.assign(__iterator_wrapper<_Tp, _InputIterator>(__first), __iterator_wrapper<_Tp, _InputIterator>(__last));
  }
#else
  void assign(const_iterator __first, const_iterator __last) {_M_container.assign(__first, __last);}
#endif /* _STLP_MEMBER_TEMPLATES */

#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_back(value_type __x = 0) {
#else
  void push_back(value_type __x) {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    _M_container.push_back(cast_traits::cast(__x));
  }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __pos, value_type __x = 0) {
#else
  iterator insert(iterator __pos, value_type __x) {
#endif /*!_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/
    return cast_traits::ite_cast(_M_container.insert(cast_traits::ite_cast(__pos), cast_traits::cast(__x)));
 }

#if defined(_STLP_DONT_SUP_DFLT_PARAM) && !defined(_STLP_NO_ANACHRONISMS)
  void push_back() { push_back(static_cast<value_type>(0)); }
  iterator insert(iterator __position) { return insert(__position, static_cast<value_type>(0)); }
# endif /*_STLP_DONT_SUP_DFLT_PARAM && !_STLP_NO_ANACHRONISMS*/

  void swap(_Self& __x) {_M_container.swap(__x._M_container);}

#if defined ( _STLP_MEMBER_TEMPLATES)
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    _M_container.insert(cast_traits::ite_cast(__pos),
                        __iterator_wrapper<_Tp, _InputIterator>(__first), __iterator_wrapper<_Tp, _InputIterator>(__last));
  }
#else /* _STLP_MEMBER_TEMPLATES */
  void insert(iterator __pos, const_iterator __first, const_iterator __last) {
    _M_container.insert(cast_traits::ite_cast(__pos), __first, __last);
  }
#endif /* _STLP_MEMBER_TEMPLATES */

  void insert (iterator __pos, size_type __n, value_type __x) {
    _M_container.insert(cast_traits::ite_cast(__pos), __n, cast_traits::cast(__x));
  }
  
  void pop_back() {_M_container.pop_back();}
  iterator erase(iterator __pos) {return cast_traits::ite_cast(_M_container.erase(cast_traits::ite_cast(__pos)));}
  iterator erase(iterator __first, iterator __last) {
    return cast_traits::ite_cast(_M_container.erase(cast_traits::ite_cast(__first), 
                                                    cast_traits::ite_cast(__last)));
  }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size, value_type __x = 0) {
#else
  void resize(size_type __new_size, value_type __x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    _M_container.resize(__new_size, cast_traits::cast(__x));
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size) { resize(__new_size, static_cast<value_type>(0)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void clear() { _M_container.clear();}
};


#endif /* _STLP_SPECIALIZED_VECTOR_H */
