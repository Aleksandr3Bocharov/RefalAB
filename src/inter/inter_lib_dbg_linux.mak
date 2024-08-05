#############################################################################
# inter_lib_dbg_linux.mak
#	Makefile for interpreter library(libr2_dbg.a) (debug mode) creation,
# 	result - lib/libr2_dbg.a library
#       Version for UNIX ( FreeBSD, Linux )
#
# Copyright(C) Aleksandr Bocharov
# Author : Aleksandr Bocharov
# Date : 05.08.2024
#############################################################################

####### Compiler, tools and options

.SUFFIXES: .c .ref

CC	=	gcc
CFLAGS	=	-pipe -Wall -O2 -Dmdebug -DUNIX
AR	=	ar
REFXCV	=	src/inter/refxcv	# refal2 + assembler for xcv
REFLIB	=	lib/libr2_dbg.a
S	=      	src/inter
####### Files

SOURCES =		\
	$(S)/d.c	\
	$(S)/rfintf.c 	\
	$(S)/rfrun1.c 	\
	$(S)/rfrun2.c 	\
	$(S)/xapply.c 	\
	$(S)/xar.c 	\
	$(S)/xcf.c 	\
	$(S)/xgcd.c 	\
	$(S)/xjak.c 	\
	$(S)/xmo.c 	\
	$(S)/xrename.c 	\
	$(S)/xtime.c 	\
	$(S)/xvv.c 	\
	$(S)/xvv5.c 	\
	$(S)/xcv.ref

OBJECTS =		\
	$(S)/d.o 	\
	$(S)/rfintf.o 	\
	$(S)/rfrun1.o 	\
	$(S)/rfrun2.o 	\
	$(S)/xapply.o 	\
	$(S)/xar.o 	\
	$(S)/xcf.o 	\
	$(S)/xcv.o 	\
	$(S)/xgcd.o 	\
	$(S)/xjak.o 	\
	$(S)/xmo.o 	\
	$(S)/xrename.o 	\
	$(S)/xtime.o 	\
	$(S)/xvv.o 	\
	$(S)/xvv5.o

####### Implicit rules

.ref.o: 
	$(REFXCV)  
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ 

####### Build rules

all: $(REFLIB)

$(REFLIB): $(OBJECTS)
	$(AR) rs $(REFLIB) $(OBJECTS) 


####### Dependences

$(S)/d.o:	$(S)/d.c $(S)/refal.def

$(S)/rfintf.o: 	$(S)/rfintf.c $(S)/refal.def

$(S)/rfrun1.o: 	$(S)/rfrun1.c $(S)/refal.def

$(S)/rfrun2.o: 	$(S)/rfrun2.c $(S)/refal.def

$(S)/xapply.o: 	$(S)/xapply.c $(S)/refal.def

$(S)/xar.o: 	$(S)/xar.c $(S)/refal.def

$(S)/xcf.o: 	$(S)/xcf.c $(S)/refal.def

$(S)/xcoden.o: 	$(S)/xcoden.c $(S)/refal.def

$(S)/xgcd.o: 	$(S)/xgcd.c $(S)/refal.def

$(S)/xjak.o: 	$(S)/xjak.c $(S)/refal.def

$(S)/xmo.o: 	$(S)/xmo.c $(S)/refal.def

$(S)/xrename.o: $(S)/xrename.c $(S)/refal.def

$(S)/xtime.o: 	$(S)/xtime.c $(S)/refal.def

$(S)/xvv.o: 	$(S)/xvv.c $(S)/refal.def

$(S)/xvv5.o: 	$(S)/xvv5.c $(S)/refal.def


####### End of Makefile
