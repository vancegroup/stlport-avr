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

#ifndef _STLP_VOID_PTR_TRAITS_H
#define _STLP_VOID_PTR_TRAITS_H

/*
 * Little struct traits to cast any qualified pointer type to void*
 * and reverse. This struct is only defined for pointer types and 
 * do not use the STLport cast macro as a compiler that support
 * partial template specialization can't not support the C++ cast
 * correctly
 */

/*
 * Base struct to deal with qualifiers
 */

template <class _Tp>
struct __void_ptr_traits_cv {
  typedef void* void_cv_type;

  inline static void * cast(void *__ptr) {
    return __ptr;
  }

  inline static void ** ite_cast(void **__ptr) {
    return __ptr;
  }

  inline static void *const* const_ite_cast(void *const*__ptr) {
    return __ptr;
  }

  inline static void *& ref_cast(void *&__ref) {
    return __ref;
  }
};

template <class _VoidCVType>
struct __void_ptr_traits_cv_base {
  typedef _VoidCVType* void_cv_type;

  inline static void * cast(void_cv_type __ptr) {
    return const_cast<void*>(__ptr);
  }

  inline static void ** ite_cast(void_cv_type *__ptr) {
    return const_cast<void **>(__ptr);
  }

  inline static void *const* const_ite_cast(void_cv_type const*__ptr) {
    return const_cast<void *const*>(__ptr);
  }

  inline static void *& ref_cast(void_cv_type &__ref) {
    return const_cast<void *&>(__ref);
  }

  /*
   * The reverse versions
   */
  inline static void_cv_type cast(void *__ptr) {
    return const_cast<void_cv_type>(__ptr);
  }

  inline static void_cv_type * ite_cast(void **__ptr) {
    return const_cast<void_cv_type *>(__ptr);
  }

  inline static void_cv_type const* const_ite_cast(void *const*__ptr) {
    return const_cast<void_cv_type const*>(__ptr);
  }

  inline static void_cv_type & ref_cast(void *&__ref) {
    return const_cast<void_cv_type &>(__ref);
  }
};

template <class _Tp>
struct __void_ptr_traits_cv<_Tp const> : __void_ptr_traits_cv_base<void const>
{};

template <class _Tp>
struct __void_ptr_traits_cv<_Tp volatile> : __void_ptr_traits_cv_base<void volatile>
{};

template <class _Tp>
struct __void_ptr_traits_cv<_Tp const volatile> : __void_ptr_traits_cv_base<void const volatile>
{};

template <class _Tp>
struct __void_ptr_traits {
  typedef __void_ptr_traits_cv<_Tp> __cv;
  typedef typename __cv::void_cv_type void_cv_type;

  inline static _Tp * cast(void *__ptr) {
    return reinterpret_cast<_Tp *>(__cv::cast(__ptr));
  }

  inline static _Tp ** ite_cast(void **__ptr) {
    return reinterpret_cast<_Tp **>(__cv::ite_cast(__ptr));
  }

  inline static _Tp *const* const_ite_cast(void *const*__ptr) {
    return reinterpret_cast<_Tp *const*>(__cv::const_ite_cast(__ptr));
  }

  inline static _Tp *& ref_cast(void *&__ref) {
    return reinterpret_cast<_Tp *&>(__cv::ref_cast(__ref));
  }

  /*
   * Reverse versions
   */
  inline static void * cast(_Tp *__ptr) {
    return __cv::cast(reinterpret_cast<void_cv_type>(__ptr));
  }

  inline static void ** ite_cast(_Tp **__ptr) {
    return __cv::ite_cast(reinterpret_cast<void_cv_type *>(__ptr));
  }

  inline static void *const* const_ite_cast(_Tp *const*__ptr) {
    return __cv::const_ite_cast(reinterpret_cast<void_cv_type const*>(__ptr));
  }

  inline static void *& ref_cast(_Tp *&__ref) {
    return __cv::ref_cast(reinterpret_cast<void_cv_type &>(__ref));
  }
};

#endif /* _STLP_VOID_PTR_TRAITS_H */
