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
// WARNING: This is an internal header file, included by other C++
// standard library headers.  You should not attempt to use this header
// file directly.


#ifndef __SGI_STL_INTERNAL_NUM_GET_H
#define __SGI_STL_INTERNAL_NUM_GET_H

#ifndef __SGI_STL_INTERNAL_ITERATOR_BASE_H
# include <stl/_iterator_base.h>
#endif

#ifndef __SGI_STL_INTERNAL_STREAMBUF
# include <stl/_streambuf.h>
#endif

# ifndef __STL_C_LOCALE_H
#  include <stl/c_locale.h>
# endif

#ifndef __SGI_STL_INTERNAL_NUMPUNCT_H
# include <stl/_numpunct.h>
#endif
#ifndef __SGI_STL_INTERNAL_CTYPE_H
# include <stl/_ctype.h>
#endif

__STL_BEGIN_NAMESPACE

// defined in _istream.h
template <class _CharT, class _Traits>
extern basic_streambuf<_CharT, _Traits>* __STL_CALL _M_get_istreambuf(basic_istream<_CharT, _Traits>& ) ;

// We do not read any characters until operator* is called.  The first
// time operator* is called, it calls getc.  Subsequent calls to getc 
// return a cached character, and calls to operator++ use snextc.  Before
// operator* or operator++ has been called, _M_is_initialized is false.
template<class _CharT, class _Traits>
class istreambuf_iterator
{
public:
  typedef _CharT                           char_type;
  typedef _Traits                          traits_type;
  typedef typename _Traits::int_type       int_type;
  typedef basic_streambuf<_CharT, _Traits> streambuf_type;
  typedef basic_istream<_CharT, _Traits>   istream_type;

  typedef input_iterator_tag               iterator_category;
  typedef _CharT                           value_type;
  typedef typename _Traits::off_type       difference_type;
  typedef const _CharT*                    pointer;
  typedef const _CharT&                    reference;

public:
  istreambuf_iterator(streambuf_type* __p = 0) { this->_M_init(__p); }
  istreambuf_iterator(basic_istream<_CharT, _Traits>& __is) { this->_M_init(_M_get_istreambuf(__is)); }

  char_type operator*() const 
    { if (!_M_is_initialized) this->_M_getc() ; return _M_c ; }

  istreambuf_iterator<_CharT, _Traits>& operator++() { this->_M_nextc(); return *this; }

  istreambuf_iterator<_CharT, _Traits>  operator++(int);

  bool equal(const istreambuf_iterator<_CharT, _Traits>& __i) const {
    return this->_M_is_initialized && __i._M_is_initialized
      ? this->_M_eof == __i._M_eof
      : this->_M_equal_aux(__i);
  }

private:
  void _M_init(streambuf_type* __p) {
    _M_buf = __p;
    _M_eof = !__p;
    _M_is_initialized = _M_eof;
  }

  void _M_getc() const {
    int_type __c = _M_buf->sgetc();
# if !defined (__STL_NEED_MUTABLE) /*  && ! defined (__SUNPRO_CC) */
    _M_c = traits_type::to_char_type(__c);
    _M_eof = traits_type::eq_int_type(__c, traits_type::eof());
    _M_is_initialized = true;
# else
    typedef istreambuf_iterator<_CharT,_Traits> _Self;
    _Self* __that = __CONST_CAST(_Self*, this);
    __that->_M_c = __STATIC_CAST(_CharT, traits_type::to_char_type(__c));
    __that->_M_eof = traits_type::eq_int_type(__c, traits_type::eof());
    __that->_M_is_initialized = true;
# endif
  }


  bool _M_equal_aux(const istreambuf_iterator<_CharT, _Traits>& __i) const {
    if (!this->_M_is_initialized)
      this->_M_getc();
    if (!__i._M_is_initialized)
      __i._M_getc();    
    return this->_M_eof == __i._M_eof;
  }

  void _M_nextc() {
    int_type __c = _M_buf->snextc();

    _M_c = traits_type::to_char_type(__c);
    _M_eof = traits_type::eq_int_type(__c, traits_type::eof());
    _M_is_initialized = true;
  }

private:
  streambuf_type* _M_buf;
  mutable _CharT _M_c;
#if !defined(__SC__)		//*TY 03/20/2000 - 
  mutable unsigned char _M_eof;
  mutable unsigned char _M_is_initialized;
#else
  mutable bool _M_eof;
  mutable bool _M_is_initialized;
#endif
};

template<class _CharT, class _Traits>
inline bool __STL_CALL operator==(const istreambuf_iterator<_CharT, _Traits>& __x,
                                  const istreambuf_iterator<_CharT, _Traits>& __y) {
  return __x.equal(__y);
}

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE

template<class _CharT, class _Traits>
inline bool __STL_CALL operator!=(const istreambuf_iterator<_CharT, _Traits>& __x,
                                  const istreambuf_iterator<_CharT, _Traits>& __y) {
  return !__x.equal(__y);
}

#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */

# if defined (__STL_USE_TEMPLATE_EXPORT)
__STL_EXPORT_TEMPLATE_CLASS istreambuf_iterator<char, char_traits<char> >;
#  if defined (INSTANTIATE_WIDE_STREAMS)
__STL_EXPORT_TEMPLATE_CLASS istreambuf_iterator<wchar_t, char_traits<wchar_t> >;
#  endif
# endif /* __STL_USE_TEMPLATE_EXPORT */

# ifdef __STL_USE_OLD_HP_ITERATOR_QUERIES
template <class _CharT, class _Traits>
inline input_iterator_tag __STL_CALL iterator_category(const istreambuf_iterator<_CharT, _Traits>&) { return input_iterator_tag(); }
template <class _CharT, class _Traits>
inline streamoff __STL_CALL 
distance_type(const istreambuf_iterator<_CharT, _Traits>&) { typedef streamoff __off_type; return __off_type(); }
template <class _CharT, class _Traits>
inline _CharT* __STL_CALL value_type(const istreambuf_iterator<_CharT, _Traits>&) { return (_CharT*)0; }
# endif

//----------------------------------------------------------------------
// num_get facets

# ifdef __STL_LIMITED_DEFAULT_TEMPLATES
template <class _CharT, class _InputIter>  
# else
template <class _CharT, class _InputIter = istreambuf_iterator<_CharT> >  
# endif
class num_get: public locale::facet
{
  friend class _Locale;
#if defined(__MRC__) || defined(__SC__)	//*TY 04/29/2000 - added workaround for mpw
  typedef locale::facet _facet;			//*TY 04/29/2000 - they forget to look into nested class for the ctor.
#endif
public:
  typedef _CharT     char_type;
  typedef _InputIter iter_type;

#if !(defined(__MRC__)||defined(__SC__))	//*TY 02/26/2000 - added workaround for MPW compilers; explicit will prevent the compiler to find out the proper ctor
  explicit 
#endif										//*TY 02/26/2000 - 
  num_get(size_t __refs = 0) 
#if !(defined(__MRC__) || defined(__SC__) )		//*TY 04/29/2000 - added workaround for mpw
  : locale::facet(__refs)
#else
  : _facet(__refs)		//*TY 04/29/2000 - they forget to look into the nested class for the ctor
#endif
  {}
    
# ifndef __STL_NO_BOOL
  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, bool& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }
# endif

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, short& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, int& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, long& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, unsigned short& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, unsigned int& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, unsigned long& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }

#ifdef __STL_LONG_LONG

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, __STL_LONG_LONG& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, unsigned __STL_LONG_LONG& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }

#endif /* _STL_LONG_LONG */

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, float& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, double& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }

# ifndef __STL_NO_LONG_DOUBLE

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, long double& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }
# endif

  _InputIter get(_InputIter __in, _InputIter __end, ios_base& __str,
                ios_base::iostate& __err, void*& __val) const {
    return do_get(__in, __end, __str, __err, __val);
  }

  __STL_STATIC_MEMBER_DECLSPEC static locale::id id;

protected:
  ~num_get() {}

  typedef string               string_type; 
  typedef ctype<_CharT>        _Ctype;
  typedef numpunct<_CharT>     _Numpunct;

# ifndef __STL_NO_BOOL
  virtual _InputIter do_get(_InputIter __in, _InputIter __end,
                           ios_base& __str, ios_base::iostate& __err, bool& __val) const;
# endif
  // issue 118
  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                           ios_base::iostate& __err, short& __val) const;
  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                           ios_base::iostate& __err, int& __val) const;
  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                           ios_base::iostate& __err, long& __val) const;
  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                           ios_base::iostate& __err, unsigned short& __val) const;
  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                           ios_base::iostate& __err, unsigned int& __val) const;
  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                           ios_base::iostate& __err, unsigned long& __val) const;
  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                          ios_base::iostate& __err, float& __val) const;
  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                           ios_base::iostate& __err, double& __val) const;
  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                           ios_base::iostate& __err,
                           void*& __p) const;

#ifndef __STL_NO_LONG_DOUBLE
  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                           ios_base::iostate& __err, long double& __val) const;
#endif /* __STL_LONG_DOUBLE */

#ifdef __STL_LONG_LONG

  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, __STL_LONG_LONG& __val) const;
  virtual _InputIter do_get(_InputIter __in, _InputIter __end, ios_base& __str,
                           ios_base::iostate& __err, unsigned __STL_LONG_LONG& __val) const;
#endif /* __STL_LONG_LONG */

};


# ifdef __STL_USE_TEMPLATE_EXPORT
__STL_EXPORT_TEMPLATE_CLASS num_get<char, istreambuf_iterator<char, char_traits<char> > >;
__STL_EXPORT_TEMPLATE_CLASS num_get<char, const char*>;
#  ifndef __STL_NO_WCHAR_T
__STL_EXPORT_TEMPLATE_CLASS num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >;
__STL_EXPORT_TEMPLATE_CLASS num_get<wchar_t, const wchar_t*>;
#  endif /* __STL_NO_WCHAR_T */
# endif

# if defined (__STL_EXPOSE_STREAM_IMPLEMENTATION)

extern bool  __STL_CALL __valid_grouping(const string &, const string &);

template <class _InputIter, class _Integer>
bool __STL_CALL
__get_integer_nogroup(_InputIter& __first, _InputIter& __last,
                      int __base, _Integer& __val, int __got, bool __is_negative);
inline bool __STL_CALL __get_fdigit(char& __c, const char*);
inline bool __STL_CALL __get_fdigit_or_sep(char& __c, char __sep, const char *);
# ifndef __STL_NO_WCHAR_T
bool __STL_CALL __get_fdigit(wchar_t&, const wchar_t*);
bool __STL_CALL __get_fdigit_or_sep(wchar_t&, wchar_t, const wchar_t*);
# endif
void __STL_CALL _Initialize_get_float(const locale&,
                                       char&, char&, char&, char&, char&,
                                       char&, string&,
                                       char*);
# ifndef __STL_NO_WCHAR_T
void  __STL_CALL _Initialize_get_float(const locale&,
                                        wchar_t&, wchar_t&, wchar_t&, wchar_t&, wchar_t&,
                                        wchar_t&, string&, wchar_t*);
# endif
void  __STL_CALL __string_to_float(const string&, float&);
void  __STL_CALL __string_to_float(const string&, double&);
void  __STL_CALL __string_to_float(const string&, long double&);
# endif

__STL_END_NAMESPACE

#  if defined (__STL_EXPOSE_STREAM_IMPLEMENTATION) && ! defined (__STL_LINK_TIME_INSTANTIATION)
#   include <stl/_num_get.c>
#  endif

#endif /* __SGI_STL_INTERNAL_NUM_GET_H */

// Local Variables:
// mode:C++
// End:

