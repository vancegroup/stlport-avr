// STLport configuration file
// It is internal STLport header - DO NOT include it directly

// common configuration settings for Apple MPW MrCpp / SCpp

#if defined(__MRC__) && __MRC__ < 0x500
# error Apple's MPW MrCpp v.5.0.0 or better compiler required
#endif
#if defined(__SC__) && __SC__ < 0x890
# error Apple's MPW SCpp v.8.9.0 or better compiler required
#endif

#ifdef qMacApp
# ifndef __CONDITIONALMACROS__ // skip including ConditionalMacros_AC.h if ConditionalMacros.h is already included
# include <CoreSwitches_AC.h>
# include <ConditionalMacros_AC.h>
# include <Types_AC.h>
# define __STL_FILE__ _FILE_AC
# define __STL_DEBUG_MESSAGE      
# define __stl_debug_message ProgramBreak_AC
# include <ConditionalMacros.h>
# endif
# include <Types.h>
#else
# include <ConditionalMacros.h>
# include <Types.h>
#endif

#define __STL_UINT32_T UInt32
typedef int wint_t;

#ifndef TYPE_BOOL
# error <ConditionalMacros.h> must be included. (TYPE_BOOL)
#endif
#if !TYPE_BOOL
# define __STL_NO_BOOL
# define __STL_DONT_USE_BOOL_TYPEDEF
#endif

#ifndef TYPE_LONGLONG
# error <ConditionalMacros.h> must be included. (TYPE_LONGLONG)
#endif
#if TYPE_LONGLONG
//# define __STL_LONG_LONG long long // deactivated since long long is not allowed as a template value argument [File "{STL}stl:_limits.h"; line 282]
#endif

#if !__option(exceptions)
# define __STL_HAS_NO_EXCEPTIONS
#endif

#define __STL_DEBUG_MESSAGE_POST DebugStr("\pSTL diagnosis issued. See 'stderr' for detail.");
#define __STL_ASSERT_MSG_TRAILER " "

#ifdef __STL_DEBUG
#   define __STL_THROW(x) (DebugStr("\pSTL is about to throw exception: "#x),throw x)
#endif

#if defined(__MRC__)
# ifndef __spillargs
#  define __spillargs 1 // MrCpp requires this symbol to be defined as 1 to properly handle va_start; ref.[ file stdarg.h; line 26 ]
# endif
#endif

#ifndef __STL_NATIVE_INCLUDE_PATH
# if __option(unix_includes)
#  define __STL_NATIVE_INCLUDE_PATH ../CIncludes // expects the alias to {CIncludes} under the same folder as {STL}
# else
#  define __STL_NATIVE_INCLUDE_PATH ::CIncludes // expects the alias to {CIncludes} under the same folder as {STL}
# endif
#endif
#if !defined(__STL_MAKE_HEADER)
# if !__option(unix_includes)
#  define __STL_MAKE_HEADER(path, header) <path:header> // Mac uses ":" for directory delimiter
# endif
#endif

# define _STLD _DBG	// to keep the length of generated symbols within the compiler limitation

#define __SGI_STL_OWN_IOSTREAMS						//*TY 01/11/2000 - EXPERIMENTAL
#define __STL_USE_STDIO_IO 1						//*TY 02/24/2000 - see also ; ref.[ file _fstream.h; line 36 ]


// native library limitations
#define __STL_VENDOR_GLOBAL_STD						// mpw's c++ libs do not utilize namespace std yet
#define __STL_NO_BAD_ALLOC							// known limitation
#define __STL_HAS_NO_NEW_C_HEADERS					// known limitation
#define __STL_NO_NEW_NEW_HEADER						// known limitation
#define __STL_HAS_NO_NEW_IOSTREAMS					// known limitation
#define __STL_NO_NATIVE_MBSTATE_T					// known limitation
#define __STL_NO_NATIVE_WIDE_FUNCTIONS				// known limitation
#define __STL_NO_NATIVE_WIDE_STREAMS				// known limitation
# define __STL_NO_EXCEPTION_HEADER 1				// fbp : please double-check the opportunity to use native header !
//*TY 05/01/2000 - mpw confuse on the using declarations for the math functions
# define __STL_NO_USING_FOR_GLOBAL_FUNCTIONS  1

// compiler limitations
# define __STL_MPWFIX_TRY try{											//*TY 06/01/2000 - exception handling bug workaround
# define __STL_MPWFIX_CATCH }catch(...){throw;}							//*TY 06/01/2000 - exception handling bug workaround
# define __STL_MPWFIX_CATCH_ACTION(action) }catch(...){action;throw;}	//*TY 06/01/2000 - exception handling bug workaround
# define __STL_NO_METHOD_SPECIALIZATION				//*TY 04/15/2000 - late breaking compiler bug; ref.[ file _ios.h; line 161 ]
# define __STL_NO_COMPLEX_SPECIALIZATIONS			//*TY 02/25/2000 - late breaking compiler bug; ref.[ file _complex.h; line 36 ]
# define __STL_THROW_RETURN_BUG						// known limitation 
# define __STL_NO_CLASS_PARTIAL_SPECIALIZATION		// known limitation
# define __STL_NO_PARTIAL_SPECIALIZATION_SYNTAX		// known limitation
# define __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER		// known limitation
# define __STL_NO_RELOPS_NAMESPACE					// known limitation
// end of stl_apple.h
