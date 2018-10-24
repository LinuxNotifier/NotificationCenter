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

void NcDatabase::initDatabase()
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
