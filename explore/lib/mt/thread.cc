// -*- C++ -*- Time-stamp: <10/05/21 15:21:44 ptr>

/*
 * Copyright (c) 1997-1999, 2002-2010
 * Petr Ovtchenkov
 *
 * Portion Copyright (c) 1999-2001
 * Parallel Graphics Ltd.
 *
 * Licensed under the Academic Free License version 3.0
 *
 * Derived from original <mt/xmt.h> of 'complement' project
 * [http://complement.sourceforge.net]
 * to make it close to JTC1/SC22/WG21 C++ 0x working draft
 * [http://www.open-std.org/Jtc1/sc22/wg21/docs/papers/2008/n2521.pdf]
 */

#include <config/feature.h>

#include <sys/types.h>
#ifndef _WIN32
# include <unistd.h>
#endif
#include <fcntl.h>
#include <cstdlib>

#include <mt/mutex>
#include <mt/thread>
#include <mt/callstack.h>

#include <cstring>
#ifndef _WIN32
# include <ostream>
#endif

#include <memory>
#include <functional>
#include <cerrno>
#include <string>
#include <ctime>
#include <list>

#include <stdio.h>
#include <syscall.h>

#ifdef STLPORT
// #  include <unordered_map>
#  include <unordered_set>
// #  include <hash_map>
// #  include <hash_set>
// #  define __USE_STLPORT_HASH
#  define __USE_STLPORT_TR1
#else
#  if defined(__GNUC__) && (__GNUC__ < 4)
// #    include <ext/hash_map>
#    include <ext/hash_set>
#    define __USE_STD_HASH
#  else
// #    include <tr1/unordered_map>
#    include <tr1/unordered_set>
#    define __USE_STD_TR1
#  endif
#endif


#ifdef WIN32
# pragma warning( disable : 4290)
// using namespace std;
#endif

#if defined(__USE_STLPORT_HASH) || defined(__USE_STLPORT_TR1) || defined(__USE_STD_TR1)
#  define __HASH_NAMESPACE std
#endif
#if defined(__USE_STD_HASH)
#  define __HASH_NAMESPACE __gnu_cxx
#endif

namespace __HASH_NAMESPACE {

#ifdef __USE_STD_TR1
namespace tr1 {
#endif

template <>
struct hash<std::tr2::thread_base*>
{
    size_t operator()(const std::tr2::thread_base* __x) const
      { return reinterpret_cast<size_t>(__x); }
};

#ifdef __USE_STD_TR1
}
#endif

} // namespace __HASH_NAMESPACE


namespace std {

namespace tr2 {

namespace detail {

#ifdef __USE_STLPORT_HASH
typedef std::hash_set<thread_base*> thread_pool_t;
#endif
#ifdef __USE_STD_HASH
typedef __gnu_cxx::hash_set<thread_base*> thread_pool_t;
#endif
#if defined(__USE_STLPORT_TR1) || defined(__USE_STD_TR1)
typedef std::tr1::unordered_set<thread_base*> thread_pool_t;
#endif

static mutex thrpool_lock;
static thread_pool_t thread_pool;

int Init_count = 0;

// problem: ::getpid() really return cached value, so pid returned may be
// parent's pid really. I use syscall here and rewrite it during Thread::fork().

static pid_t _pid  = syscall( SYS_getpid );
static pid_t _ppid = syscall( SYS_getppid );

#ifdef __FIT_PSHARED_MUTEX
std::string _notpshared( "Platform not support process shared mutex" );
#endif

#ifdef __FIT_XSI_THR
std::string _notrecursive( "Platform not support recursive mutex" );
#endif

static std::tr2::thread_base::thread_key_type _mt_key = static_cast<std::tr2::thread_base::thread_key_type>(-1);
static std::tr2::mutex _F_lock;

// assume that sizeof( long ) >= sizeof( void * );
// otherwise, #ifdef workaround should be here.
// At present, I don't know such OS.
typedef long _uw_alloc_type;

// typedef std::allocator<_uw_alloc_type> alloc_type;
static int _idx = 0;    // user words index
// static int _self_idx; // user words index, that word point to self
static mutex _idx_lock;
#ifdef __FIT_PTHREADS
void *_uw_save = 0; // place to save user words array during fork
#endif

void _dealloc_uw()
{
#ifdef __FIT_PTHREADS
  _uw_alloc_type *user_words = static_cast<_uw_alloc_type *>(pthread_getspecific( _mt_key ));
#endif
#ifdef __FIT_WIN32THREADS
  _uw_alloc_type *user_words = static_cast<_uw_alloc_type *>(TlsGetValue( _mt_key ));
#endif
  if ( user_words != 0 ) {
    free( user_words );
    user_words = 0;
  }
}

static _uw_alloc_type *_alloc_uw( int __idx )
{
#ifdef __FIT_PTHREADS
  _uw_alloc_type *user_words = static_cast<_uw_alloc_type *>(pthread_getspecific( _mt_key ));
#endif
#ifdef __FIT_WIN32THREADS
  _uw_alloc_type *user_words = static_cast<_uw_alloc_type *>(TlsGetValue( _mt_key ));
#endif

  if ( user_words == 0 ) {  // first time in this thread
    size_t uw_alloc_size = sizeof( _uw_alloc_type ) * (__idx + 2);

    user_words = static_cast<_uw_alloc_type *>( malloc( uw_alloc_size ) );
    std::fill( user_words, user_words + __idx + 2, 0 );
#ifdef __FIT_PTHREADS
    pthread_setspecific( _mt_key, user_words );
#endif
#ifdef __FIT_WIN32THREADS
    TlsSetValue( _mt_key, user_words );
#endif
    user_words[0] = uw_alloc_size;
  } else { // not first time in this thread
    size_t uw_alloc_size = user_words[0];
    if ( (__idx + 2) * sizeof( _uw_alloc_type ) > uw_alloc_size ) { // reallocate
      size_t tmp = sizeof( _uw_alloc_type ) * (__idx + 2);
      _uw_alloc_type *_mtmp = static_cast<_uw_alloc_type *>(malloc( tmp ));
      std::copy( user_words, user_words + uw_alloc_size / sizeof(_uw_alloc_type), _mtmp );
      std::fill( _mtmp + uw_alloc_size / sizeof(_uw_alloc_type), _mtmp + __idx + 2, 0 );
      free( user_words );
      user_words = _mtmp;
      user_words[0] = tmp;
#ifdef __FIT_PTHREADS
      pthread_setspecific( _mt_key, user_words );
#endif
#ifdef __FIT_WIN32THREADS
      TlsSetValue( _mt_key, user_words );
#endif
    }
  }

  return user_words + __idx + 1;
}

} // namespace detail
} // namespace tr2
} // namespace std

namespace std {

namespace tr2 {

using namespace std;

defer_lock_t defer_lock;
try_to_lock_t try_to_lock;
adopt_lock_t adopt_lock;

char *Init_buf[32];
int& thread_base::Init::_count( detail::Init_count ); // trick to avoid friend declarations
bool _at_fork_set = false;

const std::string msg1( "Can't create thread" );
const std::string msg2( "Can't fork" );

// __FIT_DECLSPEC
// void signal_throw( int sig ) throw( int )
// {
//   throw sig;
// }


thread_base::Init::Init()
{
  lock_guard<mutex> lk( detail::_F_lock );
  if ( _count++ == 0 ) {
#ifdef __FIT_PTHREADS
# if !(defined(__FreeBSD__) || defined(__OpenBSD__))
    if ( !_at_fork_set ) { // call only once
      if ( pthread_atfork( __at_fork_prepare, __at_fork_parent, __at_fork_child ) ) {
        throw std::runtime_error( "Problems with pthread_atfork" );
      }
      _at_fork_set = true;
    }
# endif // !(__FreeBSD__ || __OpenBSD__)
    pthread_key_create( &detail::_mt_key, 0 );
#endif
#ifdef __FIT_WIN32THREADS
    detail::_mt_key = TlsAlloc();
#endif
    // Thread::_self_idx = Thread::xalloc();
  }
}

thread_base::Init::~Init()
{
  lock_guard<mutex> lk( detail::_F_lock );

  if ( --_count == 0 ) {
#ifdef __FIT_WIN32THREADS
    TlsFree( detail::_mt_key );
#endif
#ifdef __FIT_PTHREADS
    pthread_key_delete( detail::_mt_key );
#endif
  }
}

#ifdef __FIT_WIN32THREADS
static const thread_base::native_handle_type _bad_thread_id = INVALID_HANDLE_VALUE;
#endif // __FIT_WIN32THREADS

#if defined(__FIT_PTHREADS)
# if !(defined(__FreeBSD__) || defined(__OpenBSD__))
static const thread_base::native_handle_type _bad_thread_id = static_cast<thread_base::native_handle_type>(-1);
# else // __FreeBSD__ || __OpenBSD__
// pthread_t is defined as 'typedef struct pthread *pthread_t;'
static const thread_base::native_handle_type _bad_thread_id = static_cast<thread_base::native_handle_type>(0);
# endif // !(__FreeBSD__ || __OpenBSD__)
#endif // __FIT_UITHREADS || _PTHREADS

void thread_base::Init::__at_fork_prepare()
{
#ifdef __FIT_PTHREADS
  detail::_F_lock.lock();
  detail::thrpool_lock.lock();

  if ( detail::Init_count > 0 ) {
    detail::_uw_save = pthread_getspecific( detail::_mt_key );
  }

  for ( detail::thread_pool_t::const_iterator i = detail::thread_pool.begin(); i != detail::thread_pool.end(); ++i ) {
    if ( (*i)->_id != _bad_thread_id ) {
      const_cast<thread_base*>(*i)->_id_lock.lock();
    }
  }

#endif
}

void thread_base::Init::__at_fork_parent()
{
#ifdef __FIT_PTHREADS
  for ( detail::thread_pool_t::const_iterator i = detail::thread_pool.begin(); i != detail::thread_pool.end(); ++i ) {
    if ( (*i)->_id != _bad_thread_id ) {
      const_cast<thread_base*>(*i)->_id_lock.unlock();
    }
  }

  detail::thrpool_lock.unlock();
  detail::_F_lock.unlock();
#endif
}

void thread_base::Init::__at_fork_child()
{
#ifdef __FIT_PTHREADS
  for ( detail::thread_pool_t::const_iterator i = detail::thread_pool.begin(); i != detail::thread_pool.end(); ++i ) {
    if ( (*i)->_id != _bad_thread_id ) {
      const_cast<thread_base*>(*i)->_id_lock.unlock();
    }
  }

  detail::thrpool_lock.unlock();

  if ( detail::Init_count > 0 ) {
     // otherwise we do it in Thread::Init::Init() below
# if !(defined(__FreeBSD__) || defined(__OpenBSD__))
    // I am misunderstand this point, Solaris 7 require this (to be restored)

    // pthread_atfork( __at_fork_prepare, __at_fork_parent, __at_fork_child );

    // while Linux (and other) inherit this setting from parent process?
    // At least Linux glibc 2.2.5 try to made lock in recursive
    // call of pthread_atfork
# else
// should be fixed...
# endif // !(__FreeBSD__ || __OpenBSD__)
    pthread_key_create( &detail::_mt_key, 0 ); // take new key
    pthread_setspecific( detail::_mt_key, detail::_uw_save ); // store preserved user words array
    detail::_uw_save = 0;
    // Note, that only calling thread inherited when we use POSIX:
    detail::Init_count = 1; // i.e. only ONE (calling) thread...
  }
  detail::_F_lock.unlock();
#endif
}

thread_base::id::id() :
    _id( _bad_thread_id )
{ }

__FIT_DECLSPEC
thread_base::thread_base() :
    _id( _bad_thread_id )
{
  new( Init_buf ) Init();

  lock_guard<mutex> lk( detail::thrpool_lock );
  detail::thread_pool.insert( this );
}

__FIT_DECLSPEC
thread_base::~thread_base()
{
  if ( joinable() ) {
    thread_base::join();
  } else {
    lock_guard<mutex> lk( detail::thrpool_lock );
    detail::thread_pool.erase( this );
  }

  ((Init *)Init_buf)->~Init();
}

__FIT_DECLSPEC
bool thread_base::joinable() const // if true, you can (and should) use join()
{
  lock_guard<mutex> lk( _id_lock );
  return (_id != _bad_thread_id);
}

__FIT_DECLSPEC
void thread_base::join()
{
#ifdef __FIT_WIN32THREADS
  ret_t rt = 0;

  WaitForSingleObject( _id, -1 );
  GetExitCodeThread( _id, &rt );
  CloseHandle( _id );
  _id = _bad_thread_id;
#endif // __FIT_WIN32THREADS
#ifdef __FIT_PTHREADS
  pthread_join( _id, 0 );

  {
    lock_guard<mutex> lk(detail::thrpool_lock);
    detail::thread_pool.erase( this );
  }

  _id = _bad_thread_id; // lock not required here, only one thread
#endif // PTHREADS
}

__FIT_DECLSPEC
void thread_base::detach()
{
#ifdef __FIT_PTHREADS
  lock_guard<mutex> lk( _id_lock );
  if ( pthread_detach( _id ) ) {
    // throw system_error;
  }
  {
    lock_guard<mutex> lk(detail::thrpool_lock);
    for ( detail::thread_pool_t::const_iterator i = detail::thread_pool.begin(); i != detail::thread_pool.end(); ++i ) {
      if ( (*i)->_id == _id ) {
        detail::thread_pool.erase( i );
        break;
      }
    }
  }
  _id = _bad_thread_id;
#endif
}

pid_t getpid()
{
  return detail::_pid;
}

pid_t getppid()
{
  return detail::_ppid;
}

thread_base::id get_id()
{
#ifdef __FIT_PTHREADS
  return thread_base::id( pthread_self() );
#endif
#ifdef __FIT_WIN32THREADS
  return thread_base::id( GetCurrentThread() );
#endif
}

__FIT_DECLSPEC
void fork() throw( fork_in_parent, std::runtime_error )
{
#ifdef __unix
  thread_base::id fthr = this_thread::get_id();
  fork_in_parent f( ::fork() );
  if ( f.pid() > 0 ) {
    throw f;
  }
  if ( f.pid() == -1 ) {
    throw std::runtime_error( msg2 );
  }
  detail::_ppid = detail::_pid;
  detail::_pid = syscall( SYS_getpid );

  // lock not required: it in child and only one thread yet
  list<detail::thread_pool_t::key_type> trash;
  for ( detail::thread_pool_t::const_iterator i = detail::thread_pool.begin(); i != detail::thread_pool.end(); ++i ) {
    if ( (*i)->get_id() != fthr ) {
      const_cast<thread_base*>(*i)->_id = _bad_thread_id;
      trash.push_back( *i );
    }
  }
  for ( list<detail::thread_pool_t::key_type>::const_iterator i = trash.begin(); i != trash.end(); ++i ) {
    detail::thread_pool.erase( *i );
  }
#endif
}

namespace this_thread
{

__FIT_DECLSPEC
void become_daemon() throw( fork_in_parent, std::runtime_error )
{
#ifdef __unix
  try {
    std::tr2::this_thread::fork();

    ::chdir( "/var/tmp" ); // for CWD: if not done, process remain with same WD
                         // and don't allow unmount volume, for example
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
#endif
}

#if 0
std::thread_base::id get_id()
{
#ifdef __FIT_PTHREADS
  return thread_base::id( pthread_self() );
#endif
#ifdef __FIT_WIN32THREADS
  return thread_base::id( GetCurrentThread() );
#endif
}
#endif // 0

__FIT_DECLSPEC
void sleep( const std::tr2::system_time& abstime )
{
  std::tr2::system_time ct = std::tr2::get_system_time();

  if ( abstime > ct ) {
    std::tr2::nanoseconds delta = abstime - ct;

#ifdef __unix
    ::timespec t;
    t.tv_sec = delta.count() / std::tr2::nanoseconds::ticks_per_second;
    t.tv_nsec = delta.count() % std::tr2::nanoseconds::ticks_per_second;
    nanosleep( const_cast<const ::timespec *>(&t), 0 );
#endif
  }
#ifdef WIN32
  time_t ct = time( 0 );
  time_t _conv = abstime.tv_sec * 1000 + abstime.tv_nsec / 1000000;

  Sleep( _conv >= ct ? _conv - ct : 1 );
#endif
}

__FIT_DECLSPEC
void sleep( const std::tr2::nanoseconds& rel_t )
{
  ::timespec t;
  t.tv_sec = rel_t.count() / std::tr2::nanoseconds::ticks_per_second;
  t.tv_nsec = rel_t.count() % std::tr2::nanoseconds::ticks_per_second;
  ::nanosleep( const_cast<const ::timespec *>(&t), 0 );
}

__FIT_DECLSPEC int xalloc()
{
  std::tr2::lock_guard<std::tr2::mutex> _l( std::tr2::detail::_idx_lock );
  return detail::_idx++;
}

__FIT_DECLSPEC long& iword( int __idx )
{
  return *static_cast<long *>( std::tr2::detail::_alloc_uw( __idx ) );
}

__FIT_DECLSPEC void*& pword( int __idx )
{
  return *reinterpret_cast<void **>( std::tr2::detail::_alloc_uw( __idx ));
}

__FIT_DECLSPEC void block_signal( int sig )
{
#ifdef __unix
  sigset_t sigset;

  sigemptyset( &sigset );
  sigaddset( &sigset, sig );
#  ifdef __FIT_PTHREADS
  pthread_sigmask( SIG_BLOCK, &sigset, 0 );
#  endif
#endif // __unix
}

__FIT_DECLSPEC void unblock_signal( int sig )
{
#ifdef __unix
  sigset_t sigset;

  sigemptyset( &sigset );
  sigaddset( &sigset, sig );
#  ifdef __FIT_PTHREADS
  pthread_sigmask( SIG_UNBLOCK, &sigset, 0 );
#  endif
#endif // __unix
}

__FIT_DECLSPEC int signal_handler( int sig, void (*handler)(int) )
{
#ifdef __unix
  struct sigaction act;

  sigemptyset( &act.sa_mask );
  sigaddset( &act.sa_mask, sig );

  act.sa_flags = 0; // SA_RESTART;
  act.sa_handler = handler;
  return sigaction( sig, &act, 0 );
#else
  return -1;
#endif // __unix
}

__FIT_DECLSPEC int signal_handler( int sig, void (*handler)(int, siginfo_t*, void*) )
{
#ifdef __unix
  struct sigaction act;

  sigemptyset( &act.sa_mask );
  sigaddset( &act.sa_mask, sig );

  act.sa_flags = SA_SIGINFO; // SA_RESTART;
  act.sa_sigaction = handler;
  return sigaction( sig, &act, 0 );
#else
  return -1;
#endif // __unix
}

} // namespace this_thread

} // namespace tr2

} // namespace std
