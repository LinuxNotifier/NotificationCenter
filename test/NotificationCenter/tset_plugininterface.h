#ifndef TSET_PLUGININTERFACE_H
#define TSET_PLUGININTERFACE_H

#include "plugininterface.h"
#include <QObject>

class QWidget;
class NotificationCenter;

class TestPlugin : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
    Q_PLUGIN_METADATA(IID PluginInterface_IID FILE "test.json")

    public:
        TestPlugin();
        ~TestPlugin() override;
        void initialize(NotificationCenter *nc) override;
        QWidget* centralWidget() override;
        QWidget* settingsWidget() override;
        QString interfaceVersion() const override;
};

#endif // TSET_PLUGININTERFACE_H
