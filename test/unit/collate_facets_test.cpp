#include "locale_test.h"

#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <locale>
#  include <stdexcept>
#  include <algorithm>

#  if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#  endif

//
// tests implementation
//
void LocaleTest::collate_facet()
{
  {
    CPPUNIT_ASSERT( has_facet<collate<char> >(locale::classic()) );
    collate<char> const& col = use_facet<collate<char> >(locale::classic());

    char const str1[] = "abcdef1";
    char const str2[] = "abcdef2";
    const size_t size1 = sizeof(str1) / sizeof(str1[0]) - 1;
    const size_t size2 = sizeof(str2) / sizeof(str2[0]) - 1;

    CPPUNIT_ASSERT( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 1) == 0 );
    CPPUNIT_ASSERT( col.compare(str1, str1 + size1, str2, str2 + size2) == -1 );

    //Smallest string should be before largest one:
    CPPUNIT_ASSERT( col.compare(str1, str1 + size1 - 2, str2, str2 + size2 - 1) == -1 );
    CPPUNIT_ASSERT( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 2) == 1 );
  }

#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    locale loc("fr_FR");
    {
      CPPUNIT_ASSERT( has_facet<collate<char> >(loc) );
      collate<char> const& col = use_facet<collate<char> >(loc);

      char const str1[] = "abcdef1";
      char const str2[] = "abcdef2";
      const size_t size1 = sizeof(str1) / sizeof(str1[0]) - 1;
      const size_t size2 = sizeof(str2) / sizeof(str2[0]) - 1;

      CPPUNIT_ASSERT( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 1) == 0 );
      CPPUNIT_ASSERT( col.compare(str1, str1 + size1, str2, str2 + size2) == -1 );

      //Smallest string should be before largest one:
      CPPUNIT_ASSERT( col.compare(str1, str1 + size1 - 2, str2, str2 + size2 - 1) == -1 );
      CPPUNIT_ASSERT( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 2) == 1 );
    }
    {
      CPPUNIT_ASSERT( has_facet<collate<char> >(loc) );

      string strs[] = {"abdd", "abçd", "abbd", "abcd"};
      sort(strs, strs + 4, loc);
      CPPUNIT_ASSERT( strs[0] == "abbd" );
      CPPUNIT_ASSERT( strs[1] == "abcd" );
      CPPUNIT_ASSERT( strs[2] == "abçd" );
      CPPUNIT_ASSERT( strs[3] == "abdd" );
    }
#    if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
    {
      CPPUNIT_ASSERT( has_facet<collate<wchar_t> >(loc) );
      collate<wchar_t> const& col = use_facet<collate<wchar_t> >(loc);

      wchar_t const str1[] = L"abcdef1";
      wchar_t const str2[] = L"abcdef2";
      const size_t size1 = sizeof(str1) / sizeof(str1[0]) - 1;
      const size_t size2 = sizeof(str2) / sizeof(str2[0]) - 1;

      CPPUNIT_ASSERT( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 1) == 0 );
      CPPUNIT_ASSERT( col.compare(str1, str1 + size1, str2, str2 + size2) == -1 );

      //Smallest string should be before largest one:
      CPPUNIT_ASSERT( col.compare(str1, str1 + size1 - 2, str2, str2 + size2 - 1) == -1 );
      CPPUNIT_ASSERT( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 2) == 1 );
    }
    {
      CPPUNIT_ASSERT( has_facet<collate<wchar_t> >(loc) );

      // Here we would like to use L"abçd" but it looks like all compilers
      // do not support storage of unicode characters in exe resulting in
      // compilation error. We avoid this test for the moment.
      wstring strs[] = {L"abdd", L"abcd", L"abbd", L"abcd"};
      sort(strs, strs + 4, loc);
      CPPUNIT_ASSERT( strs[0] == L"abbd" );
      CPPUNIT_ASSERT( strs[1] == L"abcd" );
      CPPUNIT_ASSERT( strs[2] == L"abcd" );
      CPPUNIT_ASSERT( strs[3] == L"abdd" );
    }
#    endif
  }
  catch (runtime_error const&) {
    CPPUNIT_MESSAGE("No french locale to check collate facet");
  }
#  endif
}

void LocaleTest::collate_by_name()
{
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in
   * a runtime_error exception.
   */
#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    locale loc(locale::classic(), new collate_byname<char>(static_cast<char const*>(0)));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new collate_byname<char>("yasli_language"));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

#    if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  try {
    locale loc(locale::classic(), new collate_byname<wchar_t>(static_cast<char const*>(0)));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new collate_byname<wchar_t>("yasli_language"));
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
