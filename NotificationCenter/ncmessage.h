#ifndef NCMESSAGE_H
#define NCMESSAGE_H

#include <ncglobal.h>
#include <QString>
#include <QIcon>
#include <QList>
#include <QHash>
#include <memory>

class NcMessagePrivate;
class NotificationCenter;
class NotificationCenterPrivate;
class NcDatabase;
class NcMessage;

typedef QList<std::shared_ptr<NcMessage> > MessageList;
typedef QHash<QString, std::shared_ptr<NcMessage> > MessageMap;
typedef std::shared_ptr<NcMessage> NcMessageSharedPointer;

/**
 * This class encapsulates a message that transfered among the NotificationCenter
 */
class NcMessage
{
    friend class NotificationCenter;
    friend class NotificationCenterPrivate;
    friend class MessageManager;

    public:
        // TODO: use using to import enum class from NcMessagePrivate (https://stackoverflow.com/questions/3293279/how-do-you-import-an-enum-into-a-different-namespace-in-c)
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

        NcMessage();
        ~NcMessage();

        QString notificationId() const;
        NcMessage& setNotificationId(const QString& notificationId);
        QString applicationId() const;
        QString title() const;
        NcMessage& setTitle(const QString& title);
        QIcon icon() const;
        NcMessage& setIcon(const QString& icon);
        NcMessage& setIcon(const QIcon& icon);
        QString preview() const;
        NcMessage& setPreview(const QString& preview);
        QString content() const;
        NcMessage& setContent(const QString& content);
        QString data() const;
        NcMessage& setData(const QString& data);
        Priority priority() const;
        NcMessage& setPriority(Priority priority);
        Duration duration() const;
        NcMessage& setDuration(Duration duration);
        QString triggerTime() const;
        QString createdTime() const;
        bool isNew() const;

        static int defaultDuration() {
            return default_duration;
        };

    private:
        // Q_DISABLE_COPY(NcMessage);

        NcMessage& setApplicationId(const QString& applicationId);
        NcMessage& setTriggerTime(const QString& triggerTime);
        NcMessage& setCreatedTime(const QString& createdTime);
        NcMessage& setIsNew(bool isNew);

        // NOTE: modify NcMessage::Duration::Default doc when changed
        static const int default_duration = 10;

        std::shared_ptr<NcMessagePrivate> d_ptr;
};

#endif // NCMESSAGE_H   
