// STLport configuration file
// It is internal STLport header - DO NOT include it directly

// system-dependent defines 

# if defined(__SunOS_5_5_1)
#  define __STL_NO_NATIVE_WIDE_FUNCTIONS 1
# endif

# if defined (__SunOS_5_8) && ( __cplusplus >= 199711L)
#  define __STL_HAS_NATIVE_FLOAT_ABS
# endif


#  define __STL_LONG_LONG  long long
// on solaris 2.x only ?

#if defined(_XOPEN_SOURCE) && (_XOPEN_VERSION - 0 >= 4)
# define __STL_RAND48 1
#endif

#  define __STL_LINK_TIME_INSTANTIATION 1

# if ! defined(_BOOL)
#  define __STL_NO_BOOL 1
# endif

// compatibility mode stuff
# if (__SUNPRO_CC >= 0x510) && (!defined (__SUNPRO_CC_COMPAT) || (__SUNPRO_CC_COMPAT == 5 ))
#  define __STL_NATIVE_INCLUDE_PATH ../CC/Cstd
#  define __STL_NATIVE_CPP_RUNTIME_INCLUDE_PATH ../CC
# elif (__SUNPRO_CC >= 0x500) && (!defined (__SUNPRO_CC_COMPAT) || (__SUNPRO_CC_COMPAT == 5 ))
#  define __STL_NATIVE_INCLUDE_PATH ../CC
# elif (defined (__SUNPRO_CC_COMPAT) && __SUNPRO_CC_COMPAT == 4)
#  define __STL_LIMITED_DEFAULT_TEMPLATES 1
#  define __STL_NATIVE_INCLUDE_PATH ../CC4
# else
#  define __STL_NATIVE_INCLUDE_PATH ../CC
# endif

#  if (__SUNPRO_CC >= 0x500 ) && ( defined (__STL_NO_NEW_IOSTREAMS) || defined (__STL_HAS_NO_NEW_IOSTREAMS) )
// if the project is set up to use libiostream (__STL_NO_NEW_IOSTREAMS should be defined then),
// use classic iostreams
#   define __STL_NATIVE_OLD_STREAMS_INCLUDE_PATH ../CCios
#  endif

# if (__SUNPRO_CC < 0x600)
// those are tested and proved not to work...

#  define __STL_STATIC_ARRAY_BUG 1
#  define __STL_STATIC_CONST_INIT_BUG 1

// this is not really true ; but use of new-style native headers bring in namespace problems,
// so it works better with our wrapper only.
#  define __STL_HAS_NO_NEW_C_HEADERS 1

#  define __STL_NO_CLASS_PARTIAL_SPECIALIZATION 1
#  define __STL_USE_OLD_HP_ITERATOR_QUERIES

# endif


// those do not depend on compatibility
# if (__SUNPRO_CC < 0x510)
#  define __STL_NO_TYPENAME_ON_RETURN_TYPE 1 
#  define __STL_NONTEMPL_BASE_MATCH_BUG 1
# endif


# if (__SUNPRO_CC < 0x510) || (defined (__SUNPRO_CC_COMPAT) && (__SUNPRO_CC_COMPAT < 5))

#  define __STL_NO_QUALIFIED_FRIENDS 1

// no partial , just for explicit one
#  define __STL_PARTIAL_SPEC_NEEDS_TEMPLATE_ARGS
#  define __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER 1

#  define __STL_NON_TYPE_TMPL_PARAM_BUG 1

#  define __STL_NO_MEMBER_TEMPLATES 1
#  define __STL_NO_MEMBER_TEMPLATE_KEYWORD 1

#  define __STL_NO_FRIEND_TEMPLATES 1
#  define __STL_NO_MEMBER_TEMPLATE_CLASSES 1

#  define __STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS

# endif

// Features that depend on compatibility switch
# if ( __SUNPRO_CC < 0x500 ) || (defined (__SUNPRO_CC_COMPAT) && (__SUNPRO_CC_COMPAT < 5))

#  define __STL_HAS_NO_NEW_IOSTREAMS 1

// in case of SGI iostreams, we have to rename our streams not to clash with those
// provided in native lib
# if defined (__SGI_STL_OWN_IOSTREAMS)
# define cin _STL_cin
# define cout _STL_cout
# define cerr _STL_cerr
# define clog _STL_clog
# define strstream _STL_strstream 
# define ostrstream _STL_ostrstream
# define istrstream _STL_istrstream
# define strstreambuf _STL_strstreambuf
# endif


#  define __STL_NO_NEW_NEW_HEADER 1
// #  define __STL_NO_RELOPS_NAMESPACE
#  define __STL_HAS_NO_NAMESPACES 1
#  define __STL_NEED_MUTABLE  1
#  define __STL_NO_BAD_ALLOC 1
#  define __STL_NO_EXCEPTION_HEADER 1
#  define __STL_NATIVE_C_INCLUDE_PATH ../include
# elif (__SUNPRO_CC < 0x510)
#  define __STL_NATIVE_C_HEADER(header) <../CC/##header##.SUNWCCh>
#  define __STL_NATIVE_CPP_C_HEADER(header) <../CC/##header##.SUNWCCh>
# else
#  define __STL_NATIVE_C_INCLUDE_PATH /usr/include
#  define __STL_NATIVE_CPP_C_INCLUDE_PATH ../CC/std
# endif



#  if ( __SUNPRO_CC < 0x500 )

# undef __STL_NATIVE_C_HEADER
# undef __STL_NATIVE_CPP_C_HEADER

#   define wint_t __wint_t 
// famous CC 4.2 bug
#   define __STL_INLINE_STRING_LITERAL_BUG 1
// /usr/include
#   define __STL_NATIVE_C_INCLUDE_PATH ../include

// 4.2 cannot handle iterator_traits<_Tp>::iterator_category as return type ;(
#  define __STL_USE_OLD_HP_ITERATOR_QUERIES

// 4.2 does not like it
#  undef  __STL_PARTIAL_SPEC_NEEDS_TEMPLATE_ARGS

#  define __STL_LIMITED_DEFAULT_TEMPLATES 1

#  define __STL_NEED_TYPENAME 1
#  define __STL_NEED_EXPLICIT 1
#  define __STL_UNINITIALIZABLE_PRIVATE 1
#  define __STL_NO_BAD_ALLOC 1
#  define __SGI_STL_NO_ARROW_OPERATOR 1
#  define __STL_NO_PROXY_ARROW_OPERATOR 1
#  define __STL_DEFAULT_CONSTRUCTOR_BUG 1
#  define __STL_GLOBAL_NESTED_RETURN_TYPE_PARAM_BUG 1

#   if ( __SUNPRO_CC < 0x420 )
#    define __STL_NO_PARTIAL_SPECIALIZATION_SYNTAX 1
#    define __STL_NO_NEW_STYLE_CASTS 1
#    define __STL_NO_METHOD_SPECIALIZATION 1

#    if ( __SUNPRO_CC > 0x401 )
#     if (__SUNPRO_CC==0x410)
#      define __STL_BASE_TYPEDEF_OUTSIDE_BUG  1
#     endif
#    else
   // SUNPro C++ 4.0.1
#     define __STL_BASE_MATCH_BUG          1
#     define __STL_BASE_TYPEDEF_BUG        1
#      if ( __SUNPRO_CC < 0x401 )
        __GIVE_UP_WITH_STL(SUNPRO_401)
#      endif
#    endif /* 4.0.1 */
#   endif /* 4.2 */

#  endif /* <  5.0 */

