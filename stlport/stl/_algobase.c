/*
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
#ifndef __SGI_STL_ALGOBASE_C
#define __SGI_STL_ALGOBASE_C

#if defined ( __STL_CLASS_PARTIAL_SPECIALIZATION ) && ! defined (__SGI_STL_INTERNAL_ITERATOR_H)
# include <stl/_iterator.h>
#endif

__STL_BEGIN_NAMESPACE

template <class _InputIter1, class _InputIter2>
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2) {
  __STL_DEBUG_CHECK(__check_range(__first1, __last1))
  __STL_DEBUG_CHECK(__check_range(__first2, __last2))
  for ( ; __first1 != __last1 && __first2 != __last2
        ; ++__first1, ++__first2) {
    if (*__first1 < *__first2)
      return true;
    if (*__first2 < *__first1)
      return false;
  }
  return __first1 == __last1 && __first2 != __last2;
}

template <class _InputIter1, class _InputIter2, class _Compare>
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2,
                             _Compare __comp) {
  __STL_DEBUG_CHECK(__check_range(__first1, __last1))
  __STL_DEBUG_CHECK(__check_range(__first2, __last2))
  for ( ; __first1 != __last1 && __first2 != __last2
        ; ++__first1, ++__first2) {
    if (__comp(*__first1, *__first2))
      return true;
    if (__comp(*__first2, *__first1))
      return false;
  }
  return __first1 == __last1 && __first2 != __last2;
}

# ifndef __STL_NO_EXTENSIONS

template <class _InputIter1, class _InputIter2>
int __lexicographical_compare_3way(_InputIter1 __first1, _InputIter1 __last1,
                                   _InputIter2 __first2, _InputIter2 __last2)
{
  while (__first1 != __last1 && __first2 != __last2) {
    if (*__first1 < *__first2)
      return -1;
    if (*__first2 < *__first1)
      return 1;
    ++__first1;
    ++__first2;
  }
  if (__first2 == __last2) {
    return !(__first1 == __last1);
  }
  else {
    return -1;
  }
}


template <class _InputIter1, class _InputIter2>
int lexicographical_compare_3way(_InputIter1 __first1, _InputIter1 __last1,
                                 _InputIter2 __first2, _InputIter2 __last2)
{
  __STL_DEBUG_CHECK(__check_range(__first1, __last1))
  __STL_DEBUG_CHECK(__check_range(__first2, __last2))
  return __lexicographical_compare_3way(__first1, __last1, __first2, __last2);
}
# endif

template <class _RandomAccessIter, class _Tp>
__STL_INLINE_LOOP _RandomAccessIter __find(_RandomAccessIter __first, _RandomAccessIter __last,
                                           const _Tp& __val,
                                           random_access_iterator_tag)
{
  __STL_DIFFERENCE_TYPE(_RandomAccessIter) __trip_count = (__last - __first) >> 2;

  for ( ; __trip_count > 0 ; --__trip_count) {
    if (*__first == __val) return __first;
    ++__first;

    if (*__first == __val) return __first;
    ++__first;

    if (*__first == __val) return __first;
    ++__first;

    if (*__first == __val) return __first;
    ++__first;
  }

  switch(__last - __first) {
  case 3:
    if (*__first == __val) return __first;
    ++__first;
  case 2:
    if (*__first == __val) return __first;
    ++__first;
  case 1:
    if (*__first == __val) return __first;
    ++__first;
  case 0:
  default:
    return __last;
  }
}

template <class _RandomAccessIter, class _Predicate>
__STL_INLINE_LOOP _RandomAccessIter __find_if(_RandomAccessIter __first, _RandomAccessIter __last,
                                              _Predicate __pred,
                                              random_access_iterator_tag)
{
  __STL_DIFFERENCE_TYPE(_RandomAccessIter) __trip_count = (__last - __first) >> 2;

  for ( ; __trip_count > 0 ; --__trip_count) {
    if (__pred(*__first)) return __first;
    ++__first;

    if (__pred(*__first)) return __first;
    ++__first;

    if (__pred(*__first)) return __first;
    ++__first;

    if (__pred(*__first)) return __first;
    ++__first;
  }

  switch(__last - __first) {
  case 3:
    if (__pred(*__first)) return __first;
    ++__first;
  case 2:
    if (__pred(*__first)) return __first;
    ++__first;
  case 1:
    if (__pred(*__first)) return __first;
    //    ++__first;
  case 0:
  default:
    return __last;
  }
}

template <class _InputIter, class _Tp>
inline _InputIter __find(_InputIter __first, _InputIter __last,
                       const _Tp& __val,
                       input_iterator_tag)
{
  while (__first != __last && !(*__first == __val))
    ++__first;
  return __first;
}

template <class _InputIter, class _Predicate>
inline _InputIter __find_if(_InputIter __first, __STL_MPW_EXTRA_CONST _InputIter __last,
                            _Predicate __pred,
                            input_iterator_tag)
{
  while (__first != __last && !__pred(*__first))
    ++__first;
  return __first;
}

template <class _InputIter, class _Predicate>
_InputIter find_if(_InputIter __first, _InputIter __last,
                   _Predicate __pred) {
  __STL_DEBUG_CHECK(__check_range(__first, __last))
    return __find_if(__first, __last, __pred, __ITERATOR_CATEGORY(__first, _InputIter));
}

template <class _InputIter, class _Tp>
_InputIter find(_InputIter __first, _InputIter __last, const _Tp& __val)
{
  __STL_DEBUG_CHECK(__check_range(__first, __last))
    return __find(__first, __last, __val, __ITERATOR_CATEGORY(__first, _InputIter));
}

template <class _ForwardIter1, class _ForwardIter2, class _BinaryPred>
_ForwardIter1 search(_ForwardIter1 __first1, _ForwardIter1 __last1,
                     _ForwardIter2 __first2, _ForwardIter2 __last2,
                     _BinaryPred  __predicate) 
{
  __STL_DEBUG_CHECK(__check_range(__first1, __last1))
  __STL_DEBUG_CHECK(__check_range(__first2, __last2))
  // Test for empty ranges
  if (__first1 == __last1 || __first2 == __last2)
    return __first1;

  // Test for a pattern of length 1.
  _ForwardIter2 __tmp(__first2);
  ++__tmp;
  if (__tmp == __last2) {
    while (__first1 != __last1 && !__predicate(*__first1, *__first2))
      ++__first1;
    return __first1;    
  }
  
  // General case.

  _ForwardIter2 __p1, __p;

  __p1 = __first2; ++__p1;

  //  _ForwardIter1 __current = __first1;

  while (__first1 != __last1) {
    while (__first1 != __last1) {
      if (__predicate(*__first1, *__first2))
        break;
      ++__first1;
    }
    while (__first1 != __last1 && !__predicate(*__first1, *__first2))
      ++__first1;
    if (__first1 == __last1)
      return __last1;

    __p = __p1;
    _ForwardIter1 __current = __first1; 
    if (++__current == __last1) return __last1;

    while (__predicate(*__current, *__p)) {
      if (++__p == __last2)
        return __first1;
      if (++__current == __last1)
        return __last1;
    }

    ++__first1;
  }
  return __first1;
}

// find_first_of, with and without an explicitly supplied comparison function.

template <class _InputIter, class _ForwardIter, class _BinaryPredicate>
_InputIter __find_first_of(_InputIter __first1, _InputIter __last1,
                           _ForwardIter __first2, _ForwardIter __last2,
                           _BinaryPredicate __comp) {
  for ( ; __first1 != __last1; ++__first1) 
    for (_ForwardIter __iter = __first2; __iter != __last2; ++__iter)
      if (__comp(*__first1, *__iter))
        return __first1;
  return __last1;
}


// find_end, with and without an explicitly supplied comparison function.
// Search [first2, last2) as a subsequence in [first1, last1), and return
// the *last* possible match.  Note that find_end for bidirectional iterators
// is much faster than for forward iterators.

// find_end for forward iterators. 

template <class _ForwardIter1, class _ForwardIter2,
          class _BinaryPredicate>
_ForwardIter1 __find_end(_ForwardIter1 __first1, _ForwardIter1 __last1,
                         _ForwardIter2 __first2, _ForwardIter2 __last2,
                         forward_iterator_tag, forward_iterator_tag,
                         _BinaryPredicate __comp)
{
  if (__first2 == __last2)
    return __last1;
  else {
    _ForwardIter1 __result = __last1;
    while (1) {
      _ForwardIter1 __new_result
        = search(__first1, __last1, __first2, __last2, __comp);
      if (__new_result == __last1)
        return __result;
      else {
        __result = __new_result;
        __first1 = __new_result;
        ++__first1;
      }
    }
  }
}

// find_end for bidirectional iterators.  Requires partial specialization.
#if defined ( __STL_CLASS_PARTIAL_SPECIALIZATION )
 
template <class _BidirectionalIter1, class _BidirectionalIter2,
          class _BinaryPredicate>
_BidirectionalIter1
__find_end(_BidirectionalIter1 __first1, _BidirectionalIter1 __last1,
           _BidirectionalIter2 __first2, _BidirectionalIter2 __last2,
           bidirectional_iterator_tag, bidirectional_iterator_tag, 
           _BinaryPredicate __comp)
{
  typedef reverse_iterator<_BidirectionalIter1> _RevIter1;
  typedef reverse_iterator<_BidirectionalIter2> _RevIter2;

  _RevIter1 __rlast1(__first1);
  _RevIter2 __rlast2(__first2);
  _RevIter1 __rresult = search(_RevIter1(__last1), __rlast1,
                               _RevIter2(__last2), __rlast2,
                               __comp);

  if (__rresult == __rlast1)
    return __last1;
  else {
    _BidirectionalIter1 __result = __rresult.base();
    advance(__result, -distance(__first2, __last2));
    return __result;
  }
}
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class _ForwardIter1, class _ForwardIter2, 
          class _BinaryPredicate>
_ForwardIter1 
find_end(_ForwardIter1 __first1, _ForwardIter1 __last1, 
         _ForwardIter2 __first2, _ForwardIter2 __last2,
         _BinaryPredicate __comp)
{
  __STL_DEBUG_CHECK(__check_range(__first1, __last1))
  __STL_DEBUG_CHECK(__check_range(__first2, __last2))
  return __find_end(__first1, __last1, __first2, __last2,
# if defined (__STL_CLASS_PARTIAL_SPECIALIZATION)
                    __ITERATOR_CATEGORY(__first1, _ForwardIter1),
                    __ITERATOR_CATEGORY(__first2, _ForwardIter2),
# else
		    forward_iterator_tag(),
		    forward_iterator_tag(),
# endif
                    __comp);
}

template <class _ForwardIter, class _Tp, class _Compare, class _Distance>
_ForwardIter __lower_bound(_ForwardIter __first, _ForwardIter __last,
                              const _Tp& __val, _Compare __comp, _Distance*)
{
  _Distance __len = 0;
  distance(__first, __last, __len);
  _Distance __half;
  _ForwardIter __middle;

  while (__len > 0) {
    __half = __len >> 1;
    __middle = __first;
    advance(__middle, __half);
    if (__comp(*__middle, __val)) {
      __first = __middle;
      ++__first;
      __len = __len - __half - 1;
    }
    else
      __len = __half;
  }
  return __first;
}

__STL_END_NAMESPACE

#endif /* __SGI_STL_ALGOBASE_C */

// Local Variables:
// mode:C++
// End:
