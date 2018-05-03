#include "qcepfinddialog.h"
#include "ui_qcepfinddialog.h"
#include "qcepapplication.h"
#include "qcepmainwindow.h"

QcepFindDialog::QcepFindDialog(QcepMainWindow *parent) :
  QDialog(parent)
{
  setupUi(this);

  g_Application -> prop_FindString() -> linkTo(m_FindString);

  m_MainWindow = parent;

  if (m_MainWindow) {
    connect(m_FindButton,         &QPushButton::clicked,
            this,                 &QcepFindDialog::doFind);

    connect(m_FindNextButton,     &QPushButton::clicked,
            this,                 &QcepFindDialog::doFindNext);

    connect(m_FindPreviousButton, &QPushButton::clicked,
            this,                 &QcepFindDialog::doFindPrevious);

    connect(m_CancelButton,       &QPushButton::clicked,
            this,                 &QcepFindDialog::doCancel);
  }
}

QcepFindDialog::~QcepFindDialog()
{
}

void QcepFindDialog::doFind()
{
  m_MainWindow -> doFind();
}

void QcepFindDialog::doFindNext()
{
  m_MainWindow -> doFindNext();
}

void QcepFindDialog::doFindPrevious()
{
  m_MainWindow -> doFindPrevious();
}

void QcepFindDialog::doCancel()
{
  reject();
}
