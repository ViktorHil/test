########################################################
# Copyright 2016 Continental Automotive Systems Inc.
#
# Generic Make file to build 
#
########################################################

SOURCES:= ${wildcard *.cpp}
OBJECTS:= ${SOURCES:.cpp=.o}


.PHONY: all clean distclean install

all: $(OBJECTS)

clean distclean:
	rm -f *.o

$(OBJECTS):
	g++ -pthread -std=gnu++17 ${@:.o=.cpp} -o Test


