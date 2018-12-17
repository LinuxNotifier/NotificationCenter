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
        QString m_content;
        QString m_data;
        NcMessage::Priority m_priority = NcMessage::Priority::Normal;
        NcMessage::Duration m_duration = NcMessage::Duration::Default;
        QString m_triggerTime;
        QString m_createdTime;

        // used to indicate if this notification is new (not from database)
        // TODO: check if new messsage is new? (choose to store this message or not)
        bool m_isNew = true;

        NcMessage *q_ptr = nullptr;
};

#endif // NCMESSAGE_P_H
