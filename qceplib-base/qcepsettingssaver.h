#ifndef QCEPSETTINGSSAVER_H
#define QCEPSETTINGSSAVER_H

#include "qcepmacros.h"
#include <QObject>
#include "qcepobject-ptr.h"
#include <QTimer>
#include <QMutex>
#include <QDateTime>

#include "qcepproperty-ptr.h"

class QcepSettingsSaver : public QObject
{
  Q_OBJECT
public:
  explicit QcepSettingsSaver(QObject *owner);
  ~QcepSettingsSaver();

  void propertyChanged(QcepProperty *prop = NULL);

public slots:
  void start();
  void performSave();
  void printMessage(QString msg, QDateTime ts=QDateTime::currentDateTime());

private:
  QMutex             m_Mutex;
  QObject           *m_Owner;
  QAtomicInt         m_ChangeCount;
  QAtomicPointer<QcepProperty> m_LastChanged;
  QTimer             m_Timer;
  int                m_SaveDelay;
};

#endif // QCEPSETTINGSSAVER_H
