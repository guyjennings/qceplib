#include "qcepspecserverthread.h"
#include "qcepdebug.h"
#include "qcepspecserver.h"

QcepSpecServerThread::QcepSpecServerThread(QString name)
  : inherited(name)
{

}

QcepSpecServerThread::~QcepSpecServerThread()
{
}

void QcepSpecServerThread::initialize(QcepObjectWPtr             parent,
                                      QcepSpecServerSettingsWPtr settings)
{
  inherited::initialize(parent);

  m_SpecServerSettings = settings;
}

void QcepSpecServerThread::shutdown()
{
  exit();

  wait();
}

void QcepSpecServerThread::run()
{
  if (qcepDebug(DEBUG_THREADS)) {
    printMessage("Spec Server Thread Started");
  }

  m_SpecServer =
      QcepSpecServerPtr(
        new QcepSpecServer("specServer"));

  m_SpecServer -> initialize(sharedFromThis(),
                             m_SpecServerSettings);

  int rc = exec();

  m_SpecServer = QcepSpecServerPtr();

  if (qcepDebug(DEBUG_THREADS)) {
    printMessage(tr("Spec Server Thread terminated with rc %1").arg(rc));
  }
}

QcepSpecServerWPtr QcepSpecServerThread::specServer()
{
  while (isRunning()) {
    if (m_SpecServer) return m_SpecServer;

    msleep(50);
  }

  return m_SpecServer;
}
