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

NotificationCenterPrivate& NotificationCenterPrivate::instance()
{
    static NotificationCenterPrivate instance(&NotificationCenter::instance());
    return instance;
}

NcMessage& NotificationCenterPrivate::createMessage()
{
    return *(new NcMessage);
}

bool NotificationCenterPrivate::notify(const NcMessage& message)
{
    // return true;
    return DatabaseManager::instance().insertMessage(message.messageId(),
            message.title(),
            message.preview(),
            message.content(),
            // FIXME: store QIcon data
            // message.icon(),
            QString(""),
            message.sound(),
            static_cast<int>(message.action()),
            message.createdTime(),
            static_cast<int>(message.priority()),
            message.duration(),
            message.notificationId(),
            message.applicationId()
            );
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
    return NotificationCenterPrivate::createMessage();
}

bool NotificationCenter::notify(const NcMessage& message)
{
    return NotificationCenterPrivate::notify(message);
}
