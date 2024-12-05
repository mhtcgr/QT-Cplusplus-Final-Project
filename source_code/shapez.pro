QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += resources_big
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    belt.cpp \
    card.cpp \
    cardscene.cpp \
    centre.cpp \
    cutter.cpp \
    device.cpp \
    grid.cpp \
    main.cpp \
    mainscene.cpp \
    mine.cpp \
    miner.cpp \
    myscene.cpp \
    playscene.cpp \
    retbutton.cpp \
    rotater.cpp \
    savebutton.cpp \
    shop.cpp \
    trashcan.cpp \
    upgradedialog.cpp

HEADERS += \
    Init.h \
    belt.h \
    card.h \
    cardscene.h \
    centre.h \
    cutter.h \
    device.h \
    grid.h \
    mainscene.h \
    mine.h \
    miner.h \
    myscene.h \
    playscene.h \
    retbutton.h \
    rotater.h \
    savebutton.h \
    shop.h \
    trashcan.h \
    upgradedialog.h

FORMS += \
    mainscene.ui \
    playscene.ui \
    shop.ui \
    upgradedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../image/grid.png \
    ../image/折れ線グラフ.png \
    Image/black.jpg

RESOURCES += \
    ../last/last.qrc \
    ../res/realPic.qrc \
    ../res/ui/building_icons/bc.qrc \
    ../res/ui/building_icons/res.qrc
