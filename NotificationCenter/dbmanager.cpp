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
                    "(message_id TEXT PRIMARY KEY NOT NULL, "
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

bool DatabaseManager::insertMessage(const NcMessage& message)
{
    if (!message.isValid())
        return false;

    return DatabaseManager::insertMessage(message.messageId(),
            message.title(),
            message.preview(),
            message.content(),
            message.icon(),
            static_cast<int>(message.action()),
            message.createdTime(),
            static_cast<int>(message.priority()),
            message.duration(),
            message.notificationId(),
            message.applicationId()
            );
}

bool DatabaseManager::insertMessage(const QString& message_id, const QString& title,
        const QString& preview, const QString& content,
        const QIcon& icon, int action,
        const QString& created_time, int priority, int duration,
        const QString& notification_id, const QString& application_id)
{
    QSqlQuery query(m_db);
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
#if DEBUG
    qDebug() << "saving" <<pixmap << "into database";
#endif
    query.bindValue(":icon", bytes);

    query.bindValue(":priority", priority);
    query.bindValue(":created_time", created_time);
    query.bindValue(":duration", duration);
    query.bindValue(":action", action);
    query.bindValue(":notification_id", notification_id);
    query.bindValue(":application_id", application_id);
    return query.exec();
}

bool DatabaseManager::alterMessage(const NcMessage& message)
{
    return DatabaseManager::alterMessage(message.messageId(),
            message.title(),
            message.preview(),
            message.content(),
            message.icon(),
            static_cast<int>(message.action()),
            message.createdTime(),
            static_cast<int>(message.priority()),
            message.duration(),
            message.notificationId(),
            message.applicationId()
            );
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
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM messages WHERE message_id = :message_id");
    query.bindValue(":message_id", message_id);
    return query.exec();
}

NcMessage& DatabaseManager::selectMessage(const QString& message_id)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM messages WHERE message_id = :message_id");
    query.bindValue(":message_id", message_id);
    NcMessage &message = NotificationCenter::createMessage();
    if (query.exec() && query.first())
    {
        message.setMessageId(query.value(0).toString())
            .setTitle(query.value(1).toString())
            .setPreview(query.value(2).toString())
            .setContent(query.value(3).toString())
            .setAction(static_cast<NcMessage::Action>(query.value(5).toInt()))
            .setCreatedTime(query.value(6).toString())
            .setPriority(static_cast<NcMessage::Priority>(query.value(7).toInt()))
            .setDuration(query.value(8).toInt())
            .setNotificationId(query.value(9).toString())
            .setApplicationId(query.value(10).toString());

        QPixmap pixmap;
        if (pixmap.loadFromData(query.value(4).toByteArray(), "PNG") and !pixmap.isNull()) {
            message.setIcon(QIcon(pixmap));
#if DEBUG
        qDebug() << "loading icon from database succeeded" << pixmap;
#endif
        }
        message.setValid();
    }
#if DEBUG
    else {
        qDebug() << "no such message:" << message_id;
    }
#endif
    return message;
}

MessageList DatabaseManager::selectAllMessages()
{
    MessageList messageList;
    QSqlQuery query(m_db);
    if (!query.exec("SELECT message_id FROM messages ORDER BY created_time"))
        return messageList;
    while (query.next()) {
        messageList << &selectMessage(query.value(0).toString());
    }
    return messageList;
}

QSqlDatabase& DatabaseManager::internalDatabase()
{
    return m_db;
}
