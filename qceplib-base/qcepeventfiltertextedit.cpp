#include "qcepeventfiltertextedit.h"
#include <QTextEdit>
#include <QEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include "qcepmainwindow.h"

QcepEventFilterTextEdit::QcepEventFilterTextEdit(QObject *parent, QcepMainWindow *win)
  : inherited(parent, win)
{
}

bool QcepEventFilterTextEdit::eventFilter(QObject *watched, QEvent *event)
{
  QTextEdit *txed = qobject_cast<QTextEdit*>(watched);

  if (txed) {
    QList<QWidget*> widgets = txed->findChildren<QWidget*>();

    int nWidgets = widgets.count();

    auto evType = event -> type();

    if (evType == QEvent::ContextMenu) {
      QContextMenuEvent *ctxev = static_cast<QContextMenuEvent*>(event);

      QMenu* menu = txed -> createStandardContextMenu();

      m_MainWindow -> textEditContextMenu(txed, menu);

      menu->exec(ctxev->globalPos());

      delete menu;

      return true;
    }
  }

  return false;
}
