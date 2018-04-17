#ifndef QCEPSIMPLESERVER_H
#define QCEPSIMPLESERVER_H

#include "qceplib_global.h"
#include "qcepobject.h"
#include "qcepsimpleserversettings-ptr.h"
#include "qcepscriptengine-ptr.h"

class QCEP_EXPORT QcepSimpleServer : public QcepObject
{
  Q_OBJECT

private:
  typedef QcepObject inherited;

public:
  Q_INVOKABLE QcepSimpleServer(QString name);
  ~QcepSimpleServer();

  void initialize(QcepObjectWPtr               parent,
                  QcepSimpleServerSettingsWPtr settings,
                  QcepScriptEngineWPtr         scriptEngine);

public:
  QcepSimpleServerSettingsWPtr  m_ServerSettings;
  QcepScriptEngineWPtr          m_ScriptEngine;
};

#endif // QCEPSIMPLESERVER_H
