#include "qcepsimpleserversettings.h"

QcepSimpleServerSettings::QcepSimpleServerSettings(QString name)
  : inherited(name),
    m_RunSimpleServer(this,"runSimpleServer", 1, "Run Simple Socket Server?"),
    m_SimpleServerPort(this,"simpleServerPort", 1234, "Port for Simple Socket Server")
{
  if (qcepDebug(DEBUG_CONSTRUCTORS)) {
    printf("QcepSimpleServerSettings::QcepSimpleServerSettings(%p)\n", this);
  }
}

QcepSimpleServerSettings::~QcepSimpleServerSettings()
{
  if (qcepDebug(DEBUG_CONSTRUCTORS)) {
    printf("QcepSimpleServerSettings::~QcepSimpleServerSettings(%p)\n", this);
  }
}

void QcepSimpleServerSettings::initialize(QcepObjectWPtr parent)
{
  inherited::initialize(parent);
}
