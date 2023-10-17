QT += gui
QT += widgets
QT += quick
QT += quickcontrols2

TEMPLATE = lib
DEFINES += PLUGIN1508PL8T_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# надо вынести функционал бэкенда  в библиотеку (device, register, field)
SOURCES += \
    lfmtab.cpp \
    plugin1508pl8t.cpp \
    sinetab.cpp \
    writefieldstructure.cpp

HEADERS += \
    lfmtab.h \
    plugin1508pl8t.h\
    ..\..\USPI\Sources\Src\Extensions\ControlPanelInterface.h \
    sinetab.h \
    writefieldstructure.h

INCLUDEPATH += ..\..\USPI\Sources\Src\Extensions\

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
