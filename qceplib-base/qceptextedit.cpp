#include "qceptextedit.h"
#include <QMenu>
#include <QContextMenuEvent>
#include "qcepmainwindow.h"

QcepTextEdit::QcepTextEdit(QWidget *parent)
  : inherited(parent)
{

}

QcepTextEdit::~QcepTextEdit()
{
}

void QcepTextEdit::contextMenuEvent(QContextMenuEvent *e)
{
  QcepMainWindow *mainWin = qobject_cast<QcepMainWindow*>(window());

  QMenu* menu = createStandardContextMenu();

  if (mainWin) {
    menu -> addSeparator();

    menu -> addAction(mainWin -> m_ActionFind);
    menu -> addAction(mainWin -> m_ActionFindSelected);
    menu -> addAction(mainWin -> m_ActionFindNext);
    menu -> addAction(mainWin -> m_ActionFindPrevious);
  }

  menu -> exec(e->globalPos());

  delete menu;
}
