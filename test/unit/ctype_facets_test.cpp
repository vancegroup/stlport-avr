#include "locale_test.h"

#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <locale>
#  include <stdexcept>
#  include <memory>

#  if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#  endif

// Pls, don't write #ifdef _STLP_REAL_LOCALE_IMPLEMENTED here!
// It undefined in any case!!!!!

static const char* tested_locales[] = {
//name,
#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  // We need exception support to check support of the following localizations.
  "fr_FR",
  "ru_RU.koi8r",
  "en_GB",
  "en_US",
#  endif
  "",
  "C"
};

//
// tests implementation
//
void LocaleTest::_ctype_facet( const locale& loc)
{
  CPPUNIT_ASSERT( has_facet<ctype<char> >(loc) );
  ctype<char> const& ct = use_facet<ctype<char> >(loc);
  //is
  {
    CPPUNIT_ASSERT( ct.is(ctype_base::digit, '0') );
    CPPUNIT_ASSERT( ct.is(ctype_base::upper, 'A') );
    CPPUNIT_ASSERT( ct.is(ctype_base::lower, 'a') );
    CPPUNIT_ASSERT( ct.is(ctype_base::alpha, 'A') );
    CPPUNIT_ASSERT( ct.is(ctype_base::space, ' ') );
    CPPUNIT_ASSERT( !ct.is(ctype_base::space, '2') );
    CPPUNIT_ASSERT( ct.is(ctype_base::punct, '.') );
    CPPUNIT_ASSERT( ct.is(ctype_base::xdigit, 'a') );
  }

  //is range
  {
    char values[] = "0Aa .";
    ctype_base::mask res[sizeof(values)];
    ct.is(values, values + sizeof(values), res);
    // '0'
    CPPUNIT_ASSERT( (res[0] & ctype_base::print) != 0 );
    CPPUNIT_ASSERT( (res[0] & ctype_base::digit) != 0 );
    CPPUNIT_ASSERT( (res[0] & ctype_base::xdigit) != 0 );
    // 'A'
    CPPUNIT_ASSERT( (res[1] & ctype_base::print) != 0 );
    CPPUNIT_ASSERT( (res[1] & ctype_base::alpha) != 0 );
    CPPUNIT_ASSERT( (res[1] & ctype_base::xdigit) != 0 );
    CPPUNIT_ASSERT( (res[1] & ctype_base::upper) != 0 );
    // 'a'
    CPPUNIT_ASSERT( (res[2] & ctype_base::print) != 0 );
    CPPUNIT_ASSERT( (res[2] & ctype_base::alpha) != 0 );
    CPPUNIT_ASSERT( (res[2] & ctype_base::xdigit) != 0 );
    CPPUNIT_ASSERT( (res[2] & ctype_base::lower) != 0 );
    CPPUNIT_ASSERT( (res[2] & ctype_base::space) == 0 );
    // ' '
    CPPUNIT_ASSERT( (res[3] & ctype_base::print) != 0 );
    CPPUNIT_ASSERT( (res[3] & ctype_base::space) != 0 );
    CPPUNIT_ASSERT( (res[3] & ctype_base::digit) == 0 );
    // '.'
    CPPUNIT_ASSERT( (res[4] & ctype_base::print) != 0 );
    CPPUNIT_ASSERT( (res[4] & ctype_base::punct) != 0 );
    CPPUNIT_ASSERT( (res[4] & ctype_base::digit) == 0 );
  }

  //scan_is
  {
    char range[] = "abAc123 .";
    const char *rbeg = range;
    const char *rend = range + sizeof(range);

    const char *res;
    res = ct.scan_is((ctype_base::mask)(ctype_base::alpha | ctype_base::lower), rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == 'a' );

    res = ct.scan_is(ctype_base::upper, rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == 'A' );

    res = ct.scan_is(ctype_base::punct, rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == '.' );
  }

  //scan_not
  {
    char range[] = "abAc123 .";
    const char *rbeg = range;
    const char *rend = range + sizeof(range);

    const char *res;
    res = ct.scan_not((ctype_base::mask)(ctype_base::alpha | ctype_base::lower), rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == '1' );

    res = ct.scan_not(ctype_base::alpha, rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == '1' );

    res = ct.scan_not(ctype_base::punct, rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == 'a' );
  }

  //toupper
  {
    CPPUNIT_ASSERT( ct.toupper('a') == 'A' );
    CPPUNIT_ASSERT( ct.toupper('A') == 'A' );
    CPPUNIT_ASSERT( ct.toupper('1') == '1' );
  }

  //toupper range
  {
    char range[] = "abAc1";
    char expected_range[] = "ABAC1";
    ct.toupper(range, range + sizeof(range));
    CPPUNIT_ASSERT( equal(range, range + sizeof(range), expected_range) );
  }

  //tolower
  {
    CPPUNIT_ASSERT( ct.tolower('A') == 'a' );
    CPPUNIT_ASSERT( ct.tolower('a') == 'a' );
    CPPUNIT_ASSERT( ct.tolower('1') == '1' );
  }

  //tolower range
  {
    char range[] = "ABaC1";
    char expected_range[] = "abac1";
    ct.tolower(range, range + sizeof(range));
    CPPUNIT_ASSERT( equal(range, range + sizeof(range), expected_range) );
  }

  //widen
  {
    CPPUNIT_ASSERT( ct.widen('a') == 'a' );
  }

  //widen range
  {
    char range[] = "ABaC1";
    char res[sizeof(range)];
    ct.widen(range, range + sizeof(range), res);
    CPPUNIT_ASSERT( equal(range, range + sizeof(range), res) );
  }

  //narrow
  {
    CPPUNIT_ASSERT( ct.narrow('a', 'b') == 'a' );
  }

  //narrow range
  {
    char range[] = "ABaC1";
    char res[sizeof(range)];
    ct.narrow(range, range + sizeof(range), 'b', res);
    CPPUNIT_ASSERT( equal(range, range + sizeof(range), res) );
  }
}

void LocaleTest::_ctype_facet_w( const locale& loc )
{
# ifndef _STLP_NO_WCHAR_T
  CPPUNIT_ASSERT( has_facet<ctype<wchar_t> >(loc) );
  ctype<wchar_t> const& wct = use_facet<ctype<wchar_t> >(loc);
  //is
  {
    CPPUNIT_ASSERT( wct.is(ctype_base::digit, L'0') );
    CPPUNIT_ASSERT( wct.is(ctype_base::upper, L'A') );
    CPPUNIT_ASSERT( wct.is(ctype_base::lower, L'a') );
    CPPUNIT_ASSERT( wct.is(ctype_base::alpha, L'A') );
    CPPUNIT_ASSERT( wct.is(ctype_base::space, L' ') );
    CPPUNIT_ASSERT( !wct.is(ctype_base::space, L'2') );
    CPPUNIT_ASSERT( wct.is(ctype_base::punct, L'.') );
    CPPUNIT_ASSERT( wct.is(ctype_base::xdigit, L'a') );
  }

  //is range
  {
    wchar_t values[] = L"0Aa .";
    ctype_base::mask res[sizeof(values) / sizeof(wchar_t)];
    wct.is(values, values + (sizeof(values) / sizeof(wchar_t)), res);
    // '0'
    CPPUNIT_ASSERT( (res[0] & ctype_base::print) != 0 );
    CPPUNIT_ASSERT( (res[0] & ctype_base::digit) != 0 );
    CPPUNIT_ASSERT( (res[0] & ctype_base::xdigit) != 0 );
    // 'A'
    CPPUNIT_ASSERT( (res[1] & ctype_base::print) != 0 );
    CPPUNIT_ASSERT( (res[1] & ctype_base::alpha) != 0 );
    CPPUNIT_ASSERT( (res[1] & ctype_base::xdigit) != 0 );
    CPPUNIT_ASSERT( (res[1] & ctype_base::upper) != 0 );
    // 'a'
    CPPUNIT_ASSERT( (res[2] & ctype_base::print) != 0 );
    CPPUNIT_ASSERT( (res[2] & ctype_base::alpha) != 0 );
    CPPUNIT_ASSERT( (res[2] & ctype_base::xdigit) != 0 );
    CPPUNIT_ASSERT( (res[2] & ctype_base::lower) != 0 );
    CPPUNIT_ASSERT( (res[2] & ctype_base::space) == 0 );
    // ' '
    CPPUNIT_ASSERT( (res[3] & ctype_base::print) != 0 );
    CPPUNIT_ASSERT( (res[3] & ctype_base::space) != 0 );
    CPPUNIT_ASSERT( (res[3] & ctype_base::digit) == 0 );
    // '.'
    CPPUNIT_ASSERT( (res[4] & ctype_base::print) != 0 );
    CPPUNIT_ASSERT( (res[4] & ctype_base::punct) != 0 );
    CPPUNIT_ASSERT( (res[4] & ctype_base::digit) == 0 );
  }

  //scan_is
  {
    wchar_t range[] = L"abAc123 .";
    const wchar_t *rbeg = range;
    const wchar_t *rend = range + (sizeof(range) / sizeof(wchar_t));

    const wchar_t *res;
    res = wct.scan_is((ctype_base::mask)(ctype_base::alpha | ctype_base::lower), rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == L'a' );

    res = wct.scan_is(ctype_base::upper, rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == L'A' );

    res = wct.scan_is(ctype_base::punct, rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == L'.' );
  }

  //scan_not
  {
    wchar_t range[] = L"abAc123 .";
    const wchar_t *rbeg = range;
    const wchar_t *rend = range + (sizeof(range) / sizeof(wchar_t));

    const wchar_t *res;
    res = wct.scan_not((ctype_base::mask)(ctype_base::alpha | ctype_base::lower), rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == L'1' );

    res = wct.scan_not(ctype_base::alpha, rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == L'1' );

    res = wct.scan_not(ctype_base::punct, rbeg, rend);
    CPPUNIT_ASSERT( res != rend );
    CPPUNIT_ASSERT( *res == L'a' );
  }

  //toupper
  {
    CPPUNIT_ASSERT( wct.toupper(L'a') == L'A' );
    CPPUNIT_ASSERT( wct.toupper(L'A') == L'A' );
    CPPUNIT_ASSERT( wct.toupper(L'1') == L'1' );
  }

  //toupper range
  {
    wchar_t range[] = L"abAc1";
    wchar_t expected_range[] = L"ABAC1";
    wct.toupper(range, range + sizeof(range) / sizeof(wchar_t));
    CPPUNIT_ASSERT( equal(range, range + sizeof(range) / sizeof(wchar_t), expected_range) );
  }

  //tolower
  {
    CPPUNIT_ASSERT( wct.tolower(L'A') == L'a' );
    CPPUNIT_ASSERT( wct.tolower(L'a') == L'a' );
    CPPUNIT_ASSERT( wct.tolower(L'1') == L'1' );
  }

  //tolower range
  {
    wchar_t range[] = L"ABaC1";
    wchar_t expected_range[] = L"abac1";
    wct.tolower(range, range + sizeof(range) / sizeof(wchar_t));
    CPPUNIT_ASSERT( equal(range, range + sizeof(range) / sizeof(wchar_t), expected_range) );
  }

  //widen
  {
    CPPUNIT_ASSERT( wct.widen('a') == L'a' );
  }

  //widen range
  {
    char range[] = "ABaC1";
    wchar_t res[sizeof(range)];
    wchar_t expected_res[] = L"ABaC1";
    wct.widen(range, range + sizeof(range), res);
    CPPUNIT_ASSERT( equal(expected_res, expected_res + sizeof(range), res) );
  }

  //narrow
  {
    CPPUNIT_ASSERT( wct.narrow(L'a', 'b') == L'a' );
  }

  //narrow range
  {
    wchar_t range[] = L"ABaC1";
    char res[sizeof(range) / sizeof(wchar_t)];
    char expected_res[] = "ABaC1";
    wct.narrow(range, range + sizeof(range) / sizeof(wchar_t), 'b', res);
    CPPUNIT_ASSERT( equal(expected_res, expected_res + sizeof(range) / sizeof(wchar_t), res) );
  }
# endif
}


template <class _Tp>
void test_supported_locale(LocaleTest inst, _Tp __test) {
  size_t n = sizeof(tested_locales) / sizeof(tested_locales[0]);
  for (size_t i = 0; i < n; ++i) {
    auto_ptr<locale> loc;
#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
    try {
#  endif
      loc.reset(new locale(tested_locales[i]));
#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
    }
    catch (runtime_error const&) {
      //This locale is not supported.
      continue;
    }
#  endif

    CPPUNIT_MESSAGE( loc->name().c_str() );
    (inst.*__test)(*loc);

    loc.reset(new locale(locale::classic(), tested_locales[i], locale::ctype));
    (inst.*__test)(*loc);
  }
}

void LocaleTest::ctype_facet()
{
  test_supported_locale(*this, &LocaleTest::_ctype_facet);
#ifndef _STLP_NO_WCHAR_T
  test_supported_locale(*this, &LocaleTest::_ctype_facet_w);
#endif
}

void LocaleTest::ctype_by_name()
{
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in
   * a runtime_error exception.
   */
#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    locale loc(locale::classic(), new ctype_byname<char>(static_cast<char const*>(0)));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new ctype_byname<char>("yasli_language"));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new codecvt_byname<char, char, mbstate_t>(static_cast<char const*>(0)));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new codecvt_byname<char, char, mbstate_t>("yasli_language"));
    //STLport implementation do not care about name pass to this facet.
#    if !defined (STLPORT)
    CPPUNIT_ASSERT( false );
#    endif
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new ctype_byname<char>("fr_FR"));
    CPPUNIT_ASSERT( has_facet<ctype<char> >(loc) );
    ctype<char> const& ct = use_facet<ctype<char> >(loc);
    CPPUNIT_ASSERT( ct.is(ctype_base::mask(ctype_base::print | ctype_base::lower | ctype_base::alpha), 'ç') );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

#    if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  try {
    locale loc(locale::classic(), new ctype_byname<wchar_t>(static_cast<char const*>(0)));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new ctype_byname<wchar_t>("yasli_language"));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new codecvt_byname<wchar_t, char, mbstate_t>(static_cast<char const*>(0)));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new codecvt_byname<wchar_t, char, mbstate_t>("yasli_language"));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }
#    endif
#  endif
}

#endif
