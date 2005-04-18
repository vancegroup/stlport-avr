@ECHO OFF
REM **************************************************************************
REM *
REM * configure.bat for setting up compiling STLport under Windows
REM * to see available options, call with option --help
REM *
REM * Copyright (C) 2004 Michael Fink
REM *
REM **************************************************************************

REM Attention! Batch file labels only have 8 significant characters!

echo STLport Configuration Tool for Windows
echo.

REM no options at all?
if NOT "%1xyz123" == "xyz123" goto init

echo Please specify some options or use "configure.bat --help" to see the
echo available options.
goto skp_comp

:init

REM initially create/overwrite config.mak
echo # STLport Configuration Tool for Windows > ..\Makefiles\config.mak
echo # >> ..\Makefiles\config.mak
echo # config.mak generated with command line: >> ..\Makefiles\config.mak
echo # configure.bat %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\Makefiles\config.mak
echo # >> ..\Makefiles\config.mak

set STLPORT_COMPILE_COMMAND=

REM
REM option loop
REM
:loop

REM help option
if "%1" == "-?" goto opt_help
if "%1" == "-h" goto opt_help
if "%1" == "/?" goto opt_help
if "%1" == "/h" goto opt_help
if "%1" == "--help" goto opt_help

REM compiler option
if "%1" == "-c" goto opt_comp
if "%1" == "/c" goto opt_comp
if "%1" == "--compiler" goto opt_comp

REM processor option
if "%1" == "-p" goto opt_proc
if "%1" == "/p" goto opt_proc
if "%1" == "--processor" goto opt_proc

REM cross compiling
if "%1" == "-x" goto opt_x
if "%1" == "/x" goto opt_x
if "%1" == "--cross" goto opt_x

REM C runtime library
if "%1" == "--rtl-static" goto opt_rtl
if "%1" == "--rtl-dynamic" goto opt_rtl

REM clean rule
if "%1" == "--clean" goto opt_clean

echo Unknown option: %1

:cont_lp

shift

REM no more options?
if "%1xyz123" == "xyz123" goto end_loop

goto loop


REM **************************************************************************
REM *
REM * Help
REM *
REM **************************************************************************
:opt_help
echo The following options are available:
echo.
echo "-c <compiler>" or "--compiler <compiler>"
echo    Uses specified compiler to compile STLport. The following keywords
echo    are available:
echo    msvc6    Microsoft Visual C++ 6.0
echo    msvc7    Microsoft Visual C++ .NET 2002
echo    msvc71   Microsoft Visual C++ .NET 2003
echo    msvc8    Microsoft Visual C++ .NET 2005 (beta)
REM echo    icl      Intel C++ Compiler
echo    evc3     Microsoft eMbedded Visual C++ 3
echo    evc4     Microsoft eMbedded Visual C++ .NET
echo.
echo "-p <processor>" or "--processor <processor>"
echo    Sets target processor for given compiler; currently only used for
echo    evc3 and evc4 compiler. The following keywords are available:
echo    ARM     ARM processor
echo    x86     x86 processor (Emulator)
echo    MIPS    MIPS processor (evc3 only)
echo    MIPS16  MIPS16 processor (evc4 only)
echo    MIPSII  MIPS II processor (evc4 only)
echo    MIPSIV  MIPS IV processor (evc4 only)
echo.
echo "-x"
echo    Enables cross-compiling; the result is that all built files that are
echo    normally put under "bin" and "lib" get extra subfolders depending on
echo    the compiler name.
echo.
echo "--rtl-static"
echo "--rtl-dynamic"
echo    Enables usage of static (libc.lib family) or dynamic (msvcrt.lib family)
echo    C/C++ runtime library when linking with STLport. If you want your appli/dll
echo    to link statically with STLport but using the dynamic C runtime use
echo    --rtl-dynamic; if you want to link dynamicaly with STLport but using the
echo    static C runtime use --rtl-static. See README.options for details.
echo    Don't forget to signal the link method when building your appli or dll, in
echo    _site_config.h set the following macro depending on the configure option:
echo    "--rtl-dynamic -> _STLP_USE_DYNAMIC_LIB"
echo    "--rtl-static  -> _STLP_USE_STATIC_LIB"
echo    This is a Microsoft-only option.
echo.
echo "--clean"
echo    Removes the build configuration file.
goto skp_comp

REM **************************************************************************
REM *
REM * Compiler configuration
REM *
REM **************************************************************************
:opt_comp

set STLPORT_SELECTED_CONFIG=%2

if "%2" == "msvc6" goto oc_msvc6
if "%2" == "msvc7" goto oc_msvc7
if "%2" == "msvc71" goto oc_msvc71
if "%2" == "msvc8" goto oc_msvc8
if "%2" == "icl"   goto oc_icl

if "%2" == "evc3" goto oc_evc3
if "%2" == "evc4" goto oc_evc4

echo Unknown compiler: %2
goto oc_end

:oc_msvc6
echo Setting compiler: Microsoft Visual C++ 6.0
echo TARGET_OS=x86 >> ..\Makefiles\config.mak
set STLPORT_COMPILE_COMMAND=nmake -f nmake-vc6.mak
goto oc_end

:oc_msvc7
echo Setting compiler: Microsoft Visual C++ .NET 2002
echo TARGET_OS=x86 >> ..\Makefiles\config.mak
set STLPORT_COMPILE_COMMAND=nmake -f nmake-vc70.mak
goto oc_end

:oc_msvc71
echo Setting compiler: Microsoft Visual C++ .NET 2003
echo TARGET_OS=x86 >> ..\Makefiles\config.mak
set STLPORT_COMPILE_COMMAND=nmake -f nmake-vc71.mak
goto oc_end

:oc_msvc8
echo Setting compiler: Microsoft Visual C++ .NET 2005 (beta)
echo TARGET_OS=x86 >> ..\Makefiles\config.mak
set STLPORT_COMPILE_COMMAND=nmake -f nmake-vc8.mak
goto oc_end

:oc_icl
echo Compiler not supported in "explore" yet: Intel C++ Compiler
REM echo Setting compiler: Intel C++ Compiler
REM set STLPORT_COMPILE_COMMAND=nmake -f nmake-icl.mak
goto oc_end

:oc_evc3
echo Setting compiler: Microsoft eMbedded Visual C++ 3
echo COMPILER_NAME=evc3 >> ..\Makefiles\config.mak
echo CEVERSION=300 >> ..\Makefiles\config.mak
set STLPORT_COMPILE_COMMAND=nmake -f nmake-evc3.mak
goto oc_end

:oc_evc4
echo Setting compiler: Microsoft eMbedded Visual C++ .NET
echo COMPILER_NAME=evc4 >> ..\Makefiles\config.mak
echo CEVERSION=420 >> ..\Makefiles\config.mak
set STLPORT_COMPILE_COMMAND=nmake -f nmake-evc4.mak
goto oc_end

:oc_end
shift

goto cont_lp


REM **************************************************************************
REM *
REM * Target processor configuration
REM *
REM **************************************************************************
:opt_proc

if "%STLPORT_SELECTED_CONFIG%" == "evc3" goto op_ok
if "%STLPORT_SELECTED_CONFIG%" == "evc4" goto op_ok

echo Error: Setting processor for compiler other than evc3 and evc4!
goto op_end

:op_ok

if "%2" == "ARM" goto op_arm
if "%2" == "Arm" goto op_arm
if "%2" == "arm" goto op_arm

if "%2" == "X86" goto op_x86
if "%2" == "x86" goto op_x86

if "%2" == "MIPS" goto op_mips
if "%2" == "MIPS16" goto op_mips
if "%2" == "MIPSII" goto op_mips
if "%2" == "MIPSIV" goto op_mips

echo Unknown processor: %2
goto op_end

:op_arm
echo Setting processor: ARM
echo TARGET_PROC=arm >> ..\Makefiles\config.mak
goto op_end

:op_x86
echo Setting processor: x86 (Emulator)
echo TARGET_PROC=x86 >> ..\Makefiles\config.mak
goto op_end

:op_mips
echo Setting processor: MIPS
REM note, MIPSII (and all evc4 MIPS processors) are in the CE 4.0 SDK, so the
REM version gets redefined here
if "%STLPORT_SELECTED_CONFIG%" == "evc4" echo CEVERSION=400 >> ..\Makefiles\config.mak
echo TARGET_PROC=mips >> ..\Makefiles\config.mak

if "%2" == "MIPS16" echo DEFS_COMMON=/DMIPS16 >> ..\Makefiles\config.mak
if "%2" == "MIPSII" echo DEFS_COMMON=/DMIPSII >> ..\Makefiles\config.mak
if "%2" == "MIPSIV" echo DEFS_COMMON=/DMIPSIV >> ..\Makefiles\config.mak

if "%2" == "MIPS16" echo MIPS_MACHINE_TYPE=MIPS16 >> ..\Makefiles\config.mak
if "%2" == "MIPSII" echo MIPS_MACHINE_TYPE=MIPS >> ..\Makefiles\config.mak
if "%2" == "MIPSIV" echo MIPS_MACHINE_TYPE=MIPSFPU >> ..\Makefiles\config.mak

goto op_end

:op_end
shift

goto cont_lp


REM **************************************************************************
REM *
REM * Cross Compiling option
REM *
REM **************************************************************************

:opt_x
echo Setting up for cross compiling.
echo CROSS_COMPILING=1 >> ..\Makefiles\config.mak
goto cont_lp


REM **************************************************************************
REM *
REM * C runtime library selection
REM *
REM **************************************************************************

:opt_rtl
if "%STLPORT_SELECTED_CONFIG%" == "msvc6" goto or_ok
if "%STLPORT_SELECTED_CONFIG%" == "msvc7" goto or_ok
if "%STLPORT_SELECTED_CONFIG%" == "msvc71" goto or_ok
if "%STLPORT_SELECTED_CONFIG%" == "msvc8" goto or_ok

echo Error: Setting C runtime library for compiler other than microsoft ones!
goto or_end

:or_ok

if "%1" == "--rtl-static" echo Selecting static C runtime library for STLport
if "%1" == "--rtl-static" echo STLP_BUILD_FORCE_STATIC_RUNTIME=1 >> ..\Makefiles\config.mak

if "%1" == "--rtl-dynamic" echo Selecting dynamic C runtime library for STLport
if "%1" == "--rtl-dynamic" echo STLP_BUILD_FORCE_DYNAMIC_RUNTIME=1 >> ..\Makefiles\config.mak

:or_end
goto cont_lp

REM **************************************************************************
REM *
REM * Clean
REM *
REM **************************************************************************
:opt_clean
del ..\Makefiles\config.mak
goto cont_lp

REM **************************************************************************
REM *
REM * End loop
REM *
REM **************************************************************************

:end_loop

echo Done configuring STLport.
echo.

if "%STLPORT_COMPILE_COMMAND%" == "" goto skp_comp
echo Please type "%STLPORT_COMPILE_COMMAND%" to build STLport.
echo Type "%STLPORT_COMPILE_COMMAND% install" to install STLport to the "lib"
echo and "bin" folder when done.
echo.

:skp_comp
set STLPORT_SELECTED_CONFIG=
set STLPORT_COMPILE_COMMAND=
