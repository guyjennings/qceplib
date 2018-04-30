#ifndef QCEPSIMPLESERVER_H
#define QCEPSIMPLESERVER_H

#include "qceplib_global.h"
#include "qcepserver.h"
#include "qcepsimpleserversettings-ptr.h"
#include "qcepscriptengine-ptr.h"
#include <QTcpServer>
#include <QTcpSocket>

class QCEP_EXPORT QcepSimpleServer : public QcepServer
{
  Q_OBJECT

private:
  typedef QcepServer inherited;

public:
  Q_INVOKABLE QcepSimpleServer(QString name);
  ~QcepSimpleServer();

  void initialize(QcepObjectWPtr               parent,
                  QcepSimpleServerSettingsWPtr settings,
                  QcepScriptEngineWPtr         scriptEngine);

  void startServer(QHostAddress addr, int port);
  void stopServer();
  void finishedCommand(QScriptValue result);

public slots:
  void haltSimpleServer();
  void runModeChanged();
  void serverPortChanged();
  void openNewConnection();
  void connectionClosed();
  void clientRead();
  void shutdown();

private:
  QcepSimpleServerSettingsWPtr  m_ServerSettings;
  QTcpServer                    m_Server;
  QTcpSocket                    *m_Socket;
};

Q_DECLARE_METATYPE(QcepSimpleServer*)

#endif // QCEPSIMPLESERVER_H
