QCEPLIB_HDF5_VERSION = "1.8.16"

DEFINES += QCEPLIB_HDF5_VERSION=\"$${QCEPLIB_HDF5_VERSION}\"

include(qceplib-hdf5/qceplib-hdf5-$${QCEPLIB_HDF5_VERSION}.pri)
