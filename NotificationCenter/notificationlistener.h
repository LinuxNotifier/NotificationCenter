#ifndef NOTIFICATIONLISTENER_H
#define NOTIFICATIONLISTENER_H

#include "notification.h"
#include "notificationevent.h"
#include <QObject>
#include <memory>

class NotificationChannel;

class NotificationListener : public QObject
{
    Q_OBJECT
    signals:
        void notificationEvent(NotificationEvent *event);

    public:
        NotificationListener(QObject *parent = nullptr);
        virtual ~NotificationListener();

        void setApplicationId(const QString& applicationId) {
            m_applicationId = applicationId;
        };

    private:
        QString m_applicationId;
};

#endif // NOTIFICATIONLISTENER_H
