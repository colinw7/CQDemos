TEMPLATE = app

TARGET = CQFireworks

DEPENDPATH += .

MOC_DIR = .moc

QT += widgets

QMAKE_CXXFLAGS += -std=c++14

#CONFIG += debug

SOURCES += \
CQFireworks.cpp \
CFireworks.cpp \

HEADERS += \
CQFireworks.h \
CFireworks.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
../../../CQUtil/include \
../../../CConfig/include \
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
-lBox2D -lpng -ljpeg -ltre 
