#ifndef QCEPMACROS_H
#define QCEPMACROS_H

#include <QVector>
#include <QList>
#include <QMetaType>
#include <QPointF>
#include <QRectF>

#define GUI_THREAD_CHECK Q_ASSERT(qApp && qApp ->thread() == QThread::currentThread())
#define THREAD_CHECK     Q_ASSERT(QThread::currentThread() == thread())

#define INVOKE_CHECK(res) if(!res) { printf("Invoke failed File %s, Line %d\n", __FILE__, __LINE__); }
#define CONNECT_CHECK(res) if(!res) { printf("Connect failed File %s, Line %d\n", __FILE__, __LINE__); }

#define STR(s) _STR(s)
#define _STR(s) #s

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

extern const char* qceplibVersion();
extern const char* qcepH5Version();

#endif // QCEPMACROS_H
