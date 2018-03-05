#include "qcepobjectpropertiesmodel.h"
#include "qcepobject.h"
#include <QMetaProperty>

QcepObjectPropertiesModel::QcepObjectPropertiesModel(QObject *parent, QcepObjectWPtr obj)
  : QAbstractTableModel(parent)
{
}

QVariant QcepObjectPropertiesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  QVariant res = QVariant();

  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      res = "#";
      break;

    case 1:
      res = "Property";
      break;

    case 2:
      res = "Value";
      break;
    }
  }

  return res;
}

QModelIndex QcepObjectPropertiesModel::index(int row, int column, const QModelIndex &parent) const
{
  // TODO: Implement me!

  return createIndex(row, column);
}

//QModelIndex QcepObjectPropertiesModel::parent(const QModelIndex &index) const
//{
//  // TODO: Implement me!

//  return QModelIndex();
//}

int QcepObjectPropertiesModel::rowCount(const QModelIndex &parent) const
{
  int res = 0;

  QcepObjectPtr obj(m_Object);

  // TODO: Implement me!

  if (obj) {
    const QMetaObject *meta = obj->metaObject();

    int count = meta->propertyCount();
    int offset = QObject::staticMetaObject.propertyCount();

    res = count-offset;
  }

  return res;
}

int QcepObjectPropertiesModel::columnCount(const QModelIndex &parent) const
{
//  if (!parent.isValid())
//    return 0;

  // TODO: Implement me!

  return 3;
}

QVariant QcepObjectPropertiesModel::data(const QModelIndex &index, int role) const
{
  QVariant res;

  if (index.isValid()) {
    QcepObjectPtr obj(m_Object);

    if (obj && role == Qt::DisplayRole) {
      const QMetaObject *meta = obj->metaObject();
      int count  = meta->propertyCount();
      int offset = QObject::staticMetaObject.propertyCount();
      int col    = index.column();
      int row    = index.row();
      QMetaProperty metaproperty = meta->property(row+offset);

      switch (col) {
      case 0:
        res = tr("%1").arg(index.row());
        break;

      case 1:
        res = metaproperty.name();
        break;

      case 2:
        res = convertToString(obj->property(metaproperty.name()));
        break;
      }
    }
  }

  return res;
}

QString QcepObjectPropertiesModel::convertToString(QVariant val) const
{
  QString res;

  if (val.canConvert(QMetaType::QRect)) {
    QRect r = val.toRect();

    res = tr("[%1,%2,%3,%4]")
        .arg(r.left())
        .arg(r.top())
        .arg(r.right())
        .arg(r.bottom());
  } else if (val.canConvert(QMetaType::QRectF)) {
    QRectF r = val.toRectF();

    res = tr("[%1,%2,%3,%4]")
        .arg(r.left())
        .arg(r.top())
        .arg(r.right())
        .arg(r.bottom());
  } else {
    res = val.toString();
  }

  return res;
}
void QcepObjectPropertiesModel::deselect()
{
  beginResetModel();

  m_Object = QcepObjectWPtr();

  endResetModel();
}

void QcepObjectPropertiesModel::select(QcepObjectWPtr obj)
{
  beginResetModel();

  m_Object = obj;

  endResetModel();
}
