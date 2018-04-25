#ifndef QCEPMACROS_H
#define QCEPMACROS_H

#include "qceplib_global.h"
#include <QVector>
#include <QList>
#include <QMetaType>
#include <QPointF>
#include <QRectF>

//#define GUI_THREAD_CHECK Q_ASSERT(qApp && qApp ->thread() == QThread::currentThread())
//#define THREAD_CHECK     Q_ASSERT(QThread::currentThread() == thread())

#ifdef QT_NO_DEBUG
#  define GUI_THREAD_CHECK ((void) 0)
#  define THREAD_CHECK     ((void) 0)
#else
#  define GUI_THREAD_CHECK QcepObject::guiThreadCheck(this, __FILE__, __LINE__)
#  define THREAD_CHECK     QcepObject::threadCheck(this, __FILE__, __LINE__)
#endif

#define INVOKE_CHECK(res) if(!res) { printf("Invoke failed File %s, Line %d\n", __FILE__, __LINE__); }
#define CONNECT_CHECK(res) if(!res) { printf("Connect failed File %s, Line %d\n", __FILE__, __LINE__); }

#define STR(s) _STR(s)
#define _STR(s) #s

#define NEWPTR(a) new a
#define NEWPT2(a) new a,&QObject::deleteLater

typedef QVector<double> QcepDoubleVector;
Q_DECLARE_METATYPE(QcepDoubleVector)
typedef QVector<bool> QcepBoolVector;
Q_DECLARE_METATYPE(QcepBoolVector)
typedef QVector<int> QcepIntVector;
Q_DECLARE_METATYPE(QcepIntVector)
typedef QVector<QString> QcepStringVector;
Q_DECLARE_METATYPE(QcepStringVector)

typedef QList<double> QcepDoubleList;
Q_DECLARE_METATYPE(QcepDoubleList)
typedef QList<bool> QcepBoolList;
Q_DECLARE_METATYPE(QcepBoolList)
typedef QList<int> QcepIntList;
Q_DECLARE_METATYPE(QcepIntList)
typedef QList<QString> QcepStringList;
Q_DECLARE_METATYPE(QcepStringList)

typedef QVector<QPointF> QcepPolygon;
Q_DECLARE_METATYPE(QcepPolygon)

Q_DECLARE_METATYPE(QPointF)
Q_DECLARE_METATYPE(QRectF)

extern QCEP_EXPORT const char* qceplibVersion();
extern QCEP_EXPORT const char* qcepH5Version();

#endif // QCEPMACROS_H
