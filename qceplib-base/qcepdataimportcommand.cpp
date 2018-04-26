#include "qcepdataimportcommand.h"
#include "qcepdatasetmodel.h"
#include "qcepexperiment.h"
#include "qcepdataimportparameters.h"
#include "qcepdataimportdialog.h"
#include "qcepfileimporter.h"
#include "qcepallocator.h"
#include <QtConcurrentRun>

QcepDataImportCommand::QcepDataImportCommand(QcepDatasetModelWPtr model,
                                             const QModelIndexList &idx,
                                             QStringList files) :
  inherited("dataImport"),
  m_Model(model),
  m_Indexes(idx),
  m_Files(files)
{
  QcepDatasetModelPtr dsm(m_Model);

  if (dsm) {
    m_Experiment = dsm->experiment();

    QcepExperimentPtr expt(m_Experiment);

    if (expt) {
      m_Parameters = expt->dataImportParameters();

      m_ImportedData =
          QcepAllocator::newDataset(sharedFromThis(), "import");

      m_ImportedDataset =
          QcepDatasetModelPtr(
            NEWPTR(QcepDatasetModel(m_Experiment, m_ImportedData)));

      if (files.count() == 1) {
        m_FileImporter = QcepFileImporter::importFile(m_ImportedDataset,
                                                      m_ImportedIndexes,
                                                      files.value(0));

      } else {
        m_FileImporter = QcepFileImporter::importFiles(m_ImportedDataset,
                                                       m_ImportedIndexes,
                                                       files);
      }
    }
  }
}

bool QcepDataImportCommand::exec()
{
  bool res = false;
  QcepDataImportDialog dlog(m_ImportedDataset,
                            m_ImportedIndexes,
                            m_Model,
                            m_Indexes,
                            m_Files,
                            m_Experiment,
                            m_Parameters);

  if (m_FileImporter) {
    CONNECT_CHECK(
          connect(m_FileImporter.data(), &QcepFileImporter::importProgress,
                  &dlog, &QcepDataImportDialog::importProgress));

    CONNECT_CHECK(
          connect(m_FileImporter.data(), &QcepFileImporter::importCompleted,
                  &dlog, &QcepDataImportDialog::importCompleted));
  }

  QtConcurrent::run(m_FileImporter.data(), &QcepFileImporter::exec);

  if (dlog.exec() == QDialog::Accepted) {
    copyResults();

    res = true;
  }

  return false;
}

void QcepDataImportCommand::copyResults()
{
  QcepDatasetModelPtr model(m_Model);

  if (model) {
    foreach (QModelIndex idx, m_ImportedIndexes) {
      QcepDataObjectPtr obj = m_ImportedDataset->indexedObject(idx);

      model->append(m_Indexes.value(0), obj);
    }
  }
}
