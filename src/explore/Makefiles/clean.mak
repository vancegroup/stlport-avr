# -*- Makefile -*- Time-stamp: <03/07/15 12:19:04 ptr>
# $Id$

PHONY += clean clobber distclean

clean::	
	@-rm -f core core.*
	@-rm -f $(OBJ) $(DEP)
	@-rm -f $(OBJ_DBG) $(DEP_DBG)
	@-rm -f $(OBJ_STLDBG) $(DEP_STLDBG)

clobber::	clean
	@-rm -f $(DEPENDS_COLLECTION)

distclean::	clobber
