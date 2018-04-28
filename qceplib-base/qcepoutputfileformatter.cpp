#include "qcepoutputfileformatter.h"
#include "qcepoutputfileformattersettings.h"
#include "qcepoutputfileformattertiff.h"
#include "qcepoutputfileformatterhdf.h"
#include <QDir>
#include "qcepimagedata.h"

QcepOutputFileFormatter::QcepOutputFileFormatter(QString name)
  : inherited(name)
{
}

QcepOutputFileFormatter::~QcepOutputFileFormatter()
{
}

void QcepOutputFileFormatter::initialize(QcepObjectWPtr parent)
{
  inherited::initialize(parent);
}

void QcepOutputFileFormatter::saveImageData(QcepOutputFileFormatterSettingsWPtr set,
                                            QString                            name,
                                            QcepImageDataBasePtr               img,
                                            QcepImageDataBasePtr               overflow,
                                            int                                canOverwrite)
{
}

void QcepOutputFileFormatter::mkPath(QString filePath)
{
  QFileInfo f(filePath);
  QDir dir = f.dir();

  if (!dir.exists()) {
    dir.mkpath(dir.absolutePath());
  }
}

QString QcepOutputFileFormatter::uniqueFileName(QcepImageDataBasePtr data)
{
  QString res = QString();

  if (data) {
    QDir dir(data->get_FileDirectory());

    QString extn = data->get_FileExtension();
    QString name = data->possibleFileName(extn);
    QString path = dir.filePath(name);

    QFileInfo f(path);

    if (f.exists()) {
      int i = data -> get_FileUniqueIndex()+1;

      for ( ; ; i++) {
        QString newName = data->possibleFileName(extn, i);
        QString newPath = dir.filePath(newName);
        QFileInfo f(newPath);

        if (!f.exists()) {
          data -> set_FileUniqueIndex(i);
          data -> set_FileName(newName);
          data -> set_FilePath(newPath);

          res = newPath;

          break;
        }
      }
    } else {
      data -> set_FileName(name);
      data -> set_FilePath(path);

      res = path;
    }
  }

  return res;
}
