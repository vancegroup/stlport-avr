#
# Basename for libraries
#

#
# This makefile will work for SUN CC 5.0-5.3 (Forte 6 Update 2)
#

LIB_BASENAME = libstlport_sunpro64

CC = CC -xarch=v9
CXX = CC -xarch=v9

COMP = SUN64

include sunpro-common.mak
