#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <memory>

using namespace std;

class NotificationCenter;
class NcDatabase;
class PluginInterface;

class PluginManager : public QObject
{
    Q_OBJECT

    friend class NotificationCenter;

    signals:
        void newPlugin(shared_ptr<PluginInterface> plugin);
        void pluginDeleted(const QString pluginId);

    private slots:
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

        NcDatabase &m_ncDb;
        bool m_valid = false;
    
};

#endif // PLUGINMANAGER_H
