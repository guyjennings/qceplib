#ifndef QCEPSPECSERVERSETTINGS_H
#define QCEPSPECSERVERSETTINGS_H

#include "qceplib_global.h"
#include "qcepobject.h"
#include "qcepproperty.h"

class QCEP_EXPORT QcepSpecServerSettings : public QcepObject
{
  Q_OBJECT

private:
  typedef QcepObject inherited;

public:
  Q_INVOKABLE QcepSpecServerSettings(QString name);
  ~QcepSpecServerSettings();

  void initialize(QcepObjectWPtr parent);

public:
  Q_PROPERTY(int    runSpecServer    READ get_RunSpecServer WRITE set_RunSpecServer)
  QCEP_INTEGER_PROPERTY(RunSpecServer)

  Q_PROPERTY(int    specServerPort    READ get_SpecServerPort WRITE set_SpecServerPort)
  QCEP_INTEGER_PROPERTY(SpecServerPort)
};

Q_DECLARE_METATYPE(QcepSpecServerSettings*)

#endif // QCEPSPECSERVERSETTINGS_H
