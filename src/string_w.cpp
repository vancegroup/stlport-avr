#include "stlport_prefix.h"
#include <stl/_string.h>

__STL_BEGIN_NAMESPACE
# ifndef __STL_NO_FORCE_INSTANTIATE
#  ifndef __STL_NO_WCHAR_T
template class __STL_CLASS_DECLSPEC allocator<wchar_t>;
template class __STL_CLASS_DECLSPEC _String_base<wchar_t, allocator<wchar_t> >;
# ifdef __STL_DEBUG
template class __STL_CLASS_DECLSPEC _Nondebug_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
# endif
template class __STL_CLASS_DECLSPEC basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
#  endif
# endif
__STL_END_NAMESPACE

