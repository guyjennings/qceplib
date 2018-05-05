linux-g++:QMAKE_TARGET.arch = $$QMAKE_HOST.arch
linux-g++-32:QMAKE_TARGET.arch = x86
linux-g++-64:QMAKE_TARGET.arch = x86_64
macx-*-32:QMAKE_TARGET.arch = x86

SZIPBASE = $${PWD}/szip-$${QCEPLIB_SZIP_VERSION}/src/

macx {
  SZIPCONF = $${PWD}/szip-config-$${QCEPLIB_SZIP_VERSION}/macx/
} else:unix {
  contains(QMAKE_TARGET.arch, x86_64) {
    SZIPCONF = $${PWD}/szip-config-$${QCEPLIB_SZIP_VERSION}/lin64/
  } else {
    SZIPCONF = $${PWD}/szip-config-$${QCEPLIB_SZIP_VERSION}/lin32/
  }
} else:win32 {
  contains(QMAKE_TARGET.arch, x86_64) {
    SZIPCONF = $${PWD}/szip-config-$${QCEPLIB_SZIP_VERSION}/win64/
  } else {
    SZIPCONF = $${PWD}/szip-config-$${QCEPLIB_SZIP_VERSION}/win32/
  }
}

INCLUDEPATH += $${SZIPCONF} $${SZIPBASE}
