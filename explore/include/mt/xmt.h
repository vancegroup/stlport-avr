// -*- C++ -*- Time-stamp: <01/01/31 10:47:42 ptr>

/*
 *
 * Copyright (c) 1997-1999
 * Petr Ovchenkov
 *
 * Copyright (c) 1999-2000
 * ParallelGraphics Ltd.
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
#pragma VERSIONID "$SunId$"
#  else
#pragma ident "$SunId$"
#  endif
#endif

#ifndef __config_feature_h
#include <config/feature.h>
#endif

#include <cstddef>
#include <stdexcept>

#ifdef WIN32
#  include <windows.h>
#  include <memory>
#  ifndef _REENTRANT
#    define _REENTRANT
#  endif
#  include <ctime>

// namespace std {

extern "C" {

typedef struct  timespec {              /* definition per POSIX.4 */
        time_t          tv_sec;         /* seconds */
        long            tv_nsec;        /* and nanoseconds */
} timespec_t;

typedef struct timespec timestruc_t;    /* definition per SVr4 */

}

#define ETIME   62      /* timer expired                        */

// } // namespace std

#else // !WIN32
#  if defined( _REENTRANT ) && !defined(_NOTHREADS)
#    if defined( __STL_USE_NEW_STYLE_HEADERS ) && defined( __SUNPRO_CC )
#      include <ctime>
#    endif
#    if !defined(_PTHREADS) && !defined(_SOLARIS_THREADS)
#      ifdef __STL_THREADS
#        ifdef __STL_SOLARIS_THREADS
#          define _SOLARIS_THREADS
#        elif defined( __STL_PTHREADS )
#          define _PTHREADS
#        endif
#      else
#        define _SOLARIS_THREADS // my default choice
#      endif
#    endif
#    ifdef _PTHREADS
#      include <pthread.h>
#    endif
#    ifdef __STL_UITHREADS
#      include <thread.h>
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

extern __PG_DECLSPEC void signal_throw( int sig ) throw( int );
#ifdef __unix
extern "C"  void *_xcall( void * ); // forward declaration
#endif
#ifdef WIN32
extern "C" unsigned long __stdcall _xcall( void *p ); // forward declaration
#endif

#ifndef WIN32
using std::size_t;
#endif
#ifdef __GNUC__
  // using std::runtime_error;
#else
using __STD::runtime_error;
#endif

class Mutex
{
  public:
    Mutex()
      {
#ifdef _PTHREADS
	pthread_mutex_init( &_M_lock, 0 );
#endif
#ifdef __STL_UITHREADS
	mutex_init( &_M_lock, 0, 0 );
#endif
#ifdef WIN32
	InitializeCriticalSection( &_M_lock );
#endif
      }

    ~Mutex()
      {
#ifdef _PTHREADS
	pthread_mutex_destroy( &_M_lock );
#endif
#ifdef __STL_UITHREADS
	mutex_destroy( &_M_lock );
#endif
#ifdef WIN32
	DeleteCriticalSection( &_M_lock );
#endif
      }

    void lock()
      {
#ifdef __STL_PTHREADS
	pthread_mutex_lock( &_M_lock );
#endif
#ifdef __STL_UITHREADS
	mutex_lock( &_M_lock );
#endif
#ifdef __STL_WIN32THREADS
	EnterCriticalSection( &_M_lock );
#endif
      }

#if !defined( WIN32 ) || (defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0400)
    int trylock()
      {
#ifdef __STL_PTHREADS
	return pthread_mutex_trylock( &_M_lock );
#endif
#ifdef __STL_UITHREADS
	return mutex_trylock( &_M_lock );
#endif
#ifdef __STL_WIN32THREADS
	return TryEnterCriticalSection( &_M_lock ) != 0 ? 0 : -1;
#endif
#ifdef _NOTHREADS
        return 0;
#endif
      }
#endif // !WIN32 || _WIN32_WINNT >= 0x0400

    void unlock()
      {
#ifdef __STL_PTHREADS
	pthread_mutex_unlock( &_M_lock );
#endif
#ifdef __STL_UITHREADS
	mutex_unlock( &_M_lock );
#endif
#ifdef WIN32
	LeaveCriticalSection( &_M_lock );
#endif
      }

  protected:
#ifdef _PTHREADS
    pthread_mutex_t _M_lock;
#endif
#ifdef __STL_UITHREADS
    mutex_t _M_lock;
#endif
#ifdef WIN32
    CRITICAL_SECTION _M_lock;
#endif

  private:
#ifndef WIN32
    friend class Condition;
#endif
};

class MutexSDS : // Self Deadlock Safe
        public Mutex
{
  public:
    MutexSDS() :
        _count( 0 ),
#ifdef __unix
#  ifdef __STL_UITHREADS
        _id( __STATIC_CAST(thread_t,-1) )
#  elif defined(_PTHREADS)
        _id( __STATIC_CAST(pthread_t,-1) )
#  else
#    error "only POSIX and Solaris threads supported now in *NIXes"
#  endif
#endif

#ifdef WIN32
        _id( INVALID_HANDLE_VALUE )
#endif
      { }

    void lock()
      {
#ifdef _PTHREADS
        pthread_t _c_id = pthread_self();
#endif
#ifdef __STL_UITHREADS
        thread_t _c_id = thr_self();
#endif
#ifdef WIN32
        HANDLE _c_id = GetCurrentThread();
#endif
        if ( _c_id != _id ) {
          Mutex::lock();
          _id = _c_id;
          _count = 0;
        }
        ++_count;
      }

    void unlock()
      {
        if ( --_count == 0 ) {
#ifdef __unix
#  ifdef __STL_UITHREADS
         _id = __STATIC_CAST(thread_t,-1);
#  elif defined(_PTHREADS)
         _id =  __STATIC_CAST(pthread_t,-1);
#  endif
#endif

#ifdef WIN32
          _id = INVALID_HANDLE_VALUE;
#endif
          Mutex::unlock();
        }
      }

  protected:
    unsigned _count;
#ifdef _PTHREADS
    pthread_t _id;
#endif
#ifdef __STL_UITHREADS
    thread_t  _id;
#endif
#ifdef WIN32
    HANDLE    _id;
#endif
};

class Locker
{
  public:
    Locker( const Mutex& point ) :
      m( point )
      { const_cast<Mutex&>(m).lock(); }
    ~Locker()
      { const_cast<Mutex&>(m).unlock(); }

  private:
    const Mutex& m;
};

class LockerSDS // self deadlock safe
{
  public:
    LockerSDS( const MutexSDS& point ) :
      m( point )
      { const_cast<MutexSDS&>(m).lock(); }
    ~LockerSDS()
      { const_cast<MutexSDS&>(m).unlock(); }

  private:
    const MutexSDS& m;
};

class Condition
{
  public:
    Condition() :
        _val( true )
      {
#ifdef WIN32
        _cond = CreateEvent( 0, TRUE, TRUE, 0 );
#endif
#ifdef _PTHREADS
        pthread_cond_init( &_cond, 0 );
#endif
#ifdef __STL_UITHREADS
        cond_init( &_cond, 0, 0 );
#endif
      }

    ~Condition()
      {
#ifdef WIN32
        CloseHandle( _cond );
#endif
#ifdef _PTHREADS
        pthread_cond_destroy( &_cond );
#endif
#ifdef __STL_UITHREADS
        cond_destroy( &_cond );
#endif
      }

    bool set( bool __v )
      {
        MT_REENTRANT( _lock, _x1 );

        bool tmp = _val;
        _val = __v;
#ifdef WIN32
         if ( __v == true && tmp == false ) {
           SetEvent( _cond );
         } else if ( __v == false && tmp == true ) {
           ResetEvent( _cond );
         }
#endif
#ifdef __STL_UITHREADS
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
#ifdef WIN32
          if ( WaitForSingleObject( _cond, -1 ) == WAIT_FAILED ) {
            return -1;
          }
          return 0;
#endif
#if defined(__STL_UITHREADS) || defined(_PTHREADS)
          MT_REENTRANT( _lock, _x1 );
          int ret = 0;
          while ( !_val ) {
            ret =
#ifdef _PTHREADS
              pthread_cond_wait( &_cond, &_lock._M_lock );
#endif
#ifdef __STL_UITHREADS
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
#ifdef WIN32
        MT_LOCK( _lock );
        _val = false;
        ResetEvent( _cond );
        MT_UNLOCK( _lock );
        if ( WaitForSingleObject( _cond, -1 ) == WAIT_FAILED ) {
          return -1;
        }
        return 0;
#endif
#if defined(_PTHREADS) || defined(__STL_UITHREADS)
        MT_REENTRANT( _lock, _x1 );
        _val = false;
        int ret;
        while ( !_val ) {
          ret =
#ifdef _PTHREADS
            pthread_cond_wait( &_cond, &_lock._M_lock );
#endif
#ifdef __STL_UITHREADS
            cond_wait( &_cond, &_lock._M_lock );
#endif
        }

        return ret;
#endif
#ifdef _NOTHREADS
        return 0;
#endif
      }

    __PG_DECLSPEC int wait_time( const timespec *abstime );

    int signal()
      {
        MT_REENTRANT( _lock, _x1 );

        _val = true;
#ifdef WIN32
        return SetEvent( _cond ) == FALSE ? -1 : 0;
#endif
#ifdef _PTHREADS
        return pthread_cond_signal( &_cond );
#endif
#ifdef __STL_UITHREADS
        return cond_signal( &_cond );
#endif
#ifdef _NOTHREADS
        return 0;
#endif
      }

  protected:
#ifdef WIN32
    HANDLE _cond;
#endif
#ifdef _PTHREADS
    pthread_cond_t _cond;
#endif
#ifdef __STL_UITHREADS
    cond_t _cond;
#endif
    Mutex _lock;
    // __STLPORT_STD::_STL_mutex_lock _lock;
    bool _val;
};

class Thread
{
  public:
    typedef int (*entrance_type)( void * );
#ifdef __STL_WIN32THREADS
    typedef HANDLE thread_key_type;
#endif
#ifdef __STL_PTHREADS
    typedef pthread_key_t thread_key_type;
#endif
#ifdef __STL_UITHREADS
    typedef thread_key_t thread_key_type;
#endif

#ifdef __STL_USE_SGI_ALLOCATORS
    typedef __STD::alloc alloc_type;
#else 
    typedef __STD::allocator<long *> alloc_type;
#endif

    enum {
#ifdef __STL_UITHREADS // __STL_SOLARIS_THREADS
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
#ifdef __STL_WIN32THREADS
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
        static int _count;
    };

    __PG_DECLSPEC Thread( unsigned flags = 0 );

    explicit __PG_DECLSPEC Thread( entrance_type entrance, const void *p = 0, size_t psz = 0, unsigned flags = 0 );

    __PG_DECLSPEC ~Thread();

    __PG_DECLSPEC
    void launch( entrance_type entrance, const void *p = 0, size_t psz = 0 );
    __PG_DECLSPEC int join();
    __PG_DECLSPEC int suspend();
    __PG_DECLSPEC int resume();
    __PG_DECLSPEC int kill( int sig );
    static __PG_DECLSPEC void exit( int code = 0 );
#ifdef __STL_UITHREADS
    static __PG_DECLSPEC int join_all();
#endif
    static __PG_DECLSPEC void block_signal( int sig );
    static __PG_DECLSPEC void unblock_signal( int sig );
    static __PG_DECLSPEC void signal_handler( int sig, SIG_PF );

    static __PG_DECLSPEC void sleep( timespec *t, timespec *e = 0 );
    static __PG_DECLSPEC void gettime( timespec *t );

    bool good() const
      { return _id != bad_thread_key; }

    static int xalloc()
      { return _idx++; }
    __PG_DECLSPEC long&  iword( int __idx );
    __PG_DECLSPEC void*& pword( int __idx );

#ifndef WIN32
    static thread_key_type mtkey()
      { return _mt_key; }
#endif
#ifdef WIN32
    static unsigned long mtkey()
      { return _mt_key; }
#endif
    static const thread_key_type bad_thread_key;

  private:
    Thread( const Thread& )
      { }

#ifdef __GNUC__
    void _create( const void *p, size_t psz );
#else
    void _create( const void *p, size_t psz ) throw( __STD::runtime_error);
#endif
    static void *_call( void *p );

    static void unexpected();
    static void terminate();

    static alloc_type alloc;
    static int _idx; // user words index
#ifndef WIN32
    static thread_key_type _mt_key;
#endif
#ifdef WIN32
    static unsigned long _mt_key;
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
#ifdef __STL_UITHREADS
    thread_t  _id;
#endif
#ifdef WIN32
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
#ifdef WIN32
    friend unsigned long __stdcall _xcall( void *p );
#endif
};

} // namespace __impl

// #ifdef _MSC_VER // VC 5
// extern "C" {

// struct  timespec { /* definition per POSIX.4 */
//   time_t tv_sec;         /* seconds */
//  long   tv_nsec;        /* and nanoseconds */
// };

// }

// #endif // _MSC_VER

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
