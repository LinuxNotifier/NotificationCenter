#include "notificationcenter.h"
#include "notificationcenter_p.h"
#include "ncmessage.h"
#include "dbmanager.h"
#include "nclogging.h"

NotificationCenterPrivate::NotificationCenterPrivate(NotificationCenter *q_ptr) :
    q_ptr(q_ptr)
{

}

NotificationCenterPrivate::~NotificationCenterPrivate()
{

}

NotificationCenter::NotificationCenter(QObject *parent) :
    QObject(parent),
    d_ptr(new NotificationCenterPrivate(this))
{
    
}

NotificationCenter::~NotificationCenter()
{
    
}

NotificationCenter& NotificationCenter::instance()
{
    static NotificationCenter instance;
    return instance;
}

NcMessage& NotificationCenter::createMessage()
{
    return *(new NcMessage);
}

bool NotificationCenter::notify(NcMessage& message)
{
    if (message.isValid())          // already notified
        return false;

    message.setValid();
    return DatabaseManager::instance().insertMessage(message);
}
