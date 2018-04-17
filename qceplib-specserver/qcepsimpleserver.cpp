#include "qcepsimpleserver.h"
#include "qcepsimpleserversettings.h"
#include "qcepscriptengine.h"

QcepSimpleServer::QcepSimpleServer(QString name)
  : inherited(name)
{

}

QcepSimpleServer::~QcepSimpleServer()
{
}

void QcepSimpleServer::initialize(QcepObjectWPtr               parent,
                                  QcepSimpleServerSettingsWPtr settings,
                                  QcepScriptEngineWPtr         scriptEngine)
{
  inherited::initialize(parent, scriptEngine);

  m_ServerSettings = settings;

  QcepSimpleServerSettingsPtr set(m_ServerSettings);

  if (set) {
    connect(set -> prop_RunSimpleServer(), &QcepIntProperty::valueChanged,
            this, &QcepSimpleServer::runModeChanged);

    connect(set -> prop_SimpleServerPort(), &QcepIntProperty::valueChanged,
            this, &QcepSimpleServer::serverPortChanged);
  }

  connect(&m_Server, &QTcpServer::newConnection,
          this, &QcepSimpleServer::openNewConnection);

  runModeChanged();
}

void QcepSimpleServer::runModeChanged()
{
  THREAD_CHECK;

  QcepSimpleServerSettingsPtr set(m_ServerSettings);

  if (set) {
    if (set -> get_RunSimpleServer()) {
      startServer(QHostAddress::Any, set -> get_SimpleServerPort());
    } else {
      stopServer();
    }
  }
}

void QcepSimpleServer::serverPortChanged()
{
  THREAD_CHECK;

  QcepSimpleServerSettingsPtr set(m_ServerSettings);

  if (set) {
    stopServer();

    if (set -> get_RunSimpleServer()) {
      startServer(QHostAddress::Any, set -> get_SimpleServerPort());
    }
  }
}

void QcepSimpleServer::startServer(QHostAddress addr, int port)
{
  if (qcepDebug(DEBUG_SERVER)) {
    printMessage(tr("Starting simple server on address %1, port %2")
                 .arg(addr.toString()).arg(port));
  }

  m_Server.setMaxPendingConnections(1);

  if (m_Server.isListening()) {
    m_Server.close();
  }

  if (!m_Server.listen(addr, port)) {
    criticalMessage(tr("Failed to bind to address %1 port %2\nIs there another copy of qxrd running already?").arg(addr.toString()).arg(port));
  }
}

void QcepSimpleServer::stopServer()
{
  if (m_Server.isListening()) {
    m_Server.close();
  }
}

void QcepSimpleServer::openNewConnection()
{
  m_Socket = m_Server.nextPendingConnection();

  connect(m_Socket, &QIODevice::readyRead,
          this,     &QcepSimpleServer::clientRead);

  if (qcepDebug(DEBUG_SERVER)) {
    printMessage(tr("New connection from %1").arg(m_Socket->peerAddress().toString()) );
  }
}

void QcepSimpleServer::connectionClosed()
{
  if (qcepDebug(DEBUG_SERVER)) {
    printMessage("Client closed connection");
  }
}

void QcepSimpleServer::clientRead()
{
  QTextStream ts( m_Socket );

  while ( m_Socket->canReadLine() ) {
    QString str = ts.readLine();

    if (qcepDebug(DEBUG_SERVER)) {
      printMessage(tr("Command: %1 received").arg(str));
    }

    emit executeServerCommand(this, str);
  }
}

void QcepSimpleServer::finishedCommand(QScriptValue result)
{
  if (qcepDebug(DEBUG_SERVER)) {
    printMessage(tr("Result: %1").arg(result.toString()));
  }

  if (m_Socket && (m_Socket->isWritable())) {
    m_Socket -> write(qPrintable(QcepScriptEngine::convertToString(result)+"\n"));
  }
}

void QcepSimpleServer::shutdown()
{
  m_Server.close();
}
