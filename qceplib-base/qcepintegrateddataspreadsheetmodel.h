#ifndef QCEPINTEGRATEDDATASPREADSHEETMODEL_H
#define QCEPINTEGRATEDDATASPREADSHEETMODEL_H

#include "qcepintegrateddata-ptr.h"
#include "qcepspreadsheetmodel.h"

class QcepIntegratedDataSpreadsheetModel : public QcepSpreadsheetModel
{
public:
  QcepIntegratedDataSpreadsheetModel(QcepIntegratedDataWPtr integ);

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
  QcepIntegratedDataWPtr m_Integrated;
};

#endif // QCEPINTEGRATEDDATASPREADSHEETMODEL_H
