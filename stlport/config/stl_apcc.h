// STLport config file for Apogee 4.x

#  define __STL_NO_NEW_NEW_HEADER 1
#  define __STL_HAS_NO_NEW_IOSTREAMS 1
#  define __STL_HAS_NO_NEW_C_HEADERS 1

#  define __STL_RAND48 1
#  define __STL_LONG_LONG long long
#  define __STL_NO_BAD_ALLOC 1
#  define __STL_NO_MEMBER_TEMPLATE_KEYWORD 1
#  define __STL_NON_TYPE_TMPL_PARAM_BUG 1
// #  define __STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS 1
#  define __STL_NO_EXCEPTION_HEADER 1

# undef  __STL_LINK_TIME_INSTANTIATION
# define __STL_LINK_TIME_INSTANTIATION 1

# ifdef __STDLIB
#  undef __STL_HAS_NO_NEW_IOSTREAMS
#  undef __STL_NO_NEW_C_HEADERS
#  undef __STL_NO_NEW_NEW_HEADER
#  undef __STL_NO_BAD_ALLOC
#  undef __STL_LONG_LONG
# else
#  undef  __STL_NO_EXCEPTION_SPEC
#  define __STL_NO_EXCEPTION_SPEC 1
# endif


