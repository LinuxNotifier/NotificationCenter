#ifndef TEST_EXTENSIONINTERFACE_H
#define TEST_EXTENSIONINTERFACE_H

#include "extensioninterface.h"
#include <QObject>

class QWidget;
class NotificationCenter;

class TestPlugin : public QObject, public ExtensionInterface
{
    Q_OBJECT
    Q_INTERFACES(ExtensionInterface)
    Q_PLUGIN_METADATA(IID ExtensionInterface_IID FILE "test.json")

    public:
        TestPlugin();
        ~TestPlugin() override;

        bool initialize(NotificationCenter *nc) override;
        QJsonObject metadata() const override;
        QWidget* centralWidget() override;
        QWidget* settingsWidget() override;
};

#endif // TEST_EXTENSIONINTERFACE_H
