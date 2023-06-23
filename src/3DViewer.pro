QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./model/common/s21_create_matrix.c \
    ./model/common/s21_remove_matrix.c \
    ./model/s21_parser.c \
    ./model/s21_transform.c \
    ./controller/controller.cc \
    ./view/app/glwidget.cc \
    ./main.cc \
    ./view/app/mainwindow.cc

HEADERS += \
    ./model/common/s21_matrix.h \
    ./model/s21_3DViewer_v1.h \
    ./controller/controller.h \
    ./view/app/glwidget.h \
    ./view/app/mainwindow.h

FORMS += \
    ./view/app/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(./lib/QtGifImage/src/gifimage/qtgifimage.pri)