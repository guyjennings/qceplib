#ifndef QCEPFINDDIALOG_H
#define QCEPFINDDIALOG_H

#include <QDialog>

namespace Ui {
class QcepFindDialog;
}

class QcepFindDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QcepFindDialog(QWidget *parent = 0);
  ~QcepFindDialog();

private:
  Ui::QcepFindDialog *ui;
};

#endif // QCEPFINDDIALOG_H
