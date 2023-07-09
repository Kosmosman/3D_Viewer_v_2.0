QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./model/affine_transformations/affinis.cc \
    ./model/basic_model/model.cc \
    ./model/parcer/parcer.cc \
    ./main.cc \
    ./view/app/glwidget.cc \
    ./view/app/mainwindow.cc

HEADERS += \
    ./controller/controller.h \
    ./model/affine_transformations/affinis.h \
    ./model/basic_model/model.h \
    ./model/parcer/parcer.h \
    ./view/app/glwidget.h \
    ./view/app/mainwindow.h

FORMS += \
    ./view/app/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(./lib/QtGifImage/src/gifimage/qtgifimage.pri)
