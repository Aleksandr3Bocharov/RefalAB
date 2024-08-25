#############################################################################
# comp_dbg_linux.mak
# 	makefile for building of the compiler from refal-2 language (debug mode), 
# 	result - bin/refal2_dbg executable module.
#       Version for UNIX ( FreeBSD, Linux )
#
# Copyright (C) Aleksandr Bocharov
# Author: Aleksandr Bocharov
# Date: 05.08.2024
#############################################################################

####### Compiler, tools and options

.SUFFIXES: .c 

CC		=	gcc
CFLAGS		=	-pipe -Wall -O2 -Dmdebug -DUNIX
LINK		=	gcc

S		=	src/comp
BIN_DIR		=	bin

####### Files

SOURCES =			\
		$(S)/ccst.c 	\
		$(S)/cerr.c 	\
		$(S)/cgop.c 	\
		$(S)/cj.c 	\
		$(S)/clu.c 	\
		$(S)/cs.c 	\
		$(S)/plc.c 	\
		$(S)/refal.c

OBJECTS =			\
		$(S)/ccst.o 	\
		$(S)/cerr.o 	\
		$(S)/cgop.o 	\
		$(S)/cj.o 	\
		$(S)/clu.o 	\
		$(S)/cs.o 	\
		$(S)/plc.o 	\
		$(S)/refal.o

TARGET =	refal2_dbg


####### Implicit rules

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

####### Build rules

all:	$(TARGET)

$(TARGET): $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/$(TARGET) $(OBJECTS) 

####### Dependences

$(S)/ccst.o: $(S)/ccst.c

$(S)/cerr.o: $(S)/cerr.c $(S)/refal.def

$(S)/cgop.o: $(S)/cgop.c $(S)/refal.def

$(S)/cj.o: $(S)/cj.c $(S)/refal.def

$(S)/clu.o: $(S)/clu.c $(S)/refal.def

$(S)/cs.o: $(S)/cs.c $(S)/refal.def

$(S)/plc.o: $(S)/plc.c

$(S)/refal.o: $(S)/refal.c $(S)/refal.def

### End of Makefile
