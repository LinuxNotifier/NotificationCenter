#include "notificationcenter.h"
#include "notificationcenter_p.h"
#include "plugininterface.h"
#include "messagemanager.h"
#include "pluginmanager.h"
#include "ncmessage.h"
#include "mainwindow.h"
#include "ncdebug.h"
#include <memory>

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
    connect(view, SIGNAL(messageClosed(const QString)), this, SIGNAL(messageExpired(const QString)));

}

void NotificationCenter::setMessageModel(MessageManager *messageManager)
{
    d_ptr->m_messageManager = messageManager;
    connect(d_ptr->m_messageManager, SIGNAL(newMessage(shared_ptr<NcMessage>)), this, SIGNAL(newMessage(shared_ptr<NcMessage>)));
    connect(d_ptr->m_messageManager, SIGNAL(messageExpired(const QString)), this, SIGNAL(messageExpired(const QString)));
}

void NotificationCenter::setPluginModel(PluginManager *pluginManager)
{
    d_ptr->m_pluginManager = pluginManager;
    connect(d_ptr->m_pluginManager, SIGNAL(newPlugin(shared_ptr<PluginInterface>)), this, SIGNAL(newPlugin(shared_ptr<PluginInterface>)));
    connect(d_ptr->m_pluginManager, SIGNAL(pluginDeleted(const QString)), this, SIGNAL(pluginDeleted(const QString)));
}

shared_ptr<NcMessage> NotificationCenter::createMessage()
{
    shared_ptr<NcMessage> msg(new NcMessage);
    return msg;
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
    return true;
}

bool NotificationCenter::quietMode()
{
    return instance().d_ptr->m_quietMode;
}

void NotificationCenter::setQuietMode(bool quiet)
{
    instance().d_ptr->m_quietMode = quiet;
    emit instance().modeChanged(quiet);
}

void NotificationCenter::toggleQuietMode()
{
    NotificationCenter &nc = instance();
    nc.d_ptr->m_quietMode = !nc.d_ptr->m_quietMode;
}
