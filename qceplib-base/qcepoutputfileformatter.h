#ifndef QCEPOUTPUTFILEFORMATTER_H
#define QCEPOUTPUTFILEFORMATTER_H

#include "qceplib_global.h"
#include "qcepobject.h"

#include "qcepimagedata-ptr.h"
#include "qcepmaskdata-ptr.h"
#include "qcepoutputfileformattersettings-ptr.h"

class QCEP_EXPORT QcepOutputFileFormatter : public QcepObject
{
  Q_OBJECT

private:
  typedef QcepObject inherited;

public:
  QcepOutputFileFormatter(QString name);
  ~QcepOutputFileFormatter();

  void initialize(QcepObjectWPtr parent);

  virtual void saveImageData(QcepOutputFileFormatterSettingsPtr set,
                            QString                             name,
                            QcepImageDataBasePtr                img,
                            QcepImageDataBasePtr                overflow,
                            int                                 canOverwrite);

  virtual void saveImageData(QcepOutputFileFormatterSettingsPtr set,
                            QcepImageDataBasePtr                img,
                            QcepImageDataBasePtr                overflow) = 0;

protected:
  void    mkPath           (QString filePath);
  QString uniqueFileName   (QcepImageDataBasePtr      data);
};

#endif // QCEPOUTPUTFILEFORMATTER_H
