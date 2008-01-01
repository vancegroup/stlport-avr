
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

static wchar_t* _ToWChar(const char* buf, wchar_t *wbuf, size_t wbufSize) {
  wchar_t *wcur = wbuf;
  wchar_t *wend = wbuf + wbufSize - 1;
  for (; wcur != wend && *buf != 0; ++buf, ++wcur)
    *wcur = *buf;
  *wcur = 0;
  return wbuf;
}

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

struct _Locale_ctype *_Locale_ctype_create(const char *nm, struct _Locale_name_hint* hint,
                                           int *__err_code) {
  *__err_code = _STLP_LOC_UNKNOWN_NAME;
  return (struct _Locale_ctype*)__LOCALE_CREATE( nm, LC_CTYPE );
}

struct _Locale_codecvt *_Locale_codecvt_create(const char *nm, struct _Locale_name_hint* hint,
                                               int *__err_code) {
  // Glibc do not support multibyte manipulation for the moment, it simply implements "C".
  if (nm[0] == 'C' && nm[1] == 0)
  { return (struct _Locale_codecvt*)0x01; }
  *__err_code = _STLP_LOC_NO_PLATFORM_SUPPORT; return 0;
}

struct _Locale_numeric *_Locale_numeric_create(const char *nm, struct _Locale_name_hint* hint,
                                               int *__err_code) {
  *__err_code = _STLP_LOC_UNKNOWN_NAME;
  return (struct _Locale_numeric*)__LOCALE_CREATE( nm, LC_NUMERIC );
}
  
struct _Locale_time *_Locale_time_create(const char *nm, struct _Locale_name_hint* hint,
                                         int *__err_code) {
  *__err_code = _STLP_LOC_UNKNOWN_NAME;
  return (struct _Locale_time*)__LOCALE_CREATE( nm, LC_TIME );
}

struct _Locale_collate *_Locale_collate_create(const char *nm, struct _Locale_name_hint* hint,
                                               int *__err_code) {
  *__err_code = _STLP_LOC_UNKNOWN_NAME;
  return (struct _Locale_collate*)__LOCALE_CREATE( nm, LC_COLLATE );
}

struct _Locale_monetary *_Locale_monetary_create(const char *nm, struct _Locale_name_hint* hint,
                                                 int *__err_code) {
  *__err_code = _STLP_LOC_UNKNOWN_NAME;
  return (struct _Locale_monetary*)__LOCALE_CREATE( nm, LC_MONETARY );
}

struct _Locale_messages *_Locale_messages_create(const char *nm, struct _Locale_name_hint* hint,
                                                 int *__err_code) {
  *__err_code = _STLP_LOC_UNKNOWN_NAME;
  return (struct _Locale_messages*)__LOCALE_CREATE( nm, LC_MESSAGES );
}

/*
  try to see locale category LC should be used from environment;
  according POSIX, the order is
  1. LC_ALL
  2. category (LC_CTYPE, LC_NUMERIC, ... )
  3. LANG
  If set nothing, return "C" (this really implementation-specific).
*/
static const char *_Locale_aux_default( const char *LC, char *nm )
{
  char *name = getenv( "LC_ALL" );

  if ( name != NULL && *name != 0 ) {
    return name;
  }
  name = getenv( LC );
  if ( name != NULL && *name != 0 ) {
    return name;
  }
  name = getenv( "LANG" );
  if ( name != NULL && *name != 0 ) {
    return name;
  }

  return _C_name;
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
  return ((__c_locale)__loc)->__names[LC_CTYPE];
}

char const*_Locale_codecvt_name( const struct _Locale_codecvt *__loc, char *buf )
{
  return _C_name;
}

char const*_Locale_numeric_name( const struct _Locale_numeric *__loc, char *buf )
{
  return ((__c_locale)__loc)->__names[LC_NUMERIC];
}

char const*_Locale_time_name( const struct _Locale_time *__loc, char *buf )
{
  return ((__c_locale)__loc)->__names[LC_TIME];
}

char const*_Locale_collate_name( const struct _Locale_collate *__loc, char *buf )
{
  return ((__c_locale)__loc)->__names[LC_COLLATE];
}

char const*_Locale_monetary_name( const struct _Locale_monetary *__loc, char *buf )
{
  return ((__c_locale)__loc)->__names[LC_MONETARY];
}

char const*_Locale_messages_name( const struct _Locale_messages *__loc, char *buf )
{
  return ((__c_locale)__loc)->__names[LC_MESSAGES];
}

void _Locale_ctype_destroy( struct _Locale_ctype *__loc )
{ __LOCALE_DESTROY(__loc); }

void _Locale_codecvt_destroy( struct _Locale_codecvt *__loc )
{}

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

  if( loc[0]=='L' && loc[1]=='C' && loc[2]=='_') {
    expr = strstr( (char*)loc, category );
    if ( expr == NULL )
      return NULL; /* Category not found. */
    ++expr;
    len_name = strcspn( expr, ";" );
    len_name = len_name >= _Locale_MAX_SIMPLE_NAME ? _Locale_MAX_SIMPLE_NAME - 1 : len_name;
    strncpy( buf, expr, len_name );
    buf[len_name] = 0;
    return buf;
  }
  return loc;
}

char const*_Locale_extract_ctype_name(const char *loc, char *buf,
                                      struct _Locale_name_hint* hint, int *__err_code)
{ return __Extract_locale_name( loc, "LC_CTYPE=", buf ); }

char const*_Locale_extract_numeric_name(const char *loc, char *buf,
                                        struct _Locale_name_hint* hint, int *__err_code)
{ return __Extract_locale_name( loc, "LC_NUMERIC=", buf ); }

char const*_Locale_extract_time_name(const char *loc, char *buf,
                                     struct _Locale_name_hint* hint, int *__err_code)
{ return __Extract_locale_name( loc, "LC_TIME=", buf ); }

char const*_Locale_extract_collate_name(const char *loc, char *buf,
                                        struct _Locale_name_hint* hint, int *__err_code)
{ return __Extract_locale_name( loc, "LC_COLLATE=", buf ); }

char const*_Locale_extract_monetary_name(const char *loc, char *buf,
                                         struct _Locale_name_hint* hint, int *__err_code)
{ return __Extract_locale_name( loc, "LC_MONETARY=", buf ); }

char const*_Locale_extract_messages_name(const char *loc, char *buf,
                                         struct _Locale_name_hint* hint, int *__err_code)
{ return __Extract_locale_name( loc, "LC_MESSAGES=", buf ); }

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
_Locale_mask_t _WLocale_ctype( struct _Locale_ctype *__loc, wint_t wc, _Locale_mask_t __mask )
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

wint_t _WLocale_tolower( struct _Locale_ctype *__loc, wint_t c )
{
  return towlower_l( c, ((__c_locale)__loc) );
}

wint_t _WLocale_toupper( struct _Locale_ctype *__loc, wint_t c )
{
  return towupper_l( c, ((__c_locale)__loc) );
}
#endif

int _WLocale_mb_cur_max( struct _Locale_codecvt * lcodecvt) { return 1; }
int _WLocale_mb_cur_min( struct _Locale_codecvt * lcodecvt) { return 1; }
int _WLocale_is_stateless( struct _Locale_codecvt * lcodecvt) { return 1; }

#if !defined (_STLP_NO_WCHAR_T)
size_t _WLocale_mbtowc(struct _Locale_codecvt *lcodecvt,
                       wchar_t *to,
                       const char *from, size_t n,
                       mbstate_t *st)
{ *to = *from; return 1; }

size_t _WLocale_wctomb(struct _Locale_codecvt *lcodecvt,
                       char *to, size_t n,
                       const wchar_t c,
                       mbstate_t *st)
{ *to = (char)c; return 1; }
#endif

size_t _WLocale_unshift(struct _Locale_codecvt *lcodecvt,
                        mbstate_t *st,
                        char *buf, size_t n, char ** next)
{ *next = buf; return 0; }

/* Collate */
int _Locale_strcmp(struct _Locale_collate * __loc,
                   const char *s1, size_t n1,
		   const char *s2, size_t n2) {
  int ret = 0;
  char buf1[64], buf2[64];
  while (n1 > 0 || n2 > 0) {
    size_t bufsize1 = n1 < 63 ? n1 : 63;
    size_t bufsize2 = n2 < 63 ? n2 : 63;
    strncpy(buf1, s1, bufsize1); buf1[bufsize1] = 0;
    strncpy(buf2, s2, bufsize2); buf2[bufsize2] = 0;

    ret = strcoll_l(buf1, buf2, (__c_locale)__loc);
    if (ret != 0) return ret;
    s1 += bufsize1; n1 -= bufsize1;
    s2 += bufsize2; n2 -= bufsize2;
  }
  return ret;
}

#if !defined (_STLP_NO_WCHAR_T)
int _WLocale_strcmp(struct _Locale_collate *__loc,
                    const wchar_t *s1, size_t n1,
                    const wchar_t *s2, size_t n2) {
  int ret = 0;
  wchar_t buf1[64], buf2[64];
  while (n1 > 0 || n2 > 0) {
    size_t bufsize1 = n1 < 63 ? n1 : 63;
    size_t bufsize2 = n2 < 63 ? n2 : 63;
    wcsncpy(buf1, s1, bufsize1); buf1[bufsize1] = 0;
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
  const char *real_src;
  char *buf = NULL;
  size_t result;

  if (src_n == 0)
  {
    if (dest != NULL) dest[0] = 0;
    return 0;
  }
  if (src[src_n] != 0) {
    buf = malloc(src_n + 1);
    strncpy(buf, src, src_n);
    buf[src_n] = 0;
    real_src = buf;
  }
  else
    real_src = src;
  result = strxfrm_l(dest, real_src, dest_n, (__c_locale)__loc);
  if (buf != NULL) free(buf);
  return result;
}

# ifndef _STLP_NO_WCHAR_T

size_t _WLocale_strxfrm( struct _Locale_collate *__loc,
                        wchar_t *dest, size_t dest_n,
                        const wchar_t *src, size_t src_n )
{
  const wchar_t *real_src;
  wchar_t *buf = NULL;
  size_t result;

  if (src_n == 0)
  {
    if (dest != NULL) dest[0] = 0;
    return 0;
  }
  if (src[src_n] != 0) {
    buf = malloc((src_n + 1) * sizeof(wchar_t));
    wcsncpy(buf, src, src_n);
    buf[src_n] = 0;
    real_src = buf;
  }
  else
    real_src = src;
  result = wcsxfrm_l(dest, real_src, dest_n, (__c_locale)__loc);
  if (buf != NULL) free(buf);
  return result;
}

# endif

/* Numeric */

char _Locale_decimal_point(struct _Locale_numeric *__loc)
{
  return *(__nl_langinfo_l(RADIXCHAR, (__c_locale)__loc));
}

char _Locale_thousands_sep(struct _Locale_numeric *__loc)
{
  return *(__nl_langinfo_l(THOUSEP, (__c_locale)__loc));
}

const char* _Locale_grouping(struct _Locale_numeric *__loc)
{
  return (_Locale_thousands_sep(__loc) != 0 ) ? (__nl_langinfo_l(GROUPING, (__c_locale)__loc)) : _empty_str;
}

const char *_Locale_true(struct _Locale_numeric *__loc)
{
  return __nl_langinfo_l(YESSTR, (__c_locale)__loc);
}

const char *_Locale_false(struct _Locale_numeric *__loc)
{
  return __nl_langinfo_l(NOSTR, (__c_locale)__loc);
}

#ifndef _STLP_NO_WCHAR_T
wchar_t _WLocale_decimal_point(struct _Locale_numeric *__loc)
{ return (wchar_t)_Locale_decimal_point(__loc); }
wchar_t _WLocale_thousands_sep(struct _Locale_numeric *__loc)
{ return (wchar_t)_Locale_thousands_sep(__loc); }
const wchar_t *_WLocale_true(struct _Locale_numeric *__loc, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_true(__loc), buf, bufSize); }
const wchar_t *_WLocale_false(struct _Locale_numeric *__loc, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_false(__loc), buf, bufSize); }
#endif

/* Monetary */

const char *_Locale_int_curr_symbol(struct _Locale_monetary *__loc)
{
  return __nl_langinfo_l(INT_CURR_SYMBOL, (__c_locale)__loc);
}

const char *_Locale_currency_symbol(struct _Locale_monetary *__loc)
{
  return __nl_langinfo_l(CURRENCY_SYMBOL, (__c_locale)__loc);
}

char _Locale_mon_decimal_point(struct _Locale_monetary * __loc)
{
  return *(__nl_langinfo_l(MON_DECIMAL_POINT,(__c_locale)__loc));
}

char _Locale_mon_thousands_sep(struct _Locale_monetary *__loc)
{
  return *(__nl_langinfo_l(MON_THOUSANDS_SEP, (__c_locale)__loc));
}

#ifndef _STLP_NO_WCHAR_T
const wchar_t *_WLocale_int_curr_symbol(struct _Locale_monetary *__loc, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_int_curr_symbol(__loc), buf, bufSize); }
const wchar_t *_WLocale_currency_symbol(struct _Locale_monetary *__loc, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_currency_symbol(__loc), buf, bufSize); }
wchar_t _WLocale_mon_decimal_point(struct _Locale_monetary * __loc)
{ return (wchar_t)_Locale_mon_decimal_point(__loc); }
wchar_t _WLocale_mon_thousands_sep(struct _Locale_monetary * __loc)
{ return (wchar_t)_Locale_mon_thousands_sep(__loc); }
const wchar_t *_WLocale_positive_sign(struct _Locale_monetary *__loc, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_positive_sign(__loc), buf, bufSize); }
const wchar_t *_WLocale_negative_sign(struct _Locale_monetary *__loc, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_negative_sign(__loc), buf, bufSize); }
#endif

const char *_Locale_mon_grouping(struct _Locale_monetary *__loc)
{
  return (_Locale_mon_thousands_sep( __loc ) != 0 ) ? __nl_langinfo_l(MON_GROUPING, (__c_locale)__loc) : _empty_str;
}

const char *_Locale_positive_sign(struct _Locale_monetary *__loc)
{
  return __nl_langinfo_l(POSITIVE_SIGN, (__c_locale)__loc);
}

const char *_Locale_negative_sign(struct _Locale_monetary *__loc)
{
  return __nl_langinfo_l(NEGATIVE_SIGN, (__c_locale)__loc);
}

char _Locale_int_frac_digits(struct _Locale_monetary *__loc)
{
  return *(__nl_langinfo_l(INT_FRAC_DIGITS, (__c_locale)__loc));
}

char _Locale_frac_digits(struct _Locale_monetary *__loc)
{
  return *(__nl_langinfo_l(FRAC_DIGITS, (__c_locale)__loc));
}

/* 1 if currency_symbol precedes a positive value, 0 if succeeds */
int _Locale_p_cs_precedes(struct _Locale_monetary *__loc)
{
  return *(__nl_langinfo_l(P_CS_PRECEDES, (__c_locale)__loc));
}

/* 1 if a space separates currency_symbol from a positive value. */
int _Locale_p_sep_by_space(struct _Locale_monetary *__loc)
{
  return *(__nl_langinfo_l(P_SEP_BY_SPACE, (__c_locale)__loc));
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
  return *(__nl_langinfo_l(P_SIGN_POSN, (__c_locale)__loc));
}

/* 1 if currency_symbol precedes a negative value, 0 if succeeds */
int _Locale_n_cs_precedes(struct _Locale_monetary *__loc)
{
  return *(__nl_langinfo_l(N_CS_PRECEDES, (__c_locale)__loc));
}

/* 1 if a space separates currency_symbol from a negative value. */
int _Locale_n_sep_by_space(struct _Locale_monetary *__loc)
{
  return *(__nl_langinfo_l(N_SEP_BY_SPACE, (__c_locale)__loc));
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
  return *(__nl_langinfo_l(N_SIGN_POSN, (__c_locale)__loc));
}


/* Time */
const char *_Locale_full_monthname(struct _Locale_time *__loc, int _m )
{
  return __nl_langinfo_l(MON_1 + _m, (__c_locale)__loc);
}

const char *_Locale_abbrev_monthname(struct _Locale_time *__loc, int _m )
{
  return __nl_langinfo_l(ABMON_1 + _m, (__c_locale)__loc);
}

const char *_Locale_full_dayofweek(struct _Locale_time *__loc, int _d )
{
  return __nl_langinfo_l(DAY_1 + _d, (__c_locale)__loc);
}

const char *_Locale_abbrev_dayofweek(struct _Locale_time *__loc, int _d )
{
  return __nl_langinfo_l(ABDAY_1 + _d, (__c_locale)__loc);
}

const char *_Locale_d_t_fmt(struct _Locale_time *__loc)
{
  return __nl_langinfo_l(D_T_FMT, (__c_locale)__loc);
}

const char *_Locale_d_fmt(struct _Locale_time *__loc )
{
  return __nl_langinfo_l(D_FMT, (__c_locale)__loc);
}

const char *_Locale_t_fmt(struct _Locale_time *__loc )
{
  return __nl_langinfo_l(T_FMT, (__c_locale)__loc);
}

const char *_Locale_long_d_t_fmt(struct _Locale_time *__loc )
{
  return __nl_langinfo_l(ERA_D_T_FMT, (__c_locale)__loc);
}

const char *_Locale_long_d_fmt(struct _Locale_time *__loc )
{
  return __nl_langinfo_l(ERA_D_FMT, (__c_locale)__loc);
}

const char *_Locale_am_str(struct _Locale_time *__loc )
{
  return __nl_langinfo_l(AM_STR, (__c_locale)__loc);
}

const char *_Locale_pm_str(struct _Locale_time* __loc )
{
  return __nl_langinfo_l(PM_STR, (__c_locale)__loc);
}

#ifndef _STLP_NO_WCHAR_T
const wchar_t *_WLocale_full_monthname(struct _Locale_time *__loc, int _m, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_full_monthname(__loc, _m), buf, bufSize); }
const wchar_t *_WLocale_abbrev_monthname(struct _Locale_time *__loc, int _m, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_abbrev_monthname(__loc, _m), buf, bufSize); }
const wchar_t *_WLocale_full_dayofweek(struct _Locale_time *__loc, int _d, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_full_dayofweek(__loc, _d), buf, bufSize); }
const wchar_t *_WLocale_abbrev_dayofweek(struct _Locale_time *__loc, int _d, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_abbrev_dayofweek(__loc, _d), buf, bufSize); }
const wchar_t *_WLocale_am_str(struct _Locale_time *__loc, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_am_str(__loc), buf, bufSize); }
const wchar_t *_WLocale_pm_str(struct _Locale_time* __loc, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_pm_str(__loc), buf, bufSize); }
#endif

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
