#ifndef QCEPEVENTFILTERTEXTEDIT_H
#define QCEPEVENTFILTERTEXTEDIT_H

#include "qcepeventfilter.h"

class QcepEventFilterTextEdit : public QcepEventFilter
{
  Q_OBJECT

private:
  typedef QcepEventFilter inherited;

public:
  explicit QcepEventFilterTextEdit(QObject *parent, QcepMainWindow *win);

  bool eventFilter(QObject *watched, QEvent *event);

signals:

public slots:
};

#endif // QCEPEVENTFILTERTEXTEDIT_H
