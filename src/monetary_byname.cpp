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

#include <stl/_monetary.h>
// #include <stl/_ostream.h>
// #include <stl/_istream.h>
#include "c_locale.h"


__STL_BEGIN_NAMESPACE

static void _Init_monetary_formats(money_base::pattern& pos_format,
                                    money_base::pattern& neg_format,
                                    _Locale_monetary * monetary) {
  switch (_Locale_p_sign_posn(monetary)) {
    case 0: case 1:
      pos_format.field[0] = (char) money_base::sign;
      if (_Locale_p_cs_precedes(monetary)) {
	pos_format.field[1] = (char) money_base::symbol;
	if (_Locale_p_sep_by_space(monetary)) {
	  pos_format.field[2] = (char) money_base::space;
	  pos_format.field[3] = (char) money_base::value;
	}
	else {
	  pos_format.field[2] = (char) money_base::value;
	  pos_format.field[3] = (char) money_base::none;
	}
      }
      else {
	pos_format.field[2] = (char) money_base::value;
	if (_Locale_p_sep_by_space(monetary)) {
	  pos_format.field[2] = (char) money_base::space;
	  pos_format.field[3] = (char) money_base::symbol;
	}
	else {
	  pos_format.field[2] = (char) money_base::symbol;
	  pos_format.field[3] = (char) money_base::none;
	}
      }       
      break;
    case 2:
      if (_Locale_p_cs_precedes(monetary)) {
	pos_format.field[0] = (char) money_base::symbol;
	if (_Locale_p_sep_by_space(monetary)) {
	  pos_format.field[1] = (char) money_base::space;
	  pos_format.field[2] = (char) money_base::value;
	  pos_format.field[3] = (char) money_base::sign;
	}
	else {
	  pos_format.field[1] = (char) money_base::value;
	  pos_format.field[2] = (char) money_base::sign;
	  pos_format.field[3] = (char) money_base::none;
	}
      }
      else {
	pos_format.field[1] = (char) money_base::value;
	if (_Locale_p_sep_by_space(monetary)) {
	  pos_format.field[1] = (char) money_base::space;
	  pos_format.field[2] = (char) money_base::symbol;
	  pos_format.field[3] = (char) money_base::sign;
	}
	else {
	  pos_format.field[1] = (char) money_base::symbol;
	  pos_format.field[2] = (char) money_base::sign;
	  pos_format.field[3] = (char) money_base::none;
	}
      }
      break;
    case 3:
      if (_Locale_p_cs_precedes(monetary)) {
	pos_format.field[0] = (char) money_base::sign;
	pos_format.field[1] = (char) money_base::symbol;
	if (_Locale_p_sep_by_space(monetary)) {
	  pos_format.field[2] = (char) money_base::space;
	  pos_format.field[3] = (char) money_base::value;
	}
	else {
	  pos_format.field[2] = (char) money_base::value;
	  pos_format.field[3] = (char) money_base::none;
	}
      }
      else {
	pos_format.field[0] = (char) money_base::value;
	pos_format.field[1] = (char) money_base::sign;
	pos_format.field[2] = (char) money_base::symbol;
	pos_format.field[3] = (char) money_base::none;
      }
      break;
    case 4: default:
      if (_Locale_p_cs_precedes(monetary)) {
	pos_format.field[0] = (char) money_base::symbol;
	pos_format.field[1] = (char) money_base::sign;
	pos_format.field[2] = (char) money_base::value;
	pos_format.field[3] = (char) money_base::none;
      }
      else {
	pos_format.field[0] = (char) money_base::value;
	if (_Locale_p_sep_by_space(monetary)) {
	  pos_format.field[1] = (char) money_base::space;
	  pos_format.field[2] = (char) money_base::symbol;
	  pos_format.field[3] = (char) money_base::sign;
	}
        else {
	  pos_format.field[1] = (char) money_base::symbol;
	  pos_format.field[2] = (char) money_base::sign;
	  pos_format.field[3] = (char) money_base::none;
	}
      }
    break;
  }

  switch (_Locale_n_sign_posn(monetary)) {
    case 0: case 1:
      neg_format.field[0] = (char) money_base::sign;
      if (_Locale_n_cs_precedes(monetary)) {
        neg_format.field[1] = (char) money_base::symbol;
	if (_Locale_n_sep_by_space(monetary)) {
	  neg_format.field[2] = (char) money_base::space;
	  neg_format.field[3] = (char) money_base::value;
	}
	else {
	  neg_format.field[2] = (char) money_base::value;
	  neg_format.field[3] = (char) money_base::none;
	}
      }
      else {
	neg_format.field[2] = (char) money_base::value;
	if (_Locale_n_sep_by_space(monetary)) {
	  neg_format.field[2] = (char) money_base::space;
	  neg_format.field[3] = (char) money_base::symbol;
	}
	else {
	  neg_format.field[2] = (char) money_base::symbol;
	  neg_format.field[3] = (char) money_base::none;
	}
      }       
      break;
    case 2:
      if (_Locale_n_cs_precedes(monetary)) {
	neg_format.field[0] = (char) money_base::symbol;
	if (_Locale_n_sep_by_space(monetary)) {
	  neg_format.field[1] = (char) money_base::space;
	  neg_format.field[2] = (char) money_base::value;
	  neg_format.field[3] = (char) money_base::sign;
	}
	else {
	  neg_format.field[1] = (char) money_base::value;
	  neg_format.field[2] = (char) money_base::sign;
	  neg_format.field[3] = (char) money_base::none;
	}
      }
      else {
	neg_format.field[1] = (char) money_base::value;
	if (_Locale_n_sep_by_space(monetary)) {
	  neg_format.field[1] = (char) money_base::space;
	  neg_format.field[2] = (char) money_base::symbol;
	  neg_format.field[3] = (char) money_base::sign;
	}
	else {
	  neg_format.field[1] = (char) money_base::symbol;
	  neg_format.field[2] = (char) money_base::sign;
	  neg_format.field[3] = (char) money_base::none;
	}
      }
      break;
    case 3:
      if (_Locale_n_cs_precedes(monetary)) {
	neg_format.field[0] = (char) money_base::sign;
	neg_format.field[1] = (char) money_base::symbol;
	if (_Locale_n_sep_by_space(monetary)) {
	  neg_format.field[2] = (char) money_base::space;
	  neg_format.field[3] = (char) money_base::value;
	}
	else {
	  neg_format.field[2] = (char) money_base::value;
	  neg_format.field[3] = (char) money_base::none;
	}
      }
      else {
	neg_format.field[0] = (char) money_base::value;
	neg_format.field[1] = (char) money_base::sign;
	neg_format.field[2] = (char) money_base::symbol;
	neg_format.field[3] = (char) money_base::none;
      }
      break;
    case 4: default:
      if (_Locale_n_cs_precedes(monetary)) {
	neg_format.field[0] = (char) money_base::symbol;
	neg_format.field[1] = (char) money_base::sign;
	neg_format.field[2] = (char) money_base::value;
	neg_format.field[3] = (char) money_base::none;
      }
      else {
	neg_format.field[0] = (char) money_base::value;
	if (_Locale_n_sep_by_space(monetary)) {
	  neg_format.field[1] = (char) money_base::space;
	  neg_format.field[2] = (char) money_base::symbol;
	  neg_format.field[3] = (char) money_base::sign;
	}
        else {
	  neg_format.field[1] = (char) money_base::symbol;
	  neg_format.field[2] = (char) money_base::sign;
	  neg_format.field[3] = (char) money_base::none;
	}
      }
      break;
  }
}


//
// moneypunct_byname<>
//

_Locale_monetary* __acquire_monetary(const char* name);
void __release_monetary(_Locale_monetary* mon);

moneypunct_byname<char, true>::moneypunct_byname(const char * name,
						 size_t refs):
  moneypunct<char, true>(refs),
  _M_monetary(__acquire_monetary(name))
{
  if (!_M_monetary)
    locale::_M_throw_runtime_error();
  _Init_monetary_formats(_M_pos_format, _M_neg_format, _M_monetary);
}

moneypunct_byname<char, true>::~moneypunct_byname()
{
  __release_monetary(_M_monetary);
}

char moneypunct_byname<char, true>::do_decimal_point() const 
  {return _Locale_mon_decimal_point(_M_monetary);}

char moneypunct_byname<char, true>::do_thousands_sep() const
  {return _Locale_mon_thousands_sep(_M_monetary);}

string moneypunct_byname<char, true>::do_grouping() const
  {return _Locale_mon_grouping(_M_monetary);}

string moneypunct_byname<char, true>::do_curr_symbol() const
  {return _Locale_int_curr_symbol(_M_monetary);}

string moneypunct_byname<char, true>::do_positive_sign() const
  {return _Locale_positive_sign(_M_monetary);}

string moneypunct_byname<char, true>::do_negative_sign() const
  {return _Locale_negative_sign(_M_monetary);}

int moneypunct_byname<char, true>::do_frac_digits() const 
  {return _Locale_int_frac_digits(_M_monetary);}

moneypunct_byname<char, false>::moneypunct_byname(const char * name,
						  size_t refs):
  moneypunct<char, false>(refs),
  _M_monetary(__acquire_monetary(name))
{
  if (!_M_monetary)
    locale::_M_throw_runtime_error();
  _Init_monetary_formats(_M_pos_format, _M_neg_format, _M_monetary);
}

moneypunct_byname<char, false>::~moneypunct_byname()
{
  __release_monetary(_M_monetary);
}

char moneypunct_byname<char, false>::do_decimal_point() const
  {return _Locale_mon_decimal_point(_M_monetary);}

char moneypunct_byname<char, false>::do_thousands_sep() const
  {return _Locale_mon_thousands_sep(_M_monetary);}

string moneypunct_byname<char, false>::do_grouping() const
  {return _Locale_mon_grouping(_M_monetary);}

string moneypunct_byname<char, false>::do_curr_symbol() const
  {return _Locale_currency_symbol(_M_monetary);}

string moneypunct_byname<char, false>::do_positive_sign() const
  {return _Locale_positive_sign(_M_monetary);}

string moneypunct_byname<char, false>::do_negative_sign() const
  {return _Locale_negative_sign(_M_monetary);}

int moneypunct_byname<char, false>::do_frac_digits() const 
  {return _Locale_frac_digits(_M_monetary);}

//
// moneypunct_byname<wchar_t>
//
# ifndef __STL_NO_WCHAR_T

moneypunct_byname<wchar_t, true>::moneypunct_byname(const char * name,
						 size_t refs):
  moneypunct<wchar_t, true>(refs),
  _M_monetary(__acquire_monetary(name))
{
  if (!_M_monetary)
    locale::_M_throw_runtime_error();
  _Init_monetary_formats(_M_pos_format, _M_neg_format, _M_monetary);
}

moneypunct_byname<wchar_t, true>::~moneypunct_byname() 
{
  __release_monetary(_M_monetary);
}

wchar_t moneypunct_byname<wchar_t, true>::do_decimal_point() const
  {return _Locale_mon_decimal_point(_M_monetary);}

wchar_t moneypunct_byname<wchar_t, true>::do_thousands_sep() const
  {return _Locale_mon_thousands_sep(_M_monetary);}

string moneypunct_byname<wchar_t, true>::do_grouping() const
  {return _Locale_mon_grouping(_M_monetary);}

wstring moneypunct_byname<wchar_t, true>::do_curr_symbol() const
{
  string str = _Locale_int_curr_symbol(_M_monetary);
# if defined (__STL_NO_MEMBER_TEMPLATES) || defined (__STL_MSVC)
  wstring result(wstring::_Reserve_t(), str.size());
  copy(str.begin(), str.end(), result.begin());
# else
  wstring result(str.begin(), str.end());
# endif
  return result;
}

wstring moneypunct_byname<wchar_t, true>::do_positive_sign() const
{
  string str = _Locale_positive_sign(_M_monetary);
# if defined (__STL_NO_MEMBER_TEMPLATES) || defined (__STL_MSVC)
  wstring result(wstring::_Reserve_t(), str.size());
  copy(str.begin(), str.end(), result.begin());
# else
  wstring result(str.begin(), str.end());
# endif
  return result;
}


wstring moneypunct_byname<wchar_t, true>::do_negative_sign() const
{
  string str = _Locale_negative_sign(_M_monetary);
# if defined (__STL_NO_MEMBER_TEMPLATES) || defined (__STL_MSVC) 
  wstring result(wstring::_Reserve_t(), str.size());
  copy(str.begin(), str.end(), result.begin());
# else
  wstring result(str.begin(), str.end());
# endif
  return result;
}

int moneypunct_byname<wchar_t, true>::do_frac_digits() const 
  {return _Locale_int_frac_digits(_M_monetary);}

moneypunct_byname<wchar_t, false>::moneypunct_byname(const char * name,
						 size_t refs):
  moneypunct<wchar_t, false>(refs),
  _M_monetary(__acquire_monetary(name))
{
  if (!_M_monetary)
    locale::_M_throw_runtime_error() ;
  _Init_monetary_formats(_M_pos_format, _M_neg_format, _M_monetary);
}

moneypunct_byname<wchar_t, false>::~moneypunct_byname()
{
  __release_monetary(_M_monetary);
}

wchar_t moneypunct_byname<wchar_t, false>::do_decimal_point() const
  {return _Locale_mon_decimal_point(_M_monetary);}

wchar_t moneypunct_byname<wchar_t, false>::do_thousands_sep() const
  {return _Locale_mon_thousands_sep(_M_monetary);}

string moneypunct_byname<wchar_t, false>::do_grouping() const
  {return _Locale_mon_grouping(_M_monetary);}

wstring moneypunct_byname<wchar_t, false>::do_curr_symbol() const
{
  string str =  _Locale_currency_symbol(_M_monetary);
# if defined (__STL_NO_MEMBER_TEMPLATES) || defined (__STL_MSVC)
  wstring result(wstring::_Reserve_t(), str.size());
  copy(str.begin(), str.end(), result.begin());
# else
  wstring result(str.begin(), str.end());
# endif
  return result;
}

wstring moneypunct_byname<wchar_t, false>::do_positive_sign() const
{
  string str = _Locale_positive_sign(_M_monetary);
# if defined (__STL_NO_MEMBER_TEMPLATES) || defined (__STL_MSVC)
  wstring result(wstring::_Reserve_t(), str.size());
  copy(str.begin(), str.end(), result.begin());
# else
  wstring result(str.begin(), str.end());
# endif
  return result;
}

wstring moneypunct_byname<wchar_t, false>::do_negative_sign() const
{
  string str = _Locale_negative_sign(_M_monetary);
# if defined (__STL_NO_MEMBER_TEMPLATES) || defined (__STL_MSVC)
  wstring result(wstring::_Reserve_t(), str.size());
  copy(str.begin(), str.end(), result.begin());
# else
  wstring result(str.begin(), str.end());
# endif
  return result;
}

int moneypunct_byname<wchar_t, false>::do_frac_digits() const 
  {return _Locale_frac_digits(_M_monetary);}

# endif

__STL_END_NAMESPACE  

// Local Variables:
// mode:C++
// End:
