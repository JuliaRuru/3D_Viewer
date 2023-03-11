QT += core gui opengl widgets openglwidgets
include(misc/QtGifImage/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += -lopengl32

SOURCES += \
    View/engine.cpp \
    main.cpp \
    View/mainwindow.cpp \
    Model/s21_viewer.cpp \
    View/viewerwidget.cpp \
    Controller/controller.cpp \
    Model/s21_matrix_oop.cpp

HEADERS += \
    View/engine.h \
    View/mainwindow.h \
    Model/s21_viewer.h \
    View/viewerwidget.h \
    Controller/controller.h \
    Model/s21_matrix_oop.h

FORMS += \
    View/UI/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ICON += \
    ./misc/viewer.icns

DISTFILES += \
    misc/QtGifImage/src/gifimage/qtgifimage.pri

RESOURCES += \
    View/shaders.qrc

CONFIG += sdk_no_version_check
CONFIG += c++17

