#include "qcepdebug.h"
#include "qcepmacros.h"
#include "qcepobject.h"
#include "qcepsettingssaver.h"
#include "qcepproperty.h"
#include <stdio.h>
#include "qcepmutexlocker.h"
#include <QThread>

QcepSettingsSaver::QcepSettingsSaver(QObject *owner) :
  QObject(),
  m_Owner(owner),
  m_SaveDelay(5000)
{
  if (qcepDebug(DEBUG_CONSTRUCTORS)) {
    printf("QcepSettingsSaver::QcepSettingsSaver(%p)\n", this);
  }

  connect(&m_Timer, SIGNAL(timeout()), this, SLOT(performSave()));
}

QcepSettingsSaver::~QcepSettingsSaver()
{
  if (qcepDebug(DEBUG_CONSTRUCTORS)) {
    printf("QcepSettingsSaver::~QcepSettingsSaver(%p)\n", this);
  }
}

void QcepSettingsSaver::start()
{
  if (QThread::currentThread() != thread()) {
    INVOKE_CHECK(QMetaObject::invokeMethod(this, "start"));
  } else {
    m_Timer.setSingleShot(false);

    m_ChangeCount.fetchAndStoreOrdered(0);
    m_LastChanged.fetchAndStoreOrdered(0);

    m_Timer.start(m_SaveDelay);
  }
}

void QcepSettingsSaver::performSave()
{
  int nupdates = m_ChangeCount.fetchAndStoreOrdered(0);

  if (nupdates > 0) {
    QcepMutexLocker lock(__FILE__, __LINE__, &m_Mutex);

    if (qcepDebug(DEBUG_PREFS)) {
      printMessage(tr("Settings Saver saving %1 updates").arg(nupdates));
      QcepProperty *p = m_LastChanged.fetchAndStoreOrdered(NULL);

      if (p) {
        printMessage(tr("Last property changed %1").arg(p->name()));
      }
    }

    QTime tic;
    tic.start();

    INVOKE_CHECK(QMetaObject::invokeMethod(m_Owner, "writeSettings", Qt::DirectConnection));

    if (qcepDebug(DEBUG_PREFS)) {
      printMessage(tr("Saving settings took %1 msec").arg(tic.elapsed()));
    }
  }
}

void QcepSettingsSaver::propertyChanged(QcepProperty * prop)
{
  m_ChangeCount.fetchAndAddOrdered(1);
  m_LastChanged.store(prop);
}

void QcepSettingsSaver::printMessage(QString msg, QDateTime ts)
{
  INVOKE_CHECK(QMetaObject::invokeMethod(m_Owner, "printMessage", Q_ARG(QString, msg), Q_ARG(QDateTime, ts)));
}
