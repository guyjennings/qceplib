#ifndef QCEPNEWCOLUMNSCANDIALOG_H
#define QCEPNEWCOLUMNSCANDIALOG_H

#include <QDialog>
#include "ui_qcepnewcolumnscandialog.h"

#include "qcepdatasetmodel-ptr.h"

class QcepNewColumnScanDialog : public QDialog, public Ui::QcepNewColumnScanDialog
{
  Q_OBJECT

public:
  explicit QcepNewColumnScanDialog(QcepDatasetModelPtr model, const QModelIndex &idx);
  ~QcepNewColumnScanDialog();

  void accept();

private slots:
  void addColumn();
  void delColumn();

private:
  QcepDatasetModelPtr m_Model;
  QModelIndex         m_Index;
};

#endif // QCEPNEWCOLUMNSCANDIALOG_H
