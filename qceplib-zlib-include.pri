QCEPLIB_ZLIB_VERSION = "1.2.11"

DEFINES += QCEPLIB_ZLIB_VERSION=\"$${QCEPLIB_ZLIB_VERSION}\"

include(qceplib-zlib/qceplib-zlib-include-$${QCEPLIB_ZLIB_VERSION}.pri)
