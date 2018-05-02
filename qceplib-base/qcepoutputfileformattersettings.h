#ifndef QCEPOUTPUTFILEFORMATTERSETTINGS_H
#define QCEPOUTPUTFILEFORMATTERSETTINGS_H

#include "qceplib_global.h"
#include "qcepobject.h"
#include "qcepproperty.h"
#include "qcepimagedata-ptr.h"
#include "qcepoutputfileformatter-ptr.h"

class QCEP_EXPORT QcepOutputFileFormatterSettings : public QcepObject
{
  Q_OBJECT

private:
  typedef QcepObject inherited;

public:
  Q_INVOKABLE QcepOutputFileFormatterSettings(QString name);
  ~QcepOutputFileFormatterSettings();

  void initialize(QcepObjectWPtr parent);

//  void saveImageData(QString              name,
//                     QcepImageDataBasePtr img,
//                     QcepImageDataBasePtr overflow,
//                     int                  canOverwrite);

  void saveImageData(QcepImageDataBasePtr img,
                     QcepImageDataBasePtr overflow);

  void incBacklog();
  void decBacklog();

private:
  QcepOutputFileFormatterPtr newOutputFormatter(QString name);

public:
  enum {
    OutputFormatTIFF,
    OutputFormatHDF,
    OutputFormatTEXT
  };

  enum {
    OutputCompressionNone,
    OutputCompressionZIP,
    OutputCompressionGZIP,
    OutputCompressionBZIP2
  };

public: // Properties
  Q_PROPERTY(int outputFormat READ get_OutputFormat WRITE set_OutputFormat)
  QCEP_INTEGER_PROPERTY(OutputFormat)

  Q_PROPERTY(int compressFormat READ get_CompressFormat WRITE set_CompressFormat)
  QCEP_INTEGER_PROPERTY(CompressFormat)

  Q_PROPERTY(int compressLevel READ get_CompressLevel WRITE set_CompressLevel)
  QCEP_INTEGER_PROPERTY(CompressLevel)
};

#endif // QCEPOUTPUTFILEFORMATTERSETTINGS_H
