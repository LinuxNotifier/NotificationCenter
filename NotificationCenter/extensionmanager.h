#ifndef EXTENSIONMANAGER_H
#define EXTENSIONMANAGER_H

#include <QObject>
#include <memory>
#include <QHash>

class NotificationCenter;
class Database;
class ExtensionInterface;
class QPluginLoader;

// typedef QHash<QString, QPluginLoader*> PluginLoaderMap;
// typedef QHash<QString, ExtensionInterface*> PluginMap;
typedef QHash<QString, std::shared_ptr<QPluginLoader> > PluginLoaderMap;
typedef QHash<QString, std::shared_ptr<ExtensionInterface> > PluginMap;

class ExtensionManager : public QObject
{
    Q_OBJECT

    friend class NotificationCenter;

    signals:
        void newExtension(std::shared_ptr<QPluginLoader> pluginLoader);
        void newExtension(std::shared_ptr<ExtensionInterface> plugin);
        void extensionDeleted(const QString pluginId);

    private slots:
        void onNewPlugin(std::shared_ptr<QPluginLoader> pluginLoader);
        void onNewPlugin(std::shared_ptr<ExtensionInterface> plugin);
        void onPluginEnabled(const QString pluginId);
        void onPluginDisabled(const QString pluginId);
        void onPluginRemoved(const QString pluginId);

    public:
        explicit ExtensionManager(NotificationCenter *parent);
        ~ExtensionManager();

        inline bool isValid() {
            return m_valid;
        };

    private:
        void initPluginTable();
        void loadExtensions();
        // bool insertPlugin()

        Database *m_ncDb = nullptr;
        PluginLoaderMap m_pluginLoaderMap;
        PluginLoaderMap m_pluginMap;
        bool m_valid = false;
    
};

#endif // EXTENSIONMANAGER_H
