#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include "notificationevent.h"
#include <memory>
#include <QString>
#include <QHash>
#include <QList>
#include <QObject>

class NotificationListener;
class NotificationCenter;
class NotificationManager;
class Notification;
class Notifier;

class NotificationService : public QObject
{
    Q_OBJECT
    public:
        NotificationService(NotificationCenter *nc);
        ~NotificationService();

        static bool createNotificationChannel(const QString& applicationId, NotificationListener *listener);
        bool removeNotificationChannel(const QString& applicationId, NotificationListener *listener);

        // set notificaitonId to renotify
        static QString postNotification(const Notification& notification);
        static QString postNotification(std::shared_ptr<Notification> notification);
        static void cancelNotification(const QString& notificationId);
        // TODO: deliver/send/dispatch/notify/post
        // static void notify(Notifier *widget);   // show Notifier popup

        static void postEvent(NotificationEvent *event);

    private:
        static void installGlobalNotificationListener(NotificationListener *listener);
        void removeGlobalNotificationListener(NotificationListener *listener);

        static QHash<QString, NotificationListener*> m_listenerMap;
        static QList<NotificationListener*> m_globalListenerList;
        static QHash<QString, QList<QString> > m_notifyId2AppId;
        static QHash<QString, QList<QString> > m_appId2NotifyId;
        // static NotificationManager *m_notificationManager;
        NotificationManager *m_notificationManager = nullptr;
};

#endif // NOTIFICATIONSERVICE_H
