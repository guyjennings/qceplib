message(qceplib-libzip-include PWD = $${PWD} QCEPLIB_LIBZIP_VERSION = $${QCEPLIB_LIBZIP_VERSION})

linux-g++:QMAKE_TARGET.arch = $$QMAKE_HOST.arch
linux-g++-32:QMAKE_TARGET.arch = x86
linux-g++-64:QMAKE_TARGET.arch = x86_64
macx-*-32:QMAKE_TARGET.arch = x86

LIBZIPBASE = $${PWD}/libzip-$${QCEPLIB_LIBZIP_VERSION}/lib/

macx {
} else:unix {
  LIBS += -lzip
} else:win32 {
}

INCLUDEPATH += $${LIBZIPBASE} $${PWD}

