// -*- C++ -*- Time-stamp: <2012-04-16 19:02:56 ptr>

/*
 * Copyright (c) 2004-2009
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
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

#include "locale_test.h"

#include <sstream>
#include <locale>
#include <stdexcept>

using namespace std;

static const char* tested_locales[] = {
//name,
  "fr_FR",
  "ru_RU.koi8r",
  "en_GB",
  "en_US",
  "",
  "C"
};

typedef void (locale_test::*_Test) (const locale&);

static void test_supported_locale( locale_test& inst, _Test __test )
{
  size_t n = sizeof(tested_locales) / sizeof(tested_locales[0]);

  for ( size_t i = 0; i < n; ++i ) {
    locale loc;
    try {
      locale tmp(tested_locales[i]);
      loc = tmp;
    }
    catch ( runtime_error const& ) {
      //This locale is not supported.
      continue;
    }

    (inst.*__test)(loc);
  }
}

int EXAM_IMPL(locale_test::locale_by_name)
{
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in
   * a runtime_error exception.
   */
  try {
    locale loc(static_cast<char const*>(0));

    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch ( runtime_error const& ) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc("yasli_language");

    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    string very_large_locale_name(1024, '?');
    locale loc(very_large_locale_name.c_str());

    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    string very_large_locale_name("LC_CTYPE=");
    very_large_locale_name.append(1024, '?');
    locale loc(very_large_locale_name.c_str());

    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    string very_large_locale_name("LC_ALL=");
    very_large_locale_name.append(1024, '?');
    locale loc(very_large_locale_name.c_str());

    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc( "C" );

    EXAM_MESSAGE( "'C' locale always here" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

  try {
    // On platform without real localization support we should rely on the "C" locale facet.
    locale loc("");

    EXAM_MESSAGE( "'' locale always here" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(locale_test::loc_has_facet)
{
  locale loc("C");
  typedef numpunct<char> implemented_facet;
  EXAM_CHECK( has_facet<implemented_facet>(loc) );

  /*
  typedef num_put<char, back_insert_iterator<string> > not_implemented_facet;
  EXAM_RESULT( !has_facet<not_implemented_facet>(loc) );
  */
  return EXAM_RESULT;
}

int EXAM_IMPL(locale_test::locale_init_problem)
{
  test_supported_locale(*this, &locale_test::_locale_init_problem);

  return EXAM_RESULT;
}

/*
 * Creation of a locale instance imply initialization of some STLport internal
 * static objects first. We use a static instance of locale to check that this
 * initialization is done correctly.
 */
static locale global_loc;
static locale other_loc("");

void locale_test::_locale_init_problem( const locale& loc)
{
#    if !defined (__APPLE__) && !defined (__FreeBSD__) || \
        !defined(__GNUC__) || ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__> 3)))
  typedef codecvt<char,char,mbstate_t> my_facet;
#    else
// std::mbstate_t required for gcc 3.3.2 on FreeBSD...
// I am not sure what key here---FreeBSD or 3.3.2...
//      - ptr 2005-04-04
  typedef codecvt<char,char,std::mbstate_t> my_facet;
#    endif

  locale loc_ref(global_loc);
  {
    locale gloc( loc_ref, new my_facet() );
    EXAM_CHECK_ASYNC( has_facet<my_facet>( gloc ) );
    //The following code is just here to try to confuse the reference counting underlying mecanism:
    locale::global( locale::classic() );
    locale::global( gloc );
  }

  try {
    ostringstream os("test") ;
    locale loc2( loc, new my_facet() );
     EXAM_CHECK_ASYNC( has_facet<my_facet>( loc2 ) );
    os.imbue( loc2 );
  }
  catch ( runtime_error& ) {
    EXAM_ERROR_ASYNC( "unexpected runtime_error exception" );
  }
  catch ( ... ) {
    EXAM_ERROR_ASYNC( "unexpected unknown exception" );
  }

  try {
    ostringstream os2("test2");
  }
  catch ( runtime_error& ) {
    EXAM_ERROR_ASYNC( "unexpected runtime_error exception" );
  }
  catch ( ... ) {
    EXAM_ERROR_ASYNC( "unexpected unknown exception" );
  }
}

int EXAM_IMPL(locale_test::default_locale)
{
  locale loc( "" );

  return EXAM_RESULT;
}

class dummy_facet :
    public locale::facet
{
  public:
    static locale::id id;
};

locale::id dummy_facet::id;

int EXAM_IMPL(locale_test::combine)
{
  {
    try {
      locale loc("");
      if (!has_facet<messages<char> >(loc)) {
        loc.combine<messages<char> >(loc);
        EXAM_ERROR( "runtime_error exception expected" );
      }
    }
    catch (const runtime_error & /* e */) {
      EXAM_MESSAGE( "runtime_error exception, as expected" );
    }

    try {
      locale loc;
      if (!has_facet<dummy_facet>(loc)) {
        loc.combine<dummy_facet>(loc);
        EXAM_ERROR( "runtime_error exception expected" );
      }
    }
    catch (const runtime_error & /* e */) {
      EXAM_MESSAGE( "runtime_error exception, as expected" );
    }
  }

  locale loc1(locale::classic()), loc2;
  size_t loc1_index = 0;
  for ( size_t i = 0; _get_ref_monetary(i) != 0; ++i ) {
    try {
      {
        locale loc(_get_ref_monetary_name(_get_ref_monetary(i)));
        if (loc1 == locale::classic()) {
          loc1 = loc;
          loc1_index = i;
          continue;
        } else {
          loc2 = loc;
        }
      }

      //We can start the test
      ostringstream ostr;
      ostr << "combining '" << loc2.name() << "' money facets with '" << loc1.name() << "'";
      EXAM_MESSAGE( ostr.str().c_str() );

      //We are going to combine money facets as all formats are different.
      {
        //We check that resulting locale has correctly acquire loc2 facets.
        locale loc = loc1.combine<moneypunct<char, true> >(loc2);
        loc = loc.combine<moneypunct<char, false> >(loc2);
        loc = loc.combine<money_put<char> >(loc2);
        loc = loc.combine<money_get<char> >(loc2);

        //Check loc has the correct facets:
        _money_put_get2(loc2, loc, _get_ref_monetary(i));

        //Check loc1 has not been impacted:
        _money_put_get2(loc1, loc1, _get_ref_monetary(loc1_index));

        //Check loc2 has not been impacted:
        _money_put_get2(loc2, loc2, _get_ref_monetary(i));
      }
      {
        //We check that resulting locale has not wrongly acquire loc1 facets that hasn't been combine:
        locale loc = loc2.combine<numpunct<char> >(loc1);
        loc = loc.combine<time_put<char> >(loc1);
        loc = loc.combine<time_get<char> >(loc1);

        //Check loc has the correct facets:
        _money_put_get2(loc2, loc, _get_ref_monetary(i));

        //Check loc1 has not been impacted:
        _money_put_get2(loc1, loc1, _get_ref_monetary(loc1_index));

        //Check loc2 has not been impacted:
        _money_put_get2(loc2, loc2, _get_ref_monetary(i));
      }

      {
        // Check auto combination do not result in weird reference counting behavior 
        // (might generate a crash).
        loc1.combine<numpunct<char> >(loc1);
      }

      loc1 = loc2;
      loc1_index = i;
    }
    catch (runtime_error const&) {
      //This locale is not supported.
      continue;
    }
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(locale_test::collate_facet)
{
  {
    EXAM_CHECK( has_facet<collate<char> >(locale::classic()) );
    collate<char> const& col = use_facet<collate<char> >(locale::classic());

    char const str1[] = "abcdef1";
    char const str2[] = "abcdef2";
    const size_t size1 = sizeof(str1) / sizeof(str1[0]) - 1;
    const size_t size2 = sizeof(str2) / sizeof(str2[0]) - 1;

    EXAM_CHECK( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 1) == 0 );
    EXAM_CHECK( col.compare(str1, str1 + size1, str2, str2 + size2) == -1 );

    //Smallest string should be before largest one:
    EXAM_CHECK( col.compare(str1, str1 + size1 - 2, str2, str2 + size2 - 1) == -1 );
    EXAM_CHECK( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 2) == 1 );
  }

  try {
    locale loc("fr_FR");
    {
      EXAM_CHECK( has_facet<collate<char> >(loc) );
      collate<char> const& col = use_facet<collate<char> >(loc);

      char const str1[] = "abcdef1";
      char const str2[] = "abcdef2";
      const size_t size1 = sizeof(str1) / sizeof(str1[0]) - 1;
      const size_t size2 = sizeof(str2) / sizeof(str2[0]) - 1;

      EXAM_CHECK( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 1) == 0 );
      EXAM_CHECK( col.compare(str1, str1 + size1, str2, str2 + size2) == -1 );

      //Smallest string should be before largest one:
      EXAM_CHECK( col.compare(str1, str1 + size1 - 2, str2, str2 + size2 - 1) == -1 );
      EXAM_CHECK( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 2) == 1 );
    }
    {
      EXAM_CHECK( has_facet<collate<char> >(loc) );
      collate<char> const& col = use_facet<collate<char> >(loc);

      string strs[] = {"abdd", "ab\x0e7d", "abbd", "abcd"};

      string transformed[4];
      for (size_t i = 0; i < 4; ++i) {
        transformed[i] = col.transform(strs[i].data(), strs[i].data() + strs[i].size());
      }

      sort(strs, strs + 4, loc);
      EXAM_CHECK( strs[0] == "abbd" );
      EXAM_CHECK( strs[1] == "abcd" );
      EXAM_CHECK( strs[2] == "ab\x0e7d" );
      EXAM_CHECK( strs[3] == "abdd" );

      sort(transformed, transformed + 4);

      EXAM_CHECK( col.transform(strs[0].data(), strs[0].data() + strs[0].size()) == transformed[0] );
      EXAM_CHECK( col.transform(strs[1].data(), strs[1].data() + strs[1].size()) == transformed[1] );
      EXAM_CHECK( col.transform(strs[2].data(), strs[2].data() + strs[2].size()) == transformed[2] );
      EXAM_CHECK( col.transform(strs[3].data(), strs[3].data() + strs[3].size()) == transformed[3] );

      // Check empty string result in empty key.
      EXAM_CHECK( col.transform(strs[0].data(), strs[0].data()).empty() );

      // Check that only characters that matter are taken into accout to build the key.
      EXAM_CHECK( col.transform(strs[0].data(), strs[0].data() + 2) == col.transform(strs[1].data(), strs[1].data() + 2) );
    }
#    if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
    {
      EXAM_CHECK( has_facet<collate<wchar_t> >(loc) );
      collate<wchar_t> const& col = use_facet<collate<wchar_t> >(loc);

      wchar_t const str1[] = L"abcdef1";
      wchar_t const str2[] = L"abcdef2";
      const size_t size1 = sizeof(str1) / sizeof(str1[0]) - 1;
      const size_t size2 = sizeof(str2) / sizeof(str2[0]) - 1;

      EXAM_CHECK( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 1) == 0 );
      EXAM_CHECK( col.compare(str1, str1 + size1, str2, str2 + size2) == -1 );

      //Smallest string should be before largest one:
      EXAM_CHECK( col.compare(str1, str1 + size1 - 2, str2, str2 + size2 - 1) == -1 );
      EXAM_CHECK( col.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 2) == 1 );
    }
    {
      size_t i;
      EXAM_CHECK( has_facet<collate<wchar_t> >(loc) );
      collate<wchar_t> const& col = use_facet<collate<wchar_t> >(loc);

      // Here we would like to use L"abçd" but it looks like all compilers
      // do not support storage of unicode characters in exe resulting in
      // compilation error. We avoid this test for the moment.
      wstring strs[] = {L"abdd", L"abcd", L"abbd", L"abcd"};

      wstring transformed[4];
      for (i = 0; i < 4; ++i) {
        transformed[i] = col.transform(strs[i].data(), strs[i].data() + strs[i].size());
      }

      sort(strs, strs + 4, loc);
      EXAM_CHECK( strs[0] == L"abbd" );
      EXAM_CHECK( strs[1] == L"abcd" );
      EXAM_CHECK( strs[2] == L"abcd" );
      EXAM_CHECK( strs[3] == L"abdd" );

      sort(transformed, transformed + 4);

      EXAM_CHECK( col.transform(strs[0].data(), strs[0].data() + strs[0].size()) == transformed[0] );
      EXAM_CHECK( col.transform(strs[1].data(), strs[1].data() + strs[1].size()) == transformed[1] );
      EXAM_CHECK( col.transform(strs[2].data(), strs[2].data() + strs[2].size()) == transformed[2] );
      EXAM_CHECK( col.transform(strs[3].data(), strs[3].data() + strs[3].size()) == transformed[3] );

      EXAM_CHECK( col.transform(strs[0].data(), strs[0].data()).empty() );

      EXAM_CHECK( col.transform(strs[0].data(), strs[0].data() + 2) == col.transform(strs[1].data(), strs[1].data() + 2) );
    }
#    endif
  }
  catch ( runtime_error const& ) {
    // EXAM_MESSAGE("No french locale to check collate facet");
    throw exam::skip_exception();
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(locale_test::collate_by_name)
{
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in
   * a runtime_error exception.
   */
  try {
    locale loc(locale::classic(), new collate_byname<char>(static_cast<char const*>(0)));

    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new collate_byname<char>("yasli_language"));

    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    string veryLongFacetName("LC_COLLATE=");
    veryLongFacetName.append(512, '?');
    locale loc(locale::classic(), new collate_byname<char>(veryLongFacetName.c_str()));

    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), "C", locale::collate);
  }
  catch (runtime_error const& e) {
    EXAM_MESSAGE( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_MESSAGE( "unexpected unkown exception" );
  }

  try {
    // On platform without real localization support we should rely on the "C" facet.
    locale loc(locale::classic(), "", locale::collate);
  }
  catch (runtime_error const& e) {
    EXAM_MESSAGE( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_MESSAGE( "unexpected unkown exception" );
  }

  try {
    locale loc(locale::classic(), new collate_byname<char>("C"));

    //We check that the C locale gives a lexicographical comparison:
    collate<char> const& cfacet_byname = use_facet<collate<char> >(loc);
    collate<char> const& cfacet = use_facet<collate<char> >(locale::classic());

    char const str1[] = "abcdef1";
    char const str2[] = "abcdef2";
    const size_t size1 = sizeof(str1) / sizeof(str1[0]) - 1;
    const size_t size2 = sizeof(str2) / sizeof(str2[0]) - 1;

    EXAM_CHECK( cfacet_byname.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 1) ==
                    cfacet.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 1) );
    EXAM_CHECK( cfacet_byname.compare(str1, str1 + size1, str2, str2 + size2) ==
                    cfacet.compare(str1, str1 + size1, str2, str2 + size2) );

    //Smallest string should be before largest one:
    EXAM_CHECK( cfacet_byname.compare(str1, str1 + size1 - 2, str2, str2 + size2 - 1) ==
                    cfacet.compare(str1, str1 + size1 - 2, str2, str2 + size2 - 1) );
    EXAM_CHECK( cfacet_byname.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 2) ==
                    cfacet.compare(str1, str1 + size1 - 1, str2, str2 + size2 - 2) );

    // We cannot play with 'ç' char here because doing so would make test result
    // dependant on char being consider as signed or not...
    string strs[] = {"abdd", /* "abçd",*/ "abbd", "abcd"};

    vector<string> v1(strs, strs + sizeof(strs) / sizeof(strs[0]));
    sort(v1.begin(), v1.end(), loc);
    vector<string> v2(strs, strs + sizeof(strs) / sizeof(strs[0]));
    sort(v2.begin(), v2.end(), locale::classic());
    EXAM_CHECK( v1 == v2 );

    EXAM_CHECK( (cfacet_byname.transform(v1[0].data(), v1[0].data() + v1[0].size()).compare(cfacet_byname.transform(v1[1].data(), v1[1].data() + v1[1].size())) ==
                    v1[0].compare(v1[1])) );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_MESSAGE( "unexpected unkown exception" );
  }

#    if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
#      if defined (STLPORT) || !defined (__GNUC__)
  try {
    locale loc(locale::classic(), new collate_byname<wchar_t>(static_cast<char const*>(0)));

    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#      endif

  try {
    locale loc(locale::classic(), new collate_byname<wchar_t>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#    endif

  return EXAM_RESULT;
}

void locale_test::_ctype_facet( const locale& loc)
{
  EXAM_CHECK_ASYNC( has_facet<ctype<char> >(loc) );
  ctype<char> const& ct = use_facet<ctype<char> >(loc);
  //is
  {
    EXAM_CHECK_ASYNC( ct.is(ctype_base::digit, '0') );
    EXAM_CHECK_ASYNC( ct.is(ctype_base::upper, 'A') );
    EXAM_CHECK_ASYNC( ct.is(ctype_base::lower, 'a') );
    EXAM_CHECK_ASYNC( ct.is(ctype_base::alpha, 'A') );
    EXAM_CHECK_ASYNC( ct.is(ctype_base::space, ' ') );
    EXAM_CHECK_ASYNC( !ct.is(ctype_base::space, '2') );
    EXAM_CHECK_ASYNC( ct.is(ctype_base::punct, '.') );
    EXAM_CHECK_ASYNC( ct.is(ctype_base::xdigit, 'a') );
  }

  //is range
  {
    char values[] = "0Aa .";
    ctype_base::mask res[sizeof(values)];
    ct.is(values, values + sizeof(values), res);
    // '0'
    EXAM_CHECK_ASYNC( (res[0] & ctype_base::print) != 0 );
    EXAM_CHECK_ASYNC( (res[0] & ctype_base::digit) != 0 );
    EXAM_CHECK_ASYNC( (res[0] & ctype_base::xdigit) != 0 );
    // 'A'
    EXAM_CHECK_ASYNC( (res[1] & ctype_base::print) != 0 );
    EXAM_CHECK_ASYNC( (res[1] & ctype_base::alpha) != 0 );
    EXAM_CHECK_ASYNC( (res[1] & ctype_base::xdigit) != 0 );
    EXAM_CHECK_ASYNC( (res[1] & ctype_base::upper) != 0 );
    // 'a'
    EXAM_CHECK_ASYNC( (res[2] & ctype_base::print) != 0 );
    EXAM_CHECK_ASYNC( (res[2] & ctype_base::alpha) != 0 );
    EXAM_CHECK_ASYNC( (res[2] & ctype_base::xdigit) != 0 );
    EXAM_CHECK_ASYNC( (res[2] & ctype_base::lower) != 0 );
    EXAM_CHECK_ASYNC( (res[2] & ctype_base::space) == 0 );
    // ' '
    EXAM_CHECK_ASYNC( (res[3] & ctype_base::print) != 0 );
    EXAM_CHECK_ASYNC( (res[3] & ctype_base::space) != 0 );
    EXAM_CHECK_ASYNC( (res[3] & ctype_base::digit) == 0 );
    // '.'
    EXAM_CHECK_ASYNC( (res[4] & ctype_base::print) != 0 );
    EXAM_CHECK_ASYNC( (res[4] & ctype_base::punct) != 0 );
    EXAM_CHECK_ASYNC( (res[4] & ctype_base::digit) == 0 );
  }

  //scan_is
  {
    char range[] = "abAc123 .";
    const char *rbeg = range;
    const char *rend = range + sizeof(range);

    const char *res;
    res = ct.scan_is((ctype_base::mask)(ctype_base::alpha | ctype_base::lower), rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == 'a' );

    res = ct.scan_is(ctype_base::upper, rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == 'A' );

    res = ct.scan_is(ctype_base::punct, rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == '.' );
  }

  //scan_not
  {
    char range[] = "abAc123 .";
    const char *rbeg = range;
    const char *rend = range + sizeof(range);

    const char *res;
    res = ct.scan_not((ctype_base::mask)(ctype_base::alpha | ctype_base::lower), rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == '1' );

    res = ct.scan_not(ctype_base::alpha, rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == '1' );

    res = ct.scan_not(ctype_base::punct, rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == 'a' );
  }

  //toupper
  {
    EXAM_CHECK_ASYNC( ct.toupper('a') == 'A' );
    EXAM_CHECK_ASYNC( ct.toupper('A') == 'A' );
    EXAM_CHECK_ASYNC( ct.toupper('1') == '1' );
  }

  //toupper range
  {
    char range[] = "abAc1";
    char expected_range[] = "ABAC1";
    ct.toupper(range, range + sizeof(range));
    EXAM_CHECK_ASYNC( equal(range, range + sizeof(range), expected_range) );
  }

  //tolower
  {
    EXAM_CHECK_ASYNC( ct.tolower('A') == 'a' );
    EXAM_CHECK_ASYNC( ct.tolower('a') == 'a' );
    EXAM_CHECK_ASYNC( ct.tolower('1') == '1' );
  }

  //tolower range
  {
    char range[] = "ABaC1";
    char expected_range[] = "abac1";
    ct.tolower(range, range + sizeof(range));
    EXAM_CHECK_ASYNC( equal(range, range + sizeof(range), expected_range) );
  }

  //widen
  {
    EXAM_CHECK_ASYNC( ct.widen('a') == 'a' );
  }

  //widen range
  {
    char range[] = "ABaC1";
    char res[sizeof(range)];
    ct.widen(range, range + sizeof(range), res);
    EXAM_CHECK_ASYNC( equal(range, range + sizeof(range), res) );
  }

  //narrow
  {
    EXAM_CHECK_ASYNC( ct.narrow('a', 'b') == 'a' );
  }

  //narrow range
  {
    char range[] = "ABaC1";
    char res[sizeof(range)];
    ct.narrow(range, range + sizeof(range), 'b', res);
    EXAM_CHECK_ASYNC( equal(range, range + sizeof(range), res) );
  }
}

void locale_test::_ctype_facet_w( const locale& loc )
{
# ifndef _STLP_NO_WCHAR_T
  EXAM_CHECK_ASYNC( has_facet<ctype<wchar_t> >(loc) );
  ctype<wchar_t> const& wct = use_facet<ctype<wchar_t> >(loc);
  //is
  {
    EXAM_CHECK_ASYNC( wct.is(ctype_base::digit, L'0') );
    EXAM_CHECK_ASYNC( wct.is(ctype_base::upper, L'A') );
    EXAM_CHECK_ASYNC( wct.is(ctype_base::lower, L'a') );
    EXAM_CHECK_ASYNC( wct.is(ctype_base::alpha, L'A') );
    EXAM_CHECK_ASYNC( wct.is(ctype_base::space, L' ') );
    EXAM_CHECK_ASYNC( !wct.is(ctype_base::space, L'2') );
    EXAM_CHECK_ASYNC( wct.is(ctype_base::punct, L'.') );
    EXAM_CHECK_ASYNC( wct.is(ctype_base::xdigit, L'a') );
  }

  //is range
  {
    wchar_t values[] = L"0Aa .";
    ctype_base::mask res[sizeof(values) / sizeof(wchar_t)];
    wct.is(values, values + (sizeof(values) / sizeof(wchar_t)), res);
    // '0'
    EXAM_CHECK_ASYNC( (res[0] & ctype_base::print) != 0 );
    EXAM_CHECK_ASYNC( (res[0] & ctype_base::digit) != 0 );
    EXAM_CHECK_ASYNC( (res[0] & ctype_base::xdigit) != 0 );
    // 'A'
    EXAM_CHECK_ASYNC( (res[1] & ctype_base::print) != 0 );
    EXAM_CHECK_ASYNC( (res[1] & ctype_base::alpha) != 0 );
    EXAM_CHECK_ASYNC( (res[1] & ctype_base::xdigit) != 0 );
    EXAM_CHECK_ASYNC( (res[1] & ctype_base::upper) != 0 );
    // 'a'
    EXAM_CHECK_ASYNC( (res[2] & ctype_base::print) != 0 );
    EXAM_CHECK_ASYNC( (res[2] & ctype_base::alpha) != 0 );
    EXAM_CHECK_ASYNC( (res[2] & ctype_base::xdigit) != 0 );
    EXAM_CHECK_ASYNC( (res[2] & ctype_base::lower) != 0 );
    EXAM_CHECK_ASYNC( (res[2] & ctype_base::space) == 0 );
    // ' '
    EXAM_CHECK_ASYNC( (res[3] & ctype_base::print) != 0 );
    EXAM_CHECK_ASYNC( (res[3] & ctype_base::space) != 0 );
    EXAM_CHECK_ASYNC( (res[3] & ctype_base::digit) == 0 );
    // '.'
    EXAM_CHECK_ASYNC( (res[4] & ctype_base::print) != 0 );
    EXAM_CHECK_ASYNC( (res[4] & ctype_base::punct) != 0 );
    EXAM_CHECK_ASYNC( (res[4] & ctype_base::digit) == 0 );
  }

  //scan_is
  {
    wchar_t range[] = L"abAc123 .";
    const wchar_t *rbeg = range;
    const wchar_t *rend = range + (sizeof(range) / sizeof(wchar_t));

    const wchar_t *res;
    res = wct.scan_is((ctype_base::mask)(ctype_base::alpha | ctype_base::lower), rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == L'a' );

    res = wct.scan_is(ctype_base::upper, rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == L'A' );

    res = wct.scan_is(ctype_base::punct, rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == L'.' );
  }

  //scan_not
  {
    wchar_t range[] = L"abAc123 .";
    const wchar_t *rbeg = range;
    const wchar_t *rend = range + (sizeof(range) / sizeof(wchar_t));

    const wchar_t *res;
    res = wct.scan_not((ctype_base::mask)(ctype_base::alpha | ctype_base::lower), rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == L'1' );

    res = wct.scan_not(ctype_base::alpha, rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == L'1' );

    res = wct.scan_not(ctype_base::punct, rbeg, rend);
    EXAM_CHECK_ASYNC( res != rend );
    EXAM_CHECK_ASYNC( *res == L'a' );
  }

  //toupper
  {
    EXAM_CHECK_ASYNC( wct.toupper(L'a') == L'A' );
    EXAM_CHECK_ASYNC( wct.toupper(L'A') == L'A' );
    EXAM_CHECK_ASYNC( wct.toupper(L'1') == L'1' );
  }

  //toupper range
  {
    wchar_t range[] = L"abAc1";
    wchar_t expected_range[] = L"ABAC1";
    wct.toupper(range, range + sizeof(range) / sizeof(wchar_t));
    EXAM_CHECK_ASYNC( equal(range, range + sizeof(range) / sizeof(wchar_t), expected_range) );
  }

  //tolower
  {
    EXAM_CHECK_ASYNC( wct.tolower(L'A') == L'a' );
    EXAM_CHECK_ASYNC( wct.tolower(L'a') == L'a' );
    EXAM_CHECK_ASYNC( wct.tolower(L'1') == L'1' );
  }

  //tolower range
  {
    wchar_t range[] = L"ABaC1";
    wchar_t expected_range[] = L"abac1";
    wct.tolower(range, range + sizeof(range) / sizeof(wchar_t));
    EXAM_CHECK_ASYNC( equal(range, range + sizeof(range) / sizeof(wchar_t), expected_range) );
  }

  //widen
  {
    EXAM_CHECK_ASYNC( wct.widen('a') == L'a' );
  }

  //widen range
  {
    char range[] = "ABaC1";
    wchar_t res[sizeof(range)];
    wchar_t expected_res[] = L"ABaC1";
    wct.widen(range, range + sizeof(range), res);
    EXAM_CHECK_ASYNC( equal(expected_res, expected_res + sizeof(range), res) );
  }

  //narrow
  {
    EXAM_CHECK_ASYNC( wct.narrow(L'a', 'b') == L'a' );
  }

  //narrow range
  {
    wchar_t range[] = L"ABaC1";
    char res[sizeof(range) / sizeof(wchar_t)];
    char expected_res[] = "ABaC1";
    wct.narrow(range, range + sizeof(range) / sizeof(wchar_t), 'b', res);
    EXAM_CHECK_ASYNC( equal(expected_res, expected_res + sizeof(range) / sizeof(wchar_t), res) );
  }
# endif
}

static void _ctype_test_supported_locale( locale_test& inst, _Test __test )
{
  size_t n = sizeof(tested_locales) / sizeof(tested_locales[0]);
  for (size_t i = 0; i < n; ++i) {
    locale loc;
    try
    {
      locale tmp(tested_locales[i]);
      loc = tmp;
    }
    catch (runtime_error const&) {
      //This locale is not supported.
      continue;
    }

    EXAM_MESSAGE_ASYNC( loc.name().c_str() );
    (inst.*__test)(loc);

    {
      locale tmp(locale::classic(), tested_locales[i], locale::ctype);
      loc = tmp;
    }
    (inst.*__test)(loc);

    {
      locale tmp(locale::classic(), new ctype_byname<char>(tested_locales[i]));
#ifndef _STLP_NO_WCHAR_T
      locale tmp0(tmp, new ctype_byname<wchar_t>(tested_locales[i]));
      tmp = tmp0;
#endif
      loc = tmp;
    }
    (inst.*__test)(loc);
  }
}

int EXAM_IMPL(locale_test::ctype_facet)
{
  _ctype_test_supported_locale(*this, &locale_test::_ctype_facet);
#ifndef _STLP_NO_WCHAR_T
  _ctype_test_supported_locale(*this, &locale_test::_ctype_facet_w);
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(locale_test::ctype_by_name)
{
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in
   * a runtime_error exception.
   */
#    if  defined (STLPORT) || (!defined(__GNUC__) && (!defined (_MSC_VER) || (_MSC_VER > 1400)))
   // libstdc++ call freelocate on bad locale
  try {
    locale loc(locale::classic(), new ctype_byname<char>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#    endif

  try {
    locale loc(locale::classic(), new ctype_byname<char>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new codecvt_byname<char, char, mbstate_t>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new codecvt_byname<char, char, mbstate_t>("yasli_language"));
    //STLport implementation do not care about name pass to this facet.
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new ctype_byname<char>("fr_FR"));
    EXAM_CHECK( has_facet<ctype<char> >(loc) );
    ctype<char> const& ct = use_facet<ctype<char> >(loc);
    EXAM_CHECK( ct.is(ctype_base::mask(ctype_base::print | ctype_base::lower | ctype_base::alpha), char(0xe7)) );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new ctype_byname<char>("C"));
    ctype<char> const& cfacet_byname = use_facet<ctype<char> >(loc);
    ctype<char> const& cfacet = use_facet<ctype<char> >(locale::classic());

    for (char c = 0;; ++c) {
      EXAM_CHECK(cfacet_byname.is(ctype_base::space, c) == cfacet.is(ctype_base::space, c));
      if (cfacet_byname.is(ctype_base::print, c) != cfacet.is(ctype_base::print, c))
      {
        EXAM_CHECK(cfacet_byname.is(ctype_base::print, c) == cfacet.is(ctype_base::print, c));
      }
      EXAM_CHECK(cfacet_byname.is(ctype_base::cntrl, c) == cfacet.is(ctype_base::cntrl, c));
      EXAM_CHECK(cfacet_byname.is(ctype_base::upper, c) == cfacet.is(ctype_base::upper, c));
      EXAM_CHECK(cfacet_byname.is(ctype_base::lower, c) == cfacet.is(ctype_base::lower, c));
      EXAM_CHECK(cfacet_byname.is(ctype_base::alpha, c) == cfacet.is(ctype_base::alpha, c));
      EXAM_CHECK(cfacet_byname.is(ctype_base::digit, c) == cfacet.is(ctype_base::digit, c));
      EXAM_CHECK(cfacet_byname.is(ctype_base::punct, c) == cfacet.is(ctype_base::punct, c));
      EXAM_CHECK(cfacet_byname.is(ctype_base::xdigit, c) == cfacet.is(ctype_base::xdigit, c));
      EXAM_CHECK(cfacet_byname.is(ctype_base::alnum, c) == cfacet.is(ctype_base::alnum, c));
      EXAM_CHECK(cfacet_byname.is(ctype_base::graph, c) == cfacet.is(ctype_base::graph, c));
      if (c == 127) break;
    }
  }
  catch (runtime_error const& /* e */) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

#if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  try {
    locale loc(locale::classic(), new ctype_byname<wchar_t>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new ctype_byname<wchar_t>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new codecvt_byname<wchar_t, char, mbstate_t>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new codecvt_byname<wchar_t, char, mbstate_t>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(locale_test::messages_by_name)
{
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in
   * a runtime_error exception.
   */
  try {
    locale loc(locale::classic(), new messages_byname<char>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new messages_byname<char>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  /*
  try {
    locale loc(locale::classic(), new messages_byname<char>(""));
    CPPUNIT_FAIL;
  }
  catch (runtime_error const& e) {
    CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_FAIL;
  }
  */

#    if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  try {
    locale loc(locale::classic(), new messages_byname<wchar_t>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new messages_byname<wchar_t>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#    endif

  return EXAM_RESULT;
}

struct ref_monetary
{
  const char *name;
  const char *money_int_prefix;
  const char *money_int_prefix_old;
  const char *money_prefix;
  const char *money_suffix;
  const char *money_decimal_point;
  const char *money_thousands_sep;
};

static const ref_monetary monetary_tested_locales[] = {
//{  name,         money_int_prefix, money_int_prefix_old, money_prefix, money_suffix, money_decimal_point, money_thousands_sep},
  { "fr_FR",       "EUR ",           "FRF ",               "",           "",           ",",
#    if defined (WIN32) || defined (_WIN32)
                                                                                                            "\xa0" },
#    else
                                                                                                            " " },
#    endif
  { "ru_RU.koi8r", "RUB ",           "RUR ",               "",           "\xd2\xd5\xc2", ".",               " " },
  { "en_GB",       "GBP ",           "",                   "\xa3",       "",           ".",                 "," },
  { "en_US",       "USD ",           "",                   "$",          "",           ".",                 "," },
  { "C",           "",               "",                   "",           "",           " ",                 " " },
};


const ref_monetary* locale_test::_get_ref_monetary(size_t i)
{
  if (i < sizeof(monetary_tested_locales) / sizeof(monetary_tested_locales[0])) {
    return monetary_tested_locales + i;
  }
  return 0;
}

const char* locale_test::_get_ref_monetary_name(const ref_monetary* _ref)
{
  return _ref->name;
}

void locale_test::_money_put_get( const locale& loc, const ref_monetary* rl )
{
  _money_put_get2(loc, loc, rl);
}

void locale_test::_money_put_get2( const locale& loc, const locale& streamLoc, const ref_monetary* prl )
{
  const ref_monetary &rl = *prl;
  EXAM_CHECK_ASYNC( has_facet<money_put<char> >(loc) );
  money_put<char> const& fmp = use_facet<money_put<char> >(loc);
  EXAM_CHECK_ASYNC( has_facet<money_get<char> >(loc) );
  money_get<char> const& fmg = use_facet<money_get<char> >(loc);

  ostringstream ostr;
  ostr.imbue(streamLoc);
  ostr << showbase;

  //Check a positive value (international format)
  {
    string str_res;
    //money_put
    {
      EXAM_CHECK_ASYNC( (has_facet<moneypunct<char, true> >(loc)) );
      moneypunct<char, true> const& intl_fmp = use_facet<moneypunct<char, true> >(loc);

      ostreambuf_iterator<char, char_traits<char> > res = fmp.put(ostr, true, ostr, ' ', 123456);

      EXAM_CHECK_ASYNC( !res.failed() );
      str_res = ostr.str();
      //EXAM_MESSAGE(str_res.c_str());

      size_t fieldIndex = 0;
      size_t index = 0;

      //On a positive value we skip the sign field if exists:
      if (intl_fmp.pos_format().field[fieldIndex] == money_base::sign) {
        ++fieldIndex;
      }
      // international currency abbreviation, if it is before value

      /*
       * int_curr_symbol
       *
       *   The international currency symbol. The operand is a four-character
       *   string, with the first three characters containing the alphabetic
       *   international currency symbol in accordance with those specified
       *   in the ISO 4217 specification. The fourth character is the character used
       *   to separate the international currency symbol from the monetary quantity.
       *
       * (http://www.opengroup.org/onlinepubs/7990989775/xbd/locale.html)
       */
      string::size_type p = strlen( rl.money_int_prefix );
      if (p != 0) {
        EXAM_CHECK_ASYNC( intl_fmp.pos_format().field[fieldIndex] == money_base::symbol );
        string::size_type p_old = strlen( rl.money_int_prefix_old );
        EXAM_CHECK_ASYNC( (str_res.substr(index, p) == rl.money_int_prefix) ||
                        ((p_old != 0) &&
                         (str_res.substr(index, p_old) == rl.money_int_prefix_old)) );
        if ( str_res.substr(index, p) == rl.money_int_prefix ) {
          index += p;
        } else {
          index += p_old;
        }
        ++fieldIndex;
      }

      // space after currency
      if (intl_fmp.pos_format().field[fieldIndex] == money_base::space ||
          intl_fmp.pos_format().field[fieldIndex] == money_base::none) {
        // iternational currency symobol has four chars, one of these chars
        // is separator, so if format has space on this place, it should
        // be skipped.
        ++fieldIndex;
      }

      // sign
      if (intl_fmp.pos_format().field[fieldIndex] == money_base::sign) {
        ++fieldIndex;
      }

      // value
      EXAM_CHECK_ASYNC( str_res[index++] == '1' );
      if (!intl_fmp.grouping().empty()) {
        EXAM_CHECK_ASYNC( str_res[index++] == /* intl_fmp.thousands_sep() */ *rl.money_thousands_sep );
      }
      EXAM_CHECK_ASYNC( str_res[index++] == '2' );
      EXAM_CHECK_ASYNC( str_res[index++] == '3' );
      EXAM_CHECK_ASYNC( str_res[index++] == '4' );
      if (intl_fmp.frac_digits() != 0) {
        EXAM_CHECK_ASYNC( str_res[index++] == /* intl_fmp.decimal_point() */ *rl.money_decimal_point );
      }
      EXAM_CHECK_ASYNC( str_res[index++] == '5' );
      EXAM_CHECK_ASYNC( str_res[index++] == '6' );
      ++fieldIndex;

      // sign
      if (intl_fmp.pos_format().field[fieldIndex] == money_base::sign) {
        ++fieldIndex;
      }

      // space
      if (intl_fmp.pos_format().field[fieldIndex] == money_base::space ) {
        EXAM_CHECK_ASYNC( str_res[index++] == ' ' );
        ++fieldIndex;
      }

      // sign
      if (intl_fmp.pos_format().field[fieldIndex] == money_base::sign) {
        ++fieldIndex;
      }

      //as space cannot be last the only left format can be none:
      while ( fieldIndex < 3 ) {
        EXAM_CHECK_ASYNC( intl_fmp.pos_format().field[fieldIndex] == money_base::none );
        ++fieldIndex;
      }
    }

    //money_get
    {
      ios_base::iostate err = ios_base::goodbit;
      string digits;

      istringstream istr(str_res);
      ostr.str( "" );
      ostr.clear();
      fmg.get(istr, istreambuf_iterator<char, char_traits<char> >(), true, ostr, err, digits);
      EXAM_CHECK_ASYNC( (err & (ios_base::failbit | ios_base::badbit)) == 0 );
      EXAM_CHECK_ASYNC( digits == "123456" );
    }
  }

  ostr.str("");
  //Check a negative value (national format)
  {
    EXAM_CHECK_ASYNC( (has_facet<moneypunct<char, false> >(loc)) );
    moneypunct<char, false> const& dom_fmp = use_facet<moneypunct<char, false> >(loc);
    string str_res;
    //Check money_put
    {
      ostreambuf_iterator<char, char_traits<char> > res = fmp.put(ostr, false, ostr, ' ', -123456);

      EXAM_CHECK_ASYNC( !res.failed() );
      str_res = ostr.str();
      //CPPUNIT_MESSAGE(str_res.c_str());

      size_t fieldIndex = 0;
      size_t index = 0;

      if (dom_fmp.neg_format().field[fieldIndex] == money_base::sign) {
        EXAM_CHECK_ASYNC( str_res.substr(index, dom_fmp.negative_sign().size()) == dom_fmp.negative_sign() );
        index += dom_fmp.negative_sign().size();
        ++fieldIndex;
      }

      string::size_type p = strlen( rl.money_prefix );
      if (p != 0) {
        EXAM_CHECK_ASYNC( str_res.substr(index, p) == rl.money_prefix );
        index += p;
        ++fieldIndex;
      }
      if (dom_fmp.neg_format().field[fieldIndex] == money_base::space ||
          dom_fmp.neg_format().field[fieldIndex] == money_base::none) {
        EXAM_CHECK_ASYNC( str_res[index++] == ' ' );
        ++fieldIndex;
      }

      EXAM_CHECK_ASYNC( str_res[index++] == '1' );
      if (!dom_fmp.grouping().empty()) {
        EXAM_CHECK_ASYNC( str_res[index++] == dom_fmp.thousands_sep() );
      }
      EXAM_CHECK_ASYNC( str_res[index++] == '2' );
      EXAM_CHECK_ASYNC( str_res[index++] == '3' );
      EXAM_CHECK_ASYNC( str_res[index++] == '4' );
      if (dom_fmp.frac_digits() != 0) {
        EXAM_CHECK_ASYNC( str_res[index++] == dom_fmp.decimal_point() );
      }
      EXAM_CHECK_ASYNC( str_res[index++] == '5' );
      EXAM_CHECK_ASYNC( str_res[index++] == '6' );
      ++fieldIndex;

      //space cannot be last:
      if ((fieldIndex < 3) &&
          dom_fmp.neg_format().field[fieldIndex] == money_base::space) {
        EXAM_CHECK_ASYNC( str_res[index++] == ' ' );
        ++fieldIndex;
      }

      if (fieldIndex == 3) {
        //If none is last we should not add anything to the resulting string:
        if (dom_fmp.neg_format().field[fieldIndex] == money_base::none) {
          EXAM_CHECK_ASYNC( index == str_res.size() );
        } else {
          EXAM_CHECK_ASYNC( dom_fmp.neg_format().field[fieldIndex] == money_base::symbol );
          EXAM_CHECK_ASYNC( str_res.substr(index, strlen(rl.money_suffix)) == rl.money_suffix );
        }
      }
    }

    //money_get
    {
      ios_base::iostate err = ios_base::goodbit;
#  if defined (STLPORT)
      _STLP_LONGEST_FLOAT_TYPE val;
#  else
      long double val;
#  endif

      istringstream istr(str_res);
      fmg.get(istr, istreambuf_iterator<char, char_traits<char> >(), false, ostr, err, val);
      EXAM_CHECK_ASYNC( (err & (ios_base::failbit | ios_base::badbit)) == 0 );
      if (dom_fmp.negative_sign().empty()) {
        //Without negative sign there is no way to guess the resulting amount sign ("C" locale):
        EXAM_CHECK_ASYNC( val == 123456 );
      }
      else {
        EXAM_CHECK_ASYNC( val == -123456 );
      }
    }
  }
}


// Test for bug in case when number of digits in value less then number
// of digits in fraction. I.e. '9' should be printed as '0.09',
// if x.frac_digits() == 2.

void locale_test::_money_put_X_bug( const locale& loc, const ref_monetary* prl )
{
  const ref_monetary &rl = *prl;
  EXAM_CHECK_ASYNC( has_facet<money_put<char> >(loc) );
  money_put<char> const& fmp = use_facet<money_put<char> >(loc);

  ostringstream ostr;
  ostr.imbue(loc);
  ostr << showbase;

  // ostr.str("");
  // Check value with one decimal digit:
  {
    EXAM_CHECK_ASYNC( (has_facet<moneypunct<char, false> >(loc)) );
    moneypunct<char, false> const& dom_fmp = use_facet<moneypunct<char, false> >(loc);
    string str_res;
    // Check money_put
    {
      ostreambuf_iterator<char, char_traits<char> > res = fmp.put(ostr, false, ostr, ' ', 9);

      EXAM_CHECK_ASYNC( !res.failed() );
      str_res = ostr.str();

      size_t fieldIndex = 0;
      size_t index = 0;

      if (dom_fmp.pos_format().field[fieldIndex] == money_base::sign) {
        EXAM_CHECK_ASYNC( str_res.substr(index, dom_fmp.positive_sign().size()) == dom_fmp.positive_sign() );
        index += dom_fmp.positive_sign().size();
        ++fieldIndex;
      }

      string::size_type p = strlen( rl.money_prefix );
      if (p != 0) {
        EXAM_CHECK_ASYNC( str_res.substr(index, p) == rl.money_prefix );
        index += p;
        ++fieldIndex;
      }
      if (dom_fmp.neg_format().field[fieldIndex] == money_base::space ||
          dom_fmp.neg_format().field[fieldIndex] == money_base::none) {
        EXAM_CHECK_ASYNC( str_res[index++] == ' ' );
        ++fieldIndex;
      }
      if (dom_fmp.frac_digits() != 0) {
        EXAM_CHECK_ASYNC( str_res[index++] == '0' );
        EXAM_CHECK_ASYNC( str_res[index++] == dom_fmp.decimal_point() );
        for ( int fd = 1; fd < dom_fmp.frac_digits(); ++fd ) {
          EXAM_CHECK_ASYNC( str_res[index++] == '0' );
        }
      }
      EXAM_CHECK_ASYNC( str_res[index++] == '9' );
      ++fieldIndex;

      //space cannot be last:
      if ((fieldIndex < 3) &&
          dom_fmp.neg_format().field[fieldIndex] == money_base::space) {
        EXAM_CHECK_ASYNC( str_res[index++] == ' ' );
        ++fieldIndex;
      }

      if (fieldIndex == 3) {
        //If none is last we should not add anything to the resulting string:
        if (dom_fmp.neg_format().field[fieldIndex] == money_base::none) {
          EXAM_CHECK_ASYNC( index == str_res.size() );
        } else {
          EXAM_CHECK_ASYNC( dom_fmp.neg_format().field[fieldIndex] == money_base::symbol );
          EXAM_CHECK_ASYNC( str_res.substr(index, strlen(rl.money_suffix)) == rl.money_suffix );
        }
      }
    }
  }

  ostr.str("");
  // Check value with two decimal digit:
  {
    EXAM_CHECK_ASYNC( (has_facet<moneypunct<char, false> >(loc)) );
    moneypunct<char, false> const& dom_fmp = use_facet<moneypunct<char, false> >(loc);
    string str_res;
    // Check money_put
    {
      ostreambuf_iterator<char, char_traits<char> > res = fmp.put(ostr, false, ostr, ' ', 90);

      EXAM_CHECK_ASYNC( !res.failed() );
      str_res = ostr.str();

      size_t fieldIndex = 0;
      size_t index = 0;

      if (dom_fmp.pos_format().field[fieldIndex] == money_base::sign) {
        EXAM_CHECK_ASYNC( str_res.substr(index, dom_fmp.positive_sign().size()) == dom_fmp.positive_sign() );
        index += dom_fmp.positive_sign().size();
        ++fieldIndex;
      }

      string::size_type p = strlen( rl.money_prefix );
      if (p != 0) {
        EXAM_CHECK_ASYNC( str_res.substr(index, p) == rl.money_prefix );
        index += p;
        ++fieldIndex;
      }
      if (dom_fmp.neg_format().field[fieldIndex] == money_base::space ||
          dom_fmp.neg_format().field[fieldIndex] == money_base::none) {
        EXAM_CHECK_ASYNC( str_res[index++] == ' ' );
        ++fieldIndex;
      }
      if (dom_fmp.frac_digits() != 0) {
        EXAM_CHECK_ASYNC( str_res[index++] == '0' );
        EXAM_CHECK_ASYNC( str_res[index++] == dom_fmp.decimal_point() );
        for ( int fd = 1; fd < dom_fmp.frac_digits() - 1; ++fd ) {
          EXAM_CHECK_ASYNC( str_res[index++] == '0' );
        }
      }
      EXAM_CHECK_ASYNC( str_res[index++] == '9' );
      if (dom_fmp.frac_digits() != 0) {
        EXAM_CHECK_ASYNC( str_res[index++] == '0' );
      }
      ++fieldIndex;

      //space cannot be last:
      if ((fieldIndex < 3) &&
          dom_fmp.neg_format().field[fieldIndex] == money_base::space) {
        EXAM_CHECK_ASYNC( str_res[index++] == ' ' );
        ++fieldIndex;
      }

      if (fieldIndex == 3) {
        //If none is last we should not add anything to the resulting string:
        if (dom_fmp.neg_format().field[fieldIndex] == money_base::none) {
          EXAM_CHECK_ASYNC( index == str_res.size() );
        } else {
          EXAM_CHECK_ASYNC( dom_fmp.neg_format().field[fieldIndex] == money_base::symbol );
          EXAM_CHECK_ASYNC( str_res.substr(index, strlen(rl.money_suffix)) == rl.money_suffix );
        }
      }
    }
  }
}

typedef void (locale_test::*_MTest) ( const locale&, const ref_monetary* );

static void _monetary_test_supported_locale( locale_test& inst, _MTest __test)
{
  size_t n = sizeof(monetary_tested_locales) / sizeof(monetary_tested_locales[0]);
  for (size_t i = 0; i < n; ++i) {
    locale loc;
    try {
      locale tmp(monetary_tested_locales[i].name);
      loc = tmp;
    }
    catch (runtime_error const&) {
      //This locale is not supported.
      continue;
    }
    EXAM_MESSAGE_ASYNC( loc.name().c_str() );
    (inst.*__test)(loc, monetary_tested_locales + i);

    {
      locale tmp(locale::classic(), monetary_tested_locales[i].name, locale::monetary);
      loc = tmp;
    }
    (inst.*__test)(loc, monetary_tested_locales + i);

    {
      locale tmp0(locale::classic(), new moneypunct_byname<char, true>(monetary_tested_locales[i].name));
      locale tmp1(tmp0, new moneypunct_byname<char, false>(monetary_tested_locales[i].name));
      loc = tmp1;
    }
    (inst.*__test)(loc, monetary_tested_locales + i);
  }
}

int EXAM_IMPL(locale_test::money_put_get)
{
  _monetary_test_supported_locale( *this, &locale_test::_money_put_get );
  return EXAM_RESULT;
}

int EXAM_IMPL(locale_test::money_put_X_bug)
{
  _monetary_test_supported_locale( *this, &locale_test::_money_put_X_bug );
  return EXAM_RESULT;
}

int EXAM_IMPL(locale_test::moneypunct_by_name)
{
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in
   * a runtime_error exception.
   */
#    if defined (STLPORT) || !defined (__GNUC__)
  try {
    locale loc(locale::classic(), new moneypunct_byname<char, true>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#    endif

  try {
    locale loc(locale::classic(), new moneypunct_byname<char, true>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    string veryLongFacetName("LC_MONETARY=");
    veryLongFacetName.append(512, '?');
    locale loc(locale::classic(), new moneypunct_byname<char, true>(veryLongFacetName.c_str()));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

#    if defined (STLPORT) || !defined (__GNUC__)
  try {
    locale loc(locale::classic(), new moneypunct_byname<char, false>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#    endif

  try {
    locale loc(locale::classic(), new moneypunct_byname<char, false>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    string veryLongFacetName("LC_MONETARY=");
    veryLongFacetName.append(512, '?');
    locale loc(locale::classic(), new moneypunct_byname<char, false>(veryLongFacetName.c_str()));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new moneypunct_byname<char, false>("C"));
    moneypunct<char, false> const& cfacet_byname = use_facet<moneypunct<char, false> >(loc);
    moneypunct<char, false> const& cfacet = use_facet<moneypunct<char, false> >(locale::classic());

    money_base::pattern cp = cfacet.pos_format();
    money_base::pattern cp_bn = cfacet_byname.pos_format();
    EXAM_CHECK( cp_bn.field[0] == cp.field[0] );
    EXAM_CHECK( cp_bn.field[1] == cp.field[1] );
    EXAM_CHECK( cp_bn.field[2] == cp.field[2] );
    EXAM_CHECK( cp_bn.field[3] == cp.field[3] );

    EXAM_CHECK( cfacet_byname.frac_digits() == cfacet.frac_digits() );
    if (cfacet_byname.frac_digits() != 0) {
      EXAM_CHECK( cfacet_byname.decimal_point() == cfacet.decimal_point() );
    }
    EXAM_CHECK( cfacet_byname.grouping() == cfacet.grouping() );
    if (!cfacet_byname.grouping().empty()) {
      EXAM_CHECK( cfacet_byname.thousands_sep() == cfacet.thousands_sep() );
    }
    EXAM_CHECK( cfacet_byname.positive_sign() == cfacet.positive_sign() );
    EXAM_CHECK( cfacet_byname.negative_sign() == cfacet.negative_sign() );
  }
  catch (runtime_error const& /* e */) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

  try {
    locale loc(locale::classic(), new moneypunct_byname<char, true>("C"));
    moneypunct<char, true> const& cfacet_byname = use_facet<moneypunct<char, true> >(loc);
    moneypunct<char, true> const& cfacet = use_facet<moneypunct<char, true> >(locale::classic());

    money_base::pattern cp = cfacet.pos_format();
    money_base::pattern cp_bn = cfacet_byname.pos_format();
    EXAM_CHECK( cp_bn.field[0] == cp.field[0] );
    EXAM_CHECK( cp_bn.field[1] == cp.field[1] );
    EXAM_CHECK( cp_bn.field[2] == cp.field[2] );
    EXAM_CHECK( cp_bn.field[3] == cp.field[3] );

    EXAM_CHECK( cfacet_byname.frac_digits() == cfacet.frac_digits() );
    if ( cfacet_byname.frac_digits() != 0 ) {
      EXAM_CHECK( cfacet_byname.decimal_point() == cfacet.decimal_point() );
    }
    EXAM_CHECK( cfacet_byname.grouping() == cfacet.grouping() );
    if ( !cfacet_byname.grouping().empty() ) {
      EXAM_CHECK( cfacet_byname.thousands_sep() == cfacet.thousands_sep() );
    }
    EXAM_CHECK( cfacet_byname.positive_sign() == cfacet.positive_sign() );
    EXAM_CHECK( cfacet_byname.negative_sign() == cfacet.negative_sign() );
  }
  catch (runtime_error const& /* e */) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

  try {
    // On platform without real localization support we should rely on the "C" locale facet.
    locale loc(locale::classic(), new moneypunct_byname<char, false>(""));
  }
  catch (runtime_error const& /* e */) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

#    if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
#      if defined (STLPORT) || !defined (__GNUC__)
  try {
    locale loc(locale::classic(), new moneypunct_byname<wchar_t, true>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#      endif

  try {
    locale loc(locale::classic(), new moneypunct_byname<wchar_t, true>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

#      if defined (STLPORT) || !defined (__GNUC__)
  try {
    locale loc(locale::classic(), new moneypunct_byname<wchar_t, false>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#      endif

  try {
    locale loc(locale::classic(), new moneypunct_byname<wchar_t, false>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#    endif

  return EXAM_RESULT;
}

#include "complete_digits.h"

struct ref_locale {
  const char *name;
  const char *decimal_point;
  const char *thousands_sep;
};

static const ref_locale num_tested_locales[] = {
//{  name,         decimal_point, thousands_sepy_thousands_sep},
  { "fr_FR",       ",",           "\xa0"},
  { "ru_RU.koi8r", ",",           "."},
  { "en_GB",       ".",           ","},
  { "en_US",       ".",           ","},
  { "C",           ".",           ","},
};

void locale_test::_num_put_get( const locale& loc, const ref_locale* prl )
{
  const ref_locale& rl = *prl;
  EXAM_CHECK_ASYNC( has_facet<numpunct<char> >(loc) );
  numpunct<char> const& npct = use_facet<numpunct<char> >(loc);
  EXAM_CHECK_ASYNC( npct.decimal_point() == *rl.decimal_point );

  float val = 1234.56f;
  ostringstream fostr;
  fostr.imbue(loc);
  fostr << val;

  string ref = "1";
  if (!npct.grouping().empty()) {
    ref += npct.thousands_sep();
  }
  ref += "234";
  ref += npct.decimal_point();
  ref += "56";
  //cout << "In " << loc.name() << " 1234.56 is written: " << fostr.str() << endl;
  EXAM_CHECK_ASYNC( fostr.str() == ref );

  val = 12345678.9f;
  ref = "1";
  ref += npct.decimal_point();
  ref += "23457e+";
  string digits = "7";
  complete_digits(digits);
  ref += digits;
  fostr.str("");
  fostr << val;
  EXAM_CHECK_ASYNC( fostr.str() == ref );

  val = 1000000000.0f;
  fostr.str("");
  fostr << val;
  digits = "9";
  complete_digits(digits);
  EXAM_CHECK_ASYNC( fostr.str() == string("1e+") + digits );

  val = 1234.0f;
  ref = "1";
  if (!npct.grouping().empty()) {
    ref += npct.thousands_sep();
  }
  ref += "234";
  fostr.str("");
  fostr << val;
  EXAM_CHECK_ASYNC( fostr.str() == ref );

  val = 10000001.0f;
  fostr.str("");
  fostr << val;
  digits = "7";
  complete_digits(digits);
  EXAM_CHECK_ASYNC( fostr.str() == string("1e+") + digits );

  if (npct.grouping().size() == 1 && npct.grouping()[0] == 3) {
    int ival = 1234567890;
    fostr.str("");
    fostr << ival;
    ref = "1";
    ref += npct.thousands_sep();
    ref += "234";
    ref += npct.thousands_sep();
    ref += "567";
    ref += npct.thousands_sep();
    ref += "890";
    EXAM_CHECK_ASYNC( fostr.str() == ref );
  }

#if defined (__BORLANDC__)
  num_put<char> const& nput = use_facet<num_put<char> >(loc);
  typedef numeric_limits<double> limd;
  fostr.setf(ios_base::uppercase | ios_base::showpos);

  if (limd::has_infinity) {
    double infinity = limd::infinity();
    fostr.str("");
    nput.put(fostr, fostr, ' ', infinity);
    EXAM_CHECK_ASYNC( fostr.str() == string("+Inf") );
  }

  if (limd::has_quiet_NaN) {
    /* Ignore FPU exceptions */
    unsigned int _float_control_word = _control87(0, 0);
    _control87(EM_INVALID|EM_INEXACT, MCW_EM);
    double qnan = limd::quiet_NaN();
    /* Reset floating point control word */
    _clear87();
    _control87(_float_control_word, MCW_EM);
    fostr.str("");
    nput.put(fostr, fostr, ' ', qnan);
    EXAM_CHECK_ASYNC( fostr.str() == string("+NaN") );
  }
#endif
}

typedef void (locale_test::*_NTest) (const locale&, const ref_locale*);

static void num_test_supported_locale( locale_test& inst, _NTest __test )
{
  size_t n = sizeof(num_tested_locales) / sizeof(num_tested_locales[0]);
  for (size_t i = 0; i < n; ++i) {
    locale loc;
    try {
      locale tmp(num_tested_locales[i].name);
      loc = tmp;
    }
    catch (runtime_error const&) {
      //This locale is not supported.
      continue;
    }
    EXAM_MESSAGE_ASYNC( loc.name().c_str() );
    (inst.*__test)(loc, num_tested_locales + i);

    {
      locale tmp(locale::classic(), num_tested_locales[i].name, locale::numeric);
      loc = tmp;
    }
    (inst.*__test)(loc, num_tested_locales + i);

    {
      locale tmp(locale::classic(), new numpunct_byname<char>(num_tested_locales[i].name));
      loc = tmp;
    }
    (inst.*__test)(loc, num_tested_locales + i);
  }
}

int EXAM_IMPL(locale_test::num_put_get)
{
  num_test_supported_locale(*this, &locale_test::_num_put_get);
  return EXAM_RESULT;
}

int EXAM_IMPL(locale_test::numpunct_by_name)
{
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in
   * a runtime_error exception.
   */
#    if defined (STLPORT) || !defined (__GNUC__)
  try {
    locale loc(locale::classic(), new numpunct_byname<char>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#    endif

  try {
    locale loc(locale::classic(), new numpunct_byname<char>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    string veryLongFacetName("LC_NUMERIC=");
    veryLongFacetName.append(512, '?');
    locale loc(locale::classic(), new numpunct_byname<char>(veryLongFacetName.c_str()));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), "C", locale::numeric);
  }
  catch (runtime_error const& e) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

  try {
    // On platform without real localization support we should rely on the "C" facet.
    locale loc(locale::classic(), "", locale::numeric);
  }
  catch (runtime_error const& e) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

  try {
    locale loc(locale::classic(), new numpunct_byname<char>("C"));
    numpunct<char> const& cfacet_byname = use_facet<numpunct<char> >(loc);
    numpunct<char> const& cfacet = use_facet<numpunct<char> >(locale::classic());

    EXAM_CHECK( cfacet_byname.decimal_point() == cfacet.decimal_point() );
    EXAM_CHECK( cfacet_byname.grouping() == cfacet.grouping() );
    if (!cfacet.grouping().empty()) {
      EXAM_CHECK( cfacet_byname.thousands_sep() == cfacet.thousands_sep() );
    }
#    if !defined (STLPORT) || !defined (__GLIBC__)
    EXAM_CHECK( cfacet_byname.truename() == cfacet.truename() );
    EXAM_CHECK( cfacet_byname.falsename() == cfacet.falsename() );
#    endif
  }
  catch (runtime_error const& /* e */) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

  try {
    // On platform without real localization support we should rely on the "C" locale facet.
    locale loc(locale::classic(), new numpunct_byname<char>(""));
  }
  catch (runtime_error const& e) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

#    if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
#      if defined (STLPORT) || !defined (__GNUC__)
  try {
    locale loc(locale::classic(), new numpunct_byname<wchar_t>(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#      endif

  try {
    locale loc(locale::classic(), new numpunct_byname<wchar_t>("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#    endif

  return EXAM_RESULT;
}

void locale_test::_time_put_get( const locale& loc )
{
  {
    typedef time_put<char, ostreambuf_iterator<char, char_traits<char> > > time_put_facet;
    EXAM_CHECK_ASYNC( has_facet<time_put_facet>(loc) );
    const time_put_facet& tmp = use_facet<time_put_facet>(loc);

    struct tm xmas = { 0, 0, 12, 25, 11, 93 };
    ostringstream ostr;
    ostr.imbue(loc);
    string format = "%B %d %Y";

    time_put_facet::iter_type ret = tmp.put(ostr, ostr, ' ', &xmas, format.data(), format.data() + format.size());
    EXAM_CHECK_ASYNC( !ret.failed() );

    /*
     * In other words, user conformation is required for reliable parsing
     * of user-entered dates and times, but machine-generated formats can be
     * parsed reliably. This allows parsers to be aggressive about interpreting
     * user variations on standard format.
     *
     *                                             ISO/IEC 14882, 22.2.5.1
     */
    typedef time_get<char, istreambuf_iterator<char, char_traits<char> > > time_get_facet;
    EXAM_CHECK_ASYNC( has_facet<time_get_facet>(loc) );
    const time_get_facet& tmg = use_facet<time_get_facet>(loc);
    basic_ios<char> io(0);
    io.imbue(loc);

    istringstream istr( ostr.str() );
    istreambuf_iterator<char, char_traits<char> > i( istr );
    istreambuf_iterator<char, char_traits<char> > e;
    ios_base::iostate err = ios_base::goodbit;
    struct tm other = { 15, 20, 9, 14, 7, 105 };

    i = tmg.get_monthname( i, e, io, err, &other );
    EXAM_CHECK_ASYNC( err == ios_base::goodbit );
    EXAM_CHECK_ASYNC( other.tm_mon == xmas.tm_mon );

    ++i; ++i; ++i; ++i; // skip day of month and spaces around it
    i = tmg.get_year( i, e, io, err, &other );

    EXAM_CHECK_ASYNC( err == ios_base::eofbit );
    EXAM_CHECK_ASYNC( other.tm_year == xmas.tm_year );

    ostringstream ostrX;
    ostrX.imbue(loc);
    format = "%x %X";

    ret = tmp.put(ostrX, ostrX, ' ', &xmas, format.data(), format.data() + format.size());
    EXAM_CHECK_ASYNC( !ret.failed() );

    istringstream istrX( ostrX.str() );
    istreambuf_iterator<char, char_traits<char> > j( istrX );

    err = ios_base::goodbit;

    struct tm yet_more = { 15, 20, 9, 14, 7, 105 };

    j = tmg.get_date( j, e, io, err, &yet_more );

    EXAM_CHECK_ASYNC( err == ios_base::goodbit );

    EXAM_CHECK_ASYNC( yet_more.tm_sec != xmas.tm_sec );
    EXAM_CHECK_ASYNC( yet_more.tm_min != xmas.tm_min );
    EXAM_CHECK_ASYNC( yet_more.tm_hour != xmas.tm_hour );
    EXAM_CHECK_ASYNC( yet_more.tm_mday == xmas.tm_mday );
    EXAM_CHECK_ASYNC( yet_more.tm_mon == xmas.tm_mon );
    EXAM_CHECK_ASYNC( yet_more.tm_year == xmas.tm_year );

    ++j; // skip space

    j = tmg.get_time( j, e, io, err, &yet_more );

    EXAM_CHECK_ASYNC( err == ios_base::eofbit || err == ios_base::goodbit );

    EXAM_CHECK_ASYNC( yet_more.tm_sec == xmas.tm_sec );
    EXAM_CHECK_ASYNC( yet_more.tm_min == xmas.tm_min );
    EXAM_CHECK_ASYNC( yet_more.tm_hour == xmas.tm_hour );
    EXAM_CHECK_ASYNC( yet_more.tm_mday == xmas.tm_mday );
    EXAM_CHECK_ASYNC( yet_more.tm_mon == xmas.tm_mon );
    EXAM_CHECK_ASYNC( yet_more.tm_year == xmas.tm_year );
  }
#  if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  {
    typedef time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > time_put_facet;
    EXAM_CHECK_ASYNC( has_facet<time_put_facet>(loc) );
    const time_put_facet& tmp = use_facet<time_put_facet>(loc);

    struct tm xmas = { 0, 0, 12, 25, 11, 93 };
    wostringstream ostr;
    ostr.imbue(loc);
    wstring format = L"%B %d %Y";

    time_put_facet::iter_type ret = tmp.put(ostr, ostr, ' ', &xmas, format.data(), format.data() + format.size());
    EXAM_CHECK_ASYNC( !ret.failed() );

    /*
     * In other words, user conformation is required for reliable parsing
     * of user-entered dates and times, but machine-generated formats can be
     * parsed reliably. This allows parsers to be aggressive about interpreting
     * user variations on standard format.
     *
     *                                             ISO/IEC 14882, 22.2.5.1
     */
    typedef time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > > time_get_facet;
    EXAM_CHECK_ASYNC( has_facet<time_get_facet>(loc) );
    const time_get_facet& tmg = use_facet<time_get_facet>(loc);
    // Intentional instantiation with char to show a bug in a previous STLport version.
    basic_ios<char> io(0);
    io.imbue(loc);

    wistringstream istr( ostr.str() );
    istreambuf_iterator<wchar_t, char_traits<wchar_t> > i( istr );
    istreambuf_iterator<wchar_t, char_traits<wchar_t> > e;
    ios_base::iostate err = ios_base::goodbit;
    struct tm other = { 15, 20, 9, 14, 7, 105 };

    i = tmg.get_monthname( i, e, io, err, &other );
    EXAM_CHECK_ASYNC( err == ios_base::goodbit );
    EXAM_CHECK_ASYNC( other.tm_mon == xmas.tm_mon );

    ++i; ++i; ++i; ++i; // skip day of month and spaces around it
    i = tmg.get_year( i, e, io, err, &other );

    EXAM_CHECK_ASYNC( err == ios_base::eofbit );
    EXAM_CHECK_ASYNC( other.tm_year == xmas.tm_year );

    wostringstream ostrX;
    ostrX.imbue(loc);
    format = L"%x %X";

    ret = tmp.put(ostrX, ostrX, ' ', &xmas, format.data(), format.data() + format.size());
    EXAM_CHECK_ASYNC( !ret.failed() );

    wistringstream istrX( ostrX.str() );
    istreambuf_iterator<wchar_t, char_traits<wchar_t> > j( istrX );

    err = ios_base::goodbit;

    struct tm yet_more = { 15, 20, 9, 14, 7, 105 };

    j = tmg.get_date( j, e, io, err, &yet_more );

    EXAM_CHECK_ASYNC( err == ios_base::goodbit );

    EXAM_CHECK_ASYNC( yet_more.tm_sec != xmas.tm_sec );
    EXAM_CHECK_ASYNC( yet_more.tm_min != xmas.tm_min );
    EXAM_CHECK_ASYNC( yet_more.tm_hour != xmas.tm_hour );
    EXAM_CHECK_ASYNC( yet_more.tm_mday == xmas.tm_mday );
    EXAM_CHECK_ASYNC( yet_more.tm_mon == xmas.tm_mon );
    EXAM_CHECK_ASYNC( yet_more.tm_year == xmas.tm_year );

    ++j; // skip space

    j = tmg.get_time( j, e, io, err, &yet_more );

    EXAM_CHECK_ASYNC( err == ios_base::eofbit || err == ios_base::goodbit );

    EXAM_CHECK_ASYNC( yet_more.tm_sec == xmas.tm_sec );
    EXAM_CHECK_ASYNC( yet_more.tm_min == xmas.tm_min );
    EXAM_CHECK_ASYNC( yet_more.tm_hour == xmas.tm_hour );
    EXAM_CHECK_ASYNC( yet_more.tm_mday == xmas.tm_mday );
    EXAM_CHECK_ASYNC( yet_more.tm_mon == xmas.tm_mon );
    EXAM_CHECK_ASYNC( yet_more.tm_year == xmas.tm_year );
  }
#  endif
}

typedef void (locale_test::*_TTest) (const locale&);

static void time_test_supported_locale( locale_test& inst, _TTest __test)
{
  size_t n = sizeof(tested_locales) / sizeof(tested_locales[0]);
  for (size_t i = 0; i < n; ++i) {
    locale loc;
    try {
      locale tmp(tested_locales[i]);
      loc = tmp;
    }
    catch (runtime_error const&) {
      //This locale is not supported.
      continue;
    }

    EXAM_MESSAGE_ASYNC( loc.name().c_str() );
    (inst.*__test)(loc);

    {
      locale tmp(locale::classic(), tested_locales[i], locale::time);
      loc = tmp;
    }
    (inst.*__test)(loc);

    {
      typedef time_put_byname<char, ostreambuf_iterator<char, char_traits<char> > > time_put_facet;
      locale tmp0(locale::classic(), new time_put_facet(tested_locales[i]));
      typedef time_get_byname<char, istreambuf_iterator<char, char_traits<char> > > time_get_facet;
      locale tmp1(tmp0, new time_get_facet(tested_locales[i]));
      loc = tmp1;
    }
    (inst.*__test)(loc);
  }
}

int EXAM_IMPL(locale_test::time_put_get)
{
  time_test_supported_locale(*this, &locale_test::_time_put_get);

  return EXAM_RESULT;
}

int EXAM_IMPL(locale_test::time_by_name)
{
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in
   * a runtime_error exception.
   */
#    if defined (STLPORT) || !defined (_MSC_VER) || (_MSC_VER > 1400)
  try {
    locale loc(locale::classic(), new time_put_byname<char, ostreambuf_iterator<char, char_traits<char> > >(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }
#    endif

  try {
    locale loc(locale::classic(), new time_put_byname<char, ostreambuf_iterator<char, char_traits<char> > >("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    string veryLongFacetName("LC_TIME=");
    veryLongFacetName.append(512, '?');
    locale loc(locale::classic(), new time_put_byname<char, ostreambuf_iterator<char, char_traits<char> > >(veryLongFacetName.c_str()));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new time_get_byname<char, istreambuf_iterator<char, char_traits<char> > >(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new time_get_byname<char, istreambuf_iterator<char, char_traits<char> > >("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    string veryLongFacetName("LC_TIME=");
    veryLongFacetName.append(512, '?');
    locale loc(locale::classic(), new time_get_byname<char, istreambuf_iterator<char, char_traits<char> > >(veryLongFacetName.c_str()));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const& /* e */) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), "C", locale::time);
  }
  catch (runtime_error const& /* e */) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

  try {
    // On platform without real localization support we should rely on the "C" facet.
    locale loc(locale::classic(), "", locale::time);
  }
  catch (runtime_error const& /* e */) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

  try {
    locale loc(locale::classic(), new time_get_byname<char, istreambuf_iterator<char, char_traits<char> > >("C"));
  }
  catch (runtime_error const& /* e */) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

  try {
    // On platform without real localization support we should rely on the "C" locale facet.
    locale loc(locale::classic(), new time_get_byname<char, istreambuf_iterator<char, char_traits<char> > >(""));
  }
  catch (runtime_error const& /* e */) {
    EXAM_ERROR( "unexpected runtime_error exception" );
  }
  catch (...) {
    EXAM_ERROR( "unexpected unknown exception" );
  }

#    if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  try {
    locale loc(locale::classic(), new time_put_byname<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new time_put_byname<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new time_get_byname<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(static_cast<char const*>(0)));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

  try {
    locale loc(locale::classic(), new time_get_byname<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >("yasli_language"));
    EXAM_ERROR( "runtime_error exception expected" );
  }
  catch (runtime_error const&) {
    EXAM_MESSAGE( "runtime_error exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "runtime_error exception expected" );
  }

#    endif

  return EXAM_RESULT;
}

int EXAM_IMPL(locale_test::hidden)
{
  /* Check linkage: bug ID 3472902; some names, used in num_put,
     was not exported with visibility=hidden.
  */
  std::locale l(std::locale::classic(), new std::num_put<char>() );

  return EXAM_RESULT;
}
