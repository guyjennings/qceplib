#ifndef QCEPOUTPUTFILEFORMATTERTEXT_H
#define QCEPOUTPUTFILEFORMATTERTEXT_H

#include "qceplib_global.h"
#include "qcepobject.h"

#include "qcepimagedata-ptr.h"
#include "qcepmaskdata-ptr.h"
#include "qcepoutputfileformattersettings-ptr.h"
#include "qcepoutputfileformatter.h"
#include <sstream>

class QCEP_EXPORT QcepOutputFileFormatterTEXT : public QcepOutputFileFormatter
{
  Q_OBJECT

private:
  typedef QcepOutputFileFormatter inherited;

public:
  Q_INVOKABLE QcepOutputFileFormatterTEXT(QString name);

  void saveImageData(QcepOutputFileFormatterSettingsWPtr settings,
                     QcepImageDataBasePtr                img,
                     QcepImageDataBasePtr                overflow);
private:
  QTime                               m_Tic;
  int                                 m_Compression;
  int                                 m_CompressionLevel;
  QcepOutputFileFormatterSettingsWPtr m_Settings;
  QString                             m_FileName;
  std::ostringstream                  m_OutputStream;
  const char*                         m_OutputBuffer;
  int                                 m_OutputCount;
  FILE*                               m_OutputFile;
  QcepImageDataBasePtr                m_Image;
  int                                 m_NRows;
  int                                 m_NCols;

private:
  QString fileExtension();
};

#endif // QCEPOUTPUTFILEFORMATTERTEXT_H
