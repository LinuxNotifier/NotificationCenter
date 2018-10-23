#ifndef NCMESSAGE_P_H
#define NCMESSAGE_P_H

#include <QString>
#include <QIcon>

class NcMessage;
class NotificationCenter;

class NcMessagePrivate
{
    friend class NcMessage;
    friend class NotificationCenter;

    public:
        ~NcMessagePrivate();

        const QString& createdTime() const;
        const QIcon& icon() const;
        NcMessagePrivate& setIcon(const QString& icon);
        NcMessagePrivate& setIcon(const QIcon& icon);
        const QString& title() const;
        NcMessagePrivate& setTitle(const QString& title);
        const QString& preview() const;
        NcMessagePrivate& setPreview(const QString& preview);
        const QString& content() const;
        NcMessagePrivate& setContent(const QString& content);
        const QString& sound() const;
        NcMessagePrivate& setSound(NcMessage::Sound sound);
        NcMessagePrivate& setSound(const QString& sound);
        int duration() const;
        NcMessagePrivate& setDuration(NcMessage::Duration duration);
        NcMessagePrivate& setDuration(int duration);
        NcMessage::Priority priority() const;
        NcMessagePrivate& setPriority(NcMessage::Priority priority);
        NcMessage::Action action() const;
        NcMessagePrivate& setAction(NcMessage::Action action);

        const QString& messageId() const;
        const QString& notificationId() const;
        const QString& applicationId() const;
    private:
        explicit NcMessagePrivate(NcMessage *q_ptr);
        Q_DISABLE_COPY(NcMessagePrivate)
        // FIXME: d_func() somehow returns a const pointer
        Q_DECLARE_PUBLIC(NcMessage)

        NcMessagePrivate& setMessageId(const QString& messageId);
        NcMessagePrivate& setNotificationId(const QString& notificationId);
        NcMessagePrivate& setApplicationId(const QString& applicationId);

        QString m_messageId;
        QString m_applicationId;
        QString m_notificationId;
        QIcon m_icon;
        QString m_title;
        QString m_preview;
        QString m_content;
        QString m_sound;

        const QString m_createdTime;
        NcMessage::Priority m_priority = NcMessage::Priority::Normal;
        NcMessage::Action m_action = NcMessage::Action::Create;
        int m_duration;

        // NOTE: modify NcMessage::Duration::Default doc when changed
        static const int default_duration = 10;

        NcMessage *q_ptr;
};

#endif // NCMESSAGE_P_H
