#ifndef QCEPSIMPLESERVER_H
#define QCEPSIMPLESERVER_H

#include "qceplib_global.h"
#include "qcepobject.h"

class QCEP_EXPORT QcepSimpleServer : public QcepObject
{
  Q_OBJECT

private:
  typedef QcepObject inherited;

public:
  Q_INVOKABLE QcepSimpleServer(QString name);
  ~QcepSimpleServer();

  void initialize(QcepObjectWPtr parent);

public:
};

#endif // QCEPSIMPLESERVER_H
