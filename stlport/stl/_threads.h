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

// WARNING: This is an internal header file, included by other C++
// standard library headers.  You should not attempt to use this header
// file directly.
// Stl_config.h should be included before this file.


#ifndef __SGI_STL_INTERNAL_THREADS_H
#define __SGI_STL_INTERNAL_THREADS_H

// Supported threading models are native SGI, pthreads, uithreads
// (similar to pthreads, but based on an earlier draft of the Posix
// threads standard), and Win32 threads.  Uithread support by Jochen
// Schlick, 1999, and Solaris threads generalized to them.

#ifndef __STL_CONFIG_H
#include <stl/_config.h>
#endif

# if ! defined (__STLPORT_CSTDDEF)
#  include <cstddef>
# endif

# if ! defined (__STLPORT_CSTDLIB)
#  include <cstdlib>
# endif

// On SUN, zero-initialization works just fine...
# ifdef __sun
# define __STL_MUTEX_INITIALIZER
# endif

# if defined(__STL_SGI_THREADS)
#  include <mutex.h>
// Hack for SGI o32 compilers.
#if !defined(__add_and_fetch) && \
    (__mips < 3 || !(defined (_ABIN32) || defined(_ABI64)))
#  define __add_and_fetch(__l,__v) add_then_test((unsigned long*)__l,__v)  
#  define __test_and_set(__l,__v)  test_and_set(__l,__v)
#endif /* o32 */

# if __mips < 3 || !(defined (_ABIN32) || defined(_ABI64))
#  define __STL_ATOMIC_EXCHANGE(__p, __q) test_and_set(__p, __q)
# else
#  define __STL_ATOMIC_EXCHANGE(__p, __q) __test_and_set((unsigned long*)__p, (unsigned long)__q)
# endif

#  define __STL_ATOMIC_INCREMENT(__x) __add_and_fetch(__x, 1)
#  define __STL_ATOMIC_DECREMENT(__x) __add_and_fetch(__x, (size_t) -1)
# elif defined(__STL_PTHREADS)
#  include <pthread.h>
#  if defined (PTHREAD_MUTEX_INITIALIZER) && ! defined (__STL_MUTEX_INITIALIZER)
#   define __STL_MUTEX_INITIALIZER = { PTHREAD_MUTEX_INITIALIZER }
#  endif
#   define __STL_PTHREAD_ATTR_DEFAULT 0
# elif defined(__STL_WIN32)

#  if !defined (__STLPORT_WINDOWS_H_INCLUDED) && ! defined (_WINDOWS_) && ! defined (__WINDOWS__)
#   if ! (defined ( __STL_MSVC ) || defined (__BORLANDC__) || defined (__ICL) || defined (__WATCOMC__) )
// #    define NOMINMAX
#    ifdef __STL_USE_MFC
#     include <afx.h>
#    else
#     include <windows.h>
#    endif
#   else 
// This section serves as a replacement for windows.h header for Visual C++
extern "C" {
#   if (defined(_M_MRX000) || defined(_M_ALPHA) \
       || (defined(_M_PPC) && (_MSC_VER >= 1000))) && !defined(RC_INVOKED)
#    define InterlockedIncrement       _InterlockedIncrement
#    define InterlockedDecrement       _InterlockedDecrement
#    define InterlockedExchange        _InterlockedExchange
#    define __STL_STDCALL
#   else
#    ifdef _MAC
#     define __STL_STDCALL _cdecl
#    else
#     define __STL_STDCALL __stdcall
#    endif
#   endif

__STL_IMPORT_DECLSPEC long __STL_STDCALL InterlockedIncrement(long*);
__STL_IMPORT_DECLSPEC long __STL_STDCALL InterlockedDecrement(long*);
__STL_IMPORT_DECLSPEC long __STL_STDCALL InterlockedExchange(long*, long);

__STL_IMPORT_DECLSPEC void __STL_STDCALL Sleep(unsigned long);
__STL_IMPORT_DECLSPEC void __STL_STDCALL OutputDebugStringA( const char* lpOutputString );

#    if defined (InterlockedIncrement)
#     pragma intrinsic(_InterlockedIncrement)
#     pragma intrinsic(_InterlockedDecrement)
#     pragma intrinsic(_InterlockedExchange)
#    endif
} /* extern "C" */

#   endif /* STL_MSVC */

// #   undef min
// #   undef max
#   define __STLPORT_WINDOWS_H_INCLUDED

#  endif /* _WINDOWS_ */

#  define __STL_ATOMIC_INCREMENT(__x)           InterlockedIncrement((long*)__x)
#  define __STL_ATOMIC_DECREMENT(__x)           InterlockedDecrement((long*)__x)
#  define __STL_ATOMIC_EXCHANGE(__x, __y)       InterlockedExchange((long*)__x, (long)__y)

# elif defined(__DECC) || defined(__DECCXX)
#  include <machine/builtins.h>
#  define __STL_ATOMIC_EXCHANGE __ATOMIC_EXCH_LONG
#  define __STL_ATOMIC_INCREMENT(__x, __y) __ATOMIC_ADD_LONG(__x, 1)
#  define __STL_ATOMIC_DECREMENT(__x, __y) __ATOMIC_ADD_LONG(__x, -1)
//# elif defined(__sun) && defined (__sparc) 
//	extern "C" unsigned int __stl_atomic_exchange(__stl_atomic_t * __x, __stl_atomic_t __v);
//	extern "C" void __stl_atomic_decrement(__stl_atomic_t* i);
//	extern "C" void __stl_atomic_increment(__stl_atomic_t* i);
# elif defined (__STL_UITHREADS)
// this inclusion is potential hazard to bring up all sorts
// of old-style headers. Let's assume vendor already know how
// to deal with that.
#  include <time.h>
#  include <synch.h>
#  include <cstdio>
#  include <cwchar>



#elif defined(__STL_OS2THREADS)
  // This section serves to replace os2.h for VisualAge C++
  typedef unsigned long ULONG;
  #ifndef __HEV__  /* INCL_SEMAPHORE may also define HEV */
    #define __HEV__
    typedef ULONG HEV;
    typedef HEV*  PHEV;
  #endif
  typedef ULONG APIRET;
  typedef ULONG HMTX;
  typedef HMTX*  PHMTX;
  typedef const char*  PCSZ;
  typedef ULONG BOOL32;
  APIRET _System DosCreateMutexSem(PCSZ pszName, PHEV phev, ULONG
flAttr, BOOL32 fState);
  APIRET _System DosRequestMutexSem(HMTX hmtx, ULONG ulTimeout);
  APIRET _System DosReleaseMutexSem(HMTX hmtx);
  APIRET _System DosCloseMutexSem(HMTX hmtx);
# define __STL_MUTEX_INITIALIZER = { 0 };

# endif

# ifndef __STL_MUTEX_INITIALIZER
#   if defined(__STL_ATOMIC_EXCHANGE)
#     define __STL_MUTEX_INITIALIZER = { 0 }
#   elif defined(__STL_UITHREADS)
#     define __STL_MUTEX_INITIALIZER = { DEFAULTMUTEX }
#   else
#     define __STL_MUTEX_INITIALIZER
#   endif
# endif

__STL_BEGIN_NAMESPACE

# if defined (__STL_WIN32) || defined (__sgi)
  typedef long __stl_atomic_t;
# else
  typedef size_t __stl_atomic_t;
#endif  

// Helper struct.  This is a workaround for various compilers that don't
// handle static variables in inline functions properly.
template <int __inst>
struct _STL_mutex_spin {
  enum { __low_max = 30, __high_max = 1000 };
  // Low if we suspect uniprocessor, high for multiprocessor.
  static unsigned __max;
  static unsigned __last;
  // #if defined(__STL_SGI_THREADS) || defined(__STL_WIN32THREADS)
  static void __STL_CALL _M_do_lock(volatile __stl_atomic_t* __lock);
  static void __STL_CALL _S_nsec_sleep(int __log_nsec);
  // # endif
};


// Locking class.  Note that this class *does not have a constructor*.
// It must be initialized either statically, with __STL_MUTEX_INITIALIZER,
// or dynamically, by explicitly calling the _M_initialize member function.
// (This is similar to the ways that a pthreads mutex can be initialized.)
// There are explicit member functions for acquiring and releasing the lock.

// There is no constructor because static initialization is essential for
// some uses, and only a class aggregate (see section 8.5.1 of the C++
// standard) can be initialized that way.  That means we must have no
// constructors, no base classes, no virtual functions, and no private or
// protected members.

// For non-static cases, clients should use  _STL_mutex.

struct __STL_CLASS_DECLSPEC _STL_mutex_base
{
#if defined(__STL_ATOMIC_EXCHANGE)
  // It should be relatively easy to get this to work on any modern Unix.
  volatile __stl_atomic_t _M_lock;
#endif

#if defined(__STL_SGI_THREADS) || defined(__STL_WIN32THREADS)

  inline void _M_initialize() { _M_lock=0; }
  inline void _M_destroy() {}

  void _M_acquire_lock() {
    _STL_mutex_spin<0>::_M_do_lock(&_M_lock);
  }

  inline void _M_release_lock() {
    volatile __stl_atomic_t* __lock = &_M_lock;
#   if defined(__STL_SGI_THREADS) && defined(__GNUC__) && __mips >= 3
        asm("sync");
        *__lock = 0;
#   elif defined(__STL_SGI_THREADS) && __mips >= 3 \
	 && (defined (_ABIN32) || defined(_ABI64))
        __lock_release(__lock);
#   else
        *__lock = 0;
        // This is not sufficient on many multiprocessors, since
        // writes to protected variables and the lock may be reordered.
#   endif
  }

#elif defined(__STL_PTHREADS)
  pthread_mutex_t _M_lock;
  inline void _M_initialize() {
    pthread_mutex_init(&_M_lock,__STL_PTHREAD_ATTR_DEFAULT);
  }
  inline void _M_destroy() {
    pthread_mutex_destroy(&_M_lock);
  }
  inline void _M_acquire_lock() { 
#if defined ( __hpux ) && ! defined (PTHREAD_MUTEX_INITIALIZER)
    if (!_M_lock.field1)  _M_initialize();
#endif
    pthread_mutex_lock(&_M_lock); 
  }
  inline void _M_release_lock() { pthread_mutex_unlock(&_M_lock); }
  
#elif defined (__STL_UITHREADS)
  mutex_t _M_lock;
  inline void _M_initialize() {
    mutex_init(&_M_lock,0,NULL);	
  }
  inline void _M_destroy() {
    mutex_destroy(&_M_lock);
  }
  inline void _M_acquire_lock() { mutex_lock(&_M_lock); }
  inline void _M_release_lock() { mutex_unlock(&_M_lock); }

#elif defined(__STL_OS2THREADS)
  HMTX _M_lock;
  inline void _M_initialize() { DosCreateMutexSem(NULL, &_M_lock, 0,
false); }
  inline void _M_destroy() { DosCloseMutexSem(_M_lock); }
  inline void _M_acquire_lock() {
    if(!_M_lock) _M_initialize();
    DosRequestMutexSem(_M_lock, -1);
  }
  inline void _M_release_lock() { DosReleaseMutexSem(_M_lock); }
#else /* No threads */
  inline void _M_initialize() {}
  inline void _M_destroy() {}
  inline void _M_acquire_lock() {}
  inline void _M_release_lock() {}
#endif
};

// This class could be just a smart pointer, but we do want to keep 
// WIN32 optimized at a maximum
#if (defined(__sgi)) || defined(__STL_WIN32)
struct __STL_CLASS_DECLSPEC _STL_mutex_indirect : _STL_mutex_base {};
#else
struct __STL_CLASS_DECLSPEC _STL_mutex_indirect
{
  void*    _M_lock;

# if defined(__STL_PTHREADS)
  inline void _M_initialize() {
    _M_lock = (void*)__STL_VENDOR_CSTD::calloc(1,sizeof(pthread_mutex_t));
    pthread_mutex_init((pthread_mutex_t*)_M_lock,__STL_PTHREAD_ATTR_DEFAULT);
  }
  inline void _M_destroy() {
    pthread_mutex_destroy((pthread_mutex_t*)_M_lock);
    free((char*)_M_lock);
  }
  inline void _M_acquire_lock() { 
    pthread_mutex_lock((pthread_mutex_t*)_M_lock); 
  }
  inline void _M_release_lock() { pthread_mutex_unlock((pthread_mutex_t*)_M_lock); }
  
# elif defined (__STL_UITHREADS)
  inline void _M_initialize() {
    _M_lock = (void*)calloc(1,sizeof(mutex_t));
    mutex_init((mutex_t*)_M_lock,0,NULL);	
  }
  inline void _M_destroy() {
    mutex_destroy((mutex_t*)_M_lock);
    free((char*)_M_lock);
  }
  inline void _M_acquire_lock() { mutex_lock((mutex_t*)_M_lock); }
  inline void _M_release_lock() { mutex_unlock((mutex_t*)_M_lock); }

#elif defined(__STL_OS2THREADS)
  inline void _M_initialize() {
    _M_lock = (void*)calloc(1,sizeof(HMTX));
    DosCreateMutexSem(NULL, (HMTX*)_M_lock, 0, false);
  }
  inline void _M_destroy() {
    DosCloseMutexSem(*(HMTX*)_M_lock);
    free((char*)_M_lock);
  }
  inline void _M_acquire_lock() {
    if(!_M_lock) _M_initialize();
    DosRequestMutexSem(*(HMTX*)_M_lock, -1);
  }
  inline void _M_release_lock() { DosReleaseMutexSem(*(HMTX*)_M_lock); }
# else /* No threads */
  inline void _M_initialize() {}
  inline void _M_destroy() {}
  inline void _M_acquire_lock() {}
  inline void _M_release_lock() {}
# endif
};
#endif

// Locking class.  The constructor initializes the lock, the destructor destroys it.
// Well - behaving class, does not need static initializer

struct __STL_CLASS_DECLSPEC _STL_mutex : public _STL_mutex_indirect {
  inline _STL_mutex () {
    _M_initialize();
  }

  inline ~_STL_mutex () {
    _M_destroy();
  }
private:
  _STL_mutex(const _STL_mutex&);
  void operator=(const _STL_mutex&);
};

// Class _Refcount_Base provides a type, __stl_atomic_t, a data member,
// _M_ref_count, and member functions _M_incr and _M_decr, which perform
// atomic preincrement/predecrement.  The constructor initializes 
// _M_ref_count.
struct __STL_CLASS_DECLSPEC _Refcount_Base
{
  // The data member _M_ref_count
  volatile __stl_atomic_t _M_ref_count;

# if !defined (__STL_WIN32) && !defined (__sgi)
  _STL_mutex _M_mutex;
# endif

  // Constructor
  _Refcount_Base(__stl_atomic_t __n) : _M_ref_count(__n) {}

  // _M_incr and _M_decr
# if defined (__STL_THREADS) && defined ( __STL_ATOMIC_EXCHANGE )
   void _M_incr() { __STL_ATOMIC_INCREMENT((__stl_atomic_t*)&_M_ref_count); }
  __stl_atomic_t _M_decr() { return __STL_ATOMIC_DECREMENT((__stl_atomic_t*)&_M_ref_count); }
# elif defined(__STL_PTHREADS) || defined (__STL_UITHREADS) || defined (__STL_OS2THREADS)
  void _M_incr() {
    _M_mutex._M_acquire_lock();
    ++_M_ref_count;
    _M_mutex._M_release_lock();
  }
  __stl_atomic_t _M_decr() {
    _M_mutex._M_acquire_lock();
    volatile __stl_atomic_t __tmp = --_M_ref_count;
    _M_mutex._M_release_lock();
    return __tmp;
  }
# else  /* No threads */
  void _M_incr() { ++_M_ref_count; }
  __stl_atomic_t _M_decr() { return --_M_ref_count; }
# endif
};

// Atomic swap on unsigned long
// This is guaranteed to behave as though it were atomic only if all
// possibly concurrent updates use _Atomic_swap.
// In some cases the operation is emulated with a lock.
# if defined (__STL_THREADS) && defined ( __STL_ATOMIC_EXCHANGE )
inline __stl_atomic_t _Atomic_swap(volatile __stl_atomic_t * __p, __stl_atomic_t __q) {
  return (__stl_atomic_t) __STL_ATOMIC_EXCHANGE(__p,__q);
}
# elif defined(__STL_PTHREADS) || defined (__STL_UITHREADS)  || defined (__STL_OS2THREADS)
// We use a template here only to get a unique initialized instance.
template<int __dummy>
struct _Swap_lock_struct {
  static _STL_STATIC_MUTEX _S_swap_lock;
};


// This should be portable, but performance is expected
// to be quite awful.  This really needs platform specific
// code.
inline __stl_atomic_t _Atomic_swap(__stl_atomic_t * __p, __stl_atomic_t __q) {
  _Swap_lock_struct<0>::_S_swap_lock._M_acquire_lock();
  __stl_atomic_t __result = *__p;
  *__p = __q;
  _Swap_lock_struct<0>::_S_swap_lock._M_release_lock();
  return __result;
}
# else
/* no threads */
static inline __stl_atomic_t  __STL_CALL
_Atomic_swap(__stl_atomic_t * __p, __stl_atomic_t __q) {
  __stl_atomic_t __result = *__p;
  *__p = __q;
  return __result;
}
# endif

// A locking class that uses _STL_STATIC_MUTEX.  The constructor takes
// a reference to an _STL_STATIC_MUTEX, and acquires a lock.  The destructor
// releases the lock.
// It's not clear that this is exactly the right functionality.
// It will probably change in the future.

struct __STL_CLASS_DECLSPEC _STL_auto_lock
{
  _STL_STATIC_MUTEX& _M_lock;
  
  _STL_auto_lock(_STL_STATIC_MUTEX& __lock) : _M_lock(__lock)
    { _M_lock._M_acquire_lock(); }
  ~_STL_auto_lock() { _M_lock._M_release_lock(); }

private:
  void operator=(const _STL_auto_lock&);
  _STL_auto_lock(const _STL_auto_lock&);
};

__STL_END_NAMESPACE

# if !defined (__STL_LINK_TIME_INSTANTIATION)
#  include <stl/_threads.c>
# endif

#endif /* __SGI_STL_INTERNAL_THREADS_H */

// Local Variables:
// mode:C++
// End:
