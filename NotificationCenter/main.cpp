#include "mainwindow.h"
#include "notificationcenter.h"
#include "nclogging.h"
#include "ncglobal.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QObject>
#include <QLocale>
#include <stdio.h>

bool setLanguage(const QString& language);

int main(int argc, char *argv[])
{
#ifdef DEBUG
    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
#endif

    QApplication app(argc, argv);
    app.setOrganizationName("LinuxNotifier");
    app.setApplicationName("NotificationCenter");
    app.setApplicationVersion(__NOTIFICATIONCENTER_VERSION__);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    setLanguage("zh_TW");

    NotificationCenter::instance();

    MainWindow w;
    w.show();

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
