#ifndef NOTIFICATIONCENTER_H
#define NOTIFICATIONCENTER_H

#include <QObject>
#include <memory>

class ExtensionInterface;
// class NotificationService;
class Notification;
class NotificationCenterPrivate;
class NotificationWidget;
class MainWindow;
class NotificationManager;
class ExtensionManager;
class NotificationHandler;
class QPluginLoader;

// this is for Python plugins to detech if in debug mode
extern const bool Debug;

class NotificationCenter : public QObject
{
    Q_OBJECT

    signals:
        // NOTE: all messages through NotificationCenter may be leaked to other plugins,
        // you should customize notification widget to display privacy information if you
        // have to do so.

        void newNotification(std::shared_ptr<Notification> notification);
        void displayNotification(NotificationWidget *widget);
        void messageExpired(const QString notificationId);
        void messageClosed(const QString notificationId);
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
        static inline NotificationCenter& instance(QObject *parent = nullptr) {
            static NotificationCenter instance(parent);
            return instance;
        };

        static QString version();

        void setView(MainWindow *view);
        void setNotificationModel(NotificationManager *messageManager);
        void setPluginModel(ExtensionManager *extensionManager);

        // TODO: using signal's sender to idnetify the caller, and trust the applicationId
        // return notification id
        static bool notify(std::shared_ptr<Notification> notification);
        // TODO: directly call MainWindow::show()
        static bool notify(const Notification& notification);
        static bool registerNotificationService(const QString& applicationId, NotificationHandler *handler);
        // TODO
        // renotify(notificaitonId)
        // removeNotification(const QString notificationId);
        // replaceNotification(notificaitonId, notification, CREATE_ON_NO, actionHandler)
        // NOTE: the following method always returns true
        static bool display(NotificationWidget *widget);

        static bool registerExtension(ExtensionInterface *plugin);
        /**
         * @return channelToken the token to post notifications to this channel
         */
        static int createNotficationNotificationChannel(const QString& id, const QString& name);

        // TODO
        // static QString themeName();  // for the extensions to adjust their theme accordingly
        static bool quietMode();
        static void setQuietMode(bool quiet = true);
        static void toggleQuietMode();


    private:
        explicit NotificationCenter(QObject *parent = nullptr);
        Q_DISABLE_COPY(NotificationCenter);

        std::shared_ptr<NotificationCenterPrivate> d_ptr;
};

#endif // NOTIFICATIONCENTER_H
