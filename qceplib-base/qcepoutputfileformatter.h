#ifndef QCEPOUTPUTFILEFORMATTER_H
#define QCEPOUTPUTFILEFORMATTER_H

#include "qceplib_global.h"
#include "qcepobject.h"

#include "qcepimagedata-ptr.h"
#include "qcepmaskdata-ptr.h"
#include "qcepoutputfileformattersettings-ptr.h"
#include <sstream>

class QCEP_EXPORT QcepOutputFileFormatter : public QcepObject
{
  Q_OBJECT

private:
  typedef QcepObject inherited;

public:
  QcepOutputFileFormatter(QString name);
  ~QcepOutputFileFormatter();

  void initialize(QcepObjectWPtr parent);

//  virtual void saveImageData(QcepOutputFileFormatterSettingsWPtr set,
//                            QString                             name,
//                            QcepImageDataBasePtr                img,
//                            QcepImageDataBasePtr                overflow,
//                            int                                 canOverwrite);

  virtual void saveImageData(QcepOutputFileFormatterSettingsWPtr set,
                            QcepImageDataBasePtr                img,
                            QcepImageDataBasePtr                overflow) = 0;
protected:
  virtual QString fileExtension() = 0;

  void    mkPath           (QString filePath);
  QString uniqueFileName   (QcepImageDataBasePtr      data);

  void beginSaveImageData(QcepOutputFileFormatterSettingsWPtr settings,
                          QcepImageDataBasePtr                img,
                          QcepImageDataBasePtr                overflow);

  void compressOutputData();
  void compressOutputDataBzip2();
  void compressOutputDataGzip();
  void compressOutputDataZip();

protected:
  QTime                               m_Tic;
  int                                 m_Compression;
  int                                 m_CompressionLevel;
  QcepOutputFileFormatterSettingsWPtr m_Settings;
  QString                             m_FileName;
  std::ostringstream                  m_OutputStream;
  const char*                         m_OutputBuffer;
  int                                 m_OutputCount;
  QcepImageDataBasePtr                m_Image;
  int                                 m_NRows;
  int                                 m_NCols;
};

#endif // QCEPOUTPUTFILEFORMATTER_H
