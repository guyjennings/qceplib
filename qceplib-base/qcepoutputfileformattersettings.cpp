#include "qcepoutputfileformattersettings.h"
#include "qcepoutputfileformatter.h"
#include "qcepoutputfileformatter-ptr.h"
#include <QtConcurrentRun>
#include "qcepimagedata.h"
#include "qcepoutputfileformatterhdf.h"
#include "qcepoutputfileformattertiff.h"

QcepOutputFileFormatterSettings::QcepOutputFileFormatterSettings(QString name)
  : inherited(name),
    m_OutputFormat  (this, "outputFormat",   OutputFormatTIFF,      "Output Format"),
    m_CompressFormat(this, "compressFormat", OutputCompressionNone, "Output Compression Format"),
    m_CompressLevel (this, "compressLevel",  3,                     "Output Compression Level")
{
}

QcepOutputFileFormatterSettings::~QcepOutputFileFormatterSettings()
{
}

void QcepOutputFileFormatterSettings::initialize(QcepObjectWPtr parent)
{
  inherited::initialize(parent);
}

void QcepOutputFileFormatterSettings::saveImageData(QString              name,
                                                    QcepImageDataBasePtr img,
                                                    QcepImageDataBasePtr overflow,
                                                    int                  canOverwrite)
{
  QcepOutputFileFormatterSettingsPtr set =
      qSharedPointerDynamicCast<QcepOutputFileFormatterSettings>(sharedFromThis());

  QcepOutputFileFormatterPtr fmt = newOutputFormatter("formatter");

  incBacklog();

  QtConcurrent::run([=]() { fmt -> saveImageData(set, name, img, overflow, canOverwrite); } );
}

void QcepOutputFileFormatterSettings::saveImageData(QcepImageDataBasePtr img,
                                                    QcepImageDataBasePtr overflow)
{
  QcepOutputFileFormatterSettingsPtr set =
      qSharedPointerDynamicCast<QcepOutputFileFormatterSettings>(sharedFromThis());

  QcepOutputFileFormatterPtr fmt = newOutputFormatter("formatter");

  incBacklog();

  QtConcurrent::run([=]() { fmt -> saveImageData(set, img, overflow); } );
}

QcepOutputFileFormatterPtr QcepOutputFileFormatterSettings::newOutputFormatter(QString name)
{
  QcepOutputFileFormatterPtr res;

  switch (get_OutputFormat()) {
  case OutputFormatTIFF:
    res = QcepOutputFileFormatterPtr(
          NEWPT2(QcepOutputFileFormatterTIFF(name)));
    break;

  case OutputFormatHDF:
    res = QcepOutputFileFormatterPtr(
          NEWPT2(QcepOutputFileFormatterHDF(name)));
    break;
  }

  if (res) {
    res -> initialize(sharedFromThis());
  }

  return res;
}

void QcepOutputFileFormatterSettings::incBacklog()
{
}

void QcepOutputFileFormatterSettings::decBacklog()
{
}
