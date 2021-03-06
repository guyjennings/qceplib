#ifndef QCEPOBJECT_H
#define QCEPOBJECT_H

#include <QObject>
#include <QSettings>
#include "qcepobjectnamer.h"
#include <QDateTime>
#include <QSet>
#include "qcepobject-ptr.h"
#include <QVector>
#include "qcepproperty.h"
#include "qcepfileformatter-ptr.h"
#include <QScriptValue>

class QcepObject : public QObject, public QEnableSharedFromThis<QcepObject>
{
  Q_OBJECT
public:
  QcepObject(QString name);
  virtual ~QcepObject();

  static int allocatedObjects();
  static int deletedObjects();

#ifndef QT_NO_DEBUG
  static QSet<QcepObject*> allocatedObjectsSet();
#endif

  static QcepObjectPtr readDataObject(QcepFileFormatterPtr fmt);

  void readObject(QcepFileFormatterPtr fmt);
  void writeObject(QcepFileFormatterPtr fmt);

  virtual void readObjectData(QcepFileFormatterPtr fmt);
  virtual void writeObjectData(QcepFileFormatterPtr fmt);

signals:

public slots:
  virtual void printLine(QString line) const;
  virtual void printMessage(QString msg, QDateTime dt=QDateTime::currentDateTime()) const;
  virtual void criticalMessage(QString msg, QDateTime ts=QDateTime::currentDateTime()) const;
  virtual void statusMessage(QString msg, QDateTime ts=QDateTime::currentDateTime()) const;

  virtual QString settingsScript();

  QString toScriptLiteral(QVariant v);
  QVariant fromScriptLiteral(QString lit);

  void readObjectSettings(QSettings *set, QString section);

  void dumpObjectTreePtr(int level=0);

  int childCount() const;

  int isChanged() const;
  QString changedBy() const;

  int childrenChanged() const;
  QString childrenChangedBy() const;

  int checkChildren(int verbose=0, int level=0) const;

  void setParentPtr(QcepObjectWPtr parent);
  QcepObjectWPtr parentPtr() const;
  QVector<QcepObjectPtr> childrenPtr() const;
  QcepObjectWPtr childPtr(int n) const;

  QcepObjectPtr construct(QString className);

public:
  virtual void writeSettings(QSettings *set, QString section);
  virtual void readSettings(QSettings *set, QString section);

  QString get_Name() const;
  void    set_Name(QString name);

  QString get_Type() const;
//  void    set_Type(QString name);

  static QString addSlashes(QString str);

  virtual void addChildPtr(QcepObjectPtr child);
  virtual void removeChildPtr(QcepObjectPtr child);

  void propertyChanged(QcepProperty *prop);

  static QScriptValue toScriptValue(QScriptEngine *engine, const QcepObjectPtr &data);
  static void fromScriptValue(const QScriptValue &obj, QcepObjectPtr &data);

protected:
  template <typename T>
  bool checkPointer(QcepObjectWPtr ptr, QSharedPointer<T>& field);

  template <typename T>
  bool checkPointer(QcepObjectWPtr ptr, QWeakPointer<T>& field);

private:
  QcepObjectWPtr                      m_Parent;
  QVector<QcepObjectPtr>              m_Children;
  QcepObjectNamer                     m_ObjectNamer;
  QAtomicInt                          m_ChangeCount;
  QAtomicPointer<QcepProperty>        m_LastChanged;

public:
  Q_PROPERTY(QString name READ get_Name WRITE set_Name STORED false)
//  QCEP_STRING_PROPERTY(Name)

  Q_PROPERTY(QString type READ get_Type /*WRITE set_Type*/ STORED false)
//  QCEP_STRING_PROPERTY(Type)

//  Q_PROPERTY(int typeID READ get_TypeID WRITE set_TypeID STORED false)
//  QCEP_INTEGER_PROPERTY(TypeID)
};

Q_DECLARE_METATYPE(QcepObject*)

#endif // QCEPOBJECT_H
