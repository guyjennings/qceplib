#ifndef QCEPTEXTEDIT_H
#define QCEPTEXTEDIT_H

#include "qceplib_global.h"
#include <QTextEdit>

class QCEP_EXPORT QcepTextEdit : public QTextEdit
{
  Q_OBJECT

private:
  typedef QTextEdit inherited;

public:
  explicit QcepTextEdit(QWidget *parent = nullptr);
  virtual ~QcepTextEdit();

signals:

public slots:

protected:
  void contextMenuEvent(QContextMenuEvent *e);
};

#endif // QCEPTEXTEDIT_H
