#ifndef QCEPALLOCATORTHREAD_H
#define QCEPALLOCATORTHREAD_H

#include "qcepthread.h"
#include "qcepapplication-ptr.h"
#include "qcepsettingssaver-ptr.h"
#include "qcepallocator-ptr.h"

class QcepAllocatorThread : public QcepThread
{
  Q_OBJECT

public:
  QcepAllocatorThread(QcepApplicationWPtr   app,
                      QcepSettingsSaverWPtr saver);
  ~QcepAllocatorThread();

  void shutdown();

  QcepAllocatorPtr allocator() const;

protected:
  void run();

private:
  QcepAllocatorPtr      m_Allocator;
  QcepSettingsSaverWPtr m_Saver;
};

#endif // QCEPALLOCATORTHREAD_H
