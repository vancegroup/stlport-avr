// -*- C++ -*- Time-stamp: <03/01/17 08:22:10 ptr>

/*
 *
 * Copyright (c) 1997-1999, 2002
 * Petr Ovtchenkov
 *
 * Portion Copyright (c) 1999-2001
 * Parallel Graphics Ltd.
 *
 * Licensed under the Academic Free License Version 1.0
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 */

#ifndef __XMT_H
#define __XMT_H

#ifdef __unix
#  ifdef __HP_aCC
#pragma VERSIONID "@(#)$Id$"
#  else
#ident "@(#)$Id$"
#  endif
#endif

#ifndef __config_feature_h
#include <config/feature.h>
#endif

#include <memory>
#include <cstddef>
#include <stdexcept>

#ifdef WIN32
#  include <windows.h>
#  include <memory>
#  include <ctime>

extern "C" {

typedef struct  timespec {              /* definition per POSIX.4 */
        time_t          tv_sec;         /* seconds */
        long            tv_nsec;        /* and nanoseconds */
} timespec_t;

typedef struct timespec timestruc_t;    /* definition per SVr4 */

} // extern "C"

#define ETIME   62      /* timer expired                        */

#else // !WIN32
#  if defined( _REENTRANT ) && !defined(_NOTHREADS)
#    if defined( __STL_USE_NEW_STYLE_HEADERS ) && defined( __SUNPRO_CC )
#      include <ctime>
#    endif
#    ifdef _PTHREADS
#      include <pthread.h>
#      include <semaphore.h>
#    else
#      include <thread.h>
#      include <synch.h>
#    endif
#  elif !defined(_NOTHREADS) // !_REENTRANT
#    define _NOTHREADS
#  endif
// #  define __DLLEXPORT
#endif // !WIN32

#ifdef _REENTRANT

#  define MT_REENTRANT(point,nm) __impl::Locker nm(point)
#  define MT_REENTRANT_SDS(point,nm) __impl::LockerSDS nm(point)
#  define MT_LOCK(point)         point.lock()
#  define MT_UNLOCK(point)       point.unlock()

#else

#  define MT_REENTRANT(point,nm) ((void)0)
#  define MT_REENTRANT_SDS(point,nm) ((void)0)
#  define MT_LOCK(point)         ((void)0)
#  define MT_UNLOCK(point)       ((void)0)

#endif

#include <signal.h>

extern "C" {

#ifndef SIG_PF // sys/signal.h

#  ifdef WIN32
typedef void __cdecl SIG_FUNC_TYP(int);
#  else
typedef void SIG_FUNC_TYP(int);
#  endif
typedef SIG_FUNC_TYP *SIG_TYP;
#  define SIG_PF SIG_TYP

#  ifndef SIG_DFL
#    define SIG_DFL (SIG_PF)0
#  endif
#  ifndef SIG_ERR
#    define SIG_ERR (SIG_PF)-1
#  endif
#  ifndef SIG_IGN
#    define SIG_IGN (SIG_PF)1
#  endif
#  ifndef SIG_HOLD
#    define SIG_HOLD (SIG_PF)2
#  endif
#endif // SIG_PF

} // extern "C"

namespace __impl {

// extern __FIT_DECLSPEC void signal_throw( int sig ) throw( int );
// extern __FIT_DECLSPEC void signal_thread_exit( int sig );

#ifdef __unix
extern "C"  void *_xcall( void * ); // forward declaration
#endif
#ifdef WIN32
extern "C" unsigned long __stdcall _xcall( void *p ); // forward declaration
#endif

#ifndef WIN32
// using std::size_t;
#endif
#ifdef __GNUC__
  // using std::runtime_error;
#else
using std::runtime_error;
#endif

class fork_in_parent :
        public std::exception
{
  public:
    fork_in_parent() throw()
      { _pid = 0; }
    fork_in_parent( pid_t p ) throw()
      { _pid = p; }
    virtual ~fork_in_parent() throw()
      { }
    virtual const char *what() const throw()
      { return "class fork_in_parent"; }
    pid_t pid() throw()
      { return _pid; }

  private:
    pid_t _pid;
};

// if parameter SCOPE (process scope) true, PTHREAD_PROCESS_SHARED will
// be used; otherwise PTHREAD_PROCESS_PRIVATE.
// Of cause, system must support process scope...
template <bool SCOPE>
class __mutex_base
{
  public:
    __mutex_base()
      {
#ifdef _PTHREADS
        if ( SCOPE ) {
          pthread_mutexattr_t att;
          pthread_mutexattr_init( &att );
          pthread_mutexattr_setpshared( &att, PTHREAD_PROCESS_SHARED );
          pthread_mutex_init( &_M_lock, &att );
          pthread_mutexattr_destroy( &att );
        } else {
          pthread_mutex_init( &_M_lock, 0 );
        }
#endif
#ifdef __FIT_UITHREADS
        if ( SCOPE ) {
          // or USYNC_PROCESS_ROBUST to detect already initialized mutex
          // in process scope
          mutex_init( &_M_lock, USYNC_PROCESS, 0 );
        } else {
          mutex_init( &_M_lock, 0, 0 );
        }
#endif
#ifdef WIN32
	InitializeCriticalSection( &_M_lock );
#endif
      }

    ~__mutex_base()
      {
#ifdef _PTHREADS
	pthread_mutex_destroy( &_M_lock );
#endif
#ifdef __FIT_UITHREADS
	mutex_destroy( &_M_lock );
#endif
#ifdef WIN32
	DeleteCriticalSection( &_M_lock );
#endif
      }
  protected:
#ifdef _PTHREADS
    pthread_mutex_t _M_lock;
#endif
#ifdef __FIT_UITHREADS
    mutex_t _M_lock;
#endif
#ifdef __FIT_WIN32THREADS
    CRITICAL_SECTION _M_lock;
#endif

#ifndef __FIT_WIN32THREADS
  private:
    friend class Condition;
#endif
};

// if parameter R (recursive), than __Mutex will be recursive-safe
// and may be not recursive-safe for R = false.
template <bool R, bool SCOPE>
class __Mutex :
    public __mutex_base<SCOPE>
{
  public:
    __Mutex()
      { }

    ~__Mutex()
      { }

    void lock()
      {
#ifdef _PTHREADS
	pthread_mutex_lock( &_M_lock );
#endif
#ifdef __FIT_UITHREADS
	mutex_lock( &_M_lock );
#endif
#ifdef __FIT_WIN32THREADS
	EnterCriticalSection( &_M_lock );
#endif
      }

#if !defined( WIN32 ) || (defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0400)
    int trylock()
      {
#ifdef _PTHREADS
	return pthread_mutex_trylock( &_M_lock );
#endif
#ifdef __FIT_UITHREADS
	return mutex_trylock( &_M_lock );
#endif
#ifdef __FIT_WIN32THREADS
	return TryEnterCriticalSection( &_M_lock ) != 0 ? 0 : -1;
#endif
#ifdef _NOTHREADS
        return 0;
#endif
      }
#endif // !WIN32 || _WIN32_WINNT >= 0x0400

    void unlock()
      {
#ifdef _PTHREADS
	pthread_mutex_unlock( &_M_lock );
#endif
#ifdef __FIT_UITHREADS
	mutex_unlock( &_M_lock );
#endif
#ifdef __FIT_WIN32THREADS
	LeaveCriticalSection( &_M_lock );
#endif
      }

  protected:
#ifdef _PTHREADS
    pthread_mutex_t _M_lock;
#endif
#ifdef __FIT_UITHREADS
    mutex_t _M_lock;
#endif
#ifdef __FIT_WIN32THREADS
    CRITICAL_SECTION _M_lock;
#endif

#ifndef __FIT_WIN32THREADS
  private:
    friend class Condition;
#endif
};

// Recursive Safe mutex.

// This specialization need for POSIX and DCE threads,
// because Windows CriticalSection is recursive safe.
// By the way, point for enhancement:  __UNIX_98
// (or XSI---X/Open System Interfaces Extention) has recursive mutex option.
// Another specialization?

#ifdef __unix

template <bool SCOPE>
class __Mutex<true,SCOPE> : // Recursive Safe
    public __mutex_base<SCOPE>
{
  public:
    __Mutex() :
        _count( 0 ),
#ifdef __FIT_UITHREADS
        _id( __STATIC_CAST(thread_t,-1) )
#endif
#ifdef _PTHREADS
        _id( __STATIC_CAST(pthread_t,-1) )
#endif
      { }

    ~__Mutex()
      { }

    void lock()
      {
#ifndef _NOTHREADS
#  ifdef _PTHREADS
        pthread_t _c_id = pthread_self();
#  endif
#  ifdef __FIT_UITHREADS
        thread_t _c_id = thr_self();
#  endif
        if ( _c_id != _id ) {
#  ifdef _PTHREADS
          pthread_mutex_lock( &_M_lock );
#  endif
#  ifdef __FIT_UITHREADS
          mutex_lock( &_M_lock );
#  endif
          _id = _c_id;
          _count = 0;
        }
        ++_count;
#endif // !_NOTHREADS
      }

    // Equivalent to lock(), except that if the mutex object referenced
    // by mutex is currently locked the call return immediately.
    // If mutex is currently owned by the calling thread, the mutex lock count
    // incremented by one and the trylock() function immediately return success
    // (value 0). Otherwise, if mutex is currently owned by another thread,
    // return error (non-zero).

    int trylock()
      {
#ifdef _NOTHREADS
        return 0;
#else // _NOTHREADS
#  ifdef _PTHREADS
        pthread_t _c_id = pthread_self();
#  endif
#  ifdef __FIT_UITHREADS
        thread_t _c_id = thr_self();
#  endif
        if ( _c_id != _id ) {
          int res;
#  ifdef _PTHREADS
          res = pthread_mutex_trylock( &_M_lock );
#  endif
#  ifdef __FIT_UITHREADS
          res = mutex_trylock( &_M_lock );
#  endif
          if ( res != 0 ) {
            return res;
          }

          _id = _c_id;
          _count = 0;
        }
        ++_count;

#endif // !_NOTHREADS
      }

    void unlock()
      {
#ifndef _NOTHREADS
        if ( --_count == 0 ) {
#  ifdef __FIT_UITHREADS
          _id = __STATIC_CAST(thread_t,-1);
          mutex_unlock( &_M_lock );
#  endif
#  ifdef _PTHREADS
          _id =  __STATIC_CAST(pthread_t,-1);
          pthread_mutex_unlock( &_M_lock );
#  endif
#endif // !_NOTHREADS
        }
      }

  protected:
#ifndef _NOTHREADS
    unsigned _count;
#endif // !_NOTHREADS

#ifdef _PTHREADS
    pthread_t _id;
#endif
#ifdef __FIT_UITHREADS
    thread_t  _id;
#endif
};

#endif // __unix

template <bool R, bool PS>
class __Locker
{
  public:
    __Locker( const __Mutex<R,PS>& point ) :
      m( point )
      { const_cast<__Mutex<R,PS>&>(m).lock(); }
    ~__Locker()
      { const_cast<__Mutex<R,PS>&>(m).unlock(); }

  private:
    const __Mutex<R,PS>& m;
};

typedef __Mutex<false,false>  Mutex;
typedef __Mutex<true,false>   MutexSDS;

typedef __Locker<false,false> Locker;
typedef __Locker<true,false>  LockerSDS;

class Condition
{
  public:
    Condition() :
        _val( true )
      {
#ifdef __FIT_WIN32THREADS
        _cond = CreateEvent( 0, TRUE, TRUE, 0 );
#endif
#ifdef _PTHREADS
        pthread_cond_init( &_cond, 0 );
#endif
#ifdef __FIT_UITHREADS
        cond_init( &_cond, 0, 0 );
#endif
      }

    ~Condition()
      {
#ifdef __FIT_WIN32THREADS
        CloseHandle( _cond );
#endif
#ifdef _PTHREADS
        pthread_cond_destroy( &_cond );
#endif
#ifdef __FIT_UITHREADS
        cond_destroy( &_cond );
#endif
      }

    bool set( bool __v )
      {
        MT_REENTRANT( _lock, _x1 );

        bool tmp = _val;
        _val = __v;
#ifdef __FIT_WIN32THREADS
         if ( __v == true && tmp == false ) {
           SetEvent( _cond );
         } else if ( __v == false && tmp == true ) {
           ResetEvent( _cond );
         }
#endif
#ifdef __FIT_UITHREADS
        if ( __v == true && tmp == false ) {
          cond_signal( &_cond );
        }
#endif
#ifdef _PTHREADS
        if ( __v == true && tmp == false ) {
          pthread_cond_signal( &_cond );
        }
#endif
        return tmp;
      }

    bool set() const
      { return _val; }

    int try_wait()
      {
        if ( _val == false ) {
#ifdef __FIT_WIN32THREADS
          if ( WaitForSingleObject( _cond, -1 ) == WAIT_FAILED ) {
            return -1;
          }
          return 0;
#endif
#if defined(__FIT_UITHREADS) || defined(_PTHREADS)
          MT_REENTRANT( _lock, _x1 );
          int ret = 0;
          while ( !_val ) {
            ret =
#ifdef _PTHREADS
              pthread_cond_wait( &_cond, &_lock._M_lock );
#endif
#ifdef __FIT_UITHREADS
              cond_wait( &_cond, &_lock._M_lock );
#endif
          }
          return ret;
#endif
        }
        return 0;
      }

    int wait()
      {
#ifdef __FIT_WIN32THREADS
        MT_LOCK( _lock );
        _val = false;
        ResetEvent( _cond );
        MT_UNLOCK( _lock );
        if ( WaitForSingleObject( _cond, -1 ) == WAIT_FAILED ) {
          return -1;
        }
        return 0;
#endif
#if defined(_PTHREADS) || defined(__FIT_UITHREADS)
        MT_REENTRANT( _lock, _x1 );
        _val = false;
        int ret;
        while ( !_val ) {
          ret =
#ifdef _PTHREADS
            pthread_cond_wait( &_cond, &_lock._M_lock );
#endif
#ifdef __FIT_UITHREADS
            cond_wait( &_cond, &_lock._M_lock );
#endif
        }

        return ret;
#endif
#ifdef _NOTHREADS
        return 0;
#endif
      }

    __FIT_DECLSPEC int wait_time( const timespec *abstime );
    __FIT_DECLSPEC int wait_delay( const timespec *abstime );
    __FIT_DECLSPEC int try_wait_time( const timespec *abstime );
    __FIT_DECLSPEC int try_wait_delay( const timespec *abstime );

    int signal()
      {
        MT_REENTRANT( _lock, _x1 );

        _val = true;
#ifdef __FIT_WIN32THREADS
        return SetEvent( _cond ) == FALSE ? -1 : 0;
#endif
#ifdef _PTHREADS
        return pthread_cond_signal( &_cond );
#endif
#ifdef __FIT_UITHREADS
        return cond_signal( &_cond );
#endif
#ifdef _NOTHREADS
        return 0;
#endif
      }

  protected:
#ifdef __FIT_WIN32THREADS
    HANDLE _cond;
#endif
#ifdef _PTHREADS
    pthread_cond_t _cond;
#endif
#ifdef __FIT_UITHREADS
    cond_t _cond;
#endif
    Mutex _lock;
    // __STLPORT_STD::_STL_mutex_lock _lock;
    bool _val;
};

class Semaphore
{
  public:
    Semaphore( int cnt = 1, bool ipc = false )
      {
#ifdef __FIT_WIN32THREADS
        _sem = CreateSemaphore( NULL, cnt, INT_MAX, 0 ); // check!
#endif
#ifdef __FIT_UITHREADS
        sema_init( &_sem, cnt, ipc ? USYNC_PROCESS : USYNC_THREAD, 0 );
#endif
#ifdef _PTHREADS
        sem_init( &_sem, ipc ? 1 : 0, cnt );
#endif
      }

    ~Semaphore()
      {
#ifdef __FIT_WIN32THREADS
        CloseHandle( _sem );
#endif
#ifdef __FIT_UITHREADS
        sema_destroy( &_sem );
#endif
#ifdef _PTHREADS
        sem_destroy( &_sem );
#endif        
      }

    int wait()
      {
#ifdef __FIT_WIN32THREADS
        if ( WaitForSingleObject( _sem, -1 ) == WAIT_FAILED ) {
          return -1;
        }
        return 0;
#endif
#ifdef __FIT_UITHREADS
        return sema_wait( &_sem );
#endif
#ifdef _PTHREADS
        return sem_wait( &_sem );
#endif
      }

    int try_wait()
      {
#ifdef __FIT_WIN32THREADS
#  warning "Fix me!"
#endif
#ifdef __FIT_UITHREADS
        return sema_trywait( &_sem );
#endif
#ifdef _PTHREADS
        return sem_trywait( &_sem );
#endif        
      }

    int post()
      {
#ifdef __FIT_WIN32THREADS
#  warning "Fix me!"
#endif
#ifdef __FIT_UITHREADS
        return sema_post( &_sem );
#endif
#ifdef _PTHREADS
        return sem_post( &_sem );
#endif        
      }

    int value()
      {
#ifdef __FIT_WIN32THREADS
#  warning "Fix me!"
#endif
#ifdef __FIT_UITHREADS
#  warning "No semaphore value for Solaris threads!"
#endif
#ifdef _PTHREADS
        int v;
        int e = sem_getvalue( &_sem, &v );
        
        return e == 0 ? v : -1;
#endif        
      }

  protected:
#ifdef __FIT_WIN32THREADS
    HANDLE _sem;
#endif
#ifdef __FIT_UITHREADS
    sema_t _sem;
#endif
#ifdef _PTHREADS
    sem_t _sem;
#endif
};

class Thread
{
  public:
    typedef int (*entrance_type)( void * );
#ifdef __FIT_WIN32THREADS
    typedef HANDLE thread_key_type;
#endif
#ifdef _PTHREADS
    typedef pthread_key_t thread_key_type;
#endif
#ifdef __FIT_UITHREADS
    typedef thread_key_t thread_key_type;
#endif

    enum {
#ifdef __FIT_UITHREADS // __STL_SOLARIS_THREADS
      bound     = THR_BOUND,
      detached  = THR_DETACHED,
      new_lwp   = THR_NEW_LWP,
      suspended = THR_SUSPENDED,
      daemon    = THR_DAEMON
#endif
#if defined(_PTHREADS)
      bound     = PTHREAD_SCOPE_SYSTEM,   // otherwise, PTHREAD_SCOPE_PROCESS, default
      detached  = PTHREAD_CREATE_DETACHED,// otherwise, PTHREAD_CREATE_JOINABLE, default
      new_lwp   = 0, // pthread_setconcurrency( pthread_getconcurrency() + 1 );
      suspended = 0,
      daemon    = detached
#endif
#ifdef __FIT_WIN32THREADS
      bound     = 0,
      detached  = 0,
      new_lwp   = 0,
      suspended = CREATE_SUSPENDED,
      daemon    = 0
#endif
    };

    class Init
    {
      public:
        Init();
        ~Init();
      private:
        static int& _count;
    };

    __FIT_DECLSPEC Thread( unsigned flags = 0 );

    explicit __FIT_DECLSPEC Thread( entrance_type entrance, const void *p = 0, size_t psz = 0, unsigned flags = 0 );

    __FIT_DECLSPEC ~Thread();

    __FIT_DECLSPEC
    void launch( entrance_type entrance, const void *p = 0, size_t psz = 0 );
    __FIT_DECLSPEC int join();
    __FIT_DECLSPEC int suspend();
    __FIT_DECLSPEC int resume();
    __FIT_DECLSPEC int kill( int sig );
#ifdef __FIT_UITHREADS
    static __FIT_DECLSPEC int join_all();
#endif
    static __FIT_DECLSPEC void block_signal( int sig );
    static __FIT_DECLSPEC void unblock_signal( int sig );
    static __FIT_DECLSPEC void signal_handler( int sig, SIG_PF );
    static __FIT_DECLSPEC void signal_exit( int sig ); // signal handler

    // sleep at least up to time t
    static __FIT_DECLSPEC void sleep( timespec *t, timespec *e = 0 );
    // delay execution at least on time interval t
    static __FIT_DECLSPEC void delay( timespec *t, timespec *e = 0 );
    // get precise time
    static __FIT_DECLSPEC void gettime( timespec *t );
    static __FIT_DECLSPEC void fork() throw( fork_in_parent, std::runtime_error );
    static __FIT_DECLSPEC void become_daemon() throw( fork_in_parent, std::runtime_error );

    bool good() const
      { return _id != bad_thread_key; }
    __FIT_DECLSPEC bool is_self();

    static __FIT_DECLSPEC int xalloc();
    long&  iword( int __idx )
      {
        _STLP_ASSERT( is_self() );
        return *static_cast<long *>(_alloc_uw( __idx ));
      }
    void*& pword( int __idx )
      {
        _STLP_ASSERT( is_self() );
        return *reinterpret_cast<void **>(_alloc_uw( __idx ));
      }

#ifndef __FIT_WIN32THREADS
    static thread_key_type mtkey()
      { return _mt_key; }
#endif
#ifdef __FIT_WIN32THREADS
    static unsigned long mtkey()
      { return _mt_key; }
#endif
    static const thread_key_type bad_thread_key;

  protected:
    static __FIT_DECLSPEC void _exit( int code = 0 );

  private:
    Thread( const Thread& )
      { }

    void _create( const void *p, size_t psz ) throw( std::runtime_error);
    static void *_call( void *p );

    static void unexpected();
    static void terminate();

    // assume that sizeof( long ) >= sizeof( void * );
    // otherwise, #ifdef workaround should be here.
    // At present, I don't know such OS.
#if 1
    typedef long _uw_alloc_type;
#endif
    typedef std::allocator<_uw_alloc_type> alloc_type;
    __FIT_DECLSPEC void _dealloc_uw();
    __FIT_DECLSPEC _uw_alloc_type *_alloc_uw( int __idx );

    static alloc_type alloc;
    static int _idx; // user words index
    static int _self_idx; // user words index, that word point to self
    static Mutex _idx_lock;
    static Mutex _start_lock;
#ifdef __FIT_WIN32THREADS
    static unsigned long& _mt_key;
#else
    static thread_key_type& _mt_key;
#endif
    size_t uw_alloc_size;

#ifdef _PTHREADS
    pthread_t _id;
// #  ifdef __sun
// #    error "Sorry, Solaris has no pthread_{suspend,continue} calls"
    // sorry, POSIX threads don't have suspend/resume calls, so it should
    // be simulated via cond_wait
    Condition _suspend;
// #  endif
#endif
#ifdef __FIT_UITHREADS
    thread_t  _id;
#endif
#ifdef __FIT_WIN32THREADS
    HANDLE    _id;
    unsigned long _thr_id;
#endif
    entrance_type _entrance;
    void *_param;
    size_t _param_sz;
    unsigned _flags;
    //  Mutex _params_lock; --- no needs
    friend class Init;
    // extern "C", wrap for thread_create
#ifdef __unix
    friend void *_xcall( void * );
#endif
#ifdef __FIT_WIN32THREADS
    friend unsigned long __stdcall _xcall( void *p );
#endif
};

} // namespace __impl

timespec operator +( const timespec& a, const timespec& b );
timespec operator -( const timespec& a, const timespec& b );
timespec operator /( const timespec& a, unsigned b );
timespec operator /( const timespec& a, unsigned long b );

// timespec& operator =( timespec& a, const timespec& b );
timespec& operator +=( timespec& a, const timespec& b );
timespec& operator -=( timespec& a, const timespec& b );
timespec& operator /=( timespec& a, unsigned b );
timespec& operator /=( timespec& a, unsigned long b );

#endif // __XMT_H
