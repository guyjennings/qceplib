#ifndef QCEPSPECSERVERTHREAD_H
#define QCEPSPECSERVERTHREAD_H

#include "qceplib_global.h"
#include "qcepthread.h"
#include "qcepspecserver-ptr.h"
#include "qcepspecserversettings-ptr.h"
#include "qcepscriptengine-ptr.h"

class QCEP_EXPORT QcepSpecServerThread : public QcepThread
{
  Q_OBJECT

private:
  typedef QcepThread inherited;

public:
  Q_INVOKABLE QcepSpecServerThread(QString name);
  ~QcepSpecServerThread();

  void initialize(QcepObjectWPtr             parent,
                  QcepSpecServerSettingsWPtr settings,
                  QcepScriptEngineWPtr       scriptEngine);

  QcepSpecServerWPtr specServer();

  void haltSpecServer();

protected:
  void run();

private:
  QcepSpecServerPtr          m_SpecServer;
  QcepSpecServerSettingsWPtr m_SpecServerSettings;
  QcepScriptEngineWPtr       m_ScriptEngine;
};

#endif // QCEPSPECSERVERTHREAD_H
