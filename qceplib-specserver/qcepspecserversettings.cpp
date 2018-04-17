#include "qcepspecserversettings.h"

QcepSpecServerSettings::QcepSpecServerSettings(QString name)
  : inherited(name),
  m_RunSpecServer(this,"runSpecServer", 1, "Run SPEC Server?"),
  m_SpecServerPort(this,"specServerPort", -1, "Port for SPEC Server")
{
}

QcepSpecServerSettings::~QcepSpecServerSettings()
{
}

void QcepSpecServerSettings::initialize(QcepObjectWPtr parent)
{
  inherited::initialize(parent);
}
