// -*- C++ -*- Time-stamp: <00/02/21 15:31:08 ptr>

#ident "$SunId$ %Q%"

#ifdef WIN32
#  ifdef _DLL
#    define __XMT_DLL __declspec( dllexport )
#  else
#    define __XMT_DLL
#  endif
#else
#  define __XMT_DLL
#endif

#include <xmt.h>

#include <cstring>
#ifndef _WIN32
#  include <ostream>
#endif
#ifdef __SGI_STL_OWN_IOSTREAMS
#include <iostream>
#endif
#include <memory>
#include <functional>
#include <cerrno>

#ifdef WIN32
// #include <iostream>
// #include <iomanip>
// #include <win_config.h>

using namespace std;
#endif

extern "C" {
#ifdef WIN32
  typedef unsigned long (__stdcall *entrance_type_C)( void * );
#else
  typedef void *(*entrance_type_C)( void * );
#endif
}

#ifdef WIN32
#  if 0
extern "C" int APIENTRY
DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved )
{
  return TRUE;   // ok
}
#  endif
#endif

namespace __impl {

#ifndef _WIN32
using __STD::cerr;
using __STD::endl;
#endif

#ifdef _WIN32
using std::timespec;
#endif

__XMT_DLL
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
  MT_REENTRANT( _lock, _1 ); // ??
  _val = false;
  timespec _abstime = *abstime;
  int ret = pthread_cond_wait( &_cond, &_lock._M_lock, &_abstime );
  if ( ret == ETIMEDOUT ) {
    _val = true;
  }
  return ret;
#endif
#ifdef __STL_UITHREADS
  MT_REENTRANT( _lock, _1 );
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
int Thread::Init::_count = 0;

__XMT_DLL
void signal_throw( int sig ) throw( int )
{ throw sig; }

Thread::Init::Init()
{
  if ( _count++ == 0 ) {
#ifdef __STL_UITHREADS
    thr_keycreate( &_mt_key, 0 );
#endif
#ifdef __STL_PTHREADS
    pthread_key_create( &_mt_key, 0 );
#endif
#ifdef __STL_WIN32THREADS
    _mt_key = TlsAlloc();
#endif
  }
}

Thread::Init::~Init()
{
  if ( --_count == 0 ) {
#ifdef __STL_WIN32THREADS
    TlsFree( _mt_key );
#endif
#ifdef __STL_PTHREADS
    pthread_key_delete( _mt_key );
#endif
  }
}

int Thread::_idx = 0;

#ifdef WIN32
const Thread::thread_key_type Thread::bad_thread_key = INVALID_HANDLE_VALUE;
unsigned long Thread::_mt_key = __STATIC_CAST(unsigned long,-1);
#else
const Thread::thread_key_type Thread::bad_thread_key = __STATIC_CAST(Thread::thread_key_type,-1);
Thread::thread_key_type Thread::_mt_key = __STATIC_CAST(Thread::thread_key_type,-1);
#endif

__XMT_DLL
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

__XMT_DLL
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

__XMT_DLL
Thread::~Thread()
{
  long **user_words;

#ifdef __STL_UITHREADS
  thr_getspecific( _mt_key, reinterpret_cast<void **>(&user_words) );
#endif
#ifdef __STL_PTHREADS
  user_words = pthread_getspecific( _mt_key );
#endif
#ifdef __STL_WIN32THREADS
  user_words = reinterpret_cast<long **>(TlsGetValue( _mt_key ));
#endif
  if ( user_words != 0 ) {
    alloc().deallocate( user_words, uw_alloc_size );
  }

  ((Init *)Init_buf)->~Init();

#ifdef WIN32
  __stl_assert( _id == bad_thread_key );
#else
  // __stl_assert( _id == -1 );
  kill( SIGTERM );
#endif
}

__XMT_DLL
void Thread::launch( entrance_type entrance, const void *p, size_t psz )
{
  if ( _id == bad_thread_key ) {
    _entrance = entrance;
    _create( p, psz );
  }
}

__XMT_DLL
int Thread::join()
{
#ifdef __STL_WIN32THREADS
  unsigned long ret_code = 0;
  if ( _id != bad_thread_key ) {
    WaitForSingleObject( _id, -1 );
    GetExitCodeThread( _id, &ret_code );
    _id = bad_thread_key;
  }
#else // !WIN32
  int ret_code = 0;
  if ( _id != bad_thread_key && (_flags & (daemon | detached) ) == 0 ) {
#  ifdef __STL_PTHREADS
    pthread_join( _id, (void **)(&ret_code) );
#  endif
#  ifdef __STL_UITHREADS
    thr_join( _id, 0, (void **)(&ret_code) );
#  endif
    _id = bad_thread_key;
  }
#endif // !WIN32

  return ret_code;
}

__XMT_DLL
int Thread::suspend()
{
  if ( _id != bad_thread_key ) {
#ifdef __STL_WIN32THREADS
    return SuspendThread( _id );
#endif
#ifdef __STL_PTHREADS
    // sorry, POSIX threads don't have suspend/resume calls, so it should
    // be simulated via condwait
    if ( _id != pthread_self() ) {
      throw domain_error( "Thread::suspend() for POSIX threads work only while call from the same thread." );
      // May be signalling pthread_kill( _id, SIG??? ) will be good workaround?
    }
    _suspend.wait();
#endif
#ifdef __STL_UITHREADS
    return thr_suspend( _id );
#endif
  }

  return -1;
}

__XMT_DLL
int Thread::resume()
{
  if ( _id != bad_thread_key ) {
#ifdef __STL_WIN32THREADS
    return ResumeThread( _id );
#endif
#ifdef __STL_PTHREADS
    // sorry, POSIX threads don't have suspend/resume calls, so it should
    // be simulated via condwait
    _suspend.set( true ); // less syscall than _suspend.signal();
#endif
#ifdef __STL_UITHREADS
    return thr_continue( _id );
#endif
  }

  return -1;
}

__XMT_DLL
int Thread::kill( int sig )
{
  if ( _id != bad_thread_key ) {
#ifdef __STL_UITHREADS
    return thr_kill( _id, sig );
#endif
#ifdef __STL_PTHREADS
    return pthread_kill( _id, sig );
#endif
#ifdef __STL_WIN32THREADS
  // The behavior of TerminateThread significant differ from SOLARIS and POSIX
  // threads, and I don't find analogs to workaround...
    return TerminateThread( _id, 0 ) ? 0 : -1;
#endif
  }
  return -1;
}

__XMT_DLL
void Thread::exit( int code )
{
#ifdef __STL_PTHREADS
  pthread_exit( (void *)code );
#endif
#ifdef __STL_UITHREADS
  thr_exit( (void *)code );
#endif
#ifdef __STL_WIN32THREADS
  ExitThread( code );
#endif
}

__XMT_DLL
int Thread::join_all()
{
#ifdef __STL_UITHREADS
  while ( thr_join( 0, 0, 0 ) == 0 ) ;
#endif

  return 0;
}

__XMT_DLL
void Thread::block_signal( int sig )
{
#ifdef __unix
  sigset_t sigset;

  sigemptyset( &sigset );
  sigaddset( &sigset, sig );
#  ifdef __STL_SOLARIS_THREADS
  thr_sigsetmask( SIG_BLOCK, &sigset, 0 );
#  endif
#  ifdef __STL_PTHREADS
  pthread_sigsetmask( SIG_BLOCK, &sigset, 0 );
#  endif
#endif // __unix
}

__XMT_DLL
void Thread::unblock_signal( int sig )
{
#ifdef __unix
  sigset_t sigset;

  sigemptyset( &sigset );
  sigaddset( &sigset, sig );
#  ifdef __STL_UITHREADS
  thr_sigsetmask( SIG_UNBLOCK, &sigset, 0 );
#  endif
#  ifdef __STL_PTHREADS
  pthread_sigsetmask( SIG_UNBLOCK, &sigset, 0 );
#  endif
#endif // __unix
}

__XMT_DLL
void Thread::signal_handler( int sig, SIG_PF handler )
{
#ifdef __unix  // catch SIGPIPE here
  struct sigaction act;

  sigemptyset( &act.sa_mask );
  sigaddset( &act.sa_mask, sig );
 
  act.sa_flags = 0;
  act.sa_handler = handler;
  sigaction( sig, &act, 0 );
#endif // __unix
}

__XMT_DLL
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

void Thread::_create( const void *p, size_t psz ) throw(runtime_error)
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
#ifdef __STL_PTHREADS
  err = pthread_create( &_id, 0, entrance_type_C(_call), this );
#endif
#ifdef __STL_UITHREADS
  err = thr_create( 0, 0, entrance_type_C(_call), this, _flags, &_id );
#endif
#ifdef __STL_WIN32THREADS
  _id = CreateThread( 0, 0, entrance_type_C(_call), this, _flags, &_thr_id );
  err = GetLastError();
#endif
  if ( err != 0 ) {
    if ( psz > sizeof(void *) ) { // clear allocated here
      delete [] __STATIC_CAST(char *,_param);
    }
    throw runtime_error( "Can't create thread" );
  }
}

#ifdef _WIN32
#pragma warning( disable : 4101 )
#endif

void *Thread::_call( void *p )
{
  Thread *me = static_cast<Thread *>(p);

  // After exit of me->_entrance, there is may be no more *me itself,
  // so it's members may be unaccessable. Don't use me->"*" after call
  // of me->_entrance!!!
  void *_param     = me->_param;
  size_t _param_sz = me->_param_sz;
  int ret;

#ifdef __STL_PTHREADS
  if ( me->_flags & (daemon | detached) ) {
    pthread_detach( me->_id );
  }
#endif

#ifdef WIN32
  set_unexpected( unexpected );
  set_terminate( terminate );
#else
  std::set_unexpected( unexpected );
  std::set_terminate( terminate );
#endif
	
  try {
    ret = me->_entrance( me->_param );
    // I should be make me->_id = bad_thread_key; here...
    // Next line is in conflict what I say in this function begin.
    // So don't delete Thread before it termination!

    me->_id = bad_thread_key;
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
  Thread::exit( ret );
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
  Thread::exit( -1 );
}

void Thread::terminate()
{
#ifndef _WIN32
  cerr << "\nTerminate exception" << endl;
#endif
  Thread::exit( -2 );
}

__XMT_DLL
long& Thread::iword( int __idx )
{
  long **user_words;

#ifdef __STL_UITHREADS
  thr_getspecific( _mt_key, reinterpret_cast<void **>(&user_words) );
#endif
#ifdef __STL_PTHREADS
  user_words = pthread_getspecific( _mt_key );
#endif
#ifdef __STL_WIN32THREADS
  user_words = reinterpret_cast<long **>(TlsGetValue( _mt_key ));
#endif
  if ( user_words == 0 ) {
    uw_alloc_size = sizeof( long ) * (__idx + 1);
#ifndef __STL_USE_SGI_ALLOCATORS // __STL_USE_STD_ALLOCATORS
#  ifdef _MSC_VER
    user_words = alloc().allocate( uw_alloc_size, (const void *)0 );
#  else
    user_words = alloc().allocate( uw_alloc_size );
#  endif
#else // __STL_USE_SGI_ALLOCATORS
    user_words = alloc::allocate( uw_alloc_size );
#endif // __STL_USE_SGI_ALLOCATORS
    __STD::fill( *user_words, *user_words + uw_alloc_size, 0 );
#ifdef __STL_UITHREADS
    thr_setspecific( _mt_key, user_words );
#endif
#ifdef __STL_PTHREADS
    pthread_setspecific( _mt_key, user_words );
#endif
#ifdef __STL_WIN32THREADS
    TlsSetValue( _mt_key, user_words );
#endif
  } else if ( (__idx + 1) * sizeof( long ) > uw_alloc_size ) {
    size_t tmp = sizeof( long ) * (__idx + 1);
#ifndef __STL_USE_SGI_ALLOCATORS // __STL_USE_STD_ALLOCATORS
#ifdef _MSC_VER
    long **_mtmp = alloc().allocate( tmp, (const void *)0 );
#else // __STL_USE_SGI_ALLOCATORS
    long **_mtmp = alloc().allocate( tmp );
#endif // __STL_USE_SGI_ALLOCATORS
    __STD::copy( *user_words, *user_words + uw_alloc_size, *_mtmp );
    alloc().deallocate( user_words, uw_alloc_size );
    user_words = _mtmp;
#else // !__STL_USE_STD_ALLOCATORS && !_MSC_VER
    user_words = alloc::reallocate( user_words, uw_alloc_size, tmp );
#endif // !__STL_USE_STD_ALLOCATORS && !_MSC_VER
    __STD::fill( *user_words + uw_alloc_size, *user_words + tmp, 0 );
    uw_alloc_size = tmp;
#ifdef __STL_UITHREADS
    thr_setspecific( _mt_key, user_words );
#endif
#ifdef __STL_PTHREADS
    pthread_setspecific( _mt_key, user_words );
#endif
#ifdef __STL_WIN32THREADS
    TlsSetValue( _mt_key, user_words );
#endif
  }

  long *_ytmp = (long *)&user_words[__idx];
  return *_ytmp;
}

__XMT_DLL
void*& Thread::pword( int __idx )
{
  long **user_words;

#ifdef __STL_UITHREADS
  thr_getspecific( _mt_key, reinterpret_cast<void **>(&user_words) );
#endif
#ifdef __STL_PTHREADS
  user_words = pthread_getspecific( _mt_key );
#endif
#ifdef __STL_WIN32THREADS
  user_words = reinterpret_cast<long **>( TlsGetValue( _mt_key ) );
#endif
  if ( user_words == 0 ) {
    uw_alloc_size = sizeof( long ) * (__idx + 1);
// #ifdef _MSC_VER
//    user_words = (long *)alloc().allocate( uw_alloc_size, (const void *)0 );
// #else
    user_words = alloc().allocate( uw_alloc_size );
// #endif
    __STD::fill( *user_words, *user_words + uw_alloc_size, 0 );
#ifdef __STL_UITHREADS
    thr_setspecific( _mt_key, user_words );
#endif
#ifdef __STL_PTHREADS
    pthread_setspecific( _mt_key, user_words );
#endif
#ifdef __STL_WIN32THREADS
    TlsSetValue( _mt_key, user_words );
#endif
  } else if ( (__idx + 1) * sizeof( long ) > uw_alloc_size ) {
    size_t tmp = sizeof( long ) * (__idx + 1);
// #if defined( __STL_USE_STD_ALLOCATORS ) || defined( _MSC_VER )
#ifndef  __STL_USE_SGI_ALLOCATORS
// #ifdef _MSC_VER
//     long *_mtmp = (long *)alloc().allocate( tmp, (const void *)0 );
// #else
    long **_mtmp = alloc().allocate( tmp );
// #endif
    __STD::copy( *user_words, *user_words + uw_alloc_size, *_mtmp );
    alloc().deallocate( user_words, uw_alloc_size );
    user_words = _mtmp;
#else // __STL_USE_SGI_ALLOCATORS
    user_words = alloc::reallocate( user_words, uw_alloc_size, tmp );
#endif // __STL_USE_SGI_ALLOCATORS
    __STD::fill( *user_words + uw_alloc_size, *user_words + tmp, 0 );
    uw_alloc_size = tmp;
#ifdef __STL_UITHREADS
    thr_setspecific( _mt_key, *user_words );
#endif
#ifdef __STL_PTHREADS
    pthread_setspecific( _mt_key, *user_words );
#endif
#ifdef __STL_WIN32THREADS
    TlsSetValue( _mt_key, *user_words );
#endif
  }

  // void *_xtmp = *(user_words + __idx);
  // void **_ytmp = (void **)(*user_words + __idx);
  void **_ytmp = (void **)&user_words[__idx];
  return *_ytmp;
}

} // namespace __impl
