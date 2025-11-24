QT += core gui widgets sql serialport positioning network mqtt multimedia multimediawidgets
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG += resources_big

TRANSLATIONS += Language_CN.ts\
                Language_EN.ts


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 定义输出目录
OBJECTS_DIR = $$OUT_PWD/obj
DESTDIR = $$PWD/output/$${QT_ARCH}_$${QT_BUILD_MODE}

# 源文件和头文件
SOURCES += \
    src/camera.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mytask.cpp

HEADERS += \
    include/mainwindow.h \
    include/mytask.h \
    include/camera.h

FORMS += \
    resources/mainwindow.ui

# 资源文件
RESOURCES += \
    resources/pic.qrc \
    resources/qss.qrc \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RC_ICONS = resources/turang.ico
INCLUDEPATH += $$PWD/include

#LIBS += D:\Postgraduate\QtDevelop\mqtt\build-qtmqtt-Desktop_Qt_5_14_1_MSVC2017_64bit-Release\lib\lib*.a
#LIBS += D:\Postgraduate\QtDevelop\mqtt\build-qtmqtt-Desktop_Qt_5_14_1_MSVC2017_64bit-Debug\lib\Qt*.dll
