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


#ifndef __SGI_STL_INTERNAL_NUM_PUT_H
#define __SGI_STL_INTERNAL_NUM_PUT_H

#ifndef __SGI_STL_INTERNAL_NUMPUNCT_H
# include <stl/_numpunct.h>
#endif
#ifndef __SGI_STL_INTERNAL_CTYPE_H
# include <stl/_ctype.h>
#endif
#ifndef __SGI_STL_INTERNAL_STREAMBUF
# include <stl/_streambuf.h>
#endif

__STL_BEGIN_NAMESPACE

template <class _CharT, class _Traits>
extern basic_streambuf<_CharT, _Traits>* __STL_CALL _M_get_ostreambuf(basic_ostream<_CharT, _Traits>& ) ;

// The default template argument is declared in iosfwd
template<class _CharT, class _Traits>
class ostreambuf_iterator
{
public:
  typedef _CharT                           char_type;
  typedef _Traits                          traits_type;
  typedef typename _Traits::int_type       int_type;
  typedef basic_streambuf<_CharT, _Traits> streambuf_type;
  typedef basic_ostream<_CharT, _Traits>   ostream_type;

  typedef output_iterator_tag              iterator_category;
  typedef void                             value_type;
  typedef void                             difference_type;
  typedef void                             pointer;
  typedef void                             reference;

public:
  ostreambuf_iterator(streambuf_type* __buf) __STL_NOTHROW : _M_buf(__buf), _M_ok(__buf!=0) {}
  ostreambuf_iterator(ostream_type& __o) __STL_NOTHROW : _M_buf(_M_get_ostreambuf(__o)), _M_ok(_M_buf != 0) {}

  ostreambuf_iterator<_CharT, _Traits>& operator=(char_type __c) {
    _M_ok = _M_ok && !traits_type::eq_int_type(_M_buf->sputc(__c),
                                               traits_type::eof());
    return *this;
  }    
  
  ostreambuf_iterator<_CharT, _Traits>& operator*()     { return *this; }
  ostreambuf_iterator<_CharT, _Traits>& operator++()    { return *this; }
  ostreambuf_iterator<_CharT, _Traits>& operator++(int) { return *this; }

  bool failed() const { return !_M_ok; }

private:
  streambuf_type* _M_buf;
  bool _M_ok;
};

# if defined (__STL_USE_TEMPLATE_EXPORT)
__STL_EXPORT_TEMPLATE_CLASS ostreambuf_iterator<char, char_traits<char> >;
#  if defined (INSTANTIATE_WIDE_STREAMS)
__STL_EXPORT_TEMPLATE_CLASS ostreambuf_iterator<wchar_t, char_traits<wchar_t> >;
#  endif
# endif /* __STL_USE_TEMPLATE_EXPORT */

# ifdef __STL_USE_OLD_HP_ITERATOR_QUERIES
template <class _CharT, class _Traits>
inline output_iterator_tag __STL_CALL 
iterator_category(const ostreambuf_iterator<_CharT, _Traits>&) { return output_iterator_tag(); }
# endif

//----------------------------------------------------------------------
// num_put facet

# ifdef __STL_LIMITED_DEFAULT_TEMPLATES
template <class _CharT, class _OutputIter>  
# else
template <class _CharT, class _OutputIter = ostreambuf_iterator<_CharT, char_traits<_CharT> > >  
# endif
class num_put: public locale::facet
{
  friend class _Locale;
#if defined(__MRC__) || defined(__SC__)	//*TY 04/29/2000 - added workaround for mpw
  typedef locale::facet _facet;			//*TY 04/29/2000 - they forget to look into nested class for the ctor.
#endif									//*TY 04/29/2000 - 
public:
  typedef _CharT      char_type;
  typedef _OutputIter iter_type;

#if !(defined(__MRC__)||defined(__SC__))	//*TY 02/26/2000
  explicit 
#endif										//*TY 02/26/2000 - 
  num_put(size_t __refs = 0) : _BaseFacet(__refs) {}

# ifndef __STL_NO_BOOL
  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                bool __val) const {
    return do_put(__s, __f, __fill, __val);
  }
# endif
  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
               long __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                unsigned long __val) const {
    return do_put(__s, __f, __fill, __val);
  }

#ifdef __STL_LONG_LONG
  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                __STL_LONG_LONG __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                unsigned __STL_LONG_LONG __val) const {
    return do_put(__s, __f, __fill, __val);
  }
#endif

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                double __val) const {
    return do_put(__s, __f, __fill, (double)__val);
  }

#ifndef __STL_NO_LONG_DOUBLE
  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                long double __val) const {
    return do_put(__s, __f, __fill, __val);
  }
# endif

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                const void * __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  __STL_STATIC_MEMBER_DECLSPEC static locale::id id;

protected:
  ~num_put() {}   
# ifndef __STL_NO_BOOL
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, bool __val) const;
# endif
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, long __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, unsigned long __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, double __val) const;
#ifndef __STL_NO_LONG_DOUBLE
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, long double __val) const;
#endif

#ifdef __STL_LONG_LONG
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, __STL_LONG_LONG __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, 
                           unsigned __STL_LONG_LONG __val) const ;
#endif /* __STL_LONG_LONG */
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, const void* __val) const;
};

# ifdef __STL_USE_TEMPLATE_EXPORT
__STL_EXPORT_TEMPLATE_CLASS num_put<char, ostreambuf_iterator<char, char_traits<char> > >;
// __STL_EXPORT_TEMPLATE_CLASS num_put<char, char*>;
#  ifndef __STL_NO_WCHAR_T
__STL_EXPORT_TEMPLATE_CLASS num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >;
// __STL_EXPORT_TEMPLATE_CLASS num_put<wchar_t, wchar_t*>;
#  endif /* __STL_NO_WCHAR_T */
# endif

# if defined (__STL_EXPOSE_STREAM_IMPLEMENTATION)

template <class _Integer>
char* __STL_CALL
__write_integer_backward(char* __buf, ios_base::fmtflags __flags, _Integer __x);

void  __STL_CALL __string_to_float(const string&, float&);
void  __STL_CALL __string_to_float(const string&, double&);
void  __STL_CALL __string_to_float(const string&, long double&);

extern char* __STL_CALL __write_float(char*, ios_base::fmtflags, int, double);
extern char* __STL_CALL __write_float(char*, ios_base::fmtflags, int, long double);

#ifndef __STL_NO_WCHAR_T
extern wchar_t* __STL_CALL __convert_float_buffer(const char*, const char*, wchar_t*, const ctype<wchar_t>&, wchar_t);
#endif
extern void __STL_CALL __adjust_float_buffer(char*, char*, char);

extern char* __STL_CALL
__write_integer(char* buf, ios_base::fmtflags flags, long x);

extern ptrdiff_t __STL_CALL __insert_grouping(char* first, char* last, const string&, char, char, char, int);
#  ifndef __STL_NO_WCHAR_T
extern ptrdiff_t __STL_CALL __insert_grouping(wchar_t*, wchar_t*, const string&, wchar_t, wchar_t, wchar_t, int);
#  endif

# endif


__STL_END_NAMESPACE

#  if defined (__STL_EXPOSE_STREAM_IMPLEMENTATION) && ! defined (__STL_LINK_TIME_INSTANTIATION)
#   include <stl/_num_put.c>
#  endif

#endif /* __SGI_STL_INTERNAL_NUMERIC_FACETS_H */

// Local Variables:
// mode:C++
// End:

