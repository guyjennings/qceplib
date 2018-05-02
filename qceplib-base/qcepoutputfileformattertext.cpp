#include "qcepoutputfileformattertext.h"

QcepOutputFileFormatterTEXT::QcepOutputFileFormatterTEXT(QString name)
  : inherited(name)
{

}

void QcepOutputFileFormatterTEXT::saveImageData(QcepOutputFileFormatterSettingsWPtr settings,
                                                QcepImageDataBasePtr img,
                                                QcepImageDataBasePtr overflow)
{
  beginSaveImageData(settings, img, overflow);

  printMessage("QcepOutputFileFormatterTEXT::saveImageData not yet written");

  compressOutputData();
}

QString QcepOutputFileFormatterTEXT::fileExtension()
{
  return ".txt";
}
