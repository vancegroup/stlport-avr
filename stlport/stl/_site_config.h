// 
// This file defines site configuration.
//
//

/* 
 * __STL_NO_THREADS: if defined, STLport don't use any 
 * multithreading support. Synonym is _NOTHREADS
 */
// #define _NOTHREADS
// #define __STL_NO_THREADS

/* _PTHREADS: if defined, use Posix threads for multithreading support. */
// #define _PTHREADS

/*
 *  Consistency check : if we use SGI iostreams, we have to use consistent
 *  thread model (single-threaded or multi-threaded) with the compiled library
 *  
 *  Default is multithreaded build. If you want to build and use single-threaded
 *  STLport, please change __STL_NOTHREADS configuration setting above and rebuild the library
 *
 */

# if defined (__STL_NO_IOSTREAMS) || defined (__STL_NO_NEW_IOSTREAMS) && ! defined ( __STL_NO_SGI_IOSTREAMS )
#  define __STL_NO_SGI_IOSTREAMS
# endif

# if !defined (__STL_NO_SGI_IOSTREAMS) &&  ! defined (__SGI_STL_OWN_IOSTREAMS)
#  define __SGI_STL_OWN_IOSTREAMS
# endif


# if defined (__SGI_STL_OWN_IOSTREAMS) \
  && !defined (__STL_NO_THREADS) && ! defined (_NOTHREADS) && !defined (_REENTRANT)

#  if defined(_MSC_VER) && !defined(__MWERKS__) && !defined (__COMO__) && !defined(_MT)
#   error "Only multi-threaded runtime library may be linked with STLport!"  
#  endif

// boris : you may change that to build non-threadsafe STLport library
#  if defined (__BUILDING_STLPORT)
#   define _REENTRANT 1
#  endif

# endif

/*
 * Turn __STL_USE_DYNAMIC_LIB to enforce use of .dll version of STLport library.
 * NOTE : please do that only if you know what you are doing !
 * Changing default will require you to change makefile in "src" accordingly
 * and to rebuild STLPort library !
 * On UNIX, this has no effect. 
 *
 */
// # define __STL_USE_DYNAMIC_LIB

/*
 * Turn __STL_USE_STATIC_LIB to enforce use of static version of STLport library.
 * NOTE : please do that only if you know what you are doing !
 * Changing default will require you to change makefile in "src" accordingly
 * and to rebuild STLPort library !
 * On UNIX, this has no effect. 
 *
 */
// # define __STL_USE_STATIC_LIB


/* 
 * __STL_USE_OWN_NAMESPACE/__STL_NO_OWN_NAMESPACE
 * If defined, STLport uses _STL:: namespace, else std::
 * The reason you have to use separate namespace is that new-style IO
 * compiled library may have its own idea about STL stuff (string, vector, etc.),
 * so redefining them in the same namespace would break ODR and may cause
 * undefined behaviour. Rule of thumb is - if new-style iostreams are
 * available, there WILL be a conflict. Otherwise you should be OK.
 * This flag is going to be defined by default in stl_config.h if __STL_USE_NEW_IOSTREAMS is on.
 * But you may wish to force it anyway.
 * Alternatively, you may want to disable it setting __STL_NO_OWN_NAMESPACE on.
 */
// #  define __STL_USE_OWN_NAMESPACE  1
// #  define __STL_NO_OWN_NAMESPACE  1


/* 
 * Uncomment __STL_USE_NEWALLOC to force allocator<T> to use plain "new"
 * instead of SGI optimized node allocator engine.
 */
// #define   __STL_USE_NEWALLOC   1

/* 
 * Uncomment __STL_USE_MALLOC to force allocator<T> to use plain "malloc" 
 * instead of SGI optimized node allocator engine.
 */
// #define   __STL_USE_MALLOC 1

/*
 * Set __STL_DEBUG_ALLOC to use allocators that perform memory debugging,
 * such as padding/checking for memory consistency 
 */
// #define   __STL_DEBUG_ALLOC 1


/*
 * Uncomment this to force all debug diagnostic to be directed through a
 * user-defined global function:
 *	void __stl_debug_message(const char * format_str, ...)
 * instead of predefined STLport routine. 
 * This allows you to take control of debug message output.
 * Default routine calls fprintf(stderr,...)
 * Note : If you set this macro, you must supply __stl_debug_message 
 * function definition somewhere.
 */
//#define __STL_DEBUG_MESSAGE 1

/*
 * Uncomment this to force all failed assertions to be executed through
 * user-defined global function:
 *	void __stl_debug_terminate(void). This allows
 * you to take control of assertion behaviour for debugging purposes.
 * Default routine throws unique exception if __STL_USE_EXCEPTIONS is set,
 * calls abort() otherwise.
 * Note : If you set this macro, you must supply __stl_debug_terminate 
 * function definition somewhere.
 */
//#define __STL_DEBUG_TERMINATE 1

/*
 * Comment this out to enable throwing exceptions from default __stl_debug_terminate()
 * instead of calling abort().
 */
#define __STL_NO_DEBUG_EXCEPTIONS 1

/* 
 * Uncomment that to disable exception handling code 
 */
// #define   __STL_NO_EXCEPTIONS 1

/*
 * __STL_NO_NAMESPACES: if defined, don't put the library in namespace
 * stlport:: or std::, even if the compiler supports namespaces
 */

// #define   __STL_NO_NAMESPACES 1

//==========================================================
// Compatibility section
//==========================================================

/* 
 * Use abbreviated class names for linker benefit (don't affect interface).
 * This option is obsolete, but should work in this release.
 *
 */
// # define __STL_USE_ABBREVS

/* 
 * This definition precludes SGI reverse_iterator to be compatible with
 * other parts of MSVC library. (With partial specialization, it just
 * has no effect).
 * Use it _ONLY_ if you use SGI-style reverse_iterator<> template explicitly
 */
// #    define __STL_NO_MSVC50_COMPATIBILITY 1

/*
 * __STL_USE_RAW_SGI_ALLOCATORS is a hook so that users can disable use of
 * allocator<T> as default parameter for containers, and use SGI
 * raw allocators as default ones, without having to edit library headers.
 * Use of this macro is strongly discouraged.
 */
// #define   __STL_USE_RAW_SGI_ALLOCATORS 1

//==========================================================================

// This section contains swithes which should be off by default,
// but so few compilers would have it undefined, so that we set them here,
// with the option to be turned off later in compiler-specific file

# define __STL_INCOMPLETE_EXCEPTION_HEADER

