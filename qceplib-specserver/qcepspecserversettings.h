#ifndef QCEPSPECSERVERSETTINGS_H
#define QCEPSPECSERVERSETTINGS_H

#include "qceplib_global.h"
#include "qcepobject.h"

class QCEP_EXPORT QcepSpecServerSettings : public QcepObject
{
  Q_OBJECT

private:
  typedef QcepObject inherited;

public:
  Q_INVOKABLE QcepSpecServerSettings(QString name);
  ~QcepSpecServerSettings();

  void initialize(QcepObjectWPtr parent);
};

#endif // QCEPSPECSERVERSETTINGS_H
