class NcMessage {
    %TypeHeaderCode
        #include "notificationcenter.h"
        #include "ncmessage.h"
        #include <memory>
        #include <QDebug>
    %End

    public:
        enum class Action {
            /**
             * Create: create a new message, this is the default behaviour
             * Replace: replace an old message by notificationId
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
            UntilConfirmation = 1,
            UntilShutdown = 2,
            Default = 3,
        };

        NcMessage();
        ~NcMessage();

        QString createdTime() const;
        QIcon icon() const;
        NcMessage& setIcon(const QString& icon);
        NcMessage& setIcon(const QIcon& icon);
        QString title() const;
        NcMessage& setTitle(const QString& title);
        QString preview() const;
        NcMessage& setPreview(const QString& preview);
        QString body() const;
        NcMessage& setBody(const QString& content);
        int duration() const;
        /* the following method has the same python signature */
        /* NcMessage& setDuration(Duration duration); */
        NcMessage& setDuration(int duration);
        Priority priority() const;
        NcMessage& setPriority(Priority priority);
        Action action() const;
        NcMessage& setAction(Action action);
        QString notificationId() const;
        QString applicationId() const;

        bool isValid() const;

    private:
        /* Q_DISABLE_COPY(NcMessage); */

        /* NcMessage() /Factory/; */
        /* NcMessage(const NcMessage&); */
        /* NcMessage& operator=(const NcMessage&); */
};
