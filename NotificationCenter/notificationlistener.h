#ifndef NOTIFICATIONLISTENER_H
#define NOTIFICATIONLISTENER_H

#include "notification.h"

class NotificationChannel;

class NotificationListener
{
    public:
        NotificationListener() = default;
        virtual ~NotificationListener() {};

        void addNotificationChannel(const QString& channelId, const int channelToken);
        void removeNotificationChannel(const QString& channelId);

        virtual void onNewNotification(Notification notification) {};

    private:

};

#endif // NOTIFICATIONLISTENER_H
