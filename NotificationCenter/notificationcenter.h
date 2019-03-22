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
class Notifier;
class NotificationManager;
class ExtensionManager;
class NotificationListener;
class QPluginLoader;

// this is for Python plugins to detect if in debug mode
extern const bool Debug;

class NotificationCenter : public QObject
{
    Q_OBJECT

    signals:
        // NOTE: all notifications through NotificationCenter may be leaked to other plugins,
        // you should customize notification widget to display privacy information if you
        // have to do so.

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
        void setPluginModel(ExtensionManager *extensionManager);

        static bool registerExtension(ExtensionInterface *plugin);

        // TODO
        // static QString themeName();  // for the extensions to adjust their theme accordingly
        // static bool isActive();  // shown and on-the-top
        static bool quietMode();
        static void setQuietMode(bool quiet = true);
        static void toggleQuietMode();


    private:
        explicit NotificationCenter(QObject *parent = nullptr);
        Q_DISABLE_COPY(NotificationCenter);

        std::shared_ptr<NotificationCenterPrivate> d_ptr;
};

#endif // NOTIFICATIONCENTER_H
