QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminhelper.cpp \
    main.cpp \
    mainwindow.cpp \
    # ./VICOLib_impl/vicolib.cpp \
    # ./VICOLib_impl/vicoquery.cpp \
    vicolibrary.cpp


HEADERS += \
    adminhelper.h \
    mainwindow.h \
    # ./VICOLib_impl/constants.h \
    ./VICOLib_impl/types.h \
    ./VICOLib_impl/vicolib.h \
    # ./VICOLib_impl/vicolibglobal.h \
    # ./VICOLib_impl/vicoquery.h \
    structdef.h \
    vicolibrary.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
