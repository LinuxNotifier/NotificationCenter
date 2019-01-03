#ifndef NOTIFICATIONCHANNEL_H
#define NOTIFICATIONCHANNEL_H

#include <QString>

class NotificationChannel
{
    public:
        NotificationChannel(const QString& id, const QString& name);
        ~NotificationChannel();

    private:
        QString mId;
        QString mName;
};

#endif // NOTIFICATIONCHANNEL_H
