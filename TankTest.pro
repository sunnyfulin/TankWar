#-------------------------------------------------
#
# Project created by QtCreator 2016-09-12T11:16:07
#
#-------------------------------------------------

QT       += core gui widgets multimedia

TARGET = TankTest
TEMPLATE = app

DESTDIR += bin
MOC_DIR += moc
OBJECTS_DIR += obj

RESOURCES += \
    images.qrc \
    sound.qrc

include(./src/src.pri)
