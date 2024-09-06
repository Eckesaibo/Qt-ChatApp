QT += core gui widgets network sql multimedia

TARGET = ChatApp
TEMPLATE = app

SOURCES += \
    ClientHandlerThread.cpp \
    SocketThread.cpp \
    chatwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    server.cpp

HEADERS += \
    ClientHandlerThread.h \
    SocketThread.h \
    chatwindow.h \
    loginwindow.h \
    server.h \
    server.h

FORMS += \
    chatwindow.ui \
    loginwindow.ui

DISTFILES +=

RESOURCES += \
    char.qrc

