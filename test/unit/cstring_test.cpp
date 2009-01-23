#define _STLP_DO_IMPORT_CSTD_FUNCTIONS

#include "cstring_test.h"

#include <cstring>

//This test purpose is to check the right import of math.h C symbols
//into the std namespace so we do not use the using namespace std
//specification

#if defined (_MSC_VER) && (_MSC_VER >= 1400)
//For deprecated symbols like strcat, strtok...
#  pragma warning (disable : 4996)
#endif

int EXAM_IMPL(cstring_test::import_checks)
{
#if !defined (STLPORT) || defined (_STLP_USE_NAMESPACES)
  std::size_t bar = 0;
  EXAM_CHECK( bar == 0 );

  EXAM_CHECK( std::memchr("foo", 'o', 3) != NULL );
  EXAM_CHECK( std::memcmp("foo1", "foo2", 3) == 0 );
  char buf1[1], buf2[1];
  EXAM_CHECK( std::memcpy(buf1, buf2, 0) != NULL );
  EXAM_CHECK( std::memmove(buf1, buf2, 0) != NULL );
  EXAM_CHECK( std::memset(buf1, 0, 1) != NULL );
  char buf[16]; buf[0] = 0;
  const char* foo = "foo";
#  if !defined(_WIN32_WCE)
  EXAM_CHECK( std::strcoll("foo", "foo") == 0 );
  EXAM_CHECK( std::strerror(0) != NULL );
#  endif
  EXAM_CHECK( std::strcat((char*)buf, foo) == (char*)buf ); // buf <- foo
  EXAM_CHECK( std::strchr(foo, 'o') != NULL );
  EXAM_CHECK( std::strcmp("foo1", "foo2") < 0 );
  EXAM_CHECK( std::strcpy((char*)buf, foo) == (char*)buf ); // buf <- foo
  EXAM_CHECK( std::strcspn("foo", "o") == 1 );
  EXAM_CHECK( std::strlen("foo") == 3 );
  EXAM_CHECK( std::strncat((char*)buf, foo, 2) == (char*)buf ); // buf <- foofo
  EXAM_CHECK( std::strncmp("foo1", "foo2", 3) == 0 );
  EXAM_CHECK( std::strncpy((char*)buf, foo, 3) == (char*)buf ); // buf <- foo
  EXAM_CHECK( std::strpbrk(foo, "abcdo") == foo + 1 );
  const char* foofoo = "foofoo";
  EXAM_CHECK( std::strrchr(foofoo, 'f') == foofoo + 3 );
  EXAM_CHECK( std::strspn(foofoo, "aofz") == 6 );
  EXAM_CHECK( std::strstr(foo, "") == foo );
  char foofoobuf[] = "foofoo";
  EXAM_CHECK( std::strtok(foofoobuf, "z") != NULL );
#  if !defined(_WIN32_WCE)
  EXAM_CHECK( std::strxfrm((char*)buf, foo, 3) != 0 );
#  endif

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
