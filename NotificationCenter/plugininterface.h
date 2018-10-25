#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtCore>

class PluginInfo;
class NotificationCenter;
class QWidget;

#define PluginInterface_IID "org.linuxnotifier.NotificationCenter"

typedef QHash<QString, QString> PluginMetadata;

class PluginInterface
{
    public:
        PluginInterface();
        virtual void initialize(NotificationCenter *nc) = 0;
        // this widget will be showed on NotificationCenter
        // return nullptr when no widget
        virtual QWidget* centralWidget() = 0;
        // this widget is showed for settings
        // return nullptr when no widget
        virtual QWidget* settingsWidget() = 0;

        QString interfaceVersion() const;

    private:
        const QString m_interfaceVersion;

    protected:
};

Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_IID)

#endif // PLUGININTERFACE_H
