#ifndef NOTIFICATIONCENTER_P_H
#define NOTIFICATIONCENTER_P_H

class NotificationCenter;
class NcMessage;
class MessageManager;

class NotificationCenterPrivate
{
    friend class NotificationCenter;

    public:
        ~NotificationCenterPrivate();

    private:
        explicit NotificationCenterPrivate(NotificationCenter *q_ptr);
        Q_DISABLE_COPY(NotificationCenterPrivate)

        MessageManager *m_messageManager;
        bool m_quietMode = false;
        NotificationCenter *q_ptr;
};

#endif // NOTIFICATIONCENTER_P_H
