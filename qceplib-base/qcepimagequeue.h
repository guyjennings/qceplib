#ifndef QCEPIMAGEQUEUE_H
#define QCEPIMAGEQUEUE_H

#include "qceplib_global.h"
#include "qcepmacros.h"

#include "qcepimagedata.h"
#include "qcepmaskdata.h"
#include <QQueue>
#include <QString>
#include <QSharedPointer>

class QCEP_EXPORT QcepImageQueueBase : public QcepObject
{
  Q_OBJECT

private:
  typedef QcepObject inherited;

public:
  QcepImageQueueBase(QString name);
  ~QcepImageQueueBase();
  void initialize(QcepObjectWPtr parent);

//  void preallocate(int nFrames, int nCols, int nRows);

//  Q_PROPERTY(int nRows READ get_NRows WRITE set_NRows)
//  QCEP_INTEGER_PROPERTY(NRows)

//  Q_PROPERTY(int nCols READ get_NCols WRITE set_NCols)
//  QCEP_INTEGER_PROPERTY(NCols)

  Q_PROPERTY(int size  READ get_Size  WRITE set_Size STORED false)
  QCEP_INTEGER_PROPERTY(Size)

  Q_PROPERTY(int count READ get_Count WRITE set_Count STORED false)
  QCEP_INTEGER_PROPERTY(Count)
};

template <typename T>
class QCEP_EXPORT QcepImageQueue : public QcepImageQueueBase
{

private:
  typedef QcepImageQueueBase inherited;

public:
  QcepImageQueue(QString name);
  ~QcepImageQueue();

  void deallocate();

  QSharedPointer<T> dequeue();
  void enqueue(QSharedPointer<T> data);
  QSharedPointer<T> operator[](int n);

private:
  mutable QMutex               m_Lock;
  QQueue< QSharedPointer<T> >  m_Queue;
};

class QCEP_EXPORT QcepImageBaseQueue : public QcepImageQueue<QcepImageDataBase> {
  Q_OBJECT

public:
  Q_INVOKABLE QcepImageBaseQueue(QString name);
};

class QCEP_EXPORT QcepUInt16ImageQueue : public QcepImageQueue<QcepUInt16ImageData> {
  Q_OBJECT

public:
  Q_INVOKABLE QcepUInt16ImageQueue(QString name);
};

class QCEP_EXPORT QcepInt16ImageQueue : public QcepImageQueue<QcepInt16ImageData> {
  Q_OBJECT

public:
  Q_INVOKABLE QcepInt16ImageQueue(QString name);
};

class QCEP_EXPORT QcepUInt32ImageQueue : public QcepImageQueue<QcepUInt32ImageData> {
  Q_OBJECT

public:
  Q_INVOKABLE QcepUInt32ImageQueue(QString name);
};

class QCEP_EXPORT QcepInt32ImageQueue : public QcepImageQueue<QcepInt32ImageData> {
  Q_OBJECT

public:
  Q_INVOKABLE QcepInt32ImageQueue(QString name);
};

class QCEP_EXPORT QcepDoubleImageQueue : public QcepImageQueue<QcepDoubleImageData> {
  Q_OBJECT

public:
  Q_INVOKABLE QcepDoubleImageQueue(QString name);
};

class QCEP_EXPORT QcepFloatImageQueue : public QcepImageQueue<QcepFloatImageData> {
  Q_OBJECT

public:
  Q_INVOKABLE QcepFloatImageQueue(QString name);
};

class QCEP_EXPORT QcepMaskQueue : public QcepImageQueue<QcepMaskData> {
  Q_OBJECT

public:
  Q_INVOKABLE QcepMaskQueue(QString name);
};

Q_DECLARE_METATYPE(QcepImageBaseQueue*)
Q_DECLARE_METATYPE(QcepUInt16ImageQueue*)
Q_DECLARE_METATYPE(QcepInt16ImageQueue*)
Q_DECLARE_METATYPE(QcepUInt32ImageQueue*)
Q_DECLARE_METATYPE(QcepInt32ImageQueue*)
Q_DECLARE_METATYPE(QcepDoubleImageQueue*)
Q_DECLARE_METATYPE(QcepFloatImageQueue*)
Q_DECLARE_METATYPE(QcepMaskQueue*)

#endif
