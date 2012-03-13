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

#ifndef _STLP_INTERNAL_ITERATOR_BASE_H
#define _STLP_INTERNAL_ITERATOR_BASE_H

#ifndef _STLP_CSTDDEF
#  include <cstddef>
#endif

_STLP_BEGIN_NAMESPACE

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Category, class _Tp, _STLP_DFL_TMPL_PARAM(_Distance,ptrdiff_t),
          _STLP_DFL_TMPL_PARAM(_Pointer,_Tp*), _STLP_DFL_TMPL_PARAM(_Reference,_Tp&) >
struct iterator {
  typedef _Category  iterator_category;
  typedef _Tp        value_type;
  typedef _Distance  difference_type;
  typedef _Pointer   pointer;
  typedef _Reference reference;
};
_STLP_TEMPLATE_NULL
struct iterator<output_iterator_tag, void, void, void, void> {
  typedef output_iterator_tag  iterator_category;
#ifdef _STLP_CLASS_PARTIAL_SPECIALIZATION
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;
#endif
};

#  if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
#    define _STLP_VALUE_TYPE(_It, _Tp)        (_STLP_TYPENAME _STLP_STD::iterator_traits< _Tp >::value_type*)0
#    if defined (__BORLANDC__) || defined (__SUNPRO_CC)
#      define _STLP_ITERATOR_CATEGORY(_It, _Tp) _STLP_STD::iterator_traits< _Tp >::iterator_category()
#    else
#      define _STLP_ITERATOR_CATEGORY(_It, _Tp) _STLP_TYPENAME _STLP_STD::iterator_traits< _Tp >::iterator_category()
#    endif
// #    define _STLP_IS_REF_TYPE_REAL_REF(_It, _Tp) _STLP_STD::is_reference< _STLP_TYPENAME _STLP_STD::iterator_traits< _Tp >::reference >::_Ret()
#  else
#    define _STLP_ITERATOR_CATEGORY(_It, _Tp)   _STLP_STD::__iterator_category(_It, _STLP_STD::is_pointer<_Tp>::type())
#    define _STLP_VALUE_TYPE(_It, _Tp)          _STLP_STD::__value_type(_It, _STLP_STD::is_pointer<_Tp>::type())
#    define _STLP_IS_REF_TYPE_REAL_REF(_It, _Tp) false_type()
#  endif

template <class _Iterator>
struct iterator_traits
{
    typedef typename _Iterator::difference_type   difference_type;
    typedef typename _Iterator::value_type        value_type;
    typedef typename _Iterator::pointer           pointer;
    typedef typename _Iterator::reference         reference;
    typedef typename _Iterator::iterator_category iterator_category;
};

template <class _Tp>
struct iterator_traits<_Tp*>
{
    typedef ptrdiff_t                  difference_type;
    typedef _Tp                        value_type;
    typedef _Tp*                       pointer;
    typedef _Tp&                       reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class _Tp>
struct iterator_traits<const _Tp*>
{
    typedef ptrdiff_t                  difference_type;
    typedef _Tp                        value_type;
    typedef const _Tp*                 pointer;
    typedef const _Tp&                 reference;
    typedef random_access_iterator_tag iterator_category;
};

// specialization for _Tp __far* ? What is platforms for?

_STLP_END_NAMESPACE
#include <stl/_ptrs_specialize.h>
_STLP_BEGIN_NAMESPACE

_STLP_MOVE_TO_PRIV_NAMESPACE

template <class _IteratorCategory>
struct __distance_aux
{
    template <class _Iterator>
    static typename iterator_traits<_Iterator>::difference_type _STLP_CALL distance(const _Iterator& __first, const _Iterator& __last)
      {
        typename iterator_traits<_Iterator>::difference_type __n = 0;
        for (_Iterator __it(__first); __it != __last; ++__it) {
          ++__n;
        }
        return __n;
      }
};

template <>
struct __distance_aux<typename _STLP_STD::random_access_iterator_tag>
{
    template <class _Iterator>
    static typename iterator_traits<_Iterator>::difference_type _STLP_CALL distance(const _Iterator& __first, const _Iterator& __last)
      { return __last - __first; }
};

_STLP_MOVE_TO_STD_NAMESPACE

template <class _Iterator>
inline
typename iterator_traits<_Iterator>::difference_type _STLP_CALL distance(_Iterator __first, _Iterator __last)
{ return _STLP_PRIV __distance_aux<typename iterator_traits<_Iterator>::iterator_category>::distance(__first, __last); }

// fbp: those are being used for iterator/const_iterator definitions everywhere
template <class _Tp>
struct _Nonconst_traits;

template <class _Tp>
struct _Const_traits {
  typedef _Tp value_type;
  typedef const _Tp&  reference;
  typedef const _Tp*  pointer;
  typedef _Const_traits<_Tp> _ConstTraits;
  typedef _Nonconst_traits<_Tp> _NonConstTraits;
};

template <class _Tp>
struct _Nonconst_traits {
  typedef _Tp value_type;
  typedef _Tp& reference;
  typedef _Tp* pointer;
  typedef _Const_traits<_Tp> _ConstTraits;
  typedef _Nonconst_traits<_Tp> _NonConstTraits;
};

/*
 * dums: A special iterator/const_iterator traits for set and multiset for which even
 * the iterator is not mutable
 */
template <class _Tp>
struct _Nonconst_Const_traits;

template <class _Tp>
struct _Const_Const_traits {
  typedef _Tp value_type;
  typedef const _Tp&  reference;
  typedef const _Tp*  pointer;
  typedef _Const_Const_traits<_Tp> _ConstTraits;
  typedef _Nonconst_Const_traits<_Tp> _NonConstTraits;
};

template <class _Tp>
struct _Nonconst_Const_traits {
  typedef _Tp value_type;
  typedef const _Tp& reference;
  typedef const _Tp* pointer;
  typedef _Const_Const_traits<_Tp> _ConstTraits;
  typedef _Nonconst_Const_traits<_Tp> _NonConstTraits;
};

/*
 * A macro to generate a new iterator traits from one of the
 * previous one. Changing the iterator traits type make iterators
 * from different containers not comparable.
 */
#define _STLP_CREATE_ITERATOR_TRAITS_BASE(Motif, Traits)        \
template <class _Tp>                                            \
struct _##Motif;                                                \
template <class _Tp>                                            \
struct _Const##Motif : public _STLP_STD::_Const_##Traits<_Tp> {  \
  typedef _Const##Motif<_Tp> _ConstTraits;                      \
  typedef _##Motif<_Tp> _NonConstTraits;                        \
};                                                              \
template <class _Tp>                                            \
struct _##Motif : public _STLP_STD::_Nonconst_##Traits<_Tp> {    \
  typedef _Const##Motif<_Tp> _ConstTraits;                      \
  typedef _##Motif<_Tp> _NonConstTraits;                        \
};

#define _STLP_CREATE_ITERATOR_TRAITS(Motif, Traits)             \
_STLP_MOVE_TO_PRIV_NAMESPACE                                    \
_STLP_CREATE_ITERATOR_TRAITS_BASE(Motif, Traits)                \
_STLP_MOVE_TO_STD_NAMESPACE

#define _STLP_CREATE_HASH_ITERATOR_TRAITS(Motif, Traits)        \
_STLP_MOVE_TO_PRIV_NAMESPACE                                    \
_STLP_CREATE_ITERATOR_TRAITS_BASE(NonLocal##Motif, Traits)      \
_STLP_CREATE_ITERATOR_TRAITS_BASE(Local##Motif, Traits)         \
template <class _Tp>                                            \
struct _##Motif {                                               \
  typedef _ConstNonLocal##Motif<_Tp> _ConstTraits;              \
  typedef _NonLocal##Motif<_Tp> _NonConstTraits;                \
  typedef _ConstLocal##Motif<_Tp> _ConstLocalTraits;            \
  typedef _Local##Motif<_Tp> _NonConstLocalTraits;              \
};                                                              \
_STLP_MOVE_TO_STD_NAMESPACE

/*
#  if defined (_STLP_BASE_TYPEDEF_BUG)
// this workaround is needed for SunPro 4.0.1
template <class _Traits>
struct __cnst_traits_aux : private _Traits {
  typedef typename _Traits::value_type value_type;
};
#  define __TRAITS_VALUE_TYPE(_Traits) __cnst_traits_aux<_Traits>::value_type
#  else
#  define __TRAITS_VALUE_TYPE(_Traits) _Traits::value_type
#  endif
*/

_STLP_MOVE_TO_PRIV_NAMESPACE

template <class _InputIter, class _Distance>
inline void _STLP_CALL
__advance(_InputIter& __i, _Distance __n, const input_iterator_tag &)
{ while (__n--) ++__i; }

// fbp : added output iterator tag variant
template <class _InputIter, class _Distance>
inline void _STLP_CALL
__advance(_InputIter& __i, _Distance __n, const output_iterator_tag &)
{ while (__n--) ++__i; }

#if defined (_STLP_NONTEMPL_BASE_MATCH_BUG)
template <class _ForwardIterator, class _Distance>
inline void _STLP_CALL
__advance(_ForwardIterator& i, _Distance n, const forward_iterator_tag &)
{ while (n--) ++i; }
#endif

template <class _BidirectionalIterator, class _Distance>
inline void _STLP_CALL
__advance(_BidirectionalIterator& __i, _Distance __n,
          const bidirectional_iterator_tag &) {
  if (__n > 0)
    while (__n--) ++__i;
  else
    while (__n++) --__i;
}

template <class _RandomAccessIterator, class _Distance>
inline void _STLP_CALL
__advance(_RandomAccessIterator& __i, _Distance __n,
          const random_access_iterator_tag &)
{ __i += __n; }

_STLP_MOVE_TO_STD_NAMESPACE

template <class _InputIterator, class _Distance>
inline void _STLP_CALL advance(_InputIterator& __i, _Distance __n)
{ _STLP_PRIV __advance(__i, __n, _STLP_ITERATOR_CATEGORY(__i, _InputIterator)); }

_STLP_END_NAMESPACE

#endif /* _STLP_INTERNAL_ITERATOR_BASE_H */


// Local Variables:
// mode:C++
// End:
