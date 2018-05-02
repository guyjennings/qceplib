#include "qcepeventfiltertextedit.h"
#include <QTextEdit>
#include <QEvent>
#include <QContextMenuEvent>
#include <QMenu>

QcepEventFilterTextEdit::QcepEventFilterTextEdit(QObject *parent, QcepMainWindow *win)
  : inherited(parent, win)
{
}

bool QcepEventFilterTextEdit::eventFilter(QObject *watched, QEvent *event)
{
  QTextEdit *txed = qobject_cast<QTextEdit*>(watched);

  if (txed && event -> type() == QEvent::ContextMenu) {
    QContextMenuEvent *ctxev = static_cast<QContextMenuEvent*>(event);

    QMenu* menu = txed -> createStandardContextMenu();

    menu->exec(ctxev->globalPos());

    delete menu;

    return true;
  }

  return false;
}
