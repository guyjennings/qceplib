#include "qcepoutputfileformattertiff.h"
#include "qcepimagedata.h"
#include "qcepoutputfileformattersettings.h"
#include "tiffio.h"
#include "qcepimagedataformattiff.h"

QcepOutputFileFormatterTIFF::QcepOutputFileFormatterTIFF(QString name)
  : inherited(name)
{
}

void QcepOutputFileFormatterTIFF::saveImageData(QcepOutputFileFormatterSettingsPtr set,
                                                QcepImageDataBasePtr               img,
                                                QcepImageDataBasePtr               overflow)
{
  if (img && set) {
    m_Tic.start();
    m_Settings = set;
    m_Image = img;
    m_NRows = m_Image -> get_Height();
    m_NCols = m_Image -> get_Width();
    m_Compression      = m_Settings -> get_CompressFormat();
    m_CompressionLevel = m_Settings -> get_CompressLevel();

    QcepDoubleImageDataPtr dimage = qSharedPointerDynamicCast<QcepDoubleImageData>(img);

    if (dimage) {
      saveDoubleData(set, dimage, overflow);
    } else {
      QcepUInt32ImageDataPtr i32image = qSharedPointerDynamicCast<QcepUInt32ImageData>(img);

      if (i32image) {
        saveInt32Data(set, i32image, overflow);
      } else {
        QcepUInt16ImageDataPtr i16image = qSharedPointerDynamicCast<QcepUInt16ImageData>(img);

        if (i16image) {
          saveInt16Data(set, i16image, overflow);
        } else {
          criticalMessage("QcepOutputFileFormatterTIFF::saveImageData: unkown image type");
        }
      }
    }
  }

  if (set) {
    set -> decBacklog();
  }
}

#define TIFFCHECK(a) tiffCheck((a), __FILE__, __LINE__)

void QcepOutputFileFormatterTIFF::saveDoubleData(QcepOutputFileFormatterSettingsPtr set,
                                                 QcepDoubleImageDataPtr             dimg,
                                                 QcepImageDataBasePtr               overflow)
{
  beginOutputData(32, SAMPLEFORMAT_IEEEFP);

  QVector<float> buffvec(m_NCols);
  float* buffer = buffvec.data();

  for (int y=0; y<m_NRows; y++) {
    for (int x=0; x<m_NCols; x++) {
      buffer[x] = dimg->value(x,y);
    }

    TIFFCHECK(qcepTIFFWriteScanline(m_OutputTIFF, buffer, y, 0));
  }

  endOutputData();
}

void QcepOutputFileFormatterTIFF::saveInt16Data (QcepOutputFileFormatterSettingsPtr set,
                                                 QcepUInt16ImageDataPtr             dimg,
                                                 QcepImageDataBasePtr               overflow)
{
  beginOutputData(16, SAMPLEFORMAT_UINT);

  QVector<quint16> buffvec(m_NCols);
  quint16* buffer = buffvec.data();

  for (int y=0; y<m_NRows; y++) {
    for (int x=0; x<m_NCols; x++) {
      buffer[x] = dimg->value(x,y);
    }

    TIFFCHECK(qcepTIFFWriteScanline(m_OutputTIFF, buffer, y, 0));
  }

  endOutputData();
}

void QcepOutputFileFormatterTIFF::saveInt32Data (QcepOutputFileFormatterSettingsPtr set,
                                                 QcepUInt32ImageDataPtr             dimg,
                                                 QcepImageDataBasePtr               overflow)
{
  beginOutputData(32, SAMPLEFORMAT_UINT);

  QVector<quint32> buffvec(m_NCols);
  quint32* buffer = buffvec.data();

  for (int y=0; y<m_NRows; y++) {
    for (int x=0; x<m_NCols; x++) {
      buffer[x] = dimg->value(x,y);
    }

    TIFFCHECK(qcepTIFFWriteScanline(m_OutputTIFF, buffer, y, 0));
  }

  endOutputData();
}

void QcepOutputFileFormatterTIFF::tiffCheck(int stat, const char *file, int line)
{
  if (stat < 0) {
    printMessage(tr("TIFF Error %1 : File \"%2\", Line %3").arg(stat).arg(file).arg(line));
  }
}

void QcepOutputFileFormatterTIFF::beginOutputData(int nBits, int pixFormat)
{
  switch(m_Compression) {
  case QcepOutputFileFormatterSettings::OutputCompressionNone:
    m_Image -> set_FileExtension(".tif");
    break;

  case QcepOutputFileFormatterSettings::OutputCompressionBZIP2:
    m_Image -> set_FileExtension(".tif.bz2");
    break;

  case QcepOutputFileFormatterSettings::OutputCompressionGZIP:
    m_Image -> set_FileExtension(".tif.gz");
    break;

  case QcepOutputFileFormatterSettings::OutputCompressionZIP:
    m_Image -> set_FileExtension(".tif.zip");
    break;
  }

  m_FileName = uniqueFileName(m_Image);

  mkPath(m_FileName);

  printMessage(tr("Starting to save data in file \"%1\"").arg(m_FileName));

  if (m_Compression == 0) {
    m_OutputTIFF = qcepTIFFOpen(qPrintable(m_FileName), "w");
  } else {
    m_OutputTIFF = qcepTIFFStreamOpen(qPrintable(m_FileName), &m_OutputStream);
  }

  if (m_OutputTIFF) {
    TIFFCHECK(qcepTIFFSetField(m_OutputTIFF, TIFFTAG_IMAGEWIDTH,      m_NCols));
    TIFFCHECK(qcepTIFFSetField(m_OutputTIFF, TIFFTAG_IMAGELENGTH,     m_NRows));
    TIFFCHECK(qcepTIFFSetField(m_OutputTIFF, TIFFTAG_SAMPLESPERPIXEL, 1));

    TIFFCHECK(qcepTIFFSetField(m_OutputTIFF, TIFFTAG_PLANARCONFIG,    PLANARCONFIG_CONTIG));
    TIFFCHECK(qcepTIFFSetField(m_OutputTIFF, TIFFTAG_BITSPERSAMPLE,   nBits));
    TIFFCHECK(qcepTIFFSetField(m_OutputTIFF, TIFFTAG_SAMPLEFORMAT,    pixFormat));

    TIFFCHECK(qcepTIFFSetField(m_OutputTIFF, TIFFTAG_DOCUMENTNAME, qPrintable(m_Image->get_FileName())));
    TIFFCHECK(qcepTIFFSetField(m_OutputTIFF, TIFFTAG_DATETIME,     qPrintable(m_Image->get_DateTime().toString("yyyy:MM:dd hh:mm:ss"))));
  }
}

void QcepOutputFileFormatterTIFF::endOutputData()
{
  if (m_OutputTIFF) {
    qcepTIFFClose(m_OutputTIFF);
  }

  if (m_Compression) {
    printMessage(tr("Started compressing data in file \"%1\" after %2 msec")
                 .arg(m_FileName).arg(m_Tic.elapsed()));

    const std::string& tmp = m_OutputStream.str();
    m_OutputBuffer = tmp.c_str();
    m_OutputCount  = tmp.length();

    compressOutputData();
  }

  m_Image -> set_ObjectSaved(true);
  m_Image -> saveMetaData(m_FileName);

  //TODO: save overflow data?
  //TODO: update estimated time

  printMessage(tr("Saved data in file \"%1\" after %2 msec")
               .arg(m_FileName).arg(m_Tic.elapsed()));
}

void QcepOutputFileFormatterTIFF::compressOutputData()
{
  switch (m_Compression) {
  case QcepOutputFileFormatterSettings::OutputCompressionNone:
    break;

  case QcepOutputFileFormatterSettings::OutputCompressionBZIP2:
    compressOutputDataBzip2();
    break;

  case QcepOutputFileFormatterSettings::OutputCompressionGZIP:
    compressOutputDataGzip();
    break;

  case QcepOutputFileFormatterSettings::OutputCompressionZIP:
    compressOutputDataZip();
    break;
  }
}