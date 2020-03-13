QT += core gui svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = fotoboxapp
TEMPLATE = app

SOURCES += main.cpp \
            MainWindow.cpp \
            ClickableLabel.cpp \
            ImagePreview.cpp \
            third/QrCode.cpp

HEADERS += MainWindow.h \
            ClickableLabel.h \
            ImagePreview.h \
            third/QrCode.hpp
