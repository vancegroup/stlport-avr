/* STLport configuration file
 * It is internal STLport header - DO NOT include it directly
 */

/* Systems having GLIBC installed have different traits */
#if ! defined (__STL_USE_GLIBC) && \
   ( defined (__linux__) || defined (__CYGWIN__) )
# define __STL_USE_GLIBC
#endif

#   define __STL_NO_MEMBER_TEMPLATE_KEYWORD

#   define __STL_HAS_NO_NEW_C_HEADERS     1

# if defined(__FreeBSD__) || defined (__hpux)
#  define __STL_NO_WCHAR_T
# endif

# if defined(__MINGW32__)
/* Mingw32, egcs compiler using the Microsoft C runtime */
#   undef  __STL_NO_DRAND48
#   define __STL_NO_DRAND48
#   ifdef _MT
#     define _REENTRANT
#   endif
#  define __STL_IMPORT_DECLSPEC __attribute__((dllimport))
#  define __STL_EXPORT_DECLSPEC __attribute__((dllexport))
#  define __STL_CLASS_IMPORT_DECLSPEC __attribute__((dllimport))
#  define __STL_CLASS_EXPORT_DECLSPEC __attribute__((dllexport))
#  define __STL_CALL __cdecl 

#  if defined (__STL_USE_DYNAMIC_LIB)
#   define __STL_USE_DECLSPEC 1
#  endif

# endif

/* cygwin is a little bit different, but most traits are same. */
# if defined ( __STL_USE_GLIBC  ) && !defined (__CYGWIN__) || defined (__MINGW32__)
# else
#   define __STL_NO_NATIVE_MBSTATE_T      1
# endif

/* g++ 2.7.x and above */
#   define __STL_LONG_LONG long long 
#   define __STL_NO_NATIVE_WIDE_FUNCTIONS 1
#   define __STL_NO_NATIVE_WIDE_STREAMS   1
#   define __STL_HAS_NO_NEW_IOSTREAMS     1

# ifdef __HONOR_STD
#   define __STL_VENDOR_GLOBAL_CSTD       1
# else
/* dwa 12/18/99 -- fhonor-std doesn't actually work in gcc 2.95.2
 * also note that __HONOR_STD is not automatically defined in 
 * accordance with -fhonor-std. */
#   define __STL_VENDOR_GLOBAL_EXCEPT_STD 1
# endif

#   if (__GNUC_MINOR__ < 95)
#     define __STL_VENDOR_GLOBAL_EXCEPT_STD 1
/* egcs fails to initialize builtin types in expr. like this : new(p) char();  */
#     define __STL_DEFAULT_CONSTRUCTOR_BUG 1
#   else
// boris : this is temporary
#    undef __STL_INCOMPLETE_EXCEPTION_HEADER
#   endif

#   if (__GNUC_MINOR__ < 90) /* egcs 1.1 */
#     define __STL_NO_TEMPLATE_CONVERSIONS
#     define __STL_NO_MEMBER_TEMPLATE_CLASSES 1
#     define __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER 1
#     define __STL_NO_FRIEND_TEMPLATES 1
#     define __STL_HAS_NO_NAMESPACES 1
#     define __STL_NO_METHOD_SPECIALIZATION 1
/*  DJGPP doesn't seem to implement it in 2.8.x */
#     ifdef DJGPP
#      define  __STL_NO_STATIC_TEMPLATE_DATA 1
#     endif
#   endif

#  if __GNUC__ <= 2 && __GNUC_MINOR__ <= 7 && ! defined (__CYGWIN32__)
/* Will it work with 2.6 ? I doubt it. */
#   if ( __GNUC_MINOR__ < 6 )
    __GIVE_UP_WITH_STL(GCC_272);
#   endif

# define  __STL_NO_RELOPS_NAMESPACE
# define  __STL_NON_TYPE_TMPL_PARAM_BUG
# define  __STL_LIMITED_DEFAULT_TEMPLATES 1
# define  __STL_DEFAULT_TYPE_PARAM 1
# define  __STL_NO_BAD_ALLOC
# define  __SGI_STL_NO_ARROW_OPERATOR 1
# ifndef __STL_NO_STATIC_TEMPLATE_DATA
#  define  __STL_NO_STATIC_TEMPLATE_DATA
# endif
# define  __STL_NO_MEMBER_TEMPLATES 1
# define  __STL_NO_CLASS_PARTIAL_SPECIALIZATION 1
# define  __STL_NO_METHOD_SPECIALIZATION 1

#  if !defined (__CYGWIN32__) 
#   define __STL_NESTED_TYPE_PARAM_BUG   1
#   define __STL_BASE_MATCH_BUG       1
/*  unused operators are required (forward) */
#   define  __STL_CONST_CONSTRUCTOR_BUG 
#   define __STL_NO_DEFAULT_NON_TYPE_PARAM
#  endif
#   define __STL_NO_PARTIAL_SPECIALIZATION_SYNTAX 1
#   define __STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS 1
#   define __STL_NO_EXCEPTION_HEADER 1
#  else /* ! <= 2.7.* */
#  endif /* ! <= 2.7.* */

/* static template data members workaround strategy for gcc tries
 * to use weak symbols.
 * if you don't want to use that, #define __STL_WEAK_ATTRIBUTE=0 ( you'll
 * have to put "#define __PUT_STATIC_DATA_MEMBERS_HERE" line in one of your
 * compilation unit ( or CFLAGS for it ) _before_ including any STL header ).
 */
#   if defined (__STL_NO_STATIC_TEMPLATE_DATA) && ! defined (__STL_WEAK_ATTRIBUTE )
/* systems using GNU ld or format that supports weak symbols
   may use "weak" attribute
   Linux & Solaris ( x86 & SPARC ) are being auto-recognized here */
#    if defined(__STL_GNU_LD) || defined(__ELF__) || defined (__CYGWIN__) || \
     (( defined (__SVR4) || defined ( __svr4__ )) && \
      ( defined (sun) || defined ( __sun__ )))
#     define __STL_WEAK_ATTRIBUTE 1
#    endif
#   endif /* __STL_WEAK_ATTRIBUTE */


/* strict ANSI prohibits "long long" ( gcc) */
#  if defined ( __STRICT_ANSI__ )
#    undef __STL_LONG_LONG
// #    define __STL_STRICT_ANSI 1
#  endif

# if !defined (__STRICT_ANSI__) || defined (__BUILDING_STLPORT)
#    define __STL_USE_TEMPLATE_EXPORT
#    define __STL_EXPORT_TEMPLATE_KEYWORD extern
#    define __STL_IMPORT_TEMPLATE_KEYWORD extern
# endif

#   ifndef __EXCEPTIONS
#     undef  __STL_HAS_NO_EXCEPTIONS
#     define __STL_HAS_NO_EXCEPTIONS  1
#   endif

#if (__GNUC_MINOR__ < 8)

# define __STL_NO_SGI_IOSTREAMS 1
# undef  __SGI_STL_OWN_IOSTREAMS
# define __STL_NATIVE_INCLUDE_PATH ../g++-include

# if defined ( __STL_NO_STATIC_TEMPLATE_DATA )
#   define __STL_STATIC_TEMPLATE_DATA 0
#   if !defined ( __STL_WEAK_ATTRIBUTE )
#    define __STL_WEAK_ATTRIBUTE 0
#   endif
# else
#   define __STL_STATIC_TEMPLATE_DATA 1
# endif

/* tuning of static template data members workaround */
# if ( __STL_STATIC_TEMPLATE_DATA < 1 )
#  if ( __STL_WEAK_ATTRIBUTE > 0 )
#   define __STL_WEAK __attribute__ (( weak ))
#  else
#   define __STL_WEAK
#  endif /* __STL_WEAK_ATTRIBUTE */

#   ifdef __PUT_STATIC_DATA_MEMBERS_HERE
#    define __DECLARE_INSTANCE(type,item,init) type item __STL_WEAK init
#   else
#    define __DECLARE_INSTANCE(type,item,init)
#   endif /* __PUT_STATIC_DATA_MEMBERS_HERE */

# endif /* __STL_STATIC_TEMPLATE_DATA */

#else

// gcc-2.95.0 used to use "g++-3" directory which has been changed to "g++" in
// system-dependent "include" for 2.95.2 except for Cygwin and Mingw packages.
// I expect "g++-3" not being used in later releases.
// If your installation use "g++-3" include directory for any reason (pre-2.95.2 or Win binary kit),
// please change the macro below to point to your directory. 
# if (__GNUC_MINOR__ == 95 && ( defined (__CYGWIN__) || defined (__MINGW32__) ) )
#   define __STL_NATIVE_INCLUDE_PATH g++-3
# else
#   define __STL_NATIVE_INCLUDE_PATH g++
# endif

# ifndef __FreeBSD__
// <exception> et al
#  define __STL_NATIVE_CPP_RUNTIME_INCLUDE_PATH ../include
# endif

#endif /* GNUC_MINOR < 8 */

# define __STL_NATIVE_CPP_C_INCLUDE_PATH __STL_NATIVE_INCLUDE_PATH
# define __STL_NATIVE_C_INCLUDE_PATH ../include



