/* class PluginInterface /Abstract/ {  */
class PluginInterface { 
    %TypeHeaderCode
        #include "plugininterface.h"
        #include <QDebug>
    %End
    public:
        virtual void initialize(NotificationCenter *nc) = 0;
        virtual QJsonObject metadata() const = 0;
        virtual QWidget* centralWidget() = 0;
        virtual QWidget* settingsWidget() = 0;

        virtual QString interfaceVersion() const = 0;
};
