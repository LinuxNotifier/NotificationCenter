#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <global.h>
#include <QString>
#include <QIcon>
#include <QList>
#include <QHash>
#include <memory>

class NotificationPrivate;
class NotificationCenter;
class NotificationCenterPrivate;
class Database;
class Notification;

typedef QList<std::shared_ptr<Notification> > MessageList;
typedef QHash<QString, std::shared_ptr<Notification> > MessageMap;
typedef std::shared_ptr<Notification> NotificationSharedPointer;

/**
 * This class encapsulates a message that transfered among the NotificationCenter
 */
class Notification
{
    friend class NotificationCenter;
    friend class NotificationCenterPrivate;
    friend class NotificationManager;

    public:
        // TODO: use using to import enum class from NotificationPrivate (https://stackoverflow.com/questions/3293279/how-do-you-import-an-enum-into-a-different-namespace-in-c)
        enum class Priority {
            /**
             * Low: for messages that can be directedly ignored, and likely to be displayed
             * after normal notifications even if it is more new
             * Normal: the default priority of messages
             * High: more likely to be displayed on the top
             * Critical: most-hight priority, always shown on the top of other messages, shown
             * even in Do-Not-Disturbe mode, this should be used in critical situations like
             * low-power warning
             */
            Low,
            Normal,
            High,
            Critical,
        };
        enum class Duration {
            /**
             * UntilConfirmation: keep this message until user manually close it even if
             * machine rebooted before
             * UntilShutdown: remove this message after this machine shutdown
             * Default: to keep this message in default seconds, right now 10s
             */
            UntilConfirmation = 1 << 0,
            UntilShutdown = 1 << 1,
            Default = UntilConfirmation | UntilShutdown,
        };

        Notification();
        ~Notification();

        QString notificationId() const;
        Notification& setNotificationId(const QString& notificationId);
        QString applicationId() const;
        QString title() const;
        Notification& setTitle(const QString& title);
        QIcon icon() const;
        Notification& setIcon(const QString& icon);
        Notification& setIcon(const QIcon& icon);
        QString preview() const;
        Notification& setPreview(const QString& preview);
        QString content() const;
        Notification& setContent(const QString& content);
        QString data() const;
        Notification& setData(const QString& data);
        Priority priority() const;
        Notification& setPriority(Priority priority);
        Duration duration() const;
        Notification& setDuration(Duration duration);
        QString triggerTime() const;
        QString createdTime() const;
        bool isNew() const;

        static int defaultDuration() {
            return default_duration;
        };

    private:
        // Q_DISABLE_COPY(Notification);

        Notification& setApplicationId(const QString& applicationId);
        Notification& setTriggerTime(const QString& triggerTime);
        Notification& setCreatedTime(const QString& createdTime);
        Notification& setIsNew(bool isNew);

        // NOTE: modify Notification::Duration::Default doc when changed
        static const int default_duration = 10;

        std::shared_ptr<NotificationPrivate> d_ptr;
};

#endif // NOTIFICATION_H
