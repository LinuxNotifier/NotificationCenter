#include "notificationcenter.h"
#include "notificationcenter_p.h"
#include "notificationwidget.h"
#include "extensioninterface.h"
#include "notificationmanager.h"
#include "notificationservice.h"
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
    d_ptr->m_notificationService = new NotificationService(this);
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
}

void NotificationCenter::setPluginModel(ExtensionManager *extensionManager)
{
    d_ptr->m_extensionManager = extensionManager;
    connect(d_ptr->m_extensionManager, SIGNAL(newExtension(std::shared_ptr<QPluginLoader>)), this, SIGNAL(newExtension(std::shared_ptr<QPluginLoader>)));
    connect(d_ptr->m_extensionManager, SIGNAL(extensionDeleted(const QString)), this, SIGNAL(extensionDeleted(const QString)));
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
