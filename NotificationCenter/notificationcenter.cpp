#include "notificationcenter.h"
#include "notificationcenter_p.h"
#include "notificationwidget.h"
#include "extensioninterface.h"
#include "notificationmanager.h"
#include "extensionmanager.h"
#include "notification.h"
#include "mainwindow.h"
#include "debug.h"
#include "global.h"
#include <memory>
#include <QDateTime>

#if DEBUG
const bool Debug = true;
#else
const bool Debug = false;
#endif

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

QString NotificationCenter::version()
{
    return instance().d_ptr->m_ncVersion;
}

void NotificationCenter::setView(MainWindow *view)
{
    d_ptr->m_view = view;
    connect(d_ptr->m_view, SIGNAL(messageClosed(const QString)), this, SIGNAL(messageClosed(const QString)));
}

void NotificationCenter::setNotificationModel(NotificationManager *messageManager)
{
    d_ptr->m_notificationManager = messageManager;
    connect(d_ptr->m_notificationManager, SIGNAL(newNotification(std::shared_ptr<Notification>)), this, SIGNAL(newNotification(std::shared_ptr<Notification>)));
    connect(d_ptr->m_notificationManager, SIGNAL(messageExpired(const QString)), this, SIGNAL(messageExpired(const QString)));
}

void NotificationCenter::setPluginModel(ExtensionManager *extensionManager)
{
    d_ptr->m_extensionManager = extensionManager;
    connect(d_ptr->m_extensionManager, SIGNAL(newExtension(std::shared_ptr<QPluginLoader>)), this, SIGNAL(newExtension(std::shared_ptr<QPluginLoader>)));
    connect(d_ptr->m_extensionManager, SIGNAL(extensionDeleted(const QString)), this, SIGNAL(extensionDeleted(const QString)));
}

bool NotificationCenter::notify(const Notification& notification)
{
    // TODO: don't need to recreate a new one
    std::shared_ptr<Notification> msg(new Notification(notification));
    return notify(msg);
}

bool NotificationCenter::notify(std::shared_ptr<Notification> notification)
{
    // TODO: set notificationId here, return notificationId
    if (!notification->isNew())
        return true;
    notification->setNotificationId(QUuid::createUuid().toString());
    notification->setCreatedTime(QDateTime::currentDateTime().toString());
    NotificationManager *msgMgr = instance().d_ptr->m_notificationManager;
    QString applicationId = notification->applicationId();
    auto map = instance().d_ptr->m_notificationServiceMap;
    // FIX: NotificationListner
    // if (map.contains(applicationId)) {
    //     map[applicationId]->onNewNotification(notification);
    // }
    if (msgMgr) {
        // we need the result of inserting a notification, so didn't implement it with signals
        bool inserted = instance().d_ptr->m_notificationManager->insertNotification(notification);
        if (inserted)
            return true;
    }
    return true;    // return true if no notification manager
}

bool NotificationCenter::display(NotificationWidget *widget)
{
    // emit instance().displayNotification(widget);
    emit instance().d_ptr->m_view->displayNotification(widget);
    return true;
}

bool NotificationCenter::registerNotificationService(const QString& applicationId, NotificationHandler *handler)
{
    if (applicationId.isEmpty() || instance().d_ptr->m_notificationServiceMap.contains(applicationId))
    {
        qWarning() << "invalid applicationId or applicationId already exists";
        return false;
    }
    instance().d_ptr->m_notificationServiceMap[applicationId] = handler;
    return true;

}

bool NotificationCenter::registerExtension(ExtensionInterface *plugin)
{
    // // invalid application will not able to custom notifications, but it can
    // // still send naive notificaitons
    QString applicationId = plugin->applicationId();
    // if (applicationId.isEmpty()) {
    //     qWarning() << "empty application id";
    //     return false;
    // }
    // if (instance().d_ptr->m_extensionMap.contains(applicationId)) {
    //     qWarning() << "extension with application id:" << applicationId << "already exists";
    //     return false;
    // }
    instance().d_ptr->m_extensionMap[applicationId] = plugin;
    emit instance().newExtension(std::shared_ptr<ExtensionInterface>(plugin));
    return true;
}
int NotificationCenter::createNotficationNotificationChannel(const QString& id, const QString& name)
{
    return instance().d_ptr->m_notificationManager->createNotificationChannel(id, name);
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
