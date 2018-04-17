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

public:
  Q_PROPERTY(int    runSimpleServer    READ get_RunSimpleServer WRITE set_RunSimpleServer)
  QCEP_INTEGER_PROPERTY(RunSimpleServer)

  Q_PROPERTY(int    simpleServerPort    READ get_SimpleServerPort WRITE set_SimpleServerPort)
  QCEP_INTEGER_PROPERTY(SimpleServerPort)
};

Q_DECLARE_METATYPE(QcepSimpleServerSettings*)

#endif // QCEPSIMPLESERVERSETTINGS_H
