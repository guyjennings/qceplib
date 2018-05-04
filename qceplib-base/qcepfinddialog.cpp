#include "qcepfinddialog.h"
#include "ui_qcepfinddialog.h"
#include "qcepapplication.h"
#include "qcepmainwindow.h"

QcepFindDialog::QcepFindDialog(QcepMainWindow *parent, QTextEdit *te) :
  QDialog(parent),
  m_MainWindow(parent),
  m_TextEdit(te),
  m_LineEdit(nullptr)
{
  initialize();
}

QcepFindDialog::QcepFindDialog(QcepMainWindow *parent, QLineEdit *le) :
  QDialog(parent),
  m_MainWindow(parent),
  m_TextEdit(nullptr),
  m_LineEdit(le)
{
  initialize();
}

void QcepFindDialog::initialize()
{
  setupUi(this);

  g_Application -> prop_FindString() -> linkTo(m_FindString);

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
  if (m_TextEdit) {
    m_MainWindow -> doFindNextTextEdit(m_TextEdit);
  } else if (m_LineEdit) {
    m_MainWindow -> doFindNextLineEdit(m_LineEdit);
  }
}

void QcepFindDialog::doFindNext()
{
  if (m_TextEdit) {
    m_MainWindow -> doFindNextTextEdit(m_TextEdit);
  } else if (m_LineEdit) {
    m_MainWindow -> doFindNextLineEdit(m_LineEdit);
  }
}

void QcepFindDialog::doFindPrevious()
{
  if (m_TextEdit) {
    m_MainWindow -> doFindPreviousTextEdit(m_TextEdit);
  } else if (m_LineEdit) {
    m_MainWindow -> doFindPreviousLineEdit(m_LineEdit);
  }
}

void QcepFindDialog::doCancel()
{
  reject();
}
