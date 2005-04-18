#include <errno.h>
#include <errno.h> // not typo, check errno def/undef/redef

#ifndef _STLP_WCE

#include "cppunit/cppunit_proxy.h"

//
// TestCase class
//
class ErrnoTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(ErrnoTest);
  CPPUNIT_TEST(check);
  CPPUNIT_TEST_SUITE_END();

protected:
  void check();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ErrnoTest);

void ErrnoTest::check()
{
  errno = 1;

  CPPUNIT_ASSERT( errno == 1 );
  errno = 0;

/* Note: in common, you can't write ::errno or std::errno,
 * due to errno in most cases is just a macro, that frequently
 * (in MT environment errno is a per-thread value) expand to something like
 * (*__errno_location()). I don't know way how masquerade such
 * things: name of macro can't include ::.
 *
 *                - ptr, 2005-03-30
 */
# if 0
  if ( ::errno != 0 ) {
    return 1;
  }
  if ( std::errno != 0 ) {
    return 1;
  }
# endif
}
#endif // _STLP_WCE
