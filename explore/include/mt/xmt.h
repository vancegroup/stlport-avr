// -*- C++ -*- Time-stamp: <99/02/09 16:23:20 ptr>
#ifndef __XMT_H
#define __XMT_H

#ident "%Z% $Date$ $Revision$ $RCSfile$ %Q%"

#include <cstddef>
#include <stdexcept>

#ifdef WIN32
#  include <windows.h>
// #define pthread_mutex_t            CRITICAL_SECTION
// #define pthread_mutex_init( a, b ) InitializeCriticalSection( a )
// #define pthread_mutex_destroy( a ) DeleteCriticalSection( a )
// #define pthread_mutex_lock( a )    EnterCriticalSection( a )
// #define pthread_mutex_unlock( a )  LeaveCriticalSection( a )
#  include <memory>
#  define _REENTRANT
#  define __DLLEXPORT __declspec( dllexport )
#else
#  if defined( __STL_USE_NEW_STYLE_HEADERS ) && defined( __SUNPRO_CC )
#    include <ctime>
#  endif
#  ifdef _PTHREADS
#    include <pthread.h>
#  endif
#  ifdef _SOLARIS_THREADS
#    include <thread.h>
#  endif
#  define __DLLEXPORT
#endif

namespace __impl {

#ifndef WIN32
using std::size_t;
#endif
using std::runtime_error;

class Mutex
{
  public:
    Mutex()// :
//	count( 0 )
      {
#ifdef _PTHREADS
	pthread_mutex_init( &mutex, 0 );
#endif
#ifdef _SOLARIS_THREADS
	mutex_init( &mutex, 0, 0 );
#endif
#ifdef WIN32
	InitializeCriticalSection( &mutex );
#endif
      }

    ~Mutex()
      {
#ifdef _PTHREADS
	pthread_mutex_destroy( &mutex );
#endif
#ifdef _SOLARIS_THREADS
	mutex_destroy( &mutex );
#endif
#ifdef WIN32
	DeleteCriticalSection( &mutex );
#endif
      }

    void lock()
      {
//	++count;
#ifdef _PTHREADS
	pthread_mutex_lock( &mutex );
#endif
#ifdef _SOLARIS_THREADS
	mutex_lock( &mutex );
#endif
#ifdef WIN32
	EnterCriticalSection( &mutex );
#endif
//	own = pthread_self();
      }

    void unlock()
      {
#ifdef _PTHREADS
	pthread_mutex_unlock( &mutex );
#endif
#ifdef _SOLARIS_THREADS
	mutex_unlock( &mutex );
#endif
#ifdef WIN32
	LeaveCriticalSection( &mutex );
#endif
//	--count;
      }

  protected:
//    void __lock()
//      {	++count; }
//    void __unlock()
//      { --count; }
#ifdef _PTHREADS
    pthread_mutex_t mutex;
#endif
#ifdef _SOLARIS_THREADS
    mutex_t mutex;
#endif
#ifdef WIN32
    CRITICAL_SECTION mutex;
#endif

  private:
//    pthread_t own;
//    int count;
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

class Thread
{
  public:
    typedef int (*entrance_type)( void * );

    __DLLEXPORT
    Thread();

    explicit __DLLEXPORT Thread( entrance_type entrance, const void *p = 0, size_t psz = 0 );

    __DLLEXPORT
    void launch( entrance_type entrance, const void *p = 0, size_t psz = 0 );
    __DLLEXPORT
    int join();
    static __DLLEXPORT void exit( int code = 0 );

  private:
    Thread( const Thread& )
      { }

    void _create( const void *p, size_t psz ) throw(runtime_error);
    static void *_call( void *p );

    static void unexpected();
    static void terminate();


#ifdef _PTHREADS
    pthread_t _id;
#endif
#ifdef _SOLARIS_THREADS
    thread_t  _id;
#endif
#ifdef WIN32
    HANDLE    _id;
    unsigned long _thr_id;
#endif
    entrance_type _entrance;
    void *_param;
    size_t _param_sz;
    //  Mutex _params_lock; --- no needs
};

} // namespace __impl

#ifdef _REENTRANT

#  define MT_REENTRANT(point,nm) __impl::Locker nm(point)
#  define MT_LOCK(point)         point.lock()
#  define MT_UNLOCK(point)       point.unlock()

#  define MT_MUTEX_LOCK(l)     mutex_lock(l)
#  define MT_MUTEX_UNLOCK(l)   mutex_unlock(l)
#  define MT_MUTEX_INIT(l,f)   mutex_init(l,f,0)
#  define MT_MUTEX_DESTROY(l)  mutex_destroy(l)
#  define MT_COND_INIT(c,f)    cond_init(c,f,0)
#  define MT_COND_WAIT(c,mp)   cond_wait(c,mp)
#  define MT_COND_SIGNAL(c)    cond_signal(c)
#  define MT_COND_DESTROY(c)   cond_destroy(c)

#else

#  define MT_REENTRANT(point,nm) ((void)0)
#  define MT_LOCK(point)         ((void)0)
#  define MT_UNLOCK(point)       ((void)0)

#  define MT_MUTEX_LOCK(l)
#  define MT_MUTEX_UNLOCK(l)
#  define MT_MUTEX_INIT(l,f)
#  define MT_MUTEX_DESTROY(l)
#  define MT_COND_INIT(c,f)
#  define MT_COND_WAIT(c,mp)
#  define MT_COND_SIGNAL(c)
#  define MT_COND_DESTROY(c)

#endif

#endif // __XMT_H
