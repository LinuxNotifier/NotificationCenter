#ifndef NCMESSAGE_P_H
#define NCMESSAGE_P_H

#include <QString>
#include <QIcon>

class NcMessage;
class NotificationCenter;

class NcMessagePrivate
{
    friend class NcMessage;

    public:
        ~NcMessagePrivate();

    private:
        explicit NcMessagePrivate(NcMessage *q_ptr);
        Q_DISABLE_COPY(NcMessagePrivate)
        // FIXME: d_func() somehow returns a const pointer

        QString m_notificationId;
        QString m_applicationId;
        QString m_title;
        QIcon m_icon;
        QString m_preview;
        QString m_body;
        QString m_actionUrl;
        NcMessage::Priority m_priority = NcMessage::Priority::Normal;
        int m_duration = default_duration;
        QString m_actions;
        QString m_data;
        QString m_triggerTime;
        QString m_createdTime;

        // NOTE: modify NcMessage::Duration::Default doc when changed
        static const int default_duration = 10;

        NcMessage::Action m_action = NcMessage::Action::Create;
        bool valid = false;

        NcMessage *q_ptr = nullptr;
};

#endif // NCMESSAGE_P_H
