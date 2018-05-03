#include "qcepfinddialog.h"
#include "ui_qcepfinddialog.h"
#include "qcepapplication.h"
#include "qcepmainwindow.h"

QcepFindDialog::QcepFindDialog(QWidget *parent) :
  QDialog(parent)
{
  setupUi(this);

  g_Application -> prop_FindString() -> linkTo(m_FindString);

  QcepMainWindow* mainWin = qobject_cast<QcepMainWindow*>(parent);

  if (mainWin) {
    connect(m_FindButton, &QPushButton::clicked,
            mainWin,      &QcepMainWindow::doFind);

    connect(m_FindNextButton, &QPushButton::clicked,
            mainWin,          &QcepMainWindow::doFindNext);

    connect(m_FindPreviousButton, &QPushButton::clicked,
            mainWin,              &QcepMainWindow::doFindPrevious);
  }
}

QcepFindDialog::~QcepFindDialog()
{
}
