// -*- C++ -*- Time-stamp: <99/08/17 12:28:21 ptr>

#ident "$SunId$ %Q%"

#include <xmt.h>

#include <cstring>
#ifndef _WIN32
#  include <ostream>
#endif
#include <memory>
#include <functional>

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
extern "C" int APIENTRY
DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved )
{
  return TRUE;   // ok
}
#endif

namespace __impl {

#ifndef _WIN32
using std::cerr;
using std::endl;
#endif

char *Init_buf[32];
int Thread::Init::_count = 0;

__DLLEXPORT
void signal_throw( int sig ) throw( int )
{ throw sig; }

Thread::Init::Init()
{
  if ( _count++ == 0 ) {
#ifdef __STL_SOLARIS_THREADS
    thr_keycreate( &_mt_key, 0 );
#endif
#ifdef _PTHREADS
    pthread_key_create( &_mt_key, 0 );
#endif
#ifdef WIN32
    _mt_key = TlsAlloc();
#endif
  }
}

Thread::Init::~Init()
{
  if ( --_count == 0 ) {
#ifdef WIN32
    TlsFree( _mt_key );
#endif
#ifdef _PTHREADS
    pthread_key_delete( _mt_key );
#endif
  }
}

int Thread::_idx = 0;
Thread::thread_key_type Thread::_mt_key = __STATIC_CAST(thread_t,-1);

__DLLEXPORT
Thread::Thread( unsigned __f ) :
#ifdef WIN32
    _id( INVALID_HANDLE_VALUE ),
#else
    _id( __STATIC_CAST(thread_t,-1) ),
#endif
    _entrance( 0 ),
    _param( 0 ),
    _param_sz( 0 ),
    _flags( __f ),
    uw_alloc_size( 0 )
{
  new( Init_buf ) Init();
}

__DLLEXPORT
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

__DLLEXPORT
Thread::~Thread()
{
  long **user_words;

#ifdef __STL_SOLARIS_THREADS
  thr_getspecific( _mt_key, reinterpret_cast<void **>(&user_words) );
#endif
#ifdef _PTHREADS
  user_words = pthread_getspecific( _mt_key );
#endif
#ifdef WIN32
  user_words = TlsGetValue( _mt_key );
#endif
  if ( user_words != 0 ) {
    alloc().deallocate( user_words, uw_alloc_size );
  }

  ((Init *)Init_buf)->~Init();

#ifdef WIN32
  __stl_assert( _id == INVALID_HANDLE_VALUE );
#else
  // __stl_assert( _id == -1 );
  kill( SIGTERM );
#endif
}

__DLLEXPORT
void Thread::launch( entrance_type entrance, const void *p, size_t psz )
{
#ifdef WIN32
  if ( _id == INVALID_HANDLE_VALUE ) {
#else
  if ( _id == -1 ) {
#endif
    _entrance = entrance;
    _create( p, psz );
  }
}

__DLLEXPORT
int Thread::join()
{
#ifdef WIN32
  unsigned long ret_code = 0;
  if ( _id != INVALID_HANDLE_VALUE ) {
    WaitForSingleObject( _id, -1 );
    GetExitCodeThread( _id, &ret_code );
    _id = INVALID_HANDLE_VALUE;
  }
#else // !WIN32
  int ret_code = 0;
  if ( _id != __STATIC_CAST(thread_t,-1) && (_flags & (daemon | detached) ) == 0 ) {
#  ifdef _PTHREADS
    pthread_join( _id, (void **)(&ret_code) );
#  endif
#  ifdef _SOLARIS_THREADS
    thr_join( _id, 0, (void **)(&ret_code) );
#  endif
    _id = __STATIC_CAST(thread_t,-1);
  }
#endif // !WIN32

  return ret_code;
}

__DLLEXPORT
int Thread::suspend()
{
#ifdef WIN32
  if ( _id != INVALID_HANDLE_VALUE ) {
    return SuspendThread( _id );
  }
#else
  if ( _id != __STATIC_CAST(thread_t,-1) ) {
#  ifdef _PTHREADS
    // sorry, POSIX threads don't have suspend/resume calls, so it should
    // be simulated via condwait
    if ( _id != pthread_self() ) {
      throw domain_error( "Thread::suspend() for POSIX threads work only while call from the same thread." );
      // May be signalling pthread_kill( _id, SIG??? ) will be good workaround?
    }
    _suspend.wait();
#  endif
#  ifdef _SOLARIS_THREADS
    return thr_suspend( _id );
#  endif
  }
#endif

  return -1;
}

__DLLEXPORT
int Thread::resume()
{
#ifdef WIN32
  if ( _id != INVALID_HANDLE_VALUE ) {
    return ResumeThread( _id );
  }
#else
  if ( _id != -1 ) {
#  ifdef _PTHREADS
    // sorry, POSIX threads don't have suspend/resume calls, so it should
    // be simulated via condwait
    _suspend.set( true ); // less syscall than _suspend.signal();
#  endif
#  ifdef _SOLARIS_THREADS
    return thr_continue( _id );
#  endif
  }
#endif

  return -1;
}

__DLLEXPORT
int Thread::kill( int sig )
{
#ifdef __unix
  if ( _id != -1 ) {
#ifdef _SOLARIS_THREADS
    return thr_kill( _id, sig );
#endif
#ifdef _PTHREADS
    return pthread_kill( _id, sig );
#endif
  }
#endif
#ifdef WIN32
  // The behavior of TerminateThread significant differ from SOLARIS and POSIX
  // threads, and I don't find analogs to workaround...
  if ( _id != INVALID_HANDLE_VALUE ) {
    return TerminateThread( _id, 0 ) ? 0 : -1;
  }
#endif
  return -1;
}

__DLLEXPORT
void Thread::exit( int code )
{
#ifdef _PTHREADS
  pthread_exit( (void *)code );
#endif
#ifdef _SOLARIS_THREADS
  thr_exit( (void *)code );
#endif
#ifdef WIN32
  ExitThread( code );
#endif
}

__DLLEXPORT
int Thread::join_all()
{
#ifdef __STL_SOLARIS_THREADS
  while ( thr_join( 0, 0, 0 ) == 0 ) ;
#endif

  return 0;
}

__DLLEXPORT
void Thread::block_signal( int sig )
{
#ifdef __unix
  sigset_t sigset;

  sigemptyset( &sigset );
  sigaddset( &sigset, sig );
#  ifdef __STL_SOLARIS_THREADS
  thr_sigsetmask( SIG_BLOCK, &sigset, 0 );
#  endif
#  ifdef _PTHREADS
  pthread_sigsetmask( SIG_BLOCK, &sigset, 0 );
#  endif
#endif // __unix
}

__DLLEXPORT
void Thread::unblock_signal( int sig )
{
#ifdef __unix
  sigset_t sigset;

  sigemptyset( &sigset );
  sigaddset( &sigset, sig );
#  ifdef __STL_SOLARIS_THREADS
  thr_sigsetmask( SIG_UNBLOCK, &sigset, 0 );
#  endif
#  ifdef _PTHREADS
  pthread_sigsetmask( SIG_UNBLOCK, &sigset, 0 );
#  endif
#endif // __unix
}

__DLLEXPORT
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
#ifdef _PTHREADS
  err = pthread_create( &_id, 0, entrance_type_C(_call), this );
#endif
#ifdef _SOLARIS_THREADS
  err = thr_create( 0, 0, entrance_type_C(_call), this, _flags, &_id );
#endif
#ifdef WIN32
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

#ifdef _PTHREADS
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
    // I should be make me->_id = -1; here...
    // Next line is in conflict what I say in this function begin.
    // So don't delete Thread before it termination!
#ifdef WIN32
    me->_id = INVALID_HANDLE_VALUE;
#else
    me->_id = __STATIC_CAST(thread_t,-1);
#endif
    // 
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

__DLLEXPORT
long& Thread::iword( int __idx )
{
  long **user_words;

#ifdef __STL_SOLARIS_THREADS
  thr_getspecific( _mt_key, reinterpret_cast<void **>(&user_words) );
#endif
#ifdef _PTHREADS
  user_words = pthread_getspecific( _mt_key );
#endif
#ifdef WIN32
  user_words = TlsGetValue( _mt_key );
#endif
  if ( user_words == 0 ) {
    uw_alloc_size = sizeof( long ) * (__idx + 1);
#ifdef __STL_USE_STD_ALLOCATORS
#  ifdef _MSC_VER
    user_words = alloc().allocate( uw_alloc_size, (const void *)0 );
#  else
    user_words = alloc().allocate( uw_alloc_size );
#  endif
#else // !__STL_USE_STD_ALLOCATORS && !_MSC_VER
    user_words = alloc::allocate( uw_alloc_size );
#endif // !__STL_USE_STD_ALLOCATORS && !_MSC_VER
    std::fill( *user_words, *user_words + uw_alloc_size, 0 );
#ifdef __STL_SOLARIS_THREADS
    thr_setspecific( _mt_key, user_words );
#endif
#ifdef _PTHREADS
    pthread_setspecific( _mt_key, user_words );
#endif
#ifdef WIN32
    TlsSetValue( _mt_key, user_words );
#endif
  } else if ( (__idx + 1) * sizeof( long ) > uw_alloc_size ) {
    size_t tmp = sizeof( long ) * (__idx + 1);
#ifdef __STL_USE_STD_ALLOCATORS
#ifdef _MSC_VER
    long **_mtmp = alloc().allocate( tmp, (const void *)0 );
#else // __STL_USE_STD_ALLOCATORS
    long **_mtmp = alloc().allocate( tmp );
#endif // __STL_USE_STD_ALLOCATORS
    std::copy( *user_words, *user_words + uw_alloc_size, *_mtmp );
    alloc().deallocate( user_words, uw_alloc_size );
    user_words = _mtmp;
#else // !__STL_USE_STD_ALLOCATORS && !_MSC_VER
    user_words = alloc::reallocate( user_words, uw_alloc_size, tmp );
#endif // !__STL_USE_STD_ALLOCATORS && !_MSC_VER
    std::fill( *user_words + uw_alloc_size, *user_words + tmp, 0 );
    uw_alloc_size = tmp;
#ifdef __STL_SOLARIS_THREADS
    thr_setspecific( _mt_key, user_words );
#endif
#ifdef _PTHREADS
    pthread_setspecific( _mt_key, user_words );
#endif
#ifdef WIN32
    TlsSetValue( _mt_key, user_words );
#endif
  }

  long *_ytmp = (long *)&user_words[__idx];
  return *_ytmp;
}

__DLLEXPORT
void*& Thread::pword( int __idx )
{
  long **user_words;

#ifdef __STL_SOLARIS_THREADS
  thr_getspecific( _mt_key, reinterpret_cast<void **>(&user_words) );
#endif
#ifdef _PTHREADS
  user_words = pthread_getspecific( _mt_key );
#endif
#ifdef WIN32
  user_words = reinterpret_cast<long **>( TlsGetValue( _mt_key ) );
#endif
  if ( user_words == 0 ) {
    uw_alloc_size = sizeof( long ) * (__idx + 1);
// #ifdef _MSC_VER
//    user_words = (long *)alloc().allocate( uw_alloc_size, (const void *)0 );
// #else
    user_words = alloc().allocate( uw_alloc_size );
// #endif
    std::fill( *user_words, *user_words + uw_alloc_size, 0 );
#ifdef __STL_SOLARIS_THREADS
    thr_setspecific( _mt_key, user_words );
#endif
#ifdef _PTHREADS
    pthread_setspecific( _mt_key, user_words );
#endif
#ifdef WIN32
    TlsSetValue( _mt_key, user_words );
#endif
  } else if ( (__idx + 1) * sizeof( long ) > uw_alloc_size ) {
    size_t tmp = sizeof( long ) * (__idx + 1);
#if defined( __STL_USE_STD_ALLOCATORS ) || defined( _MSC_VER )
// #ifdef _MSC_VER
//     long *_mtmp = (long *)alloc().allocate( tmp, (const void *)0 );
// #else
    long **_mtmp = alloc().allocate( tmp );
// #endif
    std::copy( *user_words, *user_words + uw_alloc_size, *_mtmp );
    alloc().deallocate( user_words, uw_alloc_size );
    user_words = _mtmp;
#else
    user_words = alloc::reallocate( user_words, uw_alloc_size, tmp );
#endif
    std::fill( *user_words + uw_alloc_size, *user_words + tmp, 0 );
    uw_alloc_size = tmp;
#ifdef __STL_SOLARIS_THREADS
    thr_setspecific( _mt_key, *user_words );
#endif
#ifdef _PTHREADS
    pthread_setspecific( _mt_key, *user_words );
#endif
#ifdef WIN32
    TlsSetValue( _mt_key, *user_words );
#endif
  }

  // void *_xtmp = *(user_words + __idx);
  // void **_ytmp = (void **)(*user_words + __idx);
  void **_ytmp = (void **)&user_words[__idx];
  return *_ytmp;
}

} // namespace __impl
