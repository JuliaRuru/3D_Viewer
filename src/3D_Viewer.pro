QT       += core gui opengl widgets openglwidgets
include(misc/QtGifImage/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += -lopengl32

SOURCES += \
    engine.cpp \
    main.cpp \
    mainwindow.cpp \
    rendering_calculations.c \
    viewerwidget.cpp

HEADERS += \
    engine.h \
    mainwindow.h \
    rendering_calculations.h \
    viewerwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ICON += \
    ./misc/viewer.icns

DISTFILES += \
    misc/QtGifImage/src/gifimage/qtgifimage.pri

RESOURCES += \
    shaders.qrc
