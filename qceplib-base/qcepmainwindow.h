#ifndef QCEPMAINWINDOW_H
#define QCEPMAINWINDOW_H

#include "qceplib_global.h"
#include <QMainWindow>
#include <QDateTime>
#include "qcepobject-ptr.h"
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include "qcepmainwindowsettings-ptr.h"
#include "qcepexperiment-ptr.h"
#include "qcepapplication-ptr.h"
#include <QTextEdit>
#include <QLineEdit>
#include "qcepproperty.h"

class QCEP_EXPORT QcepMainWindow : public QMainWindow
{
  Q_OBJECT

private:
  typedef QMainWindow inherited;

public:
  explicit QcepMainWindow(QString name);
  virtual ~QcepMainWindow();

  virtual void initialize(QcepObjectWPtr parent);

  virtual QcepExperimentPtr  findExperiment();
  virtual QcepApplicationPtr findApplication();

  void possiblyClose();
  bool wantToClose();

  virtual void setupMenus(QMenu *file, QMenu *edit, QMenu *window);

  virtual void saveExperiment();
  virtual void saveExperimentCopy();
  virtual void saveExperimentAs();
  virtual void doEditPreferences();

  void closeEvent(QCloseEvent *event);

  void textEditContextMenu(QTextEdit* te, QMenu *menu);
  void lineEditContextMenu(QLineEdit* te, QMenu *menu);

signals:

public slots:
  void newWindow(QcepMainWindowSettings *set);

//  void shrinkPanels(int fontSize, int spacing);
//  void setFontSize(int fontSize);
//  void setSpacing(int spacing);
  virtual void printLine(QString line);
  virtual void printMessage(QString msg, QDateTime ts=QDateTime::currentDateTime());
  virtual void criticalMessage(QString msg, QDateTime ts=QDateTime::currentDateTime());
  virtual void statusMessage(QString msg, QDateTime ts=QDateTime::currentDateTime());

  void displayStatusMessage(QString msg);

  void resizeEvent(QResizeEvent *event);
  void moveEvent(QMoveEvent *event);

  void doUndo();
  void doRedo();
  void doCut();
  void doCopy();
  void doPaste();
  void doDelete();
  void doSelectAll();
  void doFind();
  void doFindSelected();
  void doFindNext();
  void doFindPrevious();

protected:
//  void shrinkDockWidget(QDockWidget *dockWidget, int fontSize, int spacing);
//  void shrinkObject(QObject *obj, int fontSize, int spacing);
//  void setObjectSpacing(QObject *obj, int spacing);

#ifndef QT_NO_DEBUG
  void checkObjectInitialization() const;
#endif

  virtual void populateWindowsMenu();
  void appendToWindowMenu(QMenu* wmenu, QcepMainWindowSettingsWPtr s);

  virtual QString windowName() const;
  virtual void updateTitle();

private:
  void doTimerUpdate();
  void clearStatusMessage();
  void onUpdateIntervalMsecChanged(int newVal);
  void allocatedMemoryChanged();

  void populateEditMenu();
  void populateRecentExperimentsMenu();
  void setupContextMenus();


  void getFindText();
  void findTextEdit(QTextEdit *te);
  void findLineEdit(QLineEdit *le);
  void findSelectedTextEdit(QTextEdit *te);
  void findSelectedLineEdit(QLineEdit *le);
  void findNextTextEdit(QTextEdit *te);
  void findNextLineEdit(QLineEdit *le);
  void findPreviousTextEdit(QTextEdit *te);
  void findPreviousLineEdit(QLineEdit *le);

protected:
  bool                m_Initialized;
  QcepObjectWPtr      m_Parent;
  QString             m_Name;

  QLabel             *m_StatusMsg;
  QProgressBar       *m_Progress;
  QProgressBar       *m_AllocationStatus;
  QTimer              m_StatusTimer;
  QTimer              m_UpdateTimer;

  QMenu              *m_FileMenuP;
  QMenu              *m_EditMenuP;
  QMenu              *m_WindowMenuP;
  QMenu              *m_RecentExperimentsMenu;

  QAction            *m_ActionNewExperiment;
  QAction            *m_ActionRecentExperiments;
  QAction            *m_ActionOpenExperiment;
  QAction            *m_ActionCloseExperiment;

  QAction            *m_ActionSaveExperiment;
  QAction            *m_ActionSaveExperimentAs;
  QAction            *m_ActionSaveExperimentCopy;

  QAction            *m_ActionGlobalPreferences;
  QAction            *m_ActionExperimentPreferences;
  QAction            *m_ActionQuit;

  QAction            *m_ActionUndo;
  QAction            *m_ActionRedo;
  QAction            *m_ActionCut;
  QAction            *m_ActionCopy;
  QAction            *m_ActionPaste;
  QAction            *m_ActionDelete;
  QAction            *m_ActionSelectAll;

public:
  QAction            *m_ActionFind;
  QAction            *m_ActionFindSelected;
  QAction            *m_ActionFindNext;
  QAction            *m_ActionFindPrevious;
};

#endif // QCEPMAINWINDOW_H
