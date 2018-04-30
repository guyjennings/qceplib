#include "qcepspecserverthread.h"
#include "qcepdebug.h"
#include "qcepspecserver.h"

QcepSpecServerThread::QcepSpecServerThread(QString name)
  : inherited(name)
{

}

QcepSpecServerThread::~QcepSpecServerThread()
{
#ifndef QT_NO_DEBUG
  printf("Shutting down spec server thread\n");
#endif

  shutdown();

#ifndef QT_NO_DEBUG
  printf("Deleting spec server thread\n");
#endif
}

void QcepSpecServerThread::initialize(QcepObjectWPtr             parent,
                                      QcepSpecServerSettingsWPtr settings,
                                      QcepScriptEngineWPtr       scriptEngine)
{
  inherited::initialize(parent);

  m_SpecServerSettings = settings;
  m_ScriptEngine       = scriptEngine;
}

void QcepSpecServerThread::run()
{
  if (qcepDebug(DEBUG_THREADS)) {
    printMessage("Spec Server Thread Started");
  }

  {
    QcepSpecServerPtr srv =
        QcepSpecServerPtr(
          NEWPTR(QcepSpecServer("specServer")));

    if (srv) {
      srv -> initialize(sharedFromThis(),
                        m_SpecServerSettings,
                        m_ScriptEngine);
    }

    m_SpecServer = srv;
  }

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

void QcepSpecServerThread::haltSpecServer()
{
  if (m_SpecServer) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
    INVOKE_CHECK(
          QMetaObject::invokeMethod(m_SpecServer.data(), &QcepSpecServer::haltSpecServer))
#else
    INVOKE_CHECK(
          QMetaObject::invokeMethod(m_SpecServer.data(), "haltSpecServer"))
#endif
  }
}
