
#include <locale.h>
#include <langinfo.h>

#include <stl/c_locale.h>
#include <stdio.h>
#include <wctype.h>
#include <string.h>

#include <stdint.h>

#if (__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ > 2))
# define __nl_langinfo_l nl_langinfo_l
#endif

#if (__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ > 2))
#  define __LOCALE_CREATE(nm,category) newlocale(1 << category, nm, NULL )
#  define __LOCALE_DESTROY(__loc)      freelocale(__loc)
#else
#  define __LOCALE_CREATE(nm,category) __newlocale(1 << category, nm, NULL )
#  define __LOCALE_DESTROY(__loc)      __freelocale(__loc)
#endif

static const char *_empty_str = "";
static const char *_C_name = "C";

typedef struct _Named_locale {
  __locale_t __loc;
  char *__name;
} _Named_locale_t;

typedef struct _Locale_ctype {
  __locale_t __loc;
  char *__name;
  unsigned short __masks[256];
} L_ctype_t;

typedef struct _Locale_numeric {
  __locale_t __loc;
  char *__name;
} L_numeric_t;

typedef struct _Locale_time {
  __locale_t __loc;
  char *__name;
} L_time_t;

typedef struct _Locale_collate {
  __locale_t __loc;
  char *__name;
} L_collate_t;

typedef struct _Locale_monetary {
  __locale_t __loc;
  char *__name;
} L_monetary_t;

typedef struct _Locale_messages {
  __locale_t __loc;
  char *__name;
} L_messages_t;

void _Locale_init()
{}

void _Locale_final()
{}

L_ctype_t* _Locale_ctype_create(const char *nm, struct _Locale_name_hint* hint) {
  int c;
  L_ctype_t *__ctype = (L_ctype_t*)malloc(sizeof(L_ctype_t));
  if (!__ctype) return __ctype;
  memset(__ctype, 0, sizeof(L_ctype_t));
  __ctype->__name = malloc(strlen(nm) + 1);
  if (!__ctype->__name) { free(__ctype); return NULL; }
  strcpy(__ctype->__name, nm);
  __ctype->__loc = __LOCALE_CREATE(nm, LC_CTYPE);
  if (__ctype->__loc == (__locale_t)0) { free(__ctype->__name); free(__ctype); return NULL; }

  for (c = 0; c != 256; ++c) {
    if (__isalpha_l(c, __ctype->__loc))
      __ctype->__masks[c] |= _Locale_ALPHA;
  
    if (__iscntrl_l(c, __ctype->__loc))
      __ctype->__masks[c] |= _Locale_CNTRL;

    if (__isdigit_l(c, __ctype->__loc))
      __ctype->__masks[c] |= _Locale_DIGIT;

    if (__isprint_l(c, __ctype->__loc)) 
      __ctype->__masks[c] |= _Locale_PRINT;

    if (__ispunct_l(c, __ctype->__loc))
      __ctype->__masks[c] |= _Locale_PUNCT;

    if (__isspace_l(c, __ctype->__loc))
      __ctype->__masks[c] |= _Locale_SPACE;

    if (__isxdigit_l(c, __ctype->__loc))
      __ctype->__masks[c] |= _Locale_XDIGIT;

    if (__isupper_l(c, __ctype->__loc))
      __ctype->__masks[c] |= _Locale_UPPER;

    if (__islower_l(c, __ctype->__loc))
      __ctype->__masks[c] |= _Locale_LOWER;
  }


  return __ctype;
}
 
_Named_locale_t* _Locale_create(const char *nm, int category) {
  _Named_locale_t *__loc = (_Named_locale_t*)malloc(sizeof(_Named_locale_t));
  if (!__loc) return __loc;
  __loc->__name = malloc(strlen(nm) + 1);
  if (!__loc->__name) { free(__loc); return NULL; }
  strcpy(__loc->__name, nm);
  __loc->__loc = __LOCALE_CREATE(nm, category);
  if (__loc->__loc == (__locale_t)0) { free(__loc->__name); free(__loc); return NULL; }
  return __loc;
}

L_numeric_t* _Locale_numeric_create(const char *nm, struct _Locale_name_hint* hint)
{ return (L_numeric_t*)_Locale_create(nm, LC_NUMERIC); }

L_time_t* _Locale_time_create(const char *nm, struct _Locale_name_hint* hint)
{ return (L_time_t*)_Locale_create(nm, LC_TIME); }

L_collate_t* _Locale_collate_create(const char *nm, struct _Locale_name_hint* hint)
{ return (L_collate_t*)_Locale_create(nm, LC_COLLATE); }

L_monetary_t* _Locale_monetary_create(const char *nm, struct _Locale_name_hint* hint)
{ return (L_monetary_t*)_Locale_create(nm, LC_MONETARY); }

L_messages_t* _Locale_messages_create(const char *nm, struct _Locale_name_hint* hint)
{ return (L_messages_t*)_Locale_create(nm, LC_MESSAGES); }

/*
  try to see locale category LC should be used from environment;
  according POSIX, the order is
  1. LC_ALL
  2. category (LC_CTYPE, LC_NUMERIC, ... )
  3. LANG
  If set nothing, return "C" (this really implemetation-specific).
*/
const char *_Locale_aux_default( const char *LC, char *nm )
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

  return strcpy( nm, "C" );
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

char const*_Locale_ctype_name(const L_ctype_t *__ctype, char *buf)
{ return __ctype != 0 ? strncpy( buf, __ctype->__name, _Locale_MAX_SIMPLE_NAME ) : 0; }

char const*_Locale_numeric_name(const L_numeric_t *__num, char *buf)
{ return __num != 0 ? strncpy( buf, __num->__name, _Locale_MAX_SIMPLE_NAME ) : 0; }

char const*_Locale_time_name(const L_time_t *__time, char *buf)
{ return __time != 0 ? strncpy( buf, __time->__name, _Locale_MAX_SIMPLE_NAME ) : 0; }

char const*_Locale_collate_name(const L_collate_t *__col, char *buf)
{ return __col != 0 ? strncpy( buf, __col->__name, _Locale_MAX_SIMPLE_NAME ) : 0; }

char const*_Locale_monetary_name(const L_monetary_t *__mon, char *buf)
{ return __mon != 0 ? strncpy( buf, __mon->__name, _Locale_MAX_SIMPLE_NAME ) : 0; }

char const*_Locale_messages_name(const L_messages_t *__mes, char *buf)
{ return __mes != 0 ? strncpy( buf, __mes->__name, _Locale_MAX_SIMPLE_NAME ) : 0; }

void _Locale_ctype_destroy(L_ctype_t *__ctype) {
  __LOCALE_DESTROY(__ctype->__loc);
  free(__ctype->__name);
  free(__ctype);
}

void _Locale_destroy(_Named_locale_t *__loc) {
  __LOCALE_DESTROY(__loc->__loc);
  free(__loc->__name);
  free(__loc);
}

void _Locale_numeric_destroy(L_numeric_t *__num)
{ _Locale_destroy((_Named_locale_t*)__num); }

void _Locale_time_destroy(L_time_t *__time)
{ _Locale_destroy((_Named_locale_t*)__time); }

void _Locale_collate_destroy(L_collate_t *__col)
{ _Locale_destroy((_Named_locale_t*)__col); }

void _Locale_monetary_destroy(L_monetary_t *__mon)
{ _Locale_destroy((_Named_locale_t*)__mon); }

void _Locale_messages_destroy(L_messages_t* __mes)
{ _Locale_destroy((_Named_locale_t*)__mes); }

/*
 * locale loc expected either locale name indeed (platform-specific)
 * or string like "LC_CTYPE=LocaleNameForCType;LC_NUMERIC=LocaleNameForNum;"
 *
 */

char const*__Extract_locale_name( const char *loc, const char *category, char *buf )
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

struct _Locale_name_hint* _Locale_get_ctype_hint(L_ctype_t* ctype)
{ return 0; }
struct _Locale_name_hint* _Locale_get_numeric_hint(L_numeric_t* numeric)
{ return 0; }
struct _Locale_name_hint* _Locale_get_time_hint(L_time_t* time)
{ return 0; }
struct _Locale_name_hint* _Locale_get_collate_hint(L_collate_t* collate)
{ return 0; }
struct _Locale_name_hint* _Locale_get_monetary_hint(L_monetary_t* monetary)
{ return 0; }
struct _Locale_name_hint* _Locale_get_messages_hint(L_messages_t* messages)
{ return 0; }

/* ctype */

const _Locale_mask_t *_Locale_ctype_table(L_ctype_t *__ctype)
{
  /* return table with masks (upper, lower, alpha, etc.) */
  _STLP_STATIC_ASSERT( sizeof(_Locale_mask_t) == sizeof(__ctype->__masks[0]) )
  return __ctype->__masks;
}

int _Locale_toupper(L_ctype_t *__ctype, int c )
{ return __toupper_l(c, __ctype->__loc); }

int _Locale_tolower(L_ctype_t *__ctype, int c )
{ return __tolower_l(c, __ctype->__loc); }

#if !defined (_STLP_NO_WCHAR_T)
_Locale_mask_t _Locale_wchar_ctype(L_ctype_t *__ctype, wint_t wc, _Locale_mask_t __mask )
{
  _Locale_mask_t ret = 0;
  if ( (__mask & _Locale_ALPHA) != 0 && iswalpha_l(wc, __ctype->__loc))
    ret |= _Locale_ALPHA;
  
  if ( (__mask & _Locale_CNTRL) != 0 && iswcntrl_l(wc, __ctype->__loc))
    ret |= _Locale_CNTRL;

  if ( (__mask & _Locale_DIGIT) != 0 && iswdigit_l(wc, __ctype->__loc))
    ret |= _Locale_DIGIT;

  if ( (__mask & _Locale_PRINT) != 0 && iswprint_l(wc, __ctype->__loc)) 
    ret |= _Locale_PRINT;

  if ( (__mask & _Locale_PUNCT) != 0 && iswpunct_l(wc, __ctype->__loc))
    ret |= _Locale_PUNCT;

  if ( (__mask & _Locale_SPACE) != 0 && iswspace_l(wc, __ctype->__loc))
    ret |= _Locale_SPACE;

  if ( (__mask & _Locale_XDIGIT) != 0 && iswxdigit_l(wc, __ctype->__loc))
    ret |= _Locale_XDIGIT;

  if ( (__mask & _Locale_UPPER) != 0 && iswupper_l(wc, __ctype->__loc))
    ret |= _Locale_UPPER;

  if ( (__mask & _Locale_LOWER) != 0 && iswlower_l(wc, __ctype->__loc))
    ret |= _Locale_LOWER;

  return ret;
}

wint_t _Locale_wchar_tolower( L_ctype_t *__ctype, wint_t c )
{
  return __towlower_l( c, __ctype->__loc);
}

wint_t _Locale_wchar_toupper( L_ctype_t *__ctype, wint_t c )
{
  return __towupper_l( c, __ctype->__loc);
}
#endif

#if !defined (_STLP_NO_MBSTATE_T)

int _Locale_mb_cur_max( L_ctype_t * __DUMMY_PAR) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return 0;
}

int _Locale_mb_cur_min( L_ctype_t * __DUMMY_PAR) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return 0;
}

int _Locale_is_stateless( L_ctype_t * __DUMMY_PAR) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return 1;
}

#if !defined (_STLP_NO_WCHAR_T)
wint_t _Locale_btowc(L_ctype_t *__ctype, int c) {
  wint_t _c;
  /* __c_locale __tmp = __uselocale( __loc ); */
  _c = btowc( c );
  /* __uselocale( __tmp ); */
  return _c;
}

int _Locale_wctob(L_ctype_t *__loc, wint_t c) {
  int _c;
  /* __c_locale __tmp = __uselocale( __loc ); */
  _c = wctob( c );
  /* __uselocale( __tmp ); */
  return _c;
}

size_t _Locale_mbtowc(L_ctype_t *__DUMMY_PAR1,
                      wchar_t *__DUMMY_PAR2,
                      const char *__DUMMY_PAR3, size_t __DUMMY_PAR4,
                      mbstate_t *__DUMMY_PAR5) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return (size_t) -1;
}

size_t _Locale_wctomb(L_ctype_t *__DUMMY_PAR1,
                      char *__DUMMY_PAR2, size_t __DUMMY_PAR3,
                      const wchar_t __DUMMY_PAR4,
                      mbstate_t *__DUMMY_PAR5) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return (size_t) -1;
}
#endif

size_t _Locale_unshift(L_ctype_t *__DUMMY_PAR1,
                       mbstate_t *__DUMMY_PAR2,
                       char *__DUMMY_PAR3, size_t __DUMMY_PAR4, char ** __DUMMY_PAR5) {
  printf( "%s:%d\n", __FILE__, __LINE__ );
  return (size_t) -1;
}

#endif /*  _STLP_NO_MBSTATE_T */

/* Collate */
int _Locale_strcmp(L_collate_t * __col,
                   const char *s1, size_t n1, const char *s2, size_t n2) {
  return __strcoll_l( s1, s2, __col->__loc);
#if 0
  int ret;
  int minN = n1 < n2 ? n1 : n2;
  ret = strncmp(s1, s2, minN);
  if ( ret == 0 ) {
    return n1 < n2 ? -1 : (n1 > n2 ? 1 : 0);
  }
  return ret;
#endif
}

#if !defined (_STLP_NO_WCHAR_T)
int _Locale_strwcmp( L_collate_t *__col,
                     const wchar_t *s1, size_t n1,
                     const wchar_t *s2, size_t n2) {
  return __wcscoll_l( s1, s2, __col->__loc);
#if 0
  int ret;
  int minN = n1 < n2 ? n1 : n2;
  ret = wcsncmp( s1, s2, minN );
  if ( ret == 0 ) {
    return n1 < n2 ? -1 : (n1 > n2 ? 1 : 0);
  }
  return ret;
#endif
}

#endif

size_t _Locale_strxfrm(L_collate_t *__col,
                       char *dest, size_t dest_n,
                       const char *src, size_t src_n )
{
  size_t n;

  n = __strxfrm_l(dest, src, dest_n, __col->__loc);

  return n > src_n ? (size_t)-1 : n; /* dest[n] = 0? */
}

# ifndef _STLP_NO_WCHAR_T

size_t _Locale_strwxfrm(L_collate_t *__col,
                        wchar_t *dest, size_t dest_n,
                        const wchar_t *src, size_t src_n )
{
  size_t n;

  n = __wcsxfrm_l( dest, src, dest_n, __col->__loc);

  return n > src_n ? (size_t)-1 : n; /* dest[n] = 0? */
}

# endif

/* Numeric */

char _Locale_decimal_point(L_numeric_t *__num)
{
  return (__num != 0) ? *(__nl_langinfo_l(RADIXCHAR, __num->__loc)) : '.';
}

char _Locale_thousands_sep(L_numeric_t *__num)
{
  return (__num != 0) ? *(__nl_langinfo_l(THOUSEP, __num->__loc)) : ',';
}

const char* _Locale_grouping(L_numeric_t *__num)
{
  return (__num != 0 && _Locale_thousands_sep(__num) != '\0' ) ?
    (__nl_langinfo_l(GROUPING, __num->__loc)) : "";
}

const char *_Locale_true(L_numeric_t *__num)
{
  return __num != 0 ? __nl_langinfo_l(YESSTR, __num->__loc) : "true";
}

const char *_Locale_false(L_numeric_t *__num)
{
  return __num != 0 ? __nl_langinfo_l(NOSTR, __num->__loc) : "false";
}


/* Monetary */

const char *_Locale_int_curr_symbol(L_monetary_t *__mon)
{
  return __mon != 0 ? __nl_langinfo_l(INT_CURR_SYMBOL, __mon->__loc) : 0;
}

const char *_Locale_currency_symbol(L_monetary_t *__mon)
{
  return __mon != 0 ? __nl_langinfo_l(CURRENCY_SYMBOL, __mon->__loc) : 0;
}

char _Locale_mon_decimal_point(L_monetary_t * __mon)
{
  return __mon != 0 ? *(__nl_langinfo_l(MON_DECIMAL_POINT, __mon->__loc)) : '.';
}

char _Locale_mon_thousands_sep(L_monetary_t *__mon)
{
  return __mon != 0 ? *(__nl_langinfo_l(MON_THOUSANDS_SEP, __mon->__loc)) : ',';
}

const char *_Locale_mon_grouping(L_monetary_t *__mon)
{
  return (__mon != 0 && _Locale_mon_thousands_sep( __mon ) != '\0' ) ?
    __nl_langinfo_l(MON_GROUPING, __mon->__loc) : _empty_str;
}

const char *_Locale_positive_sign(L_monetary_t *__mon)
{
  return __mon != 0 ? __nl_langinfo_l(POSITIVE_SIGN, __mon->__loc) : _empty_str;
}

const char *_Locale_negative_sign(L_monetary_t *__mon)
{
  return __mon != 0 ? __nl_langinfo_l(NEGATIVE_SIGN, __mon->__loc) : _empty_str;
}

char _Locale_int_frac_digits(L_monetary_t *__mon)
{
  return __mon != 0 ? *(__nl_langinfo_l(INT_FRAC_DIGITS, __mon->__loc)) : CHAR_MAX;
}

char _Locale_frac_digits(L_monetary_t *__mon)
{
  return __mon != 0 ? *(__nl_langinfo_l(FRAC_DIGITS, __mon->__loc)) : CHAR_MAX;
}

/* 1 if currency_symbol precedes a positive value, 0 if succeeds */
int _Locale_p_cs_precedes(L_monetary_t *__mon)
{
  return __mon != 0 ? *(__nl_langinfo_l(P_CS_PRECEDES, __mon->__loc)) : CHAR_MAX;
}

/* 1 if a space separates currency_symbol from a positive value. */
int _Locale_p_sep_by_space(L_monetary_t *__mon)
{
  return __mon != 0 ? *(__nl_langinfo_l(P_SEP_BY_SPACE, __mon->__loc)) : CHAR_MAX;
}

/*
 * 0 Parentheses surround the quantity and currency_symbol
 * 1 The sign string precedes the quantity and currency_symbol
 * 2 The sign string succeeds the quantity and currency_symbol.
 * 3 The sign string immediately precedes the currency_symbol.
 * 4 The sign string immediately succeeds the currency_symbol.
 */
int _Locale_p_sign_posn(L_monetary_t *__mon)
{
  return __mon != 0 ? *(__nl_langinfo_l(P_SIGN_POSN, __mon->__loc)) : CHAR_MAX;
}

/* 1 if currency_symbol precedes a negative value, 0 if succeeds */
int _Locale_n_cs_precedes(L_monetary_t *__mon)
{
  return __mon != 0 ? *(__nl_langinfo_l(N_CS_PRECEDES, __mon->__loc)) : CHAR_MAX;
}

/* 1 if a space separates currency_symbol from a negative value. */
int _Locale_n_sep_by_space(L_monetary_t *__mon)
{
  return __mon != 0 ? *(__nl_langinfo_l(N_SEP_BY_SPACE, __mon->__loc)) : CHAR_MAX;
}

/*
 * 0 Parentheses surround the quantity and currency_symbol
 * 1 The sign string precedes the quantity and currency_symbol
 * 2 The sign string succeeds the quantity and currency_symbol.
 * 3 The sign string immediately precedes the currency_symbol.
 * 4 The sign string immediately succeeds the currency_symbol.
 */
int _Locale_n_sign_posn(L_monetary_t *__mon)
{
  return __mon != 0 ? *(__nl_langinfo_l(N_SIGN_POSN, __mon->__loc)) : CHAR_MAX;
}


/* Time */
const char *_Locale_full_monthname(L_time_t *__time, int _m )
{
  return (__time != 0 && _m >= 0 && _m < 12) ? __nl_langinfo_l(MON_1 + _m, __time->__loc) : 0;
}

const char *_Locale_abbrev_monthname(L_time_t *__time, int _m )
{
  return (__time != 0 && _m >= 0 && _m < 12) ? __nl_langinfo_l(ABMON_1 + _m, __time->__loc) : 0;
}

const char *_Locale_full_dayofweek(L_time_t *__time, int _d )
{
  return (__time != 0 && _d >= 0 && _d < 7) ? __nl_langinfo_l(DAY_1 + _d, __time->__loc) : 0;
}

const char *_Locale_abbrev_dayofweek(L_time_t *__time, int _d )
{
  return (__time != 0 && _d >= 0 && _d < 7) ? __nl_langinfo_l(ABDAY_1 + _d, __time->__loc) : 0;
}

const char *_Locale_d_t_fmt(L_time_t *__time)
{
  return __time != 0 ? __nl_langinfo_l(D_T_FMT, __time->__loc) : 0;
}

const char *_Locale_d_fmt(L_time_t *__time )
{
  return __time != 0 ? __nl_langinfo_l(D_FMT, __time->__loc) : 0;
}

const char *_Locale_t_fmt(L_time_t *__time )
{
  return __time != 0 ? __nl_langinfo_l(T_FMT, __time->__loc) : 0;
}

const char *_Locale_long_d_t_fmt(L_time_t *__time )
{
  return __time != 0 ? __nl_langinfo_l(ERA_D_T_FMT, __time->__loc) : 0;
}

const char *_Locale_long_d_fmt(L_time_t *__time )
{
  return __time != 0 ? __nl_langinfo_l(ERA_D_FMT, __time->__loc) : 0;
}

const char *_Locale_am_str(L_time_t *__time )
{
  return __time != 0 ? __nl_langinfo_l(AM_STR, __time->__loc) : _empty_str;
}

const char *_Locale_pm_str(L_time_t *__time )
{
  return __time != 0 ? __nl_langinfo_l(PM_STR, __time->__loc) : _empty_str;
}

const char *_Locale_t_fmt_ampm(L_time_t *__time )
{
  return __time != 0 ? __nl_langinfo_l(T_FMT_AMPM, __time->__loc) : 0;
}

/* Messages */

nl_catd_type _Locale_catopen(L_messages_t *__loc, const char *__cat_name )
{
  return catopen( __cat_name, NL_CAT_LOCALE );
}

void _Locale_catclose(L_messages_t *__loc, nl_catd_type __cat )
{
  catclose( __cat );
}

const char *_Locale_catgets(L_messages_t *__loc, nl_catd_type __cat,
                            int __setid, int __msgid, const char *dfault)
{
  return catgets( __cat, __setid, __msgid, dfault );
}
