QCEPLIB_LIBZIP_VERSION = "1.5.1"

DEFINES += QCEPLIB_LIBZIP_VERSION=\"$${QCEPLIB_LIBZIP_VERSION}\"

include(qceplib-libzip/qceplib-libzip-include-$${QCEPLIB_LIBZIP_VERSION}.pri)