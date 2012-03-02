// -*- C++ -*- Time-stamp: <2012-03-02 01:24:45 ptr>

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

#include "thread_test.h"

// #include <mt/date_time>
#include <thread>
#include <mutex>
#include <condition_variable>
// #include <misc/type_traits.h>
#include <typeinfo>

//#include <iostream>
//#include <iomanip>
//#include <sstream>

//#include <sys/wait.h>
//#include <sys/ipc.h>
//#include <sys/shm.h>

//#include <string>
//#include <set>

static int val = 0;

void thread_func()
{
  val = 1;
}

void thread_func_int( int v )
{
  val = v;
}

int EXAM_IMPL(thread_test::thread_call)
{
  val = -1;
 
  typename std::basic_thread<0,0> t( thread_func );

  t.join();

  EXAM_CHECK( val == 1 );

  std::basic_thread<0,0> t2( thread_func_int, 2 );

  t2.join();

  EXAM_CHECK( val == 2 );

  val = 0;

  return EXAM_RESULT;
}

static std::mutex lk;

void thread_func2()
{
  std::lock_guard<std::mutex> lock( lk );

  ++val;
}

int EXAM_IMPL(thread_test::mutex_test)
{
  val = 0;

  std::basic_thread<0,0> t( thread_func2 );

  lk.lock();
  --val;
  lk.unlock();

  t.join();

  EXAM_CHECK( val == 0 );

  std::recursive_mutex rlk;

  rlk.lock();
  rlk.lock(); // shouldn't block here
  rlk.unlock();
  rlk.unlock();

  return EXAM_RESULT;
}

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

int EXAM_IMPL(thread_test::mutex_rw_test)
{
  std::vector<std::thread*> thr(rw_mutex_ns::n_threads);

  for ( int i = 0;i < rw_mutex_ns::n_threads; ++i ) {
    thr[i] = new std::thread( rw_mutex_ns::run );
  }

  for ( int i = 0; i < rw_mutex_ns::n_threads; ++i ) {
    thr[i]->join();
    delete thr[i];
  }

  return EXAM_RESULT;
}

static std::barrier bar;

void thread_func3()
{
  try {
    EXAM_CHECK_ASYNC( val == 0 );

    bar.wait();

    std::lock_guard<std::mutex> lock( lk );

    ++val;
  }
  catch ( std::runtime_error& err ) {
    EXAM_ERROR_ASYNC( err.what() );
  }
}

int EXAM_IMPL(thread_test::barrier)
{
  val = 0;

  std::basic_thread<0,0> t( thread_func3 );

  EXAM_CHECK( val == 0 );

  bar.wait();

  lk.lock();
  --val;
  lk.unlock();

  t.join();

  EXAM_CHECK( val == 0 );

  return EXAM_RESULT;
}

void thread_func4( std::semaphore* s )
{
  EXAM_CHECK_ASYNC( val == 1 );

  val = 0;

  s->notify_one();
}

int EXAM_IMPL(thread_test::semaphore)
{
  std::semaphore s;

  val = 1;

  s.wait();

  std::basic_thread<0,0> t( thread_func4, &s );

  s.wait();

  EXAM_CHECK( val == 0 );

  t.join();

  val = 1;

  std::semaphore s1(0);

  std::basic_thread<0,0> t1( thread_func4, &s1 );

  s1.wait();

  EXAM_CHECK( val == 0 );

  t1.join();

  // notify _before_ wait acceptable:

  s1.notify_one();
  s1.wait();

  return EXAM_RESULT;
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

int EXAM_IMPL(thread_test::condition_var)
{
#if 0
  val = 0;
  
  std::thread t( thread_func5 );
  
  std::unique_lock<std::mutex> lk( cond_mtx );
  
  EXAM_CHECK( cnd.timed_wait( lk, std::tr2::milliseconds(500), true_val() ) );
  
  EXAM_CHECK( val == 1 );
  
  t.join();
  
  val = 0;
#endif
  
  return EXAM_RESULT;
}

static std::timed_mutex tm;
static const std::chrono::milliseconds time_mark(500);

void func_a()
{
  try {
    std::unique_lock<std::timed_mutex> lock( tm, std::defer_lock );

    /*
      I'm hope that 0.5 sec is enough to start another thread;
      if not, test will pass, but really test nothing.
    */

    lock.try_lock_for( time_mark );

    bar.wait();
  }
  catch ( std::runtime_error& err ) {
    EXAM_ERROR_ASYNC( err.what() );
  }
}

int EXAM_IMPL(thread_test::timed_mutex)
{
  std::chrono::system_clock::time_point t0( std::chrono::system_clock::now() );

  std::thread t1( func_a );
  std::thread t2( func_a );

  t2.join();
  t1.join();

  EXAM_CHECK( (std::chrono::system_clock::now() - t0) > time_mark );

  std::unique_lock<std::timed_mutex> lock( tm, std::defer_lock );
  EXAM_CHECK( lock.try_lock() );

  return EXAM_RESULT;
}

static std::mutex lk2;

int res[2];

void func_b()
{
  try {
    std::unique_lock<std::mutex> lock( lk, std::defer_lock );
    std::unique_lock<std::mutex> lock2( lk2, std::defer_lock );

    res[0] = std::try_lock( lock, lock2 );

    bar.wait();
  }
  catch ( std::runtime_error& err ) {
    EXAM_ERROR_ASYNC( err.what() );
  }
}

void func_c()
{
  try {
    std::unique_lock<std::mutex> lock( lk, std::defer_lock );
    std::unique_lock<std::mutex> lock2( lk2, std::defer_lock );

    res[1] = std::try_lock( lock2, lock );

    bar.wait();
  }
  catch ( std::runtime_error& err ) {
    EXAM_ERROR_ASYNC( err.what() );
  }
}

int EXAM_IMPL(thread_test::try_lock)
{
  res[0] = 10;
  res[1] = 10;

  std::thread t1( func_b );
  std::thread t2( func_c );

  t2.join();
  t1.join();

  EXAM_CHECK( ((res[0] == -1 && res[1] >= 0 && res[1] < 2) || (res[1] == -1 && res[0] >= 0 && res[0] < 2)  || (res[0] >= 0 && res[0] < 2 && res[1] >= 0 && res[1] < 2)) );

  return EXAM_RESULT;
}
