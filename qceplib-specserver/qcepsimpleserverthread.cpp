#include "qcepsimpleserverthread.h"
#include "qcepdebug.h"
#include "qcepsimpleserver.h"

QcepSimpleServerThread::QcepSimpleServerThread(QString name)
  : inherited(name)
{

}

QcepSimpleServerThread::~QcepSimpleServerThread()
{
}

void QcepSimpleServerThread::initialize(QcepObjectWPtr               parent,
                                        QcepSimpleServerSettingsWPtr settings,
                                        QcepScriptEngineWPtr         scriptEngine)
{
  inherited::initialize(parent);

  m_SimpleServerSettings = settings;
  m_ScriptEngine         = scriptEngine;
}

void QcepSimpleServerThread::run()
{
  if (qcepDebug(DEBUG_THREADS)) {
    printMessage("Simple Server Thread Started");
  }

  m_SimpleServer =
      QcepSimpleServerPtr(
        new QcepSimpleServer("simpleServer"));

  m_SimpleServer -> initialize(sharedFromThis(),
                               m_SimpleServerSettings,
                               m_ScriptEngine);

  int rc = exec();

  m_SimpleServer = QcepSimpleServerPtr();

  if (qcepDebug(DEBUG_THREADS)) {
    printMessage(tr("Simple Server Thread terminated with rc %1").arg(rc));
  }
}

QcepSimpleServerWPtr QcepSimpleServerThread::simpleServer()
{
  while (isRunning()) {
    if (m_SimpleServer) return m_SimpleServer;

    msleep(50);
  }

  return m_SimpleServer;
}