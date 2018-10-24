#include "notificationcenter.h"
#include "notificationcenter_p.h"
#include "messagemanager.h"
#include "ncmessage.h"
#include "mainwindow.h"
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

NotificationCenter& NotificationCenter::instance(QObject *parent)
{
    static NotificationCenter instance(parent);
    return instance;
}

void NotificationCenter::setView(MainWindow *view)
{
    connect(view, SIGNAL(messageClosed(const QString&)), this, SIGNAL(messageExpired(const QString&)));

}

void NotificationCenter::setMessageModel(MessageManager *messageModel)
{
    d_ptr->m_messageManager = messageModel;
    connect(d_ptr->m_messageManager, SIGNAL(newMessage(shared_ptr<NcMessage>)), this, SIGNAL(newMessage(shared_ptr<NcMessage>)));
    connect(d_ptr->m_messageManager, SIGNAL(messageExpired(const QString&)), this, SIGNAL(messageExpired(const QString&)));
}

shared_ptr<NcMessage> NotificationCenter::createMessage()
{
    shared_ptr<NcMessage> msg(new NcMessage);
    return msg;
    // return *(new NcMessage);
}

bool NotificationCenter::notify(shared_ptr<NcMessage> message)
{
    if (message->isValid())          // already notified
        return false;

    message->setValid();
    // we need the result of inserting a message, so didn't implement it with signals
    bool inserted = instance().d_ptr->m_messageManager->insertMessage(message);
    if (!inserted)
        return false;
    emit (instance().newMessage(message));
    return true;
}
