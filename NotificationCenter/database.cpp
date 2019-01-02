#include "database.h"
#include "database_p.h"
#include "notificationcenter.h"
#include "debug.h"
#include "global.h"
#include <QDir>
#include <QApplication>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QByteArray>
#include <QBuffer>
#include <QPixmap>
#include <QIcon>

DatabasePrivate::DatabasePrivate(Database *q_ptr) :
    q_ptr(q_ptr)
{

}

DatabasePrivate::~DatabasePrivate()
{

}

Database::Database(NotificationCenter *parent) :
    QObject(parent),
    d_ptr(new DatabasePrivate(this))
{
    d_ptr->m_dbName = "ncdb";
    initDatabase();
}

Database::~Database()
{
    
}

Database& Database::instance()
{
    static Database ncDb(&NotificationCenter::instance());
    return ncDb;
}

QString Database::dbName() const
{
    return d_ptr->m_dbName;
}

void Database::initDatabase()
{
    const QString dbDirName = "dbs";
    const QString dbFileName = "nc.db";
    QDir dbDir = QDir(qApp->applicationDirPath());
    if (!dbDir.cd(dbDirName)) {
        if (!dbDir.mkdir(dbDirName)) {
            qWarning() << tr("create database directory %1 failed").arg(dbDirName);
            return;
        }
        dbDir.cd(dbDirName);
    }
#if DEBUG
    if (!dbDir.exists(dbFileName))
        qInfo() << "creating new database";
#endif

    d_ptr->m_db = QSqlDatabase::addDatabase("QSQLITE", d_ptr->m_dbName);
    d_ptr->m_db.setDatabaseName(dbDir.absoluteFilePath(dbFileName));
    if (!d_ptr->m_db.open()) {
        qCritical() << QObject::tr("Error: connecting to database \"%1\" failed").arg(d_ptr->m_dbName);
        d_ptr->m_valid = false;
    }
    else {
        d_ptr->m_valid = true;
#if DEBUG
        qDebug() << QString("connected to database \"%1\"").arg(d_ptr->m_dbName);
#endif
    }
}
