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

    private:
        explicit NcMessagePrivate(NcMessage *q_ptr);
        Q_DISABLE_COPY(NcMessagePrivate)
        // FIXME: d_func() somehow returns a const pointer
        Q_DECLARE_PUBLIC(NcMessage)

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
