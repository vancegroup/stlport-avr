#include "locale_test.h"

#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <locale>
#  include <sstream>
#  include <stdexcept>
#  include <memory>

#  include "complete_digits.h"

#  if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#  endif

struct ref_locale {
  const char *name;
  const char *decimal_point;
  const char *thousands_sep;
};

// Pls, don't write #ifdef _STLP_REAL_LOCALE_IMPLEMENTED here!
// It undefined in any case!!!!!

static const ref_locale tested_locales[] = {
//{  name,         decimal_point, thousands_sepy_thousands_sep},
  { "fr_FR",       ",",           "\xa0"},
  { "ru_RU.koi8r", ",",           "."},
  { "en_GB",       ".",           ","},
  { "en_US",       ".",           ","},
  { "C",           ".",           ","},
};

//
// tests implementation
//
void LocaleTest::_num_put_get( const locale& loc, const ref_locale* prl ) {
  const ref_locale& rl = *prl;
  CPPUNIT_ASSERT( has_facet<numpunct<char> >(loc) );
  numpunct<char> const& npct = use_facet<numpunct<char> >(loc);
  CPPUNIT_ASSERT( npct.decimal_point() == *rl.decimal_point );

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
  CPPUNIT_ASSERT( fostr.str() == ref );

  val = 12345678.9f;
  ref = "1";
  ref += npct.decimal_point();
  ref += "23457e+";
  string digits = "7";
  complete_digits(digits);
  ref += digits;
  fostr.str("");
  fostr << val;
  CPPUNIT_ASSERT( fostr.str() == ref );

  val = 1000000000.0f;
  fostr.str("");
  fostr << val;
  digits = "9";
  complete_digits(digits);
  CPPUNIT_ASSERT( fostr.str() == string("1e+") + digits );

  val = 1234.0f;
  ref = "1";
  if (!npct.grouping().empty()) {
    ref += npct.thousands_sep();
  }
  ref += "234";
  fostr.str("");
  fostr << val;
  CPPUNIT_ASSERT( fostr.str() == ref );

  val = 10000001.0f;
  fostr.str("");
  fostr << val;
  digits = "7";
  complete_digits(digits);
  CPPUNIT_ASSERT( fostr.str() == string("1e+") + digits );

#if defined (__BORLANDC__)
  num_put<char> const& nput = use_facet<num_put<char> >(loc);
  typedef numeric_limits<double> limd;
  fostr.setf(ios_base::uppercase | ios_base::showpos);

  if (limd::has_infinity) {
    double infinity = limd::infinity();
    fostr.str("");
    nput.put(fostr, fostr, ' ', infinity);
    CPPUNIT_ASSERT( fostr.str() == string("+Inf") );
  }

  if (limd::has_quiet_NaN) {
    double qnan = limd::quiet_NaN();
    fostr.str("");
    nput.put(fostr, fostr, ' ', qnan);
    CPPUNIT_ASSERT( fostr.str() == string("+NaN") );
  }
#endif
}

template <class _Tp>
void test_supported_locale(LocaleTest inst, _Tp __test) {
  size_t n = sizeof(tested_locales) / sizeof(tested_locales[0]);
  for (size_t i = 0; i < n; ++i) {
    auto_ptr<locale> loc;
#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
    try {
      loc.reset(new locale(tested_locales[i].name));
    }
    catch (runtime_error const&) {
      //This locale is not supported.
      continue;
    }
#  else
    //Without exception support we only test C locale.
    if (tested_locales[i].name[0] != 'C' ||
        tested_locales[i].name[1] != 0)
      continue;
    loc.reset(new locale(tested_locales[i].name));
#  endif
    CPPUNIT_MESSAGE( loc->name().c_str() );
    (inst.*__test)(*loc, tested_locales + i);
  }
}

void LocaleTest::num_put_get()
{ test_supported_locale(*this, &LocaleTest::_num_put_get); }

void LocaleTest::numpunct_by_name()
{
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in
   * a runtime_error exception.
   */
#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    locale loc(locale::classic(), new numpunct_byname<char>(static_cast<char const*>(0)));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new numpunct_byname<char>("yasli_language"));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    string veryLongFacetName("LC_NUMERIC=");
    veryLongFacetName.append(512, '?');
    locale loc(locale::classic(), new numpunct_byname<char>(veryLongFacetName.c_str()));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const& /* e */) {
    //CPPUNIT_MESSAGE( e.what() );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), "C", locale::numeric);
  }
  catch (runtime_error const& e) {
    CPPUNIT_MESSAGE( e.what() );
    CPPUNIT_ASSERT( false );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    // On platform without real localization support we should rely on the "C" facet.
    locale loc(locale::classic(), "", locale::numeric);
  }
  catch (runtime_error const& e) {
    CPPUNIT_MESSAGE( e.what() );
    CPPUNIT_ASSERT( false );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new numpunct_byname<char>("C"));
    numpunct<char> const& cfacet_byname = use_facet<numpunct<char> >(loc);
    numpunct<char> const& cfacet = use_facet<numpunct<char> >(locale::classic());

    CPPUNIT_CHECK( cfacet_byname.decimal_point() == cfacet.decimal_point() );
    CPPUNIT_CHECK( cfacet_byname.thousands_sep() == cfacet.thousands_sep() );
    CPPUNIT_CHECK( cfacet_byname.grouping() == cfacet.grouping() );
    CPPUNIT_CHECK( cfacet_byname.truename() == cfacet.truename() );
    CPPUNIT_CHECK( cfacet_byname.falsename() == cfacet.falsename() );
  }
  catch (runtime_error const& e) {
    CPPUNIT_MESSAGE( e.what() );
    CPPUNIT_ASSERT( false );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    // On platform without real localization support we should rely on the "C" locale facet.
    locale loc(locale::classic(), new numpunct_byname<char>(""));
  }
  catch (runtime_error const& e) {
    CPPUNIT_MESSAGE( e.what() );
    CPPUNIT_ASSERT( false );
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

#    if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
  try {
    locale loc(locale::classic(), new numpunct_byname<wchar_t>(static_cast<char const*>(0)));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc(locale::classic(), new numpunct_byname<wchar_t>("yasli_language"));
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
