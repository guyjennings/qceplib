#ifndef QCEPDATASETBROWSERDIALOG_H
#define QCEPDATASETBROWSERDIALOG_H

#include <QDockWidget>
#include "ui_qcepdatasetbrowserdialog.h"
#include "qcepdatasetmodel-ptr.h"
#include "qcepexperiment-ptr.h"

class QcepDatasetBrowserDialog : public QDockWidget, public Ui::QcepDatasetBrowserDialog
{
  Q_OBJECT

public:
  explicit QcepDatasetBrowserDialog(QcepExperimentWPtr expt, QcepDatasetModelWPtr ds, QWidget *parent = 0);
  virtual ~QcepDatasetBrowserDialog();

private:
  QcepExperimentWPtr  m_Experiment;
  QcepDatasetModelWPtr m_DatasetModel;
};

#endif // QCEPDATASETBROWSERDIALOG_H
