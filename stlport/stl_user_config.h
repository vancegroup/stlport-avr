/*
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

/*
 * Purpose of this file :
 *
 * To hold user-definable portion of STLport settings which may be overridden
 * on per-project basis.
 * Please note that if you use SGI iostreams (compiled STLport) then you have
 * to use consistent settings when you compile STLport library and your project. 
 * Those settings are defined in _site_config.h and have to be the same for a given
 * STLport installation.
 *
 */


//==========================================================
// User-settable macros that control compilation:
//              Features selection
//==========================================================

/* __STL_NO_SGI_IOSTREAMS: 
 *
 *  This is major configuration switch.
 *  Turn it on to disable use of SGI iostreams and use wrappers 
 *  around your compiler's iostreams, like before.
 *  Keep it off if you want to use  SGI iostreams 
 *  (Note that in this case you have to compile library in ../src
 *  and supply resulting library at link time).
 *
 */

// # define   __STL_NO_SGI_IOSTREAMS	1


/* 
 * This macro only works in non-SGI iostreams mode.
 *
 * Uncomment to suppress using new-style streams even if they are
 * available.
 * Beware - __STL_USE_OWN_NAMESPACE depends on this macro, too.
 * Do that only if you are absolutely sure backwards-compatible 
 * <iostream.h> is not actually a wrapper with <iostream>
 * Hint : In VC++ 6.x, they are not.
 */

// #define   __STL_NO_NEW_IOSTREAMS	1

/*
 * Use this switch for embedded systems where no iostreams are available
 * at all. SGI iostreams will get disabled automatically then.
 */
// # define __STL_NO_IOSTREAMS 1

/* 
 * Set __STL_DEBUG to turn the "Debug Mode" on.
 * That gets you checked iterators/ranges in the manner
 * of "Safe STL". Very useful for debugging. Thread-safe.
 * Please do not forget to link proper STLport library flavor
 * (e.g libstlport_gcc_stldebug.a) when you set this flag in SGI iostreams mode.
 */
// #define   __STL_DEBUG 1

/*
 * By default, STLport uses proxy technique to enable operator -> for
 * iterators even for those compilers that check the return type of
 * unused instantiations. If this causes problems for you, turn the following
 * switch on to disable proxy ->() operators. This actually should be done
 * in compiler-dependant section, not here. 
 * auto_ptr implements proxy operator even if they are disabled in general,
 * as it is very unlikely that you instantiate auto_ptr<> on pointers and other builtins.
 * However, if this is the case, uncomment second line.
 */

// # define __STL_NO_PROXY_ARROW_OPERATOR 1
// # define __STL_NO_AUTO_PTR_PROXY_ARROW_OPERATOR 1


/*
 * If __STL_USE_OWN_NAMESPACE is in effect, STLport will try to rename std:: for the user
 * to _STL::. If you don't want this feature, or if it does not quite work for your
 * compiler, please define the following switch :
 */
// # define __STL_DONT_REDEFINE_STD 1

/* 
 * Edit relative path below (or put full path) to get native 
 * compiler vendor's headers included. Default is "../include"
 * Note : this cannot be set the same for different compilers, so
 * it may make sense to override in local stl_user_config.h only. 
 * Hint : never install STLport in the directory that ends with "include"
 */
// #  undef __STL_NATIVE_INCLUDE_PATH
// #  define __STL_NATIVE_INCLUDE_PATH ../include
// same for C library headers like <cstring>
// #  undef __STL_NATIVE_CPP_C_INCLUDE_PATH
// #  define __STL_NATIVE_CPP_C_INCLUDE_PATH ../include
// same for C headers like <string.h>
// #  undef __STL_NATIVE_C_INCLUDE_PATH
// #  define __STL_NATIVE_C_INCLUDE_PATH ../include


/* 
 * __STL_NO_RELOPS_NAMESPACE: if defined, don't put the relational
 * operator templates (>, <=. >=, !=) in namespace std::rel_ops, even
 * if the compiler supports namespaces.
 * Note : if the compiler do not support namespaces, those operators are not be provided by default,
 * to simulate hiding them into rel_ops. This was proved to resolve many compiler bugs with ambiguity.
 */

// #define __STL_NO_RELOPS_NAMESPACE 1

/*
 * Use this option to catch uninitialized members in your classes.
 * When it is set, construct() and destroy() fill the class storage
 * with __STL_SHRED_BYTE (see below). 
 * Note : __STL_DEBUG and __STL_DEBUG_ALLOC don't set this option automatically.
 */

// # define __STL_DEBUG_UNINITIALIZED 1

/*
 * Uncomment and provide a definition for the byte with which raw memory
 * will be filled if __STL_DEBUG_ALLOC or __STL_DEBUG_UNINITIALIZED is defined. 
 * Choose a value which is likely to cause a noticeable problem if dereferenced 
 * or otherwise abused. A good value may already be defined for your platform; see
 * stl_config.h
 */
// #define __STL_SHRED_BYTE 0xA3

//==========================================================
// Compatibility section
//==========================================================

/*
 *  Define this macro to disable anachronistic constructs (like the ones used in HP STL and
 *  not included in final standard 
 */
// define __STL_NO_ANACHRONISMS 1

/*
 *  Define this macro to disable SGI/STLport extensions (for example, to make sure your code will 
 *  compile with some other implementation )
 */
// define __STL_NO_EXTENSIONS   1

/*
 * Use obsolete overloaded template functions iterator_category(), value_type(), distance_type()
 * for querying iterator properties. Please note those names are non-standard and are not guaranteed
 * to be used by every implementation. However, this setting is on by default when partial specialization
 * is not implemented in the compiler (if __STL_NO_ANACHRONISMS is not set). 
 * Use of those interfaces for user-defined iterators is strongly discouraged: 
 * please use public inheritance from iterator<> template to achieve desired effect. 
 * Second form is to disable old-style queries in any case.
 */
// # define __STL_USE_OLD_HP_ITERATOR_QUERIES
// # define __STL_NO_OLD_HP_ITERATOR_QUERIES

/* 
 * You should define this macro if compiling with MFC - STLport <stl/_config.h>
 * then include <afx.h> instead of <windows.h> to get synchronisation primitives 
 *
 */

// # define __STL_USE_MFC 1

/*
 * Use minimum set of default arguments on template classes that have more
 * than one - for example map<>, set<>.
 * This has effect only if __STL_LIMITED_DEFAULT_TEMPLATES is on.
 * If __STL_MINIMUM_DEFAULT_TEMPLATE_PARAMS is set, you'll be able to compile
 * set<T> with those compilers, but you'll have to use __set__<T, less<T>>
 *
 * Affects : map<>, multimap<>, set<>, multiset<>, hash_*<>, 
 * queue<>, priority_queue<>, stack<>, istream_iterator<>
 */

// # define __STL_MINIMUM_DEFAULT_TEMPLATE_PARAMS 1


/* 
 * __STL_USE_SGI_STRING : Forces use of SGI string even if
 * native <string> is available. Unless you defined __STL_USE_OWN_NAMESPACE,
 * STLport uses native <string> if new iostreams are being used, 
 * as part of compiled runtime library depends on it.
 * You may force use of SGI string uncommenting this macro.
 * IMPORTANT:
 * DO NOT use SGI <string> with native <iostream> unless you recompile 
 * standard C++ runtime library with STLport installed, or
 * (better) defined __STL_USE_OWN_NAMESPACE
 */

// #define  __STL_USE_SGI_STRING  1

/*
 * __STL_WHOLE_NATIVE_STD : only meaningful in __STL_USE_OWN_NAMESPACE mode.
 * Normally, STLport only imports necessary components from native std:: namespace -
 * those not yet provided by STLport (<iostream>, <complex>, etc.) 
 * and their dependencies (<string>, <stdexcept>). 
 * You might want everything from std:: being available in std:: namespace when you
 * include corresponding STLport header (like STLport <map> provides std::map as well, etc.),
 * if you are going to use both stlport:: and std:: components in your code.
 * Otherwise this option is not recommended as it increases the size of your object files
 * and slows down compilation.
 */
// # define __STL_WHOLE_NATIVE_STD

//==========================================================



// Local Variables:
// mode:C++
// End:
