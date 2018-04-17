#include "qcepserver.h"
#include "qcepscriptengine.h"

QcepServer::QcepServer(QString name)
  : inherited(name)
{
}

QcepServer::~QcepServer()
{
}

void QcepServer::initialize(QcepObjectWPtr       parent,
                            QcepScriptEngineWPtr scriptEngine)
{
  inherited::initialize(parent);

  m_ScriptEngine = scriptEngine;

  QcepScriptEnginePtr eng(m_ScriptEngine);

  if (eng) {
    connect(this, &QcepServer::executeServerCommand,
            eng.data(), &QcepScriptEngine::evaluateScriptCommand);
  }
}
