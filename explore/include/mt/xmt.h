// -*- C++ -*- Time-stamp: <99/04/16 17:40:32 ptr>
#ifndef __XMT_H
#define __XMT_H

#ident "%Z% $Date$ $Revision$ $RCSfile$ %Q%"

#include <cstddef>
#include <stdexcept>

#ifdef WIN32
#  include <windows.h>
#  include <memory>
#  define _REENTRANT
#  define __DLLEXPORT __declspec( dllexport )
#else
#  if defined( _REENTRANT ) && !defined(_NOTHREADS)
#    if defined( __STL_USE_NEW_STYLE_HEADERS ) && defined( __SUNPRO_CC )
#      include <ctime>
#    endif
#    if !defined(_PTHREADS) && !defined(_SOLARIS_THREADS)
#      ifdef __STL_THREADS
#        ifdef __STL_SOLARIS_THREADS
#          define _SOLARIS_THREADS
#        elif __STL_PTHREADS
#          define _PTHREADS
#        endif
#      else
#        define _SOLARIS_THREADS // my default choice
#      endif
#    endif
#    ifdef _PTHREADS
#      include <pthread.h>
#    endif
#    ifdef _SOLARIS_THREADS
#      include <thread.h>
#    endif
#  elif !defined(_NOTHREADS) // !_REENTRANT
#    define _NOTHREADS
#  endif
#  define __DLLEXPORT
#endif

#ifdef _REENTRANT

#  define MT_REENTRANT(point,nm) __impl::Locker nm(point)
#  define MT_LOCK(point)         point.lock()
#  define MT_UNLOCK(point)       point.unlock()

#else

#  define MT_REENTRANT(point,nm) ((void)0)
#  define MT_LOCK(point)         ((void)0)
#  define MT_UNLOCK(point)       ((void)0)

#endif

#include <signal.h>

extern "C" {

#ifndef SIG_PF // sys/signal.h

typedef void SIG_FUNC_TYP(int);
typedef SIG_FUNC_TYP *SIG_TYP;
#define SIG_PF SIG_TYP

#define SIG_DFL (SIG_PF)0
#define SIG_ERR (SIG_PF)-1
#define SIG_IGN (SIG_PF)1
#define SIG_HOLD (SIG_PF)2

#endif
}

namespace __impl {

extern __DLLEXPORT void signal_throw( int sig ) throw( int );

#ifndef WIN32
using std::size_t;
#endif
using std::runtime_error;

class Mutex
{
  public:
    Mutex()
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
#ifdef _PTHREADS
	pthread_mutex_lock( &mutex );
#endif
#ifdef _SOLARIS_THREADS
	mutex_lock( &mutex );
#endif
#ifdef WIN32
	EnterCriticalSection( &mutex );
#endif
      }

#if !defined( WIN32 ) || (defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0400)
    int trylock()
      {
#ifdef _PTHREADS
	return pthread_mutex_trylock( &mutex );
#endif
#ifdef _SOLARIS_THREADS
	return mutex_trylock( &mutex );
#endif
#ifdef WIN32
	return TryEnterCriticalSection( &mutex ) != 0 ? 0 : -1;
#endif
#ifdef _NOTHREADS
        return 0;
#endif
      }
#endif // !WIN32 || _WIN32_WINNT >= 0x0400

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
      }

  protected:
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
#ifdef _SOLARIS_THREADS
    friend class Condition;
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
#ifdef _SOLARIS_THREADS
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
#ifdef _SOLARIS_THREADS
        cond_destroy( &_cond );
#endif
      }

    bool set( bool __v )
      {
        MT_REENTRANT( _lock, _1 );

        bool tmp = _val;
        _val = __v;
#ifdef WIN32
         if ( __v == true && tmp == false ) {
           SetEvent( _cond );
         } else if ( __v == false && tmp == true ) {
           ResetEvent( _cond );
         }
#endif
#ifdef _SOLARIS_THREADS
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
#ifdef _PTHREADS
          return pthread_cond_wait( &_cond );
#endif
#ifdef _SOLARIS_THREADS
          MT_REENTRANT( _cond_lock, _1 );
          int ret;
          while ( !_val ) {
            ret = cond_wait( &_cond, &_lock.mutex );
          }

          return ret;
#endif
        }

        return 0;
      }

    int wait()
      {
        set( false );
#ifdef WIN32
        if ( WaitForSingleObject( _cond, -1 ) == WAIT_FAILED ) {
          return -1;
        }
        return 0;
#endif
#ifdef _PTHREADS
          return pthread_cond_wait( &_cond );
#endif
#ifdef _SOLARIS_THREADS
        MT_REENTRANT( _cond_lock, _1 );
        int ret;
        while ( !_val ) {
          ret = cond_wait( &_cond, &_lock.mutex );
        }

        return ret;
#endif
#ifdef _NOTHREADS
        return 0;
#endif
      }

    int signal()
      {
        MT_REENTRANT( _lock, _1 );

        _val = true;
#ifdef WIN32
        return SetEvent( _cond ) == FALSE ? -1 : 0;
#endif
#ifdef _PTHREADS
        return pthread_cond_signal( &_cond );
#endif
#ifdef _SOLARIS_THREADS
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
#ifdef _SOLARIS_THREADS
    cond_t _cond;
    Mutex _cond_lock;
#endif
    Mutex _lock;
    bool _val;
};

class Thread
{
  public:
    typedef int (*entrance_type)( void * );
#ifdef WIN32
    typedef int thread_key_type;
#endif
#ifdef _PTHREADS
    typedef pthread_key_t thread_key_type;
#endif
#ifdef __STL_SOLARIS_THREADS
    typedef thread_key_t thread_key_type;
#endif

#ifdef _MSC_VER
    typedef std::allocator<void *> alloc;
#else
#  ifdef __STL_USE_STD_ALLOCATORS
    typedef std::allocator<void *> alloc;
#  else 
    typedef __STD::alloc alloc;
#  endif
#endif

    enum {
#ifdef __STL_SOLARIS_THREADS
      bound     = THR_BOUND,
      detached  = THR_DETACHED,
      new_lwp   = THR_NEW_LWP,
      suspended = THR_SUSPENDED,
      daemon    = THR_DAEMON
#endif
#ifdef WIN32
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

    __DLLEXPORT Thread( unsigned flags = 0 );

    explicit __DLLEXPORT Thread( entrance_type entrance, const void *p = 0, size_t psz = 0, unsigned flags = 0 );

    __DLLEXPORT ~Thread();

    __DLLEXPORT
    void launch( entrance_type entrance, const void *p = 0, size_t psz = 0 );
    __DLLEXPORT int join();
    __DLLEXPORT int suspend();
    __DLLEXPORT int resume();
    __DLLEXPORT int kill( int sig );
    static __DLLEXPORT void exit( int code = 0 );
    static __DLLEXPORT int join_all();
    static __DLLEXPORT void block_signal( int sig );
    static __DLLEXPORT void unblock_signal( int sig );
    static __DLLEXPORT void signal_handler( int sig, SIG_PF );

    bool good() const
#ifdef WIN32
      { return _id != INVALID_HANDLE_VALUE; }
#else
      { return _id != -1; }
#endif

    static int xalloc()
      { return _idx++; }
    __DLLEXPORT long&  iword( int __idx );
    __DLLEXPORT void*& pword( int __idx );

    static thread_key_type mtkey()
      { return _mt_key; }

  private:
    Thread( const Thread& )
      { }

    void _create( const void *p, size_t psz ) throw(runtime_error);
    static void *_call( void *p );

    static void unexpected();
    static void terminate();

    static int _idx; // user words index
    static thread_key_type _mt_key;
    size_t uw_alloc_size;

#ifdef _PTHREADS
    pthread_t _id;
    // sorry, POSIX threads don't have suspend/resume calls, so it should
    // be simulated via cond_wait
    Condition _suspend;
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
    unsigned _flags;
    //  Mutex _params_lock; --- no needs
    friend class Init;
};

} // namespace __impl

#endif // __XMT_H
