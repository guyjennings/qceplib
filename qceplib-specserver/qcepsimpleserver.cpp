#include "qcepsimpleserver.h"
#include "qcepsimpleserversettings.h"

QcepSimpleServer::QcepSimpleServer(QString name)
  : inherited(name)
{

}

QcepSimpleServer::~QcepSimpleServer()
{
}

void QcepSimpleServer::initialize(QcepObjectWPtr               parent,
                                  QcepSimpleServerSettingsWPtr settings)
{
  inherited::initialize(parent);
}
