/***********************************************************************************
  Prefix.h

 * Copyright (c) 1997
 * Mark of the Unicorn, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Mark of the Unicorn makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
			
		SUMMARY: Configuration #defines for STL EH test suite
		
***********************************************************************************/

#if ! defined (INCLUDED_MOTU_Prefix)
#define INCLUDED_MOTU_Prefix 1

// Gives much more thorough checking, but may slow the tests
// considerably if your malloc is slow.
#define TESTCLASS_DEEP_DATA 1

// Define this to use the SGI STL. Undefine it to test a different installation
#ifndef EH_NO_SGI_STL
# define EH_USE_SGI_STL 1
#endif

#if EH_USE_SGI_STL

#define EH_ASSERT __STL_ASSERT

//=========================================================================
// SGI STL-specific #defines
//	These control the behavior of the test suite when used with the SGI
//	STL. They have no effect when testing other STL implementations.
//=========================================================================

# define __STL_USE_RAW_SGI_ALLOCATORS
# ifndef __STL_USE_NEWALLOC
#  define __STL_USE_NEWALLOC
# endif
# if !defined  (__STL_NO_CUSTOM_IO) && ! defined (__BORLANDC__)
#  define __STL_NO_CUSTOM_IO
# endif

// Just include something to get whatever configuration header we're using.
# include <stl/_config.h>

# ifndef __STL_CALL
#  define __STL_CALL
# endif

# if defined(__STL_USE_NAMESPACES)
#  define EH_USE_NAMESPACES __STL_USE_NAMESPACES
# endif

# define EH_BEGIN_NAMESPACE __STL_BEGIN_NAMESPACE
# define EH_END_NAMESPACE __STL_END_NAMESPACE

#  define EH_NEW_HEADERS 1

# if defined (__STL_USE_NEW_IOSTREAMS)
#  define EH_NEW_IOSTREAMS 1
# endif

# if !defined (__STL_USE_EXCEPTIONS)
#  define EH_NO_EXCEPTIONS
# endif

# if defined (__STL_TEMPLATE_PARAM_SUBTYPE_BUG)
#  define EH_TEMPLATE_PARAM_SUBTYPE_BUG __STL_TEMPLATE_PARAM_SUBTYPE_BUG
# endif

# if defined(__STL_MULTI_CONST_TEMPLATE_ARG_BUG)
#  define EH_MULTI_CONST_TEMPLATE_ARG_BUG __STL_MULTI_CONST_TEMPLATE_ARG_BUG
# endif

# if defined (STLPORT)
#  define EH_STD STLPORT
# elif defined(__STD)
#  define EH_STD __STD
# endif

// we want to be portable here, so std:: won't work.
# if defined(STLPORT_CSTD)
#  define EH_CSTD STLPORT_CSTD
# else
#  define EH_CSTD std
# endif


# define EH_DISTANCE( a, b, result ) EH_STD::distance( a, b, result )

# define EH_HASHED_CONTAINERS_IMPLEMENTED 1
# define EH_HASH_CONTAINERS_SUPPORT_RESIZE 1
# define EH_HASH_CONTAINERS_SUPPORT_ITERATOR_CONSTRUCTION 1
# define EH_SLIST_IMPLEMENTED 1
# define EH_SELECT1ST_HINT __select1st_hint
// fbp : DEC cxx is unable to compile it for some reason
# if !( defined (__DECCXX)  || (defined (__GNUC__) && (__GNUC_MINOR__ < 8)))
#  define EH_ROPE_IMPLEMENTED 1
# endif
# define EH_STRING_IMPLEMENTED 1
// # define EH_BITSET_IMPLEMENTED 1
//# define EH_VALARRAY_IMPLEMENTED 1	- we have no tests yet for valarray

# define stl_destroy EH_STD::destroy
# include <memory>

# define eh_allocator(T) EH_STD::__allocator<T, EH_STD::__debug_alloc<EH_STD::__new_alloc> >

# define EH_BIT_VECTOR_IMPLEMENTED

# if defined(__STL_CLASS_PARTIAL_SPECIALIZATION) && !defined(__STL_NO_BOOL)
#  define EH_BIT_VECTOR EH_STD::vector<bool, eh_allocator(bool) >
# else
#  ifdef __STL_NO_BOOL
#  undef   EH_BIT_VECTOR_IMPLEMENTED
#  else
#   define EH_BIT_VECTOR EH_STD::__vector__<bool, eh_allocator(bool) >
#  endif
# endif

#else // !USE_SGI_STL
//=========================================================================
// Configuration for testing other non-SGI STL implementations
//=========================================================================

// Metrowerks configuration
# ifdef __MWERKS__

# define EH_ASSERT assert
// Get MSL configuration header
#  include <ansi_parms.h>

#  if __MSL__ >= 24

#   define EH_NEW_HEADERS 1
#   if defined (_MSL_USING_NAMESPACE)
#    define EH_USE_NAMESPACES 1
#   endif
#	define EH_BIT_VECTOR vector<bool>
#   define EH_DISTANCE( a, b, result ) do { result = distance( a, b ); } while (0)

#  else

#   error No configuration for earlier versions of MSL

#  endif	// __MSL__ >= 24

// Bugs fixed in CWPro3
#  if __MWERKS__ < 0x2100
#   define EH_TEMPLATE_PARAM_SUBTYPE_BUG 1
#  endif

// Bugs in CWPro3
#  if __MWERKS__ <= 0x2110
#   define EH_MULTI_CONST_TEMPLATE_ARG_BUG 1
#  else
#   pragma warning not sure the above bug is fixed yet
#  endif

#  define EH_SLIST_IMPLEMENTED 1
//#  define EH_HASHED_CONTAINERS_IMPLEMENTED 1

#  define EH_NEW_IOSTREAMS 1
#  define EH_USE_NOTHROW 1
# endif // Metrowerks configuration

#if defined (__SUNPRO_CC)
# define stl_destroy __RWSTD::__destroy
# define EH_DISTANCE( a, b, result ) distance( a, b, result )
# define EH_BIT_VECTOR EH_STD::vector<bool>
# define EH_NEW_HEADERS 1
# define EH_USE_NAMESPACES 1
# define EH_NEW_IOSTREAMS 1
# define EH_ASSERT assert
# define EH_STRING_IMPLEMENTED 1
# elif defined (__KCC)
# define stl_destroy EH_STD::destroy
# define EH_DISTANCE( a, b, result ) do { result = distance( a, b ); } while (0)
# define EH_BIT_VECTOR EH_STD::vector<bool>
# define EH_NEW_HEADERS 1
# define EH_USE_NAMESPACES 1
# define EH_NEW_IOSTREAMS 1
# define EH_ASSERT assert
# define EH_CSTD
# define EH_STRING_IMPLEMENTED 1
# define EH_MULTI_CONST_TEMPLATE_ARG_BUG 1
# define EH_SELECT1ST_HINT select1st
# else
# define stl_destroy destroy
#endif

//
// Compiler-independent configuration
//
# ifdef EH_USE_NAMESPACES
# ifdef STLPORT
#  define EH_STD STLPORT
# else
#  define EH_STD std
# endif
# ifdef STLPORT_CSTD
#  define EH_STD STLPORT_CSTD
# else
#  define EH_STD std
# endif
#  define EH_BEGIN_NAMESPACE namespace EH_STD {
#  define EH_END_NAMESPACE   }
# else
#  define EH_BEGIN_NAMESPACE
#  define EH_END_NAMESPACE
#  define EH_STD
# endif

# ifndef EH_CSTD
#  define EH_CSTD EH_STD
# endif

#endif // !USE_SGI_STL


//
// Library-independent configuration.
//
#if defined( EH_MULTI_CONST_TEMPLATE_ARG_BUG) && !defined( EH_SELECT1ST_HINT )
template <class Pair, class U>		
// JDJ (CW Pro1 doesn't like const when first_type is also const)
struct eh_select1st_hint : public unary_function<Pair, U> {
    const U& operator () (const Pair& x) const { return x.first; }
};
# define EH_SELECT1ST_HINT eh_select1st_hint
#endif


#if EH_USE_NAMESPACES
# define EH_USE_STD using namespace EH_STD;
#else
# define EH_USE_STD
#endif

#if defined (EH_USE_NAMESPACES) && !defined(__STL_VENDOR_GLOBAL_CSTD)
# define USING_CSTD_NAME(name) using EH_STD :: name;
#else
# define USING_CSTD_NAME(name)
#endif

#endif // INCLUDED_MOTU_Prefix


