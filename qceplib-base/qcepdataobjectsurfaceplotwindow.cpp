#ifdef HAVE_DATAVIS

#include "qcepdataobjectsurfaceplotwindow.h"
#include <QMessageBox>
#include "qcepimagedata.h"
#include <QCloseEvent>

using namespace QtDataVisualization;

QcepDataObjectSurfacePlotWindow::QcepDataObjectSurfacePlotWindow(
    QString            name,
    QcepExperimentWPtr /*expt*/,
    QcepDataObjectWPtr obj)
  : inherited(name),
    m_Object(obj)
{
}

void QcepDataObjectSurfacePlotWindow::initialize(QcepObjectWPtr parent)
{
  GUI_THREAD_CHECK;

  inherited::initialize(parent);

  setupUi(this);

  setupMenus(m_FileMenu, m_EditMenu, m_WindowMenu);

  setAttribute(Qt::WA_DeleteOnClose);

  QcepDoubleImageDataWPtr img = qSharedPointerDynamicCast<QcepDoubleImageData>(m_Object);

  onNewImageAvailable(img);
}

QcepDataObjectSurfacePlotWindow::~QcepDataObjectSurfacePlotWindow()
{
#ifndef QT_NO_DEBUG
  printf("Deleting Surface Plot Window\n");
#endif
}

void QcepDataObjectSurfacePlotWindow::closeEvent ( QCloseEvent * event )
{
  if (wantToClose()) {
    event -> accept();
  } else {
    event -> ignore();
  }
}

bool QcepDataObjectSurfacePlotWindow::wantToClose()
{
  return QMessageBox::question(this, tr("Really Close?"),
                               tr("Do you really want to close the window %1 ?")
                               .arg(windowTitle()),
                               QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok;
}

void QcepDataObjectSurfacePlotWindow::onNewImageAvailable(QcepDoubleImageDataWPtr img)
{
  QcepDoubleImageDataPtr imgp(img);

  if (imgp) {
    setWindowTitle(tr("Surface Plot : %1").arg(imgp->get_Name()));

    m_SurfacePlot->onNewImageAvailable(imgp);
  }
}

void QcepDataObjectSurfacePlotWindow::saveExperimentAs()
{
}

void QcepDataObjectSurfacePlotWindow::saveExperimentCopy()
{
}

void QcepDataObjectSurfacePlotWindow::doEditPreferences()
{
}

#endif
