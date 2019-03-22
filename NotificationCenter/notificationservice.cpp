#include "notificationservice.h"
#include "notificationlistener.h"
#include "notificationmanager.h"
#include "notificationevent.h"
#include <QUuid>
#include <QDateTime>
#include <QDebug>

QHash<QString, NotificationListener*> NotificationService::m_listenerMap;
QList<NotificationListener*> NotificationService::m_globalListenerList;
QHash<QString, QList<QString> > NotificationService::m_notifyId2AppId;
QHash<QString, QList<QString> > NotificationService::m_appId2NotifyId;
// NotificationManager *NotificationService::m_notificationManager = nullptr;

NotificationService::NotificationService(NotificationCenter *nc) :
    m_notificationManager(new NotificationManager(nc))
{

}

NotificationService::~NotificationService()
{
    
}

bool NotificationService::createNotificationChannel(const QString& applicationId, NotificationListener *listener)
{
    if (m_listenerMap.find(applicationId) != m_listenerMap.end())
        return false;

    m_listenerMap[applicationId] = listener;
    listener->setApplicationId(applicationId);
    return true;
}

bool NotificationService::removeNotificationChannel(const QString& applicationId, NotificationListener *listener)
{
    if (m_listenerMap[applicationId] != listener)
        return false;

    m_listenerMap.remove(applicationId);
    return true;
}

QString NotificationService::postNotification(const Notification& notification)
{
    // TODO: don't need to recreate a new one
    std::shared_ptr<Notification> n(new Notification(notification));
    return postNotification(n);
}

QString NotificationService::postNotification(std::shared_ptr<Notification> notification)
{
    QString notificationId = notification->notificationId();
    NotificationEvent *e = new NotificationEvent(Event::Type::NotificationAdded, Event::Reason::Changed);
    if (notificationId.isEmpty()) {
        notificationId = QUuid::createUuid().toString();
        notification->setNotificationId(notificationId);
        e->setReason(Event::Reason::Added);
    }
    notification->setCreatedTime(QDateTime::currentDateTime().toString());
    e->setNotification(notification);
    postEvent(e);
    return notificationId;
}

void NotificationService::cancelNotification(const QString& notificationId)
{
    NotificationEvent *e = new NotificationEvent(Event::Type::NotificationRemoved, Event::Reason::Canceled);
    e->setNotificationId(notificationId);
    postEvent(e);
}

// void NotificationService::notify(Notifier *widget)
// {
//     // TODO
// }

void NotificationService::postEvent(NotificationEvent *event)
{
    QString notificationId = event->notificationId();
    switch (event->type()) {
        case Event::Type::NotificationAdded: {
            QString applicationId = event->notification()->applicationId();
            if (!applicationId.isEmpty()) {
                m_notifyId2AppId[notificationId].append(applicationId);
                m_appId2NotifyId[applicationId].append(notificationId);
            }
            else
                applicationId = "org.linuxnotifier.Notifier";

            NotificationListener *listener = m_listenerMap[applicationId];
            if (listener)
                emit listener->notificationEvent(event);
            break;
        }
        case Event::Type::NotificationExpired: {
            for (auto applicationId : m_notifyId2AppId[notificationId]) {
                auto listener = m_listenerMap[applicationId];
                if (listener)
                    emit listener->notificationEvent(event);
            }
            break;
        }
        case Event::Type::NotificationRemoved: {
            for (auto applicationId : m_notifyId2AppId[notificationId]) {
                m_notifyId2AppId.remove(notificationId);
                m_appId2NotifyId[applicationId].removeOne(notificationId);
                auto listener = m_listenerMap[applicationId];
                if (listener)
                    emit listener->notificationEvent(event);
            }
            break;
        }
    }
    for (auto listener : m_globalListenerList) {
        emit listener->notificationEvent(event);
    }
    delete event;
}

void NotificationService::installGlobalNotificationListener(NotificationListener *listener)
{
    if (m_globalListenerList.indexOf(listener) == -1)
        m_globalListenerList.push_back(listener);
    // listener->setApplicationId("*");
}

void NotificationService::removeGlobalNotificationListener(NotificationListener *listener)
{
    m_globalListenerList.removeAll(listener);
}
