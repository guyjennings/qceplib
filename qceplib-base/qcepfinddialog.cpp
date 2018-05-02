#include "qcepfinddialog.h"
#include "ui_qcepfinddialog.h"

QcepFindDialog::QcepFindDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QcepFindDialog)
{
  ui->setupUi(this);
}

QcepFindDialog::~QcepFindDialog()
{
  delete ui;
}
