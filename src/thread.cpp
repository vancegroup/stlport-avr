// -*- C++ -*- Time-stamp: <2012-02-27 21:27:51 ptr>

/*
 * Copyright (c) 1997-1999, 2002-2012
 * Petr Ovtchenkov
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

#include "stlport_prefix.h"

#include <sys/types.h>
#ifndef _WIN32
# include <unistd.h>
#endif
#include <fcntl.h>
#include <cstdlib>

#include <string>
#include <mutex>
#include <thread>
#include <callstack.h>

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
#ifdef __FIT_SYSCALL
#  include <syscall.h>
#endif

#ifdef WIN32
# pragma warning( disable : 4290)
// using namespace std;
#endif

_STLP_BEGIN_NAMESPACE

namespace detail {

#ifdef __FIT_SYSCALL

/*
  Problem: ::getpid() really return cached value, so pid returned may be
  parent's pid really. I use syscall here and rewrite it during std::tr2::fork().
  This workaround really not correct: looks that glibc's getpid() problem
  was inspired by call from signal handler while the thread executes fork;
  i) syscall is a bad way in this case too; ii) looks, this problem is fixed.

  See also glibc's ./nptl/sysdeps/unix/sysv/linux/getpid.c and
  ./nptl/sysdeps/unix/sysv/linux/fork.c.

  BTW, syscall is treated as deprecated.
*/

static pid_t _pid  = syscall( SYS_getpid );
static pid_t _ppid = syscall( SYS_getppid );
#endif // __FIT_SYSCALL

#ifdef _STLP_PSHARED_MUTEX
_STLP_DECLSPEC _STLP_STD::string _notpshared( "Platform not support process shared mutex" );
#endif

#ifdef _STLP_XSI_THR
_STLP_DECLSPEC _STLP_STD::string _notrecursive( "Platform not support recursive mutex" );
#endif

} // namespace detail

_STLP_END_NAMESPACE

_STLP_BEGIN_NAMESPACE

defer_lock_t defer_lock;
try_to_lock_t try_to_lock;
adopt_lock_t adopt_lock;

const _STLP_STD::string msg1( "Can't create thread" );
const _STLP_STD::string msg2( "Can't fork" );

// _STLP_DECLSPEC
// void signal_throw( int sig ) throw( int )
// {
//   throw sig;
// }


#ifdef _STLP_WIN32THREADS
static const thread_base::native_handle_type _bad_thread_id = INVALID_HANDLE_VALUE;
#endif // _STLP_WIN32THREADS

#if defined(_STLP_PTHREADS)
# if !(defined(__FreeBSD__) || defined(__OpenBSD__))
static const thread_base::native_handle_type _bad_thread_id = static_cast<thread_base::native_handle_type>(-1);
# else // __FreeBSD__ || __OpenBSD__
// pthread_t is defined as 'typedef struct pthread *pthread_t;'
static const thread_base::native_handle_type _bad_thread_id = static_cast<thread_base::native_handle_type>(0);
# endif // !(__FreeBSD__ || __OpenBSD__)
#endif // __FIT_UITHREADS || _PTHREADS

_STLP_DECLSPEC thread_base::id::id() :
    _id( _bad_thread_id )
{ }

_STLP_DECLSPEC thread_base::thread_base() :
    _id( _bad_thread_id )
{
}

_STLP_DECLSPEC thread_base::~thread_base()
{
  if ( joinable() ) {
    thread_base::join();
  }
}

_STLP_DECLSPEC bool thread_base::joinable() const // if true, you can (and should) use join()
{
  lock_guard<mutex> lk( _id_lock );
  return (_id != _bad_thread_id);
}

_STLP_DECLSPEC void thread_base::join()
{
#ifdef _STLP_WIN32THREADS
  ret_t rt = 0;

  WaitForSingleObject( _id, -1 );
  GetExitCodeThread( _id, &rt );
  CloseHandle( _id );
  _id = _bad_thread_id;
#endif // _STLP_WIN32THREADS
#ifdef _STLP_PTHREADS
  pthread_join( _id, 0 );

  _id = _bad_thread_id; // lock not required here, only one thread
#endif // PTHREADS
}

_STLP_DECLSPEC void thread_base::detach()
{
#ifdef _STLP_PTHREADS
  lock_guard<mutex> lk( _id_lock );
  if ( pthread_detach( _id ) ) {
    // throw system_error;
  }
  _id = _bad_thread_id;
#endif
}

_STLP_DECLSPEC thread_base::id get_id()
{
#ifdef _STLP_PTHREADS
  return thread_base::id( pthread_self() );
#endif
#ifdef _STLP_WIN32THREADS
  return thread_base::id( GetCurrentThread() );
#endif
}

namespace this_thread
{

#if 0
std::thread_base::id get_id()
{
#ifdef _STLP_PTHREADS
  return thread_base::id( pthread_self() );
#endif
#ifdef _STLP_WIN32THREADS
  return thread_base::id( GetCurrentThread() );
#endif
}
#endif // 0

#if 0
_STLP_DECLSPEC
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

_STLP_DECLSPEC
void sleep( const std::tr2::nanoseconds& rel_t )
{
  ::timespec t;
  t.tv_sec = rel_t.count() / std::tr2::nanoseconds::ticks_per_second;
  t.tv_nsec = rel_t.count() % std::tr2::nanoseconds::ticks_per_second;
  ::nanosleep( const_cast<const ::timespec *>(&t), 0 );
}
#endif // 0

} // namespace this_thread

_STLP_END_NAMESPACE
