QT       += core gui sql core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainproject.cpp \
    messagelable.cpp \
    mypushbutton.cpp \
    mywidgetbk.cpp \
    qwidgettitle.cpp \
    registerscreen.cpp \
    usernamectrl.cpp

HEADERS += \
    mainproject.h \
    messagelable.h \
    mypushbutton.h \
    mywidgetbk.h \
    qwidgettitle.h \
    registerscreen.h \
    usernamectrl.h

FORMS += \
    mainproject.ui \
    qwidgettitle.ui \
    registerscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
