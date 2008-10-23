// -*- C++ -*- Time-stamp: <07/09/15 10:03:40 ptr>

/*
 * Copyright (c) 1997-1999, 2002-2007
 * Petr Ovtchenkov
 *
 * Portion Copyright (c) 1999-2001
 * Parallel Graphics Ltd.
 *
 * Licensed under the Academic Free License version 3.0
 *
 */

#ifndef __XMT_H
#define __XMT_H

#ifndef __config_feature_h
#include <config/feature.h>
#endif

#include <memory>
#include <cstddef>
#include <stdexcept>

#if !defined(_STLPORT_VERSION) && !defined(__STATIC_CAST)
# define __STATIC_CAST(t,v) static_cast<t>(v)
#endif

#ifdef WIN32
# include <windows.h>
# include <memory>
# include <limits>
# define ETIME   62      /* timer expired */
# pragma warning( disable : 4290)
#endif // WIN32

#ifdef __unix
# if defined( _REENTRANT ) && !defined(_NOTHREADS)
#  ifdef _PTHREADS
#   include <pthread.h>
#   include <semaphore.h>
#   include <sched.h>
#  else
#   include <thread.h>
#   include <synch.h>
#  endif
# elif !defined(_NOTHREADS) // !_REENTRANT
#  define _NOTHREADS
# endif
// #  define __DLLEXPORT
#endif // __unix

#include <cerrno>

#include <mt/time.h>

#ifdef _REENTRANT

# define MT_REENTRANT(point,nm) xmt::scoped_lock nm(point)
# define MT_LOCK(point)         point.lock()
# define MT_UNLOCK(point)       point.unlock()

#else // !_REENTRANT

# define MT_REENTRANT(point,nm) ((void)0)
# define MT_REENTRANT_RS(point,nm) ((void)0)
# define MT_LOCK(point)         ((void)0)
# define MT_UNLOCK(point)       ((void)0)

#endif // _REENTRANT

#include <signal.h>

extern "C" {

#ifndef SIG_PF // sys/signal.h

# ifdef WIN32
typedef void __cdecl SIG_FUNC_TYP(int);
# else
typedef void SIG_FUNC_TYP(int);
# endif
typedef SIG_FUNC_TYP *SIG_TYP;
# define SIG_PF SIG_TYP

# ifndef SIG_DFL
#  define SIG_DFL (SIG_PF)0
# endif
# ifndef SIG_ERR
#  define SIG_ERR (SIG_PF)-1
# endif
# ifndef SIG_IGN
#  define SIG_IGN (SIG_PF)1
# endif
# ifndef SIG_HOLD
#  define SIG_HOLD (SIG_PF)2
# endif
#endif // SIG_PF

typedef void siginfo_handler_type( int, siginfo_t *, void * );

} // extern "C"

namespace xmt {


// Exceptions

// class thread_exit;
// class thread_cancel: public thread_exit;
// class thread_error: public exception;

class lock_error :
        public std::exception
{
  private:
    int r_;

  public:

    explicit lock_error( int r ) :
        r_( r )
      { }

    virtual char const *what() throw()
      { return "std::lock_error"; }

    int error() const
      { return r_; }
};

namespace detail {

#ifdef __FIT_PSHARED_MUTEX
extern std::string _notpshared;
#endif

#ifdef __FIT_XSI_THR
extern std::string _notrecursive;
#endif

} // namespace detail

// extern __FIT_DECLSPEC void signal_throw( int sig ) throw( int );
// extern __FIT_DECLSPEC void signal_thread_exit( int sig );

// #ifdef __unix
// extern "C"  void *_xcall( void * ); // forward declaration
// #endif
// #ifdef WIN32
// extern "C" unsigned long __stdcall _xcall( void *p ); // forward declaration
// #endif

#ifndef WIN32
// using std::size_t;
#endif
#ifdef __GNUC__
  // using std::runtime_error;
#else
using std::runtime_error;
#endif

#ifndef _WIN32
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
#endif // !_WIN32


template <bool SCOPE> class __condition;

// if parameter SCOPE (process scope) true, PTHREAD_PROCESS_SHARED will
// be used; otherwise PTHREAD_PROCESS_PRIVATE.
// Of cause, system must support process scope...
// Linux at 2003-01-19 NOT SUPPORT PTHREAD_PROCESS_SHARED mutex!
// And Windows too!
// 
template <bool RECURSIVE_SAFE, bool SCOPE>
class __mutex_base
{
  public:
    __mutex_base()
      {
#ifdef _PTHREADS
        if ( SCOPE || RECURSIVE_SAFE ) {
          pthread_mutexattr_t att;
          pthread_mutexattr_init( &att );
# ifdef __FIT_PSHARED_MUTEX
          if ( SCOPE ) {
            if ( pthread_mutexattr_setpshared( &att, PTHREAD_PROCESS_SHARED ) != 0 ) {
              throw std::invalid_argument( detail::_notpshared );
            }
          }
# endif // __FIT_PSHARED_MUTEX
# ifdef __FIT_XSI_THR  // Unix 98 or X/Open System Interfaces Extention
          if ( RECURSIVE_SAFE ) {
            if ( pthread_mutexattr_settype( &att, PTHREAD_MUTEX_RECURSIVE ) != 0 ) {
              throw std::invalid_argument( detail::_notrecursive );
            }
          }
# endif
          pthread_mutex_init( &_M_lock, &att );
          pthread_mutexattr_destroy( &att );
        } else {
          pthread_mutex_init( &_M_lock, 0 );
        }
#endif // _PTHREADS
#ifdef __FIT_UITHREADS
        if ( SCOPE ) {
          // or USYNC_PROCESS_ROBUST to detect already initialized mutex
          // in process scope
          mutex_init( &_M_lock, USYNC_PROCESS, 0 );
        } else {
          mutex_init( &_M_lock, 0, 0 );
        }
#endif
#ifdef __FIT_WIN32THREADS
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

  private:
    __mutex_base( const __mutex_base& )
      { }

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
    friend class __condition<SCOPE>;
#endif
};

#ifdef __FIT_PTHREAD_SPINLOCK

// The IEEE Std. 1003.1j-2000 introduces functions to implement spinlocks.
template <bool SCOPE>
class __spinlock_base
{
  public:
    __spinlock_base()
      {
#ifdef _PTHREADS
        pthread_spin_init( &_M_lock, SCOPE ? 1 : 0 );
#endif // _PTHREADS
      }

    ~__spinlock_base()
      {
#ifdef _PTHREADS
        pthread_spin_destroy( &_M_lock );
#endif
      }
  protected:
#ifdef _PTHREADS
    pthread_spinlock_t _M_lock;
#endif
};

#endif // __FIT_PTHREAD_SPINLOCK

// Portable mutex implementation. If the parameter RECURSIVE_SAFE
// is true, mutex will be recursive safe (detect deadlock).
// If RECURSIVE_SAFE is false, implementation may not to be
// recursive-safe.
// The SCOPE parameter designate mutex scope---shared between
// processes (true), or only inside threads of one process (false).
// Note, that not all OS support interprocess mutex scope
// (for example, Windows and Linux).
template <bool RECURSIVE_SAFE, bool SCOPE>
class __mutex :
    public __mutex_base<RECURSIVE_SAFE,SCOPE>
{
  public:
    __mutex()
      { }

    ~__mutex()
      { }

    void lock()
      {
#ifdef _PTHREADS
        pthread_mutex_lock( &this->_M_lock );
#endif
#ifdef __FIT_UITHREADS
        mutex_lock( &this->_M_lock );
#endif
#ifdef __FIT_WIN32THREADS
        EnterCriticalSection( &this->_M_lock );
#endif
      }

#if !defined( WIN32 ) || (defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0400)
    int try_lock()
      {
#ifdef _PTHREADS
        return pthread_mutex_trylock( &this->_M_lock );
#endif
#ifdef __FIT_UITHREADS
        return mutex_trylock( &this->_M_lock );
#endif
#ifdef __FIT_WIN32THREADS
        return TryEnterCriticalSection( &this->_M_lock ) != 0 ? 0 : -1;
#endif
#ifdef _NOTHREADS
        return 0;
#endif
      }
#endif // !WIN32 || _WIN32_WINNT >= 0x0400

    void unlock()
      {
#ifdef _PTHREADS
        pthread_mutex_unlock( &this->_M_lock );
#endif
#ifdef __FIT_UITHREADS
        mutex_unlock( &this->_M_lock );
#endif
#ifdef __FIT_WIN32THREADS
        LeaveCriticalSection( &this->_M_lock );
#endif
      }

  private:
    __mutex( const __mutex& )
      { }

#ifndef __FIT_WIN32THREADS
  private:
    friend class __condition<SCOPE>;
#endif
};

#ifdef __FIT_PTHREAD_SPINLOCK
// Spinlock-based locks (IEEE Std. 1003.1j-2000)

template <bool RS, bool SCOPE> class __spinlock;

template <bool SCOPE>
class __spinlock<false,SCOPE> :
    public __spinlock_base<SCOPE>
{
  public:
    __spinlock()
      { }

    ~__spinlock()
      { }

    void lock()
      {
# ifdef _PTHREADS
        pthread_spin_lock( &this->_M_lock );
# endif
      }

    int try_lock()
      {
# ifdef _PTHREADS
        return pthread_spin_trylock( &this->_M_lock );
# endif
# ifdef _NOTHREADS
        return 0;
# endif
      }

    void unlock()
      {
# ifdef _PTHREADS
        pthread_spin_unlock( &this->_M_lock );
# endif
      }

  private:
    __spinlock( const __spinlock& )
      { }

};

template <bool SCOPE>
class __spinlock<true,SCOPE> : //  Recursive safe
    public __spinlock_base<SCOPE>
{
  public:
    __spinlock()
      { }

    ~__spinlock()
      { }

    void lock()
      {
# ifndef _NOTHREADS
#  ifdef _PTHREADS
        pthread_t _c_id = pthread_self();
#  endif
#  ifdef __FIT_UITHREADS
        thread_t _c_id = thr_self();
#  endif
        if ( _c_id == _id ) {
          ++_count;
          return;
        }
#  ifdef _PTHREADS
        pthread_spin_lock( &this->_M_lock );
#  endif
        _id = _c_id;
        _count = 0;
# endif // !_NOTHREADS
      }

    int try_lock()
      {
# ifdef _NOTHREADS
        return 0;
# else // _NOTHREADS
#  ifdef _PTHREADS
        pthread_t _c_id = pthread_self();
#  endif
#  ifdef __FIT_UITHREADS
        thread_t _c_id = thr_self();
#  endif
        if ( _c_id == _id ) {
          ++_count;
          return 0;
        }
#  ifdef _PTHREADS
        int res = pthread_spin_trylock( &this->_M_lock );
#  endif
        if ( res != 0 ) {
          return res;
        }

        _id = _c_id;
        _count = 0;

        return 0;
# endif // !_NOTHREADS
      }

    void unlock()
      {
# ifndef _NOTHREADS
        if ( --_count == 0 ) {
#  ifdef _PTHREADS
          _id =  __STATIC_CAST(pthread_t,-1);
          pthread_spin_unlock( &this->_M_lock );
#  endif
# endif // !_NOTHREADS
        }
      }
  protected:
# ifndef _NOTHREADS
    unsigned _count;
# endif // !_NOTHREADS

# ifdef _PTHREADS
    pthread_t _id;
# endif
# ifdef __FIT_UITHREADS
    thread_t  _id;
# endif

  private:
    __spinlock( const __spinlock& )
      { }
};
#endif // __FIT_PTHREAD_SPINLOCK

// Recursive Safe mutex.

// This specialization need for POSIX and DCE threads,
// because Windows CriticalSection is recursive safe.
// By the way, point for enhancement:  __UNIX_98
// (or XSI---X/Open System Interfaces Extention) has recursive mutex option.
// Another specialization?

#if (defined(__unix) && !defined(__FIT_XSI_THR))

// This specialization need for old POSIX and DCE threads,
// before XSI (X/Open System Interfaces Extention) or Unix 98.
// because Windows CriticalSection is recursive safe, and
// XSI implementation has appropriate mutex parameter (see
// __mutex_base above).

template <bool SCOPE>
class __mutex<true,SCOPE> : // Recursive Safe
    public __mutex_base<true,SCOPE>
{
  public:
    __mutex() :
        _count( 0 ),
# ifdef __FIT_UITHREADS
        _id( __STATIC_CAST(thread_t,-1) )
# endif
# ifdef _PTHREADS
        _id( __STATIC_CAST(pthread_t,-1) )
# endif
      { }

    ~__mutex()
      { }

    void lock()
      {
# ifndef _NOTHREADS
#  ifdef _PTHREADS
        pthread_t _c_id = pthread_self();
#  endif
#  ifdef __FIT_UITHREADS
        thread_t _c_id = thr_self();
#  endif
        if ( _c_id == _id ) {
          ++_count;
          return;
        }
#  ifdef _PTHREADS
        pthread_mutex_lock( &_M_lock );
#  endif
#  ifdef __FIT_UITHREADS
        mutex_lock( &_M_lock );
#  endif
        _id = _c_id;
        _count = 0;
# endif // !_NOTHREADS
      }

    // Equivalent to lock(), except that if the mutex object referenced
    // by mutex is currently locked the call return immediately.
    // If mutex is currently owned by the calling thread, the mutex lock count
    // incremented by one and the try_lock() function immediately return success
    // (value 0). Otherwise, if mutex is currently owned by another thread,
    // return error (non-zero).

    int try_lock()
      {
# ifdef _NOTHREADS
        return 0;
# else // _NOTHREADS
#  ifdef _PTHREADS
        pthread_t _c_id = pthread_self();
#  endif
#  ifdef __FIT_UITHREADS
        thread_t _c_id = thr_self();
#  endif
        if ( _c_id == _id ) {
          ++_count;
          return 0;
        }
#  ifdef _PTHREADS
        int res = pthread_mutex_trylock( &_M_lock );
#  endif
#  ifdef __FIT_UITHREADS
        int res = mutex_trylock( &_M_lock );
#  endif
        if ( res != 0 ) {
          return res;
        }

        _id = _c_id;
        _count = 0;

        return 0;
# endif // !_NOTHREADS
      }

    void unlock()
      {
# ifndef _NOTHREADS
        if ( --_count == 0 ) {
#  ifdef __FIT_UITHREADS
          _id = __STATIC_CAST(thread_t,-1);
          mutex_unlock( &_M_lock );
#  endif
#  ifdef _PTHREADS
          _id =  __STATIC_CAST(pthread_t,-1);
          pthread_mutex_unlock( &_M_lock );
#  endif
# endif // !_NOTHREADS
        }
      }

  private:
    __mutex( const __mutex& )
      { }

  protected:
# ifndef _NOTHREADS
    unsigned _count;
# endif // !_NOTHREADS

# ifdef _PTHREADS
    pthread_t _id;
# endif
# ifdef __FIT_UITHREADS
    thread_t  _id;
# endif
};
#endif // __unix && !__FIT_XSI_THR

#ifdef __FIT_RWLOCK
// Read-write mutex: IEEE Std 1003.1, 2001, 2004 Editions

template <bool SCOPE>
class __rw_mutex_base
{
  public:
    __rw_mutex_base()
      {
#ifdef _PTHREADS
        if ( SCOPE ) {
          pthread_rwlockattr_t att;
          pthread_rwlockattr_init( &att );
# ifdef __FIT_PSHARED_MUTEX
          if ( pthread_rwlockattr_setpshared( &att, PTHREAD_PROCESS_SHARED ) != 0 ) {
            throw std::invalid_argument( xmt::detail::_notpshared );
          }
# endif // __FIT_PSHARED_MUTEX
          pthread_rwlock_init( &_M_lock, &att );
          pthread_rwlockattr_destroy( &att );
        } else {
          pthread_rwlock_init( &_M_lock, 0 );
        }
#endif // _PTHREADS
#ifdef __FIT_UITHREADS
#error Fix me!
        if ( SCOPE ) {
          // or USYNC_PROCESS_ROBUST to detect already initialized mutex
          // in process scope
          mutex_init( &_M_lock, USYNC_PROCESS, 0 );
        } else {
          mutex_init( &_M_lock, 0, 0 );
        }
#endif
#ifdef __FIT_WIN32THREADS
#error Fix me!
        InitializeCriticalSection( &_M_lock );
#endif
      }

    ~__rw_mutex_base()
      {
#ifdef _PTHREADS
        pthread_rwlock_destroy( &_M_lock );
#endif
#ifdef __FIT_UITHREADS
#error Fix me!
        mutex_destroy( &_M_lock );
#endif
#ifdef WIN32
#error Fix me!
        DeleteCriticalSection( &_M_lock );
#endif
      }

  private:
    __rw_mutex_base( const __rw_mutex_base& )
      { }

  protected:
#ifdef _PTHREADS
    pthread_rwlock_t _M_lock;
#endif
#ifdef __FIT_UITHREADS
#error Fix me!
    mutex_t _M_lock;
#endif
#ifdef __FIT_WIN32THREADS
#error Fix me!
    CRITICAL_SECTION _M_lock;
#endif
};

template <bool SCOPE>
class __rw_mutex :
    public __rw_mutex_base<SCOPE>
{
  public:
    __rw_mutex()
      { }

    ~__rw_mutex()
      { }

    void rdlock()
      {
#ifdef _PTHREADS
        pthread_rwlock_rdlock( &this->_M_lock );
#endif
#ifdef __FIT_UITHREADS
#error Fix me!
        mutex_lock( &this->_M_lock );
#endif
#ifdef __FIT_WIN32THREADS
#error Fix me!
        EnterCriticalSection( &this->_M_lock );
#endif
      }

    void lock()
      {
#ifdef _PTHREADS
        pthread_rwlock_wrlock( &this->_M_lock );
#endif
#ifdef __FIT_UITHREADS
#error Fix me!
        mutex_lock( &this->_M_lock );
#endif
#ifdef __FIT_WIN32THREADS
#error Fix me!
        EnterCriticalSection( &this->_M_lock );
#endif
      }

#if !defined( WIN32 ) || (defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0400)
    int try_rdlock()
      {
#ifdef _PTHREADS
        return pthread_rwlock_tryrdlock( &this->_M_lock );
#endif
#ifdef __FIT_UITHREADS
#error Fix me!
        return mutex_trylock( &this->_M_lock );
#endif
#ifdef __FIT_WIN32THREADS
#error Fix me!
        return TryEnterCriticalSection( &this->_M_lock ) != 0 ? 0 : -1;
#endif
#ifdef _NOTHREADS
#error Fix me!
        return 0;
#endif
      }

    int try_lock()
      {
#ifdef _PTHREADS
        return pthread_rwlock_trywrlock( &this->_M_lock );
#endif
#ifdef __FIT_UITHREADS
#error Fix me!
        return mutex_trylock( &this->_M_lock );
#endif
#ifdef __FIT_WIN32THREADS
#error Fix me!
        return TryEnterCriticalSection( &this->_M_lock ) != 0 ? 0 : -1;
#endif
#ifdef _NOTHREADS
#error Fix me!
        return 0;
#endif
      }

#endif // !WIN32 || _WIN32_WINNT >= 0x0400

    void unlock()
      {
#ifdef _PTHREADS
        pthread_rwlock_unlock( &this->_M_lock );
#endif
#ifdef __FIT_UITHREADS
#error Fix me!
        mutex_unlock( &this->_M_lock );
#endif
#ifdef __FIT_WIN32THREADS
#error Fix me!
        LeaveCriticalSection( &this->_M_lock );
#endif
      }

  private:
    __rw_mutex( const __rw_mutex& )
      { }
};

#endif // __FIT_RWLOCK

template <class M>
class basic_lock
{
  public:
    basic_lock( const M& point, bool initially_locked = true ) :
        m( point ),
        lk( false )
      { if ( initially_locked ) lock(); }
    ~basic_lock()
      { if ( lk ) const_cast<M&>(m).unlock(); }

    void lock()
      {
        if ( lk ) {
          throw lock_error( 0 );
        }
        const_cast<M&>(m).lock();
        lk = true;
      }

    void unlock()
      {
        if ( !lk ) {
          throw lock_error( 0 );
        }
        lk = false;
        const_cast<M&>(m).unlock();
      }

  private:
    basic_lock( const basic_lock& )
      { }
    basic_lock& operator =( const basic_lock& )
      { return *this; }

    const M& m;
    bool lk;
};

#ifdef __FIT_RWLOCK
template <class M>
class basic_read_lock
{
  public:
    basic_read_lock( const M& point, bool initially_locked = true ) :
        m( point ),
        lk( false )
      { if ( initially_locked ) lock(); }
    ~basic_read_lock()
      { if ( lk ) const_cast<M&>(m).unlock(); }

    void lock()
      {
        if ( lk ) {
          throw lock_error( 0 );
        }
        const_cast<M&>(m).rdlock();
        lk = true;
      }

    void unlock()
      {
        if ( !lk ) {
          throw lock_error( 0 );
        }
        lk = false;
        const_cast<M&>(m).unlock();
      }

  private:
    basic_read_lock( const basic_read_lock& )
      { }
    basic_read_lock& operator =( const basic_read_lock& )
      { return *this; }

    const M& m;
    bool lk;
};
#endif // __FIT_RWLOCK

typedef __mutex<false,false>  mutex;
typedef __mutex<true,false>   recursive_mutex;
typedef __mutex<false,true>   shared_mutex;
typedef __mutex<true,true>    shared_recursive_mutex;
#ifdef __FIT_RWLOCK
typedef __rw_mutex<false>     rw_mutex;
#endif // __FIT_RWLOCK
#ifdef __FIT_PTHREAD_SPINLOCK
typedef __spinlock<false,false> spinlock;
typedef __spinlock<true,false>  recursive_spinlock;
#endif // __FIT_RWLOCK

typedef basic_lock<mutex>           scoped_lock;
typedef basic_lock<recursive_mutex> recursive_scoped_lock;
#ifdef __FIT_RWLOCK
typedef basic_read_lock<__rw_mutex<false> >  rd_scoped_lock;
typedef basic_lock<__rw_mutex<false> >       wr_scoped_lock;
#endif // __FIT_RWLOCK
#ifdef __FIT_PTHREAD_SPINLOCK
typedef basic_lock<spinlock>            spin_scoped_lock;
typedef basic_lock<recursive_spinlock>  recursive_spin_scoped_lock;
#endif // __FIT_RWLOCK

class native_scoped_lock
{
  public:
#ifdef _PTHREADS
    explicit native_scoped_lock( const pthread_mutex_t& m ) :
#endif
#ifdef __FIT_UITHREADS
    explicit native_scoped_lock( const mutex_t& m ) :
#endif
#ifdef __FIT_WIN32THREADS
    explicit native_scoped_lock( const CRITICAL_SECTION& m ) :
#endif
        _M_lock( m )
      {
#ifdef _PTHREADS
        pthread_mutex_lock( const_cast<pthread_mutex_t *>(&_M_lock) );
#endif
#ifdef __FIT_UITHREADS
        mutex_lock( const_cast<mutex_t *>(&_M_lock) );
#endif
#ifdef __FIT_WIN32THREADS
        EnterCriticalSection( const_cast<CRITICAL_SECTION *>(&_M_lock) );
#endif
      }

    ~native_scoped_lock()
      {
#ifdef _PTHREADS
        pthread_mutex_unlock( const_cast<pthread_mutex_t *>(&_M_lock) );
#endif
#ifdef __FIT_UITHREADS
        mutex_unlock( const_cast<mutex_t *>(&_M_lock) );
#endif
#ifdef __FIT_WIN32THREADS
        LeaveCriticalSection( const_cast<CRITICAL_SECTION *>(&_M_lock) );
#endif
      }

  private:
    native_scoped_lock( const native_scoped_lock& m ) :
        _M_lock( m._M_lock )
      { }
#ifdef _PTHREADS
    const pthread_mutex_t& _M_lock;
#endif
#ifdef __FIT_UITHREADS
    const mutex_t& _M_lock;
#endif
#ifdef __FIT_WIN32THREADS
    const CRITICAL_SECTION& _M_lock;
#endif
};

template <bool SCOPE>
class __condition
{
  public:
    __condition() :
        _val( true )
      {
#ifdef __FIT_WIN32THREADS
        _cond = CreateEvent( 0, TRUE, TRUE, 0 );
#endif
#ifdef _PTHREADS
        if ( SCOPE ) {
          pthread_condattr_t attr;
          pthread_condattr_init( &attr );
          pthread_condattr_setpshared( &attr, PTHREAD_PROCESS_SHARED );
          pthread_cond_init( &_cond, &attr );
          pthread_condattr_destroy( &attr );
        } else {
          pthread_cond_init( &_cond, 0 );
        }
#endif
#ifdef __FIT_UITHREADS
        cond_init( &_cond, 0, 0 );
#endif
      }

    ~__condition()
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

    bool set( bool __v, bool _broadcast = false )
      {
        basic_lock<__mutex<false,SCOPE> > _x1( _lock );

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
          if ( _broadcast ) {
            cond_broadcast( &_cond );
          } else {
            cond_signal( &_cond );
          }
        }
#endif
#ifdef _PTHREADS
        if ( __v == true && tmp == false ) {
          if ( _broadcast ) {
            pthread_cond_broadcast( &_cond );
          } else {
            pthread_cond_signal( &_cond );
          }
        }
#endif
        return tmp;
      }

    bool set() const
      { return _val; }

    int try_wait()
      {
        basic_lock<__mutex<false,SCOPE> > _x1( _lock );

        if ( _val == false ) {
#ifdef __FIT_WIN32THREADS
          _x1.unlock();
          if ( WaitForSingleObject( _cond, -1 ) == WAIT_FAILED ) {
            return -1;
          }
          return 0;
#endif
#if defined(__FIT_UITHREADS) || defined(_PTHREADS)
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
        basic_lock<__mutex<false,SCOPE> > lk( _lock );
        _val = false;

#ifdef __FIT_WIN32THREADS
        ResetEvent( _cond );
        lk.unlock();
        if ( WaitForSingleObject( _cond, -1 ) == WAIT_FAILED ) {
          return -1;
        }
        return 0;
#endif
#if defined(_PTHREADS) || defined(__FIT_UITHREADS)
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

    int wait_time( const ::timespec *abstime );
    int wait_time( const ::timespec& abstime )
      { return wait_time( &abstime ); }

    int wait_delay( const ::timespec *abstime );
    int wait_delay( const ::timespec& abstime )
      { return wait_time( &abstime ); }

    int try_wait_time( const ::timespec *abstime );
    int try_wait_time( const ::timespec& abstime )
      { return try_wait_time( &abstime ); }

    int try_wait_delay( const ::timespec *abstime );
    int try_wait_delay( const ::timespec& abstime )
      { return try_wait_delay( &abstime ); }

    int signal( bool _broadcast = false )
      {
        basic_lock<__mutex<false,SCOPE> > _x1( _lock );

        _val = true;
#ifdef __FIT_WIN32THREADS
        return SetEvent( _cond ) == FALSE ? -1 : 0;
#endif
#ifdef _PTHREADS
        return _broadcast ? pthread_cond_broadcast( &_cond ) : pthread_cond_signal( &_cond );
#endif
#ifdef __FIT_UITHREADS
        return _broadcast ? cond_broadcast( &_cond ) : cond_signal( &_cond );
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
    __mutex<false,SCOPE> _lock;
    bool _val;

  private:
    __condition( const __condition& )
      { }
};

typedef __condition<false> condition;

template <bool SCOPE>
class __semaphore
{
  public:
    __semaphore( int cnt = 1 )
      {
#ifdef __FIT_WIN32THREADS
        _sem = CreateSemaphore( NULL, cnt, INT_MAX, 0 ); // check!
        _cnt = cnt;
#endif
#ifdef __FIT_UITHREADS
        sema_init( &_sem, cnt, SCOPE ? USYNC_PROCESS : USYNC_THREAD, 0 );
#endif
#ifdef _PTHREADS
        sem_init( &_sem, SCOPE ? 1 : 0, cnt );
#endif
      }

    ~__semaphore()
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
        --_cnt;
        if ( WaitForSingleObject( _sem, -1 ) == WAIT_FAILED ) {
          ++_cnt;
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

    __FIT_DECLSPEC int wait_time( const ::timespec *t ); // wait for time t, or signal
    int wait_time( const ::timespec& t )
      { return wait_time( &t ); }
    __FIT_DECLSPEC int wait_delay( const ::timespec *t ); // wait, timeout is delay t, or signal
    int wait_delay( const ::timespec& t )
      { return wait_delay( &t ); }

    int try_wait()
      {
#ifdef __FIT_WIN32THREADS
        return _cnt > 0 ? (--_cnt, this->wait()) : -1;
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
        return ReleaseSemaphore( _sem, 1, &_cnt ) != 0 ? (++_cnt, 0) : -1;
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
        return static_cast<int>(_cnt);
#endif
#ifdef __FIT_UITHREADS
# warning "No semaphore value for Solaris threads!"
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
    long _cnt;
#endif
#ifdef __FIT_UITHREADS
    sema_t _sem;
#endif
#ifdef _PTHREADS
    sem_t _sem;
#endif
  private:
    __semaphore( const __semaphore& )
      { }
};

typedef __semaphore<false> semaphore;

template <bool SCOPE>
int __semaphore<SCOPE>::wait_time( const ::timespec *abstime ) // wait for time t, or signal
{
#ifdef __FIT_WIN32THREADS
  time_t ct = time( 0 );
  time_t _conv = abstime->tv_sec * 1000 + abstime->tv_nsec / 1000000;

  unsigned ms = _conv >= ct ? _conv - ct : 1;

  if ( WaitForSingleObject( _sem, ms ) == WAIT_OBJECT_0 ) {
    return 0;
  }
  return -1;
#endif
#ifdef __FIT_UITHREADS
#warning "Fix me!"
#endif
#ifdef _PTHREADS
# if !(defined(__FreeBSD__) || defined(__OpenBSD__))
  return sem_timedwait( &_sem, abstime );
# else
  return -1; // not implemented
# endif
#endif
}

template <bool SCOPE>
int __semaphore<SCOPE>::wait_delay( const ::timespec *interval ) // wait, timeout is delay t, or signal
{
#ifdef __FIT_WIN32THREADS
  unsigned ms = interval->tv_sec * 1000 + interval->tv_nsec / 1000000;

  if ( WaitForSingleObject( _sem, ms ) == WAIT_OBJECT_0 ) {
    return 0;
  }
  return -1;
#endif
#ifdef __FIT_UITHREADS
#warning "Fix me!"
#endif
#ifdef _PTHREADS
  timespec st;
  xmt::gettime( &st );
  st += *interval;
# if !(defined(__FreeBSD__) || defined(__OpenBSD__))
  return sem_timedwait( &_sem, &st );
# else
  return -1; // not implemented
# endif
#endif
}

template <bool SCOPE>
class __barrier
{
  public:
    __barrier( unsigned cnt = 2 )
      {
#ifdef _PTHREADS
        pthread_barrierattr_t attr;
        pthread_barrierattr_init( &attr );
        pthread_barrierattr_setpshared( &attr, SCOPE ? PTHREAD_PROCESS_SHARED : PTHREAD_PROCESS_PRIVATE );
        pthread_barrier_init( &_barr, &attr, cnt );
        pthread_barrierattr_destroy( &attr );
#endif
      }

    ~__barrier()
      {
#ifdef _PTHREADS
        pthread_barrier_destroy( &_barr );
#endif
      }

    int wait()
      {
#ifdef _PTHREADS
        return pthread_barrier_wait( &_barr );
#endif
      }

  private:
#ifdef _PTHREADS
    pthread_barrier_t _barr;
#endif
};

typedef __barrier<false> barrier;

__FIT_DECLSPEC void fork() throw( fork_in_parent, std::runtime_error );
__FIT_DECLSPEC void become_daemon() throw( fork_in_parent, std::runtime_error );
__FIT_DECLSPEC void block_signal( int sig );
__FIT_DECLSPEC void unblock_signal( int sig );
__FIT_DECLSPEC int signal_handler( int sig, SIG_PF );
__FIT_DECLSPEC int signal_handler( int sig, siginfo_handler_type );

class Thread
{
  public:
#ifdef _PTHREADS
    typedef void * ret_t;
#endif
#ifdef __FIT_WIN32THREADS
    typedef long ret_t;
#endif

    typedef ret_t (*entrance_type)( void * );
#ifdef __FIT_WIN32THREADS
    typedef unsigned long thread_key_type;
    typedef HANDLE thread_id_type;
    // typedef unsigned long thread_id_type;
#endif
#ifdef _PTHREADS
    typedef pthread_key_t thread_key_type;
    typedef pthread_t     thread_id_type;
#endif
#ifdef __FIT_UITHREADS
    typedef thread_key_t thread_key_type;
    typedef thread_t     thread_id_type;
#endif

    enum {
      // thread mode flags
#ifdef __FIT_UITHREADS // __STL_SOLARIS_THREADS
      bound     = THR_BOUND,
      detached  = THR_DETACHED,
      new_lwp   = THR_NEW_LWP,
      suspended = THR_SUSPENDED,
      daemon    = THR_DAEMON,
#endif
#if defined(_PTHREADS)
      bound     = PTHREAD_SCOPE_SYSTEM,   // otherwise, PTHREAD_SCOPE_PROCESS, default
      detached  = PTHREAD_CREATE_DETACHED,// otherwise, PTHREAD_CREATE_JOINABLE, default
      new_lwp   = 0, // pthread_setconcurrency( pthread_getconcurrency() + 1 );
      suspended = 0,
      daemon    = detached,
#endif
#ifdef __FIT_WIN32THREADS
      bound     = 0,
      detached  = 0x2,
      new_lwp   = 0,
      suspended = CREATE_SUSPENDED,
      daemon    = detached,
#endif
      // state flags
      goodbit = 0x00,
      badbit  = 0x01
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

    explicit __FIT_DECLSPEC Thread( entrance_type entrance, const void *p = 0, size_t psz = 0, unsigned flags = 0, size_t stack_sz = 0 );

    __FIT_DECLSPEC ~Thread();

    __FIT_DECLSPEC
    void launch( entrance_type entrance, const void *p = 0, size_t psz = 0, size_t stack_sz = 0 );

    __FIT_DECLSPEC ret_t join();
    __FIT_DECLSPEC int suspend();
    __FIT_DECLSPEC int resume();
    __FIT_DECLSPEC int kill( int sig );
#ifdef __FIT_UITHREADS
    static __FIT_DECLSPEC int join_all();
#endif
    static __FIT_DECLSPEC void signal_exit( int sig ); // signal handler
#if defined(_PTHREADS)
    static int yield()
      { return sched_yield(); }
#endif

    bool good() const
      { /* Locker lk( _llock ); */ return (_id != bad_thread_id); }
    bool bad() const
      { /* Locker lk( _llock ); */ return (_id == bad_thread_id); }
    bool is_join_req() const // if true, you can (and should) use join()
      { scoped_lock lk( _rip_id_lock ); return (_rip_id != bad_thread_id) && ((_flags & (daemon | detached)) == 0); }

    __FIT_DECLSPEC bool is_self();

    static __FIT_DECLSPEC int xalloc();
    long&  iword( int __idx )
      {
        // _STLP_ASSERT( is_self() );
        return *static_cast<long *>(_alloc_uw( __idx ));
      }
    void*& pword( int __idx )
      {
        // _STLP_ASSERT( is_self() );
        return *reinterpret_cast<void **>(_alloc_uw( __idx ));
      }

    static thread_key_type mtkey()
      { return _mt_key; }

    static const thread_id_type bad_thread_id;

  protected:
    static __FIT_DECLSPEC void _exit( int code = 0 );

  private:
    Thread( const Thread& )
      { }

    bool _not_run() const
      { /* Locker lk( _llock ); */ return _id == bad_thread_id; }
    void _create( const void *p, size_t psz ) throw( std::runtime_error);

    static void *_call( void *p );
#ifdef WIN32
    statuc unsigned long __stdcall _call( void *p );
#endif

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
    static mutex _idx_lock;
    static thread_key_type& _mt_key;
    size_t uw_alloc_size;

    thread_id_type _id;
    thread_id_type _rip_id;
    mutex _rip_id_lock;
#ifdef _PTHREADS
# ifndef __hpux
    // sorry, POSIX threads don't have suspend/resume calls, so it should
    // be simulated via cond_wait
    __condition<false> _suspend;
# endif
#endif
#ifdef __FIT_WIN32THREADS
    unsigned long _thr_id;
#endif
    entrance_type _entrance;
    void *_param;
    size_t _param_sz;
    unsigned _flags;
    size_t _stack_sz; // stack size, if not 0
#ifdef __FIT_CREATE_THREAD_STACK_INFO
    std::string _stack_on_create;
#endif
    friend class Init;
    // extern "C", wrap for thread_create
// #ifdef __unix
//     friend void *_xcall( void * );
// #endif
// #ifdef __FIT_WIN32THREADS
//     friend unsigned long __stdcall _xcall( void *p );
// #endif
};

template <bool SCOPE>
int __condition<SCOPE>::try_wait_time( const ::timespec *abstime )
{
#if defined(__FIT_WIN32THREADS)
  MT_LOCK( _lock );
#endif
#if defined(__FIT_UITHREADS) || defined(_PTHREADS)
  scoped_lock _x1( _lock );
#endif
  if ( _val == false ) {
#ifdef __FIT_WIN32THREADS
    ResetEvent( _cond );
    time_t ct = time( 0 );
    unsigned ms = abstime->tv_sec >= ct ? (abstime->tv_sec - ct) * 1000 + abstime->tv_nsec / 1000000 : 1;
    MT_UNLOCK( _lock );
    int ret = WaitForSingleObject( _cond, ms );
    if ( ret == WAIT_FAILED ) {
      return -1;
    }
    if ( ret == WAIT_TIMEOUT ) {
      SetEvent( _cond );
      return ETIME;
    }
    return 0;
#endif
#if defined(__FIT_UITHREADS) || defined(_PTHREADS)
    int ret = 0;
    while ( !_val ) {
# ifdef _PTHREADS
      ret = pthread_cond_timedwait( &_cond, &_lock._M_lock, abstime );
      if ( ret == ETIMEDOUT ) {
        break;
      }
# endif
# ifdef __FIT_UITHREADS
      ret = cond_timedwait( &_cond, /* &_lock.mutex */ &_lock._M_lock, abstime );
      if ( ret == ETIME ) {
        ret = ETIMEDOUT;
      } else if ( ret == ETIMEDOUT ) {
        break;
      }
# endif
    }

    return ret;
#endif // _PTHREADS || __FIT_UITHREADS
#ifdef _NOTHREADS
    return 0;
#endif
  }
#if defined(__FIT_WIN32THREADS)
  MT_UNLOCK( _lock );
#endif
  return 0;
}

template <bool SCOPE>
int __condition<SCOPE>::try_wait_delay( const ::timespec *interval )
{
#if defined(__FIT_WIN32THREADS)
  MT_LOCK( _lock );
#endif
#if defined(__FIT_UITHREADS) || defined(_PTHREADS)
  scoped_lock _x1( _lock );
#endif
  if ( _val == false ) {
#ifdef WIN32
    _val = false;
    ResetEvent( _cond );
    MT_UNLOCK( _lock );
    unsigned ms = interval->tv_sec * 1000 + interval->tv_nsec / 1000000;
    int ret = WaitForSingleObject( _cond, ms );
    if ( ret == WAIT_FAILED ) {
      return -1;
    }
    if ( ret == WAIT_TIMEOUT ) {
      SetEvent( _cond );
      return ETIME;
    }
    return 0;
#endif
#if defined(__FIT_UITHREADS) || defined(_PTHREADS)
    ::timespec ct;
    xmt::gettime( &ct );
    ct += *interval;

    int ret = 0;
    while ( !_val ) {
# ifdef _PTHREADS
      ret = pthread_cond_timedwait( &_cond, &_lock._M_lock, &ct );
      if ( ret == ETIMEDOUT ) {
        break;
      }
# endif
# ifdef __FIT_UITHREADS
      ret = cond_timedwait( &_cond, /* &_lock.mutex */ &_lock._M_lock, &ct );
      if ( ret == ETIME ) {
        ret = ETIMEDOUT;
      } else if ( ret == ETIMEDOUT ) {
        break;
      }
# endif
    }

    return ret;
#endif // _PTHREADS || __FIT_UITHREADS

#ifdef _NOTHREADS
    return 0;
#endif
  }

#if defined(__FIT_WIN32THREADS)
  MT_UNLOCK( _lock );
#endif
  return 0;
}

template <bool SCOPE>
int __condition<SCOPE>::wait_time( const ::timespec *abstime )
{
#ifdef __FIT_WIN32THREADS
  MT_LOCK( _lock );
  _val = false;
  ResetEvent( _cond );
  time_t ct = time( 0 );
  unsigned ms = abstime->tv_sec >= ct ? (abstime->tv_sec - ct) * 1000 + abstime->tv_nsec / 1000000 : 1;
  MT_UNLOCK( _lock );
  int ret = WaitForSingleObject( _cond, ms );
  if ( ret == WAIT_FAILED ) {
    return -1;
  }
  if ( ret == WAIT_TIMEOUT ) {
    SetEvent( _cond );
    return ETIME;
  }
  return 0;
#endif
#ifdef _PTHREADS
  scoped_lock _x1( _lock ); // ??
  _val = false;
  int ret = pthread_cond_timedwait( &_cond, &_lock._M_lock, abstime );
  if ( ret == ETIMEDOUT ) {
    _val = true;
  }
  return ret;
#endif // _PTHREADS
#ifdef __FIT_UITHREADS
  scoped_lock _x1( _lock );
  _val = false;
  int ret;
  while ( !_val ) {
    ret = cond_timedwait( &_cond, /* &_lock.mutex */ &_lock._M_lock, abstime );
    if ( ret == ETIME ) {
      _val = true;
      ret = ETIMEDOUT;
    } else if ( ret == ETIMEDOUT ) {
      _val = true;
    }
  }

  return ret;
#endif
#ifdef _NOTHREADS
  return 0;
#endif
}

template <bool SCOPE>
int __condition<SCOPE>::wait_delay( const ::timespec *interval )
{
#ifdef __FIT_WIN32THREADS
  MT_LOCK( _lock );
  _val = false;
  ResetEvent( _cond );
  unsigned ms = interval->tv_sec * 1000 + interval->tv_nsec / 1000000;
  MT_UNLOCK( _lock );
  int ret = WaitForSingleObject( _cond, ms );
  if ( ret == WAIT_FAILED ) {
    return -1;
  }
  if ( ret == WAIT_TIMEOUT ) {
    SetEvent( _cond );
    return ETIME;
  }
  return 0;
#endif
#if defined(__FIT_UITHREADS) || defined(_PTHREADS)
  ::timespec ct;
  xmt::gettime( &ct );
  ct += *interval;

  return this->wait_time( &ct );
#endif
#ifdef _NOTHREADS
  return 0;
#endif
}

pid_t getpid();
pid_t getppid();

} // namespace xmt

namespace __impl = xmt; // compatibility

#endif // __XMT_H
