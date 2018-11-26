#ifndef NOTIFICATIONCENTER_H
#define NOTIFICATIONCENTER_H

#include <QObject>
#include <memory>

class ExtensionInterface;
class NcMessage;
class NotificationCenterPrivate;
class NcNotificationWidget;
class MainWindow;
class MessageManager;
class ExtensionManager;
class QPluginLoader;

class NotificationCenter : public QObject
{
    Q_OBJECT

    signals:
        // NOTE: all messages through NotificationCenter may be leaked to other plugins,
        // you should customize notification widget to display privacy information if you
        // have to do so.

        void newMessage(std::shared_ptr<NcMessage> message);
        void newNotification(NcNotificationWidget *widget);
        void messageExpired(const QString messageId);
        void messageClosed(const QString messageId);
        void messageHandled(const QString action);

        void modeChanged(bool quiet);

        void newExtension(std::shared_ptr<QPluginLoader> pluginLoader);
        void newExtension(std::shared_ptr<ExtensionInterface> plugin);
        void extensionEnabled(const QString pluginId);
        void extensionDisabled(const QString pluginId);
        void extensionRemoved(const QString pluginId);
        void extensionDeleted(const QString pluginId);

    public:
        ~NotificationCenter();
        static NotificationCenter& instance(QObject *parent = nullptr);

        static QString version();

        void setView(MainWindow *view);
        void setMessageModel(MessageManager *messageManager);
        void setPluginModel(ExtensionManager *extensionManager);

        static bool notify(std::shared_ptr<NcMessage> message);
        static bool notify(const NcMessage &message);
        // TODO
        // renotify(notificaitonId)
        // removeNotification(const QString notificationId);
        // replaceNotification(notificaitonId, notification, CREATE_ON_NO, actionHandler)
        // NOTE: the following method always returns true
        static bool notify(NcNotificationWidget *widget);

        static void addPlugin(ExtensionInterface *plugin);

        // TODO
        // static QString themeName();
        static bool quietMode();
        static void setQuietMode(bool quiet = true);
        static void toggleQuietMode();


    private:
        explicit NotificationCenter(QObject *parent = nullptr);
        Q_DISABLE_COPY(NotificationCenter);

        std::shared_ptr<NotificationCenterPrivate> d_ptr;
};

#endif // NOTIFICATIONCENTER_H
