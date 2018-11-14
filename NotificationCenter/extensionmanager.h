#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <memory>
#include <QHash>

using namespace std;

class NotificationCenter;
class NcDatabase;
class ExtensionInterface;
class QPluginLoader;

// typedef QHash<QString, QPluginLoader*> PluginLoaderMap;
// typedef QHash<QString, ExtensionInterface*> PluginMap;
typedef QHash<QString, shared_ptr<QPluginLoader> > PluginLoaderMap;
typedef QHash<QString, shared_ptr<ExtensionInterface> > PluginMap;

class PluginManager : public QObject
{
    Q_OBJECT

    friend class NotificationCenter;

    signals:
        void newPlugin(shared_ptr<QPluginLoader> pluginLoader);
        void newPlugin(shared_ptr<ExtensionInterface> plugin);
        void pluginDeleted(const QString pluginId);

    private slots:
        void onNewPlugin(shared_ptr<QPluginLoader> pluginLoader);
        void onNewPlugin(shared_ptr<ExtensionInterface> plugin);
        void onPluginEnabled(const QString pluginId);
        void onPluginDisabled(const QString pluginId);
        void onPluginRemoved(const QString pluginId);

    public:
        explicit PluginManager(NotificationCenter *parent);
        ~PluginManager();

        inline bool isValid() {
            return m_valid;
        };

    private:
        void initPluginTable();
        void loadPlugins();
        // bool insertPlugin()

        NcDatabase *m_ncDb = nullptr;
        PluginLoaderMap m_pluginLoaderMap;
        PluginLoaderMap m_pluginMap;
        bool m_valid = false;
    
};

#endif // PLUGINMANAGER_H
