# -*- Makefile -*- Time-stamp:
# $Id: rules-o.mak

!message build\Makefiles\borland\rules-o.mak

.AUTODEPEND

.cpp{$(OUTPUT_DIR)}.obj:
	$(COMPILE_cpp_REL) $(OUTPUT_OPTION) -o$@ $<

{$(SRCDIR)\cppunit;$(SRCDIR);$(SRCROOT_EXT)\$(USE_MAKE)}.cpp{$(SRCROOT_EXT)\$(OUTPUT_DIR)}.obj:
	$(COMPILE_cpp_REL) $(OUTPUT_OPTION) -o$@ $<

.cc{$(OUTPUT_DIR)}.obj:
	$(COMPILE_cpp_REL) $(OUTPUT_OPTION) -o$@ $<

{$(SRCDIR)}.cc{$(SRCROOT_EXT)\$(OUTPUT_DIR)}.obj:
	$(COMPILE_cpp_REL) $(OUTPUT_OPTION) -o$@ $<

.c{$(OUTPUT_DIR)}.obj:
	$(COMPILE_c_REL) $(OUTPUT_OPTION) -o$@ $<

{$(SRCDIR)}.c{$(SRCROOT_EXT)\$(OUTPUT_DIR)}.obj:
	$(COMPILE_c_REL) $(OUTPUT_OPTION) -o$@ $<

.rc{$(OUTPUT_DIR)}.res:
	$(COMPILE_rc_REL) $(RC_OUTPUT_OPTION) -o$@ $<

{$(SRCDIR)}.rc{$(SRCROOT_EXT)\$(OUTPUT_DIR)}.res:
	$(COMPILE_rc_REL) $(RC_OUTPUT_OPTION) -o$@ $<

#!if "$(OUTPUT_DIR_A)" != "$(OUTPUT_DIR)"
# Rules for release output (static):

.cpp{$(OUTPUT_DIR_A)}.obj:
	$(COMPILE_cpp_STATIC) $(OUTPUT_OPTION_STATIC) -o$@ $<

{$(SRCDIR)\cppunit;$(SRCDIR);$(SRCROOT_EXT)\$(USE_MAKE)}.cpp{$(SRCROOT_EXT)\$(OUTPUT_DIR_A)}.obj:
	$(COMPILE_cpp_STATIC) $(OUTPUT_OPTION_STATIC) -o$@ $<

.cc{$(OUTPUT_DIR_A)}.obj:
	$(COMPILE_cpp_STATIC) $(OUTPUT_OPTION_STATIC) -o$@ $<

{$(SRCDIR)}.cc{$(SRCROOT_EXT)\$(OUTPUT_DIR_A)}.obj:
	$(COMPILE_cpp_STATIC) $(OUTPUT_OPTION_STATIC) -o$@ $<

.c{$(OUTPUT_DIR_A)}.obj:
	$(COMPILE_c_STATIC) $(OUTPUT_OPTION_STATIC) -o$@ $<

{$(SRCDIR)}.c{$(SRCROOT_EXT)\$(OUTPUT_DIR_A)}.obj:
	$(COMPILE_c_STATIC) $(OUTPUT_OPTION_STATIC) -o$@ $<

.rc{$(OUTPUT_DIR_A)}.res:
	$(COMPILE_rc_STATIC) $(RC_OUTPUT_OPTION_STATIC) -o$@ $<

{$(SRCDIR)}.rc{$(SRCROOT_EXT)\$(OUTPUT_DIR_A)}.res:
	$(COMPILE_rc_STATIC) $(RC_OUTPUT_OPTION_STATIC) -o$@ $<

#!endif

# Rules for debug output:

.cpp{$(OUTPUT_DIR_DBG)}.obj:
	$(COMPILE_cpp_DBG) $(OUTPUT_OPTION_DBG) -o$@ $<

{$(SRCDIR)\cppunit;$(SRCDIR);$(SRCROOT_EXT)\$(USE_MAKE)}.cpp{$(SRCROOT_EXT)\$(OUTPUT_DIR_DBG)}.obj:
	$(COMPILE_cpp_DBG) $(OUTPUT_OPTION_DBG) -o$@ $<

.cc{$(OUTPUT_DIR_DBG)}.obj:
	$(COMPILE_cpp_DBG) $(OUTPUT_OPTION_DBG) -o$@ $<

{$(SRCDIR)}.cc{$(SRCROOT_EXT)\$(OUTPUT_DIR_DBG)}.obj:
	$(COMPILE_cpp_DBG) $(OUTPUT_OPTION_DBG) -o$@ $<

.c{$(OUTPUT_DIR_DBG)}.obj:
	$(COMPILE_c_DBG) $(OUTPUT_OPTION_DBG) -o$@ $<

{$(SRCDIR)}.c{$(SRCROOT_EXT)\$(OUTPUT_DIR_DBG)}.obj:
	$(COMPILE_c_DBG) $(OUTPUT_OPTION_DBG) -o$@ $<

.rc{$(OUTPUT_DIR_DBG)}.res:
	$(COMPILE_rc_DBG) $(RC_OUTPUT_OPTION_DBG) -o$@ $<

{$(SRCDIR)}.rc{$(SRCROOT_EXT)\$(OUTPUT_DIR_DBG)}.res:
	$(COMPILE_rc_DBG) $(RC_OUTPUT_OPTION_DBG) -o$@ $<

#!if "$(OUTPUT_DIR_A_DBG)" != "$(OUTPUT_DIR_DBG)"
# Rules for debug output (static):

.cpp{$(OUTPUT_DIR_A_DBG)}.obj:
	$(COMPILE_cpp_STATIC_DBG) $(OUTPUT_OPTION_STATIC_DBG) -o$@ $<

{$(SRCDIR)\cppunit;$(SRCDIR);$(SRCROOT_EXT)\$(USE_MAKE)}.cpp{$(SRCROOT_EXT)\$(OUTPUT_DIR_A_DBG)}.obj:
	$(COMPILE_cpp_STATIC_DBG) $(OUTPUT_OPTION_STATIC_DBG) -o$@ $<

.cc{$(OUTPUT_DIR_A_DBG)}.obj:
	$(COMPILE_cpp_STATIC_DBG) $(OUTPUT_OPTION_STATIC_DBG) -o$@ $<

{$(SRCDIR)}.cc{$(SRCROOT_EXT)\$(OUTPUT_DIR_A_DBG)}.obj:
	$(COMPILE_cpp_STATIC_DBG) $(OUTPUT_OPTION_STATIC_DBG) -o$@ $<

.c{$(OUTPUT_DIR_A_DBG)}.obj:
	$(COMPILE_c_STATIC_DBG) $(OUTPUT_OPTION_STATIC_DBG) -o$@ $<

{$(SRCDIR)}.c{$(SRCROOT_EXT)\$(OUTPUT_DIR_A_DBG)}.obj:
	$(COMPILE_c_STATIC_DBG) $(OUTPUT_OPTION_STATIC_DBG) -o$@ $<

.rc{$(OUTPUT_DIR_A_DBG)}.res:
	$(COMPILE_rc_STATIC_DBG) $(RC_OUTPUT_OPTION_STATIC_DBG) -o$@ $<

{$(SRCDIR)}.rc{$(SRCROOT_EXT)\$(OUTPUT_DIR_A_DBG)}.res:
	$(COMPILE_rc_STATIC_DBG) $(RC_OUTPUT_OPTION_STATIC_DBG) -o$@ $<

#!endif

# Rules for STLport debug output:

.cpp{$(OUTPUT_DIR_STLDBG)}.obj:
	$(COMPILE_cpp_STLDBG) $(OUTPUT_OPTION_STLDBG) -o$@ $<

{$(SRCDIR)\cppunit;$(SRCDIR);$(SRCROOT_EXT)\$(USE_MAKE)}.cpp{$(SRCROOT_EXT)\$(OUTPUT_DIR_STLDBG)}.obj:
	$(COMPILE_cpp_STLDBG) $(OUTPUT_OPTION_STLDBG) -o$@ $<

.cc{$(OUTPUT_DIR_STLDBG)}.obj:
	$(COMPILE_cpp_STLDBG) $(OUTPUT_OPTION_STLDBG) -o$@ $<

{$(SRCDIR)}.cc{$(SRCROOT_EXT)\$(OUTPUT_DIR_STLDBG)}.obj:
	$(COMPILE_cpp_STLDBG) $(OUTPUT_OPTION_STLDBG) -o$@ $<

.c{$(OUTPUT_DIR_STLDBG)}.obj:
	$(COMPILE_c_STLDBG) $(OUTPUT_OPTION_STLDBG) -o$@ $<

{$(SRCDIR)}.c{$(SRCROOT_EXT)\$(OUTPUT_DIR_STLDBG)}.obj:
	$(COMPILE_c_STLDBG) $(OUTPUT_OPTION_STLDBG) -o$@ $<

.rc{$(OUTPUT_DIR_STLDBG)}.res:
	$(COMPILE_rc_STLDBG) $(RC_OUTPUT_OPTION_STLDBG) -o$@ $<

{$(SRCDIR)}.rc{$(SRCROOT_EXT)\$(OUTPUT_DIR_STLDBG)}.res:
	$(COMPILE_rc_STLDBG) $(RC_OUTPUT_OPTION_STLDBG) -o$@ $<

#!if "$(OUTPUT_DIR_A_STLDBG)" != "$(OUTPUT_DIR_STLDBG)"
# Rules for STLport debug output (static):

.cpp{$(OUTPUT_DIR_A_STLDBG)}.obj:
	$(COMPILE_cpp_STATIC_STLDBG) $(OUTPUT_OPTION_STATIC_STLDBG) -o$@ $<

{$(SRCDIR)\cppunit;$(SRCDIR);$(SRCROOT_EXT)\$(USE_MAKE)}.cpp{$(SRCROOT_EXT)\$(OUTPUT_DIR_A_STLDBG)}.obj:
	$(COMPILE_cpp_STATIC_STLDBG) $(OUTPUT_OPTION_STATIC_STLDBG) -o$@ $<

.cc{$(OUTPUT_DIR_A_STLDBG)}.obj:
	$(COMPILE_cpp_STATIC_STLDBG) $(OUTPUT_OPTION_STATIC_STLDBG) -o$@ $<

{$(SRCDIR)}.cc{$(SRCROOT_EXT)\$(OUTPUT_DIR_A_STLDBG)}.obj:
	$(COMPILE_cpp_STATIC_STLDBG) $(OUTPUT_OPTION_STATIC_STLDBG) -o$@ $<

.c{$(OUTPUT_DIR_A_STLDBG)}.obj:
	$(COMPILE_c_STATIC_STLDBG) $(OUTPUT_OPTION_STATIC_STLDBG) -o$@ $<

{$(SRCDIR)}.c{$(SRCROOT_EXT)\$(OUTPUT_DIR_A_STLDBG)}.obj:
	$(COMPILE_c_STATIC_STLDBG) $(OUTPUT_OPTION_STATIC_STLDBG) -o$@ $<

.rc{$(OUTPUT_DIR_A_STLDBG)}.res:
	$(COMPILE_rc_STATIC_STLDBG) $(RC_OUTPUT_OPTION_STATIC_STLDBG) -o$@ $<

{$(SRCDIR)}.rc{$(SRCROOT_EXT)\$(OUTPUT_DIR_A_STLDBG)}.res:
	$(COMPILE_rc_STATIC_STLDBG) $(RC_OUTPUT_OPTION_STATIC_STLDBG) -o$@ $<

#!endif

#!if EXIST( ./rules-o.mak )
# Rules like
#    {$(BOOST_TST_SRC)}.cpp{$(SRCROOT_EXT)\$(OUTPUT_DIR)}.obj:
#            $(COMPILE_cpp_REL) $(OUTPUT_OPTION) -o$@ $<
# (this is due to bad path/string processing in bogus nmake)
#!include ./rules-o.mak
#!endif

