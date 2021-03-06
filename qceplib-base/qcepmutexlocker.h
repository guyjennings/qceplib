#ifndef QCEPMUTEXLOCKER_H
#define QCEPMUTEXLOCKER_H

#include <QMutexLocker>
#include <QTime>
#include "qcepmacros.h"

class QcepMutexLocker : public QMutexLocker
{
public:
  QcepMutexLocker(const char *file, int line, QMutex * mutex);
  ~QcepMutexLocker();

  static void traceLock(const char *file, int line);
  static void dumpLocks();

private:
  QTime       m_LockTime;
  const char* m_File;
  int         m_Line;
};

#endif // QCEPMUTEXLOCKER_H
