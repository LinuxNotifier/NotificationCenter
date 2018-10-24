#include "dbmanager.h"
#include "dbmanager_p.h"
#include "notificationcenter.h"
#include "nclogging.h"
#include "ncglobal.h"
#include <QDir>
#include <QApplication>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QByteArray>
#include <QBuffer>
#include <QPixmap>
#include <QIcon>

DatabaseManagerPrivate::DatabaseManagerPrivate(DatabaseManager *q_ptr) :
    q_ptr(q_ptr)
{

}

DatabaseManagerPrivate::~DatabaseManagerPrivate()
{

}

DatabaseManager::DatabaseManager(NotificationCenter *parent) :
    QObject(parent),
    d_ptr(new DatabaseManagerPrivate(this))
{
    initDatabase();
}

DatabaseManager::~DatabaseManager()
{
    
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager databaseManager(&NotificationCenter::instance());
    return databaseManager;
}

void DatabaseManager::initDatabase()
{
    const QString dbDirName = "dbs";
    const QString dbFileName = "nc.sqlite";
    QDir dbDir = QDir(qApp->applicationDirPath());
    if (!dbDir.cd(dbDirName)) {
        dbDir.mkdir(dbDirName);
        dbDir.cd(dbDirName);
    }
#if DEBUG
    if (!dbDir.exists(dbFileName))
        qInfo() << "creating new database";
#endif

    d_ptr->m_db = QSqlDatabase::addDatabase("QSQLITE", "ncdb");
    d_ptr->m_db.setDatabaseName(dbDir.absoluteFilePath(dbFileName));
    if (!d_ptr->m_db.open()) {
        qCritical() << QObject::tr("Error: connecting to database \"ncdb\" failed");
        d_ptr->m_valid = false;
    }
    else {
        d_ptr->m_valid = true;
#if DEBUG
        qDebug() << "connected to database \"ncdb\"";
#endif
    }
}
