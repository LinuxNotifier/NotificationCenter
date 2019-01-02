#ifndef NOTIFICATION_P_H
#define NOTIFICATION_P_H

#include <QString>
#include <QIcon>

class Notification;
class NotificationCenter;

class NotificationPrivate
{
    friend class Notification;

    public:
        ~NotificationPrivate();

    private:
        explicit NotificationPrivate(Notification *q_ptr);
        Q_DISABLE_COPY(NotificationPrivate)
        // FIXME: d_func() somehow returns a const pointer

        QString m_notificationId;
        QString m_applicationId;
        QString m_title;
        QIcon m_icon;
        QString m_preview;
        QString m_content;
        QString m_data;
        Notification::Priority m_priority = Notification::Priority::Normal;
        Notification::Duration m_duration = Notification::Duration::Default;
        QString m_triggerTime;
        QString m_createdTime;

        // used to indicate if this notification is new (not from database)
        // TODO: check if new messsage is new? (choose to store this message or not)
        bool m_isNew = true;

        Notification *q_ptr = nullptr;
};

#endif // NOTIFICATION_P_H
