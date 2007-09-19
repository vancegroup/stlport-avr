
#include <locale.h>
#include <langinfo.h>

#include <stl/c_locale.h>
#include <stdio.h>
#include <wctype.h>
#include <string.h>

#include <stdint.h>

typedef __locale_t __c_locale;

#if (__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ > 2))
#  define __nl_langinfo_l nl_langinfo_l
#  define __newlocale newlocale
#  define __freelocale freelocale
#endif

#define __LOCALE_CREATE(nm,category) __newlocale(1 << category, nm, NULL )
#define __LOCALE_DESTROY(__loc)      __freelocale((__c_locale)__loc)

static const char *_empty_str = "";
static const char *_C_name = "C";

#if 0
struct _Locale_ctype
{
  __c_locale __cloc;
};

struct _Locale_numeric
{
  __c_locale __cloc;
};

struct _Locale_time
{
  __c_locale __cloc;
};

struct _Locale_collate
{
  __c_locale __cloc;
};

struct _Locale_monetary
{
  __c_locale __cloc;
};

struct _Locale_messages
{
  __c_locale __cloc;
};
#endif

void _Locale_init()
{}

void _Locale_final()
{}

int _Locale_errno(void)
{ return _STLP_UNSUPPORTED_LOCALE; }

struct _Locale_ctype *_Locale_ctype_create( const char *nm, struct _Locale_name_hint* hint )
{ return (struct _Locale_ctype*)__LOCALE_CREATE( nm, LC_CTYPE ); }

struct _Locale_numeric *_Locale_numeric_create( const char *nm, struct _Locale_name_hint* hint )
{ return (struct _Locale_numeric*)__LOCALE_CREATE( nm, LC_NUMERIC ); }
  
struct _Locale_time *_Locale_time_create( const char *nm, struct _Locale_name_hint* hint )
{ return (struct _Locale_time*)__LOCALE_CREATE( nm, LC_TIME ); }

struct _Locale_collate *_Locale_collate_create( const char *nm, struct _Locale_name_hint* hint )
{ return (struct _Locale_collate*)__LOCALE_CREATE( nm, LC_COLLATE ); }

struct _Locale_monetary *_Locale_monetary_create( const char *nm, struct _Locale_name_hint* hint )
{ return (struct _Locale_monetary*)__LOCALE_CREATE( nm, LC_MONETARY ); }

struct _Locale_messages *_Locale_messages_create( const char *nm, struct _Locale_name_hint* hint )
{ return (struct _Locale_messages*)__LOCALE_CREATE( nm, LC_MESSAGES ); }

/*
  try to see locale category LC should be used from environment;
  according POSIX, the order is
  1. LC_ALL
  2. category (LC_CTYPE, LC_NUMERIC, ... )
  3. LANG
  If set nothing, return "C" (this really implemetation-specific).
*/
static const char *_Locale_aux_default( const char *LC, char *nm )
{
  char *name = getenv( "LC_ALL" );

  if ( name != NULL && *name != 0 ) {
    return strncpy( nm, name, _Locale_MAX_SIMPLE_NAME );
  }
  name = getenv( LC );
  if ( name != NULL && *name != 0 ) {
    return strncpy( nm, name, _Locale_MAX_SIMPLE_NAME );
  }
  name = getenv( "LANG" );
  if ( name != NULL && *name != 0 ) {
    return strncpy( nm, name, _Locale_MAX_SIMPLE_NAME );
  }

  return strcpy( nm, _C_name );
}

const char *_Locale_ctype_default( char *nm )
{
  return _Locale_aux_default( "LC_CTYPE", nm );
}

const char *_Locale_numeric_default( char *nm )
{
  return _Locale_aux_default( "LC_NUMERIC", nm );
}

const char *_Locale_time_default( char *nm )
{
  return _Locale_aux_default( "LC_TIME", nm );
}

const char *_Locale_collate_default( char *nm )
{
  return _Locale_aux_default( "LC_COLLATE", nm );
}

const char *_Locale_monetary_default( char *nm )
{
  return _Locale_aux_default( "LC_MONETARY", nm );
}

const char *_Locale_messages_default( char *nm )
{
  return _Locale_aux_default( "LC_MESSAGES", nm );
}

char const*_Locale_ctype_name( const struct _Locale_ctype *__loc, char *buf )
{
  return __loc != 0 ? strncpy( buf, ((__c_locale)__loc)->__names[LC_CTYPE], _Locale_MAX_SIMPLE_NAME ) : 0;
}

char const*_Locale_numeric_name( const struct _Locale_numeric *__loc, char *buf )
{
  return __loc != 0 ? strncpy( buf, ((__c_locale)__loc)->__names[LC_NUMERIC], _Locale_MAX_SIMPLE_NAME ) : 0;
}

char const*_Locale_time_name( const struct _Locale_time *__loc, char *buf )
{
  return __loc != 0 ? strncpy( buf, ((__c_locale)__loc)->__names[LC_TIME], _Locale_MAX_SIMPLE_NAME ) : 0;
}

char const*_Locale_collate_name( const struct _Locale_collate *__loc, char *buf )
{
  return __loc != 0 ? strncpy( buf, ((__c_locale)__loc)->__names[LC_COLLATE], _Locale_MAX_SIMPLE_NAME ) : 0;
}

char const*_Locale_monetary_name( const struct _Locale_monetary *__loc, char *buf )
{
  return __loc != 0 ? strncpy( buf, ((__c_locale)__loc)->__names[LC_MONETARY], _Locale_MAX_SIMPLE_NAME ) : 0;
}

char const*_Locale_messages_name( const struct _Locale_messages *__loc, char *buf )
{
  return __loc != 0 ? strncpy( buf, ((__c_locale)__loc)->__names[LC_MESSAGES], _Locale_MAX_SIMPLE_NAME ) : 0;
}

void _Locale_ctype_destroy( struct _Locale_ctype *__loc )
{ __LOCALE_DESTROY(__loc); }

void _Locale_numeric_destroy( struct _Locale_numeric *__loc )
{ __LOCALE_DESTROY(__loc); }

void _Locale_time_destroy( struct _Locale_time *__loc )
{ __LOCALE_DESTROY(__loc); }

void _Locale_collate_destroy( struct _Locale_collate *__loc )
{ __LOCALE_DESTROY(__loc); }

void _Locale_monetary_destroy( struct _Locale_monetary *__loc )
{ __LOCALE_DESTROY(__loc); }

void _Locale_messages_destroy( struct _Locale_messages* __loc )
{ __LOCALE_DESTROY(__loc); }

/*
 * locale loc expected either locale name indeed (platform-specific)
 * or string like "LC_CTYPE=LocaleNameForCType;LC_NUMERIC=LocaleNameForNum;"
 *
 */

static char const*__Extract_locale_name( const char *loc, const char *category, char *buf )
{
  char *expr;
  size_t len_name;
  buf[0] = 0;

  if( loc[0]=='L' && loc[1]=='C' && loc[2]=='_') {
    expr = strstr( (char*)loc, category );
    if ( expr == NULL )
      return NULL; /* Category not found. */
    ++expr;
    len_name = strcspn( expr, ";" );
    len_name = len_name > _Locale_MAX_SIMPLE_NAME ? _Locale_MAX_SIMPLE_NAME : len_name;
    strncpy( buf, expr, len_name );
    buf[len_name] = 0;
    return buf;
  }
  return strncpy( buf, loc, _Locale_MAX_SIMPLE_NAME );
}

char const*_Locale_extract_ctype_name( const char *loc, char *buf, struct _Locale_name_hint* hint )
{ return __Extract_locale_name( loc, "LC_CTYPE=", buf ); }

char const*_Locale_extract_numeric_name( const char *loc, char *buf, struct _Locale_name_hint* hint )
{ return __Extract_locale_name( loc, "LC_NUMERIC=", buf ); }

char const*_Locale_extract_time_name( const char *loc, char *buf, struct _Locale_name_hint* hint )
{ return __Extract_locale_name( loc, "LC_TIME=", buf ); }

char const*_Locale_extract_collate_name( const char *loc, char *buf, struct _Locale_name_hint* hint )
{ return __Extract_locale_name( loc, "LC_COLLATE=", buf ); }

char const*_Locale_extract_monetary_name( const char *loc, char *buf, struct _Locale_name_hint* hint )
{ return __Extract_locale_name( loc, "LC_MONETARY=", buf ); }

char const*_Locale_extract_messages_name( const char *loc, char *buf, struct _Locale_name_hint* hint )
{ return __Extract_locale_name( loc, "LC_MESSAGES=", buf ); }

char const*_Locale_compose_name(char*__DUMMY_PAR1, const char*__DUMMY_PAR2, const char*__DUMMY_PAR3,
                            const char*__DUMMY_PAR4,
                            const char*__DUMMY_PAR5, const char*__DUMMY_PAR6, const char*__DUMMY_PAR7, const char*__DUMMY_PAR8) {
  /* TODO: what's this? Is this a marker that this is not yet completely
  implemented? Copy the implementation from c_locale_win32 perhaps? It seems
  to complement the extract functions above. */
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return 0;
}

struct _Locale_name_hint* _Locale_get_ctype_hint(struct _Locale_ctype* ctype)
{ return 0; }
struct _Locale_name_hint* _Locale_get_numeric_hint(struct _Locale_numeric* numeric)
{ return 0; }
struct _Locale_name_hint* _Locale_get_time_hint(struct _Locale_time* time)
{ return 0; }
struct _Locale_name_hint* _Locale_get_collate_hint(struct _Locale_collate* collate)
{ return 0; }
struct _Locale_name_hint* _Locale_get_monetary_hint(struct _Locale_monetary* monetary)
{ return 0; }
struct _Locale_name_hint* _Locale_get_messages_hint(struct _Locale_messages* messages)
{ return 0; }

/* ctype */

const _Locale_mask_t *_Locale_ctype_table( struct _Locale_ctype *__loc )
{
  /* return table with masks (upper, lower, alpha, etc.) */
  _STLP_STATIC_ASSERT( sizeof(_Locale_mask_t) == sizeof(((__c_locale)__loc)->__ctype_b[0]) )
  return ((__c_locale)__loc)->__ctype_b;
}

int _Locale_toupper( struct _Locale_ctype *__loc, int c )
{ return ((__c_locale)__loc)->__ctype_toupper[c]; }

int _Locale_tolower( struct _Locale_ctype *__loc, int c )
{ return ((__c_locale)__loc)->__ctype_tolower[c]; }

#if !defined (_STLP_NO_WCHAR_T)
_Locale_mask_t _Locale_wchar_ctype( struct _Locale_ctype *__loc, wint_t wc, _Locale_mask_t __mask )
{
  _Locale_mask_t ret = 0;
  if ( (__mask & _Locale_ALPHA) != 0 && iswalpha_l(wc, ((__c_locale)__loc)))
    ret |= _Locale_ALPHA;
  
  if ( (__mask & _Locale_CNTRL) != 0 && iswcntrl_l(wc, ((__c_locale)__loc)))
    ret |= _Locale_CNTRL;

  if ( (__mask & _Locale_DIGIT) != 0 && iswdigit_l(wc, ((__c_locale)__loc)))
    ret |= _Locale_DIGIT;

  if ( (__mask & _Locale_PRINT) != 0 && iswprint_l(wc, ((__c_locale)__loc))) 
    ret |= _Locale_PRINT;

  if ( (__mask & _Locale_PUNCT) != 0 && iswpunct_l(wc, ((__c_locale)__loc)))
    ret |= _Locale_PUNCT;

  if ( (__mask & _Locale_SPACE) != 0 && iswspace_l(wc, ((__c_locale)__loc)))
    ret |= _Locale_SPACE;

  if ( (__mask & _Locale_XDIGIT) != 0 && iswxdigit_l(wc, ((__c_locale)__loc)))
    ret |= _Locale_XDIGIT;

  if ( (__mask & _Locale_UPPER) != 0 && iswupper_l(wc, ((__c_locale)__loc)))
    ret |= _Locale_UPPER;

  if ( (__mask & _Locale_LOWER) != 0 && iswlower_l(wc, ((__c_locale)__loc)))
    ret |= _Locale_LOWER;

  return ret;
}

wint_t _Locale_wchar_tolower( struct _Locale_ctype *__loc, wint_t c )
{
  return towlower_l( c, ((__c_locale)__loc) );
}

wint_t _Locale_wchar_toupper( struct _Locale_ctype *__loc, wint_t c )
{
  return towupper_l( c, ((__c_locale)__loc) );
}
#endif

#if !defined (_STLP_NO_MBSTATE_T)

int _Locale_mb_cur_max( struct _Locale_ctype * __DUMMY_PAR) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return 0;
}

int _Locale_mb_cur_min( struct _Locale_ctype * __DUMMY_PAR) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return 0;
}

int _Locale_is_stateless( struct _Locale_ctype * __DUMMY_PAR) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return 1;
}

#if !defined (_STLP_NO_WCHAR_T)
wint_t _Locale_btowc(struct _Locale_ctype *__loc, int c) {
  wint_t _c;
  /* __c_locale __tmp = __uselocale( __loc ); */
  _c = btowc( c );
  /* __uselocale( __tmp ); */
  return _c;
}

int _Locale_wctob(struct _Locale_ctype *__loc, wint_t c) {
  int _c;
  /* __c_locale __tmp = __uselocale( __loc ); */
  _c = wctob( c );
  /* __uselocale( __tmp ); */
  return _c;
}

size_t _Locale_mbtowc(struct _Locale_ctype *__DUMMY_PAR1,
                      wchar_t *__DUMMY_PAR2,
                      const char *__DUMMY_PAR3, size_t __DUMMY_PAR4,
                      mbstate_t *__DUMMY_PAR5) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return (size_t) -1;
}

size_t _Locale_wctomb(struct _Locale_ctype *__DUMMY_PAR1,
                      char *__DUMMY_PAR2, size_t __DUMMY_PAR3,
                      const wchar_t __DUMMY_PAR4,
                      mbstate_t *__DUMMY_PAR5) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return (size_t) -1;
}
#endif

size_t _Locale_unshift(struct _Locale_ctype *__DUMMY_PAR1,
                       mbstate_t *__DUMMY_PAR2,
                       char *__DUMMY_PAR3, size_t __DUMMY_PAR4, char ** __DUMMY_PAR5) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return (size_t) -1;
}

#endif /*  _STLP_NO_MBSTATE_T */

/* Collate */
int _Locale_strcmp(struct _Locale_collate * __loc,
                   const char *s1, size_t n1,
		   const char *s2, size_t n2) {
  int ret = 0;
  char buf1[64], buf2[64];
  while (n1 > 0 || n2 > 0) {
    size_t bufsize1 = n1 < 63 ? n1 : 63;
    strncpy(buf1, s1, bufsize1); buf1[bufsize1] = 0;
    size_t bufsize2 = n2 < 63 ? n2 : 63;
    strncpy(buf2, s2, bufsize2); buf2[bufsize2] = 0;

    ret = strcoll_l(buf1, buf2, (__c_locale)__loc);
    if (ret != 0) return ret;
    s1 += bufsize1; n1 -= bufsize1;
    s2 += bufsize2; n2 -= bufsize2;
  }
  return ret;
}

#if !defined (_STLP_NO_WCHAR_T)
int _Locale_strwcmp(struct _Locale_collate *__loc,
                    const wchar_t *s1, size_t n1,
                    const wchar_t *s2, size_t n2) {
  int ret = 0;
  wchar_t buf1[64], buf2[64];
  while (n1 > 0 || n2 > 0) {
    size_t bufsize1 = n1 < 63 ? n1 : 63;
    wcsncpy(buf1, s1, bufsize1); buf1[bufsize1] = 0;
    size_t bufsize2 = n2 < 63 ? n2 : 63;
    wcsncpy(buf2, s2, bufsize2); buf2[bufsize2] = 0;

    ret = wcscoll_l(buf1, buf2, (__c_locale)__loc);
    if (ret != 0) return ret;
    s1 += bufsize1; n1 -= bufsize1;
    s2 += bufsize2; n2 -= bufsize2;
  }
  return ret;
}

#endif

size_t _Locale_strxfrm(struct _Locale_collate *__loc,
                       char *dest, size_t dest_n,
                       const char *src, size_t src_n )
{
  if (src_n == 0)
  {
    if (dest != NULL) dest[0] = 0;
    return 0;
  }
  const char *real_src;
  char *buf = NULL;
  if (src[src_n] != 0) {
    buf = malloc(src_n + 1);
    strncpy(buf, src, src_n);
    buf[src_n] = 0;
    real_src = buf;
  }
  else
    real_src = src;
  size_t result = __strxfrm_l(dest, real_src, dest_n, (__c_locale)__loc);
  if (buf != NULL) free(buf);
  return result;
>>>>>>> .merge-right.r3193
}

# ifndef _STLP_NO_WCHAR_T

size_t _Locale_strwxfrm( struct _Locale_collate *__loc,
                        wchar_t *dest, size_t dest_n,
                        const wchar_t *src, size_t src_n )
{
  if (src_n == 0)
  {
    if (dest != NULL) dest[0] = 0;
    return 0;
  }
  const wchar_t *real_src;
  wchar_t *buf = NULL;
  if (src[src_n] != 0) {
    buf = malloc((src_n + 1) * sizeof(wchar_t));
    wcsncpy(buf, src, src_n);
    buf[src_n] = 0;
    real_src = buf;
  }
  else
    real_src = src;
  size_t result = __wcsxfrm_l(dest, real_src, dest_n, (__c_locale)__loc);
  if (buf != NULL) free(buf);
  return result;
}

# endif

/* Numeric */

char _Locale_decimal_point(struct _Locale_numeric *__loc)
{
  return (__loc != 0) ? *(__nl_langinfo_l(RADIXCHAR, (__c_locale)__loc)) : '.';
}

char _Locale_thousands_sep(struct _Locale_numeric *__loc)
{
  return (__loc != 0) ? *(__nl_langinfo_l(THOUSEP, (__c_locale)__loc)) : ',';
}

const char* _Locale_grouping(struct _Locale_numeric *__loc)
{
  return (__loc != 0 && _Locale_thousands_sep(__loc) != '\0' ) ?
    (__nl_langinfo_l(GROUPING, (__c_locale)__loc)) : "";
}

const char *_Locale_true(struct _Locale_numeric *__loc)
{
  return __loc != 0 ? __nl_langinfo_l(YESSTR, (__c_locale)__loc) : "true";
}

const char *_Locale_false(struct _Locale_numeric *__loc)
{
  return __loc != 0 ? __nl_langinfo_l(NOSTR, (__c_locale)__loc) : "false";
}


/* Monetary */

const char *_Locale_int_curr_symbol(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? __nl_langinfo_l(INT_CURR_SYMBOL, (__c_locale)__loc) : 0;
}

const char *_Locale_currency_symbol(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? __nl_langinfo_l(CURRENCY_SYMBOL, (__c_locale)__loc) : 0;
}

char _Locale_mon_decimal_point(struct _Locale_monetary * __loc)
{
  return __loc != 0 ? *(__nl_langinfo_l(MON_DECIMAL_POINT,(__c_locale)__loc)) : '.';
}

char _Locale_mon_thousands_sep(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? *(__nl_langinfo_l(MON_THOUSANDS_SEP, (__c_locale)__loc)) : ',';
}

const char *_Locale_mon_grouping(struct _Locale_monetary *__loc)
{
  return (__loc != 0 && _Locale_mon_thousands_sep( __loc ) != '\0' ) ?
    __nl_langinfo_l(MON_GROUPING, (__c_locale)__loc) : _empty_str;
}

const char *_Locale_positive_sign(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? __nl_langinfo_l(POSITIVE_SIGN, (__c_locale)__loc) : _empty_str;
}

const char *_Locale_negative_sign(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? __nl_langinfo_l(NEGATIVE_SIGN, (__c_locale)__loc) : _empty_str;
}

char _Locale_int_frac_digits(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? *(__nl_langinfo_l(INT_FRAC_DIGITS, (__c_locale)__loc)) : CHAR_MAX;
}

char _Locale_frac_digits(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? *(__nl_langinfo_l(FRAC_DIGITS, (__c_locale)__loc)) : CHAR_MAX;
}

/* 1 if currency_symbol precedes a positive value, 0 if succeeds */
int _Locale_p_cs_precedes(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? *(__nl_langinfo_l(P_CS_PRECEDES, (__c_locale)__loc)) : CHAR_MAX;
}

/* 1 if a space separates currency_symbol from a positive value. */
int _Locale_p_sep_by_space(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? *(__nl_langinfo_l(P_SEP_BY_SPACE, (__c_locale)__loc)) : CHAR_MAX;
}

/*
 * 0 Parentheses surround the quantity and currency_symbol
 * 1 The sign string precedes the quantity and currency_symbol
 * 2 The sign string succeeds the quantity and currency_symbol.
 * 3 The sign string immediately precedes the currency_symbol.
 * 4 The sign string immediately succeeds the currency_symbol.
 */
int _Locale_p_sign_posn(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? *(__nl_langinfo_l(P_SIGN_POSN, (__c_locale)__loc)) : CHAR_MAX;
}

/* 1 if currency_symbol precedes a negative value, 0 if succeeds */
int _Locale_n_cs_precedes(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? *(__nl_langinfo_l(N_CS_PRECEDES, (__c_locale)__loc)) : CHAR_MAX;
}

/* 1 if a space separates currency_symbol from a negative value. */
int _Locale_n_sep_by_space(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? *(__nl_langinfo_l(N_SEP_BY_SPACE, (__c_locale)__loc)) : CHAR_MAX;
}

/*
 * 0 Parentheses surround the quantity and currency_symbol
 * 1 The sign string precedes the quantity and currency_symbol
 * 2 The sign string succeeds the quantity and currency_symbol.
 * 3 The sign string immediately precedes the currency_symbol.
 * 4 The sign string immediately succeeds the currency_symbol.
 */
int _Locale_n_sign_posn(struct _Locale_monetary *__loc)
{
  return __loc != 0 ? *(__nl_langinfo_l(N_SIGN_POSN, (__c_locale)__loc)) : CHAR_MAX;
}


/* Time */
const char *_Locale_full_monthname(struct _Locale_time *__loc, int _m )
{
  return (__loc != 0 && _m >= 0 && _m < 12) ? __nl_langinfo_l(MON_1 + _m, (__c_locale)__loc) : 0;
}

const char *_Locale_abbrev_monthname(struct _Locale_time *__loc, int _m )
{
  return (__loc != 0 && _m >= 0 && _m < 12) ? __nl_langinfo_l(ABMON_1 + _m, (__c_locale)__loc) : 0;
}

const char *_Locale_full_dayofweek(struct _Locale_time *__loc, int _d )
{
  return (__loc != 0 && _d >= 0 && _d < 7) ? __nl_langinfo_l(DAY_1 + _d, (__c_locale)__loc) : 0;
}

const char *_Locale_abbrev_dayofweek(struct _Locale_time *__loc, int _d )
{
  return (__loc != 0 && _d >= 0 && _d < 7) ? __nl_langinfo_l(ABDAY_1 + _d, (__c_locale)__loc) : 0;
}

const char *_Locale_d_t_fmt(struct _Locale_time *__loc)
{
  return __loc != 0 ? __nl_langinfo_l(D_T_FMT, (__c_locale)__loc) : 0;
}

const char *_Locale_d_fmt(struct _Locale_time *__loc )
{
  return __loc != 0 ? __nl_langinfo_l(D_FMT, (__c_locale)__loc) : 0;
}

const char *_Locale_t_fmt(struct _Locale_time *__loc )
{
  return __loc != 0 ? __nl_langinfo_l(T_FMT, (__c_locale)__loc) : 0;
}

const char *_Locale_long_d_t_fmt(struct _Locale_time *__loc )
{
  return __loc != 0 ? __nl_langinfo_l(ERA_D_T_FMT, (__c_locale)__loc) : 0;
}

const char *_Locale_long_d_fmt(struct _Locale_time *__loc )
{
  return __loc != 0 ? __nl_langinfo_l(ERA_D_FMT, (__c_locale)__loc) : 0;
}

const char *_Locale_am_str(struct _Locale_time *__loc )
{
  return __loc != 0 ? __nl_langinfo_l(AM_STR, (__c_locale)__loc) : _empty_str;
}

const char *_Locale_pm_str(struct _Locale_time* __loc )
{
  return __loc != 0 ? __nl_langinfo_l(PM_STR, (__c_locale)__loc) : _empty_str;
}

const char *_Locale_t_fmt_ampm(struct _Locale_time *__loc )
{
  return __loc != 0 ? __nl_langinfo_l(T_FMT_AMPM, (__c_locale)__loc) : 0;
}

/* Messages */

nl_catd_type _Locale_catopen(struct _Locale_messages *__loc, const char *__cat_name )
{
  return catopen( __cat_name, NL_CAT_LOCALE );
}

void _Locale_catclose(struct _Locale_messages *__loc, nl_catd_type __cat )
{
  catclose( __cat );
}

const char *_Locale_catgets(struct _Locale_messages *__loc, nl_catd_type __cat,
                            int __setid, int __msgid, const char *dfault)
{
  return catgets( __cat, __setid, __msgid, dfault );
}
