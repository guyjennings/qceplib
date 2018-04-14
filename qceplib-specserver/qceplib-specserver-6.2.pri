message(qceplib-specserver PWD = $${PWD} QCEPLIB_SPECSERVER_VERSION = $${QCEPLIB_SPECSERVER_VERSION})

include(qceplib-specserver-include-$${QCEPLIB_SPECSERVER_VERSION}.pri)

SOURCES += \
  $${PWD}/qcepspecserver.cpp \
  $${PWD}/qcepspecremote.cpp \
    $$PWD/qcepsimpleserver.cpp \
    $$PWD/qcepspecserversettings.cpp \
    $$PWD/qcepsimpleserversettings.cpp

HEADERS += \
  $${PWD}/qcepspecserver.h \
  $${PWD}/qcepspecremote.h \
  $${PWD}/spec_server.h \
    $$PWD/qcepsimpleserver.h \
    $$PWD/qcepsimpleserver-ptr.h \
    $$PWD/qcepspecremote-ptr.h \
    $$PWD/qcepspecserver-ptr.h \
    $$PWD/qcepspecserversettings.h \
    $$PWD/qcepspecserversettings-ptr.h \
    $$PWD/qcepsimpleserversettings.h \
    $$PWD/qcepsimpleserversettings-ptr.h
