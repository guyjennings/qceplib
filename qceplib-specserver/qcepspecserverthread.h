#ifndef QCEPSPECSERVERTHREAD_H
#define QCEPSPECSERVERTHREAD_H

#include "qceplib_global.h"
#include "qcepthread.h"
#include "qcepspecserver-ptr.h"
#include "qcepspecserversettings-ptr.h"

class QCEP_EXPORT QcepSpecServerThread : public QcepThread
{
  Q_OBJECT

private:
  typedef QcepThread inherited;

public:
  Q_INVOKABLE QcepSpecServerThread(QString name);
  ~QcepSpecServerThread();

  void initialize(QcepObjectWPtr             parent,
                  QcepSpecServerSettingsWPtr settings);

  QcepSpecServerWPtr specServer();

protected:
  void run();
  void shutdown();

private:
  QcepSpecServerPtr          m_SpecServer;
  QcepSpecServerSettingsWPtr m_SpecServerSettings;
};

#endif // QCEPSPECSERVERTHREAD_H
