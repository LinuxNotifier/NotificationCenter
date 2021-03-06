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
#include <QRandomGenerator>

NotificationManager::NotificationManager(NotificationCenter *parent) :
    QObject(parent),
    m_ncDb(&Database::instance())
{
    connect(parent, SIGNAL(notificationClosed(const QString)), this, SLOT(notificationClosed(const QString)));
    initNotificationTable();
    // FIXME: duplicate notification if new notification is inserted before loading
    // notifications when program starts up
    QTimer::singleShot(1000, this, &NotificationManager::loadNotifications);
    // loadNotifications();
}

NotificationManager::~NotificationManager()
{

}

int NotificationManager::createNotificationChannel(const QString& id, const QString& name)
{
    // mChannels.append(channel);
    int token = QRandomGenerator::global()->generate();
    return token;
}

void NotificationManager::initNotificationTable()
{
    QSqlQuery query(m_ncDb->internalDatabase());
    if (!query.exec("CREATE TABLE IF NOT EXISTS notifications "
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
        qCritical() << QObject::tr("creating table \"notifications\" failed");
        qCritical() << query.lastError();
        m_valid = false;
    }
    else
        m_valid = true;
}

void NotificationManager::loadNotifications()
{
    NotificationList notificationList = selectAllNotifications();
    for (const std::shared_ptr<Notification> notification : notificationList) {
        Notification::Duration duration = notification->duration();
        if (duration != Notification::Duration::UntilShutdown) {
            emit newNotification(notification);
            m_notificationMap[notification->notificationId()] = notification;
        }
        else {
            deleteNotification(notification->notificationId());
        }
    }
}


void NotificationManager::notificationClosed(const QString notificationId)
{
#if DEBUG
    qDebug() << "notification closed:" << notificationId;
#endif
    m_notificationMap.remove(notificationId);
    deleteNotification(notificationId);
}

bool NotificationManager::insertNotification(std::shared_ptr<Notification> notification)
{
    bool inserted = NotificationManager::insertNotification(notification->notificationId(),
            notification->applicationId(),
            notification->title(),
            notification->icon(),
            notification->preview(),
            notification->content(),
            notification->data(),
            static_cast<int>(notification->priority()),
            static_cast<int>(notification->duration()),
            notification->triggerTime(),
            notification->createdTime()
            );
    if (inserted) {
        m_notificationMap[notification->notificationId()] = notification;
        // emit newNotification(notification);
    }
    return inserted;
}

bool NotificationManager::insertNotification(const QString& notificationId, const
        QString& applicationId, const QString& title, const QIcon& icon, const
        QString& preview, const QString& content, const QString& data, int
        priority, int duration, const QString& triggerTime, const QString&
        createdTime)
{
    QSqlQuery query(m_ncDb->internalDatabase());
    query.prepare("INSERT INTO notifications "
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

bool NotificationManager::alterNotification(std::shared_ptr<Notification> notification)
{
    // return NotificationManager::alterNotification(notification->notificationId(),
    //         notification->title(),
    //         notification->preview(),
    //         notification->content(),
    //         notification->icon(),
    //         // static_cast<int>(notification->action()),
    //         notification->createdTime(),
    //         static_cast<int>(notification->priority()),
    //         static_cast<int>(notification->duration()),
    //         notification->notificationId(),
    //         notification->applicationId()
    //         );
    return true;
}

// bool NotificationManager::alterNotification(const QString& notificationId, const QString& title,
//         const QString& preview, const QString& content,
//         // const QIcon& icon, int action,
//         const QIcon& icon,
//         const QString& created_time, int priority, int duration,
//         const QString& notificationId, const QString& applicationId)
// {
//     deleteNotification(notificationId);
//     return insertNotification(notificationId, title, preview, content, icon,
//             // action, created_time, priority, duration,
//             created_time, priority, duration,
//             notificationId, applicationId);
// }

bool NotificationManager::deleteNotification(const QString& notificationId)
{
    QSqlQuery query(m_ncDb->internalDatabase());
    query.prepare("DELETE FROM notifications WHERE notification_id = :notification_id");
    query.bindValue(":notification_id", notificationId);
    bool result = query.exec();
    if (!result)
        qCritical() << query.lastError();
    return result;
}

std::shared_ptr<Notification> NotificationManager::selectNotification(const QString& notificationId)
{
    QSqlQuery query(m_ncDb->internalDatabase());
    query.prepare("SELECT * FROM notifications WHERE notification_id = :notification_id");
    query.bindValue(":notification_id", notificationId);
    std::shared_ptr<Notification> notification(new Notification);
    if (query.exec() && query.first())
    {
        notification->setNotificationId(query.value(0).toString())
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
            notification->setIcon(QIcon(pixmap));
#if DEBUG
            qDebug() << "loading icon from database succeeded" << pixmap;
#endif
        }
        notification->setIsNew(false);
    }
#if DEBUG
    else {
        qCritical() << query.lastError();
        qDebug() << "no such notification:" << notificationId;
    }
#endif
    return notification;
}

NotificationList NotificationManager::selectAllNotifications()
{
    NotificationList notificationList;
    QSqlQuery query(m_ncDb->internalDatabase());
    if (!query.exec("SELECT notification_id FROM notifications ORDER BY created_time")) {
        qCritical() << query.lastError();
        return notificationList;
    }
    while (query.next()) {
        notificationList << selectNotification(query.value(0).toString());
    }
    return notificationList;
}
