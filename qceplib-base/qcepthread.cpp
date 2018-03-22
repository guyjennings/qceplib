#include "qcepthread.h"
#include <stdio.h>
#include "qnewthread.h"

//TODO: change to name arg in constructor?
QcepThread::QcepThread(QString name) :
  inherited(name),
  m_Parent(),
  m_Thread()
{
  m_Thread =
      QNewThreadPtr(
        new QNewThread(this));

  m_Thread -> setObjectName(name);

//  connect(m_Thread.data(),
//          &QThread::started,
//          this,
//          &QcepThread::run,
//          Qt::DirectConnection);
}

void QcepThread::initialize(QcepObjectWPtr parent)
{
  inherited::initialize(parent);

  m_Parent = parent;
}

QcepThread::~QcepThread()
{
#ifndef QT_NO_DEBUG
  if (isRunning()) {
    printf("QcepThread %s destroyed while still running\n",
           qPrintable(objectName()));
  }
#endif
}

void QcepThread::msleep(unsigned long t)
{
  QThread::msleep(t);
}

QcepObjectWPtr QcepThread::parent()
{
  return m_Parent;
}

bool QcepThread::isRunning() const
{
  bool res = false;

  if (m_Thread) {
    res = m_Thread -> isRunning();
  }

  return res;
}

int QcepThread::exec()
{
  int res = 0;

  if (m_Thread) {
    res = m_Thread -> exec();
  }

  return res;
}

void QcepThread::exit(int retcode)
{
  if (m_Thread) {
    m_Thread -> exit(retcode);
  }
}

bool QcepThread::wait()
{
  bool res = false;

  if (m_Thread) {
    res = m_Thread -> wait();
  }

  return res;
}

void QcepThread::start()
{
  if (m_Thread) {
    m_Thread -> start();
  }
}

void QcepThread::quit()
{
  if (m_Thread) {
    m_Thread -> quit();
  }
}

void QcepThread::setObjectName(const QString &name)
{
  inherited::setObjectName(name);

  if (m_Thread) {
    m_Thread -> setObjectName(name);
  }
}
