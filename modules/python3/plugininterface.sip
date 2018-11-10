/* class ExtensionInterface /Abstract/ {  */
class ExtensionInterface { 
    %TypeHeaderCode
        #include "extensioninterface.h"
        #include <QDebug>
    %End
    public:
        virtual bool initialize(NotificationCenter *nc) = 0;
        virtual QJsonObject metadata() const = 0;
        virtual QWidget* centralWidget() = 0;
        virtual QWidget* settingsWidget() = 0;
};
