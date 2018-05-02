#include "qcepoutputfileformatterhdf.h"

QcepOutputFileFormatterHDF::QcepOutputFileFormatterHDF(QString name)
  : inherited(name)
{

}

void QcepOutputFileFormatterHDF::saveImageData(QcepOutputFileFormatterSettingsWPtr set,
                                               QcepImageDataBasePtr               img,
                                               QcepImageDataBasePtr               overflow)
{
  beginSaveImageData(set, img, overflow);

  printMessage("QcepOutputFileFormatterHDF::saveImageData not yet written");

  compressOutputData();
}

QString QcepOutputFileFormatterHDF::fileExtension()
{
  return ".h5";
}
