#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include "notification.h"
#include <QObject>
#include <memory>
#include "global.h"

class NotificationCenter;
class NotificationCenterPrivate;
class NotificationChannel;
class Notification;
class QString;
class Database;

/**
 * This class manages the lifetime of notifications.
 */
class NotificationManager : public QObject
{
    Q_OBJECT

    signals:
        void newNotification(std::shared_ptr<Notification> notification);
        void notificationExpired(const QString notificationId);

    private slots:
        void notificationClosed(const QString notificationId);

    friend class NotificationCenter;

    public:
        explicit NotificationManager(NotificationCenter *parent);
        ~NotificationManager();

        inline bool isValid() {
            return m_valid;
        };

        int createNotificationChannel(const QString& id, const QString& name);

    private:
        void initNotificationTable();
        void loadNotifications();


        bool insertNotification(std::shared_ptr<Notification> notification);
        bool insertNotification(const QString& notificationId, const
                QString& applicationId, const QString& title, const QIcon&
                icon, const QString& preview, const QString& content, const
                QString& data, int priority, int duration, const QString&
                triggerTime, const QString& createdTime);
        bool alterNotification(std::shared_ptr<Notification> notification);
        bool alterNotification(const QString& notificationId, const QString&
                applicationId, const QString& title, const QIcon& icon, const
                QString& preview, const QString& data, const QString& content,
                int priority, int duration, const QString& triggerTime, const
                QString& created_time);
        bool deleteNotification(const QString& notificationId);
        /* this method return the first notification with this notification in database,
        thought there should be "always" at most one such notification. */
        std::shared_ptr<Notification> selectNotification(const QString& notificationId);
        NotificationList selectAllNotifications();

        Database *m_ncDb = nullptr;
        NotificationMap m_notificationMap;
        bool m_valid = false;
};

#endif // NOTIFICATIONMANAGER_H
