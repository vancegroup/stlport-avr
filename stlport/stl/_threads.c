/*
 *
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
#ifndef _STLP_THREADS_C
#define _STLP_THREADS_C

# if defined (_STLP_EXPOSE_GLOBALS_IMPLEMENTATION)

# if defined(_STLP_SGI_THREADS)
#  include <time.h>
# elif defined (_STLP_UNIX)
#  include <ctime>
# endif

_STLP_BEGIN_NAMESPACE

# if ( _STLP_STATIC_TEMPLATE_DATA > 0 )
 
#  if !defined ( _STLP_ATOMIC_EXCHANGE ) && (defined (_STLP_PTHREADS) || defined (_STLP_UITHREADS) || defined (_STLP_OS2THREADS))
template<int __dummy>
_STL_STATIC_MUTEX
_Swap_lock_struct<__dummy>::_S_swap_lock _STLP_MUTEX_INITIALIZER;
#  endif

template <int __inst>
unsigned _STL_mutex_spin<__inst>::__max = _STL_mutex_spin<__inst>::__low_max;

template <int __inst>
unsigned _STL_mutex_spin<__inst>::__last = 0;

# else /* ( _STLP_STATIC_TEMPLATE_DATA > 0 ) */

#  if defined (_STLP_PTHREADS) || defined (_STLP_UITHREADS)  || defined (_STLP_OS2THREADS)
__DECLARE_INSTANCE(_STL_STATIC_MUTEX, _Swap_lock_struct<0>::_S_swap_lock, 
                   _STLP_MUTEX_INITIALIZER  );
#  endif /* _STLP_PTHREADS */

__DECLARE_INSTANCE(unsigned, _STL_mutex_spin<0>::__max,  =30);
__DECLARE_INSTANCE(unsigned, _STL_mutex_spin<0>::__last, =0);

# endif /* ( _STLP_STATIC_TEMPLATE_DATA > 0 ) */

template <int __inst>
void _STLP_CALL
_STL_mutex_spin<__inst>::_S_nsec_sleep(int __log_nsec) {
#     if defined(_STLP_WIN32THREADS)
	  if (__log_nsec <= 20) {
	      Sleep(0);
	  } else {
	      Sleep(1 << (__log_nsec - 20));
	  }
#     elif defined (_STLP_UNIX)
          struct ::timespec __ts;
          /* Max sleep is 2**27nsec ~ 60msec      */
          __ts.tv_sec = 0;
          __ts.tv_nsec = 1 << __log_nsec;
          nanosleep(&__ts, 0);
#     endif
  }


template <int __inst>
void  _STLP_CALL
_STL_mutex_spin<__inst>::_M_do_lock(volatile __stl_atomic_t* __lock)
{
#if defined(_STLP_ATOMIC_EXCHANGE)
  if (_Atomic_swap(__lock, 1)) {
    unsigned __my_spin_max = _STL_mutex_spin<0>::__max;
    unsigned __my_last_spins = _STL_mutex_spin<0>::__last;
    volatile unsigned __junk = 17; 	// Value doesn't matter.
    unsigned  __i;
    
    for (__i = 0; __i < __my_spin_max; ++__i) {
      if (__i < __my_last_spins/2 || *__lock) {
        __junk *= __junk; __junk *= __junk;
        __junk *= __junk; __junk *= __junk;
      } else {
        if (!_Atomic_swap(__lock, 1)) {
          // got it!
          // Spinning worked.  Thus we're probably not being scheduled
          // against the other process with which we were contending.
          // Thus it makes sense to spin longer the next time.
          _STL_mutex_spin<0>::__last = __i;
          _STL_mutex_spin<0>::__max = _STL_mutex_spin<0>::__high_max;
	    return;
        }
      }
    }
    
    // We are probably being scheduled against the other process.  Sleep.
    _STL_mutex_spin<0>::__max = _STL_mutex_spin<0>::__low_max;
    
    for (__i = 0 ;; ++__i) {
      int __log_nsec = __i + 6;
      
      if (__log_nsec > 27) __log_nsec = 27;
      if (!_Atomic_swap(__lock, 1)) {
	  break;
      }
      _S_nsec_sleep(__log_nsec);
    }
    
  } /* first _Atomic_swap */
# endif
}

_STLP_END_NAMESPACE

# endif /* BUILDING_STLPORT */
#endif /*  _STLP_THREADS_C */

// Local Variables:
// mode:C++
// End:
