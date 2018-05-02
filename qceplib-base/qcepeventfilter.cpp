#include "qcepeventfilter.h"
#include "qcepmainwindow.h"

QcepEventFilter::QcepEventFilter(QObject *parent, QcepMainWindow *win)
  : QObject(parent),
    m_MainWindow(win)
{
}
