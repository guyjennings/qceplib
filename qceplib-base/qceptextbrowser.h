#ifndef QCEPTEXTBROWSER_H
#define QCEPTEXTBROWSER_H

#include "qceplib_global.h"
#include <QTextBrowser>

class QCEP_EXPORT QcepTextBrowser : public QTextBrowser
{
  Q_OBJECT

private:
  typedef QTextBrowser inherited;

public:
  QcepTextBrowser(QWidget *parent = nullptr);

protected:
  void contextMenuEvent(QContextMenuEvent *e);
};

#endif // QCEPTEXTBROWSER_H
