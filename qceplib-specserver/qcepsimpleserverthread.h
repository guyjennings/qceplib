#ifndef QCEPSIMPLESERVERTHREAD_H
#define QCEPSIMPLESERVERTHREAD_H

#include "qceplib_global.h"
#include "qcepthread.h"
#include "qcepsimpleserver-ptr.h"
#include "qcepsimpleserversettings-ptr.h"

class QCEP_EXPORT QcepSimpleServerThread : public QcepThread
{
  Q_OBJECT

private:
  typedef QcepThread inherited;

public:
  Q_INVOKABLE QcepSimpleServerThread(QString name);
  ~QcepSimpleServerThread();

  void initialize(QcepObjectWPtr               parent,
                  QcepSimpleServerSettingsWPtr settings);

  QcepSimpleServerWPtr simpleServer();

protected:
  void run();
  void shutdown();

private:
  QcepSimpleServerPtr          m_SimpleServer;
  QcepSimpleServerSettingsWPtr m_SimpleServerSettings;
};

#endif // QCEPSIMPLESERVERTHREAD_H
