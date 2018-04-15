#include "qcepstartupwindowsettings.h"
#include "qcepstartupwindow.h"
#include <QThread>

QcepStartupWindowSettings::QcepStartupWindowSettings(QString name)
  : inherited(name, "Startup Window")
{

}

void QcepStartupWindowSettings::initialize(QcepObjectWPtr parent)
{
  inherited::initialize(parent);
}

QcepMainWindowPtr QcepStartupWindowSettings::newWindow()
{
  GUI_THREAD_CHECK;

  m_Window =
      QcepMainWindowPtr(
        new QcepStartupWindow("startupWindow"),
        &QObject::deleteLater);

  return m_Window;
}
