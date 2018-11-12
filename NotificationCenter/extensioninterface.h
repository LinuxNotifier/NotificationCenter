#ifndef EXTENSIONINTERFACE_H
#define EXTENSIONINTERFACE_H

#include <QtCore>
#include "ncdebug.h"

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
        ExtensionInterface();
        virtual ~ExtensionInterface();


        // return True if this extension can be applied, otherwise return false
        virtual bool initialize(NotificationCenter *nc) = 0;
        // extensionType, NC interface version, ...
        virtual QJsonObject metadata() const = 0;
        // this widget will be showed on NotificationCenter
        // return nullptr when no widget
        virtual QWidget* centralWidget();
        // this widget is showed for settings
        // return nullptr when no widget
        virtual QWidget* settingsWidget();
};

Q_DECLARE_INTERFACE(ExtensionInterface, ExtensionInterface_IID)

#endif // EXTENSIONINTERFACE_H
