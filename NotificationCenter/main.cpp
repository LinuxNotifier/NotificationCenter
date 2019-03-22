#include "mainwindow.h"
#include "notificationcenter.h"
#include "notificationmanager.h"
#include "extensionmanager.h"
#include "notification.h"
#include "notifier.h"
#include "debug.h"
#include "global.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QObject>
#include <QLocale>
#include <memory>
#include <QSettings>
#include <QFile>
#include <QThread>
#include <QTimer>

NC_APP("org.linuxnotifier.Notifier")

void initSettings();
bool setLanguage(const QString& language);

int main(int argc, char *argv[])
{
#ifdef DEBUG
    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
#endif
    QApplication app(argc, argv);
    app.setOrganizationName("LinuxNotifier");
    app.setOrganizationDomain("https://github.com/LinuxNotifier");
    app.setApplicationName("NotificationCenter");
    app.setApplicationVersion(__NOTIFICATIONCENTER_VERSION__);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    QSettings settings;
    qDebug() << settings.fileName();
    if (!QFile(settings.fileName()).exists())
        initSettings();

    setLanguage(settings.value("language", "zh_TW").toString());

    NotificationCenter &nc = NotificationCenter::instance();

    MainWindow w;
    nc.setView(&w);

    ExtensionManager extensionManager(&nc);
    nc.setPluginModel(&extensionManager);

    w.show();

    // for some weird, still unknown reason, app.exec() must be executed in python
    // if we want to make it work with threading support in Python.
    // TODO: check if python module is enabled
    int timeout = 10 * 1000;
    while (timeout > 0) {
        QApplication::processEvents();
        QThread::msleep(5);
        timeout -= 5;
    }
    // this should never be executed if the python module is loaded
    return app.exec();
}

bool setLanguage(const QString& language)
{
    static QTranslator translator;
    if (translator.load(qApp->applicationDirPath() + "/languages/NotificationCenter_" + language + ".qm")) {
        if (qApp->installTranslator(&translator)) {
#if DEBUG
            qDebug() << QObject::tr("language set to %1").arg(language);
#endif
            return true;
        }
        else {
            qWarning() << "installing translator for " + language + " failed";
            return false;
        }
    }
    else {
        qWarning() << "loading translation file for " + language + " failed";
        return false;
    }
}

void initSettings()
{
    QSettings settings;
    // beginGroup
    settings.setValue("language", "zh_TW");
    settings.setValue("quiet", false);
}
