#include <algorithm>
#if !defined (STLPORT) || !defined (_STLP_NO_IOSTREAMS)
#include <sstream>
#include <functional>
#include <iterator>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class IstmitTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(IstmitTest);
  CPPUNIT_TEST(istmit1);
  CPPUNIT_TEST_SUITE_END();

protected:
  void istmit1();
};

CPPUNIT_TEST_SUITE_REGISTRATION(IstmitTest);

//
// tests implementation
//
void IstmitTest::istmit1()
{
  char* buff="MyString";
  istringstream istr( buff );
  
  char buffer [100];
  size_t i = 0;
  istr.unsetf(ios::skipws); // Disable white-space skipping.
#ifndef _STLP_LIMITED_DEFAULT_TEMPLATES
  istream_iterator<char> s(istr),meos;  //*TY 01/10/1999 - added eos()
#else
  istream_iterator<char, ptrdiff_t> s(istr),meos;  //*TY 01/10/1999 - added eos()
#endif
  while(!(s == meos)  &&
  //*TY 01/10/1999 - added end of stream check 
  // NOTE operator!= should not be used here ifndef __STL_FUNCTION_TMPL_PARTIAL_ORDER
        *s != '\n' &&
      (i < sizeof(buffer)/sizeof(buffer[0])) )    //*TY 07/28/98 - added index check
    buffer[i++] = *s++;
  buffer[i] = '\0'; // Null terminate buffer.

  CPPUNIT_ASSERT(!strcmp(buffer, buff));
}

#endif
