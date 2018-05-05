#message(qceplib-bzip2 PWD = $${PWD} QCEPLIB_BZIP2_VERSION = $${QCEPLIB_BZIP2_VERSION})

include(qceplib-bzip2-include-$${QCEPLIB_BZIP2_VERSION}.pri)

macx|win32 {
  HEADERS += \
    $$BZIP2BASE/bzlib.h \
    $$BZIP2BASE/bzlib_private.h

  SOURCES += \
    $$BZIP2BASE/bzip2blocksort.c \
    $$BZIP2BASE/bzlib.c \
    $$BZIP2BASE/bzip2compress.c \
    $$BZIP2BASE/bzip2crctable.c \
    $$BZIP2BASE/bzip2decompress.c \
    $$BZIP2BASE/bzip2huffman.c \
    $$BZIP2BASE/bzip2randtable.c
}

HEADERS += \
  $$PWD/qcepbzlib.h

SOURCES += \
  $$PWD/qcepbzlib.cpp
