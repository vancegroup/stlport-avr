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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */


#ifndef __SGI_STL_INTERNAL_ALGOBASE_H
#define __SGI_STL_INTERNAL_ALGOBASE_H

# if defined (__STL_DEBUG) && ! defined (__STLPORT_DEBUG_H)
#  include <stl/debug/_debug.h>
# endif

# if ! defined (__STLPORT_CSTDDEF)
#  include <cstddef>
# endif

#ifndef __STLPORT_CSTRING
# include <cstring>
#endif

#ifndef __STLPORT_CLIMITS
# include <climits>
#endif

# if ! defined (__STLPORT_CSTDLIB)
#  include <cstdlib>
# endif

# ifndef __SGI_STL_INTERNAL_RELOPS
#  include <stl/_relops.h>
# endif

# ifndef __SGI_STL_INTERNAL_PAIR_H
#  include <stl/_pair.h>
# endif

#ifndef __SGI_STL_INTERNAL_ITERATOR_BASE_H
# include <stl/_iterator_base.h>
#endif

__STL_BEGIN_NAMESPACE
// swap and iter_swap
template <class _Tp>
inline void swap(_Tp& __a, _Tp& __b) {
  _Tp __tmp = __a;
  __a = __b;
  __b = __tmp;
}

template <class _ForwardIter1, class _ForwardIter2, class _Tp>
inline void __iter_swap(_ForwardIter1 __a, _ForwardIter2 __b, _Tp*) {
  swap((_Tp&)*__a, (_Tp&)*__b);
}

template <class _ForwardIter1, class _ForwardIter2>
inline void iter_swap(_ForwardIter1 __a, _ForwardIter2 __b) {
  __iter_swap(__a, __b, __VALUE_TYPE(__a, _ForwardIter1));
}

//--------------------------------------------------
// min and max

# if OBSOLETE
// boris : a cleaner solution uses transparent approach
// #  undef min
// #  undef max
# endif

# if !defined (__BORLANDC__) || defined (__STL_USE_OWN_NAMESPACE)
template <class _Tp>
inline const _Tp& __STL_MIN(const _Tp& __a, const _Tp& __b) { return __b < __a ? __b : __a; }
template <class _Tp>
inline const _Tp& __STL_MAX(const _Tp& __a, const _Tp& __b) {  return  __a < __b ? __b : __a; }
#endif /* __BORLANDC__ */

# if defined (__BORLANDC__) && ( __BORLANDC__ < 0x530 || defined (__STL_USE_OWN_NAMESPACE))
inline unsigned long __STL_MIN (unsigned long __a, unsigned long __b) { return __b < __a ? __b : __a; }
inline unsigned long __STL_MAX (unsigned long __a, unsigned long __b) {  return  __a < __b ? __b : __a; }
# endif

template <class _Tp, class _Compare>
inline const _Tp& __STL_MIN(const _Tp& __a, const _Tp& __b, _Compare __comp) { 
  return __comp(__b, __a) ? __b : __a;
}

template <class _Tp, class _Compare>
inline const _Tp& __STL_MAX(const _Tp& __a, const _Tp& __b, _Compare __comp) {
  return __comp(__a, __b) ? __b : __a;
}

//--------------------------------------------------
// copy

// All of these auxiliary functions serve two purposes.  (1) Replace
// calls to copy with memmove whenever possible.  (Memmove, not memcpy,
// because the input and output ranges are permitted to overlap.)
// (2) If we're using random access iterators, then write the loop as
// a for loop with an explicit count.

template <class _InputIter, class _OutputIter, class _Distance>
inline _OutputIter __copy(_InputIter __first, _InputIter __last,
                          _OutputIter __result,
                          input_iterator_tag, _Distance*) {
  for ( ; __first != __last; ++__result, ++__first)
    *__result = *__first;
  return __result;
}

# if defined (__STL_NONTEMPL_BASE_MATCH_BUG) 
template <class _InputIter, class _OutputIter, class _Distance>
inline _OutputIter __copy(_InputIter __first, _InputIter __last,
			  _OutputIter __result, forward_iterator_tag, _Distance* __dis) {
  for ( ; __first != __last; ++__result, ++__first)
    *__result = *__first;
  return __result;
}


template <class _InputIter, class _OutputIter, class _Distance>
inline _OutputIter __copy(_InputIter __first, _InputIter __last,
			  _OutputIter __result, bidirectional_iterator_tag, _Distance* __dis) {
  for ( ; __first != __last; ++__result, ++__first)
    *__result = *__first;
  return __result;
}
# endif 

template <class _RandomAccessIter, class _OutputIter, class _Distance>
inline _OutputIter
__copy(_RandomAccessIter __first, _RandomAccessIter __last,
       _OutputIter __result, random_access_iterator_tag, _Distance*) {
  for (_Distance __n = __last - __first; __n > 0; --__n) {
    *__result = *__first;
    ++__first;
    ++__result;
  }
  return __result;
}

inline void*
__copy_trivial(const void* __first, const void* __last, void* __result) {
  return (__last == __first) ? __result : 
    ((char*)memmove(__result, __first, ((const char*)__last - (const char*)__first))) + 
    ((const char*)__last - (const char*)__first);
}

//--------------------------------------------------
// copy_backward auxiliary functions

template <class _BidirectionalIter1, class _BidirectionalIter2, 
          class _Distance>
inline _BidirectionalIter2 __copy_backward(_BidirectionalIter1 __first, 
                                           _BidirectionalIter1 __last, 
                                           _BidirectionalIter2 __result,
                                           bidirectional_iterator_tag,
                                           _Distance*) 
{
  while (__first != __last)
    *--__result = *--__last;
  return __result;
}

template <class _RandomAccessIter, class _BidirectionalIter, class _Distance>
inline _BidirectionalIter __copy_backward(_RandomAccessIter __first, 
                                          _RandomAccessIter __last, 
                                          _BidirectionalIter __result,
                                          random_access_iterator_tag,
                                          _Distance*)
{
  for (_Distance __n = __last - __first; __n > 0; --__n)
    *--__result = *--__last;
  return __result;
}

inline void*
__copy_trivial_backward(const void* __first, const void* __last, void* __result) {
  const ptrdiff_t _Num = (const char*)__last - (const char*)__first;
  return (_Num > 0) ? memmove((char*)__result - _Num, __first, _Num) : __result ;
}

template <class _InputIter, class _OutputIter>
inline _OutputIter __copy_ptrs(_InputIter __first, _InputIter __last, _OutputIter __result, __false_type) {
  return __copy(__first, __last, __result, 
                __ITERATOR_CATEGORY(__first, _InputIter), __DISTANCE_TYPE(__first, _InputIter));
}
template <class _InputIter, class _OutputIter>
inline _OutputIter __copy_ptrs(_InputIter __first, _InputIter __last, _OutputIter __result, __true_type) {
// we know they all pointers, so this cast is OK 
  return (_OutputIter)__copy_trivial(__first, __last, __result);  
}

template <class _InputIter, class _OutputIter>
inline _OutputIter __copy_aux(_InputIter __first, _InputIter __last, _OutputIter __result, __true_type) {
  return __copy_ptrs(__first, __last, __result, 
                     _IsOKToMemCpy(__VALUE_TYPE(__first, _InputIter), 
                                   __VALUE_TYPE(__result, _OutputIter))._Ret());
}

template <class _InputIter, class _OutputIter>
inline _OutputIter __copy_aux(_InputIter __first, _InputIter __last, _OutputIter __result, __false_type) {
  return __copy(__first, __last, __result, 
		__ITERATOR_CATEGORY(__first, _InputIter), __DISTANCE_TYPE(__first, _InputIter));
}

template <class _InputIter, class _OutputIter>
inline _OutputIter copy(_InputIter __first, _InputIter __last, _OutputIter __result) {
  __STL_DEBUG_CHECK(__check_range(__first, __last))
    return __copy_aux(__first, __last, __result, _BothPtrType< _InputIter, _OutputIter> :: _Ret());
}

template <class _InputIter, class _OutputIter>
inline _OutputIter __copy_backward_ptrs(_InputIter __first, _InputIter __last, _OutputIter __result, __false_type) {
  return __copy_backward(__first, __last, __result, __ITERATOR_CATEGORY(__first, _InputIter), __DISTANCE_TYPE(__first, _InputIter));
}
template <class _InputIter, class _OutputIter>
inline _OutputIter __copy_backward_ptrs(_InputIter __first, _InputIter __last, _OutputIter __result, __true_type) {
  return (_OutputIter)__copy_trivial_backward(__first, __last, __result);  
}

template <class _InputIter, class _OutputIter>
inline _OutputIter __copy_backward_aux(_InputIter __first, _InputIter __last, _OutputIter __result, __false_type) {
  return __copy_backward(__first, __last, __result, __ITERATOR_CATEGORY(__first,_InputIter), __DISTANCE_TYPE(__first, _InputIter));
}

template <class _InputIter, class _OutputIter>
inline _OutputIter __copy_backward_aux(_InputIter __first, _InputIter __last, _OutputIter __result, __true_type) {
  return __copy_backward_ptrs(__first, __last, __result,  
                              _IsOKToMemCpy(__VALUE_TYPE(__first, _InputIter), 
                                            __VALUE_TYPE(__result, _OutputIter))._Ret());
}

template <class _InputIter, class _OutputIter>
inline _OutputIter copy_backward(_InputIter __first, _InputIter __last, _OutputIter __result) {
  __STL_DEBUG_CHECK(__check_range(__first, __last))
    return __copy_backward_aux(__first, __last, __result, _BothPtrType< _InputIter, _OutputIter> :: _Ret() );
}

#if ! defined (__STL_CLASS_PARTIAL_SPECIALIZATION) && ! defined ( __STL_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS )
#define __SGI_STL_DECLARE_COPY_TRIVIAL(_Tp)                                \
inline _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result) \
{ return (_Tp*)__copy_trivial(__first, __last, __result); } \
inline _Tp* copy_backward(const _Tp* __first, const _Tp* __last, _Tp* __result) \
{ return (_Tp*)__copy_trivial_backward(__first, __last, __result); }

__SGI_STL_DECLARE_COPY_TRIVIAL(char)
# ifndef __STL_NO_SIGNED_BUILTINS
__SGI_STL_DECLARE_COPY_TRIVIAL(signed char)
# endif
__SGI_STL_DECLARE_COPY_TRIVIAL(unsigned char)
__SGI_STL_DECLARE_COPY_TRIVIAL(short)
__SGI_STL_DECLARE_COPY_TRIVIAL(unsigned short)
__SGI_STL_DECLARE_COPY_TRIVIAL(int)
__SGI_STL_DECLARE_COPY_TRIVIAL(unsigned int)
__SGI_STL_DECLARE_COPY_TRIVIAL(long)
__SGI_STL_DECLARE_COPY_TRIVIAL(unsigned long)
#if !defined(__STL_NO_WCHAR_T) && !defined (__STL_WCHAR_T_IS_USHORT) 
__SGI_STL_DECLARE_COPY_TRIVIAL(wchar_t)
#endif
#ifdef _STL_LONG_LONG
__SGI_STL_DECLARE_COPY_TRIVIAL(long long)
__SGI_STL_DECLARE_COPY_TRIVIAL(unsigned long long)
#endif 
__SGI_STL_DECLARE_COPY_TRIVIAL(float)
__SGI_STL_DECLARE_COPY_TRIVIAL(double)
# ifndef __STL_NO_LONG_DOUBLE
__SGI_STL_DECLARE_COPY_TRIVIAL(long double)
# endif
#undef __SGI_STL_DECLARE_COPY_TRIVIAL
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

//--------------------------------------------------
// copy_n (not part of the C++ standard)

template <class _InputIter, class _Size, class _OutputIter>
__STL_INLINE_LOOP 
pair<_InputIter, _OutputIter> __copy_n(_InputIter __first, _Size __count,
                                       _OutputIter __result,
                                       input_iterator_tag) {
  for ( ; __count > 0; --__count) {
    *__result = *__first;
    ++__first;
    ++__result;
  }
  return pair<_InputIter, _OutputIter>(__first, __result);
}

template <class _RAIter, class _Size, class _OutputIter>
inline pair<_RAIter, _OutputIter>
__copy_n(_RAIter __first, _Size __count,
         _OutputIter __result,
         random_access_iterator_tag) {
  _RAIter __last = __first + __count;
  return pair<_RAIter, _OutputIter>(__last, copy(__first, __last, __result));
}

template <class _InputIter, class _Size, class _OutputIter>
inline pair<_InputIter, _OutputIter>
__copy_n(_InputIter __first, _Size __count, _OutputIter __result) {
  __STL_FIX_LITERAL_BUG(__first)
  return __copy_n(__first, __count, __result, __ITERATOR_CATEGORY(__first, _InputIter));
}

template <class _InputIter, class _Size, class _OutputIter>
inline pair<_InputIter, _OutputIter>
copy_n(_InputIter __first, _Size __count, _OutputIter __result) {
  __STL_FIX_LITERAL_BUG(__first)
  return __copy_n(__first, __count, __result, __ITERATOR_CATEGORY(__first, _InputIter));
}

//--------------------------------------------------
// fill and fill_n


template <class _ForwardIter, class _Tp>
__STL_INLINE_LOOP
void fill(_ForwardIter __first, _ForwardIter __last, const _Tp& __value) {
  __STL_DEBUG_CHECK(__check_range(__first, __last))
  for ( ; __first != __last; ++__first)
    *__first = __value;
}

template <class _OutputIter, class _Size, class _Tp>
__STL_INLINE_LOOP
_OutputIter fill_n(_OutputIter __first, _Size __n, const _Tp& __value) {
  __STL_FIX_LITERAL_BUG(__first)
  for ( ; __n > 0; --__n, ++__first)
    *__first = __value;
  return __first;
}


// Specialization: for one-byte types we can use memset.

inline void fill(unsigned char* __first, unsigned char* __last,
                 const unsigned char& __value) {
  unsigned char __tmp = __value;
  memset(__first, __tmp, __last - __first);
}
# ifndef __STL_NO_SIGNED_BUILTINS
inline void fill(signed char* __first, signed char* __last,
                 const signed char& __value) {
  signed char __tmp = __value;
  memset(__first, __STATIC_CAST(unsigned char,__tmp), __last - __first);
}
# endif
inline void fill(char* __first, char* __last, const char& __value) {
  char __tmp = __value;
  memset(__first, __STATIC_CAST(unsigned char,__tmp), __last - __first);
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Size>
inline unsigned char* fill_n(unsigned char* __first, _Size __n,
                             const unsigned char& __value) {
  fill(__first, __first + __n, __value);
  return __first + __n;
}

template <class _Size>
inline signed char* fill_n(char* __first, _Size __n,
                           const signed char& __value) {
  fill(__first, __first + __n, __value);
  return __first + __n;
}

template <class _Size>
inline char* fill_n(char* __first, _Size __n, const char& __value) {
  fill(__first, __first + __n, __value);
  return __first + __n;
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */


//--------------------------------------------------
// equal and mismatch

template <class _InputIter1, class _InputIter2>
__STL_INLINE_LOOP
pair<_InputIter1, _InputIter2> mismatch(_InputIter1 __first1,
                                        _InputIter1 __last1,
                                        _InputIter2 __first2) {
  __STL_FIX_LITERAL_BUG(__first2)
  __STL_DEBUG_CHECK(__check_range(__first1, __last1))
  while (__first1 != __last1 && *__first1 == *__first2) {
    ++__first1;
    ++__first2;
  }
  return pair<_InputIter1, _InputIter2>(__first1, __first2);
}

template <class _InputIter1, class _InputIter2, class _BinaryPredicate>
__STL_INLINE_LOOP
pair<_InputIter1, _InputIter2> mismatch(_InputIter1 __first1,
                                        _InputIter1 __last1,
                                        _InputIter2 __first2,
                                        _BinaryPredicate __binary_pred) {
  __STL_FIX_LITERAL_BUG(__first2)
  __STL_DEBUG_CHECK(__check_range(__first1, __last1))
  while (__first1 != __last1 && __binary_pred(*__first1, *__first2)) {
    ++__first1;
    ++__first2;
  }
  return pair<_InputIter1, _InputIter2>(__first1, __first2);
}

template <class _InputIter1, class _InputIter2>
__STL_INLINE_LOOP
bool equal(_InputIter1 __first1, _InputIter1 __last1,
                  _InputIter2 __first2) {
  __STL_FIX_LITERAL_BUG(__first1) __STL_FIX_LITERAL_BUG(__last1)  __STL_FIX_LITERAL_BUG(__first2)
  __STL_DEBUG_CHECK(__check_range(__first1, __last1))
  for ( ; __first1 != __last1; ++__first1, ++__first2)
    if (!(*__first1 == *__first2))
      return false;
  return true;
}

template <class _InputIter1, class _InputIter2, class _BinaryPredicate>
__STL_INLINE_LOOP
bool equal(_InputIter1 __first1, _InputIter1 __last1,
                  _InputIter2 __first2, _BinaryPredicate __binary_pred) {
  __STL_FIX_LITERAL_BUG(__first2)
  __STL_DEBUG_CHECK(__check_range(__first1, __last1))
  for ( ; __first1 != __last1; ++__first1, ++__first2)
    if (!__binary_pred(*__first1, *__first2))
      return false;
  return true;
}

//--------------------------------------------------
// lexicographical_compare and lexicographical_compare_3way.
// (the latter is not part of the C++ standard.)

template <class _InputIter1, class _InputIter2>
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2);

template <class _InputIter1, class _InputIter2, class _Compare>
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2,
                             _Compare __comp);

inline bool 
lexicographical_compare(const unsigned char* __first1,
                        const unsigned char* __last1,
                        const unsigned char* __first2,
                        const unsigned char* __last2)
{
  const size_t __len1 = __last1 - __first1;
  const size_t __len2 = __last2 - __first2;
  __STL_DEBUG_CHECK(__check_range(__first1, __last1))
  __STL_DEBUG_CHECK(__check_range(__first2, __last2))

  const int __result = memcmp(__first1, __first2, __STL_MIN (__len1, __len2));
  return __result != 0 ? (__result < 0) : (__len1 < __len2);
}


# if !(CHAR_MAX == SCHAR_MAX)
inline bool lexicographical_compare(const char* __first1, const char* __last1,
                                    const char* __first2, const char* __last2)
{
  __STL_DEBUG_CHECK(__check_range(__first1, __last1)) 
  __STL_DEBUG_CHECK(__check_range(__first2, __last2))

  return lexicographical_compare((const unsigned char*) __first1,
                                 (const unsigned char*) __last1,
                                 (const unsigned char*) __first2,
                                 (const unsigned char*) __last2);
}
#endif /* CHAR_MAX == SCHAR_MAX */

# ifndef __STL_NO_EXTENSIONS

template <class _InputIter1, class _InputIter2>
int __lexicographical_compare_3way(_InputIter1 __first1, _InputIter1 __last1,
                                   _InputIter2 __first2, _InputIter2 __last2);

inline int
__lexicographical_compare_3way(const unsigned char* __first1,
                               const unsigned char* __last1,
                               const unsigned char* __first2,
                               const unsigned char* __last2)
{
  const ptrdiff_t __len1 = __last1 - __first1;
  const ptrdiff_t __len2 = __last2 - __first2;
  const int __result = memcmp(__first1, __first2, __STL_MIN (__len1, __len2));
  return __result != 0 ? __result 
                       : (__len1 == __len2 ? 0 : (__len1 < __len2 ? -1 : 1));
}


# if !(CHAR_MAX == SCHAR_MAX)
inline int 
__lexicographical_compare_3way(const char* __first1, const char* __last1,
                               const char* __first2, const char* __last2)
{
  return __lexicographical_compare_3way((const unsigned char*) __first1,
                                        (const unsigned char*) __last1,
                                        (const unsigned char*) __first2,
                                        (const unsigned char*) __last2);
}
# endif

template <class _InputIter1, class _InputIter2>
int lexicographical_compare_3way(_InputIter1 __first1, _InputIter1 __last1,
                                 _InputIter2 __first2, _InputIter2 __last2);

# endif /* EXTENSIONS */

// count
template <class _InputIter, class _Tp>
__STL_INLINE_LOOP __STL_DIFFERENCE_TYPE(_InputIter)
count(_InputIter __first, _InputIter __last, const _Tp& __value) {
  __STL_DEBUG_CHECK(__check_range(__first, __last))
  __STL_DIFFERENCE_TYPE(_InputIter) __n = 0;
  for ( ; __first != __last; ++__first)
    if (*__first == __value)
      ++__n;
  return __n;
}

// find and find_if. Note find may be expressed in terms of find_if if appropriate binder was available.
template <class _InputIter, class _Tp>
_InputIter find(_InputIter __first, _InputIter __last, const _Tp& __val);
template <class _InputIter, class _Predicate>
_InputIter find_if(_InputIter __first, _InputIter __last, _Predicate __pred);

// search.
template <class _ForwardIter1, class _ForwardIter2, class _BinaryPred>
_ForwardIter1 search(_ForwardIter1 __first1, _ForwardIter1 __last1,
                     _ForwardIter2 __first2, _ForwardIter2 __last2, _BinaryPred  __predicate);

// find_first_of
template <class _InputIter, class _ForwardIter, class _BinaryPredicate>
_InputIter __find_first_of(_InputIter __first1, _InputIter __last1,
                           _ForwardIter __first2, _ForwardIter __last2,
                           _BinaryPredicate __comp);

template <class _ForwardIter1, class _ForwardIter2, 
          class _BinaryPredicate>
_ForwardIter1 
find_end(_ForwardIter1 __first1, _ForwardIter1 __last1, 
         _ForwardIter2 __first2, _ForwardIter2 __last2,
         _BinaryPredicate __comp);

// replace
template <class _ForwardIter, class _Tp>
__STL_INLINE_LOOP void 
replace(_ForwardIter __first, _ForwardIter __last,
        const _Tp& __old_value, const _Tp& __new_value) {
  __STL_DEBUG_CHECK(__check_range(__first, __last))
  for ( ; __first != __last; ++__first)
    if (*__first == __old_value)
      *__first = __new_value;
}

template <class _ForwardIter, class _Tp, class _Compare, class _Distance>
_ForwardIter __lower_bound(_ForwardIter __first, _ForwardIter __last,
                              const _Tp& __val, _Compare __comp, _Distance*);

__STL_END_NAMESPACE

# if !defined (__STL_LINK_TIME_INSTANTIATION)
#  include <stl/_algobase.c>
# endif

#endif /* __SGI_STL_INTERNAL_ALGOBASE_H */

// Local Variables:
// mode:C++
// End:

