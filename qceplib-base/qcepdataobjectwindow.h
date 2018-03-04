#ifndef QCEPDATAOBJECTWINDOW_H
#define QCEPDATAOBJECTWINDOW_H

#include "qceplib_global.h"
#include "qcepmainwindow.h"

class QCEP_EXPORT QcepDataObjectWindow : public QcepMainWindow
{
  Q_OBJECT

private:
  typedef QcepMainWindow inherited;

public:
  explicit QcepDataObjectWindow(QString name);

  void saveExperiment();
  void saveExperimentAs();
  void saveExperimentCopy();
  void doEditPreferences();

signals:

public slots:
};

#endif // QCEPDATAOBJECTWINDOW_H
