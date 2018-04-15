#ifndef QCEPSTARTUPWINDOWSETTINGS_H
#define QCEPSTARTUPWINDOWSETTINGS_H

#include "qcepmainwindowsettings.h"

class QCEP_EXPORT QcepStartupWindowSettings : public QcepMainWindowSettings
{
  Q_OBJECT

private:
  typedef QcepMainWindowSettings inherited;

public:
  Q_INVOKABLE QcepStartupWindowSettings(QString name);

  void initialize(QcepObjectWPtr parent);

  QcepMainWindowPtr newWindow();
};

Q_DECLARE_METATYPE(QcepStartupWindowSettings*)

#endif // QCEPSTARTUPWINDOWSETTINGS_H
