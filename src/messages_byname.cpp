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

# include "message_facets.h"

//Must include to use typeid below
#include <typeinfo>

__STL_BEGIN_NAMESPACE

void _Catalog_locale_map::insert(int key, const locale& L)
{
# ifdef __STL_NO_WCHAR_T
  typedef char _Char;
# else
  typedef wchar_t _Char;
# endif
#if !defined(__STL_NO_TYPEINFO)
  // Don't bother to do anything unless we're using a non-default ctype facet
  __STL_TRY {
    typedef ctype<_Char> wctype;
    const wctype& wct = use_facet<wctype>(L);
    const wctype* zz = (const wctype*)0;
    if (typeid(&wct) != typeid(zz)) {
      if (!M)
        M = new hash_map<int, locale, hash<int>, equal_to<int> >;

#if defined(__SC__)			//*TY 06/01/2000 - added workaround for SCpp
      if (!M) delete M;		//*TY 06/01/2000 - it forgets to generate dtor for hash_map<> class. This fake code forces to generate one.
#endif						//*TY 06/01/2000 - 

      if (M->find(key) == M->end())
        M->insert(pair<const int, locale>(key, L));
    }
  }
  __STL_CATCH_ALL {}
# endif /* __STL_NO_TYPEINFO */
}

void _Catalog_locale_map::erase(int key)
{
  if (M)
    M->erase(key);
}

locale _Catalog_locale_map::lookup(int key) const
{
  if (M) {
    hash_map<int, locale, hash<int>, equal_to<int> >::iterator i = M->find(key);
    return i != M->end() ? (*i).second : locale::classic();
  }
  else
    return locale::classic();
}


//----------------------------------------------------------------------
//
//

_Messages_impl::_Messages_impl(bool is_wide) : 
  _M_message_obj(0), _M_map(0)
{ 
  _M_delete = true;
  if (is_wide) 
    _M_map = new _Catalog_locale_map;
  _M_message_obj = __acquire_messages("C");
}

_Messages_impl::_Messages_impl(bool is_wide, _Locale_messages* msg_obj ) : 
  _M_message_obj(msg_obj), _M_map(0)
{ 
  _M_delete = true;
  if (is_wide) 
    _M_map = new _Catalog_locale_map;
}

_Messages_impl::~_Messages_impl()
{
  __release_messages(_M_message_obj);
  if (_M_map) delete _M_map;
}

int _Messages_impl::do_open(const string& filename, const locale& L) const
{  
  int result = _M_message_obj
    ? _Locale_catopen(_M_message_obj, filename.c_str())
    : -1;

  if (result >= 0 && _M_map != 0)
    _M_map->insert(result, L);

  return result;
}

string _Messages_impl::do_get(catalog cat,
                              int set, int p_id, const string& dfault) const
{
  return _M_message_obj != 0 && cat >= 0
    ? string(_Locale_catgets(_M_message_obj, cat, set, p_id, dfault.c_str()))
    : dfault;
}

# ifndef __STL_NO_WCHAR_T

wstring
_Messages_impl::do_get(catalog thecat,
		       int set, int p_id, const wstring& dfault) const
{
  typedef ctype<wchar_t> wctype;
  const wctype& ct = use_facet<wctype>(_M_map->lookup(thecat));

  const char* str = _Locale_catgets(_M_message_obj, thecat, set, p_id, "");

  // Verify that the lookup failed; an empty string might represent success.
  if (!str)
    return dfault;
  else if (str[0] == '\0') {
    const char* str2 = _Locale_catgets(_M_message_obj, thecat, set, p_id, "*");
    if (!str2 || strcmp(str2, "*") == 0)
      return dfault;
  }

  // str is correct.  Now we must widen it to get a wstring.
  size_t n = strlen(str);

  // NOT PORTABLE.  What we're doing relies on internal details of the 
  // string implementation.  (Contiguity of string elements.)
  wstring result(n, wchar_t(0));
  ct.widen(str, str + n, &*result.begin());
  return result;
}

# endif

void _Messages_impl::do_close(catalog thecat) const
{
  if (_M_message_obj)
    _Locale_catclose(_M_message_obj, thecat);
  if (_M_map) _M_map->erase(thecat);
}


//----------------------------------------------------------------------
// messages<char>

messages<char>::messages(size_t refs)  : 
  _BaseFacet(refs), _M_impl(new _Messages_impl(false))
{}

messages<char>::messages(size_t refs, _Locale_messages* msg_obj) : _BaseFacet(refs), 
  _M_impl(new _Messages_impl(false, msg_obj))
{}


//----------------------------------------------------------------------
// messages<wchar_t>

messages<wchar_t>::messages(size_t refs)  : 
  _BaseFacet(refs), _M_impl(new _Messages_impl(true))
{}

//----------------------------------------------------------------------
// messages_byname<char>

messages_byname<char>::messages_byname(const char* name, size_t refs)
  : messages<char>(refs, name ? __acquire_messages(name) : 0)
{}

messages_byname<char>::~messages_byname()
{}

# ifndef __STL_NO_WCHAR_T


messages<wchar_t>::messages(size_t refs, _Locale_messages* msg_obj)
  : _BaseFacet(refs),
    _M_impl(new _Messages_impl(true, msg_obj))
{}

//----------------------------------------------------------------------
// messages_byname<wchar_t>


messages_byname<wchar_t>::messages_byname(const char* name, size_t refs)
  : messages<wchar_t>(refs, name ? __acquire_messages(name) : 0)
{}

messages_byname<wchar_t>::~messages_byname()
{}

# endif

__STL_END_NAMESPACE

// Local Variables:
// mode:C++
// End:

