#include "qcepmacros.h"
#include "qcepdebug.h"
#include "qcepmainwindow.h"
#include <QMessageBox>
#include <QThread>
#include <QMetaObject>
#include <QApplication>
#include <stdio.h>
#include <QLayout>
#include <QDockWidget>
#include <QStatusBar>
#include <QMenu>
#include <QAbstractItemView>
#include "qcepobject.h"
#include "qcepapplication.h"
#include "qcepexperiment.h"
#include "qcepapplication-ptr.h"
#include "qcepexperiment-ptr.h"
#include "qcepmainwindow-ptr.h"
#include "qcepmainwindowsettings.h"
#include "qcepallocator.h"
#include "qcepeventfiltertextedit.h"
#include "qcepeventfilterlineedit.h"
#include "qcepfinddialog.h"

QcepMainWindow::QcepMainWindow(QString name)
  : QMainWindow(),
    m_Initialized(false),
    m_Parent(NULL),
    m_Name(name),
    m_Progress(NULL),
    m_FileMenuP(NULL),
    m_EditMenuP(NULL),
    m_WindowMenuP(NULL)
{
}

QcepMainWindow::~QcepMainWindow()
{
  if (QThread::currentThread() != thread()) {
    printMessage("Deleting window from different thread");
  }
}

void QcepMainWindow::initialize(QcepObjectWPtr parent)
{
#ifndef QT_NO_DEBUG
  if (m_Initialized) {
    printf("QcepMainWindow %s %s initialized multiple times\n",
           qPrintable(QcepObject::hexArg(this)),
           metaObject()->className());
  }

  if (parent == NULL) {
    printf("QcepMainWindow %s %s initialized with NULL parent\n",
           qPrintable(QcepObject::hexArg(this)),
           metaObject()->className());
  }
#endif

  m_Initialized = true;
  m_Parent      = parent;

  m_StatusMsg = new QLabel(NULL);
  m_StatusMsg -> setMinimumWidth(200);
  m_StatusMsg -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_StatusMsg -> setToolTip(tr("Status Messages"));

  statusBar() -> addPermanentWidget(m_StatusMsg);

  m_Progress = new QProgressBar(NULL);
  m_Progress -> setMinimumWidth(150);
  m_Progress -> setMinimum(0);
  m_Progress -> setMaximum(100);
  m_Progress -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_Progress -> setToolTip(tr("Acquisition progress"));

  statusBar() -> addPermanentWidget(m_Progress);

  m_AllocationStatus = new QProgressBar(NULL);
  m_AllocationStatus -> setMinimumWidth(100);
  m_AllocationStatus -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_AllocationStatus -> setFormat("%v/%m");
  m_AllocationStatus -> setTextVisible(true);
  m_AllocationStatus -> setToolTip(tr("Memory usage"));

  statusBar() -> addPermanentWidget(m_AllocationStatus);
}

void QcepMainWindow::printLine(QString line)
{
  QcepObjectPtr p(m_Parent);

  if (p) {
    p->printLine(line);
  } else if (g_Application) {
    g_Application->printLine(line);
  } else {
    printf("LINE: %s\n", qPrintable(line));
  }
}

void QcepMainWindow::printMessage(QString msg, QDateTime ts)
{
  QcepObjectPtr p(m_Parent);

  if (p) {
    p->printMessage(msg, ts);
  } else if (g_Application) {
    g_Application->printMessage(msg, ts);
  } else {
    printf("MESSAGE: %s\n", qPrintable(msg));
  }
}

void QcepMainWindow::criticalMessage(QString msg, QDateTime ts)
{
  QcepObjectPtr p(m_Parent);

  if (p) {
    p->criticalMessage(msg, ts);
  } else if (g_Application) {
    g_Application->criticalMessage(msg, ts);
  } else {
    printf("CRITICAL: %s\n", qPrintable(msg));
  }
}

void QcepMainWindow::statusMessage(QString msg, QDateTime ts)
{
  QcepObjectPtr p(m_Parent);

  if (p) {
    p->statusMessage(msg, ts);
  } else if (g_Application) {
    g_Application->statusMessage(msg, ts);
  } else {
    printf("STATUS: %s\n", qPrintable(msg));
  }
}

QcepExperimentPtr QcepMainWindow::findExperiment()
{
  QcepExperimentPtr res(QcepExperiment::findExperiment(m_Parent));

  if (res == NULL) {
    QcepApplicationPtr app(findApplication());

    if (app) {
      res = app->experiment(0);
    }
  }

  return res;
}

QcepApplicationPtr QcepMainWindow::findApplication()
{
  QcepApplicationPtr res(QcepApplication::findApplication(m_Parent));

  return res;
}

#ifndef QT_NO_DEBUG
void QcepMainWindow::checkObjectInitialization() const
{
  if (m_Initialized == false) {
    printf("QcepMainWindow %s %s not initialized\n",
           qPrintable(QcepObject::hexArg(this)),
           metaObject()->className());
  }
}
#endif

void QcepMainWindow::setupMenus(QMenu *file, QMenu *edit, QMenu *window)
{
  INIT_CHECK;

  m_FileMenuP = file;
  m_EditMenuP = edit;
  m_WindowMenuP = window;

  QcepApplicationPtr app(QcepApplication::findApplication(m_Parent));
  QcepExperimentPtr  exper(QcepExperiment::findExperiment(m_Parent));

  if (app) {
    CONNECT_CHECK(connect(&m_StatusTimer, &QTimer::timeout, this, &QcepMainWindow::clearStatusMessage));
    CONNECT_CHECK(connect(&m_UpdateTimer, &QTimer::timeout, this, &QcepMainWindow::doTimerUpdate));

    m_UpdateTimer.start(app->get_UpdateIntervalMsec());

    CONNECT_CHECK(connect(app->prop_UpdateIntervalMsec(), &QcepIntProperty::valueChanged, this, &QcepMainWindow::onUpdateIntervalMsecChanged));

    updateTitle();

    setWindowIcon(app -> applicationIcon());
  }

  if (m_FileMenuP && app) {
    m_FileMenuP->clear();
    m_ActionNewExperiment =
        m_FileMenuP->addAction(tr("New Experiment..."), app.data(), &QcepApplication::createNewExperiment);
//    QMenu *m_RecentExperiments = new QMenu();

    m_ActionOpenExperiment =
        m_FileMenuP->addAction(tr("Open Experiment..."), app.data(), &QcepApplication::chooseExistingExperiment);

    m_ActionRecentExperiments =
        m_FileMenuP->addAction(tr("Recent Experiments"));

    m_RecentExperimentsMenu = new QMenu(this);

    m_ActionRecentExperiments -> setMenu(m_RecentExperimentsMenu);

    CONNECT_CHECK(
          connect(m_RecentExperimentsMenu, &QMenu::aboutToShow,
                  this,                    &QcepMainWindow::populateRecentExperimentsMenu));

    m_ActionSaveExperiment =
        m_FileMenuP->addAction(tr("Save Experiment..."), this, &QcepMainWindow::saveExperiment);

    m_ActionSaveExperimentAs =
        m_FileMenuP->addAction(tr("Save Experiment As..."), this, &QcepMainWindow::saveExperimentAs);

    m_ActionSaveExperimentCopy =
        m_FileMenuP->addAction(tr("Save Experiment Copy..."), this, &QcepMainWindow::saveExperimentCopy);

    m_FileMenuP->addSeparator();

    m_ActionGlobalPreferences =
        m_FileMenuP->addAction(tr("Global Preferences..."), app.data(), &QcepApplication::editGlobalPreferences);

    m_ActionExperimentPreferences =
        m_FileMenuP->addAction(tr("Experiment Preferences..."), this, &QcepMainWindow::doEditPreferences);

    m_ActionQuit =
        m_FileMenuP->addAction(tr("Quit"), app.data(), &QcepApplication::possiblyQuit);
  }

  if (m_EditMenuP) {
    CONNECT_CHECK(connect(m_EditMenuP, &QMenu::aboutToShow, this, &QcepMainWindow::populateEditMenu));

    m_ActionUndo = new QAction(this);
    m_ActionUndo->setObjectName(QStringLiteral("m_ActionUndo"));
    m_ActionUndo->setText(QApplication::translate("QxrdWindow", "Undo", Q_NULLPTR));

    m_ActionRedo = new QAction(this);
    m_ActionRedo->setObjectName(QStringLiteral("m_ActionRedo"));
    m_ActionRedo->setText(QApplication::translate("QxrdWindow", "Redo", Q_NULLPTR));

    m_ActionCut = new QAction(this);
    m_ActionCut->setObjectName(QStringLiteral("m_ActionCut"));
    m_ActionCut->setText(QApplication::translate("QxrdWindow", "Cut", Q_NULLPTR));

    m_ActionCopy = new QAction(this);
    m_ActionCopy->setObjectName(QStringLiteral("m_ActionCopy"));
    m_ActionCopy->setText(QApplication::translate("QxrdWindow", "Copy", Q_NULLPTR));

    m_ActionPaste = new QAction(this);
    m_ActionPaste->setObjectName(QStringLiteral("m_ActionPaste"));
    m_ActionPaste->setText(QApplication::translate("QxrdWindow", "Paste", Q_NULLPTR));

    m_ActionDelete = new QAction(this);
    m_ActionDelete->setObjectName(QStringLiteral("m_ActionDelete"));
    m_ActionDelete->setText(QApplication::translate("QxrdWindow", "Delete", Q_NULLPTR));

    m_ActionSelectAll = new QAction(this);
    m_ActionSelectAll->setObjectName(QStringLiteral("m_ActionSelectAll"));
    m_ActionSelectAll->setText(QApplication::translate("QxrdWindow", "Select All", Q_NULLPTR));

    m_ActionFind = new QAction(this);
    m_ActionFind->setObjectName(QStringLiteral("m_ActionFind"));
    m_ActionFind->setText(QApplication::translate("QxrdWindow", "Find...", Q_NULLPTR));
    m_ActionFind->setShortcut(Qt::CTRL+Qt::Key_F);

    m_ActionFindSelected = new QAction(this);
    m_ActionFindSelected->setObjectName(QStringLiteral("m_ActionFindSelected"));
    m_ActionFindSelected->setText(QApplication::translate("QxrdWindow", "Find Selected", Q_NULLPTR));
    m_ActionFindSelected->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_F);

    m_ActionFindNext = new QAction(this);
    m_ActionFindNext->setObjectName(QStringLiteral("m_ActionFindNext"));
    m_ActionFindNext->setText(QApplication::translate("QxrdWindow", "Find Next", Q_NULLPTR));
    m_ActionFindNext->setShortcut(Qt::CTRL+Qt::Key_G);

    m_ActionFindPrevious = new QAction(this);
    m_ActionFindPrevious->setObjectName(QStringLiteral("m_ActionFindPrevious"));
    m_ActionFindPrevious->setText(QApplication::translate("QxrdWindow", "Find Previous", Q_NULLPTR));
    m_ActionFindPrevious->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_G);

    CONNECT_CHECK(connect(m_ActionUndo, &QAction::triggered, this, &QcepMainWindow::doUndo));
    CONNECT_CHECK(connect(m_ActionRedo, &QAction::triggered, this, &QcepMainWindow::doRedo));
    CONNECT_CHECK(connect(m_ActionCut, &QAction::triggered, this, &QcepMainWindow::doCut));
    CONNECT_CHECK(connect(m_ActionCopy, &QAction::triggered, this, &QcepMainWindow::doCopy));
    CONNECT_CHECK(connect(m_ActionPaste, &QAction::triggered, this, &QcepMainWindow::doPaste));
    CONNECT_CHECK(connect(m_ActionDelete, &QAction::triggered, this, &QcepMainWindow::doDelete));
    CONNECT_CHECK(connect(m_ActionSelectAll, &QAction::triggered, this, &QcepMainWindow::doSelectAll));
    CONNECT_CHECK(connect(m_ActionFind, &QAction::triggered, this, &QcepMainWindow::doFind));
    CONNECT_CHECK(connect(m_ActionFindSelected, &QAction::triggered, this, &QcepMainWindow::doFindSelected));
    CONNECT_CHECK(connect(m_ActionFindNext, &QAction::triggered, this, &QcepMainWindow::doFindNext));
    CONNECT_CHECK(connect(m_ActionFindPrevious, &QAction::triggered, this, &QcepMainWindow::doFindPrevious));
  }

  if (m_WindowMenuP) {
    CONNECT_CHECK(
          connect(m_WindowMenuP,  &QMenu::aboutToShow,
                  this, &QcepMainWindow::populateWindowsMenu));
  }

  setupContextMenus();
}

void QcepMainWindow::populateEditMenu()
{
  INIT_CHECK;

  QcepExperimentPtr expt(QcepExperiment::findExperiment(m_Parent));

  m_EditMenuP -> clear();

  QAction *undoAction = NULL, *redoAction = NULL;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
    //      printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);

    if (txed || lned || ispn || dspn || cbox) {
      undoAction = m_ActionUndo;
      redoAction = m_ActionRedo;
    }
  }

  if (expt) {
    if (undoAction == NULL) {
      undoAction = expt->undoStack()->createUndoAction(this);
    }

    if (redoAction == NULL) {
      redoAction = expt->undoStack()->createRedoAction(this);
    }
  }

  m_EditMenuP->addAction(undoAction);
  m_EditMenuP->addAction(redoAction);

  m_EditMenuP->addSeparator();

  m_EditMenuP->addAction(m_ActionCut);
  m_EditMenuP->addAction(m_ActionCopy);
  m_EditMenuP->addAction(m_ActionPaste);
  m_EditMenuP->addAction(m_ActionDelete);

  m_EditMenuP->addSeparator();

  m_EditMenuP->addAction(m_ActionFind);
  m_EditMenuP->addAction(m_ActionFindSelected);
  m_EditMenuP->addAction(m_ActionFindNext);
  m_EditMenuP->addAction(m_ActionFindPrevious);

  m_EditMenuP->addSeparator();

  m_EditMenuP->addAction(m_ActionSelectAll);
}

void QcepMainWindow::populateWindowsMenu()
{
  INIT_CHECK;

  QcepExperimentPtr expt(findExperiment());

  if (m_WindowMenuP) {
    m_WindowMenuP->clear();

    if (expt) {
      for (int i=0; i<expt->windowSettingsCount(); i++) {
        QcepMainWindowSettingsPtr set(expt->windowSettings(i));

        appendToWindowMenu(m_WindowMenuP, set);
      }
    }
  }
}

void QcepMainWindow::appendToWindowMenu(
    QMenu* wmenu, QcepMainWindowSettingsWPtr s)
{
  QcepMainWindowSettingsPtr set(s);

  if (set) {
    QcepMainWindowPtr win = set -> window();

    QAction *act = NULL;

    QcepMainWindowSettings *settings = set.data();

    if (win) {
      act = wmenu ->
          addAction(tr("Show %1").arg(set->get_Description()),
                    this, [=]() { newWindow(settings); });
    } else {
      act = wmenu ->
          addAction(tr("New %1").arg(set->get_Description()),
                    this, [=]() { newWindow(settings); });
    }
  }
}

void QcepMainWindow::populateRecentExperimentsMenu()
{
  INIT_CHECK;

  //  printMessage("Populating recent experiments menu");

  m_RecentExperimentsMenu->clear();

  QcepApplicationPtr app(QcepApplication::findApplication(m_Parent));

  if (app) {
    QStringList recent = app->get_RecentExperiments();

    foreach (QString exp, recent) {
      QAction *action = new QAction(exp, m_RecentExperimentsMenu);

      QcepApplication *appp = app.data();

      CONNECT_CHECK(connect(action, &QAction::triggered, [=] {appp->openRecentExperiment(exp);}));

      m_RecentExperimentsMenu -> addAction(action);
    }
  }
}

void QcepMainWindow::newWindow(QcepMainWindowSettings *set)
{
  INIT_CHECK;

  if (set) {
    QcepMainWindowPtr win = set->window();

    if (!win) {
      win = set->newWindow();

      if (win) {
        win->initialize(set->sharedFromThis());
      }
    }

    if (win) {
      win->show();
      win->raise();
      win->activateWindow();
    }
  }
}

void QcepMainWindow::closeEvent(QCloseEvent *event)
{
  if (wantToClose()) {
    hide();

    event -> accept();
  } else {
    event -> ignore();
  }
}

QString QcepMainWindow::windowName() const
{
  return m_Name;
}

void QcepMainWindow::updateTitle()
{
  INIT_CHECK;

  QcepExperimentPtr exper(findExperiment());

  QString title = windowName();

  if (exper) {
    title.append(" - ");
    title.append(exper->experimentFilePath());
  }

  title.append(" - ");
  title.append(g_Application->applicationName());

  if (sizeof(void*) == 4) {
    title.append(" - 32 bit - v");
  } else {
    title.append(" - 64 bit - v");
  }

  title.append(g_Application->applicationVersion());

  if (exper && exper->isChanged()) {
    title.append(tr(" [%1]").arg(exper->isChanged()));
  }

  setWindowTitle(title);
}

void QcepMainWindow::doTimerUpdate()
{
  INIT_CHECK;

  updateTitle();

  allocatedMemoryChanged();
}

void QcepMainWindow::displayStatusMessage(QString msg)
{
  INIT_CHECK;

  if (QThread::currentThread()==thread()) {
    m_StatusMsg -> setText(msg);

    //  printMessage(msg);

    m_StatusTimer.start(5000);
  } else {
    INVOKE_CHECK(QMetaObject::invokeMethod(this,
                                           "displayStatusMessage",
                                           Qt::QueuedConnection,
                                           Q_ARG(QString, msg)));
  }
}

void QcepMainWindow::onUpdateIntervalMsecChanged(int newVal)
{
  INIT_CHECK;

  m_UpdateTimer.setInterval(newVal);
}

void QcepMainWindow::clearStatusMessage()
{
  INIT_CHECK;

  m_StatusMsg -> setText("");
}

void QcepMainWindow::allocatedMemoryChanged()
{
  INIT_CHECK;

  int alloc = QcepAllocator::allocatedMemoryMB();
  int avail = QcepAllocator::availableMemoryMB();

  m_AllocationStatus -> setMaximum(avail);
  m_AllocationStatus -> setValue(alloc);
}

void QcepMainWindow::doUndo()
{
  INIT_CHECK;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
//    printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);

    if (txed) {
      txed->undo();
    } else if (lned) {
      lned->undo();
    } else if (ispn) {
    } else if (dspn) {
    } else if (cbox) {
    }
  }
}

void QcepMainWindow::doRedo()
{
  INIT_CHECK;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
//    printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);

    if (txed) {
      txed->redo();
    } else if (lned) {
      lned->redo();
    } else if (ispn) {
    } else if (dspn) {
    } else if (cbox) {
    }
  }
}

void QcepMainWindow::doCut()
{
  INIT_CHECK;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
//    printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);

    if (txed) {
      txed->cut();
    } else if (lned) {
      lned->cut();
    } else if (ispn) {
    } else if (dspn) {
    } else if (cbox) {
    }
  }
}

void QcepMainWindow::doCopy()
{
  INIT_CHECK;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
//    printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);

    if (txed) {
      txed->copy();
    } else if (lned) {
      lned->copy();
    } else if (ispn) {
    } else if (dspn) {
    } else if (cbox) {
    }
  }
}

void QcepMainWindow::doPaste()
{
  INIT_CHECK;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
//    printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);

    if (txed) {
      txed->paste();
    } else if (lned) {
      lned->paste();
    } else if (ispn) {
    } else if (dspn) {
    } else if (cbox) {
    }
  }
}

void QcepMainWindow::doDelete()
{
  INIT_CHECK;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
//    printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);

    if (txed) {
      if (txed->textCursor().hasSelection()) {
        txed->textCursor().deleteChar();
      }
    } else if (lned) {
      if (lned->selectedText().length()) {
        lned->del();
      }
    } else if (ispn) {
    } else if (dspn) {
    } else if (cbox) {
    }
  }
}

void QcepMainWindow::doSelectAll()
{
  INIT_CHECK;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
//    printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);
    QAbstractItemView *itmv = qobject_cast<QAbstractItemView*>(focusWidget);

    if (txed) {
      txed->selectAll();
    } else if (lned) {
      lned->selectAll();
    } else if (ispn) {
    } else if (dspn) {
    } else if (cbox) {
    } else if (itmv) {
      itmv->selectAll();
    }
  }
}

void QcepMainWindow::doFind()
{
  INIT_CHECK;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
//    printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);

    if (txed) {
      findTextEdit(txed);
    } else if (lned) {
      findLineEdit(lned);
    } else if (ispn) {
    } else if (dspn) {
    } else if (cbox) {
    }
  }
}

void QcepMainWindow::doFindSelected()
{
  INIT_CHECK;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
//    printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);

    if (txed) {
      findSelectedTextEdit(txed);
    } else if (lned) {
      findSelectedLineEdit(lned);
    } else if (ispn) {
    } else if (dspn) {
    } else if (cbox) {
    }
  }
}

void QcepMainWindow::doFindNext()
{
  INIT_CHECK;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
//    printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);

    if (txed) {
      findNextTextEdit(txed);
    } else if (lned) {
      findNextLineEdit(lned);
    } else if (ispn) {
    } else if (dspn) {
    } else if (cbox) {
    }
  }
}

void QcepMainWindow::doFindPrevious()
{
  INIT_CHECK;

  QWidget* focusWidget = QApplication::focusWidget();

  if (focusWidget) {
//    printMessage(tr("focusWidget = %1").arg(focusWidget->objectName()));

    QTextEdit *txed = qobject_cast<QTextEdit*>(focusWidget);
    QLineEdit *lned = qobject_cast<QLineEdit*>(focusWidget);
    QSpinBox  *ispn = qobject_cast<QSpinBox*>(focusWidget);
    QDoubleSpinBox *dspn = qobject_cast<QDoubleSpinBox*>(focusWidget);
    QComboBox *cbox = qobject_cast<QComboBox*>(focusWidget);

    if (txed) {
      findPreviousTextEdit(txed);
    } else if (lned) {
      findPreviousLineEdit(lned);
    } else if (ispn) {
    } else if (dspn) {
    } else if (cbox) {
    }
  }
}

void QcepMainWindow::openFindDialog()
{
  QcepFindDialog dlog(this);

  dlog.exec();
}

void QcepMainWindow::findTextEdit(QTextEdit *te)
{
  openFindDialog();
}

void QcepMainWindow::findLineEdit(QLineEdit *le)
{
  openFindDialog();
}

void QcepMainWindow::findSelectedTextEdit(QTextEdit *te)
{
  if (te) {
    QTextCursor    tc  = te->textCursor();
    QTextDocument *doc = te->document();

    QString findString = tc.selectedText();

    if (findString.length() >= 0) {
      g_Application -> set_FindString(findString);

      findNextTextEdit(te);
    }
  }
}

void QcepMainWindow::findSelectedLineEdit(QLineEdit *le)
{
}

void QcepMainWindow::findNextTextEdit(QTextEdit *te)
{
  if (te) {
    QTextCursor    tc  = te->textCursor();
    QTextDocument *doc = te->document();

    if (doc) {
      tc = doc->find(g_Application->get_FindString(), tc);

      te->setTextCursor(tc);
    }
  }
}

void QcepMainWindow::findNextLineEdit(QLineEdit *le)
{
}

void QcepMainWindow::findPreviousTextEdit(QTextEdit *te)
{
  if (te) {
    QTextCursor    tc  = te->textCursor();
    QTextDocument *doc = te->document();

    if (doc) {
      tc = doc->find(g_Application->get_FindString(),
                     tc, QTextDocument::FindBackward);

      te->setTextCursor(tc);
    }
  }
}

void QcepMainWindow::findPreviousLineEdit(QLineEdit *le)
{
}

void QcepMainWindow::setupContextMenus()
{
  QList<QWidget*> widgets = findChildren<QWidget*>();

  foreach (QWidget* w, widgets) {
    QTextEdit *txed = qobject_cast<QTextEdit*>(w);
    QLineEdit *lned = qobject_cast<QLineEdit*>(w);

    if (txed) {
      txed -> installEventFilter(new QcepEventFilterTextEdit(txed, this));
      auto policy = txed -> contextMenuPolicy();
      txed -> setContextMenuPolicy(Qt::DefaultContextMenu);
    } else if (lned) {
      lned -> installEventFilter(new QcepEventFilterLineEdit(lned, this));
    }
  }
}

void QcepMainWindow::textEditContextMenu(QTextEdit *te, QMenu *menu)
{
  menu -> addAction(m_ActionFind);
  menu -> addAction(m_ActionFindSelected);
  menu -> addAction(m_ActionFindNext);
  menu -> addAction(m_ActionFindPrevious);
}

void QcepMainWindow::lineEditContextMenu(QLineEdit *le, QMenu *menu)
{
  menu -> addAction(m_ActionFind);
  menu -> addAction(m_ActionFindSelected);
  menu -> addAction(m_ActionFindNext);
  menu -> addAction(m_ActionFindPrevious);
}

void QcepMainWindow::possiblyClose()
{
  INIT_CHECK;

  //   printf("QxrdWindow::possiblyClose()\n");
  if (wantToClose()) {
    close();
  }
}

bool QcepMainWindow::wantToClose()
{
  THREAD_CHECK;

  INIT_CHECK;

  return QMessageBox::question(this, tr("Really Close?"),
                               tr("Do you really want to close the window?"),
                               QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok;
}

void QcepMainWindow::resizeEvent(QResizeEvent *event)
{
  inherited::resizeEvent(event);

  QcepMainWindowSettingsPtr set(
        qSharedPointerDynamicCast<QcepMainWindowSettings>(m_Parent));

  if (set) {
    set -> set_WindowRect(geometry());
  }
}

void QcepMainWindow::moveEvent(QMoveEvent *event)
{
  inherited::moveEvent(event);

  QcepMainWindowSettingsPtr set(
        qSharedPointerDynamicCast<QcepMainWindowSettings>(m_Parent));

  if (set) {
    set -> set_WindowRect(geometry());
  }
}

void QcepMainWindow::saveExperiment()
{
}

void QcepMainWindow::saveExperimentAs()
{
}

void QcepMainWindow::saveExperimentCopy()
{
}

void QcepMainWindow::doEditPreferences()
{
}

//void QcepMainWindow::setFontSize(int fontSize)
//{
//  INIT_CHECK;

//  if (QThread::currentThread()==thread()) {
//    if (fontSize > 0) {
//      QFont f = font();

//      f.setPointSize(fontSize);

//      setFont(f);
//    } else {
//      QFont f = QApplication::font(this);
//      setFont(f);
//    }
//  } else {
//    INVOKE_CHECK(QMetaObject::invokeMethod(this,
//                                           "setFontSize",
//                                           Qt::QueuedConnection,
//                                           Q_ARG(int, fontSize)));
//  }
//}

//void QcepMainWindow::setSpacing(int spacing)
//{
//  INIT_CHECK;

//  if (QThread::currentThread()==thread()) {
//    setObjectSpacing(this, spacing);
//  } else {
//    INVOKE_CHECK(QMetaObject::invokeMethod(this,
//                                           "setSpacing",
//                                           Qt::QueuedConnection,
//                                           Q_ARG(int, spacing)));
//  }
//}

//void QcepMainWindow::setObjectSpacing(QObject *obj, int spacing)
//{
//  INIT_CHECK;

//  QLayout *ly = qobject_cast<QLayout*>(obj);

//  if (ly) {
//    ly->setContentsMargins(spacing, spacing, spacing, spacing);

//    QGridLayout *gl = qobject_cast<QGridLayout*>(ly);

//    if (gl) {
//      gl->setHorizontalSpacing(spacing);
//      gl->setVerticalSpacing(spacing);
//    }
//  }
//  //  QTableView *tv = qobject_cast<QTableView*>(obj);

//  //  if (tv) {
//  //    tv->setStyleSheet(tr("QTableWidget::item { padding: %1px }").arg(spacing));
//  //  }

//  foreach(QObject* chobj, obj->children()) {
//    if (chobj) {
//      setObjectSpacing(chobj, spacing);
//    }
//  }
//}

//void QcepMainWindow::shrinkPanels(int fontSize, int spacing)
//{
//  INIT_CHECK;

////  if (QThread::currentThread()==thread()) {
////    shrinkObject(this, fontSize, spacing);
////  } else {
////    INVOKE_CHECK(QMetaObject::invokeMethod(this,
////                                           "shrinkPanels",
////                                           Qt::QueuedConnection,
////                                           Q_ARG(int, fontSize),
////                                           Q_ARG(int, spacing)));
////  }
//  setFontSize(fontSize);
//  setSpacing(spacing);
//}

//void QcepMainWindow::shrinkDockWidget(QDockWidget *dw, int fontSize, int spacing)
//{
//  INIT_CHECK;

//  shrinkObject(dw, fontSize, spacing);
//}

//void QcepMainWindow::shrinkObject(QObject *obj, int fontSize, int spacing)
//{
//  INIT_CHECK;

//  if (obj) {
//    //    printf("shrinkObject %p[%s]\n", obj, qPrintable(obj->objectName()));

//    QWidget *wid = qobject_cast<QWidget*>(obj);

//    QVariant fsz = obj->property("defaultFontSize");
//    QVariant mrga = obj->property("defaultAMargins");
//    QVariant mrgb = obj->property("defaultBMargins");

//    if (qcepDebug(DEBUG_WINDOW)) {
//      printMessage(tr("QxrdWindow::shrinkObject(\"%1\",%2)").arg(obj->objectName()).HEXARG(obj));
//      printMessage(tr("Default Font Size %1, Margins A [%2,%3], B [%4,%5]").arg(fsz.toInt())
//        .arg(mrga.toPoint().x()).arg(mrga.toPoint().y())
//        .arg(mrgb.toPoint().x()).arg(mrgb.toPoint().y()));
//    }

//    if (wid) {
//      int sz = wid->font().pointSize();

//      int left, top, right, bottom;
//      wid->getContentsMargins(&left, &top, &right, &bottom);

//      if (qcepDebug(DEBUG_WINDOW)) {
//        printMessage(tr("Existing Font Size %1, Margins A [%2,%3], B [%4,%5]").arg(sz).arg(left).arg(top).arg(right).arg(bottom));
//      }

//      if (!fsz.isValid()) {
//        wid->setProperty("defaultFontSize", sz);
//        fsz = wid->property("defaultFontSize");
//      }

//      if (!mrga.isValid()) {
//        wid->setProperty("defaultAMargins", QPoint(left, top));
//        mrga = wid->property("defaultAMargins");
//      }

//      if (!mrgb.isValid()) {
//        wid->setProperty("defaultBMargins", QPoint(right, bottom));
//        mrgb = wid->property("defaultBMargins");
//      }

//      if (fontSize >= 0) {
//        QFont f = wid->font();
//        f.setPointSize(fontSize);
//        wid->setFont(f);
//      } else {
//        QFont f = wid->font();
//        f.setPointSize(fsz.toInt());
//        wid->setFont(f);
//      }

//      if (spacing >= 0) {
//        wid->setContentsMargins(spacing, spacing, spacing, spacing);
//      } else {
//        QPoint ma = mrga.toPoint();
//        QPoint mb = mrgb.toPoint();

//        if (!ma.isNull() && !mb.isNull()) {
//          wid->setContentsMargins(ma.x(), ma.y(), mb.x(), mb.y());
//        }
//      }
//    }

//    if (qcepDebug(DEBUG_WINDOW)) {
//      printMessage(tr("Default Font Size %1, Margins A [%2,%3], B [%4,%5]").arg(fsz.toInt())
//        .arg(mrga.toPoint().x()).arg(mrga.toPoint().y())
//        .arg(mrgb.toPoint().x()).arg(mrgb.toPoint().y()));
//    }

//    QLayout *ly = qobject_cast<QLayout*>(obj);

//    if (ly) {
//      if (spacing >= 0) {
//        ly->setContentsMargins(spacing, spacing, spacing, spacing);
//      } else {
//        QPoint ma = mrga.toPoint();
//        QPoint mb = mrgb.toPoint();

//        if (!ma.isNull() && !mb.isNull()) {
//          ly->setContentsMargins(ma.x(), ma.y(), mb.x(), mb.y());
//        }
//      }

//      QGridLayout *gl = qobject_cast<QGridLayout*>(ly);

//      if (gl) {
////        gl->setContentsMargins(spacing, spacing, spacing, spacing);
//        QVariant spc = gl->property("defaultSpacing");

//        if (qcepDebug(DEBUG_WINDOW)) {
//          printMessage(tr("Default spacing [%1,%2]").arg(spc.toPoint().x()).arg(spc.toPoint().y()));
//        }

//        if (!spc.isValid()) {
//          int hs = gl->horizontalSpacing();
//          int vs = gl->verticalSpacing();

//          if (qcepDebug(DEBUG_WINDOW)) {
//            printMessage(tr("Existing spacing [%1,%2]").arg(hs).arg(vs));
//          }

//          gl->setProperty("defaultSpacing", QPoint(hs,vs));
//          spc = gl->property("defaultSpacing");
//        }

//        if (spacing >= 0) {
//          gl->setHorizontalSpacing(spacing);
//          gl->setVerticalSpacing(spacing);
//        } else {
//          QPoint sp = spc.toPoint();
//          if (!sp.isNull()) {
//            gl->setHorizontalSpacing(sp.x());
//            gl->setVerticalSpacing(sp.y());
//          }
//        }

//        if (qcepDebug(DEBUG_WINDOW)) {
//          printMessage(tr("Default spacing [%1,%2]").arg(spc.toPoint().x()).arg(spc.toPoint().y()));
//        }
//      }
//    }

//    foreach(QObject* chobj, obj->children()) {
//      if (chobj) {
//        shrinkObject(chobj, fontSize, spacing);
//      }
//    }
//  }
//}


