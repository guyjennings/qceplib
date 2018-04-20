message(qceplib-bzip2-include PWD = $${PWD} QCEPLIB_BZIP2_VERSION = $${QCEPLIB_BZIP2_VERSION})

linux-g++:QMAKE_TARGET.arch = $$QMAKE_HOST.arch
linux-g++-32:QMAKE_TARGET.arch = x86
linux-g++-64:QMAKE_TARGET.arch = x86_64
macx-*-32:QMAKE_TARGET.arch = x86

BZIP2BASE = $${PWD}/bzip2-$${QCEPLIB_BZIP2_VERSION}/

macx {
} else:unix {
} else:win32 {
}

INCLUDEPATH += $${BZIP2BASE} $${PWD}

