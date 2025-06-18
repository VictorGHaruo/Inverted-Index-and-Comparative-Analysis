QT += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = plot
TEMPLATE = app

SOURCES += \
    plot.cpp \
    qcustomplot.cpp

HEADERS += \
    qcustomplot.h

QMAKE_LFLAGS += -Wl,-rpath,/lib/x86_64-linux-gnu

QMAKE_CXXFLAGS += -O2 -Wall

