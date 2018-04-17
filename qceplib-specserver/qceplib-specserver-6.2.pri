message(qceplib-specserver PWD = $${PWD} QCEPLIB_SPECSERVER_VERSION = $${QCEPLIB_SPECSERVER_VERSION})

include(qceplib-specserver-include-$${QCEPLIB_SPECSERVER_VERSION}.pri)

SOURCES += \
  $$PWD/qcepspecremote.cpp \
  $$PWD/qcepspecserver.cpp \
  $$PWD/qcepspecserversettings.cpp \
  $$PWD/qcepsimpleserver.cpp \
  $$PWD/qcepsimpleserversettings.cpp \
  $$PWD/qcepsimpleserverthread.cpp \
  $$PWD/qcepspecserverthread.cpp

HEADERS += \
  $$PWD/qcepspecserver.h \
  $$PWD/qcepspecserver-ptr.h \
  $$PWD/qcepspecserversettings.h \
  $$PWD/qcepspecserversettings-ptr.h \
  $$PWD/qcepspecserverthread.h \
  $$PWD/qcepspecserverthread-ptr.h \
  $$PWD/qcepspecremote.h \
  $$PWD/qcepspecremote-ptr.h \
  $$PWD/spec_server.h \
  $$PWD/qcepsimpleserver.h \
  $$PWD/qcepsimpleserver-ptr.h \
  $$PWD/qcepsimpleserversettings.h \
  $$PWD/qcepsimpleserversettings-ptr.h \
  $$PWD/qcepsimpleserverthread.h \
  $$PWD/qcepsimpleserverthread-ptr.h
