DEFINES += QWT_DLL

greaterThan(QT_MAJOR_VERSION,4): QT += printsupport concurrent

QT += opengl svg

QWTBASE = $${PWD}/qwt-6.1.3/src

INCLUDEPATH += $${QWTBASE}
