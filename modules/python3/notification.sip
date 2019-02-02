class Notification {
    %TypeHeaderCode
        #include "notificationcenter.h"
        #include "notification.h"
        #include <memory>
        #include <QDebug>
    %End

    public:
        enum class Priority {
            /**
             * Low: for notifications that can be directedly ignored, and likely to be displayed
             * after normal notifications even if it is more new
             * Normal: the default priority of notification
             * High: more likely to be displayed on the top
             * Critical: most-hight priority, always shown on the top of other notifications, shown
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
             * UntilConfirmation: keep this notification until user manually close it even if
             * machine rebooted before
             * UntilShutdown: remove this notification after this machine shutdown
             * Default: to keep this notification in default seconds, right now 10s
             */
            UntilConfirmation = 1,
            UntilShutdown = 2,
            Default = 3,
        };

        Notification();
        ~Notification();

        QString createdTime() const;
        QIcon icon() const;
        Notification& setIcon(const QString& icon);
        Notification& setIcon(const QIcon& icon);
        QString title() const;
        Notification& setTitle(const QString& title);
        QString preview() const;
        Notification& setPreview(const QString& preview);
        QString content() const;
        Notification& setContent(const QString& content);
        Duration duration() const;
        /* the following method has the same python signature */
        Notification& setDuration(Duration duration);
        /* Notification& setDuration(int duration); */
        Priority priority() const;
        Notification& setPriority(Priority priority);
        QString notificationId() const;
        QString applicationId() const;

    private:
        /* Q_DISABLE_COPY(Notification); */

        /* Notification() /Factory/; */
        /* Notification(const Notification&); */
        /* Notification& operator=(const Notification&); */
};
