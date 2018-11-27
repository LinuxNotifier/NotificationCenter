#include "notificationcenter.h"
#include "notificationcenter_p.h"
#include "ncnotificationwidget.h"
#include "extensioninterface.h"
#include "messagemanager.h"
#include "extensionmanager.h"
#include "ncmessage.h"
#include "mainwindow.h"
#include "ncdebug.h"
#include "ncglobal.h"
#include <memory>
#include <QDateTime>

NotificationCenterPrivate::NotificationCenterPrivate(NotificationCenter *q_ptr) :
    q_ptr(q_ptr),
    m_ncVersion(__NOTIFICATIONCENTER_VERSION__)
{

}

NotificationCenterPrivate::~NotificationCenterPrivate()
{

}

NotificationCenter::NotificationCenter(QObject *parent) :
    QObject(parent),
    d_ptr(new NotificationCenterPrivate(this))
{
    // instance().d_ptr->m_ncVersion = __NOTIFICATIONCENTER_VERSION__;
}

NotificationCenter::~NotificationCenter()
{

}

NotificationCenter& NotificationCenter::instance(QObject *parent)
{
    static NotificationCenter instance(parent);
    return instance;
}

QString NotificationCenter::version()
{
    return instance().d_ptr->m_ncVersion;
}

void NotificationCenter::setView(MainWindow *view)
{
    d_ptr->m_view = view;
    connect(d_ptr->m_view, SIGNAL(messageClosed(const QString)), this, SIGNAL(messageClosed(const QString)));
}

void NotificationCenter::setMessageModel(MessageManager *messageManager)
{
    d_ptr->m_messageManager = messageManager;
    connect(d_ptr->m_messageManager, SIGNAL(newMessage(std::shared_ptr<NcMessage>)), this, SIGNAL(newMessage(std::shared_ptr<NcMessage>)));
    connect(d_ptr->m_messageManager, SIGNAL(messageExpired(const QString)), this, SIGNAL(messageExpired(const QString)));
}

void NotificationCenter::setPluginModel(ExtensionManager *extensionManager)
{
    d_ptr->m_extensionManager = extensionManager;
    connect(d_ptr->m_extensionManager, SIGNAL(newExtension(std::shared_ptr<QPluginLoader>)), this, SIGNAL(newExtension(std::shared_ptr<QPluginLoader>)));
    connect(d_ptr->m_extensionManager, SIGNAL(extensionDeleted(const QString)), this, SIGNAL(extensionDeleted(const QString)));
}

bool NotificationCenter::notify(const NcMessage &message)
{
    // TODO: don't need to recreate a new one
    std::shared_ptr<NcMessage> msg(new NcMessage(message));
    return notify(msg);
}

bool NotificationCenter::notify(std::shared_ptr<NcMessage> message)
{
    if (message->isValid())          // already notified
        return false;

    // TODO: set messageId here, return messageId
    message->setMessageId(QUuid::createUuid().toString());
    message->setCreatedTime(QDateTime::currentDateTime().toString());
    message->setValid();
    MessageManager *msgMgr = instance().d_ptr->m_messageManager;
    if (msgMgr) {
        // we need the result of inserting a message, so didn't implement it with signals
        bool inserted = instance().d_ptr->m_messageManager->insertMessage(message);
        if (inserted)
            return true;
    }
    return false;
}

bool NotificationCenter::notify(NcNotificationWidget *widget)
{

    emit instance().newNotification(widget);
    return true;
}

void NotificationCenter::addPlugin(ExtensionInterface *plugin)
{
    emit instance().newExtension(std::shared_ptr<ExtensionInterface>(plugin));
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
