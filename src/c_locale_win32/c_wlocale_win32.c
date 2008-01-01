/*
 * Copyright (c) 2007 2008
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

static const wchar_t* __wtrue_name = L"true";
static const wchar_t* __wfalse_name = L"false";

wchar_t _WLocale_decimal_point(_Locale_numeric_t* lnum)
{
  wchar_t buf[4];
  GetLocaleInfoW(lnum->lc.id, LOCALE_SDECIMAL, buf, 4);
  return buf[0];
}

wchar_t _WLocale_thousands_sep(_Locale_numeric_t* lnum)
{
  wchar_t buf[4];
  GetLocaleInfoW(lnum->lc.id, LOCALE_STHOUSAND, buf, 4);
  return buf[0];
}

const wchar_t * _WLocale_true(_Locale_numeric_t* lnum, wchar_t* buf, size_t bufSize)
{ return __wtrue_name; }

const wchar_t * _WLocale_false(_Locale_numeric_t* lnum, wchar_t* buf, size_t bufSize)
{ return __wfalse_name; }

/* Monetary */
const wchar_t* _WLocale_int_curr_symbol(_Locale_monetary_t * lmon, wchar_t* buf, size_t bufSize)
{ GetLocaleInfoW(lmon->lc.id, LOCALE_SINTLSYMBOL, buf, (int)bufSize); return buf; }

const wchar_t* _WLocale_currency_symbol(_Locale_monetary_t * lmon, wchar_t* buf, size_t bufSize)
{ GetLocaleInfoW(lmon->lc.id, LOCALE_SCURRENCY, buf, (int)bufSize); return buf; }

wchar_t _WLocale_mon_decimal_point(_Locale_monetary_t * lmon)
{ return lmon->decimal_point[0]; }

wchar_t _WLocale_mon_thousands_sep(_Locale_monetary_t * lmon)
{ return lmon->thousands_sep[0]; }

const wchar_t* _WLocale_positive_sign(_Locale_monetary_t * lmon, wchar_t* buf, size_t bufSize)
{ GetLocaleInfoW(lmon->lc.id, LOCALE_SPOSITIVESIGN, buf, (int)bufSize); return buf; }

const wchar_t* _WLocale_negative_sign(_Locale_monetary_t * lmon, wchar_t* buf, size_t bufSize)
{ GetLocaleInfoW(lmon->lc.id, LOCALE_SNEGATIVESIGN, buf, (int)bufSize); return buf; }

/* Time */
const wchar_t * _WLocale_full_monthname(_Locale_time_t * ltime, int month,
                                        wchar_t* buf, size_t bufSize)
{ GetLocaleInfoW(ltime->lc.id, LOCALE_SMONTHNAME1 + month, buf, (int)bufSize); return buf; }

const wchar_t * _WLocale_abbrev_monthname(_Locale_time_t * ltime, int month,
                                          wchar_t* buf, size_t bufSize)
{ GetLocaleInfoW(ltime->lc.id, LOCALE_SABBREVMONTHNAME1 + month, buf, (int)bufSize); return buf; }

const wchar_t * _WLocale_full_dayofweek(_Locale_time_t * ltime, int day,
                                        wchar_t* buf, size_t bufSize)
{ GetLocaleInfoW(ltime->lc.id, LOCALE_SDAYNAME1 + day, buf, (int)bufSize); return buf; }

const wchar_t * _WLocale_abbrev_dayofweek(_Locale_time_t * ltime, int day,
                                          wchar_t* buf, size_t bufSize)
{ GetLocaleInfoW(ltime->lc.id, LOCALE_SABBREVDAYNAME1 + day, buf, (int)bufSize); return buf; }

const wchar_t* _WLocale_am_str(_Locale_time_t* ltime,
                               wchar_t* buf, size_t bufSize)
{ GetLocaleInfoW(ltime->lc.id, LOCALE_S1159, buf, (int)bufSize); return buf; }

const wchar_t* _WLocale_pm_str(_Locale_time_t* ltime,
                               wchar_t* buf, size_t bufSize)
{ GetLocaleInfoW(ltime->lc.id, LOCALE_S2359, buf, (int)bufSize); return buf; }
