#ifndef QCEPDATAOBJECTSPREADSHEETWINDOW_H
#define QCEPDATAOBJECTSPREADSHEETWINDOW_H

#include "qceplib_global.h"
#include <QObject>
#include <QWidget>
#include "ui_qcepdataobjectspreadsheetwindow.h"
#include "qcepmainwindow.h"
#include "qcepexperiment-ptr.h"
#include "qcepdataobject-ptr.h"
#include "qcepspreadsheetmodel-ptr.h"

class QCEP_EXPORT QcepDataObjectSpreadsheetWindow : public QcepMainWindow, public Ui::QcepDataObjectSpreadsheetWindow
{
  Q_OBJECT

private:
  typedef QcepMainWindow inherited;

public:
  explicit QcepDataObjectSpreadsheetWindow(
      QString name,
      QcepExperimentWPtr expt,
      QcepDataObjectWPtr  obj);
  void initialize(QcepObjectWPtr parent);
  virtual ~QcepDataObjectSpreadsheetWindow();

  void closeEvent (QCloseEvent * event);
  bool wantToClose();

signals:

public slots:

private:
  QcepExperimentWPtr      m_Experiment;
  QcepDataObjectWPtr      m_Object;
  QcepSpreadsheetModelPtr m_Model;
};

#endif // QCEPDATAOBJECTSPREADSHEETWINDOW_H
