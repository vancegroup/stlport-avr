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


#ifndef __SGI_STL_INTERNAL_MESSAGES_H
#define __SGI_STL_INTERNAL_MESSAGES_H

#ifndef __SGI_STL_IOS_BASE_H
# include <stl/_ios_base.h>
#endif

//# ifndef __STL_C_LOCALE_H
//#  include <stl/c_locale.h>
//# endif

#ifndef __SGI_STL_STRING_H
# include <stl/_string.h>
#endif

__STL_BEGIN_NAMESPACE

// messages facets

class messages_base {
public:
  typedef int catalog;
};

template <class _CharT> class messages {};

class _Messages;

__STL_TEMPLATE_NULL
class __STL_CLASS_DECLSPEC messages<char> : public locale::facet, public messages_base 
{
  friend class _Locale;
public:
  typedef messages_base::catalog catalog;
  typedef char                   char_type;
  typedef string    string_type;

  explicit messages(size_t __refs = 0);

  catalog open(const string& __fn, const locale& __loc) const
    { return do_open(__fn, __loc); }
  string_type get(catalog __c, int __set, int __msgid,
		  const string_type& __dfault) const
    { return do_get(__c, __set, __msgid, __dfault); }
  inline void close(catalog __c) const
    { do_close(__c); }

  __STL_STATIC_MEMBER_DECLSPEC static locale::id id;

  messages(_Messages*);

protected:
   messages(size_t, _Locale_messages*);
  ~messages();

  virtual catalog     do_open(const string& __fn, const locale& __loc) const;
  virtual string_type do_get(catalog __c, int __set, int __msgid,
                             const string_type& __dfault) const;
  virtual void        do_close(catalog __c) const;

  void _M_initialize(const char* __name);

private:
  _Messages* _M_impl;
};

# if !defined (__STL_NO_WCHAR_T)

__STL_TEMPLATE_NULL
class __STL_CLASS_DECLSPEC messages<wchar_t> : public locale::facet, public messages_base 
{
  friend class _Locale;
public:
  typedef messages_base::catalog catalog;
  typedef wchar_t                char_type;
  typedef wstring  string_type;

  explicit messages(size_t __refs = 0);
  
  inline catalog open(const string& __fn, const locale& __loc) const
    { return do_open(__fn, __loc); }
  inline string_type get(catalog __c, int __set, int __msgid,
                         const string_type& __dfault) const
    { return do_get(__c, __set, __msgid, __dfault); }
  inline void close(catalog __c) const
    { do_close(__c); }

  __STL_STATIC_MEMBER_DECLSPEC static locale::id id;

  messages(_Messages*);

protected:

  messages(size_t, _Locale_messages*);
  ~messages();

  virtual catalog     do_open(const string& __fn, const locale& __loc) const;
  virtual string_type do_get(catalog __c, int __set, int __msgid,
                             const string_type& __dfault) const;
  virtual void        do_close(catalog __c) const;

  void _M_initialize(const char* __name);

private:
  _Messages* _M_impl;
};

# endif /* WCHAR_T */

template <class _CharT> class messages_byname {};

__STL_TEMPLATE_NULL
class __STL_CLASS_DECLSPEC messages_byname<char> : public messages<char> {
public:
  typedef messages_base::catalog catalog;
  typedef string     string_type;

  explicit messages_byname(const char* __name, size_t __refs = 0);

protected:
  ~messages_byname();
};

# ifndef __STL_NO_WCHAR_T
__STL_TEMPLATE_NULL
class __STL_CLASS_DECLSPEC messages_byname<wchar_t> : public messages<wchar_t> {
public:
  typedef messages_base::catalog catalog;
  typedef wstring                string_type;

  explicit messages_byname(const char* __name, size_t __refs = 0);

protected:
  ~messages_byname();
};
# endif /* WCHAR_T */

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_MESSAGES_H */

// Local Variables:
// mode:C++
// End:

