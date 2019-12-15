QT       += core gui

QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game.cpp \
    gamewindow.cpp \
    main.cpp \
    gobang.cpp \
    mygameset.cpp \
    mygamestatus.cpp \
    myspecgamestatus.cpp \
    pushchess.cpp \
    specgamestatus.cpp \
    aiinterface.cpp \
    aiandnetgame.cpp \
    chessclickedservice.cpp \
    networkservice.cpp \
    inputip.cpp \
    ai.cpp \
    haveforbidden.cpp \
    haveforbiddenwidget.cpp \
    nohands.cpp

HEADERS += \
    buttonStyleSheet.h \
    game.h \
    gameset.h \
    gamestatus.h \
    gamewindow.h \
    gobang.h \
    mygameset.h \
    mygamestatus.h \
    myspecgamestatus.h \
    pushchess.h \
    specgamestatus.h \
    aiinterface.h \
    aiandnetgame.h \
    chessclickedservice.h \
    networkservice.h \
    inputip.h \
    ai.h \
    haveforbidden.h \
    haveforbiddenwidget.h \
    nohands.h

FORMS += \
    gamewindow.ui \
    gobang.ui \
    aiandnetgame.ui \
    inputip.ui \
    haveforbiddenwidget.ui \
    inputport.ui \
    loadingwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc \

RC_ICONS = myico.ico
