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
#include "qcepdataprocessorbase-ptr.h"

class QcepDatasetModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  QcepDatasetModel(QcepExperimentWPtr expt,
                   QcepDataProcessorBaseWPtr proc = QcepDataProcessorBaseWPtr(),
                   QcepDatasetPtr ds = QcepDatasetPtr());

  void readSettings(QSettings *settings, QString section);
  void writeSettings(QSettings *settings, QString section);

public slots:
  virtual void printMessage(QString msg, QDateTime dt=QDateTime::currentDateTime()) const;

  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
  QModelIndex index(const QcepDataObjectPtr &obj) const;
  QModelIndex parent(const QModelIndex &index) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  QString pathName(const QModelIndex &index);

  bool setData(const QModelIndex &index, const QVariant &value, int role);

  Qt::ItemFlags flags(const QModelIndex &index) const;

  QcepDataObjectPtr indexedObject(const QModelIndex& index) const;

  QStringList mimeTypes() const;
  QMimeData  *mimeData(const QModelIndexList &indexes) const;
  bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

  bool insertRows(int row, int count, const QModelIndex &parent);
  bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild);
  bool removeRows(int row, int count, const QModelIndex &parent);

  bool insert(int row, const QModelIndex &parent, QcepDataObjectPtr obj);

//  bool insertColumns(int col, int count, const QModelIndex &parent);
//  bool moveColumns(const QModelIndex &sourceParent, int sourceCol, int count, const QModelIndex &destinationParent, int destinationChild);
//  bool removeColumns(int col, int count, const QModelIndex &parent);

  QcepExperimentWPtr        experiment();
  QcepDataProcessorBaseWPtr processor();

public slots:
  QcepDataObjectPtr      item(const QModelIndex &index);
  QcepDataObjectPtr      item(QString path);
  QcepDataObjectPtr      item(int n);

  QcepDataGroupPtr       group(const QModelIndex &index);
  QcepDataGroupPtr       group(QString path);
  QcepDataGroupPtr       group(int n);
  QcepDataGroupPtr       newGroup(QString path);
  QcepDataGroupPtr       newGroup(const QModelIndex &index, QString name);

  QcepDataArrayPtr       array(const QModelIndex &index);
  QcepDataArrayPtr       array(QString path);
  QcepDataArrayPtr       array(int n);
  QcepDataArrayPtr       newArray(QString path, QVector<int> dims = QVector<int>());
  QcepDataArrayPtr       newArray(const QModelIndex &index, QString name, QVector<int> dims = QVector<int>());

  QcepDataColumnPtr      column(const QModelIndex &index);
  QcepDataColumnPtr      column(QString path);
  QcepDataColumnPtr      column(int n);
  QcepDataColumnPtr      newColumn(QString path, int nRows=0);
  QcepDataColumnPtr      newColumn(const QModelIndex &index, QString name, int nRows=0);

  QcepDataColumnScanPtr  columnScan(const QModelIndex &index);
  QcepDataColumnScanPtr  columnScan(QString path);
  QcepDataColumnScanPtr  columnScan(int n);
  QcepDataColumnScanPtr  newColumnScan(QString path,
                                       QStringList cols=QStringList(),
                                       int nRows=0);
  QcepDataColumnScanPtr  newColumnScan(const QModelIndex &index,
                                       QString name,
                                       QStringList cols=QStringList(),
                                       int nRows=0);

  QcepDoubleImageDataPtr image(const QModelIndex &index);
  QcepDoubleImageDataPtr image(QString path);
  QcepDoubleImageDataPtr image(int n);
  QcepDoubleImageDataPtr newImage(QString path, int width=0, int height=0);
  QcepDoubleImageDataPtr newImage(const QModelIndex &index, QString name, int width=0, int height=0);

  QcepIntegratedDataPtr  integratedData(const QModelIndex &index);
  QcepIntegratedDataPtr  integratedData(QString path);
  QcepIntegratedDataPtr  integratedData(int n);
  QcepIntegratedDataPtr  newIntegratedData(QString path, int sz);
  QcepIntegratedDataPtr  newIntegratedData(const QModelIndex &index, QString path, int sz);

  QModelIndex            append(const QModelIndex &idx, QcepDataObjectPtr obj);
  QModelIndex            append(QString path, QcepDataObjectPtr obj);

  void                   remove(QcepDataObjectPtr obj);
  void                   remove(const QModelIndex &index);
  void                   remove(QString path);

  void                   concatenateData(const QModelIndex &dest, const QModelIndexList &src);
  void                   concatenateData(const QModelIndex &dest, const QModelIndex &src);
  void                   concatenateData(const QModelIndex &dest, double val);

  void                   addData(const QModelIndex &dest, const QModelIndexList &src);
  void                   addData(const QModelIndex &dest, const QModelIndex &src);
  void                   addData(const QModelIndex &dest, double val);

  void                   subtractData(const QModelIndex &dest, const QModelIndexList &src);
  void                   subtractData(const QModelIndex &dest, const QModelIndex &src);
  void                   subtractData(const QModelIndex &dest, double val);

  void                   multiplyData(const QModelIndex &dest, const QModelIndexList &src);
  void                   multiplyData(const QModelIndex &dest, const QModelIndex &src);
  void                   multiplyData(const QModelIndex &dest, double val);

  void                   divideData(const QModelIndex &dest, const QModelIndexList &src);
  void                   divideData(const QModelIndex &dest, const QModelIndex &src);
  void                   divideData(const QModelIndex &dest, double val);

  void                   integrate(const QModelIndex &src);
  void                   polarTransform(const QModelIndex &src);
  void                   polarIntegrate(const QModelIndex &src);

  bool                   integrateParameters();
  bool                   polarTransformParameters();
  bool                   polarIntegrateParameters();

  void insertGroup(int atRow, QString name);

public:
  Qt::DropActions       supportedDropActions() const;
  QString indexDescription(const QModelIndex& index) const;

private slots:
  void onDataObjectChanged();

private:
  QString groupName(QString path);
  QString objectName(QString path);

private:
  QcepExperimentWPtr        m_Experiment;
  QcepDataProcessorBaseWPtr m_Processor;
  QcepDatasetPtr            m_Dataset;
};

#endif // QCEPDATASETMODEL_H
