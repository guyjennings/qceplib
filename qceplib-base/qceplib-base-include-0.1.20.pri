greaterThan(QT_MAJOR_VERSION,4) {
  QT += widgets concurrent
}

CONFIG += qt

QT += script

INCLUDEPATH += $${PWD}
DEPENDPATH  += $${PWD}
