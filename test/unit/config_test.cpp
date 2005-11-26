#include <new>

#include "cppunit/cppunit_proxy.h"

//Specific STLport test case:
#if defined (STLPORT)

//
// TestCase class
//
class ConfigTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(ConfigTest);
  CPPUNIT_TEST(placement_new_bug);
  CPPUNIT_TEST(endianess);
  CPPUNIT_TEST_SUITE_END();

  protected:
    void placement_new_bug();
    void endianess();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ConfigTest);


void ConfigTest::placement_new_bug()
{
  int int_val = 1;
  int *pint;
  pint = new(&int_val) int();
  CPPUNIT_ASSERT( pint == &int_val );
#  if defined (_STLP_DEF_CONST_PLCT_NEW_BUG)
  CPPUNIT_ASSERT( int_val != 0 );
#  else
  CPPUNIT_ASSERT( int_val == 0 );
#  endif
}

void ConfigTest::endianess()
{
  int val = 0x01020304;
  char *ptr = (char*)(&val);
#  if defined (_STLP_BIG_ENDIAN)
  //This test only work if sizeof(int) == 4, this is a known limitation
  //that will be handle the day we find a compiler for which it is false.
  CPPUNIT_ASSERT( *ptr == 0x01 ||
                  sizeof(int) > 4 && *ptr == 0x00 );
#  elif defined (_STLP_LITTLE_ENDIAN)
  CPPUNIT_ASSERT( *ptr == 0x04 );
#  endif
}

#endif
