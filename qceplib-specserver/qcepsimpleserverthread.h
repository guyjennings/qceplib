#ifndef QCEPSIMPLESERVERTHREAD_H
#define QCEPSIMPLESERVERTHREAD_H

#include "qceplib_global.h"
#include "qcepthread.h"
#include "qcepsimpleserver-ptr.h"
#include "qcepsimpleserversettings-ptr.h"
#include "qcepscriptengine-ptr.h"

class QCEP_EXPORT QcepSimpleServerThread : public QcepThread
{
  Q_OBJECT

private:
  typedef QcepThread inherited;

public:
  Q_INVOKABLE QcepSimpleServerThread(QString name);
  ~QcepSimpleServerThread();

  void initialize(QcepObjectWPtr               parent,
                  QcepSimpleServerSettingsWPtr settings,
                  QcepScriptEngineWPtr         scriptEngine);

  QcepSimpleServerWPtr simpleServer();

  void haltSimpleServer();

protected:
  void run();

private:
  QcepSimpleServerPtr          m_SimpleServer;
  QcepSimpleServerSettingsWPtr m_SimpleServerSettings;
  QcepScriptEngineWPtr         m_ScriptEngine;
};

#endif // QCEPSIMPLESERVERTHREAD_H
