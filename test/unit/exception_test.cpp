#include "exception_test.h"

#include <exception>
#include <stdexcept>
#include <string>

#if !defined (STLPORT) || !defined (_STLP_NO_UNEXPECTED_EXCEPT_SUPPORT)
bool g_unexpected_called = false;
void unexpected_hdl() {
  g_unexpected_called = true;
  throw std::bad_exception();
}

struct special_except {};
void throw_func() {
  throw special_except();
}

void throw_except_func() throw(std::exception) {
  throw_func();
}
#endif

int EXAM_IMPL(exception_test::what)
{
#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    throw std::runtime_error( std::string( "message" ) );
  }
  catch ( std::runtime_error& err ) {
    EXAM_CHECK( strcmp( err.what(), "message" ) == 0 );
  }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(exception_test::unexpected_except)
{
#if !defined (STLPORT) || !defined (_STLP_NO_UNEXPECTED_EXCEPT_SUPPORT)
  std::unexpected_handler hdl = &unexpected_hdl;
  std::set_unexpected(hdl);

  try {
    throw_except_func();
  }
  catch (std::bad_exception const&) {
    EXAM_CHECK( true );
  }
  catch (special_except) {
    EXAM_CHECK( false );
  }
  EXAM_CHECK( g_unexpected_called );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

#if !defined (STLPORT) || !defined (_STLP_NO_UNCAUGHT_EXCEPT_SUPPORT)
struct UncaughtClassTest
{
  UncaughtClassTest(int &res) : _res(res)
  {}

  ~UncaughtClassTest() {
    _res = std::uncaught_exception()?1:0;
  }

  int &_res;
};
#endif

int EXAM_IMPL(exception_test::uncaught_except)
{
#if !defined (STLPORT) || !defined (_STLP_NO_UNCAUGHT_EXCEPT_SUPPORT)
  int uncaught_result = -1;
  {
    UncaughtClassTest test_inst(uncaught_result);
    EXAM_CHECK( uncaught_result == -1 );
  }
  EXAM_CHECK( uncaught_result == 0 );

  {
    try {
      uncaught_result = -1;
      UncaughtClassTest test_inst(uncaught_result);
      throw "exception";
    }
    catch (...) {
    }
  }
  EXAM_CHECK( uncaught_result == 1 );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(exception_test::exception_emission)
{
#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  std::string foo = "foo";
  try {
    throw std::runtime_error(foo);
  }
  catch (std::runtime_error const& e) {
    EXAM_CHECK( foo == e.what() );
    std::runtime_error clone("");
    clone = e;
    EXAM_CHECK(foo == clone.what() );
  }
  catch (...) {
    EXAM_CHECK( false );
  }

  try {
    throw std::runtime_error(foo);
  }
  catch (std::runtime_error e) {
    EXAM_CHECK( foo == e.what() );
    std::runtime_error clone("");
    clone = e;
    EXAM_CHECK(foo == clone.what() );
  }
  catch (...) {
    EXAM_CHECK( false );
  }

  std::string msg(512, 'a');
  try {
    throw std::runtime_error(msg);
  }
  catch (std::runtime_error const& e) {
    EXAM_CHECK(msg == e.what() );
    std::runtime_error clone("");
    clone = e;
    EXAM_CHECK(msg == clone.what() );
  }
  catch (...) {
    EXAM_CHECK( false );
  }

  try {
    throw std::runtime_error(msg);
  }
  catch (std::runtime_error e) {
    EXAM_CHECK(msg == e.what() );
    std::runtime_error clone("");
    clone = e;
    EXAM_CHECK(msg == clone.what() );
  }
  catch (...) {
    EXAM_CHECK( false );
  }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
