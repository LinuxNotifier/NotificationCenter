#include "ncdatabase.h"
#include "ncdatabase_p.h"
#include "notificationcenter.h"
#include "ncdebug.h"
#include "ncglobal.h"
#include <QDir>
#include <QApplication>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QByteArray>
#include <QBuffer>
#include <QPixmap>
#include <QIcon>

NcDatabasePrivate::NcDatabasePrivate(NcDatabase *q_ptr) :
    q_ptr(q_ptr)
{

}

NcDatabasePrivate::~NcDatabasePrivate()
{

}

NcDatabase::NcDatabase(NotificationCenter *parent) :
    QObject(parent),
    d_ptr(new NcDatabasePrivate(this))
{
    d_ptr->m_dbName = "ncdb";
    initDatabase();
}

NcDatabase::~NcDatabase()
{
    
}

NcDatabase& NcDatabase::instance()
{
    static NcDatabase ncDb(&NotificationCenter::instance());
    return ncDb;
}

QString NcDatabase::dbName() const
{
    return d_ptr->m_dbName;
}

void NcDatabase::initDatabase()
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
