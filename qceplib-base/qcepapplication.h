#ifndef QCEPAPPLICATION_H
#define QCEPAPPLICATION_H

#include "qceplib_global.h"
#include <QApplication>
#include "qcepmacros.h"
#include "qcepproperty.h"
#include "qcepdataobject-ptr.h"
#include "qcepobject.h"
#include "qapplication-ptr.h"
#include "qcepapplication-ptr.h"
#include "qcepexperiment-ptr.h"
#include "qcepallocator-ptr.h"
#include "qcepstartupwindow-ptr.h"
#include "qcepstartupwindowsettings-ptr.h"
#include "qsettings-ptr.h"
#include "qcommandlineparser-ptr.h"
#include "qcommandlineoption-ptr.h"

class QCEP_EXPORT QcepApplication : public QcepObject
{
  Q_OBJECT

private:
  typedef QcepObject inherited;

public:
  explicit QcepApplication(int &argc, char **argv);
  void initializeRoot();

  static QcepApplicationWPtr findApplication(QcepObjectWPtr p);

  virtual void setDefaultObjectData(QcepDataObject *obj);

  int exec();
  void processEvents() const;
  void exit();
  void quit();
  void possiblyQuit();
  virtual void shutdownDocuments();
  bool wantToQuit();

  void appendCommand(QString cmd);
  void appendScript(QString script);
  void appendFile(QString file);

  void addCommandLineOption(QCommandLineOption *opt);
  virtual void parseCommandLine();

  virtual void openStartupWindow();
  virtual void closeStartupWindow();

  void readSettings(QSettings *settings);
  void writeSettings(QSettings *settings);

  virtual QString applicationName() = 0;
  virtual QString applicationVersion() = 0;
  virtual QString applicationDescription() = 0;
  virtual QIcon   applicationIcon() = 0;

  virtual void openExperiment(QString path) = 0;
  virtual void openRecentExperiment(QString path) = 0;

  virtual void editGlobalPreferences() = 0;
  virtual void createNewExperiment() = 0;
  virtual void chooseExistingExperiment() = 0;

  virtual void readApplicationSettings();
  virtual void writeApplicationSettings();

  virtual QSettingsPtr applicationSettings() = 0;


  virtual QcepExperimentPtr experiment(int i) const = 0;

  QcepAllocatorWPtr allocator() const;

  void debugChanged(qint64 newValue);

  Q_ENUM(QcepDebugFlags)

  Q_INVOKABLE virtual int  debugFlag(QString f);
  Q_INVOKABLE virtual QString debugFlagName(int i);
  Q_INVOKABLE virtual QString debugFlagOption(int i);
  Q_INVOKABLE virtual QString debugFlagDescription(int i);
  Q_INVOKABLE virtual int  debugFlagCount();
  Q_INVOKABLE virtual void listDebugFlags();

  Q_INVOKABLE void logMessage(QString msg) const;
  Q_INVOKABLE void warningMessage(QString msg, QDateTime dt=QDateTime::currentDateTime()) const;
  Q_INVOKABLE void statusMessage(QString msg, QDateTime dt=QDateTime::currentDateTime()) const;
  Q_INVOKABLE void criticalMessage(QString msg, QDateTime dt=QDateTime::currentDateTime()) const;
  Q_INVOKABLE void printLine(QString msg) const;

  Q_INVOKABLE void splashMessage(QString msg, QDateTime dt=QDateTime::currentDateTime());
  Q_INVOKABLE void printMessage(QString msg, QDateTime dt=QDateTime::currentDateTime()) const;

public slots:
  void openObjectBrowserWindow(QcepObjectWPtr obj);

protected:
  QApplicationPtr        m_Application;
  QCommandLineParserPtr  m_CommandLineParser;

private:
  QStringList makeStringListFromArgs(int argc, char **argv);

public:
  Q_PROPERTY(int    argc       READ get_Argc      WRITE set_Argc STORED false)
  QCEP_INTEGER_PROPERTY(Argc)

  Q_PROPERTY(QStringList argv READ get_Argv WRITE set_Argv STORED false)
  QCEP_STRING_LIST_PROPERTY(Argv)

  Q_PROPERTY(int    guiWanted  READ get_GuiWanted WRITE set_GuiWanted STORED false)
  QCEP_INTEGER_PROPERTY(GuiWanted)

  Q_PROPERTY(qint64    debug         READ get_Debug WRITE set_Debug)
  QCEP_INTEGER64_PROPERTY(Debug)

  Q_PROPERTY(QString currentExperiment READ get_CurrentExperiment WRITE set_CurrentExperiment)
  QCEP_STRING_PROPERTY(CurrentExperiment)

  Q_PROPERTY(QStringList recentExperiments READ get_RecentExperiments WRITE set_RecentExperiments)
  QCEP_STRING_LIST_PROPERTY(RecentExperiments)

  Q_PROPERTY(int recentExperimentsSize READ get_RecentExperimentsSize WRITE set_RecentExperimentsSize)
  QCEP_INTEGER_PROPERTY(RecentExperimentsSize)

  Q_PROPERTY(int experimentCount READ get_ExperimentCount WRITE set_ExperimentCount STORED false)
  QCEP_INTEGER_PROPERTY(ExperimentCount)

  Q_PROPERTY(int    updateIntervalMsec   READ get_UpdateIntervalMsec WRITE set_UpdateIntervalMsec)
  QCEP_INTEGER_PROPERTY(UpdateIntervalMsec)

  Q_PROPERTY(int    messageWindowLines   READ get_MessageWindowLines WRITE set_MessageWindowLines)
  QCEP_INTEGER_PROPERTY(MessageWindowLines)

  Q_PROPERTY(int lockerCount READ get_LockerCount WRITE set_LockerCount STORED false)
  QCEP_INTEGER_PROPERTY(LockerCount)

  Q_PROPERTY(double lockerRate READ get_LockerRate WRITE set_LockerRate STORED false)
  QCEP_DOUBLE_PROPERTY(LockerRate)

  Q_PROPERTY(QStringList cmdList READ get_CmdList WRITE set_CmdList STORED false)
  QCEP_STRING_LIST_PROPERTY(CmdList)

  Q_PROPERTY(QStringList fileList READ get_FileList WRITE set_FileList STORED false)
  QCEP_STRING_LIST_PROPERTY(FileList)

  Q_PROPERTY(int    openNew         READ get_OpenNew WRITE set_OpenNew STORED false)
  QCEP_INTEGER_PROPERTY(OpenNew)

  Q_PROPERTY(int    freshStart         READ get_FreshStart WRITE set_FreshStart STORED false)
  QCEP_INTEGER_PROPERTY(FreshStart)

private:
  QVector<QCommandLineOption*>    m_CommandLineOptions;
  QcepAllocatorPtr                m_Allocator;
  QcepStartupWindowSettingsWPtr   m_StartupWindowSettings;
  QcepStartupWindowWPtr           m_StartupWindow;
};

extern QCEP_EXPORT QcepApplication *g_Application;

#endif // QCEPAPPLICATION_H
