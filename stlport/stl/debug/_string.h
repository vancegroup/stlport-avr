/*
 * Copyright (c) 1997-1999
 * Silicon Graphics Computer Systems, Inc.
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

#ifndef _STLP_DBG_STRING_H
#define _STLP_DBG_STRING_H

#include <stl/debug/_iterator.h>

# define _STLP_DBG_STRING_BASE _Nondebug_string <_CharT, _Traits, _Alloc>

_STLP_BEGIN_NAMESPACE

# ifdef _STLP_DEBUG_USE_DISTINCT_VALUE_TYPE_HELPERS
template <class _CharT,class _Traits, class _Alloc>
inline _CharT*
value_type(const  _DBG_iter_base< _STLP_DBG_STRING_BASE >&) {
  return (_CharT*)0;
}
template <class _CharT, class _Traits, class _Alloc>
inline random_access_iterator_tag
iterator_category(const  _DBG_iter_base< _STLP_DBG_STRING_BASE >&) {
  return random_access_iterator_tag();
}
# endif

template <class _CharT, class _Traits, class _Alloc> 
class basic_string : private _STLP_RANGE_CHECKER(_CharT, typename _STLP_DBG_STRING_BASE::const_iterator),
                     public _STLP_DBG_STRING_BASE {
private:
  typedef _STLP_DBG_STRING_BASE _Base;
  typedef basic_string<_CharT, _Traits, _Alloc> _Self;
  typedef _STLP_RANGE_CHECKER(_CharT, typename _STLP_DBG_STRING_BASE::const_iterator) _CheckRange;

public:
  __IMPORT_CONTAINER_TYPEDEFS(_Base)
  typedef _DBG_iter<_Base, _Nonconst_traits<value_type> > iterator;
  typedef _DBG_iter<_Base, _Const_traits<value_type> > const_iterator;
  _STLP_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS;

# ifdef _STLP_USE_NATIVE_STRING
  // this typedef is being used for conversions
  typedef _STLP_VENDOR_STD::basic_string<_CharT,_Traits, 
    _STLP_VENDOR_STD::allocator<_CharT> >  __std_string;
# endif
public:                         // Constructor, destructor, assignment.
  typedef typename _Base::_Reserve_t _Reserve_t;

  const _Base* _Get_base() const { return (const _Base*)this; }
  _Base* _Get_base() { return (_Base*)this; }

protected:
  mutable __owned_list _M_iter_list;
  void _Invalidate_all() {
    _M_iter_list._Invalidate_all();
  }
  void _Compare_Capacity (size_type __old_capacity) {
    if (this->capacity() > __old_capacity) {
      _Invalidate_all();
    }
  }
  void _Invalidate_iterator(const iterator& __it) {
    __invalidate_iterator(&_M_iter_list, __it); 
  }
  void _Invalidate_iterators(const iterator& __first, const iterator& __last) {
    __invalidate_range(&_M_iter_list, __first, __last);
  }

public:
  basic_string() :_STLP_DBG_STRING_BASE(), _M_iter_list(_Get_base()) {}
  
  explicit basic_string(const allocator_type& __a): 
    _STLP_DBG_STRING_BASE(__a), _M_iter_list(_Get_base()) {}

  basic_string(_Reserve_t __r, size_t __n,
               const allocator_type& __a = allocator_type())
    : _STLP_DBG_STRING_BASE(__r, __n, __a), _M_iter_list(_Get_base()) {}

  basic_string(const _Self& __s): 
    _CheckRange(__s), _STLP_DBG_STRING_BASE(__s), _M_iter_list(_Get_base()) {}

  basic_string(const _Self& __s, size_type __pos, size_type __n = _Base::npos,
               const allocator_type& __a = allocator_type()):
    _STLP_DBG_STRING_BASE(__s, __pos, __n, __a), _M_iter_list(_Get_base()) {}

  basic_string(const _CharT* __s, size_type __n,
               const allocator_type& __a = allocator_type()):
    _STLP_DBG_STRING_BASE(__s, __n, __a), _M_iter_list(_Get_base()) {}

  basic_string(const _CharT* __s,
               const allocator_type& __a = allocator_type()):
    _STLP_DBG_STRING_BASE(__s, __a), _M_iter_list(_Get_base()) {}

  basic_string(size_type __n, _CharT __c,
               const allocator_type& __a = allocator_type()):
    _STLP_DBG_STRING_BASE(__n, __c, __a), _M_iter_list(_Get_base()) {}

  basic_string(__move_source<_Self> src):
    _STLP_DBG_STRING_BASE(_AsMoveSource<_Base >(src.get())), _M_iter_list(_Get_base()) {
    src.get()._Invalidate_all();
  }

#if defined (_STLP_MEMBER_TEMPLATES) && !(defined(__MRC__)||defined(__SC__))
  template <class _InputIterator>
  basic_string(_InputIterator __f, _InputIterator __l,
               const allocator_type & __a _STLP_ALLOCATOR_TYPE_DFL)
    : _CheckRange(__f, __l), 
      _STLP_DBG_STRING_BASE(__f, __l, __a), _M_iter_list(_Get_base()) {
  }
# ifdef _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
  template <class _InputIterator>
  basic_string(_InputIterator __f, _InputIterator __l)
    : _CheckRange(__f, __l), 
      _STLP_DBG_STRING_BASE(__f, __l), _M_iter_list(_Get_base()) {
  }
#  endif
#else /* _STLP_MEMBER_TEMPLATES */
  basic_string(const _CharT* __f, const _CharT* __l,
               const allocator_type& __a = allocator_type())
    : _CheckRange(__f, __l, __true_type()),
      _STLP_DBG_STRING_BASE(__f, __l, __a), _M_iter_list(_Get_base()) {
  }
  basic_string(const_iterator __f, const_iterator __l, 
               const allocator_type & __a = allocator_type())
    : _CheckRange(__f._M_iterator, __l._M_iterator, __false_type()),
      _STLP_DBG_STRING_BASE(__f._M_iterator, __l._M_iterator, __a), _M_iter_list(_Get_base()) {
  }

#endif

# ifdef _STLP_USE_NATIVE_STRING
  // these conversion operations still needed for
  // strstream, etc.
  basic_string (const __std_string& __x)
    : _STLP_DBG_STRING_BASE(__x.begin(), __x.end()), _M_iter_list(_Get_base()) {}
  operator __std_string() const { return __std_string(this->data()); }
# endif

  // constructor from non-debug version
  basic_string (const _Base& __x)
    : _STLP_DBG_STRING_BASE(__x), _M_iter_list(_Get_base()) {}

  _Self& operator=(const _Self& __s) {
    if (this != &__s) {
      _Invalidate_all();
      _Base::operator=((const _Base&)__s);
    }
    return *this;
  }

  _Self& operator=(const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    _Invalidate_all();
    _Base::operator=(__s);
    return *this;
  }

  _Self& operator=(_CharT __c) {
    _Invalidate_all();
    _Base::operator=(__c);
    return *this;
  }

public:                         // Iterators.

  iterator begin() { return iterator(&_M_iter_list, this->_M_Start()); }
  const_iterator begin() const { return const_iterator(&_M_iter_list,this->_M_Start()); }
  iterator end() { return iterator(&_M_iter_list,this->_M_Finish()); }
  const_iterator end() const { return const_iterator(&_M_iter_list,this->_M_Finish()); }
  void _M_deallocate_block() {
    _Invalidate_all();
    _Base::_M_deallocate_block();
  }

  reverse_iterator rbegin()             
    { return reverse_iterator(iterator(&_M_iter_list,this->_M_Finish())); }
  reverse_iterator rend()               
    { return reverse_iterator(iterator(&_M_iter_list,this->_M_Start())); }
  const_reverse_iterator rbegin() const 
    { return const_reverse_iterator(const_iterator(&_M_iter_list,this->_M_Finish())); }
  const_reverse_iterator rend()   const 
    { return const_reverse_iterator(const_iterator(&_M_iter_list,this->_M_Start())); }

public:                         // Size, capacity, etc.

  void resize(size_type __n, _CharT __c) {
    if (__n > this->capacity())
      _Invalidate_all();
    else if ( __n < this->size() )
      _Invalidate_iterators(this->begin() + __n, this->end());
    _Base::resize(__n, __c);
  }
  void resize(size_type __n) { resize(__n, this->_M_null()); }

  void reserve(size_type __s= 0) {
    if (__s > this->capacity()) _Invalidate_all();
    _Base::reserve(__s);
  }

  void clear() {
    _Invalidate_all();
    _Base::clear();
  } 

public:                         // Element access.

  const_reference operator[](size_type __n) const {
    _STLP_VERBOSE_ASSERT(__n < this->size(), _StlMsg_OUT_OF_BOUNDS)
    return *(begin() + __n); 
  }
  reference operator[](size_type __n) {
    _STLP_VERBOSE_ASSERT(__n < this->size(), _StlMsg_OUT_OF_BOUNDS)
    return *(begin() + __n); 
  }

  const_reference at(size_type __n) const {
    if (__n >= this->size())
      this->_M_throw_out_of_range();
    return *(begin() + __n);
  }

  reference at(size_type __n) {
    if (__n >= this->size())
      this->_M_throw_out_of_range();
    return *(begin() + __n);
  }

public:                         // Append, operator+=, push_back.

  _Self& operator+=(const _Self& __s) { return append(__s); }
  _Self& operator+=(const _CharT* __s) { _STLP_FIX_LITERAL_BUG(__s) return append(__s); }
  _Self& operator+=(_CharT __c) { push_back(__c); return *this; }

  _Self& append(const _Self& __s) { return append(__s._M_Start(), __s._M_Finish()); }

  _Self& append(const _Self& __s,
                       size_type __pos, size_type __n) {
    size_type __old_capacity = this->capacity();
    _Base::append(__s, __pos, __n);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& append(const _CharT* __s, size_type __n) {
    _STLP_FIX_LITERAL_BUG(__s)
    return append(__s, __s+__n);
  }

  _Self& append(const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    return append(__s, __s + _Traits::length(__s)); 
  }

  _Self& append(size_type __n, _CharT __c) {
    size_type __old_capacity = this->capacity();
    _Base::append(__n, __c);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

#ifdef _STLP_MEMBER_TEMPLATES

  // Check to see if _InputIterator is an integer type.  If so, then
  // it can't be an iterator.
  template <class _InputIter>
  _Self& append(_InputIter __first, _InputIter __last) {
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    size_type __old_capacity = this->capacity();
    _Base::append(__first, __last);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

#ifdef _STLP_MSVC
// specialization for append
 template <>
 inline _Self& append(iterator __f, iterator __l) {
   _STLP_FIX_LITERAL_BUG(__f) _STLP_FIX_LITERAL_BUG(__l)
   _STLP_DEBUG_CHECK(__check_range(__f, __l))
    size_type __old_capacity = this->capacity();
   _Base::append(__f._M_iterator, __l._M_iterator);
    _Compare_Capacity(__old_capacity);
   return *this;
 }
#endif

#else /* _STLP_MEMBER_TEMPLATES */

  _Self& append(const _CharT* __first, const _CharT* __last) {
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    size_type __old_capacity = this->capacity();
    _Base::append(__first, __last);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& append(const_iterator __first, const_iterator __last) {
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    size_type __old_capacity = this->capacity();
    _Base::append(__first._M_iterator, __last._M_iterator);
    _Compare_Capacity(__old_capacity);
    return *this;
  }
#endif /* _STLP_MEMBER_TEMPLATES */

  void push_back(_CharT __c) {
    size_type __old_capacity = this->capacity();
    _Base::push_back(__c);
    _Compare_Capacity(__old_capacity);
  }

  void pop_back() {
    _Invalidate_iterator(this->end());
    _Base::pop_back();
  }

public:                         // Assign
  
  _Self& assign(const _Self& __s) {
    _Invalidate_all();
    _Base::assign(__s); 
    return *this; 
  }

  _Self& assign(const _Self& __s, 
                       size_type __pos, size_type __n) {
    if (__n != 0) _Invalidate_all();
    _Base::assign(__s, __pos, __n);
    return *this;
  }

  _Self& assign(const _CharT* __s, size_type __n) {
    _STLP_FIX_LITERAL_BUG(__s)
    return assign(__s, __s + __n);
  }

  _Self& assign(const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    return assign(__s, __s + _Traits::length(__s));
  }

  _Self& assign(size_type __n, _CharT __c) {
    _Invalidate_all();
    _Base::assign(__n, __c);
    return *this;    
  }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _InputIter>
  inline _Self& assign(_InputIter __first, _InputIter __last) {
    _STLP_FIX_LITERAL_BUG(__first) _STLP_FIX_LITERAL_BUG(__last)
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    _Base::assign(__first, __last);
    return *this;    
  }

#ifdef _STLP_MSVC
// partial specialization for assign
template <>
inline _Self& assign(iterator __f, iterator __l) {
  _STLP_FIX_LITERAL_BUG(__f) _STLP_FIX_LITERAL_BUG(__l)
  _STLP_DEBUG_CHECK(__check_range(__f, __l))
  _Base::assign(__f._M_iterator, __l._M_iterator);
  return *this;
  }
#endif

#else
  _Self& assign(const _CharT* __f, const _CharT* __l) {
    _STLP_FIX_LITERAL_BUG(__f) _STLP_FIX_LITERAL_BUG(__l)
    _STLP_DEBUG_CHECK(__check_range(__f, __l))
    _Base::assign(__f, __l);
    return *this;
  }
  _Self& assign(const_iterator __f, const_iterator __l) {
    _STLP_DEBUG_CHECK(__check_range(__f, __l))
    _Base::assign(__f._M_iterator, __l._M_iterator);
    return *this;
  }
#endif  /* _STLP_MEMBER_TEMPLATES */
    
public:                         // Insert

  _Self& insert(size_type __pos, const _Self& __s) {
    size_type __old_capacity = this->capacity();
    _Base::insert(__pos, __s);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& insert(size_type __pos, const _Self& __s,
                       size_type __beg, size_type __n) {
    size_type __old_capacity = this->capacity();
    _Base::insert(__pos, __s, __beg, __n);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& insert(size_type __pos, const _CharT* __s, size_type __n) {
    _STLP_FIX_LITERAL_BUG(__s)
    size_type __old_capacity = this->capacity();
    _Base::insert(__pos, __s, __n);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& insert(size_type __pos, const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    return insert(__pos, __s, _Traits::length(__s));
  }
    
  _Self& insert(size_type __pos, size_type __n, _CharT __c) {
    size_type __old_capacity = this->capacity();
    _Base::insert(__pos, __n, __c);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  iterator insert(iterator __p, _CharT __c) {
    _STLP_FIX_LITERAL_BUG(__p)
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__p))
    size_type __old_capacity = this->capacity();
    typename _Base::iterator __ret = _Base::insert(__p._M_iterator, __c);
    _Compare_Capacity(__old_capacity);
    return iterator(&_M_iter_list, __ret);
  }

  void insert(iterator __p, size_t __n, _CharT __c) {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__p))
    size_type __old_capacity = this->capacity();
    _Base::insert(__p._M_iterator, __n, __c);
    _Compare_Capacity(__old_capacity);
  }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _InputIter>
  void insert(iterator __p, _InputIter __first, _InputIter __last) {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__p))
    _STLP_DEBUG_CHECK(__check_range(__first,__last))
    size_type __old_capacity = this->capacity();
    typedef typename _Is_integer<_InputIter>::_Integral _Integral;
    _M_insert_dispatch(__p,__first,__last,_Integral());
    _Compare_Capacity(__old_capacity);
  }
#endif /* _STLP_MEMBER_TEMPLATES */

  void insert(iterator __p, const_iterator __first, const_iterator __last) {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__p))
    _STLP_DEBUG_CHECK(__check_range(__first,__last))
    size_type __old_capacity = this->capacity();
    _Base::insert(__p._M_iterator, __first._M_iterator, __last._M_iterator); 
    _Compare_Capacity(__old_capacity);
  }

#ifdef _STLP_MEMBER_TEMPLATES
private:
  template <class _Integer>
  void _M_insert_dispatch(iterator __p, _Integer __n, _Integer __x,
                          const __true_type& /*Integral*/) {
    _Base::insert(__p, (size_type) __n, (_CharT) __x);
  }

  template <class _InputIter>
  void _M_insert_dispatch(iterator __p, _InputIter __first, _InputIter __last,
                          const __false_type& /*Integral*/) {
    typedef typename _AreSameTypes<_InputIter, iterator>::_Ret _AreSame;
    _M_insert_aux(__p, __first, __last, _AreSame());
  }

  void _M_insert_aux (iterator __p, const_iterator __first, const_iterator __last,
                      const __true_type&) {
    _Base::insert(__p._M_iterator, __first._M_iterator, __last._M_iterator);
  }

  template<class _InputIter>
  void _M_insert_aux (iterator __p, _InputIter __first, _InputIter __last,
                      const __false_type&) {
    _Base::insert(__p._M_iterator, __first, __last);
  }
#endif /* _STLP_MEMBER_TEMPLATES */

public:                         // Erase.
  _Self& erase(size_type __pos = 0, size_type __n = _Base::npos) {
    if (__pos < this->size()) {
      _Invalidate_iterators(begin() + __pos, end());
    }
    _Base::erase(__pos, __n);
    return *this;
  }
  iterator erase(iterator __position) {
    _STLP_DEBUG_CHECK(_Dereferenceable(__position))
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__position))
    _Invalidate_iterators(__position, end());
    return iterator(&_M_iter_list, _Base::erase(__position._M_iterator));
  }
  iterator erase(iterator __first, iterator __last) {
    _STLP_DEBUG_CHECK(__check_range(__first, __last, this->begin(), this->end()))
    _Invalidate_iterators(__first, end());
    return iterator(&_M_iter_list, _Base::erase(__first._M_iterator, __last._M_iterator));   
  }

public:                         // Substring.
  _Self substr(size_type __pos = 0, size_type __n = _Base::npos) const {
    if (__pos > this->size())
      this->_M_throw_out_of_range();
    return _Self(this->begin() + __pos, 
                 this->begin() + __pos + (min)(__n, this->size() - __pos),
                 allocator_type());
  }

public:                         // Replace.  (Conceptually equivalent
                                // to erase followed by insert.)
  _Self& replace(size_type __pos, size_type __n, 
                        const _Self& __s) {
    size_type __old_capacity = this->capacity();
    _Base::replace(__pos, __n, __s);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& replace(size_type __pos1, size_type __n1,
                        const _Self& __s,
                        size_type __pos2, size_type __n2) {
    size_type __old_capacity = this->capacity();
    _Base::replace(__pos1, __n1, (const _Base&)__s, __pos2, __n2);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& replace(size_type __pos, size_type __n1,
                        const _CharT* __s, size_type __n2) {    
    _STLP_FIX_LITERAL_BUG(__s)
    size_type __old_capacity = this->capacity();
    _Base::replace(__pos, __n1, __s, __n2);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& replace(size_type __pos, size_type __n1,
                        const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    size_type __old_capacity = this->capacity();
    _Base::replace(__pos, __n1, __s);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& replace(size_type __pos, size_type __n1,
                        size_type __n2, _CharT __c) {
    size_type __old_capacity = this->capacity();
    _Base::replace(__pos, __n1, __n2, __c);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& replace(iterator __first, iterator __last, 
                        const _Self& __s) { 
    _STLP_DEBUG_CHECK(__check_range(__first, __last, this->begin(), this->end()))
    size_type __old_capacity = this->capacity();
    _Base::replace(__first._M_iterator, __last._M_iterator,__s);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& replace(iterator __first, iterator __last,
                        const _CharT* __s, size_type __n) { 
    _STLP_FIX_LITERAL_BUG(__s)
    _STLP_DEBUG_CHECK(__check_range(__first, __last, this->begin(), this->end()))
    size_type __old_capacity = this->capacity();
    _Base::replace(__first._M_iterator, __last._M_iterator,__s, __n);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& replace(iterator __first, iterator __last,
                        const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    _STLP_DEBUG_CHECK(__check_range(__first, __last, this->begin(), this->end()))
    size_type __old_capacity = this->capacity();
    _Base::replace(__first._M_iterator, __last._M_iterator,__s);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

  _Self& replace(iterator __first, iterator __last, 
		 		  size_type __n, _CharT __c) {
    _STLP_DEBUG_CHECK(__check_range(__first, __last, this->begin(), this->end()))
    size_type __old_capacity = this->capacity();
    _Base::replace(__first._M_iterator, __last._M_iterator, __n, __c);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _InputIter>
  _Self& replace(iterator __first, iterator __last,
                 _InputIter __f, _InputIter __l) {
    _STLP_DEBUG_CHECK(__check_range(__first, __last, this->begin(), this->end()))
    _STLP_DEBUG_CHECK(__check_range(__f, __l))
    size_type __old_capacity = this->capacity();
    typedef typename _Is_integer<_InputIter>::_Integral _Integral;
    _M_replace_dispatch(__first, __last, __f, __l,  _Integral());
    _Compare_Capacity(__old_capacity);
    return *this;
  }
#endif /* _STLP_MEMBER_TEMPLATES */
 
  _Self& replace(iterator __first, iterator __last,
                 const_iterator __f, const_iterator __l) {
    _STLP_DEBUG_CHECK(__check_range(__first, __last, this->begin(), this->end()))
    _STLP_DEBUG_CHECK(__check_range(__f, __l))
    size_type __old_capacity = this->capacity();
    _Base::replace(__first._M_iterator, __last._M_iterator, 
		 		    __f._M_iterator, __l._M_iterator);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

#ifdef _STLP_MEMBER_TEMPLATES
private:
  template <class _Integer>
  void _M_replace_dispatch(iterator __first, iterator __last,
                           _Integer __n, _Integer __x, const __true_type& /*IsIntegral*/) {
    _Base::replace(__first, __last, (size_type) __n, (_CharT) __x);
  }

  template <class _InputIter> 
  void _M_replace_dispatch(iterator __first, iterator __last,
                           _InputIter __f, _InputIter __l, const __false_type& /*IsIntegral*/) {
    typedef typename _AreSameTypes<_InputIter, iterator>::_Ret _AreSame;
    _M_replace_aux(__first, __last, __f, __l, _AreSame());
  }
  
  void _M_replace_aux(iterator __first, iterator __last,
                      const_iterator __f, const_iterator __l, __true_type const&) {
    _Base::replace(__first._M_iterator, __last._M_iterator, 
                   __f._M_iterator, __l._M_iterator);
  }
  
  template <class _InputIter>
  void _M_replace_aux(iterator __first, iterator __last,
                      _InputIter __f, _InputIter __l, __false_type const&) {
    _Base::replace( __first._M_iterator, __last._M_iterator, __f, __l );
  }
#endif /* _STLP_MEMBER_TEMPLATES */

public:                         // Other modifier member functions.

  void swap(_Self& __s) {
    _M_iter_list._Swap_owners(__s._M_iter_list);
    _Base::swap(__s);
  }
};


// This is a hook to instantiate STLport exports in a designated DLL
# if defined (_STLP_USE_TEMPLATE_EXPORT)
#  ifndef _STLP_MEMBER_TEMPLATES
_STLP_EXPORT_TEMPLATE_CLASS __range_checker <char, basic_string<char, char_traits<char>, allocator<char> >::const_iterator>;
#  endif
_STLP_EXPORT_TEMPLATE_CLASS basic_string<char, char_traits<char>, allocator<char> >;
#  if defined (_STLP_HAS_WCHAR_T)
#  ifndef _STLP_MEMBER_TEMPLATES
_STLP_EXPORT_TEMPLATE_CLASS __range_checker <wchar_t, basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >::const_iterator>;
#  endif
_STLP_EXPORT_TEMPLATE_CLASS basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
#  endif
# endif /* _STLP_USE_TEMPLATE_EXPORT */


// ------------------------------------------------------------
// Non-member functions.

template <class _CharT, class _Traits, class _Alloc>
inline basic_string<_CharT,_Traits,_Alloc> _STLP_CALL
operator+(const basic_string<_CharT,_Traits,_Alloc>& __s,
          const basic_string<_CharT,_Traits,_Alloc>& __y)
{
  return basic_string<_CharT,_Traits,_Alloc>(*__s._Get_base() + *__y._Get_base());
}

template <class _CharT, class _Traits, class _Alloc>
inline basic_string<_CharT,_Traits,_Alloc> _STLP_CALL
operator+(const _CharT* __s,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  return basic_string<_CharT,_Traits,_Alloc>(__s + *__y._Get_base());
}

template <class _CharT, class _Traits, class _Alloc>
inline basic_string<_CharT,_Traits,_Alloc> _STLP_CALL
operator+(_CharT __c,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return basic_string<_CharT,_Traits,_Alloc>(__c + *__y._Get_base());
}

template <class _CharT, class _Traits, class _Alloc>
inline basic_string<_CharT,_Traits,_Alloc> _STLP_CALL
operator+(const basic_string<_CharT,_Traits,_Alloc>& __x,
          const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  return basic_string<_CharT,_Traits,_Alloc>(*__x._Get_base()+ __s);
}

template <class _CharT, class _Traits, class _Alloc>
inline basic_string<_CharT,_Traits,_Alloc> _STLP_CALL
operator+(const basic_string<_CharT,_Traits,_Alloc>& __x,
          const _CharT __c) {
  return basic_string<_CharT,_Traits,_Alloc>(*__x._Get_base() + __c);
}

#ifdef _STLP_EXTRA_OPERATORS_FOR_DEBUG

// Operator== and operator!=

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator==(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return (*__x._Get_base() == *__y._Get_base());
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator==(const _CharT* __s,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  return (__s == *__y._Get_base());
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator==(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  return (*__x._Get_base() == __s);
}

// Operator< (and also >, <=, and >=).

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator<(const basic_string<_CharT,_Traits,_Alloc>& __x,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return (*__x._Get_base() < *__y._Get_base());
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator<(const _CharT* __s,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  return (__s < *__y._Get_base());    
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator<(const basic_string<_CharT,_Traits,_Alloc>& __x,
          const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  return (*__x._Get_base() < __s);
}

#ifdef _STLP_USE_SEPARATE_RELOPS_NAMESPACE

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator!=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return !(__x == __y);
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator>(const basic_string<_CharT,_Traits,_Alloc>& __x,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return __y < __x;
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator<=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return !(__y < __x);
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator>=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return !(__x < __y);
}

#endif /* _STLP_USE_SEPARATE_RELOPS_NAMESPACE */

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator!=(const _CharT* __s,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  return !(__s == __y);
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator!=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  return !(__x == __s);
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator>(const _CharT* __s,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  return __y < __s;
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator>(const basic_string<_CharT,_Traits,_Alloc>& __x,
          const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  return __s < __x;
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator<=(const _CharT* __s,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  return !(__y < __s);
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator<=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  return !(__s < __x);
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator>=(const _CharT* __s,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  return !(__s < __y);
}

template <class _CharT, class _Traits, class _Alloc>
inline bool _STLP_CALL
operator>=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  return !(__x < __s);
}
#endif /*  if 0 */

// Swap.
#ifdef _STLP_FUNCTION_TMPL_PARTIAL_ORDER
template <class _CharT, class _Traits, class _Alloc>
inline void swap(basic_string<_CharT,_Traits,_Alloc>& __x,
                 basic_string<_CharT,_Traits,_Alloc>& __y) {
  __x.swap(__y);
}
#endif /* _STLP_FUNCTION_TMPL_PARTIAL_ORDER */

#ifdef _STLP_CLASS_PARTIAL_SPECIALIZATION
template <class _CharT, class _Traits, class _Alloc>
struct __move_traits<basic_string<_CharT,_Traits,_Alloc> > :
  __move_traits_help<_STLP_DBG_STRING_BASE >
{};

template <class _CharT, class _Traits, class _Alloc>
struct __action_on_move<basic_string<_CharT,_Traits,_Alloc> > {
  typedef __true_type swap;
};
#endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */

// I/O.  

#ifdef _STLP_EXTRA_OPERATORS_FOR_DEBUG
#if defined (_STLP_USE_NEW_IOSTREAMS) && ! defined (_STLP_OWN_IOSTREAMS)

template <class _CharT, class _Traits, class _Alloc>
basic_ostream<_CharT, _Traits>& _STLP_CALL
operator<<(basic_ostream<_CharT, _Traits>& __os, 
           const basic_string<_CharT,_Traits,_Alloc>& __s) {
  return __os << *__s._Get_base();
}

template <class _CharT, class _Traits, class _Alloc>
basic_istream<_CharT, _Traits>&  _STLP_CALL
operator>>(basic_istream<_CharT, _Traits>& __is,
           basic_string<_CharT,_Traits,_Alloc>& __s) {
    return __is >> *__s._Get_base();
}

#elif ! defined ( _STLP_USE_NO_IOSTREAMS )

template <class _CharT, class _Traits, class _Alloc>
ostream& _STLP_CALL operator<<(ostream& __os, 
                    const basic_string<_CharT,_Traits,_Alloc>& __s) {
  return __os << *__s._Get_base();
}

template <class _CharT, class _Traits, class _Alloc>
istream& _STLP_CALL operator>>(istream& __is, basic_string<_CharT,_Traits,_Alloc>& __s) {
    return __is >> *__s._Get_base();
}

#endif /* _STLP_USE_NEW_IOSTREAMS */
#endif /* if _STLP_EXTRA_OPERATORS_FOR_DEBUG */

#undef _STLP_DBG_STRING_BASE

_STLP_END_NAMESPACE

#endif /* _STLP_DBG_STRING */

// Local Variables:
// mode:C++
// End:
