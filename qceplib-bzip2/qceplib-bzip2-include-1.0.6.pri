linux-g++:QMAKE_TARGET.arch = $$QMAKE_HOST.arch
linux-g++-32:QMAKE_TARGET.arch = x86
linux-g++-64:QMAKE_TARGET.arch = x86_64
macx-*-32:QMAKE_TARGET.arch = x86


macx|win32 {
  BZIP2BASE = $${PWD}/bzip2-$${QCEPLIB_BZIP2_VERSION}/
  INCLUDEPATH += $${BZIP2BASE}
} else:unix {
  LIBS += -lbz2
}

INCLUDEPATH += $${PWD}
