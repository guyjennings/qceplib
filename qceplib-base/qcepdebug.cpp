#include "qcepdebug.h"
#include <stdio.h>
#include <QMetaEnum>

QSharedPointer<QcepDebugDictionary> g_DebugLevel;

QcepDebugDictionary::QcepDebugDictionary() :
  m_DebugLevel(0)
{
  setMessage(DEBUG_NOMESSAGES, "Disable All Debug Messages");
  setMessage(DEBUG_APP,        "Application startup and shutdown");
  setMessage(DEBUG_PROPERTIES, "Properties");
  setMessage(DEBUG_DYNPROPS,   "Dynamic Properties");
  setMessage(DEBUG_WINDOW,     "Window Operations");
  setMessage(DEBUG_PREFS,      "Settings/Prefs Operations");
  setMessage(DEBUG_DISPLAY,    "Display Operations");
  setMessage(DEBUG_CONSTRUCTORS, "Object Constructors/Destructors");
  setMessage(DEBUG_ALLOCATOR,    "Memory Allocation");
  setMessage(DEBUG_THREADS,      "Thread Initialization");
  setMessage(DEBUG_QUEUES,       "Queue Operations");
  setMessage(DEBUG_IMAGE_CONSTRUCTORS, "Image Object Constructors/Destructors");
  setMessage(DEBUG_LOCKING,    "Debug Mutex Lock Operations");
  setMessage(DEBUG_SERVER,       "Server Commands");
  setMessage(DEBUG_IMPORT,       "Data Import Operations");
  setMessage(DEBUG_EXPORT,       "Data Export Operations");
  setMessage(DEBUG_DATABROWSER,  "Data Browser Operations");
  setMessage(DEBUG_OBJECTBROWSER,  "Object Browser Operations");
  setMessage(DEBUG_DRAGDROP,     "Drag and Drop Operations");
  setMessage(DEBUG_PANEL_SHOW,   "Visualize PE Panel Boundaries");
  setMessage(DEBUG_CALIBRANT,    "Powder Calibrant Calculations");
  setMessage(DEBUG_ROI,          "Debug ROI Operations");
  setMessage(DEBUG_FITTING,      "Curve Fitting");
  setMessage(DEBUG_NOPARALLEL,   "Serialize Various Algorithms");
  setMessage(DEBUG_PERFORM,      "Performance Measurement");
  setMessage(DEBUG_FILES,        "File Operations");
  setMessage(DEBUG_IMAGES,       "Image Operations");
  setMessage(DEBUG_EXITWAIT,     "Halt at exit");
}

qint64 qcepDebug(int cond)
{
  if (g_DebugLevel == NULL) {
    printf("No Debug Dictionary Allocated\n");

    return 0;
  } else {
    qint64 mask = 1;

    mask <<= cond;

    return g_DebugLevel->debugLevel() & (mask);
  }
}

qint64 QcepDebugDictionary::debugLevel() const
{
  return m_DebugLevel;
}

void QcepDebugDictionary::setDebugLevel(qint64 level)
{
  m_DebugLevel = level;
}

QString QcepDebugDictionary::message(int val) const
{
  return m_Messages.value(val);
}

void QcepDebugDictionary::setMessage(int val, QString msg)
{
  if (m_Messages.contains(val)) {
    printf("Warning: duplicate messages for value %x\nExisting: %s\nNew:%s\n",
           val, qPrintable(message(val)), qPrintable(msg));
  }

  m_Messages.insert(val, msg);
}

//QString QcepDebugDictionary::hexArg(void *p)
//{
//#if (QT_POINTER_SIZE==4)
//  return tr("0x%1").arg((quint32)p, 8, 16, QLatin1Char('0'));
//#else
//  return tr("0x%1").arg((quint64)p, 16, 16, QLatin1Char('0'));
//#endif
//}

int QcepDebugDictionary::debugFlagCount()
{
  return LAST_QCEP_DEBUG;
}

QString QcepDebugDictionary::debugFlagName(int i)
{
  QString res = debugFlagNameFrom(&QcepDebug::staticMetaObject, i);

  return res;
}

QString QcepDebugDictionary::debugFlagNameFrom(const QMetaObject *meta, int i)
{
  int n = meta -> enumeratorCount();

  for (int j=0; j<n; j++) {
    QMetaEnum en = meta -> enumerator(j);

    return en.key(i);
  }

  return QString();
}

int QcepDebugDictionary::debugFlagCheck(QString name)
{
  int res = debugFlagCheckFrom(&QcepDebug::staticMetaObject, name);

  return res;
}

int QcepDebugDictionary::debugFlagCheckFrom(const QMetaObject *meta, QString f)
{
  int n = meta -> enumeratorCount();

  QString flag = "DEBUG_" + f;

  for (int i=0; i<n; i++) {
    QMetaEnum en = meta -> enumerator(i);

    bool isOk = false;
    int  val  = en.keyToValue(qPrintable(flag), &isOk);

    if (isOk) {
      return val;
    }
  }

  return -1;
}
