#include "qcepdataobject.h"
#include <QScriptEngine>
#include "qcepdatagroup.h"
#include <stdio.h>
#include "qcepapplication.h"
#include "qcepmutexlocker.h"
#include <QAtomicInteger>
#include <QFileInfo>
#include <QDir>

static QAtomicInt s_ObjectAllocateCount(0);
static QAtomicInt s_ObjectDeleteCount(0);

QcepDataObject::QcepDataObject(QString name, qint64 byteSize) :
  inherited(name),
  m_ByteSize        (this, "size", byteSize, "Object Size"),
  m_Creator         (this, "creator", "Unknown", "QXRD Version Number"),
  m_Version         (this, "version", "Unknown", "QXRD Version Number"),
  m_QtVersion       (this, "qtVersion", qVersion(), "QT Version Number"),
  m_Description     (this, "description", "", "Object Description"),
  m_FileBase        (this, "fileBase", "", "File Base of Data Object"),
  m_FileIndex       (this, "fileIndex", 0, "File Index of Data Object"),
  m_FileUniqueIndex (this, "fileUniqueIndex", 0, "File Unique Index"),
  m_FileTypeName    (this, "fileTypeName", "", "File Type Name of Data Object"),
  m_FileExtension   (this, "fileExtension", "", "File Extension of Data Object"),
  m_FileName        (this, "fileName", "", "File Name of Data Object"),
  m_FileDirectory   (this, "fileDirectory", "", "Directory Name of Data Object"),
  m_FilePath        (this, "filePath", "", "File Path of Data Object"),
  m_ObjectSaved     (this, "objectSaved", 0, "Object is Saved?")
{
  s_ObjectAllocateCount.fetchAndAddOrdered(1);

  if (name.contains("/")) {
    printMessage(tr("object %1 name contains \"/\"").arg(name));
  }

  if (g_Application) {
    g_Application->setDefaultObjectData(this);
  }
}

QcepDataObject::~QcepDataObject()
{
  s_ObjectDeleteCount.fetchAndAddOrdered(1);
}

void QcepDataObject::initialize(QcepObjectWPtr parent)
{
  inherited::initialize(parent);
}

void QcepDataObject::writeSettings(QSettings *settings)
{
  inherited::writeSettings(settings);
}

void QcepDataObject::readSettings(QSettings *settings)
{
  inherited::readSettings(settings);
}

QString QcepDataObject::mimeType()
{
  return "application/x-qcepdataobject";
}

//TODO: write this...
QString QcepDataObject::possibleFileName(QString extension, int uniqueIndex)
{
  criticalMessage(tr("QcepDataObject::possibleFileName(\"%1\",%2) not yet written")
                  .arg(extension)
                  .arg(uniqueIndex));

  return "===+++ not implemented +++===";
}

QString QcepDataObject::fileFormatAny()
{
  return "Any file (*)";
}

QString QcepDataObject::fileFormatHDF5()
{
  return "HDF5 file (*.h5)";
}

QString QcepDataObject::fileFormatNexus()
{
  return "Nexus file (*.nxs)";
}

QString QcepDataObject::fileFormatTIFF()
{
  return "TIFF (*.tif, *.tiff)";
}

QString QcepDataObject::fileFormatTabDelimited()
{
  return "Tab delimited (*.txt, *.dat)";
}

QString QcepDataObject::fileFormatTransposedTabDelimited()
{
  return "Transposed Tab delimited (*.txt, *.dat)";
}

QString QcepDataObject::fileFormatCSV()
{
  return "CSV (*.csv)";
}

QString QcepDataObject::fileFormatTransposedCSV()
{
  return "Transposed CSV (*.csv)";
}

QString QcepDataObject::fileFormatSpec()
{
  return "Spec Data File (*)";
}

QString QcepDataObject::fileFormatCIF()
{
  return "CIF File (*.cif,*)";
}

int QcepDataObject::allocatedObjects()
{
  return s_ObjectAllocateCount.load();
}

int QcepDataObject::deletedObjects()
{
  return s_ObjectDeleteCount.load();
}

QString QcepDataObject::description() const
{
  return "";
}

QString QcepDataObject::pathName() const
{
  QString suffix="";

  if (qobject_cast<const QcepDataGroup*>(this)) {
    suffix = "/";
  }

  if (parentItem()) {
    return parentItem()->pathName()+get_Name()+suffix;
  } else {
    return "/";
  }
}

void QcepDataObject::mkPath(QString filePath)
{
  QFileInfo f(filePath);
  QDir dir = f.dir();

  if (!dir.exists()) {
    dir.mkpath(dir.absolutePath());
  }
}

void QcepDataObject::setNameAndSuffix(QString oldName, QString newSuffix)
{
  QFileInfo f(oldName);

  set_Name(f.completeBaseName()+"."+newSuffix);
}

QString QcepDataObject::uniqueFileName(QString name)
{
  QFileInfo f(name);

  if (f.exists()) {
    QDir dir = f.dir();
    QString base = f.baseName();
    QString suff = f.completeSuffix();

//    QxrdAcquisitionPtr acq(acquisition());

    int width = 5;

//    if (acq) {
//      width = acq->get_FileOverflowWidth();
//    }

    for (int i=1; ; i++) {
      QString newname = dir.filePath(base+QString().sprintf("-%0*d.",width,i)+suff);
      QFileInfo f(newname);

      if (!f.exists()) {
        return newname;
      }
    }
  } else {
    return name;
  }
}

void QcepDataObject::saveData(QString & /*name*/, QString /*filter*/, Overwrite /*canOverwrite*/)
{
}

QScriptValue QcepDataObject::toScriptValue(QScriptEngine *engine, const QcepDataObjectPtr &data)
{
  return engine->newQObject(data.data());
}

void QcepDataObject::fromScriptValue(const QScriptValue &obj, QcepDataObjectPtr &data)
{
  QObject *qobj = obj.toQObject();

  if (qobj) {
    QcepDataObject *qdobj = qobject_cast<QcepDataObject*>(qobj);

    if (qdobj) {
      QcepObjectPtr p = qdobj->sharedFromThis();

      if (p) {
        QcepDataObjectPtr dp = qSharedPointerDynamicCast<QcepDataObject>(p);

        if (dp) {
          data = dp;
        }
      }
    }
  }
}

//int QcepDataObject::childCount() const
//{
//  return 0;
//}

int QcepDataObject::rowCount() const
{
  return 0;
}

int QcepDataObject::columnCount() const
{
  return 0;
}

QcepDataObjectPtr QcepDataObject::item(int /*n*/)
{
  return QcepDataObjectPtr();
}

QcepDataObjectPtr QcepDataObject::item(QString /*nm*/)
{
  return QcepDataObjectPtr();
}

QcepDataGroupPtr QcepDataObject::parentItem()
{
  return qSharedPointerDynamicCast<QcepDataGroup>(parentPtr());
}

const QcepDataGroupPtr QcepDataObject::parentItem() const
{
  return qSharedPointerDynamicCast<QcepDataGroup>(parentPtr());
}

QcepDataGroupPtr QcepDataObject::rootItem()
{
  QcepDataGroupPtr p = parentItem();

  if (p) {
    return p->rootItem();
  } else {
    QcepObjectPtr obj = sharedFromThis();

    return qSharedPointerDynamicCast<QcepDataGroup>(obj);
  }
}

void QcepDataObject::setParentItem(QcepDataGroupWPtr parent)
{
  setParentPtr(parent);
}

int QcepDataObject::indexInParent() const
{
  QcepDataGroupPtr p = parentItem();

  if (p) {
    for (int i=0; i<p->childCount(); i++) {
      if (p->item(i).data() == this) {
        return i;
      }
    }
  }

  return 0;
}

QVariant QcepDataObject::columnData(int col) const
{
  if (col == 0) {
    return get_Name();
  } else if (col == 1) {
    return get_Type();
  } else {
    return QVariant(description());
  }
}

QString QcepDataObject::metaTypeName(int id) const
{
  return QMetaType::typeName(id);
}

QString QcepDataObject::fileFormatFilterString()
{
  return "Text (*.txt)";
}
