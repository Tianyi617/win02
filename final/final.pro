QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AIStyleManager.cpp \
    BorderManager.cpp \
    EditableTextItem.cpp \
    FilterWidget.cpp \
    ImageEditCommand.cpp \
    MyGraphicsView.cpp \
    TextManager.cpp \
    cropResizeWidget.cpp \
    imagestyleeditor.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AIStyleManager.h \
    BorderManager.h \
    EditableTextItem.h \
    FilterWidget.h \
    ImageEditCommand.h \
    MyGraphicsView.h \
    NonInteractivePixmapItem.h \
    TextManager.h \
    cropResizeWidget.h \
    imagestyleeditor.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
