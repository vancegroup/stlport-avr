/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
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
# include "stlport_prefix.h"

#include "locale_impl.h"
#include <locale>
#include <typeinfo>
#include <algorithm>

#include <stdexcept>

#include "c_locale.h"
#include "aligned_buffer.h"


#include "locale_impl.h"
#include <stl/_codecvt.h>
#include <stl/_collate.h>
#include <stl/_ctype.h>
#include <stl/_monetary.h>
#include "message_facets.h"

_STLP_BEGIN_NAMESPACE

inline bool is_C_locale_name (const char* name) {
  return ((name[0] == 'C') && (name[1] == 0));
}

size_t locale::id::_S_max = 39;

static void _Stl_loc_assign_ids();

static _Stl_aligned_buffer<_Locale_impl::Init> __Loc_init_buf;
_Refcount_Base _Locale_impl::Init::_S_count(0);

_Locale_impl::Init::Init() {
  if ( _S_count._M_incr() == 1 ) {
    _Locale_impl::_S_initialize();
  }
}

_Locale_impl::Init::~Init() {
  if ( _S_count._M_decr() == 0 ) {
    _S_uninitialize();
  }
}

_Locale_impl::_Locale_impl(const char* s) :
    _Refcount_Base(0),
    name(s),
    facets_vec()
{
  facets_vec.reserve( locale::id::_S_max );
  new (&__Loc_init_buf) Init();
}

_Locale_impl::_Locale_impl( _Locale_impl const& locimpl ) :
    _Refcount_Base(0),
    name( locimpl.name ),
    facets_vec()
{
  for_each( locimpl.facets_vec.begin(), locimpl.facets_vec.end(), _get_facet );
  facets_vec = locimpl.facets_vec;
  new (&__Loc_init_buf) Init();
}

_Locale_impl::_Locale_impl( size_t n, const char* s) :
    _Refcount_Base(0),
    name(s),
    facets_vec( n, 0 )
{
  new (&__Loc_init_buf) Init();
}

_Locale_impl::~_Locale_impl() {
  for_each( facets_vec.begin(), facets_vec.end(), _release_facet );
  (&__Loc_init_buf)->~Init();
}

// Initialization of the locale system.  This must be called before
// any locales are constructed.  (Meaning that it must be called when
// the I/O library itself is initialized.)
void _STLP_CALL _Locale_impl::_S_initialize() {
  _Stl_loc_assign_ids();
  make_classic_locale();
}

// Release of the classic locale ressources. Has to be called after the last
// locale destruction and not only after the classic locale destruction as
// the facets can be shared between different facets.
void _STLP_CALL _Locale_impl::_S_uninitialize() {
#ifdef _STLP_LEAKS_PEDANTIC
  free_classic_locale();
#endif
}

// _Locale_impl non-inline member functions.
void _STLP_CALL _Locale_impl::_M_throw_bad_cast() {
  _STLP_THROW(bad_cast());  
}

void _Locale_impl::insert( _Locale_impl *from, const locale::id& n )
{
  size_t index = n._M_index;
  if (index > 0 && index < from->size()) {
    this->insert( from->facets_vec[index], index);
  }
}

locale::facet* _Locale_impl::insert(locale::facet *f, size_t index)
{
  if ( f == 0 || index == 0 )
    return 0;

  if (index >= facets_vec.size()) {
    facets_vec.resize( index + 1 );
  }
  _release_facet( facets_vec[index] );
  facets_vec[index] = _get_facet( f );

  return f;
}

//
// <locale> content which is dependent on the name
//

template <class Facet>
inline locale::facet* _Locale_insert(_Locale_impl *__that, Facet* f) {
  return __that->insert(f, Facet::id._M_index);
}

/*
 * Six functions, one for each category.  Each of them takes a
 * _Locale* and a name, constructs that appropriate category
 * facets by name, and inserts them into the locale.
 */
void _Locale_impl::insert_ctype_facets(const char* pname) {
  char buf[_Locale_MAX_SIMPLE_NAME];
  _Locale_impl* i2 = locale::classic()._M_impl;

  if (pname == 0 || pname[0] == 0)
    pname = _Locale_ctype_default(buf);

  if (pname == 0 || pname[0] == 0 || is_C_locale_name(pname)) {
    this->insert(i2, ctype<char>::id);
# ifndef _STLP_NO_MBSTATE_T
    this->insert(i2, codecvt<char, char, mbstate_t>::id);
# endif
# ifndef _STLP_NO_WCHAR_T
    this->insert(i2, ctype<wchar_t>::id);
# ifndef _STLP_NO_MBSTATE_T
    this->insert(i2, codecvt<wchar_t, char, mbstate_t>::id);
# endif
# endif
  } else {
    ctype<char>*    ct                      = 0;
# ifndef _STLP_NO_MBSTATE_T
    codecvt<char, char, mbstate_t>*    cvt  = 0;
# endif
# ifndef _STLP_NO_WCHAR_T
    ctype<wchar_t>* wct                     = 0;
    codecvt<wchar_t, char, mbstate_t>* wcvt = 0;
# endif
    _STLP_TRY {
      ct   = new ctype_byname<char>(pname);
# ifndef _STLP_NO_MBSTATE_T
      cvt  = new codecvt_byname<char, char, mbstate_t>(pname);
# endif
# ifndef _STLP_NO_WCHAR_T
      wct  = new ctype_byname<wchar_t>(pname);
      wcvt = new codecvt_byname<wchar_t, char, mbstate_t>(pname);
# endif
    }

# ifndef _STLP_NO_WCHAR_T
#  ifdef _STLP_NO_MBSTATE_T
    _STLP_UNWIND(delete ct; delete wct; delete wcvt);
#  else
    _STLP_UNWIND(delete ct; delete wct; delete cvt; delete wcvt);
#  endif
# else
#  ifdef _STLP_NO_MBSTATE_T
    _STLP_UNWIND(delete ct);
#  else
    _STLP_UNWIND(delete ct; delete cvt);
#  endif
# endif
    _Locale_insert(this, ct);
#  ifndef _STLP_NO_MBSTATE_T
    _Locale_insert(this, cvt);
#  endif
#  ifndef _STLP_NO_WCHAR_T
    _Locale_insert(this, wct);
    _Locale_insert(this, wcvt);
#  endif
  }
}

void _Locale_impl::insert_numeric_facets(const char* pname) {
  _Locale_impl* i2 = locale::classic()._M_impl;

  numpunct<char>*    punct  = 0;
  num_get<char, istreambuf_iterator<char, char_traits<char> > >*     get    = 0;
  num_put<char, ostreambuf_iterator<char, char_traits<char> > >*     put    = 0;
# ifndef _STLP_NO_WCHAR_T
  numpunct<wchar_t>* wpunct = 0;
  num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >*  wget   = 0;
  num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >*  wput   = 0;
# endif

  char buf[_Locale_MAX_SIMPLE_NAME];
  if (pname == 0 || pname[0] == 0)
    pname = _Locale_numeric_default(buf);

  if (pname == 0 || pname[0] == 0 || is_C_locale_name(pname)) {
    this->insert(i2, numpunct<char>::id);
    this->insert(i2,
                 num_put<char, ostreambuf_iterator<char, char_traits<char> >  >::id);
    this->insert(i2,
                 num_get<char, istreambuf_iterator<char, char_traits<char> > >::id);
# ifndef _STLP_NO_WCHAR_T
    this->insert(i2, numpunct<wchar_t>::id);
    this->insert(i2,
                 num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> >  >::id);
    this->insert(i2,
                 num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
# endif
  }
  else {
    _STLP_TRY {
      punct  = new numpunct_byname<char>(pname);
      get    = new num_get<char, istreambuf_iterator<char, char_traits<char> > >;
      put    = new num_put<char, ostreambuf_iterator<char, char_traits<char> > >;
# ifndef _STLP_NO_WCHAR_T
      wpunct = new numpunct_byname<wchar_t>(pname);
      wget   = new num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >;
      wput   = new num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >;
# endif
    }
# ifndef _STLP_NO_WCHAR_T
    _STLP_UNWIND(delete punct; delete wpunct; delete get; delete wget; delete put; delete wput);
# else
    _STLP_UNWIND(delete punct; delete get;delete put);
# endif

  _Locale_insert(this,punct);
  _Locale_insert(this,get);
  _Locale_insert(this,put);

# ifndef _STLP_NO_WCHAR_T
  _Locale_insert(this,wpunct);
  _Locale_insert(this,wget);
  _Locale_insert(this,wput);
# endif
  }
}

void _Locale_impl::insert_time_facets(const char* pname) {
  _Locale_impl* i2 = locale::classic()._M_impl;
  time_get<char, istreambuf_iterator<char, char_traits<char> > >*    get  = 0;
  time_put<char, ostreambuf_iterator<char, char_traits<char> > >*    put  = 0;
# ifndef _STLP_NO_WCHAR_T
  time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >* wget = 0;
  time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >* wput = 0;
# endif

  char buf[_Locale_MAX_SIMPLE_NAME];
  if (pname == 0 || pname[0] == 0)
    pname = _Locale_time_default(buf);

  if (pname == 0 || pname[0] == 0 || is_C_locale_name(pname)) {

    this->insert(i2,
                 time_get<char, istreambuf_iterator<char, char_traits<char> > >::id);
    this->insert(i2,
                 time_put<char, ostreambuf_iterator<char, char_traits<char> > >::id);
# ifndef _STLP_NO_WCHAR_T
    this->insert(i2,
                 time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
    this->insert(i2,
                 time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
# endif
  } else {
    _STLP_TRY {
      get  = new time_get_byname<char, istreambuf_iterator<char, char_traits<char> > >(pname);
      put  = new time_put_byname<char, ostreambuf_iterator<char, char_traits<char> > >(pname);
# ifndef _STLP_NO_WCHAR_T
      wget = new time_get_byname<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(pname);
      wput = new time_put_byname<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(pname);
# endif
    }
# ifndef _STLP_NO_WCHAR_T
    _STLP_UNWIND(delete get; delete wget; delete put; delete wput);
# else
    _STLP_UNWIND(delete get; delete put);
# endif
    _Locale_insert(this,get);
    _Locale_insert(this,put);
# ifndef _STLP_NO_WCHAR_T
    _Locale_insert(this,wget);
    _Locale_insert(this,wput);
# endif
  }
}

void _Locale_impl::insert_collate_facets(const char* nam) {
  _Locale_impl* i2 = locale::classic()._M_impl;

  collate<char>*    col  = 0;
# ifndef _STLP_NO_WCHAR_T
  collate<wchar_t>* wcol = 0;
# endif

  char buf[_Locale_MAX_SIMPLE_NAME];
  if (nam == 0 || nam[0] == 0)
    nam = _Locale_collate_default(buf);

  if (nam == 0 || nam[0] == 0 || is_C_locale_name(nam)) {
    this->insert(i2, collate<char>::id);
# ifndef _STLP_NO_WCHAR_T
    this->insert(i2, collate<wchar_t>::id);
# endif
  }
  else {
    _STLP_TRY {
      col   = new collate_byname<char>(nam);
# ifndef _STLP_NO_WCHAR_T
      wcol  = new collate_byname<wchar_t>(nam);
# endif
    }
# ifndef _STLP_NO_WCHAR_T
    _STLP_UNWIND(delete col; delete wcol);
# else
    _STLP_UNWIND(delete col);
# endif
    _Locale_insert(this,col);
# ifndef _STLP_NO_WCHAR_T
    _Locale_insert(this,wcol);
# endif
  }
}

void _Locale_impl::insert_monetary_facets(const char* pname) {
  _Locale_impl* i2 = locale::classic()._M_impl;

  moneypunct<char,    false>* punct   = 0;
  moneypunct<char,    true>*  ipunct  = 0;
  money_get<char, istreambuf_iterator<char, char_traits<char> > >*            get     = 0;
  money_put<char, ostreambuf_iterator<char, char_traits<char> > >*            put     = 0;

# ifndef _STLP_NO_WCHAR_T
  moneypunct<wchar_t, false>* wpunct  = 0;
  moneypunct<wchar_t, true>*  wipunct = 0;
  money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >*         wget    = 0;
  money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >*         wput    = 0;
# endif

  char buf[_Locale_MAX_SIMPLE_NAME];
  if (pname == 0 || pname[0] == 0)
    pname = _Locale_monetary_default(buf);

  if (pname == 0 || pname[0] == 0 || is_C_locale_name(pname)) {
    this->insert(i2, moneypunct<char, false>::id);
    this->insert(i2, moneypunct<char, true>::id);
    this->insert(i2, money_get<char, istreambuf_iterator<char, char_traits<char> > >::id);
    this->insert(i2, money_put<char, ostreambuf_iterator<char, char_traits<char> > >::id);
# ifndef _STLP_NO_WCHAR_T
    this->insert(i2, moneypunct<wchar_t, false>::id);
    this->insert(i2, moneypunct<wchar_t, true>::id);
    this->insert(i2, money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
    this->insert(i2, money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
# endif
  }
  else {
    _STLP_TRY {
      punct   = new moneypunct_byname<char, false>(pname);
      ipunct  = new moneypunct_byname<char, true>(pname);
      get     = new money_get<char, istreambuf_iterator<char, char_traits<char> > >;
      put     = new money_put<char, ostreambuf_iterator<char, char_traits<char> > >;
# ifndef _STLP_NO_WCHAR_T
      wpunct  = new moneypunct_byname<wchar_t, false>(pname);
      wipunct = new moneypunct_byname<wchar_t, true>(pname);
      wget    = new money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >;
      wput    = new money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >;
# endif
    }
# ifndef _STLP_NO_WCHAR_T
    _STLP_UNWIND(delete punct; delete ipunct; delete wpunct; delete wipunct; delete get; delete wget; delete put; delete wput);
# else
    _STLP_UNWIND(delete punct; delete ipunct; delete get; delete put);
# endif
    _Locale_insert(this,punct);
    _Locale_insert(this,ipunct);
    _Locale_insert(this,get);
    _Locale_insert(this,put);
# ifndef _STLP_NO_WCHAR_T
    _Locale_insert(this,wget);
    _Locale_insert(this,wpunct);
    _Locale_insert(this,wipunct);
    _Locale_insert(this,wput);
# endif
  }
}

void _Locale_impl::insert_messages_facets(const char* pname) {
  _Locale_impl* i2 = locale::classic()._M_impl;
  messages<char>*    msg  = 0;
# ifndef _STLP_NO_WCHAR_T
  messages<wchar_t>* wmsg = 0;
# endif

  char buf[_Locale_MAX_SIMPLE_NAME];
  if (pname == 0 || pname[0] == 0)
    pname = _Locale_messages_default(buf);

  if (pname == 0 || pname[0] == 0 || is_C_locale_name(pname)) {
    this->insert(i2, messages<char>::id);
# ifndef _STLP_NO_WCHAR_T
    this->insert(i2, messages<wchar_t>::id);
# endif
  }
  else {
    _STLP_TRY {
      msg  = new messages_byname<char>(pname);
# ifndef _STLP_NO_WCHAR_T
      wmsg = new messages_byname<wchar_t>(pname);
# endif
    }
# ifndef _STLP_NO_WCHAR_T
    _STLP_UNWIND(delete msg; delete wmsg);
# else
    _STLP_UNWIND(delete msg);
# endif
    _Locale_insert(this,msg);
# ifndef _STLP_NO_WCHAR_T
    _Locale_insert(this,wmsg);
# endif
  }
}

static void _Stl_loc_assign_ids() {
  // This assigns ids to every facet that is a member of a category,
  // and also to money_get/put, num_get/put, and time_get/put
  // instantiated using ordinary pointers as the input/output
  // iterators.  (The default is [io]streambuf_iterator.)

  money_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index          = 8;
  money_get<char, const char*>::id._M_index                                             = 9;
  money_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index          = 10;
  money_put<char, char*>::id._M_index                                                   = 11;

  num_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index            = 12;
  num_get<char, const char*>::id._M_index                                               = 13;
  num_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index            = 14;
  num_put<char, char*>::id._M_index                                                     = 15;
  time_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index           = 16;
  time_get<char, const char*>::id._M_index                                              = 17;
  time_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index           = 18;
  time_put<char, char*>::id._M_index                                                    = 19;

# ifndef _STLP_NO_WCHAR_T

  money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index = 27;
  money_get<wchar_t, const wchar_t*>::id._M_index                                       = 28;
  money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index = 29;
  money_put<wchar_t, wchar_t*>::id._M_index                                             = 30;

  num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index   = 31;
  num_get<wchar_t, const wchar_t*>::id._M_index                                         = 32;
  num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > ::id._M_index  = 33;
  num_put<wchar_t, wchar_t*>::id._M_index                                               = 34;
  time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index  = 35;
  time_get<wchar_t, const wchar_t*>::id._M_index                                        = 36;
  time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index  = 37;
  time_put<wchar_t, wchar_t*>::id._M_index                                              = 38;
  //  messages<wchar_t>::id._M_index                   = 38;
# endif

  //  locale::id::_S_max                               = 39;
}

static _Stl_aligned_buffer<collate<char> > _S_collate_char;
static _Stl_aligned_buffer<ctype<char> > _S_ctype_char;

# ifndef _STLP_NO_MBSTATE_T
static _Stl_aligned_buffer<codecvt<char, char, mbstate_t> > _S_codecvt_char;
# endif

static _Stl_aligned_buffer<moneypunct<char, true> > _S_moneypunct_true_char;
static _Stl_aligned_buffer<moneypunct<char, false> > _S_moneypunct_false_char;
static _Stl_aligned_buffer<numpunct<char> > _S_numpunct_char;
static _Stl_aligned_buffer<messages<char> > _S_messages_char;

static _Stl_aligned_buffer<money_get<char, istreambuf_iterator<char, char_traits<char> > > > _S_money_get_char;
static _Stl_aligned_buffer<money_put<char, ostreambuf_iterator<char, char_traits<char> > > > _S_money_put_char;
static _Stl_aligned_buffer<num_get<char, istreambuf_iterator<char, char_traits<char> > > > _S_num_get_char;
static _Stl_aligned_buffer<num_put<char, ostreambuf_iterator<char, char_traits<char> > > > _S_num_put_char;
static _Stl_aligned_buffer<time_get<char, istreambuf_iterator<char, char_traits<char> > > > _S_time_get_char;
static _Stl_aligned_buffer<time_put<char, ostreambuf_iterator<char, char_traits<char> > > > _S_time_put_char;

# ifndef _STLP_NO_WCHAR_T
static _Stl_aligned_buffer<collate<wchar_t> > _S_collate_wchar;
static _Stl_aligned_buffer<ctype<wchar_t> > _S_ctype_wchar;
# ifndef _STLP_NO_MBSTATE_T
static _Stl_aligned_buffer<codecvt<wchar_t, char, mbstate_t> > _S_codecvt_wchar;
# endif
static _Stl_aligned_buffer<moneypunct<wchar_t, true> > _S_moneypunct_true_wchar;
static _Stl_aligned_buffer<moneypunct<wchar_t, false> > _S_moneypunct_false_wchar;
static _Stl_aligned_buffer<numpunct<wchar_t> > _S_numpunct_wchar;
static _Stl_aligned_buffer<messages<wchar_t> > _S_messages_wchar;

static _Stl_aligned_buffer<money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_money_get_wchar;
static _Stl_aligned_buffer<money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_money_put_wchar;
static _Stl_aligned_buffer<num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_num_get_wchar;
static _Stl_aligned_buffer<num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_num_put_wchar;
static _Stl_aligned_buffer<time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_time_get_wchar;
static _Stl_aligned_buffer<time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_time_put_wchar;

# endif

static _Messages _Null_messages;

static locale::facet* _S_classic_facets[] = {
  0,
  &_S_collate_char,
  &_S_ctype_char,
# ifndef _STLP_NO_MBSTATE_T
  &_S_codecvt_char,
# else
  0, 
# endif
  &_S_moneypunct_true_char,
  &_S_moneypunct_false_char,
  &_S_numpunct_char,
  &_S_messages_char,

  &_S_money_get_char,
  0,
  &_S_money_put_char,
  0,

  &_S_num_get_char,
  0,
  &_S_num_put_char,
  0,
  &_S_time_get_char,
  0,
  &_S_time_put_char,
  0,
# ifndef _STLP_NO_WCHAR_T
  &_S_collate_wchar,
  &_S_ctype_wchar,

# ifndef _STLP_NO_MBSTATE_T
  &_S_codecvt_wchar,
# else
  0,
# endif
  &_S_moneypunct_true_wchar,
  &_S_moneypunct_false_wchar,
  &_S_numpunct_wchar,
  &_S_messages_wchar,

  &_S_money_get_wchar,
  0,
  &_S_money_put_wchar,
  0,

  &_S_num_get_wchar,
  0,
  &_S_num_put_wchar,
  0,
  &_S_time_get_wchar,
  0,
  &_S_time_put_wchar,
  0,
# endif
  0
};

static _Stl_aligned_buffer<_Locale_impl> _Locale_classic_impl_buf;
static _Stl_aligned_buffer<locale> _Locale_classic_buf;
static _Stl_aligned_buffer<locale> _Locale_global_buf;

// Order is significant here: this null assignment have to be placed
// BEFORE building classic _Locale_impl
static locale *_Stl_classic_locale = 0;
static locale *_Stl_global_locale = 0;

// The classic locale contains every facet that belongs to a category.
// build classic _Locale_impl (1):
static _Locale_impl *_Stl_classic_locale_impl = new (&_Locale_classic_impl_buf) _Locale_impl("C");

#if defined (_STLP_LEAKS_PEDANTIC)
static struct _Locale_classic_free {
  ~_Locale_classic_free() {
      _Stl_global_locale->~locale();
      _Stl_classic_locale->~locale();
      _Stl_classic_locale = 0;

      _Stl_classic_locale_impl->~_Locale_impl();
      _Stl_classic_locale_impl = 0;
    }
} _classic_free;
#endif

/*
 * This object is instanciated here to guarantee creation of the classic locale
 * before creation of the dependent Standard streams cout, cin, wcout...
 */
static ios_base::Init _IosInit;

void _Locale_impl::make_classic_locale() {
  // This funcion will be called once: during build classic _Locale_impl (see (1) above)

  // The classic locale contains every facet that belongs to a category.
  _Locale_impl *classic = &_Locale_classic_impl_buf;

  // classic->facets = _S_classic_facets;
  // classic->_M_size = locale::id::_S_max;
  classic->facets_vec.reserve(sizeof(_S_classic_facets)/sizeof(locale::facet *));
  classic->facets_vec.assign(&_S_classic_facets[0],_S_classic_facets+sizeof(_S_classic_facets)/sizeof(locale::facet *));

  // ctype category
  new(&_S_ctype_char) ctype<char>(0, false, 1);
  // collate category
  new(&_S_collate_char) collate<char>(1);
  new(&_S_codecvt_char) codecvt<char, char, mbstate_t>(1);
  // numeric punctuation category
  new(&_S_numpunct_char) numpunct<char>(1);
  // numeric category
  new (&_S_num_get_char) num_get<char, istreambuf_iterator<char, char_traits<char> > >(1);
  new (&_S_num_put_char) num_put<char, ostreambuf_iterator<char, char_traits<char> > >(1);
  // time category
  new (&_S_time_get_char) time_get<char, istreambuf_iterator<char, char_traits<char> > >(1);
  new (&_S_time_put_char) time_put<char, ostreambuf_iterator<char, char_traits<char> > >(1);
  // monetary category
  new (&_S_moneypunct_true_char) moneypunct<char, true>(1);
  new (&_S_moneypunct_false_char) moneypunct<char, false>(1);
  new (&_S_money_get_char) money_get<char, istreambuf_iterator<char, char_traits<char> > >(1);
  new (&_S_money_put_char) money_put<char, ostreambuf_iterator<char, char_traits<char> > >(1);
  // messages category
  new (&_S_messages_char)messages<char>(&_Null_messages);

# ifndef _STLP_NO_WCHAR_T
  // ctype category
  new(&_S_ctype_wchar) ctype<wchar_t>(1);
  // collate category
  new(&_S_collate_wchar) collate<wchar_t>(1);
  new(&_S_codecvt_wchar) codecvt<wchar_t, char, mbstate_t>(1);
  // numeric punctuation category
  new(&_S_numpunct_wchar) numpunct<wchar_t>(1);
  // numeric category
  new (&_S_num_get_wchar) num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  new (&_S_num_put_wchar) num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  // time category
  new (&_S_time_get_wchar) time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  new (&_S_time_put_wchar) time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  // monetary category
  new (&_S_moneypunct_true_wchar) moneypunct<wchar_t, true>(1);
  new (&_S_moneypunct_false_wchar) moneypunct<wchar_t, false>(1);
  new (&_S_money_get_wchar) money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  new (&_S_money_put_wchar) money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  // messages category
  new (&_S_messages_wchar)messages<wchar_t>(&_Null_messages);
# endif

  _Stl_classic_locale = new (&_Locale_classic_buf) locale( classic );
  _Stl_global_locale = new (&_Locale_global_buf) locale( _copy_Locale_impl( classic ) );
}

#ifdef _STLP_LEAKS_PEDANTIC
void _Locale_impl::free_classic_locale() {
# ifndef _STLP_NO_WCHAR_T
  (&_S_messages_wchar)->~messages<wchar_t>();
  (&_S_money_put_wchar)->~money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_money_get_wchar)->~money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_moneypunct_false_wchar)->~moneypunct<wchar_t, false>();
  (&_S_moneypunct_true_wchar)->~moneypunct<wchar_t, true>();
  (&_S_time_put_wchar)->~time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_time_get_wchar)->~time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_num_put_wchar)->~num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_num_get_wchar)->~num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_numpunct_wchar)->~numpunct<wchar_t>();
  (&_S_codecvt_wchar)->~codecvt<wchar_t, char, mbstate_t>();
  (&_S_collate_wchar)->~collate<wchar_t>();
  (&_S_ctype_wchar)->~ctype<wchar_t>();
# endif

  (&_S_messages_char)->~messages<char>();
  (&_S_money_put_char)->~money_put<char, ostreambuf_iterator<char, char_traits<char> > >();
  (&_S_money_get_char)->~money_get<char, istreambuf_iterator<char, char_traits<char> > >();
  (&_S_moneypunct_false_char)->~moneypunct<char, false>();
  (&_S_moneypunct_true_char)->~moneypunct<char, true>();
  (&_S_time_put_char)->~time_put<char, ostreambuf_iterator<char, char_traits<char> > >();
  (&_S_time_get_char)->~time_get<char, istreambuf_iterator<char, char_traits<char> > >();
  (&_S_num_put_char)->~num_put<char, ostreambuf_iterator<char, char_traits<char> > >();
  (&_S_num_get_char)->~num_get<char, istreambuf_iterator<char, char_traits<char> > >();
  (&_S_numpunct_char)->~numpunct<char>();
  (&_S_codecvt_char)->~codecvt<char, char, mbstate_t>();
  (&_S_collate_char)->~collate<char>();
  (&_S_ctype_char)->~ctype<char>();
}

#endif // _STLP_LEAKS_PEDANTIC

// Declarations of (non-template) facets' static data members
// size_t locale::id::_S_max = 39; // made before

_STLP_STATIC_MEMBER_DECLSPEC locale::id collate<char>::id = { 1 };
_STLP_STATIC_MEMBER_DECLSPEC locale::id ctype<char>::id = { 2 };

# ifndef _STLP_NO_MBSTATE_T
_STLP_STATIC_MEMBER_DECLSPEC locale::id codecvt<char, char, mbstate_t>::id = { 3 };
#  ifndef _STLP_NO_WCHAR_T
_STLP_STATIC_MEMBER_DECLSPEC locale::id codecvt<wchar_t, char, mbstate_t>::id = { 22 };
#  endif
# endif

_STLP_STATIC_MEMBER_DECLSPEC locale::id moneypunct<char, true>::id = { 4 };
_STLP_STATIC_MEMBER_DECLSPEC locale::id moneypunct<char, false>::id = { 5 };
_STLP_STATIC_MEMBER_DECLSPEC locale::id numpunct<char>::id = { 6 } ;
_STLP_STATIC_MEMBER_DECLSPEC locale::id messages<char>::id = { 7 };

# ifndef _STLP_NO_WCHAR_T
_STLP_STATIC_MEMBER_DECLSPEC locale::id collate<wchar_t>::id = { 20 };
_STLP_STATIC_MEMBER_DECLSPEC locale::id ctype<wchar_t>::id = { 21 };

_STLP_STATIC_MEMBER_DECLSPEC locale::id moneypunct<wchar_t, true>::id = { 23 } ;
_STLP_STATIC_MEMBER_DECLSPEC locale::id moneypunct<wchar_t, false>::id = { 24 } ;

_STLP_STATIC_MEMBER_DECLSPEC locale::id numpunct<wchar_t>::id = { 25 };
_STLP_STATIC_MEMBER_DECLSPEC locale::id messages<wchar_t>::id = { 26 };
# endif


_STLP_DECLSPEC _Locale_impl * _STLP_CALL _get_Locale_impl( _Locale_impl *loc )
{
  _STLP_ASSERT( loc != 0 );
  loc->_M_incr();

  return loc;
}

void _STLP_CALL _release_Locale_impl( _Locale_impl *& loc )
{
  _STLP_ASSERT( loc != 0 );
  if ( loc->_M_decr() == 0 && loc != _Stl_classic_locale_impl ) {
    delete loc;
    loc = 0;
  }
}

_Locale_impl * _STLP_CALL _copy_Locale_impl( _Locale_impl *loc )
{
   _STLP_ASSERT( loc != 0 );
  loc->_M_incr();
  _Locale_impl *loc_new = new _Locale_impl( *loc );
  loc->_M_decr();
  return loc_new;
}

_STLP_DECLSPEC _Locale_impl * _STLP_CALL _copy_Nameless_Locale_impl( _Locale_impl *loc )
{
   _STLP_ASSERT( loc != 0 );
  loc->_M_incr();
  _Locale_impl *loc_new = new _Locale_impl( *loc );
  loc->_M_decr();
  loc_new->name = "*";
  return loc_new;
}

locale::facet * _STLP_CALL _get_facet( locale::facet *f )
{
  if ( f != 0 && f->_M_delete ) {
    f->_M_incr();
  }

  return f;
}

void _STLP_CALL _release_facet( locale::facet *&f )
{
  if ( f != 0 && f->_M_delete && f->_M_decr() == 0 ) {
    delete f;
    f = 0;
  }
}

_STLP_END_NAMESPACE


// locale use many static functions/pointers from this file:
// to avoid making ones extern, simple #include implementation of locale

#include "locale.cpp"

