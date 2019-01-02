#ifndef NOTIFICATIONLISTENER_H
#define NOTIFICATIONLISTENER_H

#include "notification.h"

class NotificationChannel;

class NotificationListener
{
    public:
        NotificationListener() = default;
        virtual ~NotificationListener() {};

        void addNotificationChannel(NotificationChannel channel);
        void removeNotificationChannel(NotificationChannel channel);

        virtual void onNewNotification(Notification message) {};
};

#endif // NOTIFICATIONLISTENER_H
