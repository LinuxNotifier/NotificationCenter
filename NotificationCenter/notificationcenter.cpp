#include "notificationcenter.h"
#include "notificationcenter_p.h"
#include "messagemanager.h"
#include "ncmessage.h"
#include "dbmanager.h"
#include "nclogging.h"

NotificationCenterPrivate::NotificationCenterPrivate(NotificationCenter *q_ptr) :
    q_ptr(q_ptr),
    m_messageManager(new MessageManager(q_ptr))
{

}

NotificationCenterPrivate::~NotificationCenterPrivate()
{

}

NotificationCenter::NotificationCenter(QObject *parent) :
    QObject(parent),
    d_ptr(new NotificationCenterPrivate(this))
{
    connect(d_ptr->m_messageManager, SIGNAL(newMessage(const NcMessage&)), this, SIGNAL(newMessage(const NcMessage&)));
    connect(d_ptr->m_messageManager, SIGNAL(messageExpired(const QString&)), this, SIGNAL(messageExpired(const QString&)));
    
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
    // we need the result of inserting a message, so didn't implement it with signals
    bool inserted = instance().d_ptr->m_messageManager->insertMessage(message);
    if (inserted) {
        emit (instance().newMessage(message));
        return true;
    }
    else
        return false;
}
