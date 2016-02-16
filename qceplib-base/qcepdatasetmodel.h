#ifndef QCEPDATASETMODEL_H
#define QCEPDATASETMODEL_H

#include <QAbstractItemModel>
#include "qcepdataset-ptr.h"
#include "qcepdataset.h"
#include "qcepdataobject-ptr.h"
#include "qcepdataobject.h"
#include "qcepdatagroup-ptr.h"
#include "qcepdatagroup.h"
#include "qcepdataarray-ptr.h"
#include "qcepdataarray.h"
#include "qcepdatacolumn-ptr.h"
#include "qcepdatacolumn.h"
#include "qcepdatacolumnscan-ptr.h"
#include "qcepdatacolumnscan.h"
#include "qcepimagedata-ptr.h"
#include "qcepimagedata.h"
#include "qcepintegrateddata-ptr.h"
#include "qcepintegrateddata.h"

class QcepDatasetModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  QcepDatasetModel(QcepDatasetWPtr ds);

public slots:
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
  QModelIndex index(int row, int column, const QcepDataObjectPtr &obj) const;
  QModelIndex parent(const QModelIndex &index) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  Qt::ItemFlags flags(const QModelIndex &index) const;

  QcepDataObjectPtr indexedObject(const QModelIndex& index) const;

  QStringList mimeTypes() const;
  QMimeData  *mimeData(const QModelIndexList &indexes) const;

  bool insertRows(int row, int count, const QModelIndex &parent);
  bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild);
  bool removeRows(int row, int count, const QModelIndex &parent);

public slots:
  QcepDataObjectPtr      item(const QModelIndex &index);
  QcepDataObjectPtr      item(QString path);
  QcepDataObjectPtr      item(int n);

  QcepDataGroupPtr       group(const QModelIndex &index);
  QcepDataGroupPtr       group(QString path);
  QcepDataGroupPtr       group(int n);
  QcepDataGroupPtr       newGroup(QString path);

  QcepDataArrayPtr       array(const QModelIndex &index);
  QcepDataArrayPtr       array(QString path);
  QcepDataArrayPtr       array(int n);
  QcepDataArrayPtr       newArray(QString path, QVector<int> dims = QVector<int>());

  QcepDataColumnPtr      column(const QModelIndex &index);
  QcepDataColumnPtr      column(QString path);
  QcepDataColumnPtr      column(int n);
  QcepDataColumnPtr      newColumn(QString path, int nRows=0);

  QcepDataColumnScanPtr  columnScan(const QModelIndex &index);
  QcepDataColumnScanPtr  columnScan(QString path);
  QcepDataColumnScanPtr  columnScan(int n);
  QcepDataColumnScanPtr  newColumnScan(QString path,
                                       int nRows=0, QStringList cols=QStringList());

  QcepDoubleImageDataPtr image(const QModelIndex &index);
  QcepDoubleImageDataPtr image(QString path);
  QcepDoubleImageDataPtr image(int n);
  QcepDoubleImageDataPtr newImage(QString path, int width=0, int height=0);

  QcepIntegratedDataPtr  integratedData(const QModelIndex &index);
  QcepIntegratedDataPtr  integratedData(QString path);
  QcepIntegratedDataPtr  integratedData(int n);
  QcepIntegratedDataPtr  newIntegratedData(QString path, int sz);

  void                   append(const QModelIndex &index, QcepDataObjectPtr obj);
  void                   append(QString path, QcepDataObjectPtr obj);
  void                   remove(const QModelIndex &index);
  void                   remove(QString path);

  void insertGroup(int atRow, QString name);

private slots:
  void onDataObjectChanged();

private:
  QString indexDescription(const QModelIndex& index) const;
  QString groupName(QString path);
  QString objectName(QString path);

private:
  QcepDatasetWPtr m_Dataset;
};

#endif // QCEPDATASETMODEL_H
