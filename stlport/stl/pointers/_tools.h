/*
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

#ifndef _STLP_POINTERS_SPEC_TOOLS_H
#define _STLP_POINTERS_SPEC_TOOLS_H

#ifndef _STLP_TYPE_TRAITS_H
#  include <stl/type_traits.h>
#endif

_STLP_BEGIN_NAMESPACE

//Some usefull declarations:
template <class _Tp> struct less;

_STLP_MOVE_TO_PRIV_NAMESPACE

/*
 * Since the compiler only allows at most one non-trivial
 * implicit conversion we can make use of a shim class to
 * be sure that functions below doesn't accept classes with
 * implicit pointer conversion operators
 */
struct _ConstVolatileVoidPointerShim
{ _ConstVolatileVoidPointerShim(const volatile void*); };

//The dispatch functions:
#if !defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
struct _VoidPointerShim
{ _VoidPointerShim(void*); };
struct _ConstVoidPointerShim
{ _ConstVoidPointerShim(const void*); };
struct _VolatileVoidPointerShim
{ _VolatileVoidPointerShim(volatile void*); };

template <class _Tp>
char _UseVoidPtrStorageType(const __false_type& /*POD*/, const _Tp&);
char _UseVoidPtrStorageType(const __true_type& /*POD*/, ...);
char* _UseVoidPtrStorageType(const __true_type& /*POD*/, _VoidPointerShim);

template <class _Tp>
char _UseConstVoidPtrStorageType(const __false_type& /*POD*/, const _Tp&);
char _UseConstVoidPtrStorageType(const __true_type& /*POD*/, ...);
char* _UseConstVoidPtrStorageType(const __true_type& /*POD*/, _ConstVoidPointerShim);

template <class _Tp>
char _UseVolatileVoidPtrStorageType(const __false_type& /*POD*/, const _Tp&);
char _UseVolatileVoidPtrStorageType(const __true_type& /*POD*/, ...);
char* _UseVolatileVoidPtrStorageType(const __true_type& /*POD*/, _VolatileVoidPointerShim);
#endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */

template <class _Tp>
char _UseConstVolatileVoidPtrStorageType(const __false_type& /*POD*/, const _Tp&);
char _UseConstVolatileVoidPtrStorageType(const __true_type& /*POD*/, ...);
char* _UseConstVolatileVoidPtrStorageType(const __true_type& /*POD*/, _ConstVolatileVoidPointerShim);

template <class _Tp>
struct _StorageType {
  typedef typename __type_traits<_Tp>::is_POD_type _PODType;
  static _Tp __null_rep();

  enum { use_const_volatile_void_ptr = (sizeof(_UseConstVolatileVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };

  //Here is the type switch:
#if !defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
  enum { use_void_ptr = (sizeof(_UseVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };
  enum { use_const_void_ptr = (sizeof(_UseConstVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };
  enum { use_volatile_void_ptr = (sizeof(_UseVolatileVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };

  //If the compiler do not support the iterator_traits structure we cannot wrapper
  //iterators pass to container template methods. The iterator dereferenced value
  //has to be storable without any cast in the chosen storage type. To guaranty
  //that the void pointer has to be correctly qualified.
  typedef typename __select<!use_const_volatile_void_ptr,
                            _Tp,
          typename __select<use_void_ptr,
                            void*,
          typename __select<use_const_void_ptr,
                            const void*,
          typename __select<use_volatile_void_ptr,
                            volatile void*,
                            const volatile void*>::_Ret >::_Ret >::_Ret >::_Ret _Type;
#else
  //With iterator_traits we can wrap passed iterators and make the necessary casts. We can always
  //use a simple void* storage type:
  typedef typename __select<use_const_volatile_void_ptr,
                            void*,
                            _Tp>::_Ret _Type;
#endif
};

template <class _Tp> struct __default_less;

template <class _Tp, class _Compare>
struct _AssocStorageTypes {
  typedef typename __type_traits<_Tp>::is_POD_type _PODType;
  static _Tp __null_rep();

  //We need to also check that the comparison functor used to instanciate the assoc container
  //is the default Standard less implementation:
  enum { is_default_less = _IsConvertible<_Compare, __default_less<less<_Tp> > >::value };

  enum { use_const_volatile_void_ptr = is_default_less &&
                                       (sizeof(_UseConstVolatileVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };

  //Here is the type switch:
#if !defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
  enum { use_void_ptr = is_default_less &&
                        (sizeof(_UseVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };
  enum { use_const_void_ptr = is_default_less &&
                              (sizeof(_UseConstVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };
  enum { use_volatile_void_ptr = is_default_less &&
                                 (sizeof(_UseVolatileVoidPtrStorageType(_PODType(), __null_rep())) == sizeof(char*)) };

  enum { use_less_storage_type = use_const_volatile_void_ptr || use_void_ptr || use_const_void_ptr || use_volatile_void_ptr };

  //If the compiler do not support the iterator_traits structure we cannot wrapper
  //iterators pass to container template methods. The iterator dereferenced value
  //has to be storable without any cast in the chosen storage type. To guaranty
  //that the void pointer has to be correctly qualified.
  typedef typename __select<!use_const_volatile_void_ptr,
                            _Tp,
          typename __select<use_void_ptr,
                            void*,
          typename __select<use_const_void_ptr,
                            const void*,
          typename __select<use_volatile_void_ptr,
                            volatile void*,
                            const volatile void*>::_Ret >::_Ret >::_Ret >::_Ret _KeyStorageType;
#else
  enum { use_less_storage_type = use_const_volatile_void_ptr };

  //With iterator_traits we can wrap passed iterators and make the necessary casts. We can always
  //use a simple void* storage type:
  typedef typename __select<use_const_volatile_void_ptr,
                            void*,
                            _Tp>::_Ret _KeyStorageType;
#endif

  typedef typename __select<use_less_storage_type,
                            less<_KeyStorageType>,
                            _Compare>::_Ret _CompareStorageType;
};


#if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
/*
 * Base struct to deal with qualifiers
 */
template <class _Tp>
struct _VoidCastTraitsAux {
  typedef void* void_cv_type;

  inline static void ** uncv_ptr(void **__ptr)
  { return __ptr; }
  inline static void *const* uncv_cptr(void *const*__ptr)
  { return __ptr; }
  inline static void *** uncv_pptr(void ***__ptr)
  { return __ptr; }
  inline static void *& uncv_ref(void *&__ref)
  { return __ref; }
  inline static void * const& uncv_cref(void * const&__ref)
  { return __ref; }
  inline static void ** cv_ptr(void **__ptr)
  { return __ptr; }
  inline static void *const* cv_cptr(void *const*__ptr)
  { return __ptr; }
  inline static void *** cv_pptr(void ***__ptr)
  { return __ptr; }
  inline static void *& cv_ref(void *&__ref)
  { return __ref; }
  inline static void * const& cv_cref(void * const&__ref)
  { return __ref; }
};

template <class _VoidCVType>
struct _VoidCastTraitsAuxBase {
  typedef _VoidCVType* void_cv_type;

  inline static void ** uncv_ptr(void_cv_type *__ptr)
  { return __CONST_CAST(void **, __ptr); }
  inline static void *const* uncv_cptr(void_cv_type const*__ptr)
  { return __CONST_CAST(void *const*, __ptr); }
  inline static void *** uncv_pptr(void_cv_type **__ptr)
  { return __CONST_CAST(void***, __ptr); }
  inline static void *& uncv_ref(void_cv_type &__ref)
  { return __CONST_CAST(void *&, __ref); }
  inline static void * const& uncv_cref(void_cv_type const& __ptr)
  { return __CONST_CAST(void* const&, __ptr); }
  // The reverse versions
  inline static void_cv_type * cv_ptr(void **__ptr)
  { return __CONST_CAST(void_cv_type *, __ptr); }
  inline static void_cv_type const* cv_cptr(void *const*__ptr)
  { return __CONST_CAST(void_cv_type const*, __ptr); }
  inline static void_cv_type ** cv_pptr(void ***__ptr)
  { return __CONST_CAST(void_cv_type**, __ptr); }
  inline static void_cv_type & cv_ref(void *&__ref)
  { return __CONST_CAST(void_cv_type &, __ref); }
  inline static void_cv_type const& cv_cref(void * const&__ref)
  { return __CONST_CAST(void_cv_type const&, __ref); }
};

template <class _Tp>
struct _VoidCastTraitsAux<_Tp const*> : _VoidCastTraitsAuxBase<void const>
{};
template <class _Tp>
struct _VoidCastTraitsAux<_Tp volatile*> : _VoidCastTraitsAuxBase<void volatile>
{};
template <class _Tp>
struct _VoidCastTraitsAux<_Tp const volatile*> : _VoidCastTraitsAuxBase<void const volatile>
{};

template <class _Tp>
struct _VoidCastTraits {
  typedef _VoidCastTraitsAux<_Tp> cv_traits;
  typedef typename cv_traits::void_cv_type void_cv_type;

  inline static _Tp * to_value_type_ptr(void **__ptr)
  { return __REINTERPRET_CAST(_Tp *, cv_traits::cv_ptr(__ptr)); }
  inline static _Tp const* to_value_type_cptr(void *const*__ptr)
  { return __REINTERPRET_CAST(_Tp const*, cv_traits::cv_cptr(__ptr)); }
  inline static _Tp ** to_value_type_pptr(void ***__ptr)
  { return __REINTERPRET_CAST(_Tp **, cv_traits::cv_pptr(__ptr)); }
  inline static _Tp & to_value_type_ref(void *&__ref)
  { return __REINTERPRET_CAST(_Tp &, cv_traits::cv_ref(__ref)); }
  inline static _Tp const& to_value_type_cref(void * const& __ptr)
  { return __REINTERPRET_CAST(_Tp const&, cv_traits::cv_cref(__ptr)); }
  // Reverse versions
  inline static void* * to_storage_type_ptr(_Tp *__ptr)
  { return cv_traits::uncv_ptr(__REINTERPRET_CAST(void_cv_type *, __ptr)); }
  inline static void* const* to_storage_type_cptr(_Tp const*__ptr)
  { return cv_traits::uncv_cptr(__REINTERPRET_CAST(void_cv_type const*, __ptr)); }
  inline static void* ** to_storage_type_pptr(_Tp **__ptr)
  { return cv_traits::uncv_pptr(__REINTERPRET_CAST(void_cv_type **, __ptr)); }
  inline static void* & to_storage_type_ref(_Tp &__ref)
  { return cv_traits::uncv_ref(__REINTERPRET_CAST(void_cv_type &, __ref)); }
  inline static void* const& to_storage_type_cref(_Tp const& __ref)
  { return cv_traits::uncv_cref(__REINTERPRET_CAST(void_cv_type const&, __ref)); }
};

template <class _StorageT, class _ValueT>
struct _CastTraitsAux {
  typedef _StorageT storage_type;
  typedef _ValueT value_type;

  inline static value_type * to_value_type_ptr(storage_type *__ptr)
  { return __ptr; }
  inline static value_type const* to_value_type_cptr(storage_type const*__ptr)
  { return __ptr; }
  inline static value_type ** to_value_type_pptr(storage_type **__ptr)
  { return __ptr; }
  inline static value_type & to_value_type_ref(storage_type &__ref)
  { return __ref; }
  inline static value_type const& to_value_type_cref(storage_type const&__ref)
  { return __ref; }
  // Reverse versions
  inline static storage_type * to_storage_type_ptr(value_type *__ptr)
  { return __ptr; }
  inline static storage_type const* to_storage_type_cptr(value_type const*__ptr)
  { return __ptr; }
  inline static storage_type ** to_storage_type_pptr(value_type **__ptr)
  { return __ptr; }
  inline static storage_type & to_storage_type_ref(value_type &__ref)
  { return __ref; }
  inline static storage_type const& to_storage_type_cref(value_type const&__ref)
  { return __ref; }
};

template <class _ValueT>
struct _CastTraitsAux<void*, _ValueT> {
  typedef void* storage_type;
  typedef _ValueT value_type;
  typedef _VoidCastTraits<value_type> _CastAux;

  inline static value_type * to_value_type_ptr(storage_type *__ptr)
  { return _CastAux::to_value_type_ptr(__ptr); }
  inline static value_type const* to_value_type_cptr(storage_type const*__ptr)
  { return _CastAux::to_value_type_cptr(__ptr); }
  inline static value_type ** to_value_type_pptr(storage_type **__ptr)
  { return _CastAux::to_value_type_pptr(__ptr); }
  inline static value_type & to_value_type_ref(storage_type &__ref)
  { return _CastAux::to_value_type_ref(__ref); }
  inline static value_type const& to_value_type_cref(storage_type const& __val)
  { return _CastAux::to_value_type_cref(__val); }
  // Reverse versions
  inline static storage_type * to_storage_type_ptr(value_type *__ptr)
  { return _CastAux::to_storage_type_ptr(__ptr); }
  inline static storage_type const* to_storage_type_cptr(value_type const*__ptr)
  { return _CastAux::to_storage_type_cptr(__ptr); }
  inline static storage_type ** to_storage_type_pptr(value_type **__ptr)
  { return _CastAux::to_storage_type_pptr(__ptr); }
  inline static storage_type & to_storage_type_ref(value_type &__ref)
  { return _CastAux::to_storage_type_ref(__ref); }
  inline static storage_type const& to_storage_type_cref(value_type const& __ref)
  { return _CastAux::to_storage_type_cref(__ref); }
};

template <class _StorageT, class _ValueT>
struct _CastTraits {
  typedef _StorageT storage_type;
  typedef _ValueT value_type;
  typedef _CastTraitsAux<storage_type, value_type> _CastAux;

  inline static value_type * to_value_type_ptr(storage_type *__ptr)
  { return _CastAux::to_value_type_ptr(__ptr); }
  inline static value_type const* to_value_type_cptr(storage_type const*__ptr)
  { return _CastAux::to_value_type_cptr(__ptr); }
  inline static value_type ** to_value_type_pptr(storage_type **__ptr)
  { return _CastAux::to_value_type_pptr(__ptr); }
  inline static value_type & to_value_type_ref(storage_type &__ref)
  { return _CastAux::to_value_type_ref(__ref); }
  inline static value_type const& to_value_type_cref(storage_type const&__ref)
  { return _CastAux::to_value_type_cref(__ref); }
  // Reverse versions
  inline static storage_type * to_storage_type_ptr(value_type *__ptr)
  { return _CastAux::to_storage_type_ptr(__ptr); }
  inline static storage_type const* to_storage_type_cptr(value_type const*__ptr)
  { return _CastAux::to_storage_type_cptr(__ptr); }
  inline static storage_type ** to_storage_type_pptr(value_type **__ptr)
  { return _CastAux::to_storage_type_pptr(__ptr); }
  inline static storage_type & to_storage_type_ref(value_type &__ref)
  { return _CastAux::to_storage_type_ref(__ref); }
  inline static storage_type const& to_storage_type_cref(value_type const&__ref)
  { return _CastAux::to_storage_type_cref(__ref); }
};

#define _STLP_USE_ITERATOR_WRAPPER

template <class _StorageT, class _ValueT, class _Iterator>
struct _IteWrapper {
  typedef _CastTraits<_StorageT, _ValueT> cast_traits;
  typedef iterator_traits<_Iterator> _IteTraits;

  typedef typename _IteTraits::iterator_category iterator_category;
  typedef _StorageT value_type;
  typedef typename _IteTraits::difference_type difference_type;
  typedef value_type* pointer;
  typedef value_type const& const_reference;
  //This wrapper won't be used for input so to avoid surprise
  //the reference type will be a const reference:
  typedef const_reference reference;

  typedef _IteWrapper<_StorageT, _ValueT, _Iterator> _Self;

  _IteWrapper(_Iterator &__ite) : _M_ite(__ite) {}

  const_reference operator*() const { return cast_traits::to_storage_type_cref(*_M_ite); }

  _Self& operator= (_Self const& __rhs) {
    _M_ite = __rhs._M_ite;
    return *this;
  }

  _Self& operator++() {
    ++_M_ite;
    return *this;
  }

  _Self& operator--() {
    --_M_ite;
    return *this;
  }

  _Self& operator += (difference_type __offset) {
    _M_ite += __offset;
    return *this;
  }
  difference_type operator -(_Self const& __other) const {
    return _M_ite - __other._M_ite;
  }

  bool operator == (_Self const& __other) const {
    return _M_ite == __other._M_ite;
  }

  bool operator != (_Self const& __other) const {
    return _M_ite != __other._M_ite;
  }

  bool operator < (_Self const& __rhs) const {
    return _M_ite < __rhs._M_ite;
  }

private:
  _Iterator &_M_ite;
};

#else

/*
 * In this config the storage type is qualified in respect of the
 * value_type qualification. Simple reinterpret_cast are enough.
 */
template <class _StorageT, class _ValueT>
struct _CastTraits {
  typedef _StorageT storage_type;
  typedef _ValueT value_type;

  inline static value_type * to_value_type_ptr(storage_type *__ptr)
  { return __REINTERPRET_CAST(value_type*, __ptr); }
  inline static value_type const* to_value_type_cptr(storage_type const*__ptr)
  { return __REINTERPRET_CAST(value_type const*, __ptr); }
  inline static value_type ** to_value_type_pptr(storage_type **__ptr)
  { return __REINTERPRET_CAST(value_type **, __ptr); }
  inline static value_type & to_value_type_ref(storage_type &__ref)
  { return __REINTERPRET_CAST(value_type&, __ref); }
  inline static value_type const& to_value_type_cref(storage_type const&__ref)
  { return __REINTERPRET_CAST(value_type const&, __ref); }
  // Reverse versions
  inline static storage_type * to_storage_type_ptr(value_type *__ptr)
  { return __REINTERPRET_CAST(storage_type*, __ptr); }
  inline static storage_type const* to_storage_type_cptr(value_type const*__ptr)
  { return __REINTERPRET_CAST(storage_type const*, __ptr); }
  inline static storage_type ** to_storage_type_pptr(value_type **__ptr)
  { return __REINTERPRET_CAST(storage_type **, __ptr); }
  inline static storage_type & to_storage_type_ref(value_type &__ref)
  { return __REINTERPRET_CAST(storage_type&, __ref); }
  inline static storage_type const& to_storage_type_cref(value_type const&__ref)
  { return __REINTERPRET_CAST(storage_type const&, __ref); }
};

#endif

template <class _StorageT, class _ValueT, class _UnaryPredicate>
struct _UnaryPredWrapper {
  typedef _CastTraits<_StorageT, _ValueT> cast_traits;

  _UnaryPredWrapper (_UnaryPredicate const& __pred) : _M_pred(__pred) {}

  bool operator () (_StorageT const& __ref) const {
    return _M_pred(cast_traits::to_value_type_cref(__ref));
  }

private:
  _UnaryPredicate _M_pred;
};


template <class _StorageT, class _ValueT, class _BinaryPredicate>
struct _BinaryPredWrapper {
  typedef _CastTraits<_StorageT, _ValueT> cast_traits;

  _BinaryPredWrapper () {}
  _BinaryPredWrapper (_BinaryPredicate const& __pred) : _M_pred(__pred) {}

  _BinaryPredicate get_pred() const { return _M_pred; }

  bool operator () (_StorageT const& __fst, _StorageT const& __snd) const {
    return _M_pred(cast_traits::to_value_type_cref(__fst), cast_traits::to_value_type_cref(__snd));
  }

private:
  _BinaryPredicate _M_pred;
};

_STLP_MOVE_TO_STD_NAMESPACE

_STLP_END_NAMESPACE

#endif /* _STLP_POINTERS_SPEC_TOOLS_H */
