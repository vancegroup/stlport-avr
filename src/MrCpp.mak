MAKEFILE        = MrCpp.mak
¥MondoBuild¥    = {MAKEFILE}  # Make blank to avoid rebuilds when makefile is modified

Sym-PPC         	= -sym on
!ifdef DEBUG
config_				= .PPC.DBG
MrCpp_DebugOptions 	= -inline none,global -opt none {Sym-PPC}
STL_DebugOptions 	= -d __STL_DEBUG -d __STL_DEBUG_ALLOC -d __STL_DEBUG_UNINITIALIZED
!else
config_				= .PPC
MrCpp_DebugOptions 	= 
STL_DebugOptions 	= 
!endif
ObjDir          	= :{config_}:
SrcDir				= :

Includes     	= -i : -i "{STL}" -i "{CIncludes}"

MrCpp_Options 	= -ansi on -ansifor -bool on -exceptions on -rtti on -align power -j0 -traceback -opt size -inline 3,global -includes unix_mac
				
STL_Options  	= 	#-d __STL_USE_NEWALLOC ¶
					-d __STL_NO_SGI_IOSTREAMS ¶
					# end

Link_options = ¶
		-c 'MPS ' ¶
		-mf ¶
		-d ¶
		-Linkfaster off ¶
		#{Sym-PPC} ¶
		# end

### Default Rules ###

"{ObjDir}" Ä "{SrcDir}"

.cpp.x  Ä  .cpp  # {¥MondoBuild¥}
	###
	echo "¶nCompiling:      '"{depDir}{default}.cpp"'"
	"{MrCpp}" {depDir}{default}.cpp ¶
		-o {targDir}{default}.cpp.x ¶
		{Includes} ¶
		{MrCpp_Options} {MrCpp_DebugOptions} {other_MrCpp_Options} ¶
		{STL_Options} {STL_DebugOptions} {other_STL_Options}
		if "{status}"
			set compile_status 1
		end


### Optional Dependencies ###

setup Ä $OutOfDate
	###
	echo "¶n# Target:       '"{ObjDir}"'"
	unset compile_status
	if !`exists "{ObjDir}"`
		newfolder "{ObjDir}"
	end


### Build this target to generate "include file" dependencies. ###

Dependencies  Ä  $OutOfDate #*TY 02/26/2000 - MakeDepend does not work unless all mentioned include directory exists
	###
	echo "¶nUpdating:       {MAKEFILE} Dependencies"
	MakeDepend ¶
		-append {MAKEFILE} ¶
		-ignore "{CIncludes}" ¶
		-objdir "{ObjDir}" ¶
		-objext .x ¶
		{Includes} ¶
		{SrcFiles}


##################################################################################
#	{stl}:src: build rule
##################################################################################

### Source Files ###

STLportLibSrcFiles        =  ¶
				c_locale_stub.cpp ¶
				codecvt.cpp	¶
				codecvt_byname.cpp	¶
				codecvt_w.cpp	¶
				collate.cpp	¶
				collate_byname.cpp	¶
				collate_byname_w.cpp	¶
				collate_w.cpp	¶
				complex.cpp	¶
				complex_exp.cpp	¶
				complex_io.cpp	¶
				complex_io_w.cpp	¶
				complex_trig.cpp	¶
				ctype.cpp	¶
				ctype_byname.cpp	¶
				ctype_byname_w.cpp	¶
				ctype_w.cpp	¶
#				dll_main.cpp	¶
				fstream.cpp	¶
				fstream_w.cpp	¶
				ios.cpp	¶
				ios_base.cpp	¶
				ios_w.cpp	¶
				iostream.cpp	¶
				locale.cpp	¶
				locale_catalog.cpp	¶
				locale_impl.cpp	¶
				message_facets.cpp	¶
				message_facets_w.cpp	¶
				monetary.cpp	¶
				money_get.cpp	¶
				money_get_w.cpp	¶
				money_put.cpp	¶
				money_put_w.cpp	¶
				moneypunct.cpp	¶
				moneypunct_byname.cpp	¶
				moneypunct_byname_w.cpp	¶
				moneypunct_w.cpp	¶
				num_get.cpp	¶
				num_get_float.cpp	¶
				num_get_inst.cpp	¶
				num_get_inst_w.cpp	¶
				num_put.cpp	¶
				num_put_float.cpp	¶
				num_put_inst.cpp	¶
				num_put_inst_w.cpp	¶
				numpunct.cpp	¶
				numpunct_byname.cpp	¶
				numpunct_w.cpp	¶
				range_errors.cpp	¶
				sstream.cpp	¶
				stdio_streambuf.cpp	¶
				streambuf.cpp	¶
				string.cpp	¶
				string_w.cpp	¶
				strstream.cpp	¶
#				test.cpp	¶
				time_facets.cpp	¶
				time_get.cpp	¶
				time_get_w.cpp	¶
				time_put.cpp	¶
				time_put_w.cpp	¶
				# end


### Object Files ###

STLportLibObjFiles-PPC    =  ¶
				"{ObjDir}"c_locale_stub.cpp.x ¶
				"{ObjDir}"codecvt.cpp.x	¶
				"{ObjDir}"codecvt_byname.cpp.x	¶
				"{ObjDir}"codecvt_w.cpp.x	¶
				"{ObjDir}"collate.cpp.x	¶
				"{ObjDir}"collate_byname.cpp.x	¶
				"{ObjDir}"collate_byname_w.cpp.x	¶
				"{ObjDir}"collate_w.cpp.x	¶
				"{ObjDir}"complex.cpp.x	¶
				"{ObjDir}"complex_exp.cpp.x	¶
				"{ObjDir}"complex_io.cpp.x	¶
				"{ObjDir}"complex_io_w.cpp.x	¶
				"{ObjDir}"complex_trig.cpp.x	¶
				"{ObjDir}"ctype.cpp.x	¶
				"{ObjDir}"ctype_byname.cpp.x	¶
				"{ObjDir}"ctype_byname_w.cpp.x	¶
				"{ObjDir}"ctype_w.cpp.x	¶
				"{ObjDir}"fstream.cpp.x	¶
				"{ObjDir}"fstream_w.cpp.x	¶
				"{ObjDir}"ios.cpp.x	¶
				"{ObjDir}"ios_base.cpp.x	¶
				"{ObjDir}"ios_w.cpp.x	¶
				"{ObjDir}"iostream.cpp.x	¶
				"{ObjDir}"locale.cpp.x	¶
				"{ObjDir}"locale_catalog.cpp.x	¶
				"{ObjDir}"locale_impl.cpp.x	¶
				"{ObjDir}"message_facets.cpp.x	¶
				"{ObjDir}"message_facets_w.cpp.x	¶
				"{ObjDir}"monetary.cpp.x	¶
				"{ObjDir}"money_get.cpp.x	¶
				"{ObjDir}"money_get_w.cpp.x	¶
				"{ObjDir}"money_put.cpp.x	¶
				"{ObjDir}"money_put_w.cpp.x	¶
				"{ObjDir}"moneypunct.cpp.x	¶
				"{ObjDir}"moneypunct_byname.cpp.x	¶
				"{ObjDir}"moneypunct_byname_w.cpp.x	¶
				"{ObjDir}"moneypunct_w.cpp.x	¶
				"{ObjDir}"num_get.cpp.x	¶
				"{ObjDir}"num_get_float.cpp.x	¶
				"{ObjDir}"num_get_inst.cpp.x	¶
				"{ObjDir}"num_get_inst_w.cpp.x	¶
				"{ObjDir}"num_put.cpp.x	¶
				"{ObjDir}"num_put_float.cpp.x	¶
				"{ObjDir}"num_put_inst.cpp.x	¶
				"{ObjDir}"num_put_inst_w.cpp.x	¶
				"{ObjDir}"numpunct.cpp.x	¶
				"{ObjDir}"numpunct_byname.cpp.x	¶
				"{ObjDir}"numpunct_w.cpp.x	¶
				"{ObjDir}"range_errors.cpp.x	¶
				"{ObjDir}"sstream.cpp.x	¶
				"{ObjDir}"stdio_streambuf.cpp.x	¶
				"{ObjDir}"streambuf.cpp.x	¶
				"{ObjDir}"string.cpp.x	¶
				"{ObjDir}"string_w.cpp.x	¶
				"{ObjDir}"strstream.cpp.x	¶
				"{ObjDir}"time_facets.cpp.x	¶
				"{ObjDir}"time_get.cpp.x	¶
				"{ObjDir}"time_get_w.cpp.x	¶
				"{ObjDir}"time_put.cpp.x	¶
				"{ObjDir}"time_put_w.cpp.x	¶
				# end


### Build Rules ###

build	ÄÄ	setup
build	ÄÄ	"{ObjDir}"STLportLib{config_}.o

install  ÄÄ  build
	###
	echo "¶nInstalling:     ¶{stl¶}:lib:STLportLib{config_}.o"
	duplicate -y "{ObjDir}"STLportLib{config_}.o "{stl}":lib:STLportLib{config_}.o

"{ObjDir}"STLportLib{config_}.o  ÄÄ  {STLportLibObjFiles-PPC} {¥MondoBuild¥}
	###
	echo "¶nLibbing:        {Targ}"
	PPCLink ¶
		-xm l ¶
		-t 'XCOF' ¶
		-o {Targ} ¶
		{STLportLibObjFiles-PPC} ¶
		{Link_options} ¶
		{Sym-PPC} ¶
		# end

