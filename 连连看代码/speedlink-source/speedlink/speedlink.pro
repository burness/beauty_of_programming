QT += gui
HEADERS += \
    drawarea.h \
    gamewindow.h \
    public-header.h \
    mybutton.h \
    toplist.h
LIBS += -lwinmm
SOURCES += \
    drawarea.cpp \
    main.cpp \
    gamewindow.cpp \
    mybutton.cpp

RESOURCES += \
    resources.qrc \
    resources.qrc

FORMS += \
    gamewindow.ui

RC_FILE =speedlink.rc
