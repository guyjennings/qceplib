#ifndef QCEPGRAPHCONTROLSWIDGET_H
#define QCEPGRAPHCONTROLSWIDGET_H

#include <QWidget>
#include "qcepdataobject-ptr.h"

class QcepDataObjectGraphWindow;

class QcepGraphControlsWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QcepGraphControlsWidget(QcepDataObjectGraphWindow *window, int mode, QcepDataObjectWPtr object);

signals:

public slots:

protected:
  QcepDataObjectGraphWindow  *m_Window;
  int                         m_Mode;
  QcepDataObjectWPtr          m_Object;
};

#endif // QCEPGRAPHCONTROLSWIDGET_H
