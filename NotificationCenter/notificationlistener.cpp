#include "notificationlistener.h"
#include "notification.h"

NotificationListener::NotificationListener(QObject *parent) :
    QObject(parent)
{
    
}

NotificationListener::~NotificationListener()
{
    // TODO: auto-unregister and global listener
    // NotificationCenter::unregisterNotificationService(this);
}
