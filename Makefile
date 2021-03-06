#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = -Wall
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g -DMACHINE64
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS) -ldl
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/ccnxt

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2 -DMACHINE64
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s -ldl
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/ccnxt

INC_DEBUG32 = $(INC)
CFLAGS_DEBUG32 = $(CFLAGS) -g
RESINC_DEBUG32 = $(RESINC)
RCFLAGS_DEBUG32 = $(RCFLAGS)
LIBDIR_DEBUG32 = $(LIBDIR)
LIB_DEBUG32 = $(LIB)
LDFLAGS_DEBUG32 = $(LDFLAGS) -ldl
OBJDIR_DEBUG32 = obj/Debug
DEP_DEBUG32 = 
OUT_DEBUG32 = bin/Debug/ccnxt

INC_RELEASE32 = $(INC)
CFLAGS_RELEASE32 = $(CFLAGS) -O2
RESINC_RELEASE32 = $(RESINC)
RCFLAGS_RELEASE32 = $(RCFLAGS)
LIBDIR_RELEASE32 = $(LIBDIR)
LIB_RELEASE32 = $(LIB)
LDFLAGS_RELEASE32 = $(LDFLAGS) -s -ldl
OBJDIR_RELEASE32 = obj/Release
DEP_RELEASE32 = 
OUT_RELEASE32 = bin/Release/ccnxt

OBJ_DEBUG = $(OBJDIR_DEBUG)/artiglio.o $(OBJDIR_DEBUG)/business.o $(OBJDIR_DEBUG)/cmdline.o $(OBJDIR_DEBUG)/func_finder.o $(OBJDIR_DEBUG)/injection.o $(OBJDIR_DEBUG)/main.o $(OBJDIR_DEBUG)/offset_finder.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/artiglio.o $(OBJDIR_RELEASE)/business.o $(OBJDIR_RELEASE)/cmdline.o $(OBJDIR_RELEASE)/func_finder.o $(OBJDIR_RELEASE)/injection.o $(OBJDIR_RELEASE)/main.o $(OBJDIR_RELEASE)/offset_finder.o

OBJ_DEBUG32 = $(OBJDIR_DEBUG32)/artiglio.o $(OBJDIR_DEBUG32)/business.o $(OBJDIR_DEBUG32)/cmdline.o $(OBJDIR_DEBUG32)/func_finder.o $(OBJDIR_DEBUG32)/injection.o $(OBJDIR_DEBUG32)/main.o $(OBJDIR_DEBUG32)/offset_finder.o

OBJ_RELEASE32 = $(OBJDIR_RELEASE32)/artiglio.o $(OBJDIR_RELEASE32)/business.o $(OBJDIR_RELEASE32)/cmdline.o $(OBJDIR_RELEASE32)/func_finder.o $(OBJDIR_RELEASE32)/injection.o $(OBJDIR_RELEASE32)/main.o $(OBJDIR_RELEASE32)/offset_finder.o

all: debug release debug32 release32

clean: clean_debug clean_release clean_debug32 clean_release32

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/artiglio.o: artiglio.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c artiglio.c -o $(OBJDIR_DEBUG)/artiglio.o

$(OBJDIR_DEBUG)/business.o: business.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c business.c -o $(OBJDIR_DEBUG)/business.o

$(OBJDIR_DEBUG)/cmdline.o: cmdline.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c cmdline.c -o $(OBJDIR_DEBUG)/cmdline.o

$(OBJDIR_DEBUG)/func_finder.o: func_finder.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c func_finder.c -o $(OBJDIR_DEBUG)/func_finder.o

$(OBJDIR_DEBUG)/injection.o: injection.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c injection.c -o $(OBJDIR_DEBUG)/injection.o

$(OBJDIR_DEBUG)/main.o: main.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.c -o $(OBJDIR_DEBUG)/main.o

$(OBJDIR_DEBUG)/offset_finder.o: offset_finder.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c offset_finder.c -o $(OBJDIR_DEBUG)/offset_finder.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/artiglio.o: artiglio.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c artiglio.c -o $(OBJDIR_RELEASE)/artiglio.o

$(OBJDIR_RELEASE)/business.o: business.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c business.c -o $(OBJDIR_RELEASE)/business.o

$(OBJDIR_RELEASE)/cmdline.o: cmdline.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c cmdline.c -o $(OBJDIR_RELEASE)/cmdline.o

$(OBJDIR_RELEASE)/func_finder.o: func_finder.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c func_finder.c -o $(OBJDIR_RELEASE)/func_finder.o

$(OBJDIR_RELEASE)/injection.o: injection.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c injection.c -o $(OBJDIR_RELEASE)/injection.o

$(OBJDIR_RELEASE)/main.o: main.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.c -o $(OBJDIR_RELEASE)/main.o

$(OBJDIR_RELEASE)/offset_finder.o: offset_finder.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c offset_finder.c -o $(OBJDIR_RELEASE)/offset_finder.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

before_debug32: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG32) || mkdir -p $(OBJDIR_DEBUG32)

after_debug32: 

debug32: before_debug32 out_debug32 after_debug32

out_debug32: before_debug32 $(OBJ_DEBUG32) $(DEP_DEBUG32)
	$(LD) $(LIBDIR_DEBUG32) -o $(OUT_DEBUG32) $(OBJ_DEBUG32)  $(LDFLAGS_DEBUG32) $(LIB_DEBUG32)

$(OBJDIR_DEBUG32)/artiglio.o: artiglio.c
	$(CC) $(CFLAGS_DEBUG32) $(INC_DEBUG32) -c artiglio.c -o $(OBJDIR_DEBUG32)/artiglio.o

$(OBJDIR_DEBUG32)/business.o: business.c
	$(CC) $(CFLAGS_DEBUG32) $(INC_DEBUG32) -c business.c -o $(OBJDIR_DEBUG32)/business.o

$(OBJDIR_DEBUG32)/cmdline.o: cmdline.c
	$(CC) $(CFLAGS_DEBUG32) $(INC_DEBUG32) -c cmdline.c -o $(OBJDIR_DEBUG32)/cmdline.o

$(OBJDIR_DEBUG32)/func_finder.o: func_finder.c
	$(CC) $(CFLAGS_DEBUG32) $(INC_DEBUG32) -c func_finder.c -o $(OBJDIR_DEBUG32)/func_finder.o

$(OBJDIR_DEBUG32)/injection.o: injection.c
	$(CC) $(CFLAGS_DEBUG32) $(INC_DEBUG32) -c injection.c -o $(OBJDIR_DEBUG32)/injection.o

$(OBJDIR_DEBUG32)/main.o: main.c
	$(CC) $(CFLAGS_DEBUG32) $(INC_DEBUG32) -c main.c -o $(OBJDIR_DEBUG32)/main.o

$(OBJDIR_DEBUG32)/offset_finder.o: offset_finder.c
	$(CC) $(CFLAGS_DEBUG32) $(INC_DEBUG32) -c offset_finder.c -o $(OBJDIR_DEBUG32)/offset_finder.o

clean_debug32: 
	rm -f $(OBJ_DEBUG32) $(OUT_DEBUG32)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG32)

before_release32: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE32) || mkdir -p $(OBJDIR_RELEASE32)

after_release32: 

release32: before_release32 out_release32 after_release32

out_release32: before_release32 $(OBJ_RELEASE32) $(DEP_RELEASE32)
	$(LD) $(LIBDIR_RELEASE32) -o $(OUT_RELEASE32) $(OBJ_RELEASE32)  $(LDFLAGS_RELEASE32) $(LIB_RELEASE32)

$(OBJDIR_RELEASE32)/artiglio.o: artiglio.c
	$(CC) $(CFLAGS_RELEASE32) $(INC_RELEASE32) -c artiglio.c -o $(OBJDIR_RELEASE32)/artiglio.o

$(OBJDIR_RELEASE32)/business.o: business.c
	$(CC) $(CFLAGS_RELEASE32) $(INC_RELEASE32) -c business.c -o $(OBJDIR_RELEASE32)/business.o

$(OBJDIR_RELEASE32)/cmdline.o: cmdline.c
	$(CC) $(CFLAGS_RELEASE32) $(INC_RELEASE32) -c cmdline.c -o $(OBJDIR_RELEASE32)/cmdline.o

$(OBJDIR_RELEASE32)/func_finder.o: func_finder.c
	$(CC) $(CFLAGS_RELEASE32) $(INC_RELEASE32) -c func_finder.c -o $(OBJDIR_RELEASE32)/func_finder.o

$(OBJDIR_RELEASE32)/injection.o: injection.c
	$(CC) $(CFLAGS_RELEASE32) $(INC_RELEASE32) -c injection.c -o $(OBJDIR_RELEASE32)/injection.o

$(OBJDIR_RELEASE32)/main.o: main.c
	$(CC) $(CFLAGS_RELEASE32) $(INC_RELEASE32) -c main.c -o $(OBJDIR_RELEASE32)/main.o

$(OBJDIR_RELEASE32)/offset_finder.o: offset_finder.c
	$(CC) $(CFLAGS_RELEASE32) $(INC_RELEASE32) -c offset_finder.c -o $(OBJDIR_RELEASE32)/offset_finder.o

clean_release32: 
	rm -f $(OBJ_RELEASE32) $(OUT_RELEASE32)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE32)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release before_debug32 after_debug32 clean_debug32 before_release32 after_release32 clean_release32

