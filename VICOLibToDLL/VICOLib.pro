QT -= gui
QT += core network
QT += testlib
QT += widgets

TARGET = VICOLib
TEMPLATE = lib
DEFINES += VICOLIB_LIBRARY

VERSION = 1.1.0.0

CONFIG += c11

# 配置动态库生成
CONFIG += dll

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += VERSION=\"\\\"$${VERSION}\\\"\"

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    impl/vicolib.cpp \
    impl/vicoquery.cpp

HEADERS += \
    impl/constants.h \
    impl/types.h \
    impl/vicolib.h \
    impl/vicolibglobal.h \
    impl/vicoquery.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}

test {
message(Test build)
    TEMPLATE = app
    QT += widgets testlib
    TARGET = vicolib-test

    HEADERS +=

    SOURCES += \
    test/maintest.cpp
} else {
    message(Normal build)
}

testDPP {
message(Test build)
    TEMPLATE = app
    QT += widgets testlib
    TARGET = vicolib-testDPP

    HEADERS += \
    test/dpptest.h

    SOURCES += \
    test/dpptest.cpp \
    test/dpptestmain.cpp
} else {
    message(Normal build)
}

testMCU {
message(Test build)
    TEMPLATE = app
    QT += widgets testlib
    TARGET = vicolib-testMCU

    HEADERS += \
    test/mcutest.h
    SOURCES += \
    test/mcutest.cpp \
    test/mcutestmain.cpp
} else {
    message(Normal build)
}

testMCUUpdate {
message(Test build)
    TEMPLATE = app
    QT += widgets testlib
    TARGET = vicolib-testMCUUpdate

    HEADERS += \
    test/mcuupdatetest.h
    SOURCES += \
    test/mcuupdatetest.cpp \
    test/mcuupdatetestmain.cpp
} else {
    message(Normal build)
}

testDPPUpdate {
message(Test build)
    TEMPLATE = app
    QT += widgets testlib
    TARGET = vicolib-testDPPUpdate

    HEADERS += \
    test/dppupdatetest.h
    SOURCES += \
    test/dppupdatetest.cpp \
    test/dppupdatetestmain.cpp
} else {
    message(Normal build)
}

!isEmpty(target.path): INSTALLS += target
