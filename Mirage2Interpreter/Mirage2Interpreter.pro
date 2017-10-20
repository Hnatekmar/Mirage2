TEMPLATE = app
QT += core
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Mirage2StdLib/release/ -lMirage2StdLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Mirage2StdLib/debug/ -lMirage2StdLib
else:unix: LIBS += -L$$OUT_PWD/../Mirage2StdLib/ -lMirage2StdLib

INCLUDEPATH += $$PWD/../Mirage2StdLib
DEPENDPATH += $$PWD/../Mirage2StdLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Mirage2StdLib/release/libMirage2StdLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Mirage2StdLib/debug/libMirage2StdLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Mirage2StdLib/release/Mirage2StdLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Mirage2StdLib/debug/Mirage2StdLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Mirage2StdLib/libMirage2StdLib.a
