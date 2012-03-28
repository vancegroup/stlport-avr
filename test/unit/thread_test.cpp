// -*- C++ -*- Time-stamp: <2012-02-28 11:34:07 ptr>

/*
 * Copyright (c) 2006-2012
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

#include "cppunit/cppunit_proxy.h"

class ThreadTest :
    public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(ThreadTest);
  CPPUNIT_TEST(thread_call);
  CPPUNIT_TEST(mutex_test);
  CPPUNIT_TEST(mutex_rw_test);
  CPPUNIT_TEST(barrier);
  CPPUNIT_TEST(semaphore);
  CPPUNIT_TEST(condition_var);
  CPPUNIT_TEST_SUITE_END();

  protected:
    void thread_call();
    void mutex_test();
    void mutex_rw_test();
    void barrier();
    void semaphore();
    void condition_var();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ThreadTest);

// #include <mt/date_time>
#include <thread>

#include <mutex>
#include <condition_variable>
// #include <misc/type_traits.h>
// #include <typeinfo>

#include <iostream>
#include <iomanip>
#include <sstream>

#if defined(_STLP_UNIX) || defined(__unix)
#  include <sys/wait.h>
#  include <sys/ipc.h>
#  include <sys/shm.h>
#endif

#include <string>
#include <set>
#include <vector>

static int val = 0;

void thread_func()
{
  val = 1;
}

void thread_func_int( int v )
{
  val = v;
}

void ThreadTest::thread_call()
{
  val = -1;
 
  std::basic_thread<0,0> t( thread_func );

  t.join();

  CPPUNIT_ASSERT( val == 1 );

  std::basic_thread<0,0> t2( thread_func_int, 2 );

  t2.join();

  CPPUNIT_ASSERT( val == 2 );

  val = 0;
}

static std::mutex lk;

void thread_func2()
{
  std::lock_guard<std::mutex> lock( lk );

  ++val;
}

void ThreadTest::mutex_test()
{
  val = 0;

  std::basic_thread<0,0> t( thread_func2 );

  lk.lock();
  --val;
  lk.unlock();

  t.join();

  CPPUNIT_ASSERT( val == 0 );

  std::recursive_mutex rlk;

  rlk.lock();
  rlk.lock(); // shouldn't block here
  rlk.unlock();
  rlk.unlock();
}

#ifdef _STLP_RWLOCK

namespace rw_mutex_ns {

int n_threads = 3; 
int n_times = 10000;
int shared_res;
std::rw_mutex _lock_heap;

void run()
{
  for ( int i = 0; i < n_times; ++i ) {
    if ( rand() % 2 ) {
      std::lock_guard<std::rw_mutex> lk( _lock_heap );
      ++shared_res;
    } else {
      std::basic_read_lock<std::rw_mutex> lk(_lock_heap);
      int tmp = shared_res;
      ++tmp;
    }
  }
}

}

#endif // _STLP_RWLOCK

void ThreadTest::mutex_rw_test()
{
#ifdef _STLP_RWLOCK
  std::vector<std::thread*> thr(rw_mutex_ns::n_threads);

  for ( int i = 0;i < rw_mutex_ns::n_threads; ++i ) {
    thr[i] = new std::thread( rw_mutex_ns::run );
  }

  for ( int i = 0; i < rw_mutex_ns::n_threads; ++i ) {
    thr[i]->join();
    delete thr[i];
  }
#endif // _STLP_RWLOCK
}

static std::barrier bar;

void thread_func3()
{
  try {
    // CPPUNIT_ASSERT( val == 0 );

    bar.wait();

    std::lock_guard<std::mutex> lock( lk );

    ++val;
  }
  catch ( std::runtime_error& err ) {
    // CPPUNIT_ASSERT( err.what() );
  }
}

void ThreadTest::barrier()
{
  val = 0;

  std::basic_thread<0,0> t( thread_func3 );

  CPPUNIT_ASSERT( val == 0 );

  bar.wait();

  lk.lock();
  --val;
  lk.unlock();

  t.join();

  CPPUNIT_ASSERT( val == 0 );
}

void thread_func4( std::semaphore* s )
{
  // CPPUNIT_ASSERT( val == 1 );

  val = 0;

  s->notify_one();
}

void ThreadTest::semaphore()
{
  std::semaphore s;

  val = 1;

  s.wait();

  std::basic_thread<0,0> t( thread_func4, &s );

  s.wait();

  CPPUNIT_ASSERT( val == 0 );

  t.join();

  val = 1;

  std::semaphore s1(0);

  std::basic_thread<0,0> t1( thread_func4, &s1 );

  s1.wait();

  CPPUNIT_ASSERT( val == 0 );

  t1.join();

  // notify _before_ wait acceptable:

  s1.notify_one();
  s1.wait();
}

static std::mutex cond_mtx;
static std::condition_variable cnd;

struct true_val
{
  bool operator()() const
    { return (val == 1); }
};

void thread_func5()
{
  std::unique_lock<std::mutex> lk( cond_mtx );
  
  val = 1;
  cnd.notify_one();
}

void ThreadTest::condition_var()
{
#if 0
  val = 0;
  
  std::thread t( thread_func5 );
  
  std::unique_lock<std::mutex> lk( cond_mtx );
  
  CPPUNIT_ASSERT( cnd.timed_wait( lk, std::milliseconds(500), true_val() ) );
  
  EXAM_CHECK( val == 1 );
  
  t.join();
  
  val = 0;
#endif // 0
}

