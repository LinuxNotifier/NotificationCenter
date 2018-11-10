#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtCore>

class PluginInfo;
class NotificationCenter;
class QWidget;

#define ExtensionInterface_IID "org.linuxnotifier.NotificationCenter.Extensions"

class ExtensionInterface
{
    public:
        // enum class ExtensionType {
        //     Module,
        //     Plugin,
        // };

        virtual ~ExtensionInterface() {};

        // return True if this extension can be applied, otherwise return false
        virtual bool initialize(NotificationCenter *nc) = 0;
        // extensionType, NC interface version, ...
        virtual QJsonObject metadata() const = 0;
        // this widget will be showed on NotificationCenter
        // return nullptr when no widget
        virtual QWidget* centralWidget() {
            return nullptr;
        };
        // this widget is showed for settings
        // return nullptr when no widget
        virtual QWidget* settingsWidget() {
            return nullptr;
        };
};

Q_DECLARE_INTERFACE(ExtensionInterface, ExtensionInterface_IID)

#endif // PLUGININTERFACE_H
