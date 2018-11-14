#ifndef NOTIFICATIONCENTER_P_H
#define NOTIFICATIONCENTER_P_H

#include <QString>

class NotificationCenter;
class NcMessage;
class MessageManager;
class ExtensionManager;

class NotificationCenterPrivate
{
    friend class NotificationCenter;

    public:
        ~NotificationCenterPrivate();

    private:
        explicit NotificationCenterPrivate(NotificationCenter *q_ptr);
        Q_DISABLE_COPY(NotificationCenterPrivate)

        MainWindow *m_view = nullptr;
        MessageManager *m_messageManager = nullptr;
        ExtensionManager *m_extensionManager = nullptr;
        bool m_quietMode = false;
        const QString m_ncVersion;
        NotificationCenter *q_ptr = nullptr;
};

#endif // NOTIFICATIONCENTER_P_H
