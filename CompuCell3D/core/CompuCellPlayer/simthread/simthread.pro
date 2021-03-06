compucellnew_source_path=../..
install_path=/home/mswat/programs/CompuCellFullPython_install
xercesc_lib_dir=/home/mswat/programs/CompuCellFullPython/extralibs/xercesc/lib
xercesc_include_dir=/home/mswat/programs/CompuCellFullPython/extralibs/xercesc/include
# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./src
# Target is an application:  ../bin/CompuCellPlayer

  
INCLUDEPATH =  ../src \
	      /usr/include/python \
              $${compucellnew_source_path}/CompuCellNew/src/PublicUtilities \
              $${compucellnew_source_path}/CompuCellNew/debug \
              $${compucellnew_source_path}/CompuCellNew/ \
              $${compucellnew_source_path}/CompuCellNew/src \
              $${compucellnew_source_path}/CompuCellNew/src/include \
              $${compucellnew_source_path}/CompuCellNew/src/CompuCell3D \
              $${xercesc_include_dir}

QMAKE_LIBDIR = $${install_path}/lib \
	       $${compucellnew_source_path}/CompuCellNew/lib \
               $${xercesc_lib_dir}

LIBS += -lpython2.4 -lutil

TARGET = $${install_path}/lib/simthread
CONFIG += release \
          warn_on \
          thread \
          exceptions \
	  create_libtool \
	  create_prl	  
	
TEMPLATE = lib 

HEADERS += mainCC3D.h  PyScriptRunner.h GraphicsDataFields.h simthreadAccessor.h SimthreadBase.h
SOURCES += mainCC3D.cpp PyScriptRunner.cpp GraphicsDataFields.cpp simthreadAccessor.cpp SimthreadBase.cpp


