TEMPLATE = app

TARGET = CQGLFlag

DEPENDPATH += .

MOC_DIR = .moc

QT += widgets opengl

QMAKE_CXXFLAGS += -std=c++14

#CONFIG += debug

SOURCES += \
CQGLFlag.cpp \
CFlag.cpp \

HEADERS += \
CQGLFlag.h \
CFlag.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
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
-lCQUtil -lCConfig -lCArgs -lCUtil -lCImageLib \
-lCRGBName -lCFont -lCFile -lCFileUtil -lCMath -lCOS -lCStrUtil -lCRegExp \
-lpng -ljpeg -ltre 
