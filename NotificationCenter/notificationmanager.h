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
 * This class manages the lifetime of messages.
 */
class NotificationManager : public QObject
{
    Q_OBJECT

    signals:
        void newMessage(std::shared_ptr<Notification> message);
        void messageExpired(const QString notificationId);

    private slots:
        void messageClosed(const QString notificationId);

    friend class NotificationCenter;

    public:
        explicit NotificationManager(NotificationCenter *parent);
        ~NotificationManager();

        inline bool isValid() {
            return m_valid;
        };

        void createNotficationChannel(const NotificationChannel& channel);

    private:
        void initMessageTable();
        void loadMessages();


        bool insertMessage(std::shared_ptr<Notification> message);
        bool insertMessage(const QString& notificationId, const
                QString& applicationId, const QString& title, const QIcon&
                icon, const QString& preview, const QString& content, const
                QString& data, int priority, int duration, const QString&
                triggerTime, const QString& createdTime);
        bool alterMessage(std::shared_ptr<Notification> message);
        bool alterMessage(const QString& notificationId, const QString&
                applicationId, const QString& title, const QIcon& icon, const
                QString& preview, const QString& data, const QString& content,
                int priority, int duration, const QString& triggerTime, const
                QString& created_time);
        bool deleteMessage(const QString& notificationId);
        /* this method return the first message with this message in database,
        thought there should be "always" at most one such message. */
        std::shared_ptr<Notification> selectMessage(const QString& notificationId);
        MessageList selectAllMessages();

        Database *m_ncDb = nullptr;
        MessageMap m_messageMap;
        bool m_valid = false;
};

#endif // NOTIFICATIONMANAGER_H
