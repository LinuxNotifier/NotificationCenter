#ifndef NOTIFICATIONCENTER_H
#define NOTIFICATIONCENTER_H

#include <QObject>
#include <memory>

using namespace std;

class PluginInterface;
class NcMessage;
class NotificationCenterPrivate;
class NcNotificationWidget;
class MainWindow;
class MessageManager;
class PluginManager;
class QPluginLoader;

class NotificationCenter : public QObject
{
    Q_OBJECT

    signals:
        void newMessage(shared_ptr<NcMessage> message);
        void newNotification(NcNotificationWidget *widget);
        void messageExpired(const QString messageId);
        void messageClosed(const QString messageId);

        void modeChanged(bool quiet);

        void newPlugin(shared_ptr<QPluginLoader> plugin);
        void pluginEnabled(const QString pluginId);
        void pluginDisabled(const QString pluginId);
        void pluginRemoved(const QString pluginId);
        void pluginDeleted(const QString pluginId);

    public:
        static NotificationCenter& instance(QObject *parent = nullptr);

        static QString version();

        void setView(MainWindow *view);
        void setMessageModel(MessageManager *messageManager);
        void setPluginModel(PluginManager *pluginManager);

        static shared_ptr<NcMessage> createMessage();
        static bool notify(shared_ptr<NcMessage> message);
        // NOTE: the following method always returns true
        static bool notify(NcNotificationWidget *widget);

        static bool quietMode();
        static void setQuietMode(bool quiet = true);
        static void toggleQuietMode();


    private:
        explicit NotificationCenter(QObject *parent = nullptr);
        ~NotificationCenter();
        Q_DISABLE_COPY(NotificationCenter);

        shared_ptr<NotificationCenterPrivate> d_ptr;
};

#endif // NOTIFICATIONCENTER_H
