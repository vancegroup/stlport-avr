#include "locale_test.h"

#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <locale>
#  include <stdexcept>

#  if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#  endif

//
// tests implementation
//
void LocaleTest::messages_by_name()
{
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in
   * a runtime_error exception.
   */
#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    locale loc(locale::classic(), new messages_byname<char>(static_cast<char const*>(0)));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new messages_byname<char>("yasli_language"));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  /*
  try {
    locale loc(locale::classic(), new messages_byname<char>(""));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& e) {
    CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }
  */

#    if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  try {
    locale loc(locale::classic(), new messages_byname<wchar_t>(static_cast<char const*>(0)));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new messages_byname<wchar_t>("yasli_language"));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }
#    endif
#  endif
}

#endif
