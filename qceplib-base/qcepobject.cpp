#include "qcepobject.h"
#include "qcepproperty.h"
#include <QMetaProperty>
#include <stdio.h>
#include <QAtomicInt>
#include <QSet>
#include <QThread>

static QAtomicInt s_ObjectAllocateCount(0);
static QAtomicInt s_ObjectDeleteCount(0);

#ifndef QT_NO_DEBUG
static QSet<QcepObject*> s_Allocated;
#endif

QcepObject::QcepObject(QString name, QcepObjectWPtr parent) :
  QObject(NULL),
  m_Parent(parent),
  m_ObjectNamer(this, name)/*,
  m_Name(QcepSettingsSaverWPtr(), this, "name", name, "Object Name")*/
{
  s_ObjectAllocateCount.fetchAndAddOrdered(1);

#ifndef QT_NO_DEBUG
  s_Allocated.insert(this);
#endif

  QcepObjectPtr p(m_Parent);

  if (p) {
    p->addChildPtr(sharedFromThis());
  }
}

QcepObject::~QcepObject()
{
#ifndef QT_NO_DEBUG
  QThread *currTh = QThread::currentThread();
  QThread *objTh  = thread();

  if (objTh && (currTh != objTh)) {
    printf("Deleting object from different thread obj:%s (curr:%s, objth:%s)\n",
           qPrintable(objectName()),
           qPrintable(currTh ? currTh->objectName() : "null"),
           qPrintable(objTh ? objTh->objectName() : "null"));
  }
#endif

  s_ObjectDeleteCount.fetchAndAddOrdered(1);

#ifndef QT_NO_DEBUG
  s_Allocated.remove(this);
#endif
}

void QcepObject::addChildPtr(QcepObjectWPtr child)
{
  m_Children.append(child);
}

int QcepObject::allocatedObjects()
{
  return s_ObjectAllocateCount.load();
}

int QcepObject::deletedObjects()
{
  return s_ObjectDeleteCount.load();
}

#ifndef QT_NO_DEBUG
QSet<QcepObject*> QcepObject::allocatedObjectsSet()
{
  return s_Allocated;
}
#endif

void QcepObject::set_Name(QString name)
{
  setObjectName(name);
}

QString QcepObject::get_Name() const
{
  return objectName();
}

void QcepObject::printLine(QString line)
{
  QcepObjectPtr parent(m_Parent);

  if (parent) {
    parent->printLine(line);
  }
}

void QcepObject::printMessage(QString msg, QDateTime dt) const
{
  QcepObjectPtr parent(m_Parent);

  if (parent) {
    parent->printMessage(msg, dt);
  } else {
    printf("MESSAGE: %s %s\n",
           qPrintable(dt.toString("hh:mm:ss")), qPrintable(msg));
  }
}

void QcepObject::criticalMessage(QString msg, QDateTime dt) const
{
  QcepObjectPtr parent(m_Parent);

  if (parent) {
    parent->criticalMessage(msg, dt);
  } else {
    printf("MESSAGE: %s %s\n",
           qPrintable(dt.toString("hh:mm:ss")), qPrintable(msg));
  }
}

void QcepObject::statusMessage(QString msg, QDateTime dt) const
{
  QcepObjectPtr parent(m_Parent);

  if (parent) {
    parent->statusMessage(msg, dt);
  } else {
    printf("MESSAGE: %s %s\n",
           qPrintable(dt.toString("hh:mm:ss")), qPrintable(msg));
  }
}

void QcepObject::writeSettings(QSettings *set, QString section)
{
  if (set) {
    set->setValue("name", get_Name());
  }

  QcepProperty::writeSettings(this, set, section);
}

void QcepObject::readSettings(QSettings *set, QString section)
{
  if (QThread::currentThread() != thread()) {
    INVOKE_CHECK(QMetaObject::invokeMethod(this, "readObjectSettings", Qt::BlockingQueuedConnection, Q_ARG(QSettings*, set), Q_ARG(QString, section)));
  } else {
    readObjectSettings(set, section);
  }
}

void QcepObject::readObjectSettings(QSettings *set, QString section)
{
  QcepProperty::readSettings(this, set, section);
}

QString QcepObject::addSlashes(QString str)
{
  QString newStr;

  for(int i=0;i<str.length();i++) {
    if(str[i] == '\0') {
      newStr.append('\\');
      newStr.append('0');
    } else if(str[i] == '\'') {
      newStr.append('\\');
      newStr.append('\'');
    } else if(str[i] == '\"') {
      newStr.append('\\');
      newStr.append('\"');
    } else if(str[i] == '\\') {
      newStr.append('\\');
      newStr.append('\\');
    } else {
      newStr.append(str[i]);
    }
  }

  return newStr;
}

QString QcepObject::scriptValueLiteral(QVariant v)
{
  if (v.type() == QMetaType::QString) {
    return "\"" + addSlashes(v.toString()) + "\"";
  } else {
    return v.toString();
  }
}

QString QcepObject::settingsScript()
{
  QString res = "";
  const QMetaObject* metaObject = this->metaObject();

  for (int i=1; i < metaObject->propertyCount(); i++) {
    QMetaProperty prop = metaObject->property(i);

    if (prop.isStored()) {
      res += tr("%1.%2 = %3;\n").arg(this->get_Name())
                                .arg(prop.name())
                                .arg(scriptValueLiteral(this->property(prop.name())));
    }
  }

  return res;
}
