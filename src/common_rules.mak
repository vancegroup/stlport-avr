#
#  Target directories
#
#

$(OUTDIR) :
	$(MKDIR) $(OUTDIR)
$(RELEASE_OBJDIR_dynamic) :
	$(MKDIR) $(RELEASE_OBJDIR_dynamic)
$(DEBUG_OBJDIR_dynamic) :
	$(MKDIR) $(DEBUG_OBJDIR_dynamic)
$(STLDEBUG_OBJDIR_dynamic) :
	$(MKDIR) $(STLDEBUG_OBJDIR_dynamic)
$(RELEASE_OBJDIR_static) :
	$(MKDIR) $(RELEASE_OBJDIR_static)
$(DEBUG_OBJDIR_static) :
	$(MKDIR) $(DEBUG_OBJDIR_static)
$(STLDEBUG_OBJDIR_static) :
	$(MKDIR) $(STLDEBUG_OBJDIR_static)

#create a compiler platform directory
platform:
	-@$(MKDIR) $(OUTDIR)
	-@$(MKDIR) $(OBJDIR_COMMON)
	-@$(MKDIR) $(OBJDIR)

clean_all_obj:
	-$(RM) obj

######   Targets ##################

all_static :   platform $(ALL_STATIC_LIBS)

all_dynamic :  platform $(ALL_DYNAMIC_LIBS)

release_static :  platform $(OUTDIR)$(PATH_SEP)$(RELEASE_LIB)

debug_static :  platform $(OUTDIR)$(PATH_SEP)$(DEBUG_LIB)

stldebug_static :  platform $(OUTDIR)$(PATH_SEP)$(STLDEBUG_LIB)

release_dynamic :  platform $(OUTDIR)$(PATH_SEP)$(RELEASE_DYNLIB)

debug_dynamic :  platform $(OUTDIR)$(PATH_SEP)$(DEBUG_DYNLIB)

stldebug_dynamic :  platform $(OUTDIR)$(PATH_SEP)$(STLDEBUG_DYNLIB)

install :  all $(INSTALL_STEP)

clean : $(CLEAN_SPECIFIC)
	-$(RM) $(RELEASE_OBJDIR_static) $(DEBUG_OBJDIR_static) \
        $(STLDEBUG_OBJDIR_static) $(RELEASE_OBJDIR_dynamic) \
        $(DEBUG_OBJDIR_dynamic) $(STLDEBUG_OBJDIR_dynamic) SunWS_cache Templates.DB tempinc

clobber : clean clean_all_obj
	-$(RM) $(OUTDIR)$(PATH_SEP)$(DEBUG_NAME).* \
               $(OUTDIR)$(PATH_SEP)$(RELEASE_NAME).* $(OUTDIR)$(PATH_SEP)$(STLDEBUG_NAME).*

HEADER_DIRS1 = . SC5 using wrap_std
HEADER_DIRS2 = config stl stl/debug stl/wrappers using/h  wrap_std/h

symbolic_links :
	$(RM) $(OUTDIR)/$(RELEASE_NAME).$(DYNEXT)
	$(RM) $(OUTDIR)/$(STLDEBUG_NAME).$(DYNEXT)
	ln -s $(RELEASE_DYNLIB) $(OUTDIR)/$(RELEASE_NAME).$(DYNEXT)
	ln -s $(STLDEBUG_DYNLIB) $(OUTDIR)/$(STLDEBUG_NAME).$(DYNEXT)

install_unix :
	-$(RM) $(INSTALLDIR_INC)
	for dir in $(HEADER_DIRS1); \
	do \
	  ./mkinstalldirs $(INSTALLDIR_INC)/$$dir; \
	  for file in `cat ../stlport/$$dir/export`; \
	  do \
		$(INSTALL_H) ../stlport/$$dir/$$file $(INSTALLDIR_INC)/$$dir ; \
          done \
	done
	for dir in $(HEADER_DIRS2); \
	do \
	  ./mkinstalldirs $(INSTALLDIR_INC)/$$dir; \
	  for file in `ls ../stlport/$$dir/*.*`; \
	  do \
		$(INSTALL_H) $$file $(INSTALLDIR_INC)/$$file ; \
          done \
	done

	./mkinstalldirs $(INSTALLDIR_LIB)
	for file in `ls $(OUTDIR)/$(LIB_BASENAME)*`; \
	do \
        -$(RM)  $(INSTALLDIR_LIB)/$file
	$(INSTALL_LIB)  $$file $(INSTALLDIR_LIB); \
	done
	-$(RM) $(INSTALLDIR_LIB)/$(RELEASE_NAME).$(DYNEXT)
	-$(RM) $(INSTALLDIR_LIB)/$(STLDEBUG_NAME).$(DYNEXT)
	ln -s $(RELEASE_DYNLIB) $(INSTALLDIR_LIB)/$(RELEASE_NAME).$(DYNEXT)
	-ln -s $(STLDEBUG_DYNLIB) $(INSTALLDIR_LIB)/$(STLDEBUG_NAME).$(DYNEXT)

$(OUTDIR)$(PATH_SEP)$(RELEASE_DYNLIB) : $(OUTDIR) $(RELEASE_OBJDIR_dynamic) $(DEF_FILE) $(RELEASE_OBJECTS_dynamic)
	$(DYN_LINK) $(DYNLINK_OUT)$(OUTDIR)$(PATH_SEP)$(RELEASE_DYNLIB) $(LDFLAGS_RELEASE_dynamic) $(RELEASE_OBJECTS_dynamic) $(LDLIBS_RELEASE_dynamic) 

$(OUTDIR)$(PATH_SEP)$(RELEASE_LIB) : $(OUTDIR) $(RELEASE_OBJDIR_static) $(DEF_FILE) $(RELEASE_OBJECTS_static)
	$(LINK) $(LINK_OUT)$(OUTDIR)$(PATH_SEP)$(RELEASE_LIB) $(LDFLAGS_RELEASE_static) $(RELEASE_OBJECTS_static) $(LDLIBS_RELEASE_static)

$(OUTDIR)$(PATH_SEP)$(DEBUG_DYNLIB) : $(OUTDIR) $(DEBUG_OBJDIR_dynamic) $(DEF_FILE) $(DEBUG_OBJECTS_dynamic)
	$(DYN_LINK) $(DYNLINK_OUT)$(OUTDIR)$(PATH_SEP)$(DEBUG_DYNLIB) $(LDFLAGS_DEBUG_dynamic) $(DEBUG_OBJECTS_dynamic) $(LDLIBS_DEBUG_dynamic) 

$(OUTDIR)$(PATH_SEP)$(DEBUG_LIB) : $(OUTDIR) $(DEBUG_OBJDIR_static) $(DEF_FILE) $(DEBUG_OBJECTS_static)
	$(LINK) $(LINK_OUT)$(OUTDIR)$(PATH_SEP)$(DEBUG_LIB) $(LDLIBS_DEBUG_static) $(LDFLAGS_DEBUG_static) $(DEBUG_OBJECTS_static)  

$(OUTDIR)$(PATH_SEP)$(STLDEBUG_DYNLIB) : $(OUTDIR) $(STLDEBUG_OBJDIR_dynamic) $(DEF_FILE) $(STLDEBUG_OBJECTS_dynamic)
	$(DYN_LINK) $(DYNLINK_OUT)$(OUTDIR)$(PATH_SEP)$(STLDEBUG_DYNLIB) $(LDFLAGS_STLDEBUG_dynamic) $(STLDEBUG_OBJECTS_dynamic) $(LDLIBS_STLDEBUG_dynamic)

$(OUTDIR)$(PATH_SEP)$(STLDEBUG_LIB) : $(OUTDIR) $(STLDEBUG_OBJDIR_static) $(DEF_FILE) $(STLDEBUG_OBJECTS_static)
	$(LINK) $(LINK_OUT)$(OUTDIR)$(PATH_SEP)$(STLDEBUG_LIB) $(LDFLAGS_STLDEBUG_static) $(STLDEBUG_OBJECTS_static)  $(LDLIBS_STLDEBUG_static)

locale_impl.cpp : codecvt.cpp collate.cpp ctype.cpp monetary.cpp num_get.cpp num_get_float.cpp num_put.cpp num_put_float.cpp numpunct.cpp time_facets.cpp messages.cpp

locale_catalog.cpp : ctype_byname.cpp collate_byname.cpp codecvt_byname.cpp numpunct_byname.cpp monetary_byname.cpp messages_byname.cpp


#########################################
