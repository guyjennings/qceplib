#include "qcepeventfilterlineedit.h"
#include <QEvent>
#include <QLineEdit>
#include <QContextMenuEvent>
#include <QMenu>
#include "qcepmainwindow.h"

QcepEventFilterLineEdit::QcepEventFilterLineEdit(QObject *parent,
                                                 QcepMainWindow *win)
  : inherited(parent, win)
{
}

bool QcepEventFilterLineEdit::eventFilter(QObject *watched, QEvent *event)
{
  QLineEdit *lned = qobject_cast<QLineEdit*>(watched);

  if (lned && event -> type() == QEvent::ContextMenu) {
    QContextMenuEvent *ctxev = static_cast<QContextMenuEvent*>(event);

    QMenu* menu = lned->createStandardContextMenu();

    m_MainWindow -> lineEditContextMenu(lned, menu);

    menu->exec(ctxev->globalPos());

    delete menu;

    return true;
  }

  return false;
}
