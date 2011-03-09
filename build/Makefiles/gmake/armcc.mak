AR := armar
CXX := armcc
CC := armcc
LINK := armlink

CFLAGS = --exceptions --cpp --fpmode=ieee_full -I $(STLPORT_INCLUDE_DIR) -D__USE_C99_MATH
CXXFLAGS = --exceptions --cpp --fpmode=ieee_full -I $(STLPORT_INCLUDE_DIR) -D__USE_C99_MATH

OUTPUT_OPTION = -o $@
LINK_OUTPUT_OPTION = ${OUTPUT_OPTION}
