#ifndef QCEPOUTPUTFILEFORMATTERHDF_H
#define QCEPOUTPUTFILEFORMATTERHDF_H

#include "qceplib_global.h"
#include "qcepobject.h"

#include "qcepimagedata-ptr.h"
#include "qcepmaskdata-ptr.h"
#include "qcepoutputfileformattersettings-ptr.h"
#include "qcepoutputfileformatter.h"

class QCEP_EXPORT QcepOutputFileFormatterHDF : public QcepOutputFileFormatter
{
  Q_OBJECT

private:
  typedef QcepOutputFileFormatter inherited;

public:
  Q_INVOKABLE QcepOutputFileFormatterHDF(QString name);

  void saveImageData(QcepOutputFileFormatterSettingsWPtr set,
                     QcepImageDataBasePtr               img,
                     QcepImageDataBasePtr               overflow);
};

#endif // QCEPOUTPUTFILEFORMATTERHDF_H
