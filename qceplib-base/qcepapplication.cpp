#include "qcepapplication.h"
#include "qcepobjecttreewindow.h"
#include <QThread>
#include <QApplication>
#include <QMessageBox>
#include <QCommandLineParser>
#include "qcepdataobject.h"
#include "qceppowderpoint.h"
#include "qcepcalibrantdspacing.h"
#include "qcepcalibrantdspacings.h"
#include "qcepallocator.h"
#include "qcepstartupwindow.h"
#include "qcepstartupwindowsettings.h"
#include "qcepexperiment.h"

QcepApplication *g_Application = NULL;

QcepApplication::QcepApplication(int &argc, char **argv) :
  inherited("application"),
  m_Argc(this, "argc", argc, "Number of Command Line Arguments"),
  m_Argv(this, "argv", makeStringListFromArgs(argc, argv), "Command Line Arguments"),
  m_GuiWanted(this, "guiWanted", 1, "GUI Wanted?"),
  m_Debug(this,"debug", 0, "Debug Level"),
  m_CurrentExperiment(this, "currentExperiment", "", "Current Experiment"),
  m_RecentExperiments(this, "recentExperiments", QStringList(), "Recent Experiments"),
  m_RecentExperimentsSize(this,"recentExperimentsSize", 8, "Number of Recent Experiments to Remember"),
  m_ExperimentCount(this, "experimentCount", 0, "Number of open experiments"),
  m_UpdateIntervalMsec(this, "updateIntervalMsec", 1000, "Time Intervale for Updates (in msec)"),
  m_MessageWindowLines(this, "messageWindowLines", 1000, "Number of Lines in Message Window (0 = unlimited)"),
  m_LockerCount(this, "lockerCount", 0, "Number of mutex locks taken"),
  m_LockerRate(this, "lockerRate", 0, "Mutex Locking Rate"),
  m_CmdList(this, "cmdList", QStringList(), "Commands to Execute"),
  m_FileList(this, "fileList", QStringList(), "Files to Process"),
  m_OpenNew(this,"openNew", 0, "Open a new experiment"),
  m_FreshStart(this,"freshStart", 0, "Do a Fresh Start")
{
  g_Application = this;

  m_Application =
      QApplicationPtr(
        new QApplication(argc, argv));

  m_Allocator = QcepAllocatorPtr(
        new QcepAllocator("allocator"));

  QcepProperty::registerMetaTypes();
  QcepPowderPoint::registerMetaTypes();
  QcepPowderPointVector::registerMetaTypes();
  QcepCalibrantDSpacing::registerMetaTypes();
  QcepCalibrantDSpacings::registerMetaTypes();
}

void QcepApplication::initializeRoot()
{
  GUI_THREAD_CHECK;

  inherited::initializeRoot();

  QThread::currentThread()->setObjectName("applicationThread");

  if (m_Allocator) {
    m_Allocator->initialize(sharedFromThis());
  }

  m_StartupWindowSettings =
      qSharedPointerDynamicCast<QcepStartupWindowSettings>(
        appendWindowSettings(
          QcepStartupWindowSettingsPtr(
            new QcepStartupWindowSettings("startupWindowSettings"))));

  if (m_StartupWindowSettings) {
    m_StartupWindowSettings->initialize(sharedFromThis());
  }

  m_CommandLineParser =
      QCommandLineParserPtr(
        new QCommandLineParser());

  CONNECT_CHECK(
        connect(prop_Debug(), &QcepInt64Property::valueChanged,
                this,         &QcepApplication::debugChanged));

  readApplicationSettings();

  processEvents();

  parseCommandLine();

  if (get_GuiWanted()) {
    openStartupWindow();
  }

  processEvents();
}

void QcepApplication::setDefaultObjectData(QcepDataObject *obj)
{
  if (obj) {
    obj->set_Creator(applicationName());
    obj->set_Version(applicationVersion());
    obj->set_QtVersion(qVersion());
  }
}

QcepApplicationWPtr QcepApplication::findApplication(QcepObjectWPtr p)
{
  QcepApplicationWPtr res =
      qSharedPointerDynamicCast<QcepApplication>(p);

  if (res == NULL) {
    QcepObjectPtr objp(p);

    if (objp) {
      res = findApplication(objp->parentPtr());
    }
  }

  return res;
}

int QcepApplication::exec()
{
  int res = 0;

  if (m_Application) {
    res = m_Application -> exec();
  }

  return res;
}

void QcepApplication::processEvents() const
{
  if (m_Application) {
    m_Application -> processEvents();
  }
}

void QcepApplication::exit()
{
  if (m_Application) {
    m_Application -> exit();
  }
}

void QcepApplication::quit()
{
  if (m_Application) {
    m_Application -> quit();
  }
}

void QcepApplication::shutdownDocuments()
{
  printf("QcepApplication::shutdownDocuments\n");
}

void QcepApplication::possiblyQuit()
{
  if (wantToQuit()) {
    shutdownDocuments();
    quit();
  }
}

bool QcepApplication::wantToQuit()
{
  return QMessageBox::question(NULL, tr("Really Quit?"),
                               tr("Do you really want to exit the application?"),
                               QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok;
}

void QcepApplication::appendCommand(QString cmd)
{
  prop_CmdList()->appendValue(cmd);
}

void QcepApplication::appendScript(QString script)
{
  prop_CmdList()->appendValue(tr("loadScript(\"%1\")").arg(script));
}

void QcepApplication::appendFile(QString file)
{
  prop_FileList()->appendValue(file);
}

void QcepApplication::addCommandLineOption(QCommandLineOption *opt)
{
  m_CommandLineOptions.append(opt);
}

void QcepApplication::parseCommandLine()
{
  THREAD_CHECK;

  m_CommandLineParser -> setApplicationDescription(applicationDescription());
  m_CommandLineParser -> addHelpOption();
  m_CommandLineParser -> addVersionOption();
  m_CommandLineParser -> addPositionalArgument("files", "Files to open, optionally", "[file...]");

  QCommandLineOption newOption({"n", "new"},      "Open new");
  m_CommandLineParser -> addOption(newOption);

  QCommandLineOption freshOption({"f", "fresh"},  "Fresh start");
  m_CommandLineParser -> addOption(freshOption);

  QCommandLineOption debugOption({"d", "debug"},  "Set debug level", "debugLevel");
  m_CommandLineParser -> addOption(debugOption);

  QCommandLineOption debugListOption("Dlist", "List available debug flags");
  m_CommandLineParser -> addOption(debugListOption);

  QCommandLineOption debugNoneOption("Dnone", "Unset all debug flags");
  m_CommandLineParser -> addOption(debugNoneOption);

  QList<QCommandLineOption> debugFlagOptions;

  for (int i=0; i<debugFlagCount(); i++) {
    QString opt = debugFlagOption(i);
    QString dsc = debugFlagDescription(i);

    debugFlagOptions.append(
          QCommandLineOption(opt.mid(1), dsc));
  }

  m_CommandLineParser -> addOptions(debugFlagOptions);

  QCommandLineOption noGuiOption("nogui", "No GUI");
  m_CommandLineParser -> addOption(noGuiOption);

  QCommandLineOption guiOption("gui", "Want GUI");
  m_CommandLineParser -> addOption(guiOption);

  QCommandLineOption cmdOption({"c", "command"},  "Execute command (may be repeated)" , "command");
  m_CommandLineParser -> addOption(cmdOption);

  QCommandLineOption scriptOption({"s", "script"}, "Read script file (may be repeated)", "scriptfile");
  m_CommandLineParser -> addOption(scriptOption);

  int nOpts = m_CommandLineOptions.count();

  for (int i=nOpts-1; i>=0; --i) {
    m_CommandLineParser -> addOption(*m_CommandLineOptions.value(i));
  }

  QStringList args(QCoreApplication::arguments());

  m_CommandLineParser -> setSingleDashWordOptionMode(
        QCommandLineParser::ParseAsLongOptions);

  m_CommandLineParser -> process(args);

  if (m_CommandLineParser -> isSet(newOption)) {
    set_OpenNew(true);
  }

  if (m_CommandLineParser -> isSet(freshOption)) {
    set_FreshStart(true);
  }

  if (m_CommandLineParser -> isSet(debugOption)) {
    qint64 dbg;
    if (sscanf(qPrintable(m_CommandLineParser -> value(debugOption)),
               "%lld", &dbg)==1) {
      set_Debug(dbg);
    }
  }

  qint64 dbg = get_Debug();
  bool dbgChanged = false;

  if (m_CommandLineParser -> isSet(debugNoneOption)) {
    dbg = 0;
    dbgChanged = true;
  }

  for (int i=0; i<debugFlagCount(); i++) {
    if (m_CommandLineParser -> isSet(debugFlagOptions[i])) {
      dbg |= qint64(1) << i;
      dbgChanged = true;
    }
  }

  if (dbgChanged) {
    set_Debug(dbg);

#ifndef QT_NO_DEBUG
    printf(" new debug level 0x%llx\n", get_Debug());
#endif
  }

  if (m_CommandLineParser -> isSet(debugListOption)) {
    listDebugFlags();
    ::exit(0);
  }

  if (m_CommandLineParser -> isSet(noGuiOption)) {
    set_GuiWanted(false);
  }

  if (m_CommandLineParser -> isSet(guiOption)) {
    set_GuiWanted(true);
  }

  if (m_CommandLineParser -> isSet(cmdOption) || m_CommandLineParser -> isSet(scriptOption)) {
    // Want to preserve order of -c and -s options
    QStringList cnam = cmdOption.names();
    QStringList snam = scriptOption.names();
    QStringList opts = m_CommandLineParser -> optionNames();
    QStringList cmds = m_CommandLineParser -> values(cmdOption);
    QStringList scrp = m_CommandLineParser -> values(scriptOption);

    for (int i=0, ic=0, is=0; i<opts.size(); i++) {
      QString opt = opts.value(i);

      foreach( QString nam, cnam) {
        if (opt == nam) {
          QString cmd = cmds.value(ic++);

          printMessage(tr("cmd: %1").arg(cmd));

          appendCommand(cmd);
        }
      }

      foreach(QString nam, snam) {
        if (opt == nam) {
          QString script = scrp.value(is++);

          printMessage(tr("Script: %1").arg(script));

          appendScript(script);
        }
      }
    }
  }

  QStringList files(m_CommandLineParser -> positionalArguments());

  foreach(QString f, files) {
    printMessage(tr("File: %1").arg(f));

    appendFile(f);
  }
}

void QcepApplication::debugChanged(qint64 newValue)
{
  if (g_DebugLevel) {
    printMessage(tr("Debug level changed from %1 to %2").arg(g_DebugLevel->debugLevel()).arg(newValue));

    g_DebugLevel->setDebugLevel(newValue);
  }
}

void QcepApplication::openStartupWindow()
{
  GUI_THREAD_CHECK;

  if (m_StartupWindowSettings) {
    m_StartupWindow =
        qSharedPointerDynamicCast<QcepStartupWindow>(
          m_StartupWindowSettings -> newWindow());

    m_StartupWindow -> initialize(sharedFromThis());

    m_StartupWindow -> setApplicationIcon(applicationIcon());
    m_StartupWindow -> setApplicationDescription(
          applicationDescription()+"\n"
          "Guy Jennings\n"
          "Version " + applicationVersion() + "\n"
          "Build : " __DATE__ " : " __TIME__);

    m_StartupWindow -> setWindowTitle(applicationDescription());
    m_StartupWindow -> setWindowIcon(applicationIcon());
    m_StartupWindow -> show();
    m_StartupWindow -> raise();
  }
}

void QcepApplication::closeStartupWindow()
{
  GUI_THREAD_CHECK;

  if (m_StartupWindow) {
    m_StartupWindow -> hide();
  }
}

QcepAllocatorWPtr QcepApplication::allocator() const
{
  return m_Allocator;
}

void QcepApplication::readApplicationSettings()
{
  QSettingsPtr set(applicationSettings());

  if (set) {
    set -> beginGroup("application");
    readSettings(set.data());
    set -> endGroup();
  }
}

void QcepApplication::writeApplicationSettings()
{
  QSettingsPtr set(applicationSettings());

  if (set) {
    set -> beginGroup("application");
    writeSettings(set.data());
    set -> endGroup();
    setChanged(0);
  }
}

void QcepApplication::readSettings(QSettings *settings)
{
  inherited::readSettings(settings);

  if (m_Allocator) {
    settings->beginGroup("allocator");
    m_Allocator->readSettings(settings);
    settings->endGroup();
  }

  if (m_StartupWindowSettings) {
    settings->beginGroup("startupWindowSettings");
    m_StartupWindowSettings->readSettings(settings);
    settings->endGroup();
  }
}

void QcepApplication::writeSettings(QSettings *settings)
{
  inherited::writeSettings(settings);

  if (m_Allocator) {
    settings->beginGroup("allocator");
    m_Allocator->writeSettings(settings);
    settings->endGroup();
  }

  if (m_StartupWindowSettings) {
    settings->beginGroup("startupWindowSettings");
    m_StartupWindowSettings->writeSettings(settings);
    settings->endGroup();
  }
}

void QcepApplication::openObjectBrowserWindow(QcepObjectWPtr obj)
{
  GUI_THREAD_CHECK;

  QcepObjectTreeWindow *w =
      new QcepObjectTreeWindow(NULL, obj);

  w->show();
  w->raise();
}

QStringList QcepApplication::makeStringListFromArgs(int argc, char **argv)
{
  QStringList res;

  for (int i=0; i<argc; i++) {
    res.append(argv[i]);
  }

  return res;
}

int QcepApplication::debugFlag(QString f)
{
  int n1=0;

  if (g_DebugLevel) {
    n1 = g_DebugLevel -> debugFlagCheck(f);
  }

  return n1;
}

QString QcepApplication::debugFlagName(int i)
{
  QString res = "";

  if (g_DebugLevel) {
    res = g_DebugLevel -> debugFlagName(i);
  }

  return res;
}

int QcepApplication::debugFlagCount()
{
  int n = 0;

  if (g_DebugLevel) {
    n = g_DebugLevel -> debugFlagCount();
  }

  return n;
}

QString QcepApplication::debugFlagOption(int i)
{
  QString res;
  QString name = debugFlagName(i);

  if (name.startsWith("DEBUG_")) {
    res = tr("-D%1").arg(name.mid(6));
  }

  return res;
}

QString QcepApplication::debugFlagDescription(int i)
{
  QString res;

  if (g_DebugLevel) {
    res = g_DebugLevel -> message(i);
  }

  return res;
}

void QcepApplication::listDebugFlags()
{
  for (int i=0; i<debugFlagCount(); i++) {
    printf("%-20s : %s\n",
           qPrintable(debugFlagOption(i)),
           qPrintable(debugFlagDescription(i)));
  }
}

void QcepApplication::splashMessage(QString msg, QDateTime dt)
{
//  GUI_THREAD_CHECK;

  if (get_GuiWanted() && m_StartupWindow) {
    INVOKE_CHECK(
          QMetaObject::invokeMethod(m_StartupWindow.data(),
                                    "appendSplashMessage",
                                    Qt::QueuedConnection,
                                    Q_ARG(QString, msg),
                                    Q_ARG(QDateTime, dt)));

    processEvents();
  } else {
    printf("STARTUP: %s\n", qPrintable(msg));
  }
}

void QcepApplication::printMessage(QString msg, QDateTime dt) const
{
  if (get_GuiWanted() && m_StartupWindow) {
    INVOKE_CHECK(
          QMetaObject::invokeMethod(m_StartupWindow.data(),
                                    "appendMessage",
                                    Qt::QueuedConnection,
                                    Q_ARG(QString, msg),
                                    Q_ARG(QString, "black"),
                                    Q_ARG(QDateTime, dt)));

  } else {
    printf("MESSAGE: %s\n", qPrintable(msg));
  }
}

void QcepApplication::logMessage(QString /*msg*/) const
{
  //TODO: implement
}

void QcepApplication::warningMessage(QString msg, QDateTime dt) const
{
  if (get_GuiWanted() && m_StartupWindow) {
    INVOKE_CHECK(
          QMetaObject::invokeMethod(m_StartupWindow.data(),
                                    "appendMessage",
                                    Q_ARG(QString, msg),
                                    Q_ARG(QString, "yellow"),
                                    Q_ARG(QDateTime, dt)));
  } else {
    printf("WARNING: %s\n", qPrintable(msg));
  }
}

void QcepApplication::statusMessage(QString msg, QDateTime dt) const
{
  if (get_GuiWanted() && m_StartupWindow) {
    INVOKE_CHECK(
          QMetaObject::invokeMethod(m_StartupWindow.data(),
                                    "appendMessage",
                                    Q_ARG(QString, msg),
                                    Q_ARG(QString, "green"),
                                    Q_ARG(QDateTime, dt)));
  } else {
    printf("STATUS: %s\n", qPrintable(msg));
  }
}

void QcepApplication::criticalMessage(QString msg, QDateTime dt) const
{
  if (get_GuiWanted() && m_StartupWindow) {
    INVOKE_CHECK(
          QMetaObject::invokeMethod(m_StartupWindow.data(),
                                    "appendMessage",
                                    Q_ARG(QString, msg),
                                    Q_ARG(QString, "red"),
                                    Q_ARG(QDateTime, dt)));
  } else {
    printf("CRITICAL: %s\n", qPrintable(msg));
  }
}

void QcepApplication::printLine(QString msg) const
{
  if (get_GuiWanted() && m_StartupWindow) {
    INVOKE_CHECK(QMetaObject::invokeMethod(m_StartupWindow.data(),
                                           "appendMessage",
                                           Q_ARG(QString, msg),
                                           Q_ARG(QString, "green"),
                                           Q_ARG(QDateTime, QDateTime::currentDateTime())));
  } else {
    printf("%s\n", qPrintable(msg));
  }
}

