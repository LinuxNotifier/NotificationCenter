#ifndef NCMESSAGE_H
#define NCMESSAGE_H

#include <QString>
#include <QIcon>
#include <QList>
#include <QHash>
#include <memory>

using namespace std;

class NcMessagePrivate;
class NotificationCenter;
class NotificationCenterPrivate;
class DatabaseManager;
class NcMessage;

typedef QList<shared_ptr<NcMessage> > MessageList;
typedef QHash<QString, shared_ptr<NcMessage> > MessageMap;

/**
 * This class encapsulates a message that transfered among the NotificationCenter
 */
class NcMessage
{
    friend class NotificationCenter;
    friend class NotificationCenterPrivate;
    friend class MessageManager;

    public:
        enum class Action {
            /**
             * Create: create a new message, this is the default behaviour
             * Replace: replace an old message by messageId
             * GroupByNotificationId: show this message in the notification widget with
             * this notificationId
             */
            Create,
            Replace,
            GroupByNotificationId,
        };
        enum class Priority {
            /**
             * Low: for messages that can be directedly ignored, and likely to be displayed
             * after normal notifications even if it is more new
             * Normal: the default priority of messages
             * High: more likely to be displayed on the top
             * Urgent: most-hight priority, always shown on the top of other messages, shown
             * even in Do-Not-Disturbe mode, this should be used in critical situations like
             * low-power warning
             */
            Low,
            Normal,
            High,
            Urgent,
        };
        enum class Duration {
            /**
             *
             * UntilConfirmation: keep this message until user manually close it even if
             * machine rebooted before
             * UntilShutdown: remove this message after this machine shutdown
             * Default: to keep this message in default seconds, right now 10s
             */
            UntilConfirmation = -9,
            UntilShutdown,
            Default = 0,
        };

        ~NcMessage();

        const QString& createdTime() const;
        const QIcon& icon() const;
        NcMessage& setIcon(const QString& icon);
        NcMessage& setIcon(const QIcon& icon);
        const QString& title() const;
        NcMessage& setTitle(const QString& title);
        const QString& preview() const;
        NcMessage& setPreview(const QString& preview);
        const QString& content() const;
        NcMessage& setContent(const QString& content);
        int duration() const;
        NcMessage& setDuration(Duration duration);
        NcMessage& setDuration(int duration);
        Priority priority() const;
        NcMessage& setPriority(Priority priority);
        Action action() const;
        NcMessage& setAction(Action action);
        const QString& messageId() const;
        const QString& notificationId() const;
        const QString& applicationId() const;

        bool isValid() const;

    private:
        NcMessage();
        Q_DISABLE_COPY(NcMessage)

        NcMessage& setCreatedTime(const QString& createdTime);
        NcMessage& setMessageId(const QString& messageId);
        NcMessage& setNotificationId(const QString& notificationId);
        NcMessage& setApplicationId(const QString& applicationId);
        NcMessage& setValid(bool valid = true);

        shared_ptr<NcMessagePrivate> d_ptr;
};

#endif // NCMESSAGE_H   
