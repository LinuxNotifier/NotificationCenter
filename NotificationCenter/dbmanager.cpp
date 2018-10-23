#include "dbmanager.h"
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

DatabaseManager::DatabaseManager(NotificationCenter *parent) :
    QObject(parent)
{
    // TODO: connection with aprent, check if database exists
    m_notificationCenter = parent;
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

bool DatabaseManager::initDatabase()
{
    const QString dbDirName = "dbs";
    const QString dbFileName = "nc.sqlite";
    QDir dbDir = QDir(qApp->applicationDirPath());
    if (!dbDir.cd(dbDirName)) {
        dbDir.mkdir(dbDirName);
        dbDir.cd(dbDirName);
    }
    bool exists = dbDir.exists(dbFileName);

    m_db = QSqlDatabase::addDatabase("QSQLITE", "ncdb");
    m_db.setDatabaseName(dbDir.absoluteFilePath(dbFileName));
    if (!m_db.open()) {
        qCritical() << QObject::tr("Error: connecting to database \"ncdb\" failed");
        m_db = QSqlDatabase();
        return false;
    }
#if DEBUG
    else
        qDebug() << "connecting to database \"ncdb\" succeeded";
#endif
    if (!exists) {
        QSqlQuery query(m_db);
        if (!query.exec("CREATE TABLE messages "
                    "(message_id TEXT PRIMARY KEY, "
                    "title TEXT, "
                    "preview TEXT, "
                    "content TEXT, "
                    "icon BLOB, "
                    "action INTEGER, "
                    "created_time TEXT, "
                    "priority INTEGER, "
                    "duration INT, "
                    "notification_id TEXT, "
                    "application_id TEXT)"
                    )) {
            qCritical() << QObject::tr("initializing database \"ncdb\" failed");
            m_db = QSqlDatabase();
            return false;
        }
    }

    return true;
}

bool DatabaseManager::insertMessage(const QString& message_id, const QString& title,
        const QString& preview, const QString& content,
        const QIcon& icon, int action,
        const QString& created_time, int priority, int duration,
        const QString& notification_id, const QString& application_id)
{
    DatabaseManager &dbManager = DatabaseManager::instance();
    QSqlQuery query(dbManager.internalDatabase());
    query.prepare("INSERT INTO messages "
            "(message_id, "
            "title, "
            "preview, "
            "content, "
            "icon, "
            "action, "
            "created_time, "
            "priority, "
            "duration, "
            "notification_id, "
            "application_id)"
            "VALUES "
            "(:message_id, "
            ":title, "
            ":preview, "
            ":content, "
            ":icon, "
            ":action, "
            ":created_time, "
            ":priority, "
            ":duration, "
            ":notification_id, "
            ":application_id"
            ")");
    query.bindValue(":message_id", message_id);
    query.bindValue(":title", title);
    query.bindValue(":preview", preview);
    query.bindValue(":content", content);

    QPixmap pixmap = icon.pixmap(ICON_SIZE, ICON_SIZE);
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");
    qDebug() << pixmap;
    query.bindValue(":icon", bytes);

    query.bindValue(":priority", priority);
    query.bindValue(":created_time", created_time);
    query.bindValue(":duration", duration);
    query.bindValue(":action", action);
    query.bindValue(":notification_id", notification_id);
    query.bindValue(":application_id", application_id);
    return query.exec();
}

bool DatabaseManager::alterMessage(const QString& message_id, const QString& title,
        const QString& preview, const QString& content,
        const QIcon& icon, int action,
        const QString& created_time, int priority, int duration,
        const QString& notification_id, const QString& application_id)
{
    deleteMessage(message_id);
    return insertMessage(message_id, title, preview, content, icon,
            action, created_time, priority, duration,
            notification_id, application_id);
}

bool DatabaseManager::deleteMessage(const QString& message_id)
{
    DatabaseManager &dbManager = DatabaseManager::instance();
    QSqlQuery query(dbManager.internalDatabase());
    query.prepare("DELETE FROM messages WHERE message_id = :message_id");
    query.bindValue(":message_id", message_id);
    return query.exec();
}

QSqlDatabase& DatabaseManager::internalDatabase()
{
    return m_db;
}
