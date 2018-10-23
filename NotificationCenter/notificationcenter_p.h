#ifndef NOTIFICATIONCENTER_P_H
#define NOTIFICATIONCENTER_P_H

class NotificationCenter;
class NcMessage;

class NotificationCenterPrivate
{
    friend class NotificationCenter;

    public:
        ~NotificationCenterPrivate();

        static NotificationCenterPrivate& instance();
        static NcMessage& createMessage();
        static bool notify(const NcMessage& message);

    private:
        explicit NotificationCenterPrivate(NotificationCenter *q_ptr);
        Q_DISABLE_COPY(NotificationCenterPrivate)
        Q_DECLARE_PUBLIC(NotificationCenter)

        NotificationCenter *q_ptr;
};

#endif // NOTIFICATIONCENTER_P_H
