#ifndef NOTIFICATIONCENTER_P_H
#define NOTIFICATIONCENTER_P_H

#include <QString>
#include <QHash>

class NotificationCenter;
class Notification;
class NotificationManager;
class NotificationManager;
class ExtensionManager;
class ExtensionInterface;
class NotificationHandler;
class MainWindow;

class NotificationCenterPrivate
{
    friend class NotificationCenter;

    public:
        ~NotificationCenterPrivate();

    private:
        explicit NotificationCenterPrivate(NotificationCenter *q_ptr);
        Q_DISABLE_COPY(NotificationCenterPrivate)

        MainWindow *m_view = nullptr;
        // NotificationManager *m_notificationManager = nullptr;
        NotificationManager *m_notificationManager = nullptr;
        ExtensionManager *m_extensionManager = nullptr;
        bool m_quietMode = false;
        const QString m_ncVersion;
        QHash<QString, ExtensionInterface*> m_extensionMap;
        QHash<QString, NotificationHandler*> m_notificationServiceMap;

        NotificationCenter *q_ptr = nullptr;
};

#endif // NOTIFICATIONCENTER_P_H
