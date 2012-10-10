#############################################################################
# Makefile for building: MD2Viewer
# Generated by qmake (2.01a) (Qt 4.8.1) on: Tue Oct 9 19:49:27 2012
# Project:  assignment2.pro
# Template: app
# Command: /opt/QtSDK/Desktop/Qt/4.8.1/gcc/bin/qmake -o Makefile assignment2.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/default -I. -I/opt/QtSDK/Desktop/Qt/4.8.1/gcc/include/QtCore -I/opt/QtSDK/Desktop/Qt/4.8.1/gcc/include/QtGui -I/opt/QtSDK/Desktop/Qt/4.8.1/gcc/include/QtOpenGL -I/opt/QtSDK/Desktop/Qt/4.8.1/gcc/include -I. -I/usr/X11R6/include -I.moc -I.ui
LINK          = g++
LFLAGS        = -m64 -Wl,-O1 -Wl,-rpath,/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib
LIBS          = $(SUBLIBS)  -L/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib -L/usr/X11R6/lib64 -lGLU -lglut -lQtOpenGL -L/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib -L/usr/X11R6/lib64 -lQtGui -lQtCore -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /opt/QtSDK/Desktop/Qt/4.8.1/gcc/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = .obj/

####### Files

SOURCES       = src/GLWidget.cpp \
		src/main.cpp \
		src/Window.cpp .moc/moc_GLWidget.cpp \
		.moc/moc_Window.cpp
OBJECTS       = .obj/GLWidget.o \
		.obj/main.o \
		.obj/Window.o \
		.obj/moc_GLWidget.o \
		.obj/moc_Window.o
DIST          = /opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/linux.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/release.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/gdb_dwarf_index.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/opengl.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf \
		assignment2.pro
QMAKE_TARGET  = MD2Viewer
DESTDIR       = 
TARGET        = MD2Viewer

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): .ui/ui_SideBar.h .ui/ui_MainWindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: assignment2.pro  /opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/default/qmake.conf /opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/linux.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/release.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/gdb_dwarf_index.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/opengl.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtOpenGL.prl \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtGui.prl \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtCore.prl
	$(QMAKE) -o Makefile assignment2.pro
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/linux.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-unix.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-unix.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/release.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/gdb_dwarf_index.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/opengl.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtOpenGL.prl:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtGui.prl:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile assignment2.pro

dist: 
	@$(CHK_DIR_EXISTS) .obj/MD2Viewer1.0.0 || $(MKDIR) .obj/MD2Viewer1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .obj/MD2Viewer1.0.0/ && $(COPY_FILE) --parents src/GLWidget.h src/Window.h .obj/MD2Viewer1.0.0/ && $(COPY_FILE) --parents src/GLWidget.cpp src/main.cpp src/Window.cpp .obj/MD2Viewer1.0.0/ && $(COPY_FILE) --parents src/SideBar.ui src/MainWindow.ui .obj/MD2Viewer1.0.0/ && (cd `dirname .obj/MD2Viewer1.0.0` && $(TAR) MD2Viewer1.0.0.tar MD2Viewer1.0.0 && $(COMPRESS) MD2Viewer1.0.0.tar) && $(MOVE) `dirname .obj/MD2Viewer1.0.0`/MD2Viewer1.0.0.tar.gz . && $(DEL_FILE) -r .obj/MD2Viewer1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: .moc/moc_GLWidget.cpp .moc/moc_Window.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) .moc/moc_GLWidget.cpp .moc/moc_Window.cpp
.moc/moc_GLWidget.cpp: src/GLWidget.h
	/opt/QtSDK/Desktop/Qt/4.8.1/gcc/bin/moc $(DEFINES) $(INCPATH) src/GLWidget.h -o .moc/moc_GLWidget.cpp

.moc/moc_Window.cpp: src/GLWidget.h \
		.ui/ui_MainWindow.h \
		.ui/ui_SideBar.h \
		src/Window.h
	/opt/QtSDK/Desktop/Qt/4.8.1/gcc/bin/moc $(DEFINES) $(INCPATH) src/Window.h -o .moc/moc_Window.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: .ui/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) .ui/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: .ui/ui_SideBar.h .ui/ui_MainWindow.h
compiler_uic_clean:
	-$(DEL_FILE) .ui/ui_SideBar.h .ui/ui_MainWindow.h
.ui/ui_SideBar.h: src/SideBar.ui
	/opt/QtSDK/Desktop/Qt/4.8.1/gcc/bin/uic src/SideBar.ui -o .ui/ui_SideBar.h

.ui/ui_MainWindow.h: src/MainWindow.ui
	/opt/QtSDK/Desktop/Qt/4.8.1/gcc/bin/uic src/MainWindow.ui -o .ui/ui_MainWindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

.obj/GLWidget.o: src/GLWidget.cpp src/GLWidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/GLWidget.o src/GLWidget.cpp

.obj/main.o: src/main.cpp src/GLWidget.h \
		src/Window.h \
		.ui/ui_MainWindow.h \
		.ui/ui_SideBar.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/main.o src/main.cpp

.obj/Window.o: src/Window.cpp src/Window.h \
		src/GLWidget.h \
		.ui/ui_MainWindow.h \
		.ui/ui_SideBar.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/Window.o src/Window.cpp

.obj/moc_GLWidget.o: .moc/moc_GLWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_GLWidget.o .moc/moc_GLWidget.cpp

.obj/moc_Window.o: .moc/moc_Window.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_Window.o .moc/moc_Window.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

