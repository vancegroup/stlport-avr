/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996-1998
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

#ifndef __SGI_STL_INTERNAL_ITERATOR_OLD_H
#define __SGI_STL_INTERNAL_ITERATOR_OLD_H

#ifndef __SGI_STL_INTERNAL_ITERATOR_BASE_H
# include <stl/_iterator_base.h>
#endif

__STL_BEGIN_NAMESPACE

# ifdef __STL_USE_OLD_HP_ITERATOR_QUERIES

template <class _Container>
inline output_iterator_tag __STL_CALL
iterator_category(const back_insert_iterator<_Container>&) { return output_iterator_tag(); }
template <class _Container>
inline output_iterator_tag __STL_CALL
iterator_category(const front_insert_iterator<_Container>&) { return output_iterator_tag(); }
template <class _Container>
inline output_iterator_tag __STL_CALL
iterator_category(const insert_iterator<_Container>&) { return output_iterator_tag(); }

# endif

# if defined (__STL_MSVC50_COMPATIBILITY)
# define __Reference _Reference, class _Pointer
# define Reference__ _Reference, _Pointer
template <class _BidirectionalIterator, class _Tp, 
    __DFL_TMPL_PARAM(_Reference, _Tp& ),
    __DFL_TMPL_PARAM(_Pointer, _Tp*),
    __DFL_TYPE_PARAM(_Distance, ptrdiff_t)> 
# else
# define __Reference _Reference
# define Reference__ _Reference
template <class _BidirectionalIterator, class _Tp, __DFL_TMPL_PARAM(_Reference, _Tp& ),
    __DFL_TYPE_PARAM(_Distance, ptrdiff_t)> 
# endif
class reverse_bidirectional_iterator {
  typedef reverse_bidirectional_iterator<_BidirectionalIterator, _Tp, 
                                         Reference__, _Distance> _Self;
  //  friend inline bool operator== __STL_NULL_TMPL_ARGS (const _Self& x, const _Self& y);
protected:
  _BidirectionalIterator current;
public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef _Tp                        value_type;
  typedef _Distance                  difference_type;
# if defined (__STL_MSVC50_COMPATIBILITY)
  typedef _Pointer                   pointer;
# else
  typedef _Tp*                       pointer;
# endif
  typedef _Reference                 reference;

  reverse_bidirectional_iterator() {}
  explicit reverse_bidirectional_iterator(_BidirectionalIterator __x)
    : current(__x) {}
  _BidirectionalIterator base() const { return current; }
  _Reference operator*() const {
    _BidirectionalIterator __tmp = current;
    return *--__tmp;
  }
# if !(defined __SGI_STL_NO_ARROW_OPERATOR && ! defined (__STL_MSVC50_COMPATIBILITY))
  __STL_DEFINE_ARROW_OPERATOR
# endif
  _Self& operator++() {
    --current;
    return *this;
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    --current;
    return __tmp;
  }
  _Self& operator--() {
    ++current;
    return *this;
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    ++current;
    return __tmp;
  }
};

# ifdef __STL_USE_OLD_HP_ITERATOR_QUERIES
template <class _BidirectionalIterator, class _Tp, class __Reference, 
          class _Distance>
inline bidirectional_iterator_tag __STL_CALL
iterator_category(const reverse_bidirectional_iterator<_BidirectionalIterator, _Tp, Reference__, _Distance>&) 
{ return bidirectional_iterator_tag(); }
template <class _BidirectionalIterator, class _Tp, class __Reference, 
  class _Distance>
inline _Tp* __STL_CALL
value_type(const reverse_bidirectional_iterator<_BidirectionalIterator, _Tp, Reference__, _Distance>&)
{ return (_Tp*) 0; }
template <class _BidirectionalIterator, class _Tp, class __Reference, 
          class _Distance>
inline _Distance* __STL_CALL
distance_type(const reverse_bidirectional_iterator<_BidirectionalIterator, _Tp, Reference__, _Distance>&)
{ return (_Distance*) 0; }
#endif

template <class _BidirectionalIterator, class _Tp, class __Reference, 
          class _Distance>
inline bool  __STL_CALL operator==(
    const reverse_bidirectional_iterator<_BidirectionalIterator, _Tp,
                                               Reference__, _Distance>& __x,
    const reverse_bidirectional_iterator<_BidirectionalIterator, _Tp,
                                               Reference__, _Distance>& __y)
{
  return __x.base() == __y.base();
}

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE

template <class _BiIter, class _Tp, class __Reference, class _Distance>
inline bool  __STL_CALL operator!=(
    const reverse_bidirectional_iterator<_BiIter, _Tp, Reference__, _Distance>& __x, 
    const reverse_bidirectional_iterator<_BiIter, _Tp, Reference__, _Distance>& __y)
{
  return !(__x == __y);
}

#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */

#if ! defined ( __STL_CLASS_PARTIAL_SPECIALIZATION ) || defined (__STL_PARTIAL_SPECIALIZATION_BUG)

// This is the old version of reverse_iterator, as found in the original
//  HP STL.  It does not use partial specialization.

template <class _RandomAccessIterator, 
# if defined (__MSL__) && (__MSL__ >= 0x2405)
	__DFL_TMPL_PARAM(_Tp,iterator_traits<_RandomAccessIterator>::value_type),
# else
	class _Tp,
#endif
 __DFL_TMPL_PARAM(_Reference,_Tp&),
# if defined (__STL_MSVC50_COMPATIBILITY)
        __DFL_TMPL_PARAM(_Pointer, _Tp*),
# endif
        __DFL_TYPE_PARAM(_Distance,ptrdiff_t)> 
class reverse_iterator {
  typedef reverse_iterator<_RandomAccessIterator, _Tp, Reference__, _Distance>
          _Self;
protected:
  _RandomAccessIterator __current;
public:
  typedef random_access_iterator_tag iterator_category;
  typedef _Tp                        value_type;
  typedef _Distance                  difference_type;
# if defined (__STL_MSVC50_COMPATIBILITY)
  typedef _Pointer                   pointer;
# else
  typedef _Tp*                       pointer;
# endif
  typedef _Reference                 reference;

  reverse_iterator() {}
  reverse_iterator(const _Self& __x) : __current(__x.base()) {}
  explicit reverse_iterator(_RandomAccessIterator __x) : __current(__x) {}
  _Self& operator=(const _Self& __x) {__current = __x.base(); return *this; }  
       
  _RandomAccessIterator base() const { return __current; }
  _Reference operator*() const { return *(__current - (difference_type)1); }

# if !(defined __SGI_STL_NO_ARROW_OPERATOR && ! defined (__STL_MSVC50_COMPATIBILITY))
  __STL_DEFINE_ARROW_OPERATOR
# endif

  _Self& operator++() {
    --__current;
    return *this;
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    --__current;
    return __tmp;
  }
  _Self& operator--() {
    ++__current;
    return *this;
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    ++__current;
    return __tmp;
  }
  _Self operator+(_Distance __n) const {
    return _Self(__current - __n);
  }
  _Self& operator+=(_Distance __n) {
    __current -= __n;
    return *this;
  }
  _Self operator-(_Distance __n) const {
    return _Self(__current + __n);
  }
  _Self& operator-=(_Distance __n) {
    __current += __n;
    return *this;
  }
  _Reference operator[](_Distance __n) const { return *(*this + __n); }
};

# ifdef __STL_USE_OLD_HP_ITERATOR_QUERIES
template <class _RandomAccessIterator, class _Tp, 
          class __Reference, class _Distance>
inline random_access_iterator_tag __STL_CALL
iterator_category(const reverse_iterator<_RandomAccessIterator, _Tp, Reference__, _Distance>&)
{ return random_access_iterator_tag(); }
template <class _RandomAccessIterator, class _Tp,
  class __Reference, class _Distance>
inline _Tp*  __STL_CALL value_type(const reverse_iterator<_RandomAccessIterator, _Tp, Reference__, _Distance>&)
{ return (_Tp*) 0; }
template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline _Distance*  __STL_CALL
distance_type(const reverse_iterator<_RandomAccessIterator, _Tp, Reference__, _Distance>&)
{ return (_Distance*) 0; }
#endif

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline bool  __STL_CALL
operator==(const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __x, 
           const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __y)
{
  return __x.base() == __y.base();
}

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline bool __STL_CALL 
operator<(const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __x, 
          const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __y)
{
  return __y.base() < __x.base();
}

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline bool __STL_CALL 
operator!=(const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __x, 
           const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __y) {
  return !(__x == __y);
}

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline bool __STL_CALL 
operator>(const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __x, 
          const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __y) {
  return __y < __x;
}

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline bool __STL_CALL 
operator<=(const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __x, 
           const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __y) {
  return !(__y < __x);
}

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline bool __STL_CALL 
operator>=(const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __x, 
           const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __y) {
  return !(__x < __y);
}

#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline _Distance  __STL_CALL
operator-(const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __x, 
          const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __y)
{
  return __y.base() - __x.base();
}

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline reverse_iterator<_RandomAccessIterator, _Tp,
                        Reference__, _Distance>  __STL_CALL
operator+(_Distance __n,
          const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __x)
{
  return reverse_iterator<_RandomAccessIterator, _Tp,
                          Reference__, _Distance>(__x.base() - __n);
}

#endif /* ! defined ( __STL_CLASS_PARTIAL_SPECIALIZATION ) || defined (__STL_PARTIAL_SPECIALIZATION_BUG) */

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_ITERATOR_H */

// Local Variables:
// mode:C++
// End:
