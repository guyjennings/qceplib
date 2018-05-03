#include "qceptextbrowser.h"
#include <QMenu>
#include <QContextMenuEvent>
#include "qcepmainwindow.h"

QcepTextBrowser::QcepTextBrowser(QWidget *parent)
  : inherited(parent)
{
}

void QcepTextBrowser::contextMenuEvent(QContextMenuEvent *e)
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

