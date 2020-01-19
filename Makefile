#############################################################################
# Makefile for building: libObject.so.1.0.0

# Template: lib

#############################################################################

MAKEFILE      = Makefile

EQ            = =

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DOBJECT_LIBRARY -DQT_DEPRECATED_WARNINGS
CFLAGS        = -pipe -O2 -Wall -W -fPIC $(DEFINES)
CXXFLAGS      = -pipe -O2 -std=gnu++11 -Wall -W -fPIC $(DEFINES)
INCPATH       =  -I. 
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = Object1.0.0
DISTDIR = .tmp/Object1.0.0
LINK          = g++
LFLAGS        = -Wl,-O1 -shared -Wl,-soname,libObject.so.1
LIBS          = $(SUBLIBS)    
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ./connect.cpp \
		./indexseq.cpp \
		./membermethod.cpp \
		./method.cpp \
		./methodinfo.cpp \
		./object.cpp \
		./property.cpp \
		./slotmethodwrap.cpp 
OBJECTS       = connect.o \
		indexseq.o \
		membermethod.o \
		method.o \
		methodinfo.o \
		object.o \
		property.o \
		slotmethodwrap.o



DESTDIR       = 
TARGET        = libObject.so.1.0.0
TARGETA       = libObject.a
TARGET0       = libObject.so
TARGETD       = libObject.so.1.0.0
TARGET1       = libObject.so.1
TARGET2       = libObject.so.1.0


first: all
####### Build rules

libObject.so.1.0.0:  $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	-$(DEL_FILE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	-ln -s $(TARGET) $(TARGET0)
	-ln -s $(TARGET) $(TARGET1)
	-ln -s $(TARGET) $(TARGET2)



staticlib: libObject.a

libObject.a:  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGETA) 
	$(AR) $(TARGETA) $(OBJECTS)

all: Makefile libObject.so.1.0.0

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/


clean: 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) $(TARGET0) $(TARGET1) $(TARGET2) $(TARGETA)
########-$(DEL_FILE) Makefile


####### Sub-libraries


####### Compile


####### Install

install_target: first FORCE
	@test -d $(INSTALL_ROOT)/usr/lib || mkdir -p $(INSTALL_ROOT)/usr/lib
	-$(QINSTALL_PROGRAM) $(TARGET) $(INSTALL_ROOT)/usr/lib/$(TARGET)
	-$(STRIP) --strip-unneeded $(INSTALL_ROOT)/usr/lib/$(TARGET)
	-$(SYMLINK) $(TARGET) $(INSTALL_ROOT)/usr/lib/$(TARGET0)
	-$(SYMLINK) $(TARGET) $(INSTALL_ROOT)/usr/lib/$(TARGET1)
	-$(SYMLINK) $(TARGET) $(INSTALL_ROOT)/usr/lib/$(TARGET2)

uninstall_target: FORCE
	-$(DEL_FILE) $(INSTALL_ROOT)/usr/lib/$(TARGET) 
	 -$(DEL_FILE) $(INSTALL_ROOT)/usr/lib/$(TARGET0) 
	 -$(DEL_FILE) $(INSTALL_ROOT)/usr/lib/$(TARGET1) 
	 -$(DEL_FILE) $(INSTALL_ROOT)/usr/lib/$(TARGET2)
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/lib/ 


install: install_target  FORCE

uninstall: uninstall_target  FORCE

FORCE:

