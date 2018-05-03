#ifndef QCEPFINDDIALOG_H
#define QCEPFINDDIALOG_H

#include <QDialog>
#include "ui_qcepfinddialog.h"
#include "qcepmainwindow-ptr.h"

class QcepFindDialog : public QDialog, public Ui::QcepFindDialog
{
  Q_OBJECT

public:
  explicit QcepFindDialog(QcepMainWindow *parent);
  ~QcepFindDialog();

public slots:
  void doFind();
  void doFindNext();
  void doFindPrevious();
  void doCancel();

private:
  QcepMainWindow *m_MainWindow;
};

#endif // QCEPFINDDIALOG_H
