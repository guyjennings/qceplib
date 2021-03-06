#ifndef QCEPFILEIMPORTERTIFF_H
#define QCEPFILEIMPORTERTIFF_H

#include "qcepfileimporter.h"

class QcepFileImporterTIFF : public QcepFileImporter
{
  Q_OBJECT

public:
  QcepFileImporterTIFF(QcepDatasetModelPtr model,
                       QModelIndexList &indexes,
                       QString path);
};

#endif // QCEPFILEIMPORTERTIFF_H
