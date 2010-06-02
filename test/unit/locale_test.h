// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

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

#ifndef __TEST_LOCALE_TEST_H
#define __TEST_LOCALE_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

#include <string>
#include <iosfwd>
#include <locale>

struct ref_monetary;
struct ref_locale;

class locale_test
{
  public:
    int EXAM_DECL(locale_by_name);
    int EXAM_DECL(moneypunct_by_name);
    int EXAM_DECL(time_by_name);
    int EXAM_DECL(numpunct_by_name);
    int EXAM_DECL(ctype_by_name);
    int EXAM_DECL(collate_by_name);
    int EXAM_DECL(messages_by_name);

    int EXAM_DECL(loc_has_facet);
    int EXAM_DECL(num_put_get);
    int EXAM_DECL(money_put_get);
    int EXAM_DECL(money_put_X_bug);
    int EXAM_DECL(time_put_get);
    int EXAM_DECL(collate_facet);
    int EXAM_DECL(ctype_facet);
    int EXAM_DECL(locale_init_problem);

    int EXAM_DECL(default_locale);
    int EXAM_DECL(combine);

  private:
    void _loc_has_facet( const std::locale& );
    void _num_put_get( const std::locale&, const ref_locale* );
    void _time_put_get( const std::locale& );
    void _ctype_facet( const std::locale& );
    void _ctype_facet_w( const std::locale& );
    void _locale_init_problem( const std::locale& );

    static const ref_monetary* _get_ref_monetary(size_t);
    static const char* _get_ref_monetary_name(const ref_monetary*);

    void _money_put_get( const std::locale&, const ref_monetary* );
    void _money_put_get2( const std::locale& loc, const std::locale& streamLoc, const ref_monetary* );
    void _money_put_X_bug( const std::locale&, const ref_monetary* );
};

#endif // __TEST_EXCEPTION_TEST_H
