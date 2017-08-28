#ifndef QCEPNEWDATACOLUMNDIALOG_H
#define QCEPNEWDATACOLUMNDIALOG_H

#include "qceplib_global.h"
#include <QDialog>
#include "ui_qcepnewdatacolumndialog.h"

#include "qcepdatasetmodel-ptr.h"

class QCEP_EXPORT QcepNewDataColumnDialog : public QDialog, public Ui::QcepNewDataColumnDialog
{
  Q_OBJECT

public:
  explicit QcepNewDataColumnDialog(QcepDatasetModelPtr model, const QModelIndex &idx);
  ~QcepNewDataColumnDialog();

  void accept();

private:
  QcepDatasetModelPtr m_Model;
  QModelIndex         m_Index;
};

#endif // QCEPNEWDATACOLUMNDIALOG_H
