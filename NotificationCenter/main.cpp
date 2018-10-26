#include "mainwindow.h"
#include "notificationcenter.h"
#include "messagemanager.h"
#include "pluginmanager.h"
#include "ncmessage.h"
#include "ncdebug.h"
#include "ncglobal.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QObject>
#include <QLocale>
#include <memory>
#include <QSettings>
#include <QFile>

using namespace std;

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

    MessageManager msgManager(&nc);
    nc.setMessageModel(&msgManager);

    PluginManager pluginManager(&nc);
    nc.setPluginModel(&pluginManager);

    w.show();

    shared_ptr<NcMessage> msg = NotificationCenter::createMessage();
    msg->setTitle("hello")
        .setIcon(QIcon::fromTheme("edit-undo"))
        .setContent("hello world");
    NotificationCenter::notify(msg);
    NotificationCenter::notify(msg);


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
