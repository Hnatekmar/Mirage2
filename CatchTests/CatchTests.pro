TEMPLATE = app
CONFIG += console c++14 core
CONFIG -= app_bundle
CONFIG += qt

PKGCONFIG += catch

SOURCES += main.cpp \
    linkedlist.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Mirage2Lib/release/ -lMirage2Lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Mirage2Lib/debug/ -lMirage2Lib
else:unix: LIBS += -L$$OUT_PWD/../Mirage2Lib/ -lMirage2Lib

INCLUDEPATH += $$PWD/../Mirage2Lib
DEPENDPATH += $$PWD/../Mirage2Lib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Mirage2Lib/release/libMirage2Lib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Mirage2Lib/debug/libMirage2Lib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Mirage2Lib/release/Mirage2Lib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Mirage2Lib/debug/Mirage2Lib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Mirage2Lib/libMirage2Lib.a
