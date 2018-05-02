#ifndef QCEPOUTPUTFILEFORMATTERTIFF_H
#define QCEPOUTPUTFILEFORMATTERTIFF_H

#include "qceplib_global.h"
#include "qcepobject.h"

#include "qcepimagedata-ptr.h"
#include "qcepmaskdata-ptr.h"
#include "qcepoutputfileformattersettings-ptr.h"
#include "qcepoutputfileformatter.h"
#include "tiffio.h"

class QCEP_EXPORT QcepOutputFileFormatterTIFF : public QcepOutputFileFormatter
{
  Q_OBJECT

private:
  typedef QcepOutputFileFormatter inherited;

public:
  Q_INVOKABLE QcepOutputFileFormatterTIFF(QString name);

  void saveImageData(QcepOutputFileFormatterSettingsWPtr settings,
                     QcepImageDataBasePtr                img,
                     QcepImageDataBasePtr                overflow);

private:
  TIFF*              m_OutputTIFF;

  void tiffCheck(int stat, const char* file, int line);

  void beginOutputData(int nBits, int pixFormat);

  void saveDoubleData(QcepOutputFileFormatterSettingsWPtr settings,
                      QcepDoubleImageDataPtr              dimg,
                      QcepImageDataBasePtr                overflow);

  void saveInt32Data (QcepOutputFileFormatterSettingsWPtr settings,
                      QcepUInt32ImageDataPtr              i32img,
                      QcepImageDataBasePtr                overflow);

  void saveInt16Data (QcepOutputFileFormatterSettingsWPtr settings,
                      QcepUInt16ImageDataPtr              i16img,
                      QcepImageDataBasePtr                overflow);

  void endOutputData();

  QString fileExtension();
};

#endif // QCEPOUTPUTFILEFORMATTERTIFF_H
