INCLUDEPATH += $${PWD}

macx {
  CBFBASE = $${PWD}/CBFlib-$${QCEPLIB_CBF_VERSION}/src/
  CBFINCL = $${PWD}/CBFlib-$${QCEPLIB_CBF_VERSION}/include/

  DEFINES += CBF_NO_REGEX
} else:win32 {
  CBFBASE = $${PWD}/CBFlib-$${QCEPLIB_CBF_VERSION}/src/
  CBFINCL = $${PWD}/CBFlib-$${QCEPLIB_CBF_VERSION}/include/

  DEFINES += CBF_NO_REGEX
#  DEFINES += CBF_USE_ULP
} else:unix {
  INCLUDEPATH += /usr/include/cbf/
  LIBS += -lcbf
}

macx|win32 {
  INCLUDEPATH += $${CBFINCL}
}

