#ifndef QCEPSIMPLESERVERSETTINGS_H
#define QCEPSIMPLESERVERSETTINGS_H

#include "qceplib_global.h"
#include "qcepobject.h"
#include "qcepproperty.h"

class QCEP_EXPORT QcepSimpleServerSettings : public QcepObject
{
  Q_OBJECT

private:
  typedef QcepObject inherited;

public:
  Q_INVOKABLE QcepSimpleServerSettings(QString name);
  ~QcepSimpleServerSettings();

  void initialize(QcepObjectWPtr parent);
};

#endif // QCEPSIMPLESERVERSETTINGS_H
