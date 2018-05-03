#ifndef QCEPFINDDIALOG_H
#define QCEPFINDDIALOG_H

#include <QDialog>
#include "ui_qcepfinddialog.h"

class QcepFindDialog : public QDialog, public Ui::QcepFindDialog
{
  Q_OBJECT

public:
  explicit QcepFindDialog(QWidget *parent = 0);
  ~QcepFindDialog();

private:
};

#endif // QCEPFINDDIALOG_H
