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

  m_SpecServer =
      QcepSpecServerPtr(
        NEWPTR(QcepSpecServer("specServer")));

  m_SpecServer -> initialize(sharedFromThis(),
                             m_SpecServerSettings,
                             m_ScriptEngine);

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
