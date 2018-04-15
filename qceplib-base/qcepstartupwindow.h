#ifndef QCEPSTARTUPWINDOW_H
#define QCEPSTARTUPWINDOW_H

#include "qcepmacros.h"
#include "qcepmainwindow.h"
#include "ui_qcepstartupwindow.h"
#include <QDateTime>
#include "qcepstartupwindowsettings-ptr.h"

class QCEP_EXPORT QcepStartupWindow :
    public QcepMainWindow,
    public Ui::QcepStartupWindow
{
  Q_OBJECT

private:
  typedef QcepMainWindow inherited;

public:
  explicit QcepStartupWindow(QString name);
  void initialize(QcepObjectWPtr parent);
  ~QcepStartupWindow();

  void setApplicationIcon        (QIcon     icon);
  void setApplicationDescription (QString   desc);

public slots:
  void appendSplashMessage       (QString   msg,
                                  QDateTime dt=QDateTime::currentDateTime());
  void appendMessage             (QString   msg,
                                  QString color,
                                  QDateTime dt=QDateTime::currentDateTime());

  void onMessageWindowLinesChanged(int newVal);

private:
  QDateTime                     m_LastDateTime;
};

#endif // QCEPSTARTUPWINDOW_H
