// -*- C++ -*- Time-stamp: <02/08/01 09:18:13 ptr>

/*
 * Copyright (c) 1997-1999, 2002
 * Petr Ovtchenkov
 *
 * Copyright (c) 1999-2001
 * Parallel Graphics Ltd.
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

#ifdef __unix
#  ifdef __HP_aCC
#pragma VERSIONID "@(#)$Id$"
#  else
#pragma ident "@(#)$Id$"
#  endif
#endif

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <xmt.h>

#include <cstring>
#ifndef _WIN32
#  include <ostream>
#endif

#include <iostream>
#include <iomanip>
#include <memory>
#include <functional>
#include <cerrno>
#include <string>

#ifdef __linux
#  ifndef __USE_GNU
#    define __USE_GNU
#  endif
#  include <sys/time.h>
#endif

#include <cmath> // for time operations

#ifdef WIN32
// #include <iostream>
// #include <iomanip>
// #include <win_config.h>

// using namespace std;
#endif

/*
extern "C" {
#ifdef WIN32
  typedef unsigned long (__stdcall *entrance_type_C)( void * );
#else
  typedef void *(*entrance_type_C)( void * );
#endif
}
*/

#ifdef WIN32
#  if 0
extern "C" int APIENTRY
DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved )
{
  return TRUE;   // ok
}
#  endif
#endif

int Init_count = 0;

#ifdef WIN32
unsigned long _mt_key = __STATIC_CAST(unsigned long,-1);
#else
__impl::Thread::thread_key_type _mt_key = __STATIC_CAST(__impl::Thread::thread_key_type,-1);
void *_uw_save = 0;
#endif


#ifdef _PTHREADS
__impl::Mutex _F_lock;
#  define _F_locklock   _F_lock.lock();
#  define _F_lockunlock _F_lock.unlock();
#endif

#ifdef __FIT_UITHREADS
#  error "Unimplemented"
#endif

#ifdef __FIT_WIN32THREADS
#  define _F_locklock
#  define _F_lockunlock
#endif

extern "C" void __at_fork_prepare()
{
  _F_locklock
#ifdef _PTHREADS
  if ( Init_count > 0 ) {
    _uw_save = pthread_getspecific( ::_mt_key );
  }
#endif
}

extern "C" void __at_fork_parent()
{
  _F_lockunlock
#ifdef _PTHREADS
#endif
}

extern "C" void __at_fork_child()
{
#ifdef _PTHREADS
  if ( Init_count > 0 ) {
     // otherwise we do it in Thread::Init::Init() below
    pthread_atfork( __at_fork_prepare, __at_fork_parent, __at_fork_child );
    pthread_key_create( &::_mt_key, 0 );
    pthread_setspecific( _mt_key, _uw_save );
    _uw_save = 0;
    // Note, that only calling thread inherited when we use POSIX:
    Init_count = 1; // i.e. only ONE (calling) thread...
  }
#endif
  _F_lockunlock
}

namespace __impl {

#ifndef _WIN32
using std::cerr;
using std::endl;
#endif

__FIT_DECLSPEC
int Condition::try_wait_time( const timespec *abstime )
{
  if ( _val == false ) {
#ifdef WIN32
    MT_LOCK( _lock );
    _val = false;
    ResetEvent( _cond );
    MT_UNLOCK( _lock );
    time_t ct = time( 0 );
    unsigned ms = abstime->tv_sec >= ct ? abstime->tv_sec - ct + abstime->tv_nsec / 1000000 : 1;
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
    MT_REENTRANT( _lock, _x1 ); // ??
    int ret = 0;
    timespec _abstime = *abstime;
    while ( !_val ) {
      ret = pthread_cond_timedwait( &_cond, &_lock._M_lock, &_abstime );
      if ( ret == ETIMEDOUT ) {
        break;
      }
    }

    return ret;
#endif // _PTHREADS
#ifdef __FIT_UITHREADS
    MT_REENTRANT( _lock, _x1 );
    int ret = 0;
    timespec _abstime = *abstime;
    while ( !_val ) {
      ret = cond_timedwait( &_cond, /* &_lock.mutex */ &_lock._M_lock, &_abstime );
      if ( ret == ETIME ) {
        ret = ETIMEDOUT;
      } else if ( ret == ETIMEDOUT ) {
        break;
      }
    }

    return ret;
#endif
#ifdef _NOTHREADS
    return 0;
#endif
  }

  return 0;
}

__FIT_DECLSPEC
int Condition::wait_time( const timespec *abstime )
{
#ifdef WIN32
  MT_LOCK( _lock );
  _val = false;
  ResetEvent( _cond );
  MT_UNLOCK( _lock );
  time_t ct = time( 0 );
  unsigned ms = abstime->tv_sec >= ct ? abstime->tv_sec - ct + abstime->tv_nsec / 1000000 : 1;
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
  MT_REENTRANT( _lock, _x1 ); // ??
  _val = false;
  timespec _abstime = *abstime;
  int ret = pthread_cond_timedwait( &_cond, &_lock._M_lock, &_abstime );
  if ( ret == ETIMEDOUT ) {
    _val = true;
  }
  return ret;
#endif // _PTHREADS
#ifdef __FIT_UITHREADS
  MT_REENTRANT( _lock, _x1 );
  _val = false;
  int ret;
  timespec _abstime = *abstime;
  while ( !_val ) {
    ret = cond_timedwait( &_cond, /* &_lock.mutex */ &_lock._M_lock, &_abstime );
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

char *Init_buf[32];
// int Thread::Init::_count = 0;
int& Thread::Init::_count( ::Init_count ); // trick to avoid friend declarations

const std::string msg1( "Can't create thread" );
const std::string msg2( "Can't fork" );

// __FIT_DECLSPEC
// void signal_throw( int sig ) throw( int )
// {
//   throw sig;
// }


Thread::Init::Init()
{
  // This is performance problem, let's consider replace to atomic lock...
  _F_locklock

  if ( _count++ == 0 ) {
#ifdef __FIT_UITHREADS
    thr_keycreate( &_mt_key, 0 );
#endif
#ifdef _PTHREADS
    if ( pthread_atfork( __at_fork_prepare, __at_fork_parent, __at_fork_child ) ) {
      _F_lockunlock
      throw std::runtime_error( "Problems with pthread_atfork" );
    }
    pthread_key_create( &_mt_key, 0 );
#endif
#ifdef __FIT_WIN32THREADS
    _mt_key = TlsAlloc();
#endif
    Thread::_self_idx = Thread::xalloc();
  }

  _F_lockunlock
}

Thread::Init::~Init()
{
  // This is performance problem, let's consider replace to atomic lock...
  _F_locklock

  if ( --_count == 0 ) {
#ifdef __FIT_WIN32THREADS
    TlsFree( _mt_key );
#endif
#ifdef _PTHREADS
    pthread_key_delete( _mt_key );
#endif
  }

  _F_lockunlock
}

Thread::alloc_type Thread::alloc;
int Thread::_idx = 0;
int Thread::_self_idx = 0;
Mutex Thread::_idx_lock;
Mutex Thread::_start_lock;

#ifdef WIN32
const Thread::thread_key_type Thread::bad_thread_key = INVALID_HANDLE_VALUE;
// unsigned long Thread::_mt_key = __STATIC_CAST(unsigned long,-1);
unsigned long& Thread::_mt_key( ::_mt_key );
#else
const Thread::thread_key_type Thread::bad_thread_key = __STATIC_CAST(Thread::thread_key_type,-1);
// Thread::thread_key_type Thread::_mt_key = __STATIC_CAST(Thread::thread_key_type,-1);
Thread::thread_key_type& Thread::_mt_key( ::_mt_key );
#endif

__FIT_DECLSPEC
void Thread::_dealloc_uw()
{
  if ( uw_alloc_size != 0 ) {
    _STLP_ASSERT( _id != bad_thread_key );
    _STLP_ASSERT( is_self() );
#ifdef __FIT_UITHREADS
    _uw_alloc_type *user_words;
    thr_getspecific( _mt_key, &(static_cast<void *>(user_words)) );
#endif
#ifdef _PTHREADS
    _uw_alloc_type *user_words = static_cast<_uw_alloc_type *>(pthread_getspecific( _mt_key ));
#endif
#ifdef __FIT_WIN32THREADS
    _uw_alloc_type *user_words = static_cast<_uw_alloc_type *>(TlsGetValue( _mt_key ));
#endif
    alloc.deallocate( user_words, uw_alloc_size );
    user_words = 0;
    uw_alloc_size = 0;
  }
}

__FIT_DECLSPEC
Thread::_uw_alloc_type *Thread::_alloc_uw( int __idx )
{
  _STLP_ASSERT( _id != bad_thread_key );
  _STLP_ASSERT( is_self() );

  _uw_alloc_type *user_words;

  if ( uw_alloc_size == 0 ) {
    uw_alloc_size = sizeof( _uw_alloc_type ) * (__idx + 1);
    user_words = alloc.allocate( uw_alloc_size );
    std::fill( user_words, user_words + uw_alloc_size, 0 );
#ifdef __FIT_UITHREADS
    thr_setspecific( _mt_key, user_words );
#endif
#ifdef _PTHREADS
    pthread_setspecific( _mt_key, user_words );
#endif
#ifdef __FIT_WIN32THREADS
    TlsSetValue( _mt_key, user_words );
#endif
  } else {
#ifdef __FIT_UITHREADS
    thr_getspecific( _mt_key, &(static_cast<void *>(user_words)) );
#endif
#ifdef _PTHREADS
    user_words = static_cast<_uw_alloc_type *>(pthread_getspecific( _mt_key ));
#endif
#ifdef __FIT_WIN32THREADS
    user_words = static_cast<_uw_alloc_type *>(TlsGetValue( _mt_key ));
#endif
    if ( (__idx + 1) * sizeof( _uw_alloc_type ) > uw_alloc_size ) {
      size_t tmp = sizeof( _uw_alloc_type ) * (__idx + 1);
       _uw_alloc_type *_mtmp = alloc.allocate( tmp );
      std::copy( user_words, user_words + uw_alloc_size, _mtmp );
      std::fill( _mtmp + uw_alloc_size, _mtmp + tmp, 0 );
      alloc.deallocate( user_words, uw_alloc_size );
      user_words = _mtmp;
      uw_alloc_size = tmp;
#ifdef __FIT_UITHREADS
      thr_setspecific( _mt_key, user_words );
#endif
#ifdef _PTHREADS
      pthread_setspecific( _mt_key, user_words );
#endif
#ifdef __FIT_WIN32THREADS
      TlsSetValue( _mt_key, user_words );
#endif
    }
  }

  return user_words + __idx;
}

__FIT_DECLSPEC
Thread::Thread( unsigned __f ) :
    _id( bad_thread_key ),
    _entrance( 0 ),
    _param( 0 ),
    _param_sz( 0 ),
    _flags( __f ),
    uw_alloc_size( 0 )
{
  new( Init_buf ) Init();
}

__FIT_DECLSPEC
Thread::Thread( Thread::entrance_type entrance, const void *p, size_t psz, unsigned __f ) :
    _entrance( entrance ),
    _param( 0 ),
    _param_sz( 0 ),
    _flags( __f ),
    uw_alloc_size( 0 )
{
  new( Init_buf ) Init();
  _create( p, psz );
}

__FIT_DECLSPEC
Thread::~Thread()
{
  if ( is_self() ) {
    _dealloc_uw();
  }

  ((Init *)Init_buf)->~Init();

#ifdef WIN32
  _STLP_ASSERT( _id == bad_thread_key );
#else
  // __stl_assert( _id == -1 );
  kill( SIGTERM );
#endif
}

__FIT_DECLSPEC
bool Thread::is_self()
{
#ifdef _PTHREADS
  return good() && (_id == pthread_self());
#elif defined( __FIT_UITHREADS )
  return good() && (_id == thr_self());
#else
#  error "Fix me! (replace pthread_self())"
#endif
}

__FIT_DECLSPEC
void Thread::launch( entrance_type entrance, const void *p, size_t psz )
{
  if ( _id == bad_thread_key ) {
    _entrance = entrance;
    _create( p, psz );
  }
}

__FIT_DECLSPEC
int Thread::join()
{
#ifdef __FIT_WIN32THREADS
  unsigned long ret_code = 0;
  if ( _id != bad_thread_key ) {
    WaitForSingleObject( _id, -1 );
    GetExitCodeThread( _id, &ret_code );
    _id = bad_thread_key;
  }
#else // !WIN32
  int ret_code = 0;
  if ( _id != bad_thread_key && (_flags & (daemon | detached) ) == 0 ) {
#  ifdef _PTHREADS
    pthread_join( _id, (void **)(&ret_code) );
#  endif
#  ifdef __FIT_UITHREADS
    thr_join( _id, 0, (void **)(&ret_code) );
#  endif
    _id = bad_thread_key;
  }
#endif // !WIN32

  return ret_code;
}

__FIT_DECLSPEC
int Thread::suspend()
{
  if ( _id != bad_thread_key ) {
#ifdef __FIT_WIN32THREADS
    return SuspendThread( _id );
#endif
#ifdef _PTHREADS
    // sorry, POSIX threads don't have pthread_{suspend,continue} calls, so it should
    // be simulated via condwait
#  ifdef __hpux
    // but HP-UX 11.00 implementation of POSIX threads has extention (or it in X/Open?)
    // pthread_{suspend,continue}, I use it:
    return pthread_suspend( _id );
#  else
    if ( _id != pthread_self() ) {
      throw std::domain_error( "Thread::suspend() for POSIX threads work only while call from the same thread." );
      // May be signalling pthread_kill( _id, SIG??? ) will be good workaround?
    }
    return _suspend.wait(); // thr_suspend and pthread_cond_wait return 0 in success
#  endif
#endif // __STL_PTHREADS
#ifdef __FIT_UITHREADS
    return thr_suspend( _id );
#endif
  }

  return -1;
}

__FIT_DECLSPEC
int Thread::resume()
{
  if ( _id != bad_thread_key ) {
#ifdef __FIT_WIN32THREADS
    return ResumeThread( _id );
#endif
#ifdef _PTHREADS
    // sorry, POSIX threads don't have pthread_{suspend,continue} calls, so it should
    // be simulated via condwait
#  ifdef __hpux
    // but HP-UX 11.00 implementation of POSIX threads has extention (or it in X/Open?)
    // pthread_{suspend,continue}, I use it:
    return pthread_continue( _id );
#  else
    return _suspend.set( true ) == false ? 0 : -1; // less syscall than _suspend.signal();
#  endif
    
#endif
#ifdef __FIT_UITHREADS
    return thr_continue( _id );
#endif
  }

  return -1;
}

__FIT_DECLSPEC
int Thread::kill( int sig )
{
  if ( _id != bad_thread_key ) {
#ifdef __FIT_UITHREADS
    return thr_kill( _id, sig );
#endif
#ifdef _PTHREADS
    return pthread_kill( _id, sig );
#endif
#ifdef __FIT_WIN32THREADS
  // The behavior of TerminateThread significant differ from SOLARIS and POSIX
  // threads, and I don't find analogs to workaround...
    return TerminateThread( _id, 0 ) ? 0 : -1;
#endif
  }
  return -1;
}

__FIT_DECLSPEC
void Thread::_exit( int code )
{
#ifdef _PTHREADS
  pthread_exit( (void *)code );
#endif
#ifdef __FIT_UITHREADS
  thr_exit( (void *)code );
#endif
#ifdef __FIT_WIN32THREADS
  ExitThread( code );
#endif
}

#ifdef __FIT_UITHREADS
__FIT_DECLSPEC
int Thread::join_all()
{
  while ( thr_join( 0, 0, 0 ) == 0 ) ;

  return 0;
}
#endif

__FIT_DECLSPEC
void Thread::block_signal( int sig )
{
#ifdef __unix
  sigset_t sigset;

  sigemptyset( &sigset );
  sigaddset( &sigset, sig );
#  ifdef __FIT_UITHREADS
  thr_sigsetmask( SIG_BLOCK, &sigset, 0 );
#  endif
#  ifdef _PTHREADS
  pthread_sigmask( SIG_BLOCK, &sigset, 0 );
#  endif
#endif // __unix
}

__FIT_DECLSPEC
void Thread::unblock_signal( int sig )
{
#ifdef __unix
  sigset_t sigset;

  sigemptyset( &sigset );
  sigaddset( &sigset, sig );
#  ifdef __FIT_UITHREADS
  thr_sigsetmask( SIG_UNBLOCK, &sigset, 0 );
#  endif
#  ifdef _PTHREADS
  pthread_sigmask( SIG_UNBLOCK, &sigset, 0 );
#  endif
#endif // __unix
}

__FIT_DECLSPEC
void Thread::signal_handler( int sig, SIG_PF handler )
{
#ifdef __unix  // catch SIGPIPE here
  struct sigaction act;

  sigemptyset( &act.sa_mask );
  sigaddset( &act.sa_mask, sig );
 
  act.sa_flags = 0; // SA_RESTART;
  act.sa_handler = handler;
  sigaction( sig, &act, 0 );
#endif // __unix
}

__FIT_DECLSPEC
void Thread::signal_exit( int sig )
{
#ifdef _PTHREADS
  _uw_alloc_type *user_words =
    static_cast<_uw_alloc_type *>(pthread_getspecific( _mt_key ))
    + Thread::_self_idx;
  Thread *me = reinterpret_cast<Thread *>(*reinterpret_cast<void **>(user_words));
  _STLP_ASSERT( me->is_self() );

  // follow part of _call
  if ( (me->_flags & (daemon | detached)) != 0 ) { // otherwise join expected
    me->_id = bad_thread_key;
  }
  void *_param     = me->_param;
  size_t _param_sz = me->_param_sz;
  try {
    if ( _param_sz > sizeof(void *) ) { // that's allocated
      delete [] __STATIC_CAST(char *,_param);
      _param_sz = 0;
      _param = 0;
    }
  }
  catch ( ... ) {
  }
#endif
  Thread::_exit( 0 );
}

__FIT_DECLSPEC
void Thread::sleep( timespec *t, timespec *r )
{
#ifdef __unix
  nanosleep( t, r );
#endif
#ifdef WIN32
  time_t ct = time( 0 );
  unsigned ms = t->tv_sec >= ct ? t->tv_sec - ct + t->tv_nsec / 1000000 : 1;
  Sleep( ms );
  if ( r != 0 ) {
    r->tv_sec = ms / 1000;
    r->tv_nsec = (ms % 1000) * 1000000;
  }
#endif
}

__FIT_DECLSPEC
void Thread::gettime( timespec *t )
{
#ifdef __linux
  timeval tv;
  gettimeofday( &tv, 0 );
  TIMEVAL_TO_TIMESPEC( &tv, t );
#elif defined( WIN32 )
  time_t ct = time( 0 );
  t->tv_sec = ct / 1000;
  t->tv_nsec = (ct % 1000) * 1000000;
#elif defined(__sun) || defined(__hpux)
  clock_gettime( CLOCK_REALTIME, t );
#else
#error "You should implement OS-dependent precise clock"
#endif
}

__FIT_DECLSPEC
void Thread::fork() throw( fork_in_parent, std::runtime_error )
{
  fork_in_parent f( ::fork() );
  if ( f.pid() > 0 ) {
    throw f;
  }
  if ( f.pid() == -1 ) {
    throw std::runtime_error( msg2 );
  }
}

__FIT_DECLSPEC
void Thread::become_daemon() throw( fork_in_parent, std::runtime_error )
{
  try {
    Thread::fork();

    // chdir( "/var/tmp" );
    ::setsid();   // become session leader
    ::close( 0 ); // close stdin
    ::close( 1 ); // close stdout
    ::close( 2 ); // close stderr
    // This is broken in some versions of glibc (Linux):
    ::open( "/dev/null", O_RDONLY, 0 ); // redirect stdin from /dev/null
    ::open( "/dev/null", O_WRONLY, 0 ); // redirect stdout to /dev/null
    ::open( "/dev/null", O_WRONLY, 0 ); // redirect stderr to /dev/null
  }
  catch ( fork_in_parent& ) {
    throw;
  }
  catch ( std::runtime_error& ) {
    throw;
  }
}

// #ifdef __GNUC__
// void Thread::_create( const void *p, size_t psz )
// #else
void Thread::_create( const void *p, size_t psz ) throw(std::runtime_error)
// #endif
{
  if ( psz > sizeof(void *) ) { // can't pass on pointer
    // Hey, deallocation SHOULD be either in this method, or in _call ONLY,
    // and never more!    
    _param = new char [psz];
#ifdef WIN32
    memcpy( _param, p, psz );
#else
    std::memcpy( _param, p, psz );
#endif
  } else {
    _param = const_cast<void *>(p);
  }
  _param_sz = psz;

  int err;
#ifdef _PTHREADS
  pthread_attr_t attr;
  if ( _flags != 0 ) {
    pthread_attr_init( &attr ); // pthread_attr_create --- HP-UX 10.20
    // pthread_attr_setstacksize( &attr, 0x80000 ); // min 0x50000
    if ( _flags & bound ) {
      pthread_attr_setscope( &attr, bound ); // PTHREAD_SCOPE_PROCESS
    }
    if ( _flags & detached ) { // the same as daemon: detached == daemon for POSIX
      pthread_attr_setdetachstate( &attr, detached ); // PTHREAD_CREATE_DETACHED
    }
    // pthread_attr_setinheritsched( &attr, PTHREAD_EXPLICIT_SCHED );
    // pthread_attr_setschedpolicy(&attr,SCHED_OTHER);
  }
  _start_lock.lock(); // allow finish new thread creation before this 
                      // thread will start to run
  err = pthread_create( &_id, _flags != 0 ? &attr : 0, _xcall, this );
  _start_lock.unlock();
  if ( _flags != 0 ) {
    pthread_attr_destroy( &attr );
  }
#endif
#ifdef __FIT_UITHREADS
  _start_lock.lock();
  err = thr_create( 0, 0, _xcall, this, _flags, &_id );
  _start_lock.unlock();
#endif
#ifdef __FIT_WIN32THREADS
  _start_lock.lock();
  _id = CreateThread( 0, 0, _xcall, this, _flags, &_thr_id );
  err = GetLastError();
  _start_lock.unlock();
#endif
  if ( err != 0 ) {
    if ( psz > sizeof(void *) ) { // clear allocated here
      delete [] __STATIC_CAST(char *,_param);
    }
    throw std::runtime_error( msg1 );
  }
}

#ifdef _WIN32
#pragma warning( disable : 4101 )
#endif

extern "C" {
#ifdef __unix
  void *_xcall( void *p )
  {
    return Thread::_call( p );
  }
#endif
#ifdef WIN32
  unsigned long __stdcall _xcall( void *p )
  {
    return (unsigned long)Thread::_call( p );
  }
#endif
} // extern "C"

void *Thread::_call( void *p )
{
  _start_lock.lock(); // allow finish thread creation in parent thread
  Thread *me = static_cast<Thread *>(p);

  // After exit of me->_entrance, there is may be no more *me itself,
  // so it's members may be unaccessible. Don't use me->"*" after call
  // of me->_entrance!!!
  void *_param     = me->_param;
  size_t _param_sz = me->_param_sz;
  int ret;

//#ifdef _PTHREADS
//#  ifndef __hpux
//  if ( me->_flags & (daemon | detached) ) {
//    pthread_detach( me->_id );
//  }
//#  endif
//#endif

#ifdef WIN32
  set_unexpected( unexpected );
  set_terminate( terminate );
#else
  std::set_unexpected( Thread::unexpected );
  std::set_terminate( Thread::terminate );
#endif

  me->pword( _self_idx ) = me; // to have chance make Thread sanity by signal
  signal_handler( SIGTERM, signal_exit ); // set handler for sanity
  _start_lock.unlock();
  try {
    ret = me->_entrance( me->_param );
    // I should make me->_id = bad_thread_key; here...
    // This is in conflict what I say in the begin of this function.
    // So don't delete Thread before it termination!

    if ( (me->_flags & (daemon | detached)) != 0 ) { // otherwise join expected
      me->_id = bad_thread_key;
    }
  }
  catch ( std::exception& e ) {
#ifndef _WIN32
    cerr << e.what() << endl;
#endif
    ret = -1;
  }
  catch ( int sig ) {
    // const char *_sig_ = strsignal( sig );
#ifndef _WIN32
    cerr << "\n--- Thread: signal " << sig /* (_sig_ ? _sig_ : "unknown") */ << " detected ---" << endl;
#endif
    ret = sig;
  }
  catch ( ... ) {
#ifndef _WIN32
    cerr << "\n--- Thread: unknown exception occur ---" << endl;
#endif
    ret = -1;
  }

  try {
    if ( _param_sz > sizeof(void *) ) { // that's allocated
      delete [] __STATIC_CAST(char *,_param);
      _param_sz = 0;
      _param = 0;
    }
  }
  catch ( ... ) {
    ret = -1;
  }

#if defined( __SUNPRO_CC ) && defined( __i386 )
  Thread::_exit( ret );
#endif
  return (void *)ret;
}
#ifdef _WIN32
#pragma warning( default : 4101 )
#endif

void Thread::unexpected()
{
#ifndef _WIN32
  cerr << "\nUnexpected exception" << endl;
#endif
  signal_exit( SIGTERM );  // Thread::_exit( 0 );
}

void Thread::terminate()
{
#ifndef _WIN32
  cerr << "\nTerminate exception" << endl;
#endif
  signal_exit( SIGTERM );  // Thread::_exit( 0 );
}

int Thread::xalloc()
{
  Locker _l( _idx_lock );
  return _idx++;
}

} // namespace __impl


timespec operator +( const timespec& a, const timespec& b )
{
  timespec c;

  c.tv_sec = a.tv_sec;
  c.tv_nsec = a.tv_nsec;
  c.tv_sec += b.tv_sec;
  c.tv_nsec += b.tv_nsec;
  c.tv_sec += c.tv_nsec / 1000000000;
  c.tv_nsec %= 1000000000;

  return c;
}

timespec operator -( const timespec& a, const timespec& b )
{
  timespec c;

  c.tv_sec = a.tv_sec > b.tv_sec ? a.tv_sec - b.tv_sec : 0; // out_of_range?
  if ( a.tv_nsec > b.tv_nsec ) {
    c.tv_nsec = a.tv_nsec - b.tv_nsec;
  } else if ( c.tv_sec > 0 ) {
    --c.tv_sec;
    c.tv_nsec = 1000000000 - a.tv_nsec + b.tv_nsec;
  } else {
    c.tv_nsec = 0; // out_of_range?
  }

  return c;
}

timespec operator /( const timespec& a, unsigned b )
{
  timespec c;
  double d = a.tv_sec + 1.0e-9 * a.tv_nsec;
  d /= b;

  c.tv_nsec = int(1.0e9 * modf( d, &d ) + 0.5);
  c.tv_sec = int(d);

  return c;
}

timespec operator /( const timespec& a, unsigned long b )
{
  timespec c;
  double d = a.tv_sec + 1.0e-9 * a.tv_nsec;
  d /= b;

  c.tv_nsec = int(1.0e9 * modf( d, &d ) + 0.5);
  c.tv_sec = int(d);

  return c;
}

timespec& operator +=( timespec& a, const timespec& b )
{
  a.tv_sec += b.tv_sec;
  a.tv_nsec += b.tv_nsec;
  a.tv_sec += a.tv_nsec / 1000000000;
  a.tv_nsec %= 1000000000;

  return a;
}

timespec& operator -=( timespec& a, const timespec& b )
{
  a.tv_sec = a.tv_sec > b.tv_sec ? a.tv_sec - b.tv_sec : 0; // out_of_range?
  if ( a.tv_nsec > b.tv_nsec ) {
    a.tv_nsec -= b.tv_nsec;
  } else if ( a.tv_sec > 0 ) {
    --a.tv_sec;
    a.tv_nsec = 1000000000 - a.tv_nsec + b.tv_nsec;
  } else {
    a.tv_nsec = 0; // out_of_range?
  }

  return a;
}

timespec& operator /=( timespec& a, unsigned b )
{
  double d = a.tv_sec + 1.0e-9 * a.tv_nsec;
  d /= b;

  a.tv_nsec = int(1.0e9 * modf( d, &d ) + 0.5);
  a.tv_sec = int(d);

  return a;
}

timespec& operator /=( timespec& a, unsigned long b )
{
  double d = a.tv_sec + 1.0e-9 * a.tv_nsec;
  d /= b;

  a.tv_nsec = int(1.0e9 * modf( d, &d ) + 0.5);
  a.tv_sec = int(d);

  return a;
}
