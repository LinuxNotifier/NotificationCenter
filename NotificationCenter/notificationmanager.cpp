#include "notificationmanager.h"
#include "database.h"
#include "notificationcenter.h"
#include "notificationchannel.h"
#include "notification.h"
#include "global.h"
#include "debug.h"
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
#include <QTimer>

NotificationManager::NotificationManager(NotificationCenter *parent) :
    QObject(parent),
    m_ncDb(&Database::instance())
{
    connect(parent, SIGNAL(messageClosed(const QString)), this, SLOT(messageClosed(const QString)));
    initMessageTable();
    // FIXME: duplicate message if new message is inserted before loading
    // messages when program starts up
    QTimer::singleShot(1000, this, &NotificationManager::loadMessages);
    // loadMessages();
}

NotificationManager::~NotificationManager()
{

}

void NotificationManager::createNotficationChannel(const NotificationChannel& channel)
{
    // mChannels.append(channel);
}

void NotificationManager::initMessageTable()
{
    QSqlQuery query(m_ncDb->internalDatabase());
    if (!query.exec("CREATE TABLE IF NOT EXISTS messages "
                "(notification_id TEXT PRIMARY KEY NOT NULL, "
                "application_id TEXT NOT NULL, "
                "title TEXT, "
                "icon BLOB, "
                "preview TEXT, "
                "content TEXT, "
                "priority INT, "
                "duration INT, "
                "data TEXT, "
                "trigger_time TEXT, "
                "created_time TEXT)"
                )) {
        qCritical() << QObject::tr("creating table \"messages\" failed");
        qCritical() << query.lastError();
        m_valid = false;
    }
    else
        m_valid = true;
}

void NotificationManager::loadMessages()
{
    MessageList msgList = selectAllMessages();
    for (const std::shared_ptr<Notification> msg : msgList) {
        Notification::Duration duration = msg->duration();
        if (duration != Notification::Duration::UntilShutdown) {
            emit newMessage(msg);
            m_messageMap[msg->notificationId()] = msg;
        }
        else {
            deleteMessage(msg->notificationId());
        }
    }
}


void NotificationManager::messageClosed(const QString notificationId)
{
    qDebug() << "message closed:" << notificationId;
    m_messageMap.remove(notificationId);
    deleteMessage(notificationId);
}

bool NotificationManager::insertMessage(std::shared_ptr<Notification> message)
{
    bool inserted = NotificationManager::insertMessage(message->notificationId(),
            message->applicationId(),
            message->title(),
            message->icon(),
            message->preview(),
            message->content(),
            message->data(),
            static_cast<int>(message->priority()),
            static_cast<int>(message->duration()),
            message->triggerTime(),
            message->createdTime()
            );
    if (inserted) {
        m_messageMap[message->notificationId()] = message;
        emit newMessage(message);
    }
    return inserted;
}

bool NotificationManager::insertMessage(const QString& notificationId, const
        QString& applicationId, const QString& title, const QIcon& icon, const
        QString& preview, const QString& content, const QString& data, int
        priority, int duration, const QString& triggerTime, const QString&
        createdTime)
{
    QSqlQuery query(m_ncDb->internalDatabase());
    query.prepare("INSERT INTO messages "
            "(notification_id, "
            "application_id, "
            "title, "
            "icon, "
            "preview, "
            "content, "
            "data, "
            "priority, "
            "duration, "
            "trigger_time, "
            "created_time)"
            "VALUES "
            "(:notification_id, "
            ":application_id, "
            ":title, "
            ":icon, "
            ":preview, "
            ":content, "
            ":data, "
            ":priority, "
            ":duration, "
            ":trigger_time, "
            ":created_time)"
            );
    query.bindValue(":notification_id", notificationId);
    qDebug() << "got notificationId:" << notificationId;
    query.bindValue(":application_id", applicationId);
    query.bindValue(":title", title);

    QPixmap pixmap = icon.pixmap(ICON_SIZE, ICON_SIZE);
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");
#if DEBUG
    qDebug() << "saving" <<pixmap << "into database";
#endif
    query.bindValue(":icon", bytes);

    query.bindValue(":preview", preview);
    query.bindValue(":content", content);
    query.bindValue(":data", data);
    query.bindValue(":priority", priority);
    query.bindValue(":duration", duration);
    query.bindValue(":trigger_time", triggerTime);
    query.bindValue(":created_time", createdTime);

    bool inserted = query.exec();
    if (!inserted)
        qWarning() << query.lastError();
    return inserted;
}

bool NotificationManager::alterMessage(std::shared_ptr<Notification> message)
{
    // return NotificationManager::alterMessage(message->notificationId(),
    //         message->title(),
    //         message->preview(),
    //         message->content(),
    //         message->icon(),
    //         // static_cast<int>(message->action()),
    //         message->createdTime(),
    //         static_cast<int>(message->priority()),
    //         static_cast<int>(message->duration()),
    //         message->notificationId(),
    //         message->applicationId()
    //         );
    return true;
}

// bool NotificationManager::alterMessage(const QString& messageId, const QString& title,
//         const QString& preview, const QString& content,
//         // const QIcon& icon, int action,
//         const QIcon& icon,
//         const QString& created_time, int priority, int duration,
//         const QString& notificationId, const QString& applicationId)
// {
//     deleteMessage(notificationId);
//     return insertMessage(notificationId, title, preview, content, icon,
//             // action, created_time, priority, duration,
//             created_time, priority, duration,
//             notificationId, applicationId);
// }

bool NotificationManager::deleteMessage(const QString& notificationId)
{
    QSqlQuery query(m_ncDb->internalDatabase());
    query.prepare("DELETE FROM messages WHERE notification_id = :notification_id");
    query.bindValue(":notification_id", notificationId);
    bool result = query.exec();
    if (!result)
        qCritical() << query.lastError();
    return result;
}

std::shared_ptr<Notification> NotificationManager::selectMessage(const QString& notificationId)
{
    QSqlQuery query(m_ncDb->internalDatabase());
    query.prepare("SELECT * FROM messages WHERE notification_id = :notification_id");
    query.bindValue(":notification_id", notificationId);
    std::shared_ptr<Notification> message(new Notification);
    if (query.exec() && query.first())
    {
        message->setNotificationId(query.value(0).toString())
            .setApplicationId(query.value(1).toString())
            .setTitle(query.value(2).toString())
            .setPreview(query.value(4).toString())
            .setContent(query.value(5).toString())
            .setPriority(static_cast<Notification::Priority>(query.value(6).toInt()))
            .setDuration(static_cast<Notification::Duration>(query.value(7).toInt()))
            .setData(query.value(8).toString())
            .setTriggerTime(query.value(9).toString())
            .setCreatedTime(query.value(10).toString());
        QPixmap pixmap;
        if (pixmap.loadFromData(query.value(3).toByteArray(), "PNG") and !pixmap.isNull()) {
            message->setIcon(QIcon(pixmap));
#if DEBUG
            qDebug() << "loading icon from database succeeded" << pixmap;
#endif
        }
        message->setIsNew(false);
    }
#if DEBUG
    else {
        qCritical() << query.lastError();
        qDebug() << "no such message:" << notificationId;
    }
#endif
    return message;
}

MessageList NotificationManager::selectAllMessages()
{
    MessageList messageList;
    QSqlQuery query(m_ncDb->internalDatabase());
    if (!query.exec("SELECT notification_id FROM messages ORDER BY created_time")) {
        qCritical() << query.lastError();
        return messageList;
    }
    while (query.next()) {
        messageList << selectMessage(query.value(0).toString());
    }
    return messageList;
}
