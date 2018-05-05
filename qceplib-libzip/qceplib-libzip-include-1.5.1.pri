linux-g++:QMAKE_TARGET.arch = $$QMAKE_HOST.arch
linux-g++-32:QMAKE_TARGET.arch = x86
linux-g++-64:QMAKE_TARGET.arch = x86_64
macx-*-32:QMAKE_TARGET.arch = x86


macx {
  LIBZIPBASE = $${PWD}/libzip-$${QCEPLIB_LIBZIP_VERSION}/lib/
  LIBZIPCONF = $${PWD}/libzip-config-$${QCEPLIB_LIBZIP_VERSION}/macx/
  INCLUDEPATH += $${LIBZIPBASE} $${LIBZIPCONF}
} else:unix {
  LIBS += -lzip
} else:win32 {
  LIBZIPBASE = $${PWD}/libzip-$${QCEPLIB_LIBZIP_VERSION}/lib/
  contains(QMAKE_TARGET.arch, x86_64) {
    LIBZIPCONF = $${PWD}/libzip-config-$${QCEPLIB_LIBZIP_VERSION}/win64/
  } else {
    LIBZIPCONF = $${PWD}/libzip-config-$${QCEPLIB_LIBZIP_VERSION}/win32/
  }
  INCLUDEPATH += $${LIBZIPBASE} $${LIBZIPCONF}
}


