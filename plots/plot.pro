QT += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = plot
TEMPLATE = app

INCLUDEPATH += ../src

SOURCES += \
    plot.cpp \
    ../scr/avl.cpp \
    ../scr/bst.cpp \
    ../scr/data.cpp \
    ../scr/tree_utils.cpp \
    "../scr/rbt.cpp" \
    qcustomplot.cpp

HEADERS += \
    ../scr/avl.h \
    ../scr/bst.h \
    ../scr/data.h \
    ../scr/tree_utils.h \
    "../scr/rbt.h" \
    qcustomplot.h
