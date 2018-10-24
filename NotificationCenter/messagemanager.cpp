#include "messagemanager.h"
#include "dbmanager.h"
#include "notificationcenter.h"
#include "ncmessage.h"
#include "ncglobal.h"
#include "nclogging.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QBuffer>
#include <QPixmap>
#include <QIcon>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QUuid>
#include <QDateTime>
#include <QSqlError>

MessageManager::MessageManager(NotificationCenter *parent) :
    QObject(parent),
    m_dbManager(DatabaseManager::instance())
{
    connect(parent, SIGNAL(messageClosed(const QString&)), this, SLOT(messageClosed(const QString&)));
    initMessageTable();
}

MessageManager::~MessageManager()
{

}

bool MessageManager::isValid()
{
    return m_valid;
}

void MessageManager::initMessageTable()
{
    QSqlQuery query(m_dbManager.internalDatabase());
    if (!query.exec("CREATE TABLE IF NOT EXISTS messages "
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
        qCritical() << query.lastError();
        m_valid = false;
    }
    else
        m_valid = true;
}

void MessageManager::messageClosed(const QString& messageId)
{
    qDebug() << "message closed:" << messageId;
}

bool MessageManager::insertMessage(const NcMessage& message)
{
    return MessageManager::insertMessage(message.messageId(),
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

bool MessageManager::insertMessage(const QString& message_id, const QString& title,
        const QString& preview, const QString& content,
        const QIcon& icon, int action,
        const QString& created_time, int priority, int duration,
        const QString& notification_id, const QString& application_id)
{
    QSqlQuery query(m_dbManager.internalDatabase());
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
    bool result = query.exec();
    if (!result)
        qCritical() << query.lastError();
    return result;
}

bool MessageManager::alterMessage(const NcMessage& message)
{
    return MessageManager::alterMessage(message.messageId(),
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

bool MessageManager::alterMessage(const QString& message_id, const QString& title,
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

bool MessageManager::deleteMessage(const QString& message_id)
{
    QSqlQuery query(m_dbManager.internalDatabase());
    query.prepare("DELETE FROM messages WHERE message_id = :message_id");
    query.bindValue(":message_id", message_id);
    bool result = query.exec();
    if (!result)
        qCritical() << query.lastError();
    return result;
}

NcMessage& MessageManager::selectMessage(const QString& message_id)
{
    QSqlQuery query(m_dbManager.internalDatabase());
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
        qCritical() << query.lastError();
        qDebug() << "no such message:" << message_id;
    }
#endif
    return message;
}

MessageList MessageManager::selectAllMessages()
{
    MessageList messageList;
    QSqlQuery query(m_dbManager.internalDatabase());
    if (!query.exec("SELECT message_id FROM messages ORDER BY created_time")) {
        qCritical() << query.lastError();
        return messageList;
    }
    while (query.next()) {
        messageList << &selectMessage(query.value(0).toString());
    }
    return messageList;
}
