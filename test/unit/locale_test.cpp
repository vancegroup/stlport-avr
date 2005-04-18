#include <string>
#if !defined (STLPORT) || !defined (_STLP_NO_IOSTREAMS)
#  include <sstream>
#  include <locale>

#  include <cstdio>

#  if defined(__unix) || defined(__unix__)
#    include <sys/types.h>
#    include <sys/stat.h>
#    include <dirent.h>
#    include <unistd.h>
#    include <cstring>
#    include <iostream>
#  endif

#  include <map>

#  include "cppunit/cppunit_proxy.h"

#  if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#  endif


class LColl {
  public:
    LColl( const char * );

    bool operator[]( const string& _s )
     { return _m[_s]; }

  private:
    map<string,bool> _m;
};

LColl::LColl( const char *loc_dir )
{
#  if (defined(__unix) || defined(__unix__)) && !defined(__CYGWIN__)
  /* Iterate through catalog that contain catalogs with locale definitions, installed on system
   * (this is expected /usr/lib/locale for most linuxes and /usr/share/locale for *BSD).
   * The names of catalogs here will give supported locales.
   */
  string base( loc_dir );
  DIR *d = opendir( base.c_str() );
  struct dirent *ent;
  while ( (ent = readdir( d )) != 0 ) {
    if ( strcmp( ent->d_name, "." ) == 0 || strcmp( ent->d_name, ".." ) == 0 ) {
      continue;
    }
    string f = base;
    f += '/';
    f += ent->d_name;
    struct stat s;
    stat( f.c_str(), &s );
    if ( S_ISDIR( s.st_mode ) ) {
      _m[string(ent->d_name)] = true;
      // cout << ent->d_name << endl;
    }
  }
  closedir( d );
#  else
#    ifdef _MSC_VER
  //Avoids warning:
  (void*)loc_dir;
#    endif
#  endif
#  if defined (WIN32) && !defined (_STLP_WCE)
  // real list of installed locales should be here...
  _m[string("french")] = true;
#  endif
  // std::locale must at least support the C locale
  _m[string("C")] = true;
}

#  if !defined(__GNUC__) || (__GNUC__ > 2)
#    if defined(__FreeBSD__) || defined(__OpenBSD__)
static LColl loc_ent( "/usr/share/locale" );
#    else
static LColl loc_ent( "/usr/lib/locale" );
#    endif
#  endif // !__GNUC__ || __GNUC__ > 2

struct ref_locale {
  const char *name;
  const char *decimal_point;
  const char *thousands_sep;
  const char *money_int_prefix;
  const char *money_prefix;
  const char *money_int_suffix;
  const char *money_int_suffix_old;
  const char *money_suffix;
  const char *money_decimal_point;
  const char *money_thousands_sep;
};


// Pls, don't write #ifdef _STLP_REAL_LOCALE_IMPLEMENTED here!
// It undefined in any case!!!!!

static ref_locale tested_locales[] = {
//{  name,         decimal_point, thousands_sep, money_int_prefix, money_prefix, money_int_suffix, money_int_suffix_old, money_suffix, money_decimal_point,  money_thousands_sep},
  { "french",      ",",           "\xa0",        "",               "",           " EUR",           " FRF",               "",           ",",                  "\xa0" },
  { "ru_RU.koi8r", ",",           ".",           "",               "",           " RUR",           " RUR",               "",           ".",                  " " },
  { "en_GB",       ".",           ",",           "GBP ",           "\xa3",       "",               "",                   "",           ".",                  "," },
  { "en_US",       ".",           ",",           "USD ",           "$",          "",               "",                   "",           ".",                  "," },
  { "C",           ".",           ",",           "",               "",           "",               "",                   "",           " ",                  " " },
};


//
// TestCase class
//
class LocaleTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(LocaleTest);
  CPPUNIT_TEST(locale_by_name);
  CPPUNIT_TEST(loc_has_facet);
  CPPUNIT_TEST(num_put_get);
  CPPUNIT_TEST(money_put_get);
  CPPUNIT_TEST(time_put_get);
  CPPUNIT_TEST(collate_facet);
  CPPUNIT_TEST(locale_init_problem);
  CPPUNIT_TEST_SUITE_END();

public:
  void locale_by_name();
  void loc_has_facet();
  void num_put_get();
  void money_put_get();
  void time_put_get();
  void collate_facet();
  void locale_init_problem();
private:
  void _loc_has_facet( const locale&, const ref_locale& );
  void _num_put_get( const locale&, const ref_locale& );
  void _money_put_get( const locale&, const ref_locale& );
  void _time_put_get( const locale&, const ref_locale& );
  void _collate_facet( const locale&, const ref_locale& );
  void _locale_init_problem( const locale&, const ref_locale& );
};

CPPUNIT_TEST_SUITE_REGISTRATION(LocaleTest);

//
// tests implementation
//
void LocaleTest::_num_put_get( const locale& loc, const ref_locale& rl ) {
  float val = 1234.56f;
  ostringstream ostr;
  ostr << val;
  CPPUNIT_ASSERT( ostr );
  //CPPUNIT_TEST( ostr.str() == "1234.56" );
  CPPUNIT_ASSERT( ostr.str() == "1234.56" );

  numpunct<char> const& npct = use_facet<numpunct<char> >(loc);

  CPPUNIT_ASSERT( npct.decimal_point() == *rl.decimal_point );
  CPPUNIT_ASSERT( npct.thousands_sep() == *rl.thousands_sep );

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
  CPPUNIT_ASSERT( fostr.str() == ref );

  val = 12345678.9f;
  ostr.str("");
  ostr << val;
  CPPUNIT_ASSERT( ostr.str() == "1.23457e+07" );

  ref = "1";
  ref += npct.decimal_point();
  ref += "23457e+07";
  fostr.str("");
  fostr << val;
  CPPUNIT_ASSERT( fostr.str() == ref );

  val = 1000000000.0f;
  ostr.str("");
  ostr << val;
  CPPUNIT_ASSERT( ostr.str() == "1e+09" );

  fostr.str("");
  fostr << val;
  CPPUNIT_ASSERT( fostr.str() == "1e+09" );
}

void LocaleTest::_money_put_get( const locale& loc, const ref_locale& rl )
{
  money_put<char> const& fmp = use_facet<money_put<char> >(loc);
  money_get<char> const& fmg = use_facet<money_get<char> >(loc);
  moneypunct<char, true> const& intl_fmp = use_facet<moneypunct<char, true> >(loc);

  ostringstream ostr;
  ostr.imbue(loc);
  ostr << showbase;
  ostreambuf_iterator<char> res = fmp.put(ostr, true, ostr, ' ', 123456);

  CPPUNIT_ASSERT( !res.failed() );
  //The result is '1 234,56 EUR'
  string str_res = ostr.str();

  size_t index = 0;
  string::size_type p = strlen( rl.money_int_prefix );
  CPPUNIT_ASSERT( str_res.substr( 0, p ) == rl.money_int_prefix );
  index = p;
  CPPUNIT_ASSERT( str_res[index++] == '1' );
  if (!intl_fmp.grouping().empty()) {
    CPPUNIT_ASSERT( str_res[index++] == /* intl_fmp.thousands_sep() */ *rl.money_thousands_sep );
  }
  CPPUNIT_ASSERT( str_res[index++] == '2' );
  CPPUNIT_ASSERT( str_res[index++] == '3' );
  CPPUNIT_ASSERT( str_res[index++] == '4' );
  if (intl_fmp.frac_digits() != 0) {
    CPPUNIT_ASSERT( str_res[index++] == /* intl_fmp.decimal_point() */ *rl.money_decimal_point );
  }
  CPPUNIT_ASSERT( str_res[index++] == '5' );
  CPPUNIT_ASSERT( str_res[index++] == '6' );
  // CPPUNIT_ASSERT( str_res[p + 8] == ' ' );
  string::size_type p1 = strlen( rl.money_int_suffix );
  CPPUNIT_ASSERT( str_res.substr(index, p1) == rl.money_int_suffix || 
                  str_res.substr(index, p1) == rl.money_int_suffix_old );
  // CPPUNIT_ASSERT( intl_fmp.curr_symbol() == rl.money_suffix );

  // CPPUNIT_ASSERT( str_res.substr(p + 9, intl_fmp.curr_symbol().size()) == intl_fmp.curr_symbol() );
  // CPPUNIT_ASSERT( str_res.size() == 9 + intl_fmp.curr_symbol().size() );

  ios_base::iostate err = ios_base::goodbit;
  string digits;

  istringstream istr(str_res);
  ostr.str( "" );
  ostr.clear();
  fmg.get(istr, istreambuf_iterator<char>(), true, ostr, err, digits);
  CPPUNIT_ASSERT( (err & (ios_base::failbit | ios_base::badbit)) == 0 );
  CPPUNIT_ASSERT( digits == "123456" );

  ostr.str("");
  moneypunct<char, false> const& dom_fmp = use_facet<moneypunct<char, false> >(loc);
  res = fmp.put(ostr, false, ostr, ' ', -123456);

  CPPUNIT_ASSERT( !res.failed() );
  //The result is '-1 234,56 E' E being the euro symbol
  str_res = ostr.str();

  index = 0;
  CPPUNIT_ASSERT( str_res.substr(index, dom_fmp.negative_sign().size()) == dom_fmp.negative_sign() );
  index += dom_fmp.negative_sign().size();
  p = strlen( rl.money_prefix );
  index += p;
  CPPUNIT_ASSERT( str_res[index++] == '1' );
  if (!dom_fmp.grouping().empty()) {
    CPPUNIT_ASSERT( str_res[index++] == dom_fmp.thousands_sep() );
  }
  CPPUNIT_ASSERT( str_res[index++] == '2' );
  CPPUNIT_ASSERT( str_res[index++] == '3' );
  CPPUNIT_ASSERT( str_res[index++] == '4' );
  if (dom_fmp.frac_digits() != 0) {
    CPPUNIT_ASSERT( str_res[index++] == dom_fmp.decimal_point() );
  }
  CPPUNIT_ASSERT( str_res[index++] == '5' );
  CPPUNIT_ASSERT( str_res[index++] == '6' );
  p1 = strlen( rl.money_suffix );
  CPPUNIT_ASSERT( str_res.substr(index, p1) == rl.money_suffix );
  index += p1;
  // CPPUNIT_ASSERT( str_res[index++] == ' ' );
  // CPPUNIT_ASSERT( str_res.substr(index, dom_fmp.curr_symbol().size()) == dom_fmp.curr_symbol() );
  // CPPUNIT_ASSERT( str_res.size() == index + dom_fmp.curr_symbol().size() );

  err = 0;
  _STLP_LONG_DOUBLE val;

  istr.str(str_res);
  fmg.get(istr, istreambuf_iterator<char>(), false, ostr, err, val);
  CPPUNIT_ASSERT( (err & (ios_base::failbit | ios_base::badbit)) == 0 );
  if (dom_fmp.negative_sign().empty()) {
    //Without negative sign there is no way to guess the resulting amount sign ("C" locale):
    CPPUNIT_ASSERT( val == 123456 );
  }
  else {
    CPPUNIT_ASSERT( val == -123456 );
  }
}

void LocaleTest::_time_put_get( const locale& loc, const ref_locale&)
{
  time_put<char> const&tmp = use_facet<time_put<char> >(loc);
  //time_get<char> const&tmg = use_facet<time_get<char> >(loc);

  struct tm xmas = { 0, 0, 12, 25, 11, 93 };
  ostringstream ostr;
  ostr.imbue(loc);
  string format = "%a %d %b %y";

  time_put<char>::iter_type ret = tmp.put(ostr, ostr, ' ', &xmas, format.data(), format.data() + format.size());
  CPPUNIT_ASSERT( !ret.failed() );

  string str_ret = ostr.str();
}

void LocaleTest::_collate_facet( const locale& loc, const ref_locale&)
{
  CPPUNIT_ASSERT( has_facet<collate<char> >(loc) );
  collate<char> const& col = use_facet<collate<char> >(loc);

  char const str1[] = "françois";
  char const str2[] = "francois";

  CPPUNIT_ASSERT( col.compare(str1, str1 + sizeof(str1) / sizeof(str1[0]), str2, str2 + sizeof(str2) / sizeof(str2[0])) );
}

template <class _Tp>
void test_supported_locale(LocaleTest inst, _Tp __test) {
#  if defined(__GNUC__) && (__GNUC__ < 3) // workaround for gcc 2.95.x
#    if defined(__FreeBSD__) || defined(__OpenBSD__)
   LColl loc_ent( "/usr/share/locale" );
#    else
   LColl loc_ent( "/usr/lib/locale" );
#    endif
#  endif // __GNUC__ || __GNUC__ < 3

  int n = sizeof(tested_locales) / sizeof(tested_locales[0]);
  for ( int i = 0; i < n; ++i ) {
    if ( loc_ent[string( tested_locales[i].name )] ) {
      // cout << '\t' << tested_locales[i].name << endl;
      CPPUNIT_MESSAGE( tested_locales[i].name );
      locale loc( tested_locales[i].name );
      (inst.*__test)(loc, tested_locales[i] );
    }
  }
}

void LocaleTest::locale_by_name() {
#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  /*
   * Check of the 22.1.1.2.7 standard point. Construction of a locale
   * instance from a null pointer or an unknown name should result in 
   * a runtime_error exception.
   */
  try {
    locale loc(static_cast<char const*>(0));
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }

  try {
    locale loc("yasli_language");
    CPPUNIT_ASSERT( false );
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }
#  endif
}

void LocaleTest::loc_has_facet() {
  locale loc("C");
  typedef numpunct<char> implemented_facet;
  CPPUNIT_ASSERT( has_facet<implemented_facet>(loc) );
  /*
  typedef num_put<char, back_insert_iterator<string> > not_implemented_facet;
  CPPUNIT_ASSERT( !has_facet<not_implemented_facet>(loc) );
  */
}

void LocaleTest::num_put_get() {
  test_supported_locale(*this, &LocaleTest::_num_put_get);
}

void LocaleTest::money_put_get() {
  test_supported_locale(*this, &LocaleTest::_money_put_get);
}

void LocaleTest::time_put_get() {
  test_supported_locale(*this, &LocaleTest::_time_put_get);
}

void LocaleTest::collate_facet() {
  test_supported_locale(*this, &LocaleTest::_collate_facet);
}

void LocaleTest::locale_init_problem()
{
  test_supported_locale(*this, &LocaleTest::_locale_init_problem);
}

void LocaleTest::_locale_init_problem( const locale& loc, const ref_locale&)
{
#  if !defined (__FreeBSD__) || !defined(__GNUC__) || ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__> 3)))
  typedef codecvt<char,char,mbstate_t> my_facet;
#  else
// std::mbstate_t required for gcc 3.3.2 on FreeBSD...
// I am not sure what key here---FreeBSD or 3.3.2...
//      - ptr 2005-04-04
  typedef codecvt<char,char,std::mbstate_t> my_facet;
#  endif

  locale loc_ref;
  {
    locale gloc( loc_ref, new my_facet() );
    CPPUNIT_ASSERT( has_facet<my_facet>( gloc ) );
    //The following code is just here to try to confuse the reference counting underlying mecanism:
    locale::global( locale::classic() );
    locale::global( gloc );
  }

#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
#  endif
    ostringstream os("test") ;
    locale loc2( loc, new my_facet() );
    CPPUNIT_ASSERT( has_facet<my_facet>( loc2 ) );
    os.imbue( loc2 );
#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  }
  catch ( runtime_error& ) {
    CPPUNIT_ASSERT( false );
    // cerr << "-- " << err.what() << endl;
  }
  catch ( ... ) {
   CPPUNIT_ASSERT( false );
  }
#  endif

#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
#  endif
    ostringstream os2("test2");
#  if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  }
  catch ( runtime_error& ) {
    CPPUNIT_ASSERT( false );
  }
  catch ( ... ) {
    CPPUNIT_ASSERT( false );
  }
#  endif
}

#endif
