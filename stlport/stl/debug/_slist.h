/*
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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef _STLP_INTERNAL_DBG_SLIST_H
#define _STLP_INTERNAL_DBG_SLIST_H

#include <stl/debug/_iterator.h>

#define _STLP_FILE_UNIQUE_ID SLIST_H
_STLP_INSTRUMENT_FILE();

# ifndef _STLP_USE_WRAPPER_FOR_ALLOC_PARAM
#  undef  _DBG_slist
#  define _DBG_slist slist
# endif

#  define _STLP_DBG_SLIST_BASE __WORKAROUND_DBG_RENAME(slist) <_Tp, _Alloc>

_STLP_BEGIN_NAMESPACE

# ifdef _STLP_DEBUG_USE_DISTINCT_VALUE_TYPE_HELPERS
template <class _Tp, class _Alloc>
inline _Tp*
value_type(const _DBG_iter_base< _STLP_DBG_SLIST_BASE >&) {
  return (_Tp*)0;
}

template <class _Tp, class _Alloc>
inline forward_iterator_tag
iterator_category(const _DBG_iter_base< _STLP_DBG_SLIST_BASE >&) {
  return forward_iterator_tag();
}
# endif

template <class _Tp, _STLP_DEFAULT_ALLOCATOR_SELECT(_Tp) >
class _DBG_slist : private __range_checker<_Tp>, public _STLP_DBG_SLIST_BASE
{
private:
  typedef _STLP_DBG_SLIST_BASE _Base;
  typedef _DBG_slist<_Tp,_Alloc> _Self;

public:

  __IMPORT_CONTAINER_TYPEDEFS(_Base)

  typedef _DBG_iter<_Base, _Nonconst_traits<value_type> > iterator;
  typedef _DBG_iter<_Base, _Const_traits<value_type> > const_iterator;

protected:
  friend class __owned_link;
  mutable __owned_list _M_iter_list;
  void _Invalidate_all() {
    _M_iter_list._Invalidate_all();
  }
  void _Invalidate_iterator(const iterator& __it) {
    __invalidate_iterator(&_M_iter_list, __it); 
  }
  void _Invalidate_iterators(const iterator& __first, const iterator& __last) {
    __invalidate_range(&_M_iter_list, __first, __last);
  }

  typedef typename _Base::iterator _Base_iterator;

public:
  const _Base* _Get_base() const { return (const _Base*)this; }
  _Base* _Get_base() { return (_Base*)this; }

public:

  explicit _DBG_slist(const allocator_type& __a = allocator_type()) 
    : _STLP_DBG_SLIST_BASE(__a) , _M_iter_list(_Get_base()) {}
  
#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit _DBG_slist(size_type __n, const value_type& __x = _Tp(),
#else
  _DBG_slist(size_type __n, const value_type& __x,
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
		      const allocator_type& __a =  allocator_type())
    : _STLP_DBG_SLIST_BASE(__n, __x, __a), _M_iter_list(_Get_base()) {}
  
#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  explicit _DBG_slist(size_type __n) : _STLP_DBG_SLIST_BASE(__n) , _M_iter_list(_Get_base()) {}
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  explicit _DBG_slist(__partial_move_source<_Self> src)
		: _STLP_DBG_SLIST_BASE(_AsPartialMoveSource<_STLP_DBG_SLIST_BASE >(src.get())) , 
      _M_iter_list(_Get_base()) {}
  
  /*explicit _DBG_slist(__full_move_source<_Self> src)
		   : _STLP_DBG_SLIST_BASE(_FullMoveSource<_STLP_DBG_SLIST_BASE >(src.get())) , _M_iter_list(_Get_base()) {
    src.get()._Invalidate_all();
  }*/

#ifdef _STLP_MEMBER_TEMPLATES
  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InputIterator>
  _DBG_slist(_InputIterator __first, _InputIterator __last,
		      const allocator_type& __a _STLP_ALLOCATOR_TYPE_DFL)
    : __range_checker<_Tp>(__first, __last), 
      _STLP_DBG_SLIST_BASE(__first, __last, __a), _M_iter_list(_Get_base()) {
    } 

# ifdef _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
  template <class _InputIterator>
  _DBG_slist(_InputIterator __first, _InputIterator __last)
    : __range_checker<_Tp>(__first, __last), 
      _STLP_DBG_SLIST_BASE(__first, __last), _M_iter_list(_Get_base()) {
    } 
# endif
#else /* _STLP_MEMBER_TEMPLATES */

  _DBG_slist(const value_type* __first, const value_type* __last,
        const allocator_type& __a =  allocator_type())
    : __range_checker<_Tp>(__first, __last), 
      _STLP_DBG_SLIST_BASE(__first, __last, __a), _M_iter_list(_Get_base())  {
    }

  _DBG_slist(const_iterator __first, const_iterator __last,
		      const allocator_type& __a = allocator_type() )
    : __range_checker<_Tp>(__first._M_iterator, __last._M_iterator), 
      _STLP_DBG_SLIST_BASE(__first._M_iterator, __last._M_iterator, __a), _M_iter_list(_Get_base()) {
    }
  
#endif /* _STLP_MEMBER_TEMPLATES */

  _DBG_slist(const _Self& __x) : 
    __range_checker<_Tp>(__x), _STLP_DBG_SLIST_BASE(__x), _M_iter_list(_Get_base()) {}
  
  _Self& operator= (const _Self& __x) {
    if (this != &__x) {
      _Invalidate_iterators(this->begin(), this->end());
      _Base::operator=((const _Base&)__x);
    }
    return *this;
  }
  
  ~_DBG_slist() {}

public:
  void assign(size_type __n, const value_type& __val) {
    _Invalidate_iterators(this->begin(), this->end());
    _Base::assign(__n, __val); 
  }

public:

  iterator before_begin() { return iterator(&_M_iter_list, _Base::before_begin()); }
  const_iterator before_begin() const
    { return const_iterator(&_M_iter_list, _Base::before_begin()); }

  iterator begin() { return iterator(&_M_iter_list, _Base::begin()); }
  const_iterator begin() const 
    { return const_iterator(&_M_iter_list,_Base::begin());}

  iterator end() { return iterator(&_M_iter_list, _Base::end()); }
  const_iterator end() const { return const_iterator(&_M_iter_list, _Base::end()); }

  void swap(_Self& __x) { 
    _M_iter_list._Swap_owners(__x._M_iter_list);
    _Base::swap(__x);
  }

public:
  reference front() {
    _STLP_VERBOSE_ASSERT(!this->empty(), _StlMsg_EMPTY_CONTAINER)
    return _Base::front(); 
  }
  const_reference front() const {
    _STLP_VERBOSE_ASSERT(!this->empty(), _StlMsg_EMPTY_CONTAINER)
    return _Base::front(); 
  }
  void pop_front() {
    _STLP_VERBOSE_ASSERT(!this->empty(), _StlMsg_EMPTY_CONTAINER)
    _Base::pop_front();
  }
  iterator previous(const_iterator __pos) {
		_STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list, __pos))
		return iterator(&_M_iter_list,_Base::previous(__pos._M_iterator));
  }
  const_iterator previous(const_iterator __pos) const {
		_STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list, __pos))
    return const_iterator(&_M_iter_list,_Base::previous(__pos._M_iterator));
  }

public:

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert_after(iterator __pos, const value_type& __x = _Tp()) {
#else
  iterator insert_after(iterator __pos, const value_type& __x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    _STLP_DEBUG_CHECK(_Dereferenceable(__pos))
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list, __pos))
    return iterator(&_M_iter_list,_Base::insert_after(__pos._M_iterator, __x));
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert_after(iterator __pos) {
		return insert_after(__pos, _STLP_DEFAULT_CONSTRUCTED(_Tp));
	}
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void insert_after(iterator __pos, size_type __n, const value_type& __x) {
    _STLP_DEBUG_CHECK(_Dereferenceable(__pos))
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list, __pos))
    _Base::insert_after(__pos._M_iterator, __n, __x);
  }

#ifdef _STLP_MEMBER_TEMPLATES

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    _Invalidate_iterators(this->begin(), this->end());
    _Base::assign(__first, __last);
  }

  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InIter>
  void insert_after(iterator __pos, _InIter __first, _InIter __last) {
    _STLP_DEBUG_CHECK(_Dereferenceable(__pos))
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list, __pos))
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    _Base::insert_after(__pos._M_iterator, __first, __last);
  }

  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InIter>
  void insert(iterator __pos, _InIter __first, _InIter __last) {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list, __pos))
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    _Base::insert(__pos._M_iterator, __first, __last);
  }

#else /* _STLP_MEMBER_TEMPLATES */

  void insert_after(iterator __pos,
                    const_iterator __first, const_iterator __last) {
    _STLP_DEBUG_CHECK(_Dereferenceable(__pos))
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list, __pos))
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    _Base::insert_after(__pos._M_iterator, __first._M_iterator, __last._M_iterator);
  }
  void insert_after(iterator __pos,
                    const value_type* __first, const value_type* __last) {
    _STLP_DEBUG_CHECK(_Dereferenceable(__pos))
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list, __pos))
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    _Base::insert_after(__pos._M_iterator, __first, __last);
  }

  void insert(iterator __pos, const_iterator __first, const_iterator __last) {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    _Base::insert(__pos._M_iterator, __first._M_iterator, __last._M_iterator);
  }
  void insert(iterator __pos, const value_type* __first, 
                              const value_type* __last) {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    _Base::insert(__pos._M_iterator, __first, __last);
  }

#endif /* _STLP_MEMBER_TEMPLATES */

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert(iterator __pos, const value_type& __x = _Tp()) {
#else
  iterator insert(iterator __pos, const value_type& __x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    return iterator(&_M_iter_list, _Base::insert(__pos._M_iterator, __x));
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  iterator insert(iterator __pos) {
    return insert(__pos, _STLP_DEFAULT_CONSTRUCTED(_Tp));
  }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void insert(iterator __pos, size_type __n, const value_type& __x) {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _Base::insert(__pos._M_iterator, __n, __x);
  } 
    
public:
  iterator erase_after(iterator __pos) {
    _STLP_DEBUG_CHECK(_Dereferenceable(__pos))
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    iterator __tmp = __pos;
    _Invalidate_iterator(++__tmp);
    return iterator(&_M_iter_list, _Base::erase_after(__pos._M_iterator));
  }
  iterator erase_after(iterator __before_first, iterator __last) {
    _STLP_DEBUG_CHECK(_Dereferenceable(__before_first))
    _STLP_DEBUG_CHECK(__check_range(__before_first, __last, this->begin(), this->end()))
    _Invalidate_iterators(__before_first, __last);
    return iterator(&_M_iter_list, _Base::erase_after(__before_first._M_iterator, __last._M_iterator));
  } 

  iterator erase(iterator __pos) {
    _STLP_DEBUG_CHECK(_Dereferenceable(__pos))
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _Invalidate_iterator(__pos);
    return iterator(&_M_iter_list, _Base::erase(__pos._M_iterator));
  }
  iterator erase(iterator __first, iterator __last) {
    _STLP_DEBUG_CHECK(__check_range(__first, __last, this->begin(), this->end()))
    _Invalidate_iterators(__first, __last);
    return iterator(&_M_iter_list, _Base::erase(__first._M_iterator, __last._M_iterator));
  }

#if !defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size, const value_type& __x = _Tp()) {
#else
  void resize(size_type __new_size, const value_type& __x) {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
    _Base::resize(__new_size, __x);
  }

#if defined(_STLP_DONT_SUP_DFLT_PARAM)
  void resize(size_type __new_size) { resize(__new_size, _STLP_DEFAULT_CONSTRUCTED(_Tp)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

  void clear() {
    _Invalidate_iterators(this->begin(), this->end());      
    _Base::clear();
  }

public:
  // Moves the range [__before_first + 1, __before_last + 1) to *this,
  //  inserting it immediately after __pos.  This is constant time.
  void splice_after(iterator __pos, 
                    iterator __before_first, iterator __before_last)
  {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _STLP_DEBUG_CHECK(__check_range(__before_first, __before_last))
    if (__before_first != __before_last) {
      _Base::splice_after(__pos._M_iterator, 
                          __before_first._M_iterator, __before_last._M_iterator);
      __before_first++;
      __before_last++;
      __invalidate_range(__before_first._Owner(), __before_first, __before_last);
    }
  }

  // Moves the element that follows __prev to *this, inserting it immediately
  //  after __pos.  This is constant time.
  void splice_after(iterator __pos, iterator __prev)
  {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _Base::splice_after(__pos._M_iterator, __prev._M_iterator);
    __invalidate_iterator(__prev._Owner(), ++__prev);
  }

  // Removes all of the elements from the list __x to *this, inserting
  // them immediately after __pos.  __x must not be *this.  Complexity:
  // linear in __x.size().
  void splice_after(iterator __pos, _Self& __x) {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _STLP_VERBOSE_ASSERT(!(&__x==this), _StlMsg_INVALID_ARGUMENT)
    _Base::splice_after(__pos._M_iterator, (_Base&)__x);
    __x._Invalidate_all();
  }

  // Linear in distance(begin(), __pos), and linear in __x.size().
  void splice(iterator __pos, _Self& __x) {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _STLP_VERBOSE_ASSERT(!(&__x==this), _StlMsg_INVALID_ARGUMENT)
    _Base::splice(__pos._M_iterator, (_Base&)__x);
    //dums: Invalidation according the Standard C++98 rules but against the SGI specs:
    __x._Invalidate_all();
  }

  // Linear in distance(begin(), __pos), and in distance(__x.begin(), __i).
  void splice(iterator __pos, _Self& __x, iterator __i) {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _STLP_DEBUG_CHECK(__check_if_owner(&__x._M_iter_list ,__i))
    _STLP_VERBOSE_ASSERT(&__x!=this, _StlMsg_INVALID_ARGUMENT)
    _Base::splice(__pos._M_iterator, (_Base&)__x, __i._M_iterator);
    //dums: Invalidation according the Standard C++98 rules but against the SGI specs:
    __x._Invalidate_iterator(__i);
  }

  // Linear in distance(begin(), __pos), in distance(__x.begin(), __first),
  // and in distance(__first, __last).
  void splice(iterator __pos, _Self& __x, iterator __first, iterator __last) {
    _STLP_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _STLP_VERBOSE_ASSERT(&__x!=this, _StlMsg_INVALID_ARGUMENT)
    _STLP_DEBUG_CHECK(__check_range(__first, __last, __x.begin(), __x.end()))
    if (__first != __last) {
      _Base::splice(__pos._M_iterator, (_Base&)__x, __first._M_iterator, __last._M_iterator);      
      //dums: Invalidation according the Standard C++98 rules but against the SGI specs:
      __invalidate_range(&__x._M_iter_list, __first, __last);
    }
  }

public:

  void remove(const value_type& __val) {
    _Base_iterator __first = _Base::begin(), __last = _Base::end();
    while (__first != __last) {
      _Base_iterator __next = __first;
      ++__next;
      if (__val == *__first) {
        _Invalidate_iterator(iterator(&_M_iter_list, __first));
        _Base::erase(__first);
      }
      __first = __next;
    }
  }
  void unique() {
    _Base_iterator __first = _Base::begin(), __last = _Base::end();
    if (__first == __last) return;
    _Base_iterator __next = __first;
    while (++__next != __last) {
      if (*__first == *__next) {
        _Invalidate_iterator(iterator(&_M_iter_list, __next));
        _Base::erase(__next);
      }
      else
        __first = __next;
      __next = __first;
    }
  }
  void merge(_Self& __x) {
    _STLP_VERBOSE_ASSERT(&__x!=this, _StlMsg_INVALID_ARGUMENT)
    _STLP_DEBUG_CHECK(_STLP_STD::is_sorted(_Base::begin(), _Base::end()))
    _STLP_DEBUG_CHECK(_STLP_STD::is_sorted(__x.begin()._M_iterator, __x.end()._M_iterator))
    _Base::merge((_Base&)__x);
  }
  void sort() {
    _Base::sort();
  }

#ifdef _STLP_MEMBER_TEMPLATES
  template <class _Predicate> 
  void remove_if(_Predicate __pred) {
    _Base_iterator __first = _Base::begin(), __last = _Base::end();
    while (__first != __last) {
      _Base_iterator __next = __first;
      ++__next;
      if (__pred(*__first)) {
        _Invalidate_iterator(iterator(&_M_iter_list, __first));
        _Base::erase(__first);
      }
      __first = __next;
    }
  }

  template <class _BinaryPredicate> 
  void unique(_BinaryPredicate __pred) {
    _Base_iterator __first = _Base::begin(), __last = _Base::end();
    if (__first == __last) return;
    _Base_iterator __next = __first;
    while (++__next != __last) {
      if (__binary_pred(*__first, *__next)) {
        _Invalidate_iterator(iterator(&_M_iter_list, __next));
        _Base::erase(__next);
      }
      else
        __first = __next;
      __next = __first;
    }
  }

  template <class _StrictWeakOrdering> 
  void merge(_Self& __x, _StrictWeakOrdering __ord) {
    _STLP_VERBOSE_ASSERT(&__x!=this, _StlMsg_INVALID_ARGUMENT)
    _STLP_DEBUG_CHECK(_STLP_STD::is_sorted(_Base::begin(), _Base::end(), __ord))
    _STLP_DEBUG_CHECK(_STLP_STD::is_sorted(__x.begin()._M_iterator, __x.end()._M_iterator, __ord))
    _Base::merge((_Base&)__x, __ord);
  }

  template <class _StrictWeakOrdering>
  void sort(_StrictWeakOrdering __comp) {
    _Base::sort(__comp);
  }
#endif /* _STLP_MEMBER_TEMPLATES */

};

#define _STLP_TEMPLATE_HEADER template <class _Tp, class _Alloc>
#define _STLP_TEMPLATE_CONTAINER _DBG_slist<_Tp,_Alloc>
#define _STLP_TEMPLATE_CONTAINER_BASE _STLP_DBG_SLIST_BASE
#include <stl/debug/_relops_cont.h>
#undef _STLP_TEMPLATE_CONTAINER_BASE
#undef _STLP_TEMPLATE_CONTAINER
#undef _STLP_TEMPLATE_HEADER

_STLP_END_NAMESPACE

#undef _STLP_FILE_UNIQUE_ID

#endif /* _STLP_INTERNAL_DBG_SLIST_H */

// Local Variables:
// mode:C++
// End:
