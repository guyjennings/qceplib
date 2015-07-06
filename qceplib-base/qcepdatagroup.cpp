#include "qcepdatagroup.h"
#include <QScriptEngine>
#include "qcepdataarray.h"
#include "qcepdataarray-ptr.h"
#include "qcepdatagroup.h"
#include "qcepdatagroup-ptr.h"
#include "qcepdatacolumn.h"
#include "qcepdatacolumn-ptr.h"
#include "qcepdatacolumnscan.h"
#include "qcepdatacolumnscan-ptr.h"
#include <QFileInfo>
#include <QDir>

QcepDataGroup::QcepDataGroup(QcepSettingsSaverWPtr saver, QString name) :
  QcepDataObject(saver, name)
{
  set_Type("Data Group");
}

QString QcepDataGroup::description() const
{
  return tr("%1 Items").arg(count());
}

QcepDataGroupPtr QcepDataGroup::newDataGroup(QcepSettingsSaverWPtr saver, QString name)
{
  QcepDataGroupPtr res(new QcepDataGroup(saver, name));

  return res;
}

QcepDataObjectPtr QcepDataGroup::item(int n)
{
  return m_Objects.value(n);
}

QcepDataObjectPtr QcepDataGroup::item(QString nm)
{
  QFileInfo info(nm);

  if (info.isRoot()) {
    return rootItem();
  } else if (nm == ".") {
    return sharedFromThis();
  } else if (info.fileName() == nm) {
    foreach(QcepDataObjectPtr p, m_Objects) {
      if (p && (p->get_Name() == nm)) {
        return p;
      }
    }
  } else {
    QDir dir = info.dir();

    QcepDataObjectPtr obj = item(dir.path());

    if (obj) {
      QcepDataGroupPtr grp = qSharedPointerDynamicCast<QcepDataGroup>(obj);

      if (grp) {
        return grp->item(info.fileName());
      }
    }
  }
  return QcepDataObjectPtr();
}

int QcepDataGroup::count() const
{
  return m_Objects.count();
}

QcepDataGroupPtr  QcepDataGroup::group(QString path)
{
  QcepDataObjectPtr obj = item(path);

  return qSharedPointerDynamicCast<QcepDataGroup>(obj);
}

QcepDataArrayPtr  QcepDataGroup::array(QString path)
{
  QcepDataObjectPtr obj = item(path);

  return qSharedPointerDynamicCast<QcepDataArray>(obj);
}

QcepDataColumnPtr QcepDataGroup::column(QString path)
{
  QcepDataObjectPtr obj = item(path);

  return qSharedPointerDynamicCast<QcepDataColumn>(obj);
}

QcepDataColumnScanPtr QcepDataGroup::columnScan(QString path)
{
  QcepDataObjectPtr obj = item(path);

  return qSharedPointerDynamicCast<QcepDataColumnScan>(obj);
}

QString QcepDataGroup::directoryName(QString path)
{
  QFileInfo info(path);

  if (info.isAbsolute()) {
    return info.dir().absolutePath();
  } else {
    return info.dir().path();
  }
}

QString QcepDataGroup::object(QString path)
{
  QFileInfo info(path);

  return info.fileName();
}

QcepDataGroupPtr QcepDataGroup::containingGroup(QString path)
{
  QFileInfo info(path);

  if (info.isAbsolute()) {
    if (parentItem()) {
      return rootItem()->containingGroup(path);
    } else {
      QcepDataObjectPtr obj = referencedObject(path);

      return qSharedPointerDynamicCast<QcepDataGroup>(obj);
    }
  } else {
    QcepDataObjectPtr obj = item(path);

    return qSharedPointerDynamicCast<QcepDataGroup>(obj);
  }
}

QcepDataObjectPtr QcepDataGroup::referencedObject(QString path)
{
  QFileInfo info(path);

  if (info.isAbsolute()) {
    return rootItem()->item(path);
  } else {
    return item(path);
  }
}

void QcepDataGroup::append(QcepDataObjectPtr obj)
{
  if (obj) {
    m_Objects.append(obj);

    QcepDataGroupPtr me = qSharedPointerDynamicCast<QcepDataGroup>(sharedFromThis());

    if (me) {
      obj -> setParentItem(me);
    } else {
      printf("Can't cast to QcepDataGroupPtr");
    }

    connect(obj.data(), SIGNAL(dataObjectChanged()), this, SIGNAL(dataObjectChanged()));

    emit dataObjectChanged();
  }
}

void QcepDataGroup::append(QString path, QcepDataObjectPtr obj)
{
  QcepDataGroupPtr group = containingGroup(path);

  if (group) {
    group->append(obj);
  }
}

void QcepDataGroup::remove(QcepDataObjectPtr obj)
{
  int n = m_Objects.indexOf(obj);

  if (n >= 0) {
    m_Objects.remove(n);

    emit dataObjectChanged();
  }
}

void QcepDataGroup::remove(QString path)
{
  QcepDataObjectPtr obj = referencedObject(path);

  if (obj) {
    QcepDataGroupPtr parent = obj->parentItem();

    if (parent) {
      parent->remove(obj);
    }
  }
}

QcepDataGroupPtr QcepDataGroup::createGroup(QString path)
{
  QcepDataGroupPtr gr = group(path);

  if (gr) {
    return gr;
  } else {
    QcepDataObjectPtr obj = item(path);

    if (obj) {
      printMessage(tr("Item %1 exists and is not a data group").arg(path));
    } else {
      QcepDataGroupPtr sgr = createGroup(directoryName(path));

      if (sgr) {
        QcepDataGroupPtr ng =
            QcepDataGroupPtr(new QcepDataGroup(saver(), object(path)));

        if (ng) {
          sgr->append(ng);

          return group(path);
        }
      }
    }
  }

  return QcepDataGroupPtr();
}

QcepDataGroupPtr QcepDataGroup::newGroup(QString path)
{
  QcepDataGroupPtr group = createGroup(directoryName(path));

  if (group) {
    QcepDataGroupPtr ng =
        QcepDataGroupPtr(new QcepDataGroup(saver(), object(path)));

    if (ng) {
      group->append(ng);

      emit dataObjectChanged();

      return ng;
    }
  }

  return QcepDataGroupPtr();
}

QcepDataArrayPtr QcepDataGroup::newArray(QString path, QVector<int> dims)
{
  QcepDataGroupPtr group = createGroup(directoryName(path));

  if (group) {
    QcepDataArrayPtr array(new QcepDataArray(saver(), object(path), dims));

    if (array) {
      group->append(array);

      emit dataObjectChanged();

      return array;
    }
  }

  return QcepDataArrayPtr();
}

QcepDataColumnPtr QcepDataGroup::newColumn(QString path, int nrows)
{
  QcepDataGroupPtr group = createGroup(directoryName(path));

  if (group) {
    QcepDataColumnPtr column(new QcepDataColumn(saver(), object(path), nrows));

    if (column) {
      group->append(column);

      emit dataObjectChanged();

      return column;
    }
  }

  return QcepDataColumnPtr();
}

QcepDataColumnScanPtr QcepDataGroup::newColumnScan(QString path, int nrow, QStringList cols)
{
  QcepDataGroupPtr group = createGroup(directoryName(path));

  if (group) {
    QcepDataColumnScanPtr scan(QcepDataColumnScan::newDataColumnScan(saver(), object(path), cols, nrow));

    if (scan) {
      group->append(scan);

      emit dataObjectChanged();

      return scan;
    }
  }

  return QcepDataColumnScanPtr();
}

QScriptValue QcepDataGroup::toGroupScriptValue(QScriptEngine *engine, const QcepDataGroupPtr &data)
{
  return engine->newQObject(data.data());
}

void QcepDataGroup::fromGroupScriptValue(const QScriptValue &obj, QcepDataGroupPtr &data)
{
  QObject *qobj = obj.toQObject();

  if (qobj) {
    QcepDataGroup *qdobj = qobject_cast<QcepDataGroup*>(qobj);

    if (qdobj) {
      QcepDataObjectPtr p = qdobj->sharedFromThis();

      if (p) {
        QcepDataGroupPtr cs = qSharedPointerDynamicCast<QcepDataGroup>(p);

        if (cs) {
          data = cs;
        }
      }
    }
  }
}

