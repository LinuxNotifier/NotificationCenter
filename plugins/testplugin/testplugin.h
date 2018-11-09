#ifndef TESTPLUGIN_H
#define TESTPLUGIN_H

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
        QJsonObject metadata() const override;
        QWidget* centralWidget() override;
        QWidget* settingsWidget() override;
        QString interfaceVersion() const override;
};

#endif // TESTPLUGIN_H
