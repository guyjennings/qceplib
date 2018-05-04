#ifndef QCEPFINDDIALOG_H
#define QCEPFINDDIALOG_H

#include <QDialog>
#include "ui_qcepfinddialog.h"
#include "qcepmainwindow-ptr.h"
#include <QTextEdit>

class QcepFindDialog : public QDialog, public Ui::QcepFindDialog
{
  Q_OBJECT

public:
  explicit QcepFindDialog(QcepMainWindow *parent, QTextEdit *te);
  explicit QcepFindDialog(QcepMainWindow *parent, QLineEdit *le);
  ~QcepFindDialog();
  void initialize();

public slots:
  void doFind();
  void doFindNext();
  void doFindPrevious();
  void doCancel();

private:
  QcepMainWindow *m_MainWindow;
  QTextEdit      *m_TextEdit;
  QLineEdit      *m_LineEdit;
};

#endif // QCEPFINDDIALOG_H
