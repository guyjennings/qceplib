#ifndef QCEPEVENTFILTERLINEEDIT_H
#define QCEPEVENTFILTERLINEEDIT_H

#include "qcepeventfilter.h"

class QcepEventFilterLineEdit : public QcepEventFilter
{
  Q_OBJECT

private:
  typedef QcepEventFilter inherited;

public:
  QcepEventFilterLineEdit(QObject *parent, QcepMainWindow *win);

  bool eventFilter(QObject *watched, QEvent *event);

signals:

public slots:
};

#endif // QCEPEVENTFILTERLINEEDIT_H
