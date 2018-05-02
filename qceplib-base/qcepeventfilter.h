#ifndef QCEPEVENTFILTER_H
#define QCEPEVENTFILTER_H

#include <QObject>
#include "qcepmainwindow-ptr.h"

class QcepEventFilter : public QObject
{
  Q_OBJECT
public:
  explicit QcepEventFilter(QObject *parent, QcepMainWindow *win);

signals:

public slots:

protected:
  QcepMainWindow *m_MainWindow;
};

#endif // QCEPEVENTFILTER_H
