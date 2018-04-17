#ifndef QCEPSERVER_H
#define QCEPSERVER_H

#include "qceplib_global.h"
#include "qcepobject.h"
#include "qcepscriptengine-ptr.h"

class QCEP_EXPORT QcepServer : public QcepObject
{
  Q_OBJECT

private:
  typedef QcepObject inherited;

public:
  QcepServer(QString name);
  ~QcepServer();

  void initialize(QcepObjectWPtr       parent,
                  QcepScriptEngineWPtr scriptEngine);

signals:
  void executeServerCommand(QcepServer* srv,
                            QString cmd);

public slots:
  virtual void finishedCommand(QScriptValue result) = 0;

protected:
  QcepScriptEngineWPtr m_ScriptEngine;
};

Q_DECLARE_METATYPE(QcepServer*)

#endif // QCEPSERVER_H
