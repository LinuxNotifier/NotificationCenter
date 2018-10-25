#include "pluginmanager.h"
#include "notificationcenter.h"
#include "plugininterface.h"
#include "ncdatabase.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QTimer>

PluginManager::PluginManager(NotificationCenter *parent) :
    QObject(parent),
    m_ncDb(NcDatabase::instance())
{
    connect(parent, SIGNAL(pluginEnabled(const QString)), this, SLOT(onPluginEnabled(const QString)));
    connect(parent, SIGNAL(pluginDisabled(const QString)), this, SLOT(onPluginDisabled(const QString)));
    connect(parent, SIGNAL(pluginRemoved(const QString)), this, SLOT(onPluginRemoved(const QString)));
    initPluginTable();
    QTimer::singleShot(1000, this, &PluginManager::loadPlugins);
}

PluginManager::~PluginManager()
{

}

void PluginManager::initPluginTable()
{
    QSqlQuery query(m_ncDb.internalDatabase());
    if (!query.exec("CREATE TABLE IF NOT EXISTS plugins "
                "(plugin_id TEXT PRIMARY KEY NOT NULL, "
                "name TEXT, "
                "author TEXT, "
                "enabled BOOL, "
                "path TEXT)"
                )) {
        qCritical() << QObject::tr("creating table plugins failed");
        qCritical() << query.lastError();
        m_valid = false;
    }
    else
        m_valid = true;
}

void PluginManager::loadPlugins()
{
    QDir pluginDir(qApp->applicationDirPath());
    if (!pluginDir.cd("plugins")) {
        if (!pluginDir.mkdir("plugins")) {
            qWarning() << tr("creating plugins directory failed");
            return;
        }
        pluginDir.cd("plugins");
    }
    pluginDir.setSorting(QDir::Name);
    QStringList files = pluginDir.entryList(QDir::Files);

    for (const QString file : files)
    {
        if (!QLibrary::isLibrary(file))
            continue;
#if DEBUG
        qDebug() << "checking: " << file;
#endif
        QPluginLoader *pluginLoader = new QPluginLoader(pluginDir.absoluteFilePath(file), this);
#if DEBUG
        qDebug() << "loading plugin: " << pluginLoader->metaData();
#endif

        PluginInterface *interface = qobject_cast<PluginInterface*>(pluginLoader->instance());
        if (!interface)
        {
            qWarning() << pluginLoader->errorString();
            pluginLoader->unload();
            pluginLoader->deleteLater();
            return;
        }
#if DEBUG
        qDebug() << QString("plugin %1 loaded").arg(pluginLoader->fileName());
        // qDebug() << interface->interfaceVersion();
#endif
        m_pluginMap[pluginLoader->fileName()] = pluginLoader;
    }
}

void PluginManager::onPluginEnabled(const QString pluginId)
{
    qDebug() << QString("plugin %1 enabled").arg(pluginId);
}

void PluginManager::onPluginDisabled(const QString pluginId)
{
    qDebug() << QString("plugin %1 disabled").arg(pluginId);
}

void PluginManager::onPluginRemoved(const QString pluginId)
{
    qDebug() << QString("plugin %1 removed").arg(pluginId);
}
