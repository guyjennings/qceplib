#ifndef QCEPSETRANGEOFIMAGECOMMAND_H
#define QCEPSETRANGEOFIMAGECOMMAND_H

#include "qceplib_global.h"
#include "qcepobject.h"
#include "qcepimagedata-ptr.h"

class QCEP_EXPORT QcepSetRangeOfImageCommand : public QcepObject
{
  Q_OBJECT

public:
  Q_INVOKABLE QcepSetRangeOfImageCommand(QString name);

public slots:
  void onImageAvailable(QcepDoubleImageDataPtr img);
  QcepDoubleImageDataPtr exec(QcepDoubleImageDataPtr img);

signals:
  void processedImageAvailable(QcepDoubleImageDataPtr res);
  void progressMade(int pct);

public:
  Q_PROPERTY(int rangeChoice READ get_RangeChoice WRITE set_RangeChoice)
  QCEP_INTEGER_PROPERTY(RangeChoice)

  Q_PROPERTY(int outputChoice READ get_OutputChoice WRITE set_OutputChoice)
  QCEP_INTEGER_PROPERTY(OutputChoice)

  Q_PROPERTY(double minimum READ get_Minimum WRITE set_Minimum)
  QCEP_DOUBLE_PROPERTY(Minimum)

  Q_PROPERTY(double maximum READ get_Maximum WRITE set_Maximum)
  QCEP_DOUBLE_PROPERTY(Maximum)

  Q_PROPERTY(double newValue READ get_NewValue WRITE set_NewValue)
  QCEP_DOUBLE_PROPERTY(NewValue)
};

Q_DECLARE_METATYPE(QcepSetRangeOfImageCommand*)

#endif // QCEPSETRANGEOFIMAGECOMMAND_H
