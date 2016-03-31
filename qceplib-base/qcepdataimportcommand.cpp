#include "qcepdataimportcommand.h"

QcepDataImportCommand::QcepDataImportCommand(
    QcepDatasetModelPtr model, const QModelIndexList &idx) :
  QcepObject("dataExport", NULL),
  m_Model(model),
  m_Indexes(idx)
{
}