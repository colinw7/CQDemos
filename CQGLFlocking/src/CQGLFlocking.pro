TEMPLATE = app

TARGET = CQGLFlocking

DEPENDPATH += .

MOC_DIR = .moc

QT += widgets opengl

QMAKE_CXXFLAGS += -std=c++14

#CONFIG += debug

SOURCES += \
CQGLFlocking.cpp \
CFlocking.cpp \
CFlock.cpp \
CBoid.cpp \
CProfile.cpp \
CQGLControl.cpp \
CGLTexture.cpp \
CGLUtil.cpp \

HEADERS += \
CQGLFlocking.h \
CFlocking.h \
CFlock.h \
CBoid.h \
CProfile.h \
CQGLControl.h \
CGLTexture.h \
CGLUtil.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
../../../CGeometry3D/include \
../../../CQUtil/include \
../../../CImageLib/include \
../../../CFont/include \
../../../CArgs/include \
../../../CFile/include \
../../../CMath/include \
../../../CStrUtil/include \
../../../CUtil/include \
../../../COS/include \

unix:LIBS += \
-L$$LIB_DIR \
-L../../../CGeometry3D/lib \
-L../../../CQUtil/lib \
-L../../../CUtil/lib \
-L../../../CConfig/lib \
-L../../../CArgs/lib \
-L../../../CImageLib/lib \
-L../../../CFont/lib \
-L../../../CMath/lib \
-L../../../CRGBName/lib \
-L../../../CFile/lib \
-L../../../CFileUtil/lib \
-L../../../CStrUtil/lib \
-L../../../COS/lib \
-L../../../CRegExp/lib \
-lCGeometry3D -lCQUtil -lCConfig -lCArgs -lCUtil -lCImageLib \
-lCRGBName -lCFont -lCFile -lCFileUtil -lCMath -lCOS -lCStrUtil -lCRegExp \
-lglut -lGLU -lGL -lpng -ljpeg -ltre 
