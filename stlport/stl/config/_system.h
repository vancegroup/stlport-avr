/*
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
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

/*
 * Purpose of this file :
 *
 * To hold COMPILER-SPECIFIC portion of STLport settings.
 * In general, user should not edit this file unless
 * using the compiler not recognized below.
 *
 * If your compiler is not being recognized yet,
 * please look for definitions of macros in stl_mycomp.h,
 * copy stl_mycomp.h to stl_YOUR_COMPILER_NAME,
 * adjust flags for your compiler, and add  <include config/stl_YOUR_COMPILER_NAME>
 * to the secton controlled by unique macro defined internaly by your compiler.
 *
 * To change user-definable settings, please edit <user_config.h>
 *
 */

#ifndef __stl_config__system_h
#define __stl_config__system_h

#ifdef __sun
#  include <stl/config/_solaris.h>
#  ifdef __GNUC__
#    include <stl/config/_gcc.h>
#  endif
#  ifdef __SUNPRO_CC
#    include <stl/config/_sunprocc.h>
#  endif
/*
#  ifdef __KCC
#    include <stl/config/_kai.h>
#  endif
*/
#  ifdef __APOGEE__  /* Apogee 4.x */
#    include <stl/config/_apcc.h>
#  endif
#  ifdef __FCC_VERSION /* Fujutsu Compiler, v4.0 assumed */
#    include <stl/config/_fujitsu.h>
#  endif
#endif

#ifdef __hpux
#  include <stl/config/_hpux.h>
#  ifdef __GNUC__
#    include <stl/config/_gcc.h>
#  endif
#  ifdef __HP_aCC
#    include <stl/config/_hpacc.h>
#  endif
#endif

#if defined(linux) || defined(__linux__)
#  include <stl/config/_linux.h>
#  ifdef __INTEL_COMPILER
#    include <stl/config/_icc.h>
#  endif
   /* Intel's icc define __GNUC__! */
#  if defined(__GNUC__) && !defined(__INTEL_COMPILER)
#    include <stl/config/_gcc.h>
#  endif
/*
#  ifdef __KCC
#    include <stl/config/_kai.h>
#  endif
*/
#endif

#ifdef __FreeBSD__
#  include <stl/config/_freebsd.h>
#  ifdef __GNUC__
#    include <stl/config/_gcc.h>
#  endif
#endif

#ifdef __OpenBSD__
#  include <stl/config/_openbsd.h>
#  ifdef __GNUC__
#    include <stl/config/_gcc.h>
#  endif
#endif

#ifdef N_PLAT_NLM /* Novell NetWare */
#  include <stl/config/_netware.h>
#  ifdef __MWERKS__ /* Metrowerks CodeWarrior */
#    include <stl/config/_mwccnlm.h>
#  endif
#endif

#ifdef __sgi /* IRIX? */
#  include <stl/config/_sgi.h>
#  ifdef __GNUC__
#    include <stl/config/_gcc.h>
#  endif
#endif

#ifdef __OS400__ /* AS/400 C++ */
#  include <stl/config/_as400.h>
#  ifdef __GNUC__
#    include <stl/config/_gcc.h>
#  endif
#endif

#ifdef _AIX
#  include <stl/config/_aix.h>
#  if defined (__xlC__)  || defined (__IBMC__) || defined ( __IBMCPP__ )
     /* AIX xlC, Visual Age C++ , OS-390 C++ */
#    include <stl/config/_ibm.h>
#  endif
#endif

#ifdef _CRAY /* Cray C++ 3.4 or 3.5 */
#  include <config/stl_cray.h>
#endif

#if defined (__DECCXX) || defined (__DECC)
#  ifdef __vms
#    include <stl/config/_dec_vms.h>
#  else
#    include <stl/config/_dec.h>
#  endif
#endif

#if defined(macintosh) || defined (_MAC)
#  include <stl/config/_mac.h>
#  ifdef __MWERKS__
#    include <stl/config/_mwerks.h>
#  endif
#  if defined (__MRC__) || (defined (__SC__) && (__SC__ >= 0x882))
     /* Apple MPW SCpp 8.8.2, Apple MPW MrCpp 4.1.0 */
#    include <stl/config/_apple.h>
#  endif
#endif

#ifdef __APPLE__
#  include <stl/config/_macosx.h>
#  ifdef __GNUC__
#    include <stl/config/_gcc.h>
#  endif
#endif

#if defined (__CYGWIN__)
#  include <stl/config/_gcc.h>
#endif

#if defined (_WIN32) || defined (__WIN32) || defined (WIN32) || defined (__WIN32__) || \
    defined (__WIN16) || defined (WIN16) || defined (_WIN16) || \
    defined (__MINGW32__)
#  if defined ( __BORLANDC__ )  /* Borland C++ ( 4.x - 5.x ) */
#    include <stl/config/_bc.h>
#  endif
#  if defined (__WATCOM_CPLUSPLUS__) || defined (__WATCOMC__)  /* Watcom C++ */
#    include <stl/config/_watcom.h>
#  endif
#  if defined (__COMO__) || defined (__COMO_VERSION_)
#    include <stl/config/_como.h>
#  endif
#  if defined (__DMC__)   /* Digital Mars C++ */
#    include <stl/config/_dm.h>
#  endif
#  if defined (__SC__) && (__SC__ < 0x800) /* Symantec 7.5 */
#    include <stl/config/_symantec.h>
#  endif
#  if defined (__ICL) /* Intel reference compiler for Win */
#    include <stl/config/_intel.h>
#  endif
#  if defined (__MWERKS__)
#    include <stl/config/_mwerks.h>
#  endif
#  if defined (_MSC_VER) && (_MSC_VER >= 1200) && defined (UNDER_CE)
     /* Microsoft eMbedded Visual C++ 3.0, 4.0 (.NET) */
#    include <stl/config/_evc.h>
#  endif
   /* distinguish real MSC from Metrowerks, Intel and Comeau */
#  if defined (_MSC_VER) && !defined (__MWERKS__) && !defined (__ICL) && !defined (__COMO__) && ((_MSC_VER < 1200) || !defined (UNDER_CE))
    /* Microsoft Visual C++ 6.0, 7.0, 7.1, 8.0 */
#    define _STLP_MSVC _MSC_VER
#    include <stl/config/_msvc.h>
#  endif
#  if defined (__GNUC__)
#    include <stl/config/_gcc.h>
#  endif

#  include <stl/config/_windows.h>
#endif


/* Unable to identify the compiler, issue error diagnostic.
 * Edit <config/stl_mycomp.h> to set STLport up for your compiler. */
/* #  include <stl/config/stl_mycomp.h> */

#endif /* __stl_config__system_h */
