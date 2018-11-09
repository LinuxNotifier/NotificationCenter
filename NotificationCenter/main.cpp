#include <Python.h>
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

    Py_Initialize();
    wchar_t **python_argv = (wchar_t**)malloc((argc)* sizeof(wchar_t*));
    for (int i = 0; i < argc; i++) {
        python_argv[i] = Py_DecodeLocale(argv[i], NULL);
    }
    PySys_SetArgv(argc, python_argv);

    wchar_t *path = Py_DecodeLocale((qApp->applicationDirPath() + "/plugins/python").toLatin1().data(), NULL);
    Py_SetPath(path);
    wchar_t *program_name = Py_DecodeLocale("NotificationCenter", NULL);
    Py_SetProgramName(program_name);
    for (int i = 0; i < argc; i++) {
        PyMem_RawFree(python_argv[i]);
    }
    PyMem_RawFree(path);
    PyMem_RawFree(program_name);
    // Py_Finalize();

    // get icon filename
    // QIcon icon(":/images/notificationcenter_icon.png");
    // qDebug() << "name of icon:" << icon.name();
    // icon = QIcon::fromTheme(":dit-undo");
    // qDebug() << "name of icon:" << icon.name();

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

    shared_ptr<NcMessage> msg = NotificationCenter::createSharedMessage();
    msg->setTitle("hello")
        .setIcon(QIcon::fromTheme("edit-undo"))
        // .setContent("<b>Hi</b>\n" + QString("#include <QtCore>").toHtmlEscaped());
        // .setContent("<html><head/><body><p>sfdsdfff<img src=\":/images/notificationcenter_icon.png\"/></p><p><br/></p><p><br/></p><p><br/></p><p><br/></p><p><br/></p><p><br/></p><p><br/></p><p><br/></p><p>helo, world</p></body></html>");
        // .setContent("<html><head/><body><p>sfdsdfff<img src=\":/images/notificationcenter_icon.png\" height=\"16\" width=\"16\"/></p><p><br/></p><p><br/></p><p><br/></p><p><br/></p><p><br/></p><p><br/></p><p><br/></p><p><br/></p><p>helo, world</p></body></html>");
        .setContent("<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1&#10<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1&#10<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1&#10<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1&#10<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1&#10<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1&#10<b>Hi</b> Dany, I'm unable to do this. this file is un-editable. I tried through the terminal as well by using command - sudo gedit /etc/apt/sources.list.save.1");
        // .setContent("<b>Hi</b>, how are you doing?");
        // .setContent("<b>hello</b> world\nhello\nhello\nhello\nhello\nhello\nhello\nhello\nhello\nhello, this is a test message, you should ignore it. Hey, how are you? I'm fine. How are you? Today's weather is wonderful, how do you think? Yes, it's really wonderful.");
    // NotificationCenter::notify(msg);


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
