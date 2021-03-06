#ifndef QCEPPROPERTYVALUE_H
#define QCEPPROPERTYVALUE_H

#include <QMetaType>
#include <QSettings>

class QcepPropertyValue
{
public:
  explicit QcepPropertyValue(QObject *parent = 0);
  virtual ~QcepPropertyValue();

signals:
  
public slots:
  
public:
  virtual void setSettingsValue(QSettings *settings, QString name);
};

Q_DECLARE_METATYPE(QcepPropertyValue)
Q_DECLARE_METATYPE(QcepPropertyValue*)

#endif // QCEPPROPERTYVALUE_H
