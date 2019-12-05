QT += core gui widgets
DESTDIR = $$PWD/bin

TARGET = KeywordSearch
TEMPLATE = app

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    mydatabase.h \
    qbyuomap.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mydatabase.cpp \
    qbyuomap.cpp

